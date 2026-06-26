import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [31]

async def handle(server, session, reader):
    """Handles item purchasing from NPC shop (AC 31)."""
    sub = reader.read_8()
    logger.info(f"[AC31] handle_action_31 called. SubCmd={sub}, data: {reader.data.hex()}")
    
    if sub == 2:  # Confirm purchase step 1
        await session.send_packet(PacketWriter().write_8(31).write_8(2).write_32(0xFFFFFFFF))
        await session.send_packet(PacketWriter().write_8(31).write_8(7))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
    elif sub == 3:  # Purchase finalization
        shop_id = reader.read_8() if reader.remaining_bytes() > 0 else 31
        await session.send_packet(PacketWriter().write_8(31).write_8(3).write_8(1).write_8(3))
        await session.send_packet(PacketWriter().write_8(31).write_8(9))
        await session.send_packet(PacketWriter().write_8(31).write_8(12))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
    elif sub == 12:
        await session.send_packet(PacketWriter().write_8(31).write_8(12))
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
    else:
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
