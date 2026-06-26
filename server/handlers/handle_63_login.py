import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [63]

async def handle(server, session, reader):
    """Handles user authentication, slot updates (AC 63)."""
    sub = reader.read_8()
    
    if sub == 4:  # Login Authentication
        username = reader.read_string()
        password = reader.read_string()
        
        logger.info(f"[Auth] Username '{username}' attempting login...")
        
        # Check database credentials
        user_data = server.db.verify_user(username, password)
        
        if not user_data:
            # User doesn't exist, execute Auto-Registration
            user_id, err = server.db.register_user(username, password)
            if user_id:
                logger.info(f"[Auth] Auto-registered new account: '{username}'")
                user_data = server.db.verify_user(username, password)
            else:
                logger.error(f"[Auth] Auto-registration failed for '{username}': {err}")
                
        if user_data:
            session.user_id = user_data['id']
            session.username = user_data['username']
            session.cipher = user_data['cipher']
            
            # Send Login Success
            success_pkt = PacketWriter()
            success_pkt.write_8(63)
            success_pkt.write_8(2)
            success_pkt.write_32(session.user_id)
            await session.send_packet(success_pkt)
            
            # Send Character List
            list_pkt = PacketWriter()
            list_pkt.write_8(63)
            list_pkt.write_8(1)
            
            # Slot 1 character
            char1 = server.db.get_character_by_id(user_data['character1_id'])
            if char1:
                list_pkt.write_bytes(server.serialize_character_slot(char1))
            
            # Slot 2 character
            char2 = server.db.get_character_by_id(user_data['character2_id'])
            if char2:
                list_pkt.write_bytes(server.serialize_character_slot(char2))
                
            await session.send_packet(list_pkt)
            
            # Send AC 35, Sub 11
            await session.send_packet(PacketWriter().write_8(35).write_8(11))
        else:
            # Login failure
            fail_pkt = PacketWriter()
            fail_pkt.write_8(63).write_8(2)
            await session.send_packet(fail_pkt)
            await session.send_packet(PacketWriter().write_8(1).write_8(6))

    elif sub == 2:  # Selected Character Slot
        slot = reader.read_8()
        if slot not in (1, 2):
            await session.send_packet(PacketWriter().write_8(0).write_8(32))
            return
            
        # Query slot character
        with server.db.get_connection() as conn:
            row = conn.execute("SELECT id FROM characters WHERE user_id = ? AND slot = ?", (session.user_id, slot)).fetchone()
            char_id = row['id'] if row else 0
            
        if not char_id:
            # No character in slot: request creation
            create_req = PacketWriter()
            create_req.write_8(1)
            create_req.write_8(3)
            create_req.write_bool(bool(session.cipher))
            await session.send_packet(create_req)
        else:
            # Character exists: confirm login
            server.load_character_into_session(session, char_id)
            
            confirm = PacketWriter()
            confirm.write_8(63)
            confirm.write_8(2)
            confirm.write_32(session.char_id)
            await session.send_packet(confirm)
            
            # Commence Map Entry!
            await server.commence_login(session)
