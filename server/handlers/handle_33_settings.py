import logging
from server.network import PacketWriter

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [33]

async def handle(server, session, reader):
    """Processes settings changes (AC 33)."""
    sub = reader.read_8()
    if sub == 1:
        setting_type = reader.read_8()
        if setting_type == 1:
            session.pkable = not session.pkable
            val = 1 if session.pkable else 2
        elif setting_type == 2:
            session.joinable = not session.joinable
            val = 1 if session.joinable else 2
        elif setting_type == 4:
            session.tradable = not session.tradable
            val = 1 if session.tradable else 2
        else:
            return
            
        resp = PacketWriter().write_8(33).write_8(1).write_8(setting_type).write_8(val)
        await session.send_packet(resp)
