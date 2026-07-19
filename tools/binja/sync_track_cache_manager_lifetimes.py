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
    "BodBase": 0x38,
    "TrackRenderCacheSlot": 0x3C,
    "TrackRenderCacheSlotCursor": 0x94,
    "ObjectRenderVertex": 0x18,
    "ObjectRenderBuffers": 0x0C,
    "ObjectIndexBuffer": 0x04,
    "Object": 0xDC,
    "SegmentCache": 0xA7F8,
}

EXPECTED_STRUCT_FIELDS = {
    "BodBase": {
        0x24: ("object", "Object*"),
    },
    "TrackRenderCacheSlot": {
        0x00: ("bod", "BodBase"),
        0x38: ("cache_row_base", "float"),
    },
    "TrackRenderCacheSlotCursor": {
        0x58: ("slot", "TrackRenderCacheSlot"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x14: ("blend_mode", "int32_t"),
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x64: ("texture_group_count", "int32_t"),
        0xC0: ("render_buffers", "ObjectRenderBuffers*"),
        0xC8: ("index_buffer", "ObjectIndexBuffer*"),
        0xCC: ("group_index_starts", "int32_t*"),
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

# The constructor's main induction value is manager-relative: it advances by
# one 0x3c-byte slot while the actual TrackRenderCacheSlot begins at +0x58.
# The cursor type preserves that physical shape and exposes the owned slot
# without claiming the pre-slot address is a standalone slot allocation.
TRACK_CACHE_MANAGER_USER_VAR_UPDATES = (
    (
        "initialize_track_render_cache_manager",
        "StackVariableSourceType",
        87,
        -8,
        "slot_base",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "StackVariableSourceType",
        91,
        -4,
        "skirt_object_ref",
        "Object**",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        97,
        73,
        "family_index",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        115,
        72,
        "slot_cursor",
        "TrackRenderCacheSlotCursor*",
    ),
    (
        "initialize_track_render_cache_manager",
        "StackVariableSourceType",
        123,
        -28,
        "allocated_object",
        "Object*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        124,
        67,
        "slot_bod",
        "BodBase*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        191,
        66,
        "render_buffers",
        "ObjectRenderBuffers*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        215,
        66,
        "index_buffer",
        "ObjectIndexBuffer*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        236,
        66,
        "group_index_starts",
        "int32_t*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        260,
        67,
        "group_index_zero_bytes",
        "uint8_t*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        268,
        66,
        "group_texture_refs",
        "TextureRef**",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        289,
        66,
        "group_primitive_counts",
        "int32_t*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        315,
        66,
        "skirt_object",
        "Object*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        373,
        73,
        "shared_buffers_remaining",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        378,
        66,
        "max_vertex_count",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "StackVariableSourceType",
        392,
        -32,
        "vertex_buffer_bytes",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        393,
        66,
        "shared_vertex_buffer",
        "ObjectRenderVertex*",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        400,
        68,
        "max_index_count",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "StackVariableSourceType",
        410,
        -40,
        "index_buffer_bytes",
        "int32_t",
    ),
    (
        "initialize_track_render_cache_manager",
        "RegisterVariableSourceType",
        411,
        66,
        "shared_index_buffer",
        "uint16_t*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the slot-construction and shared-buffer lifetimes "
            "in initialize_track_render_cache_manager."
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
            "canonical track-cache manager ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_manager_owner_layouts",
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
            updates=TRACK_CACHE_MANAGER_USER_VAR_UPDATES,
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
