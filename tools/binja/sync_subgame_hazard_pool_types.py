#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_user_var_updates,
    current_enum_members,
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

SALT_STATE_TYPE_REPLACEMENTS = ("SaltState",)

CANONICAL_HAZARD_STRUCTS = (
    "SubLazer",
    "SubLazerManager",
    "Salt",
    "SaltManager",
)

EXPECTED_SALT_STATE_MEMBERS = (
    ("SALT_STATE_INACTIVE", 0),
    ("SALT_STATE_ACTIVE", 1),
    ("SALT_STATE_RECYCLE_PENDING", 2),
)

SUB_LAZER_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "state", "int32_t"),
    ("0x84", "unknown_84", "uint8_t[0x4]"),
    ("0x88", "owner_game", "SubgameRuntime*"),
    ("0x8c", "velocity", "Vec3"),
    ("0x98", "sprite_bob_phase", "float"),
    ("0x9c", "sprite_bob_phase_step", "float"),
    ("0xa0", "unknown_a0", "uint8_t[0x10]"),
)

SUB_LAZER_MANAGER_FIELD_UPDATES = (
    ("0x00", "slots", "SubLazer[0x14]"),
)

SALT_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "state", "SaltState"),
    ("0x84", "unknown_84", "uint8_t[0x4]"),
    ("0x88", "owner_game", "SubgameRuntime*"),
    ("0x8c", "fade_alpha", "float"),
    ("0x90", "spawn_velocity_y", "float"),
    ("0x94", "collision_armed", "uint8_t"),
    ("0x95", "unknown_95", "uint8_t[0x3]"),
)

SALT_MANAGER_FIELD_UPDATES = (
    ("0x00", "slots", "Salt[0x28]"),
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "SubgameRuntime*"),
)

PROTO_UPDATES = (
    (
        "initialize_sub_lazer_runtime",
        "SubLazer* __thiscall initialize_sub_lazer_runtime(SubLazer* sub_lazer)",
    ),
    (
        "initialize_salt_hazard_runtime",
        "Salt* __thiscall initialize_salt_hazard_runtime(Salt* salt)",
    ),
    (
        "initialize_sub_lazer_pool",
        "void __thiscall initialize_sub_lazer_pool(SubLazerManager* manager)",
    ),
    (
        "initialize_salt_hazard_pool",
        "void __thiscall initialize_salt_hazard_pool(SaltManager* manager)",
    ),
    (
        "spawn_sub_lazer_projectile",
        "void __thiscall spawn_sub_lazer_projectile(SubLazer* sub_lazer, const Vec3* origin, const Vec3* direction)",
    ),
    (
        "deactivate_sub_lazer_projectile",
        "void __thiscall deactivate_sub_lazer_projectile(SubLazer* sub_lazer)",
    ),
    (
        "update_sub_lazer_projectile",
        "void __thiscall update_sub_lazer_projectile(SubLazer* sub_lazer)",
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
        "void __thiscall update_salt_hazard(Salt* salt)",
    ),
)

# The selected inline Salt slot is held in ESI after the pool scan. Without
# this exact MLIL owner, BN narrows it to the embedded BodNode base and renders
# the recovered Salt fields as raw offsets even though SaltManager::slots is
# correctly typed.
SALT_USER_VAR_UPDATES = (
    (
        "spawn_salt_hazard",
        "RegisterVariableSourceType",
        37,
        72,
        "salt",
        "Salt*",
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
    salt_state_present = (
        current_enum_members(
            REPO_ROOT,
            target=args.target,
            enum_names=SALT_STATE_TYPE_REPLACEMENTS,
        ).get("SaltState")
        == EXPECTED_SALT_STATE_MEMBERS
    )
    salt_state_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical SaltState already present",
            "header": str(header_path),
            "required_types": SALT_STATE_TYPE_REPLACEMENTS,
        }
        if salt_state_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=SALT_STATE_TYPE_REPLACEMENTS,
            include_types=SALT_STATE_TYPE_REPLACEMENTS,
        )
    )
    subgame_updates = list(SUBGAME_FIELD_UPDATES)
    if struct_exists(REPO_ROOT, target=args.target, struct_name="Player"):
        subgame_updates.extend(SUBGAME_PLAYER_FIELD_UPDATES)

    operations: list[dict[str, object]] = [
        type_operation,
        salt_state_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("FrameSubgameRuntime", FRAME_SUBGAME_FIELD_UPDATES),
                ("SubgameRuntime", subgame_updates),
                ("Banner", BANNER_FIELD_UPDATES),
                ("SubLazer", SUB_LAZER_FIELD_UPDATES),
                ("SubLazerManager", SUB_LAZER_MANAGER_FIELD_UPDATES),
                ("Salt", SALT_FIELD_UPDATES),
                ("SaltManager", SALT_MANAGER_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SALT_USER_VAR_UPDATES,
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
