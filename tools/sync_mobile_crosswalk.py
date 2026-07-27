#!/usr/bin/env python3
"""Sync exact mobile symbols and generate complete crosswalk coverage."""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from snail.mobile import (
    DEFAULT_ANDROID_CORPUS_ROOT,
    DEFAULT_IOS_CORPUS_ROOT,
    DEFAULT_MOBILE_CROSSWALK_PATH,
    DEFAULT_VERIFIED_CROSSWALK_PATH,
    build_complete_mobile_crosswalk,
    exact_cross_port_backfills,
    load_json,
)
from snail.symbols import (
    DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    load_function_symbol_manifest,
    normalize_function_symbol_manifest,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--manifest",
        type=Path,
        default=DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH,
    )
    parser.add_argument(
        "--verified",
        type=Path,
        default=DEFAULT_VERIFIED_CROSSWALK_PATH,
    )
    parser.add_argument(
        "--android-index",
        type=Path,
        default=DEFAULT_ANDROID_CORPUS_ROOT / "index.json",
    )
    parser.add_argument(
        "--ios-index",
        type=Path,
        default=DEFAULT_IOS_CORPUS_ROOT / "index.json",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=DEFAULT_MOBILE_CROSSWALK_PATH,
    )
    parser.add_argument(
        "--check",
        action="store_true",
        help="Fail if either generated file differs instead of writing it",
    )
    return parser.parse_args()


def encoded(payload: dict) -> str:
    return json.dumps(payload, indent=2, ensure_ascii=False) + "\n"


def write_or_check(path: Path, text: str, *, check: bool) -> bool:
    if check:
        return path.is_file() and path.read_text(encoding="utf-8") == text
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return True


def main() -> int:
    args = parse_args()
    manifest = normalize_function_symbol_manifest(
        load_function_symbol_manifest(args.manifest)
    )
    verified = load_json(args.verified)
    android_index = load_json(args.android_index)
    ios_index = load_json(args.ios_index)

    changes = exact_cross_port_backfills(
        verified,
        android_index,
        ios_index,
    )
    evidence_note = (
        "android_symbol_evidence or ios_symbol_evidence set to "
        "exact-demangled-symbol means the other verified port name was found "
        "verbatim in that corpus; it is a name transfer, not a new semantic mapping."
    )
    if evidence_note not in verified["notes"]:
        verified["notes"].append(evidence_note)
    coverage = build_complete_mobile_crosswalk(
        manifest,
        verified,
        android_index,
        ios_index,
    )
    verified_text = encoded(verified)
    coverage_text = encoded(coverage)
    verified_ok = write_or_check(
        args.verified,
        verified_text,
        check=args.check,
    )
    coverage_ok = write_or_check(
        args.output,
        coverage_text,
        check=args.check,
    )
    if args.check and (not verified_ok or not coverage_ok):
        if not verified_ok:
            print(f"stale verified crosswalk: {args.verified}")
        if not coverage_ok:
            print(f"stale complete crosswalk: {args.output}")
        return 1

    print(
        f"exact cross-port backfills: {len(changes)}; "
        f"coverage: {coverage['counts']['manifest_functions']}/"
        f"{coverage['counts']['manifest_functions']}"
    )
    print(
        "verified symbols: "
        f"android {coverage['counts']['verified_android_symbols']}, "
        f"ios {coverage['counts']['verified_ios_symbols']}"
    )
    print(
        "available bodies: "
        f"android {coverage['counts']['available_android_mappings']}, "
        f"ios {coverage['counts']['available_ios_mappings']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
