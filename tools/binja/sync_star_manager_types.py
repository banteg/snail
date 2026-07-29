#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_symbol_updates,
    apply_struct_and_proto_updates,
    apply_user_var_updates,
    current_struct_size,
    current_type_alias_targets,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_if_missing,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"
MATRIX_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"
OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

FUNCTION_SYMBOL_UPDATES = (
    ("0x44e410", "build_sprite_tail"),
    ("0x44e580", "get_sprite_tga"),
    ("0x44e800", "initialize_texture_list"),
    ("0x44e810", "get_or_create_texture_ref"),
)

DATA_SYMBOL_UPDATES = (
    ("0x4b7790", "g_texture_refs"),
)

DATA_VAR_UPDATES = (
    ("0x4b7790", "cRTextures"),
)

GAME_ROOT_FIELD_UPDATES = (
    ("0x4f33c", "star_manager", "StarManager"),
)

BOD_BASE_FIELD_UPDATES = (
    ("0x24", "object", "Object*"),
)

EXPECTED_STRUCT_SIZES = {
    "Vec3": 0xC,
    "tColour": 0x10,
    "TgaImageView": 0x14,
    "BodNode": 0x10,
    "BodBase": 0x38,
    "TextureRef": 0xA4,
    "TextureRefList": 0x14058,
    "Sprite": 0xB4,
    "SpriteManager": 0x83D7C,
    "StarManagerEntry": 0x2C,
    "StarManager": 0x4C,
}

EXPECTED_FLAG_TYPE_WIDTHS = {
    "TextureRefFlags": 0x4,
    "SpriteFlag": 0x4,
}

EXPECTED_AUTHORED_TYPE_ALIASES = {
    "cRTexture": "TextureRef",
    "cRTextures": "TextureRefList",
    "cRSprite": "Sprite",
    "cRSpriteManager": "SpriteManager",
}

TEXTURE_REF_FIELD_UPDATES = (
    ("0x00", "flags", "TextureRefFlags"),
    ("0x04", "loaded_width", "int32_t"),
    ("0x08", "loaded_height", "int32_t"),
    ("0x0c", "name", "char[0x80]"),
    ("0x8c", "slot_index", "int32_t"),
    ("0x90", "frame_count", "int32_t"),
    ("0x94", "frame_progress_step", "float"),
    ("0x98", "texture_ref", "void*"),
    ("0xa0", "mip_levels", "int32_t"),
)

TEXTURE_REF_LIST_FIELD_UPDATES = (
    ("0x00", "count", "int32_t"),
    ("0x04", "capacity", "int32_t"),
    ("0x08", "entries", "cRTexture[0x1f4]"),
)

SPRITE_FIELD_UPDATES = (
    ("0x00", "object_ref", "void*"),
    ("0x04", "flags", "SpriteFlag"),
    ("0x08", "owner", "int32_t"),
    ("0x0c", "next", "cRSprite*"),
    ("0x10", "prev", "cRSprite*"),
    ("0x14", "render_bucket_index", "int32_t"),
    ("0x18", "render_depth_key", "float"),
    ("0x1c", "texture_ref", "cRTexture*"),
    ("0x20", "texture_ref_a", "cRTexture*"),
    ("0x24", "texture_ref_b", "cRTexture*"),
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
    ("0x04", "sprites", "cRSprite[0xbb8]"),
    ("0x83d64", "active_heads", "cRSprite*[0x5]"),
    ("0x83d78", "free_head", "cRSprite*"),
)

STAR_MANAGER_ENTRY_FIELD_UPDATES = (
    ("0x00", "active", "int32_t"),
    ("0x04", "position", "Vec3"),
    ("0x10", "velocity", "Vec3"),
    ("0x1c", "sprite", "cRSprite*"),
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
    (
        "initialize_texture_list",
        "void __thiscall initialize_texture_list(cRTextures* texture_list, int32_t capacity)",
    ),
    (
        "get_or_create_texture_ref",
        "cRTexture* __thiscall get_or_create_texture_ref(cRTextures* texture_list, char* texture_path, void* payload, int32_t flags)",
    ),
    ("initialize_sprite", "void __thiscall initialize_sprite(cRSprite* sprite)"),
    ("update_sprite", "void __thiscall update_sprite(cRSprite* sprite)"),
    (
        "register_sprite_texture",
        "void __thiscall register_sprite_texture(cRSpriteManager* manager, char* texture_path, int32_t texture_id, int32_t flags)",
    ),
    (
        "initialize_sprite_manager",
        "void __thiscall initialize_sprite_manager(cRSpriteManager* manager)",
    ),
    ("kill_sprite", "void __thiscall kill_sprite(cRSprite* sprite)"),
    (
        "allocate_sprite",
        "cRSprite* __thiscall allocate_sprite(cRSpriteManager* manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b)",
    ),
    (
        "kill_game_sprites",
        "void __thiscall kill_game_sprites(cRSpriteManager* manager)",
    ),
    (
        "build_sprite_tail",
        "void __thiscall build_sprite_tail(cRSprite* sprite, const TransformMatrix* matrix)",
    ),
    (
        "set_sprite_manager_paused",
        "void __thiscall set_sprite_manager_paused(cRSpriteManager* manager, bool paused)",
    ),
    (
        "set_sprite_texture_ref",
        "void __thiscall set_sprite_texture_ref(cRSprite* sprite, int32_t texture_id, int32_t frame)",
    ),
    (
        "get_sprite_texture",
        "cRTexture* __thiscall get_sprite_texture(cRSpriteManager* manager, int32_t texture_id)",
    ),
    (
        "get_sprite_tga",
        "TgaImageView* __thiscall get_sprite_tga(cRSpriteManager* manager, int32_t texture_id)",
    ),
    ("destroy_star_field", "void __thiscall destroy_star_field(StarManager* manager)"),
    (
        "open_star_field",
        "void __thiscall open_star_field(StarManager* manager, int32_t star_count)",
    ),
    (
        "initialize_star_field",
        "void __thiscall initialize_star_field(StarManager* manager)",
    ),
    ("hide_star_field", "void __thiscall hide_star_field(StarManager* manager)"),
    ("unhide_star_field", "void __thiscall unhide_star_field(StarManager* manager)"),
    ("update_star_field", "void __thiscall update_star_field(StarManager* manager)"),
    (
        "update_star_positions",
        "void __thiscall update_star_positions(StarManager* manager, float fade_alpha)",
    ),
)

STAR_MANAGER_REANALYSIS_FUNCTIONS = (
    "border_mouse_test",
    "update_star_positions",
)

SPRITE_TGA_USER_VAR_UPDATES = (
    (
        "border_mouse_test",
        "RegisterVariableSourceType",
        181,
        66,
        "mask",
        "TgaImageView*",
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

    object_type_operation = types_declare_if_missing(
        REPO_ROOT,
        target=args.target,
        header_path=OBJECT_HEADER_PATH,
        required_structs=("Object",),
    )
    object_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="Object",
    )
    if object_size != 0xDC:
        raise RuntimeError(
            "Object must be exactly 0xdc bytes before BodBase ownership replay; "
            f"observed {object_size!r}"
        )

    matrix_type_operation = types_declare_if_missing(
        REPO_ROOT,
        target=args.target,
        header_path=MATRIX_HEADER_PATH,
        required_structs=("TransformMatrix",),
    )
    matrix_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="TransformMatrix",
    )
    if matrix_size != 0x40:
        raise RuntimeError(
            "TransformMatrix must be exactly 0x40 bytes before Sprite ABI replay; "
            f"observed {matrix_size!r}"
        )

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(REPO_ROOT, target=args.target, struct_name=name) != expected_size
    )
    flag_type_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_FLAG_TYPE_WIDTHS,
    )
    missing_flag_types = tuple(
        name
        for name, expected_width in EXPECTED_FLAG_TYPE_WIDTHS.items()
        if flag_type_widths.get(name) != expected_width
    )
    type_operation: dict[str, object]
    if mismatched_types or missing_flag_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=(*mismatched_types, *missing_flag_types),
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["declared_flag_types"] = missing_flag_types
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
            "expected_flag_type_widths": EXPECTED_FLAG_TYPE_WIDTHS,
        }

    current_authored_aliases = current_type_alias_targets(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_AUTHORED_TYPE_ALIASES,
    )
    stale_authored_aliases = tuple(
        name
        for name, expected_target in EXPECTED_AUTHORED_TYPE_ALIASES.items()
        if current_authored_aliases.get(name) != expected_target
    )
    authored_alias_operation = (
        types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=stale_authored_aliases,
            include_types=stale_authored_aliases,
        )
        if stale_authored_aliases
        else {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "authored mobile owner aliases already current",
            "header": str(header_path),
            "expected_aliases": EXPECTED_AUTHORED_TYPE_ALIASES,
        }
    )

    struct_updates = (
        ("BodBase", BOD_BASE_FIELD_UPDATES),
        ("TextureRef", TEXTURE_REF_FIELD_UPDATES),
        ("TextureRefList", TEXTURE_REF_LIST_FIELD_UPDATES),
        ("Sprite", SPRITE_FIELD_UPDATES),
        ("SpriteManager", SPRITE_MANAGER_FIELD_UPDATES),
        ("StarManagerEntry", STAR_MANAGER_ENTRY_FIELD_UPDATES),
        ("StarManager", STAR_MANAGER_FIELD_UPDATES),
        ("GameRoot", GAME_ROOT_FIELD_UPDATES),
    )
    operations: list[dict[str, object]] = [
        object_type_operation,
        matrix_type_operation,
        type_operation,
        authored_alias_operation,
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=struct_updates,
            proto_updates=PROTO_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        ),
        *reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=STAR_MANAGER_REANALYSIS_FUNCTIONS,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SPRITE_TGA_USER_VAR_UPDATES,
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
