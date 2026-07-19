#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    current_enum_members,
    emit_summary,
    struct_exists,
    types_declare_if_missing,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_garbage_hazard_types.h"

REQUIRED_HEADER_STRUCTS = (
    "BodList",
    "BodNode",
    "SpriteFlag",
    "SubGarbagePool",
    "SubGarbage",
    "SubGarbageSlotCursor",
    "Sprite",
    "SpriteManager",
)

GARBAGE_ENUM_TYPE_REPLACEMENTS = (
    "SubGarbageState",
    "SubGarbageCollisionSide",
)

EXPECTED_GARBAGE_ENUM_MEMBERS = {
    "SubGarbageState": (
        ("SUB_GARBAGE_STATE_INACTIVE", 0),
        ("SUB_GARBAGE_STATE_ACTIVE", 1),
        ("SUB_GARBAGE_STATE_BURST_PENDING", 2),
        ("SUB_GARBAGE_STATE_BURST", 3),
    ),
    "SubGarbageCollisionSide": (
        ("SUB_GARBAGE_COLLISION_SIDE_RIGHT", 1),
        ("SUB_GARBAGE_COLLISION_SIDE_LEFT", 2),
    ),
}

GAME_FIELD_UPDATES = (
    ("0x5a8", "active_bod_list", "BodList"),
    ("0x359140", "garbage_hazards", "SubGarbagePool"),
)

SUBGAME_FIELD_UPDATES = (
    ("0x359140", "garbage_hazards", "SubGarbagePool"),
)

SPRITE_FIELD_UPDATES = (
    ("0x00", "object_ref", "void*"),
    ("0x04", "flags", "SpriteFlag"),
    ("0x08", "owner", "int32_t"),
    ("0x0c", "next", "Sprite*"),
    ("0x10", "prev", "Sprite*"),
    ("0x14", "render_bucket_index", "int32_t"),
    ("0x18", "render_depth_key", "float"),
    ("0x1c", "texture_ref", "TextureRef*"),
    ("0x20", "texture_ref_a", "TextureRef*"),
    ("0x24", "texture_ref_b", "TextureRef*"),
    ("0x28", "draw_mode", "int32_t"),
    ("0x2c", "color", "tColour"),
    ("0x3c", "previous_position", "Vec3"),
    ("0x48", "position", "Vec3"),
    ("0x54", "velocity", "Vec3"),
    ("0x60", "size_start", "float"),
    ("0x64", "size_end", "float"),
    ("0x68", "progress", "float"),
    ("0x6c", "progress_step", "float"),
    ("0x70", "lifetime", "float"),
    ("0x74", "lifetime_step", "float"),
    ("0x78", "gravity_step", "float"),
    ("0x7c", "facing_angle", "float"),
    ("0x80", "facing_angle_step", "float"),
    ("0x84", "reserved_84", "int32_t"),
    ("0x88", "corner_scale", "float"),
    ("0x8c", "facing_refresh_progress", "float"),
    ("0x90", "facing_refresh_step", "float"),
    ("0x94", "depth_offset", "float"),
    ("0x98", "depth_bias", "float"),
    ("0x9c", "texture_id", "int32_t"),
    ("0xa0", "frame_count", "int32_t"),
    ("0xa4", "frame", "int32_t"),
    ("0xa8", "frame_step", "int32_t"),
    ("0xac", "frame_progress", "float"),
    ("0xb0", "frame_progress_step", "float"),
)

SPRITE_MANAGER_FIELD_UPDATES = (
    ("0x00", "paused", "uint8_t"),
    ("0x04", "sprites", "Sprite[0xbb8]"),
    ("0x83d64", "active_heads", "Sprite*[0x5]"),
    ("0x83d78", "free_head", "Sprite*"),
)

SUB_GARBAGE_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "next_active", "SubGarbage*"),
    ("0x84", "state", "SubGarbageState"),
    ("0x88", "collision_side", "SubGarbageCollisionSide"),
    ("0x8c", "owner_game", "SubgameRuntime*"),
    ("0x90", "velocity", "Vec3"),
    ("0x9c", "radius", "float"),
    ("0xa0", "attachment_facing_angle", "float"),
    ("0xa4", "unknown_a4", "int32_t"),
    ("0xa8", "burst_rate_step", "float"),
    ("0xac", "smoke_timer", "float"),
    ("0xb0", "smoke_timer_step", "float"),
    ("0xb4", "sprite", "Sprite*"),
    ("0xb8", "source_cell", "TrackRowCell*"),
    ("0xbc", "hidden", "uint8_t"),
    ("0xc0", "owner_player", "Player*"),
)

SUB_GARBAGE_POOL_FIELD_UPDATES = (
    ("0x00", "active_head", "SubGarbage*"),
    ("0x04", "slots", "SubGarbage[0x32]"),
)

SPRITE_SYMBOL_UPDATES = (
    ("0x4b7790", "g_texture_refs"),
    ("0x78ff90", "g_sprite_texture_table"),
    ("0x790f30", "g_sprite_manager"),
    ("0x814c94", "g_sprite_active_heads"),
    ("0x814ca8", "g_sprite_free_head"),
    ("0x814cb0", "g_sprite_sentinel"),
)

# Keep the manager base as its pause byte here; a full SpriteManager data var
# makes BN fold the active/free tail aliases back into noisy parent expressions.
SPRITE_DATA_VAR_UPDATES = (
    ("0x78ff90", "TextureRef*[0x3e8]"),
    ("0x790f30", "uint8_t"),
    ("0x814c94", "Sprite*[5]"),
    ("0x814ca8", "Sprite*"),
    ("0x814cb0", "Sprite"),
)

PROTO_UPDATES = (
    ("initialize_sprite_manager", "void __thiscall initialize_sprite_manager(SpriteManager* manager)"),
    (
        "allocate_sprite",
        "Sprite* __thiscall allocate_sprite(SpriteManager* manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b)",
    ),
    ("initialize_sprite", "void __thiscall initialize_sprite(Sprite* sprite)"),
    ("update_sprite", "void __thiscall update_sprite(Sprite* sprite)"),
    ("kill_sprite", "void __thiscall kill_sprite(Sprite* sprite)"),
    ("kill_game_sprites", "void __thiscall kill_game_sprites(SpriteManager* manager)"),
    (
        "update_sprite_facing_angle",
        "void __thiscall update_sprite_facing_angle(Sprite* sprite, const TransformMatrix* matrix)",
    ),
    (
        "set_sprite_manager_paused",
        "uint8_t __thiscall set_sprite_manager_paused(SpriteManager* manager, uint8_t paused)",
    ),
    (
        "initialize_garbage_hazard",
        "SubGarbage* __thiscall initialize_garbage_hazard(SubGarbage* sub_garbage)",
    ),
    (
        "update_garbage_hazard",
        "void __thiscall update_garbage_hazard(SubGarbage* sub_garbage)",
    ),
    (
        "destroy_garbage_hazard",
        "SubGarbage* __thiscall destroy_garbage_hazard(SubGarbage* sub_garbage)",
    ),
    (
        "spawn_garbage_smoke_particle",
        "void __thiscall spawn_garbage_smoke_particle(SubGarbage* sub_garbage, Vec3* position, Vec3* velocity, Player* owner_player)",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* player)",
    ),
)

def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRSubGarbage and sprite ownership slice."
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

    current_garbage_enums = current_enum_members(
        REPO_ROOT,
        target=args.target,
        enum_names=GARBAGE_ENUM_TYPE_REPLACEMENTS,
    )
    garbage_enums_present = all(
        current_garbage_enums.get(name) == expected
        for name, expected in EXPECTED_GARBAGE_ENUM_MEMBERS.items()
    )
    garbage_enum_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical garbage lifecycle enums already present",
            "header": str(header_path),
            "required_types": GARBAGE_ENUM_TYPE_REPLACEMENTS,
        }
        if garbage_enums_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=GARBAGE_ENUM_TYPE_REPLACEMENTS,
            include_types=GARBAGE_ENUM_TYPE_REPLACEMENTS,
        )
    )

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=REQUIRED_HEADER_STRUCTS,
        ),
        garbage_enum_operation,
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Game",
            updates=GAME_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Sprite",
            updates=SPRITE_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SpriteManager",
            updates=SPRITE_MANAGER_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SubGarbage",
            updates=SUB_GARBAGE_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SubGarbagePool",
            updates=SUB_GARBAGE_POOL_FIELD_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SPRITE_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SPRITE_DATA_VAR_UPDATES,
        ),
        *apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES),
    ]

    for struct_name in ("SubgameRuntime", "FrameSubgameRuntime"):
        if struct_exists(REPO_ROOT, target=args.target, struct_name=struct_name):
            operations.extend(
                apply_struct_field_updates(
                    REPO_ROOT,
                    target=args.target,
                    struct_name=struct_name,
                    updates=SUBGAME_FIELD_UPDATES,
                )
            )

    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
