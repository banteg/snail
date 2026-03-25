#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys


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
    return completed.stdout


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


def _artifact_path(out_dir: Path, function: FunctionSymbol) -> Path:
    return out_dir / f"{function.address:08x}-{_safe_name(function.name)}.c"


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
            f"/* target: {target_metadata.get('target_id', 'unknown')} */\n"
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
        "artifact": str(out_path.relative_to(REPO_ROOT)),
    }


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
    return parser.parse_args()


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

    exported: list[dict[str, object]] = []
    expected_paths: set[Path] = set()
    for function in manifest.functions:
        decompile_text = _run_bn(
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

    removed = _prune_stale_artifacts(out_dir, expected_paths)

    index = {
        "tool": "binary_ninja",
        "target": target_metadata,
        "manifest": str(manifest_path.relative_to(REPO_ROOT)),
        "out_dir": str(out_dir.relative_to(REPO_ROOT)),
        "function_count": len(exported),
        "removed_stale_artifacts": removed,
        "exports": exported,
    }
    index_path.write_text(json.dumps(index, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(index, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
