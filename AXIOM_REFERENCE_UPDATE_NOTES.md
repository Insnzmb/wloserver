# Axiom Reference Update Notes

Date: 2026-06-28

This local working copy was created as an isolated Python-server update target.

Credit:

- WLO v6 reconstruction project credit: Insane Zombie.
- The server knowledge API exposes this credit in `V6RebuildKnowledge.summary()`.

Updated in this Python server:

- Added `server/v6_rebuild_knowledge.py` with the B:\WLOTest v6 evidence counts, proof tiers, starter-skill baseline, item-effect counts, blocked proof gates, and guarded portal route fixtures.
- Added `PacketReader.read_bytes()` because `handle_20_interaction.py` already uses it for NPC/object clicks.
- Wired `V6RebuildKnowledge` into `server/gameserver.py`.
- Added v6 starter skills `1 Defense`, `2 Flee`, and `5 Hand Attack` as state-proven baseline skills when absent.
- Added v6 portal fixture fallback after DB/eve.Emg lookup fails.
- Exposed the evidence atlas through Web Admin `/api/status` and `/api/v6-knowledge`.
- Added Python unit tests in `tests/test_v6_rebuild_knowledge.py`.
- Added `tools/harvest_wlo_v6_knowledge.py` to import bounded B/F packet, script, catalog, runtime, and harness evidence into `server/data/v6_exhaustive_knowledge.json`.
- Updated `server/v6_rebuild_knowledge.py` so the Python server loads the harvested knowledge and exposes it in `/api/v6-knowledge`.

Latest harvest summary:

- B root scanned: available.
- F root scanned: unavailable in this environment, recorded as unavailable.
- Files scanned: 12,339.
- CSV rows scanned: 9,641,358.
- Bytes scanned: 1,681,821,382.
- Packet-category source files: 9,733.
- Runtime-category source files: 2,245.
- Script-category source files: 18.
- Server-harness source files: 85.
- Packet-proven source-tier count: 876.
- Runtime-proven source-tier count: 1,827.
- Decompile-observed source-tier count: 358.

Proof boundary:

- Portal fixtures are `synthetic-only` client-compatible fallbacks.
- Dataset counts and starter skill presence come from local decompile/state-harness evidence.
- Harvested packet/script/catalog rows retain their source proof tier; they are not promoted to exact original server replies unless the source contains exact bytes or decoded request/response proof.
- They are not exact original server byte proof for this Python server.
- They do not prove live-client runtime acceptance.
- They do not prove broad portal coordinates, quest mutation, item slot/capacity, battle formula, or live-client acceptance.
- F:\_WLO_SUPER_ORGANIZED was not mounted in the current environment during the latest harvest, so the generated data records F as unavailable instead of pretending it was scanned.

Current Python server files updated:

- `server/v6_rebuild_knowledge.py`
- `server/data/v6_exhaustive_knowledge.json`
- `tools/harvest_wlo_v6_knowledge.py`
- `tests/test_v6_rebuild_knowledge.py`
- `CREDITS.md`

Verification:

- `python -m compileall -q server tests tools`
- `python -m unittest tests.test_v6_rebuild_knowledge`
