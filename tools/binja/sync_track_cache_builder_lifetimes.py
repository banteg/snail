#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "BodBase": 0x38,
    "Fringe": 0x38,
    "TrackRowCell": 0x54,
    "ObjectFaceQuad": 0x30,
    "ObjectRenderBuffers": 0x0C,
    "ObjectVertexBuffer": 0x04,
    "ObjectIndexBufferResource": 0x04,
    "ObjectIndexBuffer": 0x04,
    "Object": 0xDC,
    "SegmentCache": 0xA7F8,
}

EXPECTED_STRUCT_FIELDS = {
    "BodBase": {
        0x10: ("position", "Vec3"),
        0x24: ("object", "Object*"),
    },
    "Fringe": {
        0x00: ("bod", "BodBase"),
    },
    "TrackRowCell": {
        0x10: ("anchor_position", "Vec3"),
        0x24: ("object", "Object*"),
        0x40: ("lane_and_flags", "uint32_t"),
        0x44: ("fringe_front", "Fringe*"),
        0x50: ("fringe_back", "Fringe*"),
    },
    "ObjectFaceQuad": {
        0x0C: ("texture_ref", "TextureRef*"),
    },
    "ObjectRenderBuffers": {
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "ObjectVertexBuffer": {
        0x00: ("vtbl", "ObjectVertexBufferVtbl*"),
    },
    "ObjectIndexBufferResource": {
        0x00: ("vtbl", "ObjectIndexBufferResourceVtbl*"),
    },
    "ObjectIndexBuffer": {
        0x00: ("buffer", "ObjectIndexBufferResource*"),
    },
    "Object": {
        0x2C: ("vertex_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0xC0: ("render_buffers", "ObjectRenderBuffers*"),
        0xC4: ("grouped_vertex_count", "int32_t"),
        0xC8: ("index_buffer", "ObjectIndexBuffer*"),
        0xD0: ("group_texture_refs", "TextureRef**"),
        0xD4: ("group_primitive_counts", "int32_t*"),
    },
    "SegmentCache": {
        0x04: ("max_vertex_counts", "int32_t[5]"),
        0x18: ("max_index_counts", "int32_t[5]"),
        0x2C: ("shared_vertex_buffers", "ObjectRenderVertex*[5]"),
        0x40: ("shared_index_buffers", "uint16_t*[5]"),
        0x54: ("owner_subgame", "SubgameRuntime*"),
        0x58: ("slots", "TrackRenderCacheSlot[143][5]"),
    },
}

# The builder intentionally retains byte-offset induction variables while it
# traverses the 3200-by-8 runtime-cell slab. Later lifetimes are narrower
# borrows: one Fringe, the selected source/destination Objects, the two locked
# D3D streams, and Object** cursors over the five family slots. The final scan
# reuses the same registers for a separate family and cache-row reduction.
TRACK_CACHE_BUILDER_USER_VAR_UPDATES = (
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        65,
        73,
        "cell_byte_offset",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        108,
        72,
        "cache_row_index",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        0,
        -64,
        "cache_row_index_saved",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        237,
        71,
        "fringe_byte_offset",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        240,
        68,
        "fringe_object",
        "Fringe*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        375,
        66,
        "warning_cell_base",
        "uint8_t*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        519,
        66,
        "floor_or_slide_cell_base",
        "uint8_t*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        825,
        66,
        "ramp_cell_base",
        "uint8_t*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        368,
        67,
        "cell_flags",
        "uint32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        512,
        71,
        "floor_cell_flags",
        "uint32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        673,
        71,
        "slide_cell_flags",
        "uint32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        956,
        67,
        "updated_cell_flags",
        "uint32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        466,
        67,
        "source_facequads",
        "ObjectFaceQuad*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        478,
        66,
        "cache_object",
        "Object*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1021,
        73,
        "max_vertex_count_cursor",
        "int32_t*",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        1024,
        -68,
        "family_staging_cursor",
        "int32_t*",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        1028,
        -60,
        "family_count_byte_offset",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1042,
        71,
        "cache_object_ref",
        "Object**",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1070,
        66,
        "vertex_buffer",
        "ObjectVertexBuffer*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1107,
        66,
        "index_buffer",
        "ObjectIndexBufferResource*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1206,
        66,
        "index_buffer_unlock",
        "ObjectIndexBufferResource*",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        0,
        -52,
        "locked_vertices",
        "void*",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        0,
        -48,
        "locked_indices",
        "void*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1218,
        66,
        "flushed_object",
        "Object*",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1345,
        72,
        "family_index",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "StackVariableSourceType",
        1341,
        -60,
        "family_index_saved",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1353,
        73,
        "max_vertices_seen",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1355,
        71,
        "max_indices_seen",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1370,
        68,
        "cache_rows_remaining",
        "int32_t",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1382,
        72,
        "max_scan_object_ref",
        "Object**",
    ),
    (
        "build_track_render_caches",
        "RegisterVariableSourceType",
        1386,
        66,
        "max_scan_object",
        "Object*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the runtime-cell, family staging, and max-scan "
            "lifetimes in build_track_render_caches."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector. Defaults to the Snail Mail database.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Header documenting the canonical track-cache owners.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
    for type_name, expected_width in EXPECTED_TYPE_WIDTHS.items():
        observed_width = widths[type_name]
        if observed_width != expected_width:
            mismatches.append(
                f"{type_name}: expected width {expected_width:#x}, "
                f"observed {observed_width!r}"
            )
    for struct_name, expected_fields in EXPECTED_STRUCT_FIELDS.items():
        observed_fields = layouts[struct_name]
        for offset, expected in expected_fields.items():
            observed = observed_fields.get(offset)
            if observed != expected:
                mismatches.append(
                    f"{struct_name}+{offset:#x}: expected {expected!r}, "
                    f"observed {observed!r}"
                )
    if mismatches:
        raise RuntimeError(
            "canonical track-cache builder ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_builder_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=TRACK_CACHE_BUILDER_USER_VAR_UPDATES,
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
