#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile


REPO_ROOT = Path(__file__).resolve().parents[2]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.symbols import (  # noqa: E402
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    FunctionSymbol,
    load_function_symbol_manifest,
)


DEFAULT_OUT_DIR = REPO_ROOT / "analysis/decompile/binja/functions"
DEFAULT_INDEX_PATH = REPO_ROOT / "analysis/decompile/binja/index.json"
SAFE_NAME_RE = re.compile(r"[^A-Za-z0-9_.-]+")
SPILL_PATH_RE = re.compile(r"^path:\s+(?P<path>.+)$", re.MULTILINE)


def _safe_name(name: str) -> str:
    return SAFE_NAME_RE.sub("_", name).strip("_") or "function"


def _run_bn(*args: str) -> str:
    completed = subprocess.run(
        ["bn", *args],
        cwd=REPO_ROOT,
        check=False,
        text=True,
        capture_output=True,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"bn {' '.join(args)} failed with exit code {completed.returncode}:"
            f"\n{completed.stderr.strip()}"
        )
    spill_match = SPILL_PATH_RE.search(completed.stdout)
    if spill_match is not None:
        spill_path = Path(spill_match.group("path")).expanduser()
        if spill_path.is_file():
            return spill_path.read_text(encoding="utf-8")
    return completed.stdout


def _run_bn_text_to_file(*args: str) -> str:
    with tempfile.NamedTemporaryFile(suffix=".txt", delete=False) as handle:
        out_path = Path(handle.name)
    try:
        completed = subprocess.run(
            ["bn", *args, "--out", str(out_path)],
            cwd=REPO_ROOT,
            check=False,
            text=True,
            capture_output=True,
        )
        if completed.returncode != 0:
            raise RuntimeError(
                f"bn {' '.join(args)} failed with exit code {completed.returncode}:"
                f"\n{completed.stderr.strip()}"
            )
        return out_path.read_text(encoding="utf-8")
    finally:
        out_path.unlink(missing_ok=True)


def _load_target_metadata(target_selector: str) -> dict[str, object]:
    targets = json.loads(_run_bn("target", "list", "--format", "json"))
    if not isinstance(targets, list):
        raise RuntimeError("unexpected `bn target list --format json` output")

    if target_selector == "active":
        for target in targets:
            if isinstance(target, dict) and target.get("active") is True:
                return target
        raise RuntimeError("no active Binary Ninja target is open")

    for target in targets:
        if not isinstance(target, dict):
            continue
        if (
            target.get("selector") == target_selector
            or target.get("target_id") == target_selector
            or target.get("basename") == target_selector
            or target.get("filename") == target_selector
        ):
            return target
    raise RuntimeError(f"could not resolve Binary Ninja target: {target_selector}")


def _run_bn_json(*args: str) -> object:
    with tempfile.NamedTemporaryFile(suffix=".json", delete=False) as handle:
        out_path = Path(handle.name)
    try:
        completed = subprocess.run(
            ["bn", *args, "--format", "json", "--out", str(out_path)],
            cwd=REPO_ROOT,
            check=False,
            text=True,
            capture_output=True,
        )
        if completed.returncode != 0:
            raise RuntimeError(
                f"bn {' '.join(args)} failed with exit code {completed.returncode}:"
                f"\n{completed.stderr.strip()}"
            )
        return json.loads(out_path.read_text(encoding="utf-8"))
    finally:
        out_path.unlink(missing_ok=True)


def _artifact_path(out_dir: Path, function: FunctionSymbol) -> Path:
    return out_dir / f"{function.address:08x}-{_safe_name(function.name)}.c"


def _display_path(path: Path) -> str:
    try:
        return str(path.relative_to(REPO_ROOT))
    except ValueError:
        return str(path)


def _write_artifact(
    out_dir: Path,
    *,
    function: FunctionSymbol,
    decompile_text: str,
    target_metadata: dict[str, object],
    manifest_path: Path,
) -> dict[str, object]:
    out_path = _artifact_path(out_dir, function)
    out_path.write_text(
        (
            f"/* tool: binary_ninja */\n"
            f"/* database: {target_metadata.get('filename', 'unknown')} */\n"
            f"/* manifest: {manifest_path} */\n"
            f"/* function: {function.name} @ {function.address_hex} */\n\n"
            f"{decompile_text.rstrip()}\n"
        ),
        encoding="utf-8",
    )
    return {
        "address": function.address_hex,
        "name": function.name,
        "artifact": _display_path(out_path),
    }


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


def _load_live_function_map(target_selector: str) -> dict[int, dict[str, object]]:
    payload = _run_bn_json("function", "list", "--target", target_selector)
    if not isinstance(payload, list):
        raise RuntimeError("unexpected `bn function list --format json` output")

    live: dict[int, dict[str, object]] = {}
    for entry in payload:
        if not isinstance(entry, dict):
            continue
        address_text = entry.get("address")
        name = entry.get("name")
        if not isinstance(address_text, str) or not isinstance(name, str):
            continue
        live[int(address_text, 16)] = entry
    return live


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Export all named gameplay functions from the tracked manifest into Binary Ninja decompile artifacts."
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
        help="Path to the tracked gameplay function manifest.",
    )
    parser.add_argument(
        "--target",
        default="active",
        help="Binary Ninja target selector. Defaults to the active target.",
    )
    parser.add_argument(
        "--out-dir",
        type=Path,
        default=DEFAULT_OUT_DIR,
        help="Directory to write tracked Binary Ninja pseudocode artifacts into.",
    )
    parser.add_argument(
        "--index",
        type=Path,
        default=DEFAULT_INDEX_PATH,
        help="Index JSON path to write after exporting.",
    )
    parser.add_argument(
        "--only",
        action="append",
        default=[],
        help="Optional function selector(s) to export. Matches manifest name or hex address.",
    )
    return parser.parse_args()


def _select_functions(manifest_functions: list[FunctionSymbol], selectors: list[str]) -> list[FunctionSymbol]:
    if not selectors:
        return manifest_functions
    requested = {selector.lower() for selector in selectors}
    selected = [
        function
        for function in manifest_functions
        if function.name.lower() in requested or function.address_hex.lower() in requested
    ]
    missing = sorted(
        selector
        for selector in selectors
        if selector.lower()
        not in {
            function.name.lower()
            for function in selected
        }
        and selector.lower()
        not in {
            function.address_hex.lower()
            for function in selected
        }
    )
    if missing:
        raise RuntimeError(f"manifest does not contain requested function selector(s): {', '.join(missing)}")
    return selected


def main() -> int:
    args = parse_args()
    manifest_path = args.manifest.resolve()
    out_dir = args.out_dir.resolve()
    index_path = args.index.resolve()

    manifest = load_function_symbol_manifest(manifest_path)
    out_dir.mkdir(parents=True, exist_ok=True)
    index_path.parent.mkdir(parents=True, exist_ok=True)

    target_metadata = _load_target_metadata(args.target)
    target_selector = str(target_metadata.get("target_id") or args.target)
    live_functions = _load_live_function_map(target_selector)

    selected_functions = _select_functions(manifest.functions, list(args.only))

    exported: list[dict[str, object]] = []
    mismatches: list[dict[str, object]] = []
    expected_paths: set[Path] = set()
    for function in selected_functions:
        live = live_functions.get(function.address)
        if live is None:
            mismatches.append(
                {
                    "reason": "missing_live_function",
                    "manifest_address": function.address_hex,
                    "manifest_name": function.name,
                }
            )
        else:
            observed_name = live.get("name")
            if observed_name != function.name:
                mismatches.append(
                    {
                        "reason": "name_mismatch",
                        "manifest_address": function.address_hex,
                        "manifest_name": function.name,
                        "observed_address": live.get("address"),
                        "observed_name": observed_name,
                    }
                )
        decompile_text = _run_bn_text_to_file(
            "decompile",
            "--target",
            target_selector,
            function.address_hex,
        )
        exported.append(
            _write_artifact(
                out_dir,
                function=function,
                decompile_text=decompile_text,
                target_metadata=target_metadata,
                manifest_path=manifest_path,
            )
        )
        expected_paths.add(_artifact_path(out_dir, function))

    removed = [] if args.only else _prune_stale_artifacts(out_dir, expected_paths)

    index = {
        "tool": "binary_ninja",
        "target": target_metadata,
        "manifest": _display_path(manifest_path),
        "out_dir": _display_path(out_dir),
        "selected_count": len(selected_functions),
        "function_count": len(exported),
        "mismatch_count": len(mismatches),
        "mismatches": mismatches,
        "removed_stale_artifacts": removed,
        "exports": exported,
    }
    index_path.write_text(json.dumps(index, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(index, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
