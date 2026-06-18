#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    struct_exists,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_garbage_hazard_types.h"
TARGET = "active"

REQUIRED_HEADER_STRUCTS = (
    "BodList",
    "BodNode",
    "GarbageHazardPool",
    "GarbageHazardSlot",
    "Sprite",
    "SpriteManager",
)

GAME_FIELD_UPDATES = (
    ("0x5a8", "active_bod_list", "BodList"),
    ("0x359140", "garbage_hazards", "GarbageHazardPool"),
)

SPRITE_FIELD_UPDATES = (
    ("0x00", "object_ref", "void*"),
    ("0x04", "flags", "uint32_t"),
    ("0x08", "owner", "int32_t"),
    ("0x0c", "next", "Sprite*"),
    ("0x10", "prev", "Sprite*"),
    ("0x14", "render_bucket_index", "int32_t"),
    ("0x18", "render_depth_key", "float"),
    ("0x1c", "texture_ref", "TextureRef*"),
    ("0x20", "texture_ref_a", "TextureRef*"),
    ("0x24", "texture_ref_b", "TextureRef*"),
    ("0x28", "draw_mode", "int32_t"),
    ("0x2c", "color", "Color4f"),
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

GARBAGE_HAZARD_SLOT_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x04", "list_flags", "uint32_t"),
    ("0x08", "list_prev", "GarbageHazardSlot*"),
    ("0x0c", "list_next", "GarbageHazardSlot*"),
    ("0x38", "basis_right", "Vec3"),
    ("0x44", "basis_right_w", "float"),
    ("0x48", "basis_up", "Vec3"),
    ("0x54", "basis_up_w", "float"),
    ("0x58", "basis_forward", "Vec3"),
    ("0x64", "basis_forward_w", "float"),
    ("0x68", "world_position", "Vec3"),
    ("0x74", "world_position_w", "float"),
    ("0x80", "next_active", "GarbageHazardSlot*"),
    ("0x84", "state", "int32_t"),
    ("0x88", "collision_side", "int32_t"),
    ("0x8c", "game", "Game*"),
    ("0x90", "velocity", "Vec3"),
    ("0x9c", "radius", "float"),
    ("0xa0", "sprite_y_offset", "float"),
    ("0xa4", "unknown_a4", "int32_t"),
    ("0xa8", "burst_rate_step", "float"),
    ("0xac", "smoke_timer", "float"),
    ("0xb0", "smoke_timer_step", "float"),
    ("0xb4", "sprite", "Sprite*"),
    ("0xb8", "source_cell", "TrackRowCell*"),
    ("0xbc", "hidden", "uint8_t"),
    ("0xc0", "player", "Player*"),
)

GARBAGE_HAZARD_POOL_FIELD_UPDATES = (
    ("0x00", "active_head", "GarbageHazardSlot*"),
    ("0x04", "slots", "GarbageHazardSlot[0x32]"),
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
        "GarbageHazardSlot* __thiscall initialize_garbage_hazard(GarbageHazardSlot* slot)",
    ),
    (
        "update_garbage_hazard",
        "GarbageHazardSlot* __thiscall update_garbage_hazard(GarbageHazardSlot* slot)",
    ),
    (
        "destroy_garbage_hazard",
        "GarbageHazardSlot* __thiscall destroy_garbage_hazard(GarbageHazardSlot* slot)",
    ),
    (
        "spawn_garbage_smoke_particle",
        "void __thiscall spawn_garbage_smoke_particle(GarbageHazardSlot* slot, Vec3* position, Vec3* velocity, Player* player)",
    ),
    (
        "spawn_track_garbage_hazard",
        "Vec3* __thiscall spawn_track_garbage_hazard(Game* game, TrackRowCell* cell, Player* player)",
    ),
)


def main() -> int:
    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
            required_structs=REQUIRED_HEADER_STRUCTS,
        ),
        *apply_struct_field_updates(REPO_ROOT, target=TARGET, struct_name="Game", updates=GAME_FIELD_UPDATES),
        *apply_struct_field_updates(REPO_ROOT, target=TARGET, struct_name="Sprite", updates=SPRITE_FIELD_UPDATES),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="SpriteManager",
            updates=SPRITE_MANAGER_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="GarbageHazardSlot",
            updates=GARBAGE_HAZARD_SLOT_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="GarbageHazardPool",
            updates=GARBAGE_HAZARD_POOL_FIELD_UPDATES,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]

    if struct_exists(REPO_ROOT, target=TARGET, struct_name="GarbageHazardRuntime"):
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=TARGET,
                struct_name="GarbageHazardRuntime",
                updates=(
                    ("0x68", "world_position", "Vec3"),
                    ("0x80", "next_active", "GarbageHazardSlot*"),
                    ("0x84", "state", "int32_t"),
                    ("0x88", "collision_side", "int32_t"),
                    ("0x8c", "game", "Game*"),
                    ("0x90", "velocity", "Vec3"),
                    ("0x9c", "radius", "float"),
                    ("0xa0", "sprite_y_offset", "float"),
                    ("0xa8", "burst_rate_step", "float"),
                    ("0xac", "smoke_timer", "float"),
                    ("0xb0", "smoke_timer_step", "float"),
                    ("0xb4", "sprite", "Sprite*"),
                    ("0xb8", "source_cell", "TrackRowCell*"),
                    ("0xbc", "hidden", "uint8_t"),
                    ("0xc0", "player", "Player*"),
                ),
            )
        )

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
