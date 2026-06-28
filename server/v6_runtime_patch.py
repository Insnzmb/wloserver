"""Runtime integration for the local v6 reconstruction knowledge layer.

This keeps the fork update compact: existing server files can import and call
install_v6_rebuild_knowledge() during startup instead of carrying large inline
patches. The installed behavior is intentionally client-compatible and keeps
the proof boundary visible.
"""

from __future__ import annotations

import logging
from typing import Any

from server.v6_rebuild_knowledge import V6RebuildKnowledge

logger = logging.getLogger("WLO_Server")


def _install_packet_reader_patch() -> None:
    from server.network import PacketReader

    if hasattr(PacketReader, "read_bytes"):
        return

    def read_bytes(self: PacketReader, length: int) -> bytes:
        if length <= 0 or self.offset >= len(self.data):
            return b""
        end = min(len(self.data), self.offset + length)
        value = self.data[self.offset:end]
        self.offset = end
        return value

    PacketReader.read_bytes = read_bytes


def _install_game_server_patch() -> None:
    from server.gameserver import GameServer

    if getattr(GameServer, "_v6_rebuild_patch_installed", False):
        return

    original_init = GameServer.__init__
    original_lookup_portal = GameServer.lookup_portal
    original_update_character_skills = GameServer.update_character_skills

    def patched_init(self: GameServer, *args: Any, **kwargs: Any) -> None:
        original_init(self, *args, **kwargs)
        if not hasattr(self, "v6_knowledge"):
            self.v6_knowledge = V6RebuildKnowledge()
        logger.info("[V6 Knowledge] Loaded local evidence atlas: %s", self.v6_knowledge.summary()["counts"])

    def patched_lookup_portal(
        self: GameServer,
        map_id: int,
        portal_id: int,
        by_click_id: bool = False,
        px: int = 0,
        py: int = 0,
    ) -> tuple:
        dst_map, dst_x, dst_y = original_lookup_portal(self, map_id, portal_id, by_click_id=by_click_id, px=px, py=py)
        if dst_map is not None:
            return dst_map, dst_x, dst_y

        knowledge = getattr(self, "v6_knowledge", None) or V6RebuildKnowledge()
        fixture = knowledge.portal_fixture(map_id, portal_id)
        if fixture:
            logger.info(
                "[Portal] V6 knowledge fixture: map %s portal %s -> Map %s (%s,%s), label=%s, proof=%s, implementation=%s",
                map_id,
                portal_id,
                fixture.dst_map,
                fixture.dst_x,
                fixture.dst_y,
                fixture.label,
                fixture.proof_tier,
                fixture.implementation_tier,
            )
            return fixture.dst_map, fixture.dst_x, fixture.dst_y
        return None, None, None

    def patched_update_character_skills(self: GameServer, session: Any) -> None:
        if not hasattr(self, "v6_knowledge"):
            self.v6_knowledge = V6RebuildKnowledge()

        existing_ids = {int(skill.get("skill_id", 0)) for skill in getattr(session, "skills", [])}
        added = False
        for row in self.v6_knowledge.starter_skill_rows(existing_ids):
            session.skills.append({
                "skill_id": row["skill_id"],
                "grade": row["grade"],
                "exp": row["exp"],
            })
            existing_ids.add(row["skill_id"])
            added = True
            logger.info(
                "[SKILL] Added v6 starter skill %s (%s) to %s; proof=%s",
                row["skill_id"],
                row["source_name"],
                getattr(session, "char_name", ""),
                row["proof_tier"],
            )

        original_update_character_skills(self, session)
        if added and getattr(session, "char_id", 0):
            self.save_player_to_db(session)

    GameServer.__init__ = patched_init
    GameServer.lookup_portal = patched_lookup_portal
    GameServer.update_character_skills = patched_update_character_skills
    GameServer._v6_rebuild_patch_installed = True


def _install_web_admin_patch() -> None:
    try:
        from aiohttp import web
        from server.web_admin import WebAdminServer
    except Exception:
        return

    if getattr(WebAdminServer, "_v6_rebuild_patch_installed", False):
        return

    original_setup_routes = WebAdminServer.setup_routes
    original_handle_status = WebAdminServer.handle_status

    async def handle_v6_knowledge(self: WebAdminServer, request: Any):
        return web.json_response(self.game_server.v6_knowledge.summary())

    async def patched_handle_status(self: WebAdminServer, request: Any):
        response = await original_handle_status(self, request)
        try:
            payload = response.text
            import json
            data = json.loads(payload)
            data["v6_knowledge"] = self.game_server.v6_knowledge.summary()
            return web.json_response(data)
        except Exception:
            return response

    def patched_setup_routes(self: WebAdminServer) -> None:
        original_setup_routes(self)
        try:
            self.app.router.add_get("/api/v6-knowledge", self.handle_v6_knowledge)
        except RuntimeError:
            pass

    WebAdminServer.handle_v6_knowledge = handle_v6_knowledge
    WebAdminServer.handle_status = patched_handle_status
    WebAdminServer.setup_routes = patched_setup_routes
    WebAdminServer._v6_rebuild_patch_installed = True


def install_v6_rebuild_knowledge() -> None:
    """Install compact v6 client-compatible behavior updates."""
    _install_packet_reader_patch()
    _install_game_server_patch()
    _install_web_admin_patch()
