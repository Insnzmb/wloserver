import logging
import sqlite3
import time
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [20]

async def handle(server, session, reader):
    """Processes portals, chest, and dialog clicks (AC 20)."""
    sub = reader.read_8()
    
    # General constraints based on client findings
    if getattr(session, 'is_fishing', False):
        logger.warning(f"[{session.char_name}] Interaction blocked: Player is currently fishing.")
        await session.send_packet(PacketWriter().write_8(23).write_8(57).write_8(0).write_string("Fishing, can't act"))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
        return
    if getattr(session, 'is_remote_control', False):
        logger.warning(f"[{session.char_name}] Interaction blocked: Remote control active.")
        await session.send_packet(PacketWriter().write_8(23).write_8(57).write_8(0).write_string("Can't perform during remote control"))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
        return
        
    if sub == 8:  # Portal Collision Warp Request
        portal_id = reader.read_16()
        print(f"[PORTAL-RAW] {session.char_name} map={session.map_id} pos=({session.x},{session.y}) portal_id={portal_id} raw={reader.data.hex()}")
        logger.info(f"[{session.char_name}] Stepped on portal ID {portal_id} on map {session.map_id} pos=({session.x},{session.y}) (raw: {reader.data.hex()})")
        
        # Check portal warp cooldown (1.0 seconds)
        current_time = time.time()
        if current_time - getattr(session, 'last_warp_time', 0.0) < 1.0:
            logger.info(f"[{session.char_name}] Ignoring portal collision due to warp cooldown.")
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            return
        
        # Client portal_id may be Gray-coded. Try raw first, then Gray-decoded.
        dst_map, dst_x, dst_y = server.lookup_portal(session.map_id, portal_id, px=session.x, py=session.y)
        if dst_map is None:
            # Try Gray-decoded portal_id
            def _gray_decode(n):
                mask = n
                while mask:
                    mask >>= 1
                    n ^= mask
                return n
            gray_id = _gray_decode(portal_id)
            if gray_id != portal_id:
                logger.info(f"[{session.char_name}] Trying Gray-decoded portal_id: {portal_id} -> {gray_id}")
                dst_map, dst_x, dst_y = server.lookup_portal(session.map_id, gray_id, px=session.x, py=session.y)
        
        if dst_map:
            print(f"[PORTAL] {session.char_name} used portal {portal_id} on map {session.map_id} -> map {dst_map} (x={dst_x}, y={dst_y})")
            logger.info(f"[PORTAL] {session.char_name} used portal {portal_id} on map {session.map_id} -> map {dst_map} (x={dst_x}, y={dst_y})")
            await server.warp_player(session, dst_map, dst_x, dst_y, portal_id)
        else:
            logger.warning(f"[{session.char_name}] Portal {portal_id} not found on map {session.map_id}!")
            # Notify GM chat warning about missing portal destination
            prompt = PacketWriter().write_8(23).write_8(57).write_8(0).write_string(
                f"Portal {portal_id} is not mapped in ServerDataBase.db. Use GM command :warp <map> <x> <y>."
            )
            await session.send_packet(prompt)
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            
    elif sub == 1:  # NPC click
        if reader.remaining_bytes() >= 4:
            reader.read_bytes(3)  # Skip 3 bytes (unk/padding)
            click_id = reader.read_8()
        else:
            click_id = reader.read_8() if reader.remaining_bytes() > 0 else 0
        native_click_id = click_id
        logger.info(f"[{session.char_name}] Clicked NPC/Object ID {click_id} on map {session.map_id} (native ID: {native_click_id})")

        # Find the clicked NPC in the map NPCs list
        map_npcs = server.map_npcs.get(session.map_id, [])
        npc = None
        for n in map_npcs:
            if n['click_id'] == native_click_id:
                npc = n
                break
        
        if npc:
            # Distance check (0xa9 = 169 pixels limit)
            npc_x = npc.get('x', 0)
            npc_y = npc.get('y', 0)
            if abs(session.x - npc_x) > 169 or abs(session.y - npc_y) > 169:
                logger.warning(f"[{session.char_name}] NPC interaction blocked: NPC too far X={abs(session.x - npc_x)} Y={abs(session.y - npc_y)}")
                await session.send_packet(PacketWriter().write_8(20).write_8(8))  # Release client lock
                return

            # --- DOOR / PORTAL TRIGGER CHECK ---
            linked_portals = npc.get('linked_portals', [])
            if linked_portals:
                portal_id = linked_portals[0]
                logger.info(f"[{session.char_name}] NPC {native_click_id} is a door - triggering portal {portal_id} on map {session.map_id}")
                dst_map, dst_x, dst_y = server.lookup_portal(session.map_id, portal_id)
                if dst_map:
                    logger.info(f"[DOOR] {session.char_name} used door NPC {native_click_id} (portal {portal_id}) -> map {dst_map} ({dst_x},{dst_y})")
                    await server.warp_player(session, dst_map, dst_x, dst_y, portal_id)
                else:
                    logger.warning(f"[DOOR] Door NPC {native_click_id} linked portal {portal_id} has no destination on map {session.map_id}!")
                    await session.send_packet(PacketWriter().write_8(20).write_8(8))
                return
            
            npc_id = npc['npc_id']
            
            # Dynamic NPC ID mapping resolver
            db_id = None
            row = None
            try:
                conn = sqlite3.connect(server.static_db_path)
                conn.row_factory = sqlite3.Row
                
                overrides = {
                    (10017, 9): 25787,
                    (10017, 10): 25789,
                    (10017, 3): 25786,
                    (10017, 11): 25786,
                }
                if (session.map_id, native_click_id) in overrides:
                    db_id = overrides[(session.map_id, native_click_id)]
                    row = conn.execute("SELECT * FROM npc_data WHERE id = ?", (db_id,)).fetchone()
                
                if not row:
                    # Pre-decode client-side special template ID mappings
                    client_mappings = {
                        0x908e: 0x5209,
                        0x9092: 0x9090,
                        0x9093: 0x9091,
                        0x9094: 0x9095,
                        0x9096: 0x9097
                    }
                    mapped_npc_id = client_mappings.get(npc_id & 0xFFFF, npc_id)
                    dec_no_offset = (mapped_npc_id & 0xFFFF) ^ 0x5209
                    dec_with_offset = dec_no_offset - 9
                    candidates = [
                        dec_no_offset,
                        dec_with_offset,
                        dec_no_offset + 27000,
                        dec_with_offset + 27000,
                        dec_no_offset + 10000,
                        dec_with_offset + 10000,
                        npc_id * 2,
                        npc_id + 16000,
                        npc_id
                    ]
                    for cand_id in candidates:
                        r = conn.execute("SELECT * FROM npc_data WHERE id = ?", (cand_id,)).fetchone()
                        if r:
                            db_id = cand_id
                            row = r
                            break
                            
                if not row:
                    for tid in [npc_id - 1, npc_id]:
                        r = conn.execute("SELECT * FROM npc_data WHERE map_tid = ? LIMIT 1", (tid,)).fetchone()
                        if r:
                            db_id = r['id']
                            row = r
                            break
                
                if not row:
                    db_id = npc_id * 2
                    row = conn.execute("SELECT * FROM npc_data WHERE id = ?", (db_id,)).fetchone()
                    
                conn.close()
            except Exception as e:
                logger.error(f"[NPC Click] Error querying npc_data: {e}")
            
            logger.info(f"[NPC Click] Clicked NPC '{npc['name']}' (ID: {click_id}, template: {npc_id}, db_id: {db_id})")
            
            if row:
                name = (row['name'] or "").strip('\x00').strip()
                npc_template_id = npc_id
                talk_id = 1
                logger.info(f"[NPC Click] Query success: name='{name}', npc_template={npc_template_id}, talk_id={talk_id}")
            else:
                name = "NPC"
                npc_template_id = npc_id
                talk_id = 1
                logger.info(f"[NPC Click] Query failed. Using defaults.")
                
            # ── QUEST BATTLES ──
            quest_info = server.quest_manager.get_quest_battle(npc_template_id)
            if quest_info:
                logger.info(f"[{session.char_name}] Starting quest battle with NPC {npc_template_id}!")
                session.quest_battle_id = npc_template_id
                session.battle_win_warp = {
                    "map_id": quest_info["win_map_id"],
                    "x": quest_info["win_x"],
                    "y": quest_info["win_y"]
                }
                session.battle_bg_id = quest_info["bg_id"]
                battle_sprite = quest_info["battle_sprite_id"]
                
                await server.enter_battle(session, native_click_id, npc_template_id, battle_sprite)
                return    
                
            # Check if the NPC is a shopkeeper or merchant
            is_shopkeeper = any(x in name.lower() for x in ["shopkeeper", "merchant", "clerk", "taverner", "bartender", "pet keeper"])
            if is_shopkeeper or native_click_id == 23:
                if "props" in name.lower() or native_click_id == 23:
                    dialog_hex = "140100000001060317000000000000050001"
                    dialog_bytes = bytes.fromhex(dialog_hex)[2:]
                    pkt = PacketWriter().write_8(20).write_8(1).write_bytes(dialog_bytes)
                    await session.send_packet(pkt)
                    return
                    
                shop_id = 34 if "weapon" in name.lower() else 31
                
                for s_id in [shop_id, 2, native_click_id]:
                    shop_pkt = PacketWriter()
                    shop_pkt.write_8(54).write_8(89).write_8(s_id).write_8(2)
                    
                    shop_pkt.write_16(602).write_8(1)
                    shop_pkt.write_16(603).write_8(1)
                    
                    shop_pkt.write_16(701).write_8(2)
                    shop_pkt.write_16(702).write_8(2)
                    shop_pkt.write_16(703).write_8(2)
                    
                    await session.send_packet(shop_pkt)
                    
                    open_shop = PacketWriter()
                    open_shop.write_8(54).write_8(1).write_8(s_id).write_8(native_click_id)
                    await session.send_packet(open_shop)
                
                await session.send_packet(PacketWriter().write_8(20).write_8(8))
            else:
                # Check if the NPC is a combat/monster NPC
                dec_no_offset = (npc_template_id & 0xFFFF) ^ 0x5209
                decoded_id = dec_no_offset - 9
                is_monster = (
                    str(npc_template_id) in server.drop_tables or
                    (db_id is not None and str(db_id) in server.drop_tables) or
                    str(decoded_id) in server.drop_tables or
                    str(decoded_id + 27000) in server.drop_tables or
                    str(decoded_id + 10000) in server.drop_tables or
                    any(x in name.lower() for x in ["monster", "spider", "wolf", "troll", "grape", "crab", "gelly", "wasp", "snake", "boar", "brother", "sister", "lord", "dinosaur", "stegosaurus", "shark"]) or
                    (17000 <= npc_template_id <= 18000)
                )
                if is_monster:
                    logger.info(f"[{session.char_name}] Clicked monster NPC {npc_template_id} ({name}) -> entering battle!")
                    await server.enter_battle(session, native_click_id, npc_template_id)
                    return

                # ── CUSTOM QUEST INTERACTORS ──
                # Grandma Quest (Ill Grandma)
                if "grandma" in name.lower():
                    if not hasattr(session, 'quests') or session.quests is None:
                        session.quests = {}
                    state = session.quests.get('grandma', 0)
                    
                    if state == 0:
                        dialogue_text = "Ah... Çok hastayım. Eğer Bick'in evinden bana Kara İlaç (Black Medicine) getirebilirsen çok sevinirim..."
                        session.quests['grandma'] = 1
                        server.save_player_to_db(session)
                    elif state == 1:
                        # Check if player has Black Medicine (30259)
                        has_medicine = False
                        med_item = None
                        for item in session.inventory:
                            if item.get('item_id') == 30259 and item.get('amount', 0) > 0:
                                has_medicine = True
                                med_item = item
                                break
                        
                        if has_medicine:
                            # Remove medicine
                            med_item['amount'] = med_item.get('amount', 1) - 1
                            if med_item['amount'] <= 0:
                                session.inventory.remove(med_item)
                            
                            # Add rewards: 500 Gold, 200 Exp, White Wool (30264)
                            session.gold += 500
                            session.exp += 200
                            
                            # Send gold update
                            await session.send_packet(PacketWriter().write_8(26).write_8(4).write_32(session.gold))
                            
                            # Add White Wool (30264)
                            from server.gameserver import add_item_to_inventory
                            add_item_to_inventory(session, 30264, amount=1)
                            
                            # Send inventory update
                            await session.send_packet(server.build_inventory_packet(session))
                            
                            dialogue_text = "Çok teşekkürler! Bu Kara İlaç tam ihtiyacım olan şeydi. Kendimi çok daha iyi hissediyorum. Lütfen bu ödülü kabul et! (500 Altın, 200 Tecrübe ve Yün kazandın)"
                            session.quests['grandma'] = 2
                            server.save_player_to_db(session)
                        else:
                            dialogue_text = "Lütfen Bick'in evindeki Kara İlaç'ı (Black Medicine) bulup bana getir... Çok halsizim..."
                    else:
                        dialogue_text = "Tekrar teşekkürler evladım, sayende çok iyiyim!"
                        
                    # Show dialogue and unlock
                    pkt = PacketWriter().write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                    await session.send_packet(pkt)
                    await session.send_packet(PacketWriter().write_8(20).write_8(8))
                    return

                # Mary Lou Quest (Saç Bandı)
                elif "mary lou" in name.lower():
                    if not hasattr(session, 'quests') or session.quests is None:
                        session.quests = {}
                    state = session.quests.get('mary', 0)
                    
                    if state == 0:
                        dialogue_text = "Merhaba! En sevdiğim Saç Bandımı (Headband) ormanda kaybettim. Onu bulup bana getirebilir misin?"
                        session.quests['mary'] = 1
                        server.save_player_to_db(session)
                    elif state == 1:
                        # Check if player has Headband (22061)
                        has_band = False
                        band_item = None
                        for item in session.inventory:
                            if item.get('item_id') == 22061 and item.get('amount', 0) > 0:
                                has_band = True
                                band_item = item
                                break
                        
                        if has_band:
                            # Remove headband
                            band_item['amount'] = band_item.get('amount', 1) - 1
                            if band_item['amount'] <= 0:
                                session.inventory.remove(band_item)
                            
                            # Add rewards: 200 Gold, 100 Exp, White Rabbit Fur (46015)
                            session.gold += 200
                            session.exp += 100
                            
                            # Send gold update
                            await session.send_packet(PacketWriter().write_8(26).write_8(4).write_32(session.gold))
                            
                            # Add White Rabbit Fur
                            from server.gameserver import add_item_to_inventory
                            add_item_to_inventory(session, 46015, amount=1)
                            
                            # Send inventory update
                            await session.send_packet(server.build_inventory_packet(session))
                            
                            dialogue_text = "Saç bandımı bulmuşsun! Çok teşekkür ederim, artık saçlarımı toplayabilirim. Al bakalım bu senin ödülün! (200 Altın, 100 Tecrübe ve Tavşan Postu kazandın)"
                            session.quests['mary'] = 2
                            server.save_player_to_db(session)
                        else:
                            dialogue_text = "Lütfen Saç Bandımı bulursan bana getir. Kuzey adasındaki ormanda kaybetmiş olmalıyım..."
                    else:
                        dialogue_text = "Saç bandımı geri getirdiğin için tekrar teşekkürler!"
                        
                    pkt = PacketWriter().write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                    await session.send_packet(pkt)
                    await session.send_packet(PacketWriter().write_8(20).write_8(8))
                    return

                # Niss Quest (Save Niss)
                elif "niss" in name.lower():
                    if not hasattr(session, 'quests') or session.quests is None:
                        session.quests = {}
                    state = session.quests.get('niss', 0)
                    
                    if state == 0:
                        dialogue_text = "İmdat! Bu kafese canavarlar tarafından kilitlendim... Lütfen beni kurtar!"
                        pkt = PacketWriter().write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                        await session.send_packet(pkt)
                        await session.send_packet(PacketWriter().write_8(20).write_8(8))
                        
                        # Trigger Niss quest battle vs Wolf (Level 10)
                        session.quest_battle_id = 11066
                        session.battle_win_warp = {
                            "map_id": session.map_id,
                            "x": session.x,
                            "y": session.y
                        }
                        session.battle_bg_id = 4
                        # Enter battle: click ID, npc template ID, battle sprite (11066)
                        await server.enter_battle(session, native_click_id, npc_template_id, 11066)
                        return
                    elif state == 1:
                        # Give pet reward: Niss (ID 11066)
                        # Check if player already has Niss
                        has_niss = any(p.get('pet_id') == 11066 for p in session.pets)
                        if not has_niss:
                            # Add pet to companion list
                            lvl = 1
                            base_con = 5
                            base_wis = 5
                            base_str = 5
                            base_agi = 5
                            base_int = 5
                            max_hp = 180 + base_con * 2 + 1
                            max_sp = 94 + base_wis * 2 + 1
                            
                            pet_data = {
                                "pet_id": 11066,
                                "level": lvl,
                                "exp": 0,
                                "amity": 100,
                                "reborn": 0,
                                "potential": 0,
                                "str": base_str,
                                "con": base_con,
                                "int": base_int,
                                "wis": base_wis,
                                "agi": base_agi,
                                "hp": max_hp,
                                "sp": max_sp
                            }
                            session.pets.append(pet_data)
                            server.save_player_to_db(session)
                            
                            # Companion dynamics addition packet 15, 1
                            pkt = PacketWriter().write_8(15).write_8(1)
                            pkt.write_32(session.char_id).write_32(11066).write_8(lvl).write_32(0)
                            pkt.write_8(1).write_32(0)
                            pkt.write_8(1).write_32(0)
                            pkt.write_8(1).write_32(0)
                            pkt.write_8(1).write_16(0).write_16(0).write_8(0)
                            await session.send_packet(pkt)
                            
                            # Refresh pet list UI
                            await server.send_pet_list(session)
                            
                            dialogue_text = "Beni kurtardığın için teşekkür ederim! Yolculuğunda sana eşlik etmek istiyorum. (Niss grubuna katıldı!)"
                            session.quests['niss'] = 2
                            server.save_player_to_db(session)
                        else:
                            dialogue_text = "Zaten benimle birliktesin!"
                            session.quests['niss'] = 2
                            server.save_player_to_db(session)
                            
                        pkt = PacketWriter().write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                        await session.send_packet(pkt)
                        await session.send_packet(PacketWriter().write_8(20).write_8(8))
                        return
                    else:
                        dialogue_text = "Hazırım, gidelim!"
                        pkt = PacketWriter().write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                        await session.send_packet(pkt)
                        await session.send_packet(PacketWriter().write_8(20).write_8(8))
                        return

                # Check if NPC has a quest script
                is_starter_map = 10000 <= session.map_id < 10100
                
                quest_trigger_id = None
                if db_id and db_id in server.quest_scripts:
                    quest_trigger_id = db_id
                elif native_click_id in server.quest_scripts:
                    if native_click_id >= 100 or is_starter_map:
                        quest_trigger_id = native_click_id
                        
                if quest_trigger_id is not None:
                    script = server.quest_scripts[quest_trigger_id]
                    if len(script) > 0:
                        logger.info(f"[{session.char_name}] Starting quest script for NPC {quest_trigger_id} (clicked {native_click_id})")
                        session.active_quest_id = quest_trigger_id
                        session.active_quest_step = 0
                        session.active_quest_dialog_counter = 1
                        action = script[0]
                        if action["type"] == "dialog":
                            portrait = 3 if action.get('is_quest') else 7
                            await server._send_quest_dialogue(session, action["hex"], native_click_id, step=1, portrait_type=portrait)
                        return

                # Default fallback dialogue
                dialogue_text = "Hello, traveller! Beautiful day, isn't it? Let me know if you need anything."
                pkt = PacketWriter()
                pkt.write_8(52).write_8(1).write_16(1).write_string(dialogue_text)
                logger.info(f"[NPC Click] Sending dialogue (AC 52 Sub 1): talk_id=1, text='{dialogue_text}'")
                await session.send_packet(pkt)
                
                await session.send_packet(PacketWriter().write_8(20).write_8(8))
                
    elif sub == 6:  # Continue interaction
        logger.info(f"[{session.char_name}] Continue interaction (AC 20 Sub 6)")
        
        # Check post-battle quest warp
        win_warp = getattr(session, 'battle_win_warp', None)
        if win_warp:
            session.battle_win_warp = None
            logger.info(f"[{session.char_name}] Triggering post-battle quest warp to map {win_warp['map_id']} pos=({win_warp['x']},{win_warp['y']})")
            
            # Niss quest check:
            if getattr(session, 'quest_battle_id', None) == 11066:
                if not hasattr(session, 'quests') or session.quests is None:
                    session.quests = {}
                session.quests['niss'] = 1  # State 1: saved Niss (waiting for pet claim)
                server.save_player_to_db(session)
                session.quest_battle_id = None
                
            await server.warp_player(session, win_warp['map_id'], win_warp['x'], win_warp['y'])
            return
        
        # Check pending battle unlock
        if getattr(session, 'pending_battle_unlock', False):
            session.pending_battle_unlock = False
            logger.info(f"[{session.char_name}] Post-battle unlock: sending map ready and unlock")
            await session.send_packet(PacketWriter().write_8(23).write_8(102))
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            return
            
        # Handle active quest script
        if session.active_quest_id is not None:
            script = server.quest_scripts.get(session.active_quest_id, [])
            session.active_quest_step += 1
            
            if session.active_quest_step >= len(script):
                logger.info(f"[{session.char_name}] Finished quest script for NPC {session.active_quest_id}")
                session.active_quest_id = None
                session.active_quest_step = 0
                await session.send_packet(PacketWriter().write_8(20).write_8(8))
                return
            
            action = script[session.active_quest_step]
            step_num = getattr(session, 'active_quest_dialog_counter', 1)
            
            if action["type"] == "spawn":
                await server._send_quest_spawn(session, action["hex"])
                if "dialog_hex" in action:
                    await server._send_quest_dialogue(session, action["dialog_hex"], session.active_quest_id, step=step_num)
                    session.active_quest_dialog_counter = step_num + 1
            elif action["type"] == "dialog":
                portrait = 3 if action.get('is_quest') else 7
                await server._send_quest_dialogue(session, action["hex"], session.active_quest_id, step=step_num, portrait_type=portrait)
                session.active_quest_dialog_counter = step_num + 1
            elif action["type"] == "flag":
                await server._send_quest_flag(session, action["quest_id"], action["state"])
                next_step = session.active_quest_step + 1
                if next_step < len(script) and script[next_step]["type"] == "dialog":
                    session.active_quest_step = next_step
                    next_action = script[next_step]
                    portrait = 3 if next_action.get('is_quest') else 7
                    await server._send_quest_dialogue(session, next_action["hex"], session.active_quest_id, step=step_num, portrait_type=portrait)
                    session.active_quest_dialog_counter = step_num + 1
                else:
                    logger.info(f"[{session.char_name}] Quest script flag sent. Unlocking.")
                    session.active_quest_id = None
                    session.active_quest_step = 0
                    session.active_quest_dialog_counter = 1
                    await session.send_packet(PacketWriter().write_8(20).write_8(8))
            
            return

        await session.send_packet(PacketWriter().write_8(20).write_8(8))
        
    elif sub == 9 or sub == 2:  # Select dialogue option (sub=9 legacy, sub=2 client-accurate)
        option_id = reader.read_8()
        logger.info(f"[{session.char_name}] Selected dialogue option {option_id} (Hex: {hex(option_id)}) (sub={sub})")
        
        # Marriage Wedding Dress Check (Option 14: hold hands / oath)
        if option_id == 14:
            has_wedding_dress = False
            for equip_id in session.equipments:
                item_name = server.items.get(str(equip_id), "")
                if "wedding" in item_name.lower() or "dress" in item_name.lower():
                    has_wedding_dress = True
                    break
            if not has_wedding_dress:
                logger.warning(f"[{session.char_name}] Marriage blocked: Bride needs to dress up.")
                await session.send_packet(PacketWriter().write_8(23).write_8(57).write_8(0).write_string("Bride needs to dress up"))
                await session.send_packet(PacketWriter().write_8(20).write_8(8))
                return

        if option_id == 0x1f:  # Option 31: Buy
            await session.send_packet(PacketWriter().write_8(27).write_8(3))
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            return
        elif option_id == 0x1e:  # Option 30: Sell
            sell_hex = "140100000001060317000000000000060002"
            sell_bytes = bytes.fromhex(sell_hex)[2:]
            pkt = PacketWriter().write_8(20).write_8(1).write_bytes(sell_bytes)
            await session.send_packet(pkt)
            return
            
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
    else:
        logger.warning(f"[{session.char_name}] Unhandled AC 20 Sub: {sub}")
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
