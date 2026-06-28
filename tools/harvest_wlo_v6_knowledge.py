"""Harvest bounded WLO v6 evidence into server-consumable Python data.

This importer scans the local B/F evidence roots for structured packet,
script, catalog, runtime, and harness artifacts. It does not promote static
or synthetic rows to exact server-byte proof; each harvested source keeps a
proof tier so the Python server can use the data without overstating it.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import re
from collections import Counter
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, Iterable, Optional


PROOF_TIERS = {
    "packet-proven",
    "runtime-proven",
    "state-proven",
    "decompile-observed",
    "cpu-emulated",
    "synthetic-only",
    "hypothesis",
}

ELIGIBLE_SUFFIXES = {".csv", ".json", ".jsonl", ".md", ".txt", ".log", ".js", ".py"}
MAX_FILE_BYTES = 8 * 1024 * 1024
MAX_TEXT_SCAN_CHARS = 250_000
MAX_SOURCE_ROWS = 3
MAX_VALUES_PER_BUCKET = 10
MAX_CSV_ROWS_PER_FILE = 75_000

SKIP_DIRS = {
    ".git",
    "__pycache__",
    "node_modules",
    ".venv",
    "venv",
    ".mypy_cache",
    ".pytest_cache",
}

B_HIGH_VALUE_PATHS = (
    "packet-frame-analysis",
    "runtime-proof",
    "v6-full",
    "Wonderland Onlinev6_full_decomp_20260514-144112",
    "preproof-server",
    "RUNTIME_PROOF_STATUS.md",
    "SERVER_BUILD_HANDOFF.md",
    "SERVER_BUILD_INPUTS.json",
)

F_HIGH_VALUE_PATHS = (
    "00_START_HERE",
    "01_SERVER",
    "02_CLIENTS",
    "03_EVIDENCE",
    "04_DIDNT_WORK_OR_UNKNOWN",
    "05_TOOLS",
    "06_DOCS_NOTES_INDEXES",
)

KEY_RE = re.compile(r"\b(?:0x[0-9a-fA-F]{1,4}|\d{1,3})\s*[,/:\-]\s*(?:0x[0-9a-fA-F]{1,4}|\d{1,3})\b")
HEX_BYTE_RE = re.compile(r"\b(?:[0-9a-fA-F]{2}\s+){2,}[0-9a-fA-F]{2}\b")


def utc_now() -> str:
    return datetime.now(timezone.utc).replace(microsecond=0).isoformat().replace("+00:00", "Z")


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def read_text(path: Path, limit: int = MAX_TEXT_SCAN_CHARS) -> str:
    with path.open("rb") as handle:
        data = handle.read(limit)
    return data.decode("utf-8", errors="replace")


def safe_rel(path: Path, root: Path) -> str:
    try:
        return str(path.relative_to(root)).replace("\\", "/")
    except ValueError:
        return str(path).replace("\\", "/")


def classify_category(path: Path) -> str:
    text = str(path).replace("\\", "/").lower()
    name = path.name.lower()
    if "packet-frame-analysis" in text or "packet" in name or "s2c" in text or "reply" in name:
        return "packet"
    if "runtime-proof" in text or name.endswith(".log"):
        return "runtime"
    if "agent-4-script-events" in text or "quest" in text or "event" in text or "dialog" in text or "cutscene" in text:
        return "scripts"
    if "agent-5-battle-items" in text or "battle" in text or "skill" in text or "drop" in text or "item" in text:
        return "items_battle_skills"
    if "agent-2-assets-data" in text or "v6-full" in text or "workbench-output" in text:
        return "client_assets"
    if "preproof-server" in text:
        return "server_harness"
    if "decomp" in text or "ghidra" in text:
        return "decompile"
    return "general"


def infer_proof_tier(path: Path, row_tiers: Optional[Counter] = None) -> str:
    if row_tiers:
        for tier in ("packet-proven", "runtime-proven", "state-proven", "cpu-emulated", "decompile-observed", "synthetic-only"):
            if row_tiers.get(tier):
                return tier
    text = str(path).replace("\\", "/").lower()
    if "captured" in text or "capture" in text or "exactserverbyte" in text:
        return "packet-proven"
    if "runtime-proof" in text or "headless-runtime-proof" in text:
        return "runtime-proven"
    if "parser" in text or "cpu" in text or "helper-equivalence" in text:
        return "cpu-emulated"
    if "decomp" in text or "ghidra" in text or "agent-" in text or "v6-full" in text:
        return "decompile-observed"
    if "preproof-server" in text:
        return "synthetic-only"
    return "hypothesis"


def append_bounded(bucket: list, value: Any, limit: int = MAX_VALUES_PER_BUCKET) -> None:
    if len(bucket) < limit and value not in bucket:
        bucket.append(value)


def iter_candidate_files(root: Path) -> Iterable[Path]:
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [name for name in dirnames if name not in SKIP_DIRS]
        for filename in filenames:
            path = Path(dirpath) / filename
            if path.suffix.lower() not in ELIGIBLE_SUFFIXES:
                continue
            try:
                if path.stat().st_size > MAX_FILE_BYTES:
                    continue
            except OSError:
                continue
            yield path


def extract_json_numbers(obj: Any, prefix: str = "", out: Optional[dict] = None) -> dict:
    if out is None:
        out = {}
    if isinstance(obj, dict):
        for key, value in obj.items():
            new_prefix = f"{prefix}.{key}" if prefix else str(key)
            extract_json_numbers(value, new_prefix, out)
    elif isinstance(obj, list):
        if prefix:
            out[f"{prefix}.count"] = len(obj)
        for index, value in enumerate(obj[:10]):
            extract_json_numbers(value, f"{prefix}[{index}]", out)
    elif isinstance(obj, (int, float)) and not isinstance(obj, bool) and prefix:
        out[prefix] = obj
    return out


def csv_rows(path: Path, max_rows: int = MAX_CSV_ROWS_PER_FILE) -> Iterable[dict]:
    with path.open("r", encoding="utf-8-sig", errors="replace", newline="") as handle:
        reader = csv.DictReader(handle)
        for index, row in enumerate(reader):
            if index >= max_rows:
                break
            yield row


def harvest_csv(path: Path, harvested: dict) -> Counter:
    row_tiers: Counter = Counter()
    basename = path.name.lower()
    rows_seen = 0
    route_candidates = harvested["scriptKnowledge"]["routeCandidates"]
    opcode_counts = harvested["scriptKnowledge"]["opcodeCounts"]
    packet_keys = harvested["packetKnowledge"]["uniqueKeys"]
    packet_families = harvested["packetKnowledge"]["families"]
    exact_byte_samples = harvested["packetKnowledge"]["exactByteSamples"]

    try:
        for row in csv_rows(path):
            rows_seen += 1
            tier = str(row.get("proofTier") or row.get("proof_tier") or "").strip()
            if tier in PROOF_TIERS:
                row_tiers[tier] += 1

            for field, value in row.items():
                if value is None:
                    continue
                value_text = str(value).strip()
                field_l = str(field).lower()
                if not value_text:
                    continue
                if field_l in {"key", "candidatekeys"} or "key" in field_l:
                    for match in KEY_RE.findall(value_text):
                        append_bounded(packet_keys, match.replace(" ", ""))
                if field_l in {"familytext", "familyvalue", "family_hex", "action_hex"} or "family" in field_l:
                    append_bounded(packet_families, value_text)
                if "hex" in field_l or "byte" in field_l or "frame" in field_l:
                    for match in HEX_BYTE_RE.findall(value_text):
                        append_bounded(exact_byte_samples, match)

            if basename == "event_command_opcode_table.csv":
                command = row.get("commandKind") or row.get("command") or "unknown"
                count_text = row.get("count") or "1"
                try:
                    opcode_counts[str(command)] += int(count_text)
                except ValueError:
                    opcode_counts[str(command)] += 1

            if basename in {
                "scene_map_event_references.csv",
                "map_reference_command_candidates.csv",
                "login_world_causality_candidates.csv",
                "map_reply_byte_recovery.csv",
            }:
                map_id = row.get("mapId") or row.get("map_id")
                click_id = row.get("clickId") or row.get("click_id") or row.get("portalId")
                scene_id = row.get("sceneId") or row.get("scene_id")
                if map_id or click_id or scene_id:
                    append_bounded(
                        route_candidates,
                        {
                            "source": path.name,
                            "mapId": map_id,
                            "clickId": click_id,
                            "sceneId": scene_id,
                            "name": row.get("sceneName") or row.get("eventName") or row.get("refName") or "",
                            "proofTier": tier if tier in PROOF_TIERS else "decompile-observed",
                        },
                        10,
                    )
    except Exception as exc:
        harvested["errors"].append({"path": str(path), "error": str(exc)})

    harvested["summary"]["csvRowsScanned"] += rows_seen
    return row_tiers


def harvest_json(path: Path, harvested: dict) -> None:
    try:
        text = read_text(path)
        if path.suffix.lower() == ".jsonl":
            rows = [json.loads(line) for line in text.splitlines() if line.strip()][:500]
            data: Any = rows
        else:
            data = json.loads(text)
    except Exception as exc:
        harvested["errors"].append({"path": str(path), "error": str(exc)})
        return

    numbers = extract_json_numbers(data)
    for key, value in numbers.items():
        short_key = f"{path.name}:{key}"
        if len(harvested["sourceInventory"]["numericFacts"]) < 10:
            harvested["sourceInventory"]["numericFacts"][short_key] = value

    lowered = text.lower()
    if "packet-proven" in lowered:
        harvested["proofCounts"]["packet-proven"] += 1
    if "runtime-proven" in lowered:
        harvested["proofCounts"]["runtime-proven"] += 1
    if "state-proven" in lowered:
        harvested["proofCounts"]["state-proven"] += 1


def harvest_text(path: Path, harvested: dict) -> None:
    try:
        text = read_text(path)
    except Exception as exc:
        harvested["errors"].append({"path": str(path), "error": str(exc)})
        return

    lowered = text.lower()
    for tier in PROOF_TIERS:
        count = lowered.count(tier)
        if count:
            harvested["proofCounts"][tier] += count
    for match in KEY_RE.findall(text):
        append_bounded(harvested["packetKnowledge"]["uniqueKeys"], match.replace(" ", ""))
    for match in HEX_BYTE_RE.findall(text):
        append_bounded(harvested["packetKnowledge"]["exactByteSamples"], match)


def source_entry(path: Path, root: Path, root_label: str, category: str, tier: str) -> dict:
    stat = path.stat()
    hash_value = None
    if stat.st_size <= 1_500_000:
        hash_value = sha256_file(path)
    return {
        "root": root_label,
        "relativePath": safe_rel(path, root),
        "category": category,
        "proofTier": tier,
        "size": stat.st_size,
        "mtimeUtc": datetime.fromtimestamp(stat.st_mtime, timezone.utc).replace(microsecond=0).isoformat().replace("+00:00", "Z"),
        "sha256": hash_value,
    }


def selected_scan_paths(root: Path, label: str) -> list:
    names = B_HIGH_VALUE_PATHS if label == "B" else F_HIGH_VALUE_PATHS
    selected = []
    for name in names:
        path = root / name
        if path.exists():
            selected.append(path)
    if selected:
        return selected
    return [root]


def iter_selected_files(root: Path, label: str) -> Iterable[Path]:
    for selected in selected_scan_paths(root, label):
        if selected.is_file():
            if selected.suffix.lower() in ELIGIBLE_SUFFIXES and selected.stat().st_size <= MAX_FILE_BYTES:
                yield selected
        else:
            yield from iter_candidate_files(selected)


def scan_root(root: Path, label: str, harvested: dict) -> None:
    if not root.exists():
        harvested["roots"][label] = {
            "path": str(root),
            "available": False,
            "proofTier": "hypothesis",
            "boundary": "Root was not mounted or accessible during this harvest.",
        }
        return

    scan_paths = selected_scan_paths(root, label)
    harvested["roots"][label] = {
        "path": str(root),
        "available": True,
        "scanPaths": [str(path) for path in scan_paths],
    }
    for path in iter_selected_files(root, label):
        category = classify_category(path)
        row_tiers: Counter = Counter()
        if path.suffix.lower() == ".csv":
            row_tiers = harvest_csv(path, harvested)
        elif path.suffix.lower() in {".json", ".jsonl"}:
            harvest_json(path, harvested)
        else:
            harvest_text(path, harvested)

        tier = infer_proof_tier(path, row_tiers)
        harvested["summary"]["filesScanned"] += 1
        harvested["summary"]["bytesScanned"] += path.stat().st_size
        harvested["sourceInventory"]["categoryCounts"][category] += 1
        harvested["sourceInventory"]["proofTierCounts"][tier] += 1

        if row_tiers:
            for proof_tier, count in row_tiers.items():
                harvested["proofCounts"][proof_tier] += count

        if len(harvested["sourceInventory"]["sources"]) < MAX_SOURCE_ROWS:
            harvested["sourceInventory"]["sources"].append(source_entry(path, root, label, category, tier))


def compact_counter(counter: Counter) -> dict:
    return dict(sorted(counter.items(), key=lambda item: (-item[1], item[0])))


def finalize(harvested: dict) -> dict:
    original_error_count = len(harvested["errors"])
    harvested["sourceInventory"]["categoryCounts"] = compact_counter(harvested["sourceInventory"]["categoryCounts"])
    harvested["sourceInventory"]["proofTierCounts"] = compact_counter(harvested["sourceInventory"]["proofTierCounts"])
    harvested["scriptKnowledge"]["opcodeCounts"] = compact_counter(harvested["scriptKnowledge"]["opcodeCounts"])
    harvested["proofCounts"] = compact_counter(harvested["proofCounts"])
    harvested["packetKnowledge"]["uniqueKeyCount"] = len(harvested["packetKnowledge"]["uniqueKeys"])
    harvested["packetKnowledge"]["familyCount"] = len(harvested["packetKnowledge"]["families"])
    harvested["packetKnowledge"]["exactByteSampleCount"] = len(harvested["packetKnowledge"]["exactByteSamples"])
    harvested["scriptKnowledge"]["routeCandidateCount"] = len(harvested["scriptKnowledge"]["routeCandidates"])
    harvested["summary"]["sourcesRecorded"] = len(harvested["sourceInventory"]["sources"])
    harvested["summary"]["errorCount"] = original_error_count
    harvested["errors"] = harvested["errors"][:20]
    return harvested


def build_harvest(b_root: Path, f_root: Path) -> dict:
    harvested: Dict[str, Any] = {
        "generatedAt": utc_now(),
        "proofBoundary": {
            "proofTier": "decompile-observed + packet-proven + runtime-proven + cpu-emulated + synthetic-only",
            "boundary": (
                "This file imports evidence and known scripts into the Python server. "
                "Rows remain at their source proof tier; static/decompiled/client-compatible "
                "data is not exact original server reply proof unless exact bytes or decoded "
                "request/response artifacts are present."
            ),
        },
        "roots": {},
        "summary": {
            "filesScanned": 0,
            "sourcesRecorded": 0,
            "bytesScanned": 0,
            "csvRowsScanned": 0,
            "errorCount": 0,
        },
        "proofCounts": Counter(),
        "sourceInventory": {
            "sources": [],
            "categoryCounts": Counter(),
            "proofTierCounts": Counter(),
            "numericFacts": {},
        },
        "packetKnowledge": {
            "uniqueKeys": [],
            "families": [],
            "exactByteSamples": [],
        },
        "scriptKnowledge": {
            "opcodeCounts": Counter(),
            "routeCandidates": [],
        },
        "errors": [],
    }

    scan_root(b_root, "B", harvested)
    scan_root(f_root, "F", harvested)
    return finalize(harvested)


def main() -> int:
    parser = argparse.ArgumentParser(description="Harvest WLO v6 evidence into server/data/v6_exhaustive_knowledge.json")
    parser.add_argument("--b-root", default=r"B:\WLOTest")
    parser.add_argument("--f-root", default=r"F:\_WLO_SUPER_ORGANIZED")
    parser.add_argument("--out", default=r"server\data\v6_exhaustive_knowledge.json")
    args = parser.parse_args()

    harvested = build_harvest(Path(args.b_root), Path(args.f_root))
    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(harvested, indent=2, sort_keys=True), encoding="utf-8")
    print(json.dumps(harvested["summary"], indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
