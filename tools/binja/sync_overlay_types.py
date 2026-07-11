#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_data_var_updates, apply_proto_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_overlay_types.h"

DATA_VAR_UPDATES = (("0x4df904", "char*"),)

PROTO_UPDATES = (
    ("initialize_overlay", "void __thiscall initialize_overlay(Overlay* overlay)"),
    ("update_overlay", "void __thiscall update_overlay(Overlay* overlay)"),
    (
        "bind_subgame_owner",
        "SubgameRuntime* __thiscall bind_subgame_owner(SubgameOwnerLink* owner)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow overlay and embedded camera types to the active Binary Ninja target."
    )
    parser.add_argument("--target", default="active", help="Binary Ninja target selector.")
    parser.add_argument("--header", type=Path, default=DEFAULT_HEADER_PATH, help="Narrow type header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"overlay type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare(REPO_ROOT, target=args.target, header_path=header_path),
        *apply_data_var_updates(REPO_ROOT, target=args.target, updates=DATA_VAR_UPDATES),
        *apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
