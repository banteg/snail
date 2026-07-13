#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_hazard_pool_types.h"

FRAME_SUBGAME_FIELD_UPDATES = (
    ("0x355b64", "fringe_attachment_list_head", "FrameBodBase"),
    ("0x355b9c", "track_body_list_head", "FrameBodBase"),
    ("0x355bd4", "barrier_sub_lazer_list_head", "FrameBodBase"),
    ("0x355c0c", "salt_hazard_list_head", "FrameBodBase"),
    ("0x355c44", "landscape_slice_list_head", "FrameBodBase"),
    ("0x355c7c", "unknown_bod_355c7c", "FrameBodBase"),
    ("0x355cb4", "special_track_cell_list_head", "FrameBodBase"),
    ("0x355cec", "unknown_bod_355cec", "FrameBodBase"),
    ("0x355d24", "golb_vapour_list_head", "FrameBodBase"),
    ("0x355d5c", "unknown_bod_355d5c", "FrameBodBase"),
    ("0x356b00", "sub_lazers", "FrameSubLazerManager"),
    ("0x3578c0", "salt_hazards", "FrameSaltManager"),
    ("0x359080", "banners", "BannerPool"),
)

SUB_LAZER_FIELD_UPDATES = (
    ("0x88", "owner_game", "FrameSubgameRuntime*"),
)

SALT_FIELD_UPDATES = (
    ("0x88", "owner_game", "FrameSubgameRuntime*"),
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "FrameSubgameRuntime*"),
)

PROTO_UPDATES = (
    (
        "initialize_sub_lazer_runtime",
        "FrameSubLazerSlot* __thiscall initialize_sub_lazer_runtime(FrameSubLazerSlot* slot)",
    ),
    (
        "initialize_salt_hazard_runtime",
        "FrameSaltSlot* __thiscall initialize_salt_hazard_runtime(FrameSaltSlot* slot)",
    ),
    (
        "initialize_sub_lazer_pool",
        "int32_t* __thiscall initialize_sub_lazer_pool(FrameSubLazerManager* manager)",
    ),
    (
        "initialize_salt_hazard_pool",
        "int32_t* __thiscall initialize_salt_hazard_pool(FrameSaltManager* manager)",
    ),
    (
        "spawn_sub_lazer_projectile",
        "void __thiscall spawn_sub_lazer_projectile(FrameSubLazerSlot* slot, const FrameHazardVec3* origin, const FrameHazardVec3* direction)",
    ),
    (
        "deactivate_sub_lazer_projectile",
        "int32_t __thiscall deactivate_sub_lazer_projectile(FrameSubLazerSlot* slot)",
    ),
    (
        "update_sub_lazer_projectile",
        "void __thiscall update_sub_lazer_projectile(FrameSubLazerSlot* slot)",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(FrameSubLazerManager* manager, FrameHazardVec3* origin, const FrameHazardVec3* direction)",
    ),
    (
        "spawn_salt_hazard",
        "int32_t __thiscall spawn_salt_hazard(FrameSaltManager* manager, const FrameHazardVec3* position)",
    ),
    (
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(FrameSaltSlot* slot)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the subgame BOD-group and hazard-pool ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default="active", help="Binary Ninja target selector.")
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
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="FrameSubgameRuntime",
            updates=FRAME_SUBGAME_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="FrameSubLazerSlot",
            updates=SUB_LAZER_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="FrameSaltSlot",
            updates=SALT_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Banner",
            updates=BANNER_FIELD_UPDATES,
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
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
