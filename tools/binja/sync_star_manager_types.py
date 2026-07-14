#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"

EXPECTED_STRUCT_SIZES = {
    "Vec3": 0xC,
    "tColour": 0x10,
    "BodNode": 0x10,
    "BodBase": 0x38,
    "TextureRef": 0xA4,
    "Sprite": 0xB4,
    "SpriteManager": 0x83D7C,
    "StarManagerEntry": 0x2C,
    "StarManager": 0x4C,
}

TEXTURE_REF_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "loaded_width", "int32_t"),
    ("0x08", "loaded_height", "int32_t"),
    ("0x0c", "name", "char[0x80]"),
    ("0x8c", "slot_index", "int32_t"),
    ("0x90", "frame_count", "int32_t"),
    ("0x94", "frame_progress_step", "float"),
    ("0x98", "texture_ref", "void*"),
    ("0xa0", "mip_levels", "int32_t"),
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

STAR_MANAGER_ENTRY_FIELD_UPDATES = (
    ("0x00", "active", "int32_t"),
    ("0x04", "position", "Vec3"),
    ("0x10", "velocity", "Vec3"),
    ("0x1c", "sprite", "Sprite*"),
    ("0x20", "speed", "float"),
    ("0x24", "travel_distance", "float"),
    ("0x28", "alpha_scale", "float"),
)

STAR_MANAGER_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "state", "int32_t"),
    ("0x3c", "entries", "StarManagerEntry*"),
    ("0x40", "count", "int32_t"),
    ("0x44", "fade", "float"),
    ("0x48", "fade_step", "float"),
)

PROTO_UPDATES = (
    ("initialize_sprite", "void __thiscall initialize_sprite(Sprite* sprite)"),
    ("update_sprite", "void __thiscall update_sprite(Sprite* sprite)"),
    (
        "register_sprite_texture",
        "TextureRef* __stdcall register_sprite_texture(char* texture_path, int32_t texture_id, int32_t flags)",
    ),
    (
        "initialize_sprite_manager",
        "void __thiscall initialize_sprite_manager(SpriteManager* manager)",
    ),
    ("kill_sprite", "void __thiscall kill_sprite(Sprite* sprite)"),
    (
        "allocate_sprite",
        "Sprite* __thiscall allocate_sprite(SpriteManager* manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b)",
    ),
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
        "set_sprite_texture_ref",
        "TextureRef* __thiscall set_sprite_texture_ref(Sprite* sprite, int32_t texture_id, int32_t frame)",
    ),
    (
        "get_sprite_texture",
        "TextureRef* __stdcall get_sprite_texture(int32_t texture_id)",
    ),
    (
        "get_sprite_texture_ref",
        "void* __stdcall get_sprite_texture_ref(int32_t texture_id)",
    ),
    ("destroy_star_field", "int32_t __thiscall destroy_star_field(StarManager* manager)"),
    (
        "open_star_field",
        "void __thiscall open_star_field(StarManager* manager, int32_t star_count)",
    ),
    (
        "initialize_star_field",
        "int32_t __thiscall initialize_star_field(StarManager* manager)",
    ),
    ("hide_star_field", "int32_t __thiscall hide_star_field(StarManager* manager)"),
    ("unhide_star_field", "int32_t __thiscall unhide_star_field(StarManager* manager)"),
    ("update_star_field", "void __thiscall update_star_field(StarManager* manager)"),
    (
        "update_star_positions",
        "void __thiscall update_star_positions(StarManager* manager, float fade_alpha)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Repair the monotonic cRSprite/cRStarManager ownership lane."
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

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(REPO_ROOT, target=args.target, struct_name=name) != expected_size
    )
    type_operation: dict[str, object]
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["expected_sizes"] = {
            name: EXPECTED_STRUCT_SIZES[name] for name in mismatched_types
        }
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "sprite and star-manager owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    struct_updates = (
        ("TextureRef", TEXTURE_REF_FIELD_UPDATES),
        ("Sprite", SPRITE_FIELD_UPDATES),
        ("SpriteManager", SPRITE_MANAGER_FIELD_UPDATES),
        ("StarManagerEntry", STAR_MANAGER_ENTRY_FIELD_UPDATES),
        ("StarManager", STAR_MANAGER_FIELD_UPDATES),
    )
    operations: list[dict[str, object]] = [
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=struct_updates,
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
