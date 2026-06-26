import logging

logger = logging.getLogger("WLO_Server")

ACTION_CODES = [11]

async def handle(server, session, reader):
    """AC 11: Client request to start combat or flee."""
    sub = reader.read_8()
    logger.info(f"[{session.char_name}] handle_combat sub={sub}")
    if sub == 1:
        # Flee (escape) request
        escape_type = reader.read_8() if reader.remaining_bytes() > 0 else 0
        logger.info(f"[{session.char_name}] Flee request: escape_type={escape_type}")
        battle_id = getattr(session, 'pvp_battle_id', None)
        if battle_id and battle_id in server.active_battles:
            battle = server.active_battles[battle_id]
            await server._do_flee(session, battle)
    elif sub == 2:
        # Client clicked on NPC to start combat
        if reader.remaining_bytes() < 7:
            logger.warning(f"[{session.char_name}] handle_combat sub=2 has too few bytes: {reader.remaining_bytes()}")
            return
        pk_type = reader.read_8()
        raw_target_id = reader.read_32()
        npc_id = raw_target_id >> 8
        npc_click_id = reader.read_16()
        logger.info(f"[{session.char_name}] Combat request: pk_type={pk_type} npc_id={npc_id} npc_click={npc_click_id}")
        await server._start_pve_battle(session, npc_click_id, npc_id)
