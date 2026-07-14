#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_track_render_cache_types.h"
OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"
OBJECT_REQUIRED_STRUCTS = (
    "Vec3",
    "tColour",
    "tColourSmall",
    "ObjectRenderVertex",
    "Object",
)
SEGMENT_CACHE_REQUIRED_STRUCTS = (
    "TrackRenderCacheSlot",
    "SegmentCache",
)

TRACK_RENDER_CACHE_SLOT_FIELDS = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "cache_row_base", "float"),
)

SEGMENT_CACHE_FIELDS = (
    ("0x00", "skirt_color_bgra", "tColourSmall"),
    ("0x04", "max_vertex_counts", "int32_t[5]"),
    ("0x18", "max_index_counts", "int32_t[5]"),
    ("0x2c", "shared_vertex_buffers", "ObjectRenderVertex*[5]"),
    ("0x40", "shared_index_buffers", "uint16_t*[5]"),
    ("0x54", "owner_subgame", "SubgameRuntime*"),
    ("0x58", "slots", "TrackRenderCacheSlot[0x8f][5]"),
    ("0xa7ec", "build_cache_row_base", "float"),
    ("0xa7f0", "next_cache_row_z", "float"),
    ("0xa7f4", "next_cache_row_index", "int32_t"),
)

SYMBOL_UPDATES = (
    ("0x433830", "add_track_cache_vertex"),
    ("0x433960", "append_track_cache_object"),
)

PROTO_UPDATES = (
    ("initialize_track_render_cache_manager", "void* __thiscall initialize_track_render_cache_manager(SegmentCache* manager)"),
    ("build_track_render_caches", "int32_t __thiscall build_track_render_caches(SegmentCache* manager, tColour skirt_color)"),
    ("add_track_cache_vertex", "int32_t __thiscall add_track_cache_vertex(SegmentCache* manager, Object* source, Vec3* position, int32_t source_index, float u, float v, ObjectRenderVertex* vertices, int32_t* vertex_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv)"),
    ("append_track_cache_object", "int32_t __thiscall append_track_cache_object(SegmentCache* manager, int32_t row_index, Object* source, Vec3* position, ObjectRenderVertex* vertices, int32_t* vertex_count, uint16_t* indices, int32_t* index_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv)"),
    ("update_track_render_cache_rows", "void __thiscall update_track_render_cache_rows(SegmentCache* manager)"),
    ("remove_track_render_cache_bods", "void __thiscall remove_track_render_cache_bods(SegmentCache* manager)"),
    ("is_sub_loc_floor", "int32_t __fastcall is_sub_loc_floor(TrackRowCell* cell)"),
    ("is_sub_loc_slide", "int32_t __fastcall is_sub_loc_slide(TrackRowCell* cell)"),
    ("is_sub_loc_ramp", "int32_t __fastcall is_sub_loc_ramp(TrackRowCell* cell)"),
    ("is_sub_loc_empty", "int32_t __fastcall is_sub_loc_empty(TrackRowCell* cell)"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRSegmentCache type slice to a Binary Ninja target."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument("--header", type=Path, default=DEFAULT_HEADER_PATH, help="Narrow Binary Ninja type header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=OBJECT_HEADER_PATH,
            required_structs=OBJECT_REQUIRED_STRUCTS,
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=SEGMENT_CACHE_REQUIRED_STRUCTS,
        ),
    ]
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT, target=args.target, struct_name="TrackRenderCacheSlot", updates=TRACK_RENDER_CACHE_SLOT_FIELDS
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SegmentCache",
            updates=SEGMENT_CACHE_FIELDS,
        )
    )
    operations.extend(apply_symbol_updates(REPO_ROOT, target=args.target, updates=SYMBOL_UPDATES))
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
