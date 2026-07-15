#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_root_bod_catalog_types.h"
GAME_ROOT_FIELD_UPDATES = (
    ("0x44100", "root_bod_catalog", "RootBodCatalog"),
)

PROTO_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "uint8_t __thiscall initialize_game_assets_and_world(GameRoot* game)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow root BOD-catalog owner to a Binary Ninja target."
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

    operations: list[dict[str, object]] = [
        types_declare(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(("GameRoot", GAME_ROOT_FIELD_UPDATES),),
            proto_updates=PROTO_UPDATES,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
