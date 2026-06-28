r"""WLO v6 reconstruction knowledge used by this Python server.

The values in this module are imported from the local B:\WLOTest evidence lane.
They are usable for client-compatible implementation guidance, but only exact
packet captures, decoded request/reply pairs, runtime logs, or state deltas can
promote a behavior above the proof tiers listed here.
"""

from __future__ import annotations

from dataclasses import dataclass
from typing import Dict, Iterable, Optional, Tuple


PACKET_PROVEN = "packet-proven"
RUNTIME_PROVEN = "runtime-proven"
STATE_PROVEN = "state-proven"
DECOMPILE_OBSERVED = "decompile-observed"
CPU_EMULATED = "cpu-emulated"
SYNTHETIC_ONLY = "synthetic-only"
HYPOTHESIS = "hypothesis"


@dataclass(frozen=True)
class ProofBoundary:
    tier: str
    source: str
    boundary: str


@dataclass(frozen=True)
class PortalFixture:
    map_id: int
    click_id: int
    dst_map: int
    dst_x: int = 0
    dst_y: int = 0
    label: str = ""
    proof_tier: str = DECOMPILE_OBSERVED
    implementation_tier: str = SYNTHETIC_ONLY


class V6RebuildKnowledge:
    """Small evidence atlas for the Python server implementation."""

    SOURCE = "B:\\WLOTest local v6 decompile, packet-frame-analysis, and preproof-server evidence"

    DATASET_COUNTS = {
        "map_scenes": 1021,
        "scene_references": 10663,
        "event_command_rows": 63444,
        "answer_branch_rows": 40493,
        "item_rows": 4220,
        "skill_rows": 800,
        "npc_rows": 4102,
        "portal_transition_rows": 2839,
        "npc_dialog_shop_rows": 6410,
        "quest_event_cutscene_rows": 10385,
        "captured_world_object_ids": 150,
    }

    STARTER_SKILLS = {
        1: "Defense",
        2: "Flee",
        5: "Hand Attack",
    }

    ITEM_EFFECT_COUNTS = {
        "items_with_parsed_effects": 1055,
        "parsed_effect_entries": 1265,
        "catalog_tag": 1118,
        "critical_chance_percent": 100,
        "elemental_damage_modifier": 23,
        "stat_bonus": 24,
    }

    BLOCKED_GATES = (
        "No packet-proven portal request/reply pairs for broad map movement.",
        "No packet-proven inventory award bytes, slot layout, capacity, or stacking rules.",
        "No packet-proven quest/event/cutscene command mutation replies.",
        "No packet-proven battle damage, flee, capture, EXP, gold, or drop formulas.",
        "No runtime-proven live-client acceptance for this Python import.",
    )

    PORTAL_FIXTURES = (
        PortalFixture(10000, 1, 12050, label="Residence to Welling Village"),
        PortalFixture(11035, 3, 11034, label="Subway return route"),
        PortalFixture(11036, 12, 11037, label="Subterranean Maze forward route"),
        PortalFixture(11037, 1, 11036, label="Subterranean Maze return route"),
        PortalFixture(12050, 34, 11034, label="Welling Village to Subway route candidate"),
        PortalFixture(12050, 35, 11034, label="Welling Village to Subway route candidate"),
        PortalFixture(12050, 42, 11034, label="Welling Village to Subway route candidate"),
        PortalFixture(12050, 44, 11035, label="Welling Village to Subway alternate route candidate"),
        PortalFixture(12050, 62, 11035, label="Welling Village to Subway alternate route candidate"),
        PortalFixture(12050, 63, 11034, label="Welling Village to Subway route candidate"),
    )

    PROOF = ProofBoundary(
        tier=f"{DECOMPILE_OBSERVED} + {STATE_PROVEN} + {SYNTHETIC_ONLY}",
        source=SOURCE,
        boundary=(
            "Counts and route fixtures are derived from decompiled v6 client data, "
            "current state-harness facts, and synthetic client-compatible behavior. "
            "They are not exact original server reply proof unless separately "
            "packet-proven or runtime-proven."
        ),
    )

    def __init__(self) -> None:
        self._portal_by_key: Dict[Tuple[int, int], PortalFixture] = {
            (fixture.map_id, fixture.click_id): fixture for fixture in self.PORTAL_FIXTURES
        }

    def summary(self) -> dict:
        return {
            "source": self.PROOF.source,
            "proofTier": self.PROOF.tier,
            "boundary": self.PROOF.boundary,
            "counts": dict(self.DATASET_COUNTS),
            "starterSkills": dict(self.STARTER_SKILLS),
            "itemEffectCounts": dict(self.ITEM_EFFECT_COUNTS),
            "portalFixtures": [fixture.__dict__.copy() for fixture in self.PORTAL_FIXTURES],
            "blockedGates": list(self.BLOCKED_GATES),
        }

    def portal_fixture(self, map_id: int, click_id: int) -> Optional[PortalFixture]:
        return self._portal_by_key.get((int(map_id), int(click_id)))

    def starter_skill_rows(self, existing_skill_ids: Iterable[int]) -> list:
        existing = {int(skill_id) for skill_id in existing_skill_ids}
        rows = []
        for skill_id, name in self.STARTER_SKILLS.items():
            if skill_id not in existing:
                rows.append({
                    "skill_id": skill_id,
                    "grade": 1,
                    "exp": 0,
                    "source_name": name,
                    "proof_tier": STATE_PROVEN,
                    "boundary": "Starter skill presence is state-proven in the local guarded runtime; packet/UI byte layout is not promoted by this row.",
                })
        return rows
