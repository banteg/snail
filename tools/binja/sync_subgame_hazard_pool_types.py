#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    emit_summary,
    struct_exists,
    types_declare_missing_only,
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
    ("0x356b00", "sub_lazers", "SubLazerManager"),
    ("0x3578c0", "salt_hazards", "SaltManager"),
    ("0x359080", "banners", "BannerPool"),
)

SUBGAME_FIELD_UPDATES = (
    ("0x356b00", "sub_lazers", "SubLazerManager"),
    ("0x3578c0", "salt_hazards", "SaltManager"),
)

SUBGAME_PLAYER_FIELD_UPDATES = (
    # update_sub_lazer_projectile reads Player::interaction_max_z through the
    # borrowed owner_game backlink. Install this only after the Player lane is complete.
    ("0x3bb764", "player", "Player"),
)

HAZARD_TYPE_REPLACEMENTS = (
    "SubLazer",
    "SubLazerSlot",
    "SubLazerManager",
    "Salt",
    "SaltHazardSlot",
    "SaltManager",
)

CANONICAL_HAZARD_STRUCTS = (
    "SubLazer",
    "SubLazerManager",
    "Salt",
    "SaltManager",
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "SubgameRuntime*"),
)

PROTO_UPDATES = (
    (
        "initialize_sub_lazer_runtime",
        "SubLazer* __thiscall initialize_sub_lazer_runtime(SubLazer* slot)",
    ),
    (
        "initialize_salt_hazard_runtime",
        "Salt* __thiscall initialize_salt_hazard_runtime(Salt* slot)",
    ),
    (
        "initialize_sub_lazer_pool",
        "void __thiscall initialize_sub_lazer_pool(SubLazerManager* manager)",
    ),
    (
        "initialize_salt_hazard_pool",
        "int32_t* __thiscall initialize_salt_hazard_pool(SaltManager* manager)",
    ),
    (
        "spawn_sub_lazer_projectile",
        "void __thiscall spawn_sub_lazer_projectile(SubLazer* slot, const Vec3* origin, const Vec3* direction)",
    ),
    (
        "deactivate_sub_lazer_projectile",
        "void __thiscall deactivate_sub_lazer_projectile(SubLazer* slot)",
    ),
    (
        "update_sub_lazer_projectile",
        "void __thiscall update_sub_lazer_projectile(SubLazer* slot)",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(SubLazerManager* manager, Vec3* origin, const Vec3* direction)",
    ),
    (
        "spawn_salt_hazard",
        "int32_t __thiscall spawn_salt_hazard(SaltManager* manager, const Vec3* position)",
    ),
    (
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(Salt* slot)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the subgame BOD-group and hazard-pool ownership slice to Binary Ninja."
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

    canonical_types_present = all(
        struct_exists(REPO_ROOT, target=args.target, struct_name=struct_name)
        for struct_name in CANONICAL_HAZARD_STRUCTS
    )
    type_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical hazard structs already present",
            "header": str(header_path),
            "required_structs": CANONICAL_HAZARD_STRUCTS,
        }
        if canonical_types_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=HAZARD_TYPE_REPLACEMENTS,
        )
    )
    subgame_updates = list(SUBGAME_FIELD_UPDATES)
    if struct_exists(REPO_ROOT, target=args.target, struct_name="Player"):
        subgame_updates.extend(SUBGAME_PLAYER_FIELD_UPDATES)

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("FrameSubgameRuntime", FRAME_SUBGAME_FIELD_UPDATES),
                ("SubgameRuntime", subgame_updates),
                ("Banner", BANNER_FIELD_UPDATES),
            ),
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
