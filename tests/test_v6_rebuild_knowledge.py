import unittest

from server.network import PacketReader
from server.v6_runtime_patch import install_v6_rebuild_knowledge
from server.v6_rebuild_knowledge import (
    STATE_PROVEN,
    SYNTHETIC_ONLY,
    V6RebuildKnowledge,
)


class V6RebuildKnowledgeTests(unittest.TestCase):
    def test_summary_keeps_counts_and_proof_boundary(self):
        knowledge = V6RebuildKnowledge()
        summary = knowledge.summary()

        self.assertEqual(summary["counts"]["map_scenes"], 1021)
        self.assertEqual(summary["counts"]["item_rows"], 4220)
        self.assertEqual(summary["counts"]["skill_rows"], 800)
        self.assertIn("synthetic-only", summary["proofTier"])
        self.assertTrue(any("No packet-proven portal" in gate for gate in summary["blockedGates"]))

    def test_portal_fixture_returns_client_compatible_route(self):
        knowledge = V6RebuildKnowledge()
        fixture = knowledge.portal_fixture(11036, 12)

        self.assertIsNotNone(fixture)
        self.assertEqual(fixture.dst_map, 11037)
        self.assertEqual(fixture.implementation_tier, SYNTHETIC_ONLY)

    def test_starter_skill_rows_fill_missing_v6_baseline(self):
        knowledge = V6RebuildKnowledge()
        rows = knowledge.starter_skill_rows([1])

        self.assertEqual([row["skill_id"] for row in rows], [2, 5])
        self.assertEqual(rows[0]["proof_tier"], STATE_PROVEN)


class PacketReaderTests(unittest.TestCase):
    def test_read_bytes_advances_without_overrun(self):
        install_v6_rebuild_knowledge()
        reader = PacketReader(bytes([0x14, 0x01, 0xaa, 0xbb]))

        self.assertEqual(reader.read_8(), 0x14)
        self.assertEqual(reader.read_bytes(2), bytes([0x01, 0xaa]))
        self.assertEqual(reader.read_bytes(10), bytes([0xbb]))
        self.assertEqual(reader.remaining_bytes(), 0)


class RuntimePatchTests(unittest.TestCase):
    def test_runtime_patch_is_idempotent(self):
        install_v6_rebuild_knowledge()
        install_v6_rebuild_knowledge()

        self.assertTrue(hasattr(PacketReader, "read_bytes"))


if __name__ == "__main__":
    unittest.main()
