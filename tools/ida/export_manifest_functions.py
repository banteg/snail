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

from snail.symbols import load_function_symbol_manifest  # noqa: E402


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


def _prune_stale_artifacts(out_dir: Path, expected_paths: set[Path]) -> list[str]:
    removed: list[str] = []
    if not out_dir.is_dir():
        return removed
    for path in sorted(out_dir.glob("*.c")):
        if path in expected_paths:
            continue
        path.unlink()
        removed.append(str(path.relative_to(REPO_ROOT)))
    return removed


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
    selectors = [function.name for function in manifest.functions]
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
    expected_paths: set[Path] = set()
    for entry in exported_entries:
        if not isinstance(entry, dict):
            continue
        artifact = entry.get("artifact")
        if isinstance(artifact, str):
            expected_paths.add(Path(artifact).resolve())
    removed = _prune_stale_artifacts(out_dir, expected_paths)

    summary = {
        "tool": "ida",
        "manifest": str(manifest_path.relative_to(REPO_ROOT)),
        "database": str(db_path.relative_to(REPO_ROOT)),
        "out_dir": str(out_dir.relative_to(REPO_ROOT)),
        "function_count": len(manifest.functions),
        "exported": exported_entries,
        "failed": payload.get("failed", []),
        "removed_stale_artifacts": removed,
    }
    if args.index is not None:
        index_path = args.index.resolve()
        index_path.parent.mkdir(parents=True, exist_ok=True)
        index_path.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
        summary["index"] = str(index_path.relative_to(REPO_ROOT))
    sys.stdout.write(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
