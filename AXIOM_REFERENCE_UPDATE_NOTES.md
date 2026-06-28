# Axiom Reference Update Notes

Date: 2026-06-28

This Python server has been updated with a compact WLO v6 reconstruction knowledge layer.

Updated in this fork:

- Added `server/v6_rebuild_knowledge.py` with the B:\WLOTest v6 evidence counts, proof tiers, starter-skill baseline, item-effect counts, blocked proof gates, and guarded portal route fixtures.
- Added `server/v6_runtime_patch.py` to install the knowledge layer into the existing Python server at startup.
- Updated `server/main.py` so startup calls `install_v6_rebuild_knowledge()` before constructing server classes.
- Added runtime support for `PacketReader.read_bytes()` because NPC/object click handling uses it.
- Added v6 starter skills `1 Defense`, `2 Flee`, and `5 Hand Attack` when absent.
- Added v6 portal fixture fallback after normal portal lookup fails.
- Added Web Admin `/api/v6-knowledge` and includes v6 knowledge in `/api/status`.
- Added Python tests in `tests/test_v6_rebuild_knowledge.py`.

Proof boundary:

- Portal fixtures are `synthetic-only` client-compatible fallbacks.
- Dataset counts and starter skill presence come from local decompile/state-harness evidence.
- This update does not prove exact original server reply bytes.
- This update does not prove live-client runtime acceptance.
- This update does not prove broad portal coordinates, quest mutation, item slot/capacity, battle formula, or live-client acceptance.

Verification used locally before upload:

- `python -m compileall -q server tests`
- `python -m unittest tests.test_v6_rebuild_knowledge`
- Direct `GameServer` construction smoke loaded v6 knowledge, 28 handlers, and route fixture `(11036, 12) -> 11037`.
