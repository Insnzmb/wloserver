import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [6]

async def handle(server, session, reader):
    """Processes character walking movement (AC 6)."""
    sub = reader.read_8()
    if sub == 1:
        direction = reader.read_8()
        x = reader.read_16()
        y = reader.read_16()
        
        session.x = x
        session.y = y
        
        # Save to database on movement
        server.save_player_to_db(session)
        
        # Broadcast movement update to map
        mov = PacketWriter()
        mov.write_8(6).write_8(1)
        mov.write_32(session.char_id)
        mov.write_8(direction)
        mov.write_16(x)
        mov.write_16(y)
        server.broadcast_to_map(session.map_id, mov, exclude_session=session)
        
        # Check auto-aggro (proximity combat)
        if not getattr(session, 'in_battle', False):
            await server.check_proximity_combat(session)
