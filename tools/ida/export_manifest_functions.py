#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import sys

from runner import DEFAULT_IDA_DB_PATH, REPO_ROOT, find_ida_binary, run_ida_script
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.symbols import build_function_symbol_manifest, load_function_symbol_manifest  # noqa: E402


DEFAULT_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"
DEFAULT_OUT_DIR = REPO_ROOT / "artifacts/ida/functions"
SAFE_NAME_RE = re.compile(r"[^A-Za-z0-9_.-]+")
IDAPYTHON_SCRIPT_PATH = REPO_ROOT / "tools/ida/export_function_artifact.py"


def _safe_name(name: str) -> str:
    return SAFE_NAME_RE.sub("_", name).strip("_") or "function"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export all named gameplay functions from the tracked manifest into IDA pseudocode artifacts."
    )
    parser.add_argument(
        "--ida-bin",
        help="Path to the IDA headless binary (defaults to the first idat*/ida* on PATH).",
    )
    parser.add_argument(
        "--db",
        type=Path,
        default=DEFAULT_IDA_DB_PATH,
        help="Path to the IDA database to read from.",
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_MANIFEST_PATH,
        help="Path to the tracked gameplay function manifest.",
    )
    parser.add_argument(
        "--out-dir",
        type=Path,
        default=DEFAULT_OUT_DIR,
        help="Directory to write exported pseudocode artifacts into.",
    )
    parser.add_argument(
        "--index",
        type=Path,
        help="Optional JSON index path to write after exporting.",
    )
    parser.add_argument(
        "--only",
        action="append",
        default=[],
        help="Optional function selector(s) to export. Matches manifest name or hex address.",
    )
    return parser.parse_args()


def _extract_json_payload(log_text: str) -> dict[str, object]:
    decoder = json.JSONDecoder()
    candidate: dict[str, object] | None = None
    candidate_span = -1
    for start in (index for index, char in enumerate(log_text) if char == "{"):
        try:
            value, end = decoder.raw_decode(log_text[start:])
        except json.JSONDecodeError:
            continue
        if not isinstance(value, dict) or start + end > len(log_text):
            continue
        keys = set(value)
        if {"database", "out_dir", "exported", "failed"} <= keys:
            span = end
            if span > candidate_span:
                candidate = value
                candidate_span = span
    if candidate is None:
        raise RuntimeError(f"failed to extract JSON payload from IDA log:\n{log_text}")
    return candidate


def _artifact_path(out_dir: Path, *, address: int, name: str) -> Path:
    return out_dir / f"{address:08x}-{_safe_name(name)}.c"


def _display_path(path: Path) -> str:
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _relativize_exported_entries(exported_entries: list[dict[str, object]]) -> list[dict[str, object]]:
    normalized: list[dict[str, object]] = []
    for entry in exported_entries:
        if not isinstance(entry, dict):
            normalized.append(entry)
            continue
        normalized_entry = dict(entry)
        artifact = normalized_entry.get("artifact")
        if isinstance(artifact, str):
            artifact_path = Path(artifact)
            try:
                normalized_entry["artifact"] = str(artifact_path.resolve().relative_to(REPO_ROOT))
            except ValueError:
                normalized_entry["artifact"] = artifact
        removed = normalized_entry.get("removed_stale_artifacts")
        if isinstance(removed, list):
            normalized_removed: list[str] = []
            for item in removed:
                if not isinstance(item, str):
                    continue
                item_path = Path(item)
                try:
                    normalized_removed.append(str(item_path.resolve().relative_to(REPO_ROOT)))
                except ValueError:
                    normalized_removed.append(item)
            normalized_entry["removed_stale_artifacts"] = normalized_removed
        normalized.append(normalized_entry)
    return normalized


def _prune_stale_artifacts(out_dir: Path, expected_paths: set[Path]) -> list[str]:
    removed: list[str] = []
    if not out_dir.is_dir():
        return removed
    for path in sorted(out_dir.glob("*.c")):
        if path in expected_paths:
            continue
        path.unlink()
        removed.append(_display_path(path))
    return removed


def _load_existing_index(index_path: Path) -> dict[str, object]:
    if not index_path.is_file():
        return {}
    try:
        value = json.loads(index_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}
    return value if isinstance(value, dict) else {}


def _merge_focused_exports(
    manifest_functions,
    refreshed: list[dict[str, object]],
    *,
    out_dir: Path,
    existing_index: dict[str, object],
) -> list[dict[str, object]]:
    refreshed_by_address = {
        entry.get("address"): entry
        for entry in refreshed
        if isinstance(entry.get("address"), str)
    }
    existing_exports = existing_index.get("exported", [])
    existing_by_address = {
        entry.get("address"): entry
        for entry in existing_exports
        if isinstance(entry, dict) and isinstance(entry.get("address"), str)
    }

    merged: list[dict[str, object]] = []
    for function in manifest_functions:
        artifact_path = _artifact_path(out_dir, address=function.address, name=function.name)
        artifact = _display_path(artifact_path)
        entry = refreshed_by_address.get(function.address_hex)
        if entry is None:
            existing = existing_by_address.get(function.address_hex)
            if (
                isinstance(existing, dict)
                and existing.get("selector") == function.name
                and existing.get("name") == function.name
                and existing.get("artifact") == artifact
                and artifact_path.is_file()
            ):
                entry = existing
            elif artifact_path.is_file():
                entry = {
                    "selector": function.name,
                    "address": function.address_hex,
                    "name": function.name,
                    "artifact": artifact,
                    "removed_stale_artifacts": [],
                }
            else:
                continue
        merged.append(dict(entry))
    return merged


def _command_summary(
    index: dict[str, object],
    *,
    refreshed: list[dict[str, object]],
    index_path: Path,
    focused: bool,
) -> dict[str, object]:
    summary = dict(index)
    summary["refreshed_count"] = len(refreshed)
    if focused:
        summary["selected_count"] = len(refreshed)
        summary["function_count"] = len(refreshed)
        summary["index_function_count"] = len(index.get("exported", []))
        summary["exported"] = refreshed
    summary["index"] = _display_path(index_path)
    return summary


def _build_mismatches(manifest, exported_entries: list[dict[str, object]]) -> list[dict[str, object]]:
    manifest_by_name = {function.name: function for function in manifest.functions}
    mismatches: list[dict[str, object]] = []
    seen_selectors: set[str] = set()
    for entry in exported_entries:
        selector = entry.get("selector")
        if not isinstance(selector, str):
            continue
        seen_selectors.add(selector)
        manifest_function = manifest_by_name.get(selector)
        if manifest_function is None:
            mismatches.append(
                {
                    "reason": "unexpected_selector",
                    "selector": selector,
                    "observed_address": entry.get("address"),
                    "observed_name": entry.get("name"),
                }
            )
            continue
        observed_address = entry.get("address")
        observed_name = entry.get("name")
        if observed_address != manifest_function.address_hex or observed_name != manifest_function.name:
            mismatches.append(
                {
                    "reason": "selector_resolved_differently",
                    "selector": selector,
                    "manifest_address": manifest_function.address_hex,
                    "manifest_name": manifest_function.name,
                    "observed_address": observed_address,
                    "observed_name": observed_name,
                }
            )
    for function in manifest.functions:
        if function.name in seen_selectors:
            continue
        mismatches.append(
            {
                "reason": "missing_selector",
                "selector": function.name,
                "manifest_address": function.address_hex,
                "manifest_name": function.name,
            }
        )
    return mismatches


def _select_functions(manifest_functions, selectors: list[str]):
    if not selectors:
        return manifest_functions
    requested = {selector.lower() for selector in selectors}
    selected = [
        function
        for function in manifest_functions
        if function.name.lower() in requested or function.address_hex.lower() in requested
    ]
    selected_names = {function.name.lower() for function in selected}
    selected_addresses = {function.address_hex.lower() for function in selected}
    missing = sorted(
        selector
        for selector in selectors
        if selector.lower() not in selected_names and selector.lower() not in selected_addresses
    )
    if missing:
        raise RuntimeError(f"manifest does not contain requested function selector(s): {', '.join(missing)}")
    return selected


def main() -> int:
    args = parse_args()
    ida_bin = find_ida_binary(args.ida_bin)
    db_path = args.db.resolve()
    manifest_path = args.manifest.resolve()
    out_dir = args.out_dir.resolve()

    if not db_path.is_file():
        raise FileNotFoundError(f"IDA database not found: {db_path}")
    if not manifest_path.is_file():
        raise FileNotFoundError(f"symbol manifest not found: {manifest_path}")
    if not IDAPYTHON_SCRIPT_PATH.is_file():
        raise FileNotFoundError(f"IDAPython export script not found: {IDAPYTHON_SCRIPT_PATH}")

    manifest = load_function_symbol_manifest(manifest_path)
    selected_functions = _select_functions(manifest.functions, list(args.only))
    selectors = [
        f"{function.address_hex}@@{function.name}" for function in selected_functions
    ]
    if not selectors:
        raise RuntimeError(f"no named functions found in manifest: {manifest_path}")

    exit_code, log_text = run_ida_script(
        ida_bin=ida_bin,
        script_path=IDAPYTHON_SCRIPT_PATH,
        db_path=db_path,
        script_args=[str(out_dir), *selectors],
        log_stem="export-manifest-functions",
    )
    if exit_code != 0:
        sys.stdout.write(log_text)
        return exit_code

    payload = _extract_json_payload(log_text)
    exported_entries = payload.get("exported", [])
    if not isinstance(exported_entries, list):
        raise RuntimeError(f"unexpected exported payload shape: {payload!r}")
    exported_entries = _relativize_exported_entries(exported_entries)
    expected_paths: set[Path] = set()
    for entry in exported_entries:
        if not isinstance(entry, dict):
            continue
        artifact = entry.get("artifact")
        if isinstance(artifact, str):
            expected_paths.add((REPO_ROOT / artifact).resolve())
    removed = [] if args.only else _prune_stale_artifacts(out_dir, expected_paths)
    selected_manifest = build_function_symbol_manifest(manifest, selected_functions)
    mismatches = _build_mismatches(selected_manifest, exported_entries)

    summary = {
        "tool": "ida",
        "manifest": _display_path(manifest_path),
        "database": _display_path(db_path),
        "out_dir": _display_path(out_dir),
        "selected_count": len(selected_functions),
        "function_count": len(exported_entries),
        "exported": exported_entries,
        "mismatch_count": len(mismatches),
        "mismatches": mismatches,
        "failed": payload.get("failed", []),
        "removed_stale_artifacts": removed,
    }
    if args.index is not None:
        index_path = args.index.resolve()
        index_path.parent.mkdir(parents=True, exist_ok=True)
        index_summary = dict(summary)
        if args.only:
            indexed_entries = _merge_focused_exports(
                manifest.functions,
                exported_entries,
                out_dir=out_dir,
                existing_index=_load_existing_index(index_path),
            )
            index_summary["selected_count"] = len(indexed_entries)
            index_summary["function_count"] = len(indexed_entries)
            index_summary["exported"] = indexed_entries
        index_path.write_text(json.dumps(index_summary, indent=2) + "\n", encoding="utf-8")
        summary = _command_summary(
            index_summary,
            refreshed=exported_entries,
            index_path=index_path,
            focused=bool(args.only),
        )
    sys.stdout.write(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
