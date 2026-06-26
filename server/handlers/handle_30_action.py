import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [30]

async def handle(server, session, reader):
    """Handles item selling to NPC shop (AC 30)."""
    sub = reader.read_8()
    logger.info(f"[AC30] handle_action_30 called. SubCmd={sub}, data: {reader.data.hex()}")
    
    from server.gameserver import get_item_at_slot, remove_item_at_slot
    
    if sub == 2:  # Sell item request
        slot_idx = reader.read_8()  # inventory slot (1-50)
        amount = reader.read_8() if reader.remaining_bytes() > 0 else 1
        
        item = get_item_at_slot(session, slot_idx)
        if item:
            item_id = item['item_id']
            # Determine selling price
            item_sell_prices = {602: 10, 603: 20, 701: 40, 702: 30, 703: 50}
            sell_price = item_sell_prices.get(item_id, 10) * amount
            
            # Remove from inventory
            remove_item_at_slot(session, slot_idx, amount)
            session.gold += sell_price
            server.save_player_to_db(session)
            
            # Send gold update: [26, 4, gold]
            await session.send_packet(PacketWriter().write_8(26).write_8(4).write_32(session.gold))
            
            # Send slot update: [23, 9, slot_idx, remaining_amount]
            remaining_amt = 0
            for it in session.inventory:
                if it.get('slot') == slot_idx:
                    remaining_amt = it.get('amount', 0)
                    break
            await session.send_packet(PacketWriter().write_8(23).write_8(9).write_8(slot_idx).write_8(remaining_amt))
            
            # Send sell confirmation: [30, 2, sell_price LE, 28 bytes padding]
            confirm_pkt = PacketWriter().write_8(30).write_8(2).write_32(sell_price).write_bytes(bytes(28))
            await session.send_packet(confirm_pkt)
            
            # Also send UI unlock
            await session.send_packet(PacketWriter().write_8(30).write_8(7))
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            logger.info(f"[{session.char_name}] Sold item {item_id} (amount={amount}) for {sell_price} gold.")
        else:
            logger.warning(f"[AC30] Inventory slot {slot_idx} is empty.")
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
    elif sub == 1:  # Open sell menu confirm
        await session.send_packet(PacketWriter().write_8(30).write_8(5).write_8(1).write_8(1))
        await session.send_packet(PacketWriter().write_8(30).write_8(6))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
