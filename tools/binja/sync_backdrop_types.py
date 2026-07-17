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
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_backdrop_types.h"

GAME_ROOT_FIELD_UPDATES = (
    ("0x4ec10", "backdrop", "Backdrop"),
)

PROTO_UPDATES = (
    (
        "set_backdrop_progress_fraction",
        "void __thiscall set_backdrop_progress_fraction(Backdrop* backdrop, float zoom)",
    ),
    (
        "set_backdrop_distort",
        "void __thiscall set_backdrop_distort(Backdrop* backdrop, float distort)",
    ),
    (
        "change_backdrop",
        "void __thiscall change_backdrop(Backdrop* backdrop, LandscapeScriptRecord* record, uint8_t flip)",
    ),
    (
        "change_backdrop_real",
        "void __thiscall change_backdrop_real(Backdrop* backdrop)",
    ),
    (
        "initialize_backdrop",
        "void __thiscall initialize_backdrop(Backdrop* backdrop, int32_t last_mode)",
    ),
    (
        "set_backdrop_texture_target",
        "void __thiscall set_backdrop_texture_target(Backdrop* backdrop, int32_t world)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRBackdrop ownership slice to Binary Ninja."
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
    operations.append(
        types_declare_if_changed(
            REPO_ROOT, target=args.target, header_path=header_path
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GameRoot",
            updates=GAME_ROOT_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES)
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
