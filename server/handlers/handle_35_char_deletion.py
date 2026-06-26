import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [35]

async def handle(server, session, reader):
    """Processes character slot deletion (AC 35)."""
    sub = reader.read_8()
    if sub == 2:  # Delete Character request
        slot = reader.read_8()
        reader.read_string()  # Unknown string
        password = reader.read_string()
        
        # Allow deletion if cipher matches or is empty
        matches = not session.cipher or session.cipher == password
        
        if matches:
            # Fetch character ID
            with server.db.get_connection() as conn:
                row = conn.execute("SELECT id FROM characters WHERE user_id = ? AND slot = ?", (session.user_id, slot)).fetchone()
                char_id = row['id'] if row else 0
                
            if char_id:
                server.db.delete_character(char_id)
                logger.info(f"[Char] Character in slot {slot} deleted successfully.")
                
            # Deletion success packet sequences
            await session.send_packet(PacketWriter().write_8(24).write_8(5).write_8(53).write_8(0).write_8(0))
            await session.send_packet(PacketWriter().write_8(24).write_8(5).write_8(52).write_8(0).write_8(0))
            await session.send_packet(PacketWriter().write_8(24).write_8(5).write_8(54).write_8(0).write_8(0))
            await session.send_packet(PacketWriter().write_8(24).write_8(5).write_8(183).write_8(0).write_8(0))
            await session.send_packet(PacketWriter().write_8(20).write_8(8))
            
            resp = PacketWriter().write_8(35).write_8(2).write_8(1).write_8(slot)
            await session.send_packet(resp)
        else:
            # Cipher mismatch
            resp = PacketWriter().write_8(35).write_8(2).write_8(3).write_8(slot)
            await session.send_packet(resp)
