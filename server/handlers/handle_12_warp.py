import logging
import time
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [12]

async def handle(server, session, reader):
    """Processes map loading complete response from client (AC 12)."""
    sub = reader.read_8()
    if sub == 1:
        session.is_warping = False
        session.in_map = True
        
        # Set warp cooldown timestamp when warp completes successfully
        session.last_warp_time = time.time()
        
        # Send warp completion unlock packets
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
        await session.send_packet(PacketWriter().write_8(5).write_8(4))
        
        # Broadcast our appearance to other players on new map (remote format)
        server.broadcast_to_map(session.map_id, server.build_remote_char_spawn(session), exclude_session=session)
        
        logger.info(f"[{session.char_name}] Warp completed successfully.")
