import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [25]  # Opcode 0x19

async def handle(server, session, reader):
    """Processes player trades and pet secure trades (AC 25)."""
    sub = reader.read_8()
    logger.info(f"[{session.char_name}] AC25 Trade handler. SubCmd={sub}, raw={reader.data.hex()}")
    
    if sub == 1:  # Trade Invitation
        # In a complete secure trade system, we check recipient level >= 25 and stall rules:
        # For simulation, respond with success or a specific status code
        # Status code: 4 (Trade complete)
        writer = PacketWriter().write_8(25).write_8(4)
        await session.send_packet(writer)
    elif sub == 3:  # Feed pet
        writer = PacketWriter().write_8(25).write_8(3).write_8(1)
        await session.send_packet(writer)
    elif sub == 10:  # Release pet
        writer = PacketWriter().write_8(25).write_8(10).write_8(1)
        await session.send_packet(writer)
    else:
        await session.send_packet(PacketWriter().write_8(20).write_8(8))
