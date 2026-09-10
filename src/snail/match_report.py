"""Full-executable decomp.dev reports from source-bound matching evidence.

Like Crimson, CI validates saved compiler results instead of distributing the
original executable or compiler bundles. Scores are from snail match, not objdiff.
"""

from __future__ import annotations

import hashlib
import importlib.metadata
import json
import math
import os
import platform
import shutil
import subprocess
from collections import Counter
from pathlib import Path
from typing import Any

from . import code_inventory
from . import match as matchlib
from .symbols import REPO_ROOT, load_function_symbol_manifest

VERSION = "win32-reflexive"
EVIDENCE_SCHEMA = 2
SCORING_POLICY = {
    "version": 2,
    "references": "positional-for-normalized-exact; diagnostic-alignment-for-partials",
    "coverage": "decoded-compared-ranges; unknown-bytes-reject-exact",
    "encoding": "same-offsets-and-encodings; audited-external-relocations; resolved-local-branches",
    "padding": "untargeted-terminal-nop-int3; no-owned-code-credit",
}
VERIFICATION_MODE = "Source-bound local compilation evidence; CI checks freshness and report consistency."
PROGRESS = REPO_ROOT / "analysis/progress"
DEFAULT_EVIDENCE = PROGRESS / f"{VERSION}.json"
DEFAULT_REPORT = REPO_ROOT / "artifacts/decomp/report.json"
ATTRIBUTION = REPO_ROOT / "analysis/ownership/library-attribution.json"
CATEGORY_LABELS = {
    "game": "Game & Engine", "libs": "Libraries",
    "libs.d3dx8": "D3DX8", "libs.msvc6-crt": "MSVC runtime",
    "libs.libpng-1.2.5": "libpng 1.2.5", "libs.zlib-1.2.1": "zlib 1.2.1",
    "other": "Unclassified code",
}


def file_hash(path: Path) -> str:
    if not path.is_file():
        raise ValueError(f"missing report input: {path}")
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _input_path(path: str) -> bool:
    p = Path(path)
    if path in {"pyproject.toml", "uv.lock"}:
        return True
    if path.startswith("src/snail/") and p.suffix == ".py":
        return p.stem.startswith("match") or p.stem in {"symbols", "code_inventory", "library_attribution"}
    if path.startswith("analysis/symbols/"):
        return p.name in {"gameplay-functions.json", "gameplay-references.json"}
    if path.startswith("analysis/progress/"):
        return p.name.endswith("code-inventory.json")
    if path.startswith("analysis/ownership/"):
        return p.name in {"library-attribution.json", "reference-build.json"}
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
        "runtime": {
            "python": platform.python_version(),
            **{
                name: importlib.metadata.version(name)
                for name in ("capstone", "pefile")
            },
        },
    }


def native_id(address: int) -> str:
    return f"SnailMail_unwrapped.exe/{address:08x}"


def intersection_size(left: list, right: list) -> int:
    return sum(max(0, min(b, d) - max(a, c)) for a, b in left for c, d in right)


def validate_comparison_ranges(row: dict[str, Any]) -> None:
    start, end = row["address"], row["address"] + row["scratch_target_bytes"]
    compared, excluded, unknown = (
        row[k]
        for k in (
            "compared_target_ranges",
            "excluded_target_ranges",
            "unexplained_target_ranges",
        )
    )
    if any(len(r) != 2 for r in compared + unknown) or any(
        len(r) != 3 or r[2] != "terminal-padding" for r in excluded
    ):
        raise ValueError("invalid comparison range/reason")
    cursor = start
    for a, b in sorted([r[:2] for r in compared + excluded + unknown]):
        if type(a) is not int or type(b) is not int or a != cursor or b <= a or b > end:
            raise ValueError(
                "comparison ranges must partition the supplied target span"
            )
        cursor = b
    if cursor != end:
        raise ValueError("comparison ranges omit target bytes")


def valid_digest(value: Any) -> bool:
    return (
        isinstance(value, str)
        and len(value) == 64
        and all(c in "0123456789abcdef" for c in value)
    )


def _identity(value: Any) -> str:
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def measurement_identities(
    inputs: dict[str, str], external: dict[str, Any]
) -> dict[str, Any]:
    return {
        "target": external["image"]["sha256"],
        "inventory": _identity(
            {p: h for p, h in inputs.items() if p.endswith("code-inventory.json")}
        ),
        "ownership": _identity(
            {
                p: h
                for p, h in inputs.items()
                if p.endswith(("gameplay-functions.json", "library-attribution.json"))
            }
        ),
        "scoring": _identity(
            {
                "policy": SCORING_POLICY,
                "implementation": {
                    p: h
                    for p, h in inputs.items()
                    if p.startswith("src/snail/")
                    or p in {"uv.lock", "analysis/symbols/gameplay-references.json"}
                },
            }
        ),
        "toolchains": _identity(
            {
                k: external[k]
                for k in ("compilers", "runner", "runtime")
                if k in external
            }
        ),
        "policy": SCORING_POLICY,
    }


def progress_delta(
    previous: dict[str, Any] | None, current: dict[str, Any]
) -> dict[str, Any]:
    old = {r["address"]: r for r in previous["functions"]} if previous else {}
    prior_ids = previous.get("identities", {}) if previous else {}
    changed = [
        k
        for k in ("target", "inventory", "ownership", "scoring", "toolchains")
        if prior_ids.get(k) != current["identities"][k]
    ]
    old_bytes = {
        a
        for r in old.values()
        if r["matched"]
        for start, end in r["ranges"]
        for a in range(start, end)
    }
    new_bytes = {
        a
        for r in current["functions"]
        if r["matched"]
        for start, end in r["ranges"]
        for a in range(start, end)
    }
    added, regressed = len(new_bytes - old_bytes), len(old_bytes - new_bytes)
    return {
        "interpretation": "measurement-baseline-change"
        if changed
        else "comparable-source-progress",
        "changed_identities": changed if prior_ids else [],
        "baseline_established": not bool(prior_ids),
        "previous_identities": prior_ids,
        "previous_evidence_sha256": _identity(previous) if previous else None,
        "newly_matched_bytes": added,
        "regressed_bytes": regressed,
        "previous_matched_bytes": sum(r["size"] for r in old.values() if r["matched"]),
        "previous_total_bytes": sum(r["size"] for r in old.values()),
    }


def proof_summary(evidence: dict[str, Any]) -> dict[str, Any]:
    rows = evidence["functions"]
    total = sum(r["size"] for r in rows)
    matched = sum(r["size"] for r in rows if r["matched"])
    encoded = sum(
        r["size"] for r in rows if r["matched"] and r.get("body_byte_exact", False)
    )
    return {
        "schema": 1,
        "verification_mode": evidence["verification_mode"],
        "identities": evidence["identities"],
        "progress_delta": evidence["progress_delta"],
        "total_code_bytes": total,
        "normalized_matched_bytes": matched,
        "encoded_body_matched_bytes": encoded,
        "encoded_body_matched_functions": sum(
            bool(r["matched"] and r.get("body_byte_exact")) for r in rows
        ),
        "encoded_body_matched_percent": 100 * encoded / total if total else 0,
        "normalized_matched_percent": 100 * matched / total if total else 0,
        "normalized_matched_functions": sum(r["matched"] for r in rows),
        "unmatched_bytes": total - matched,
        "linked_bytes": 0,
        "final_image_identity": "not measured",
        "data_progress": "not measured",
        "largest_remaining_functions": [
            {"id": native_id(r["address"]), "name": r["name"], "bytes": r["size"]}
            for r in sorted(
                (r for r in rows if r["is_function"] and not r["matched"]),
                key=lambda r: (-r["size"], r["address"]),
            )[:20]
        ],
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
        compared = [
            [status.address + a, status.address + b]
            for a, b in status.compared_target_ranges
        ]
        excluded = [
            [status.address + a, status.address + b, reason]
            for a, b, reason in status.excluded_target_ranges
        ]
        unexplained = [
            [status.address + a, status.address + b]
            for a, b in status.unexplained_target_ranges
        ]
        covered = intersection_size(compared, row["ranges"])
        complete_extent = covered == row["size"]
        row.update(
            {
                "candidate": "source",
                "source": (status.config.directory / "scratch.cpp")
                .relative_to(REPO_ROOT)
                .as_posix(),
                "ratio": status.ratio * covered / row["size"],
                "matched": status.state == "match" and complete_extent,
                "scratch_target_bytes": status.target_size,
                "covered_code_bytes": covered,
                "normalized_ratio": status.ratio,
                "compared_target_ranges": compared,
                "excluded_target_ranges": excluded,
                "unexplained_target_ranges": unexplained,
                "reference_audit_mode": "positional"
                if status.ratio == 1
                else "diagnostic",
                "body_byte_exact": status.body_byte_exact,
                "encoded_body_proof": status.encoded_body_proof,
                "candidate_object_sha256": status.candidate_object_sha256,
                "matching_state": status.state,
                "references": {
                    "ok": status.masked_ok,
                    "unresolved": status.masked_unresolved,
                    "mismatched": status.masked_mismatches,
                    "unaudited": status.masked_unaudited,
                },
            }
        )
    if repository_inputs() != before or _external_inputs(configs) != external:
        raise ValueError("report inputs changed during evaluation; refresh again")
    evidence = {
        "schema": EVIDENCE_SCHEMA,
        "version": VERSION,
        "scope": "full-executable-code",
        "verification_mode": VERIFICATION_MODE,
        "identities": measurement_identities(before, external),
        "inputs": before,
        "external_inputs": external,
        "functions": rows,
    }
    previous = (
        json.loads(DEFAULT_EVIDENCE.read_text()) if DEFAULT_EVIDENCE.exists() else None
    )
    evidence["progress_delta"] = progress_delta(previous, evidence)
    return evidence


def validate_evidence(evidence: dict[str, Any]) -> None:
    if (evidence.get("schema"), evidence.get("version"), evidence.get("scope")) != (
        EVIDENCE_SCHEMA,
        VERSION,
        "full-executable-code",
    ):
        raise ValueError("unsupported public report evidence")
    current, recorded = repository_inputs(), evidence["inputs"]
    if evidence.get("verification_mode") != VERIFICATION_MODE or evidence.get(
        "identities"
    ) != measurement_identities(recorded, evidence["external_inputs"]):
        raise ValueError("measurement identities differ from pinned evidence")
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
        validate_comparison_ranges(row)
        covered = intersection_size(row["compared_target_ranges"], row["ranges"])
        ratio = row["normalized_ratio"]
        if not math.isfinite(ratio) or not 0 <= ratio <= 1:
            raise ValueError("invalid normalized score")
        if covered != row["covered_code_bytes"] or row["ratio"] != ratio * covered / row["size"]:
            raise ValueError("score or source extent differs from recorded coverage")
        refs = row["references"]
        if set(refs) != {"ok", "unresolved", "mismatched", "unaudited"} or any(
            type(v) is not int or v < 0 for v in refs.values()
        ):
            raise ValueError("invalid reference audit counts")
        if row["reference_audit_mode"] != (
            "positional" if ratio == 1 else "diagnostic"
        ):
            raise ValueError("exact credit requires positional references")
        exact = (
            ratio == 1
            and not row["unexplained_target_ranges"]
            and all(refs[k] == 0 for k in ("unresolved", "mismatched", "unaudited"))
        )
        state = "match" if exact else "audit" if ratio == 1 else "wip"
        proof = row["encoded_body_proof"]
        encoded = False
        if proof is not None:
            if not exact or not all(
                valid_digest(proof[k]) for k in ("target_sha256", "candidate_sha256")
            ):
                raise ValueError("invalid encoded-body proof")
            body_size = proof["body_size"]
            if (
                type(body_size) is not int
                or body_size <= 0
                or row["compared_target_ranges"]
                != [[row["address"], row["address"] + body_size]]
            ):
                raise ValueError("encoded body differs from compared extent")
            cursor = 0
            for a, b in proof["masked_relocation_ranges"]:
                if (
                    type(a) is not int
                    or type(b) is not int
                    or not cursor <= a < b <= body_size
                ):
                    raise ValueError("invalid encoded relocation mask")
                cursor = b
            local = proof["resolved_local_relocations"]
            if any(type(a) is not int or not 0 <= a < body_size for a in local) or len(
                set(local)
            ) != len(local):
                raise ValueError("invalid resolved local relocation")
            encoded = proof["target_sha256"] == proof["candidate_sha256"]
        if (
            row["matching_state"] != state
            or type(row["body_byte_exact"]) is not bool
            or row["body_byte_exact"] != encoded
        ):
            raise ValueError("inconsistent normalized/encoded matching evidence")
        digest = row["candidate_object_sha256"]
        if not valid_digest(digest):
            raise ValueError("missing candidate object identity")
        if row["matched"] != (exact and covered == row["size"]):
            raise ValueError("matched credit lacks complete source/reference evidence")
    delta = evidence["progress_delta"]
    delta_fields = (
        "newly_matched_bytes",
        "regressed_bytes",
        "previous_matched_bytes",
        "previous_total_bytes",
    )
    if any(type(delta[k]) is not int or delta[k] < 0 for k in delta_fields):
        raise ValueError("invalid progress delta")
    current_matched = sum(r["size"] for r in evidence["functions"] if r["matched"])
    if (
        current_matched
        != delta["previous_matched_bytes"]
        + delta["newly_matched_bytes"]
        - delta["regressed_bytes"]
    ):
        raise ValueError("progress delta does not reconcile with matched bytes")
    if delta["previous_evidence_sha256"] is not None and not valid_digest(
        delta["previous_evidence_sha256"]
    ):
        raise ValueError("invalid previous evidence identity")
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
    matchlib._write_text_atomic(
        output.with_name("proof-summary.json"),
        code_inventory.snapshot_text(proof_summary(evidence)),
    )
    return report


def _load_attribution() -> dict[int, dict[str, Any]]:
    payload = json.loads(ATTRIBUTION.read_text())
    inventory_target = json.loads((PROGRESS / "executable-code-inventory.json").read_text())["target_sha256"]
    if payload.get("schema") != 1 or payload.get("target_sha256") != inventory_target:
        raise ValueError("ownership evidence belongs to another executable")
    rows = payload["functions"]
    if len({r["address"] for r in rows}) != len(rows):
        raise ValueError("duplicate ownership identity")
    for row in rows:
        if row["component"] != "game-init" and "libs." + row["component"] not in CATEGORY_LABELS:
            raise ValueError("unknown ownership component")
    return {r["address"]: r for r in rows}


def build_report(functions: list[dict[str, Any]]) -> dict[str, Any]:
    """Full-executable totals with an optional identified Game & Engine view."""
    manifest = load_function_symbol_manifest(REPO_ROOT / "analysis/symbols/gameplay-functions.json")
    game_addresses = {f.address for f in manifest.functions if f.port_scope != "third-party"}
    attribution = _load_attribution()
    game_addresses.update(a for a, r in attribution.items() if r["component"] == "game-init")
    display_names = {r["address"]: attribution.get(r["address"], {}).get("name", r["name"]) for r in functions}
    names = Counter(display_names.values())
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
        display_name = display_names[key]
        name = display_name if names[display_name] == 1 else f"{display_name}@{row['address']:08x}"
        owner = attribution.get(key)
        categories = ["other"]
        if row["is_function"] and key in game_addresses:
            categories = ["game"]
        elif row["is_function"] and owner and owner["component"] != "game-init":
            categories = ["libs", "libs." + owner["component"]]
        metadata: dict[str, Any] = {
            "complete": is_complete,
            "progress_categories": categories,
        }
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
                        "name": display_name,
                        "size": str(size),
                        "fuzzy_match_percent": percent,
                        "metadata": {
                            "virtual_address": str(row["address"]),
                            "demangled_name": display_name,
                        },
                    },
                ]
                if row["is_function"]
                else [],
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
        "categories": [{
            "id": category,
            "name": label,
            "measures": _sum_measures([
                unit["measures"] for unit in units if category in unit["metadata"]["progress_categories"]
            ]),
        } for category, label in CATEGORY_LABELS.items()],
    }


def _sum_measures(measures: list[dict[str, Any]]) -> dict[str, Any]:
    total = sum(int(m["total_code"]) for m in measures)
    return _measures(
        total,
        sum(int(m["matched_code"]) for m in measures),
        sum(int(m["complete_code"]) for m in measures),
        sum(int(m["total_code"]) * m["fuzzy_match_percent"] for m in measures) / total if total else 0.0,
        sum(m["total_functions"] for m in measures),
        sum(m["matched_functions"] for m in measures),
        sum(m["total_units"] for m in measures),
        sum(m["complete_units"] for m in measures),
    )


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
