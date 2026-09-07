"""Conservative, byte-addressed progress scope for the entire original executable.

Analyzer instruction coverage is evidence, not source reconstruction. Keep code
claimed by either analyzer and every unclassified byte in the denominator.
Exclude identified data/alignment only where no analyzer claims code.
"""

import hashlib
import json
from collections import Counter
from pathlib import Path

import pefile

DENOMINATOR_CLASSES = {"code", "disputed_code", "unclassified"}


def merge_ranges(ranges):
    merged = []
    for start, end in sorted(ranges):
        if start >= end:
            raise ValueError(f"invalid interval: {start:#x}..{end:#x}")
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(end, merged[-1][1])
        else:
            merged.append([start, end])
    return merged


def classification_mask(start, end, ranges):
    kinds = {"code": 1, "data": 2, "alignment": 3, "unknown": 4}
    mask = bytearray(end - start)
    cursor = start
    for a, b, kind in ranges:
        if a != cursor or b <= a or b > end:
            raise ValueError("classification must partition the complete section")
        if kind not in kinds:
            raise ValueError(f"unknown classification: {kind}")
        mask[a - start:b - start] = bytes([kinds[kind]]) * (b - a)
        cursor = b
    if cursor != end:
        raise ValueError("classification does not reach section end")
    return mask


def partition_section(start, end, bn_ranges, ida_ranges, ghidra_ranges):
    """Return a disjoint exhaustive partition; shared function tails count once."""
    if start >= end:
        raise ValueError("empty executable section")
    bn_mask = bytearray(end - start)
    for a, b in merge_ranges(bn_ranges):
        a, b = max(start, a), min(end, b)
        if a < b:
            bn_mask[a - start:b - start] = b"\1" * (b - a)
    ida = classification_mask(start, end, ida_ranges)
    ghidra = classification_mask(start, end, ghidra_ranges)
    partition = []
    names = {1: "code", 2: "data", 3: "alignment", 4: "unknown"}
    for offset, (bn_code, i, g) in enumerate(zip(bn_mask, ida, ghidra, strict=True)):
        evidence = f"bn:{'code' if bn_code else 'gap'};ida:{names[i]};ghidra:{names[g]}"
        if bn_code or i == 1 or g == 1:
            category = "disputed_code" if i in (2, 3) or g in (2, 3) else "code"
        elif i == 4 and g == 4:
            category = "unclassified"
        elif {i, g} == {2, 3}:
            # Non-code disagreement does not justify choosing a convenient exclusion.
            category = "unclassified"
        elif i == 2 or g == 2:
            category = "embedded_data"
        else:
            category = "padding"
        address = start + offset
        if partition and partition[-1][2:] == [category, evidence]:
            partition[-1][1] = address + 1
        else:
            partition.append([address, address + 1, category, evidence])
    return partition


def snapshot_text(value):
    """Keep each function/interval on one line for reviewable evidence diffs."""
    lines = ["{"]
    for index, (key, item) in enumerate(value.items()):
        comma = "," if index + 1 < len(value) else ""
        if key in {"functions", "sections"}:
            lines.append(f"  {json.dumps(key)}: [")
            lines.extend(
                "    " + json.dumps(row, sort_keys=True) + ("," if n + 1 < len(item) else "")
                for n, row in enumerate(item)
            )
            lines.append("  ]" + comma)
        else:
            lines.append(f"  {json.dumps(key)}: {json.dumps(item, sort_keys=True)}{comma}")
    return "\n".join(lines + ["}", ""])


def build_inventory(image_path: Path, manifest_path: Path, bn_path: Path, ida_path: Path, ghidra_path: Path):
    image = image_path.read_bytes()
    image_hash = hashlib.sha256(image).hexdigest()
    manifest = json.loads(manifest_path.read_text())
    if manifest["unwrapped_sha256"] != image_hash:
        raise ValueError("manifest target SHA-256 mismatch")
    bn = json.loads(bn_path.read_text())
    ida = json.loads(ida_path.read_text())
    ghidra = json.loads(ghidra_path.read_text())
    snapshots = (bn, ida, ghidra)
    for snapshot in snapshots:
        if snapshot["schema_version"] != 1 or not snapshot["sections"]:
            raise ValueError("missing or unsupported analyzer snapshot")
    if ida["input_sha256"] != image_hash:
        raise ValueError("IDA input SHA-256 mismatch")
    if ghidra["input_sha256"] != image_hash:
        raise ValueError("Ghidra input SHA-256 mismatch")
    pe = pefile.PE(data=image, fast_load=True)
    expected_sections = [s for s in pe.sections if s.Characteristics & 0x20000000]
    if not expected_sections:
        raise ValueError("PE has no executable sections")
    expected_starts = {pe.OPTIONAL_HEADER.ImageBase + s.VirtualAddress for s in expected_sections}
    for snapshot in snapshots:
        starts = [s["start"] for s in snapshot["sections"]]
        if len(set(starts)) != len(starts) or set(starts) != expected_starts:
            raise ValueError("analyzer executable-section inventory differs from PE")
    bn_ranges = [r for f in bn["functions"] for r in f["ranges"]]
    sections = []
    counts = Counter()
    evidence_counts = Counter()
    denominator_mask = {}
    for section in expected_sections:
        start = pe.OPTIONAL_HEADER.ImageBase + section.VirtualAddress
        size = section.Misc_VirtualSize or section.SizeOfRawData
        end = start + size
        raw = section.get_data()[:size].ljust(size, b"\0")
        section_hash = hashlib.sha256(raw).hexdigest()
        for snapshot in snapshots:
            entry = next(s for s in snapshot["sections"] if s["start"] == start)
            if entry["end"] != end or entry["sha256"] != section_hash:
                raise ValueError(f"{snapshot['tool']} section bounds/bytes mismatch")
        ida_section = next(s for s in ida["sections"] if s["start"] == start)
        ghidra_section = next(s for s in ghidra["sections"] if s["start"] == start)
        partition = partition_section(start, end, bn_ranges, ida_section["classification"], ghidra_section["classification"])
        section_counts = Counter()
        for a, b, category, evidence in partition:
            section_counts[category] += b - a
            evidence_counts[evidence] += b - a
            if category in DENOMINATOR_CLASSES:
                denominator_mask.update(dict.fromkeys(range(a, b), True))
        counts.update(section_counts)
        sections.append({
            "name": section.Name.rstrip(b"\0").decode(), "start": start, "end": end,
            "sha256": section_hash, "virtual_bytes": size,
            "raw_file_padding_bytes": max(0, section.SizeOfRawData - size),
            "counts": dict(section_counts), "ranges": partition,
        })
    curated = {int(f["address"], 0): f for f in manifest["functions"]}
    candidates = {}
    for lane, snapshot in (("binja", bn), ("ida", ida), ("ghidra", ghidra)):
        for f in snapshot["functions"]:
            entry = candidates.setdefault(f["start"], {"start": f["start"], "names": {}, "ranges": []})
            if lane in entry["names"]:
                raise ValueError("duplicate function start in analyzer snapshot")
            entry["names"][lane] = f["name"]
            entry["ranges"].extend(f["ranges"])
    missing = sorted(curated.keys() - candidates.keys())
    if missing:
        raise ValueError(f"curated functions missing from all analyzers: {missing}")
    curated_code = set()
    owned_code = set()
    for start, entry in sorted(candidates.items()):
        entry["ranges"] = merge_ranges(entry["ranges"])
        covered = {a for lo, hi in entry["ranges"] for a in range(lo, hi) if a in denominator_mask}
        owned_code.update(covered)
        entry["denominator_bytes"] = len(covered)
        if start in curated:
            entry["curated_name"] = curated[start]["name"]
            curated_code.update(covered)
    total = sum(counts[c] for c in DENOMINATOR_CLASSES)
    return {
        "schema_version": 1,
        "target": "SnailMail_unwrapped.exe",
        "target_sha256": image_hash,
        "version_id": "win32-reflexive",
        "policy": "all executable-section bytes except identified data/alignment with no analyzer claiming code; retain all disagreements and unknowns",
        "inputs": {
            p.name: hashlib.sha256(p.read_bytes()).hexdigest()
            for p in (manifest_path, bn_path, ida_path, ghidra_path)
        },
        "summary": {
            "denominator_bytes": total,
            "executable_virtual_bytes": sum(s["virtual_bytes"] for s in sections),
            "raw_file_padding_bytes": sum(s["raw_file_padding_bytes"] for s in sections),
            "classification_bytes": dict(counts),
            "evidence_bytes": dict(evidence_counts),
            "binja_function_starts": len(bn["functions"]),
            "ida_function_starts": len(ida["functions"]),
            "ghidra_function_starts": len(ghidra["functions"]),
            "union_function_start_candidates": len(candidates),
            "curated_function_starts": len(curated),
            "curated_owned_code_bytes": len(curated_code),
            "outside_curated_owned_code_bytes": total - len(curated_code),
            "code_without_function_owner_bytes": total - len(owned_code),
        },
        "sections": sections,
        "functions": [entry for _, entry in sorted(candidates.items())],
    }
