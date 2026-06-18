#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, apply_struct_field_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_track_render_cache_types.h"

TRACK_RENDER_GRID_FIELDS = (
    ("0x54", "cell_count", "int32_t"),
    ("0x3bfac8", "cells", "TrackRowCell[8]"),
)

TRACK_RENDER_CACHE_SLOT_FIELDS = (
    ("0x24", "render_object", "RenderObjectTextureGroups*"),
    ("0x2c", "vertex_count", "int32_t"),
)

TRACK_RENDER_CACHE_MANAGER_FIELDS = (
    ("0x04", "max_vertex_counts", "int32_t[5]"),
    ("0x18", "max_index_counts", "int32_t[5]"),
    ("0x2c", "shared_vertex_buffers", "void*[5]"),
    ("0x40", "shared_index_buffers", "void*[5]"),
    ("0x54", "track_render_grid", "TrackRenderGrid*"),
    ("0x58", "slots", "TrackRenderCacheSlot[0x2cb]"),
    ("0xa7ec", "build_cache_row_base", "float"),
    ("0xa7f0", "next_cache_row_z", "float"),
    ("0xa7f4", "next_cache_row_index", "int32_t"),
)

PROTO_UPDATES = (
    ("initialize_track_render_cache_manager", "void* __fastcall initialize_track_render_cache_manager(TrackRenderCacheManager* manager)"),
    ("build_track_render_caches", "int32_t __fastcall build_track_render_caches(TrackRenderCacheManager* manager)"),
    ("update_track_render_cache_rows", "void __fastcall update_track_render_cache_rows(TrackRenderCacheManager* manager)"),
    ("remove_track_render_cache_bods", "int32_t __fastcall remove_track_render_cache_bods(TrackRenderCacheManager* manager)"),
    ("is_slide_cache_tile_family", "int32_t __fastcall is_slide_cache_tile_family(TrackRowCell* cell)"),
    ("is_floor_cache_tile_family", "int32_t __fastcall is_floor_cache_tile_family(TrackRowCell* cell)"),
    ("is_ramp_cache_tile_family", "int32_t __fastcall is_ramp_cache_tile_family(TrackRowCell* cell)"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow track render cache type slice to the active Binary Ninja target."
    )
    parser.add_argument("--target", default="active", help="Binary Ninja target selector.")
    parser.add_argument("--header", type=Path, default=DEFAULT_HEADER_PATH, help="Narrow Binary Ninja type header.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(types_declare(REPO_ROOT, target=args.target, header_path=header_path))
    operations.extend(
        apply_struct_field_updates(REPO_ROOT, target=args.target, struct_name="TrackRenderGrid", updates=TRACK_RENDER_GRID_FIELDS)
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT, target=args.target, struct_name="TrackRenderCacheSlot", updates=TRACK_RENDER_CACHE_SLOT_FIELDS
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="TrackRenderCacheManager",
            updates=TRACK_RENDER_CACHE_MANAGER_FIELDS,
        )
    )
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
