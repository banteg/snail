"""Full-executable decomp.dev reports from source-bound matching evidence.

Like Crimson, CI validates saved compiler results instead of distributing the
original executable or compiler bundles. Scores are from snail match, not objdiff.
"""

from __future__ import annotations

import hashlib
import json
import math
import os
import shutil
import subprocess
from collections import Counter
from pathlib import Path
from typing import Any

from . import code_inventory
from . import match as matchlib
from .symbols import REPO_ROOT, load_function_symbol_manifest

VERSION = "win32-reflexive"
PROGRESS = REPO_ROOT / "analysis/progress"
DEFAULT_EVIDENCE = PROGRESS / f"{VERSION}.json"
DEFAULT_REPORT = REPO_ROOT / "artifacts/decomp/report.json"


def file_hash(path: Path) -> str:
    if not path.is_file():
        raise ValueError(f"missing report input: {path}")
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _input_path(path: str) -> bool:
    p = Path(path)
    if path in {"pyproject.toml", "uv.lock"}:
        return True
    if path.startswith("src/snail/") and p.suffix == ".py":
        return p.stem.startswith("match") or p.stem in {"symbols", "code_inventory"}
    if path.startswith("analysis/symbols/"):
        return p.name in {"gameplay-functions.json", "gameplay-references.json"}
    if path.startswith("analysis/progress/"):
        return p.name.endswith("code-inventory.json")
    if path == "tools/match/cl.sh":
        return True
    return path.startswith("tools/match/") and (
        p.name in {"scratch.cpp", "scratch.conf"} or p.suffix in {".h", ".hpp", ".inc"}
    )


def repository_inputs(root: Path = REPO_ROOT) -> dict[str, str]:
    result = subprocess.run(
        ["git", "ls-files", "--cached", "--others", "--exclude-standard", "-z"],
        cwd=root, capture_output=True, check=True,
    )
    paths = sorted({p for p in result.stdout.decode().split("\0") if p and _input_path(p)})
    return {p: file_hash(root / p) for p in paths}


def _runs(addresses: list[int]) -> list[list[int]]:
    runs: list[list[int]] = []
    for address in addresses:
        if runs and runs[-1][1] == address:
            runs[-1][1] += 1
        else:
            runs.append([address, address + 1])
    return runs


def inventory() -> list[dict[str, Any]]:
    """Disjoint public symbols, including every retained code byte exactly once.

Prefer curated ownership, then BN, IDA and Ghidra body owners. Shared tails
    belong to the highest entry address within each priority class. Unowned runs get explicit units,
not invented recovered functions. All extents remain inspectable in the report
evidence and source bounds are checked before granting an exact match.
"""
    raw = json.loads((PROGRESS / "executable-code-inventory.json").read_text())
    for name, digest in raw["inputs"].items():
        path = (REPO_ROOT / "analysis/symbols" if name == "gameplay-functions.json" else PROGRESS) / name
        if file_hash(path) != digest:
            raise ValueError(f"stale full-executable inventory input: {name}")
    manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
    if raw["target_sha256"] != manifest.unwrapped_sha256:
        raise ValueError("inventory target hash differs from manifest")
    remaining: set[int] = set()
    for section in raw["sections"]:
        cursor = section["start"]
        for start, end, category, _ in section["ranges"]:
            if start != cursor or end <= start or end > section["end"]:
                raise ValueError("full-executable inventory is not a complete disjoint partition")
            if category in code_inventory.DENOMINATOR_CLASSES:
                remaining.update(range(start, end))
            elif category not in {"padding", "embedded_data"}:
                raise ValueError(f"unknown inventory classification: {category}")
            cursor = end
        if cursor != section["end"]:
            raise ValueError("full-executable inventory omits section bytes")
    expected = len(remaining)
    if expected != raw["summary"]["denominator_bytes"]:
        raise ValueError("full-executable denominator summary differs from ranges")
    rows = []
    ordered = sorted(raw["functions"], key=lambda f: (
        0 if "curated_name" in f else 1 if "binja" in f["names"] else 2 if "ida" in f["names"] else 3,
        -f["start"],
    ))
    for function in ordered:
        owned = sorted({a for start, end in function["ranges"] for a in range(start, end)} & remaining)
        if not owned:
            continue
        remaining.difference_update(owned)
        names = function["names"]
        name = function.get("curated_name") or names.get("ida") or names.get("binja") or names["ghidra"]
        rows.append({
            "address": function["start"], "name": name, "size": len(owned),
            "ranges": _runs(owned), "is_function": True,
        })
    for start, end in _runs(sorted(remaining)):
        rows.append({
            "address": start, "name": f"unassigned_code_{start:08x}",
            "size": end - start, "ranges": [[start, end]], "is_function": False,
        })
    if sum(row["size"] for row in rows) != expected:
        raise ValueError("public symbols do not account for all executable code")
    return sorted(rows, key=lambda r: r["address"])


def _external_inputs(configs: list[matchlib.ScratchConfig]) -> dict[str, Any]:
    manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
    image = REPO_ROOT / manifest.primary_target
    if file_hash(image) != manifest.unwrapped_sha256:
        raise ValueError("original executable SHA-256 mismatch")
    compilers = {}
    for compiler in sorted({c.compiler for c in configs}):
        root = matchlib.DEFAULT_MATCH_ROOT / "compilers" / compiler
        if not (root / "Bin/CL.EXE").is_file():
            raise ValueError(f"compiler missing: {compiler}")
        compilers[compiler] = {
            p.relative_to(root).as_posix(): file_hash(p)
            for p in sorted(root.rglob("*")) if p.is_file()
        }
    runner = os.environ.get("WIBO") or str(matchlib.DEFAULT_MATCH_ROOT / "bin/wibo")
    runner_path = Path(shutil.which(runner) or runner).resolve()
    return {
        "image": {"path": manifest.primary_target, "sha256": file_hash(image)},
        "compilers": compilers,
        "runner": {"name": runner_path.name, "sha256": file_hash(runner_path)},
    }


def refresh_evidence(*, jobs: int = matchlib.DEFAULT_MATCH_JOBS) -> dict[str, Any]:
    before = repository_inputs()
    manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
    image_path = REPO_ROOT / manifest.primary_target
    configs = [matchlib.load_scratch_config(p.parent) for p in sorted(matchlib.DEFAULT_MATCH_ROOT.glob("scratches/*/scratch.conf"))]
    external = _external_inputs(configs)
    # Recompute native accounting from the actual original image on refresh.
    native = code_inventory.build_inventory(
        image_path, REPO_ROOT / "analysis/symbols/gameplay-functions.json",
        PROGRESS / "binja-code-inventory.json", PROGRESS / "ida-code-inventory.json",
        PROGRESS / "ghidra-code-inventory.json",
    )
    if code_inventory.snapshot_text(native) != (PROGRESS / "executable-code-inventory.json").read_text():
        raise ValueError("native inventory is stale; run tools/report_code_inventory.py")
    rows = inventory()
    # The legacy scratch cache keys compiler CL.EXE but not every backend DLL.
    # Public attestations require a fresh compile with the entire pinned bundle.
    for config in configs:
        (config.directory / "build/scratch-build.json").unlink(missing_ok=True)
        (config.directory / "build/match-cache.json").unlink(missing_ok=True)
    statuses = matchlib.collect_scratch_statuses(manifest, image_path, jobs=jobs)
    by_address = {}
    for status in statuses:
        if status.error or status.ratio is None:
            raise ValueError(f"matching failed: {status.config.function}: {status.error}")
        if status.address in by_address:
            raise ValueError(f"duplicate source candidate: {status.address:#x}")
        by_address[status.address] = status
    if by_address.keys() - {r["address"] for r in rows if r["is_function"]}:
        raise ValueError("source candidate absent from public function inventory")
    for row in rows:
        status = by_address.get(row["address"]) if row["is_function"] else None
        row.update({"candidate": None, "source": None, "ratio": 0.0, "matched": False, "linked": False})
        if status is None:
            continue
        start, end = status.address, status.address + status.target_size
        covered = sum(max(0, min(end, b) - max(start, a)) for a, b in row["ranges"])
        complete_extent = covered == row["size"]
        row.update({
            "candidate": "source", "source": (status.config.directory / "scratch.cpp").relative_to(REPO_ROOT).as_posix(),
            "ratio": status.ratio * covered / row["size"],
            "matched": status.state == "match" and complete_extent,
            "scratch_target_bytes": status.target_size, "covered_code_bytes": covered,
            "normalized_ratio": status.ratio,
            "matching_state": status.state,
            "references": {"ok": status.masked_ok, "unresolved": status.masked_unresolved,
                           "mismatched": status.masked_mismatches, "unaudited": status.masked_unaudited},
        })
    if repository_inputs() != before or _external_inputs(configs) != external:
        raise ValueError("report inputs changed during evaluation; refresh again")
    return {"schema": 1, "version": VERSION, "scope": "full-executable-code",
            "inputs": before, "external_inputs": external, "functions": rows}


def validate_evidence(evidence: dict[str, Any]) -> None:
    if (evidence.get("schema"), evidence.get("version"), evidence.get("scope")) != (1, VERSION, "full-executable-code"):
        raise ValueError("unsupported public report evidence")
    current, recorded = repository_inputs(), evidence["inputs"]
    changed = sorted(p for p in current.keys() | recorded.keys() if current.get(p) != recorded.get(p))
    if changed:
        raise ValueError("stale matching evidence; run snail match report --refresh: " + ", ".join(changed[:8]))
    fields = ("address", "name", "size", "ranges", "is_function")
    if [{k: row[k] for k in fields} for row in evidence["functions"]] != inventory():
        raise ValueError("report denominator differs from full-executable inventory")
    for row in evidence["functions"]:
        if row["candidate"] != "source":
            if row["matched"] or row["ratio"] or row["source"]:
                raise ValueError("non-source evidence cannot claim public progress")
            continue
        source = REPO_ROOT / row["source"]
        if row["source"] not in recorded or source.name != "scratch.cpp":
            raise ValueError("candidate source is absent from pinned inputs")
        matchlib.validate_scratch_source(source)
        config = matchlib.load_scratch_config(source.parent)
        manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
        if matchlib._function_symbols_by_name(manifest)[config.function].address != row["address"]:
            raise ValueError("candidate source targets another function")
        start, end = row["address"], row["address"] + row["scratch_target_bytes"]
        covered = sum(max(0, min(end, b) - max(start, a)) for a, b in row["ranges"])
        ratio = row["normalized_ratio"]
        if not math.isfinite(ratio) or not 0 <= ratio <= 1:
            raise ValueError("invalid normalized score")
        if covered != row["covered_code_bytes"] or row["ratio"] != ratio * covered / row["size"]:
            raise ValueError("score or source extent differs from recorded coverage")
        refs = row["references"]
        exact = ratio == 1 and all(refs[k] == 0 for k in ("unresolved", "mismatched", "unaudited"))
        if row["matched"] != (exact and covered == row["size"]):
            raise ValueError("matched credit lacks complete source/reference evidence")
    external = evidence["external_inputs"]
    manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
    if external["image"] != {"path": manifest.primary_target, "sha256": manifest.unwrapped_sha256}:
        raise ValueError("evidence original executable identity differs from manifest")
    image = REPO_ROOT / manifest.primary_target
    # CI has the byte-verified, hashed analyzer evidence, but no game executable.
    if image.exists() and file_hash(image) != manifest.unwrapped_sha256:
        raise ValueError("local reference executable changed")
    for compiler, files in external["compilers"].items():
        root = matchlib.DEFAULT_MATCH_ROOT / "compilers" / compiler
        if root.exists():
            actual = {p.relative_to(root).as_posix(): file_hash(p) for p in sorted(root.rglob("*")) if p.is_file()}
            if actual != files:
                raise ValueError(f"local compiler changed: {compiler}")
    runner = Path(os.environ.get("WIBO") or matchlib.DEFAULT_MATCH_ROOT / "bin/wibo")
    if runner.is_file() and file_hash(runner) != external["runner"]["sha256"]:
        raise ValueError("local Wibo changed")


def publish(*, refresh: bool = False, output: Path = DEFAULT_REPORT, jobs: int = matchlib.DEFAULT_MATCH_JOBS) -> dict[str, Any]:
    evidence = refresh_evidence(jobs=jobs) if refresh else json.loads(DEFAULT_EVIDENCE.read_text())
    validate_evidence(evidence)
    report = build_report(evidence["functions"])
    if refresh:
        matchlib._write_text_atomic(DEFAULT_EVIDENCE, code_inventory.snapshot_text(evidence))
    matchlib._write_text_atomic(output, json.dumps(report, indent=2) + "\n")
    return report


def build_report(functions: list[dict[str, Any]]) -> dict[str, Any]:
    """One public function or unassigned range per unit; no scope filters."""
    names = Counter(row["name"] for row in functions)
    seen: set[int] = set()
    units: list[dict[str, Any]] = []
    total = matched = complete = matched_functions = complete_units = 0
    fuzzy = 0.0
    for row in functions:
        key = row["address"]
        if key in seen:
            raise ValueError(f"duplicate report function: {key}")
        seen.add(key)
        size, ratio = row["size"], row["ratio"]
        if type(size) is not int or size < 0 or not math.isfinite(ratio) or not 0 <= ratio <= 1:
            raise ValueError(f"invalid matching measures: {key}")
        if row["matched"] and ratio != 1:
            raise ValueError(f"matched function has a partial score: {key}")
        if row["linked"]:
            raise ValueError("linked credit requires an actual source reconstruction build")
        eligible = row["candidate"] == "source" and row["is_function"]
        is_matched = eligible and row["matched"]
        is_complete = eligible and row["linked"]
        # objdiff's treemap paints 100% green. An unresolved-reference 100%
        # instruction score must remain visibly partial, like our `audit` state.
        percent = (100.0 if is_matched else min(ratio * 100, 99.99)) if eligible else 0.0
        measures = _measures(
            size,
            size if is_matched else 0,
            size if is_complete else 0,
            percent,
            int(row["is_function"]),
            int(is_matched),
            1,
            int(is_complete),
        )
        name = row["name"] if names[row["name"]] == 1 else f"{row['name']}@{row['address']:08x}"
        metadata: dict[str, Any] = {"complete": is_complete}
        if row["source"]:
            metadata["source_path"] = row["source"]
        if not row["is_function"] or row["candidate"] in {"archive", "import-thunk"}:
            metadata["auto_generated"] = True
        units.append(
            {
                "name": name,
                "measures": measures,
                "functions": [
                    {
                        "name": row["name"],
                        "size": str(size),
                        "fuzzy_match_percent": percent,
                        "metadata": {"virtual_address": str(row["address"])},
                    },
                ] if row["is_function"] else [],
                "metadata": metadata,
            },
        )
        total += size
        matched += size if is_matched else 0
        complete += size if is_complete else 0
        matched_functions += int(is_matched)
        complete_units += int(is_complete)
        fuzzy += size * percent
    return {
        "version": 2,
        "measures": _measures(
            total,
            matched,
            complete,
            fuzzy / total if total else 0.0,
            sum(int(r["is_function"]) for r in functions),
            matched_functions,
            len(units),
            complete_units,
        ),
        "units": units,

    }


def _measures(
    total: int,
    matched: int,
    complete: int,
    fuzzy: float,
    functions: int,
    matched_functions: int,
    units: int,
    complete_units: int,
) -> dict[str, Any]:
    return {
        "total_code": str(total),
        "matched_code": str(matched),
        "complete_code": str(complete),
        "matched_code_percent": 100 * matched / total if total else 0.0,
        "complete_code_percent": 100 * complete / total if total else 0.0,
        "fuzzy_match_percent": fuzzy,
        "total_functions": functions,
        "matched_functions": matched_functions,
        "matched_functions_percent": 100 * matched_functions / functions if functions else 0.0,
        "total_units": units,
        "complete_units": complete_units,
    }
