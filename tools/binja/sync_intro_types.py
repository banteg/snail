#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_intro_types.h"

GAME_ROOT_FIELD_UPDATES = (
    ("0x4f2dc", "intro", "Intro"),
)

PROTO_UPDATES = (
    (
        "initialize_new_game_menu",
        "void __thiscall initialize_new_game_menu(Intro* intro)",
    ),
    ("update_new_game_menu", "void __thiscall update_new_game_menu(Intro* intro)"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRIntro ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(types_declare(REPO_ROOT, target=args.target, header_path=header_path))
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GameRoot",
            updates=GAME_ROOT_FIELD_UPDATES,
        )
    )
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
