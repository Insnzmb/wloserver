import logging

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [37]

async def handle(server, session, reader):
    """Processes companion detail requests (AC 37)."""
    sub = reader.read_8()
    if sub == 1:
        slot = reader.read_8()
        logger.info(f"[{session.char_name}] Requested stats for pet in slot {slot}")
        await server.send_pet_stats(session, slot)
