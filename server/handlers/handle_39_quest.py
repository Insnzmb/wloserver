import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [39]  # Opcode 0x27

async def handle(server, session, reader):
    """Processes quest journal and settings interactions (AC 39)."""
    sub = reader.read_8()
    logger.info(f"[{session.char_name}] AC39 Quest handler. SubCmd={sub}, raw={reader.data.hex()}")
    
    if sub == 1:  # Quest List/Journal Request
        # Respond with empty quest list for now
        writer = PacketWriter().write_8(39).write_8(1).write_8(0)
        await session.send_packet(writer)
    elif sub == 2:  # Quest Help / Team-up Request
        # Accept help request, echo success response
        writer = PacketWriter().write_8(39).write_8(2).write_8(1)
        await session.send_packet(writer)
    elif sub == 7:  # Abandon/Give up Quest
        writer = PacketWriter().write_8(39).write_8(7).write_8(1)
        await session.send_packet(writer)
    elif sub in (10, 11):  # Quest status updates
        writer = PacketWriter().write_8(39).write_8(sub).write_8(1)
        await session.send_packet(writer)
    elif sub == 12:  # Guild/Organ Member List Request
        # Respond with empty member list (0 members) to prevent client hanging
        writer = PacketWriter().write_8(39).write_8(12).write_8(0)
        await session.send_packet(writer)
    elif sub in (16, 17, 19):  # Quest logs and interactions
        writer = PacketWriter().write_8(39).write_8(sub).write_8(1)
        await session.send_packet(writer)
    elif sub in (50, 51):  # Quest tracking / settings toggles
        writer = PacketWriter().write_8(39).write_8(sub).write_8(1)
        await session.send_packet(writer)
    else:
        # Default fallback to release interaction lock
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
