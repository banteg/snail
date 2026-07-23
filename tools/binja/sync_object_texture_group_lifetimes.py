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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

EXPECTED_TYPE_WIDTHS = {
    "TransformMatrix": 0x40,
    "tColour": 0x10,
    "TextureRef": 0xA4,
    "ObjectFaceQuad": 0x30,
    "ObjectVertexBuffer": 0x04,
    "ObjectRenderBuffers": 0x0C,
    "ObjectIndexBufferResource": 0x04,
    "ObjectIndexBuffer": 0x04,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "TextureRef": {
        0x00: ("flags", "TextureRefFlags"),
    },
    "ObjectFaceQuad": {
        0x00: ("", "union"),
        0x0C: ("texture_ref", "TextureRef*"),
    },
    "ObjectVertexBuffer": {
        0x00: ("vtbl", "ObjectVertexBufferVtbl*"),
    },
    "ObjectRenderBuffers": {
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "ObjectIndexBufferResource": {
        0x00: ("vtbl", "ObjectIndexBufferResourceVtbl*"),
    },
    "ObjectIndexBuffer": {
        0x00: ("buffer", "ObjectIndexBufferResource*"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x14: ("blend_mode", "int32_t"),
        0x18: ("override_texture_ref", "TextureRef*"),
        0x2C: ("vertex_count", "int32_t"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x64: ("texture_group_count", "int32_t"),
        0x6C: ("texture_group_ends", "int32_t*"),
        0xC0: ("render_buffers", "ObjectRenderBuffers*"),
        0xC4: ("grouped_vertex_count", "int32_t"),
        0xC8: ("index_buffer", "ObjectIndexBuffer*"),
        0xCC: ("group_index_starts", "int32_t*"),
        0xD0: ("group_texture_refs", "TextureRef**"),
        0xD4: ("group_primitive_counts", "int32_t*"),
    },
}

# The sort pass owns no face storage: it borrows Object::facequads, keeps one
# TextureRef* grouping key, and walks two independent ObjectFaceQuad* cursors.
# The insertion cursor advances only when a matching face joins the active
# group, while the scan cursor advances for every inspected face. The 0x30-byte
# stack value is the by-value ObjectFaceQuad used by the native rep-movsd swap.
OBJECT_TEXTURE_GROUP_SORT_USER_VAR_UPDATES = (
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        5,
        72,
        "retained_object",
        "Object*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        9,
        71,
        "base_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "StackVariableSourceType",
        11,
        -60,
        "grouped_swaps",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        15,
        66,
        "facequad_count",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        18,
        67,
        "facequads",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "StackVariableSourceType",
        23,
        -52,
        "retained_facequads",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "StackVariableSourceType",
        0,
        -48,
        "swap_face",
        "ObjectFaceQuad",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        35,
        68,
        "base_index_times_three",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        39,
        69,
        "scan_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        42,
        68,
        "base_face_byte_offset",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        47,
        68,
        "texture_ref",
        "TextureRef*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "StackVariableSourceType",
        51,
        -56,
        "retained_texture_ref",
        "TextureRef*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        57,
        68,
        "scan_index_times_three",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        60,
        66,
        "insert_index_times_three",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        63,
        68,
        "scan_face_byte_offset",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        66,
        66,
        "insert_face_byte_offset",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        69,
        68,
        "scan_face",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "StackVariableSourceType",
        71,
        -64,
        "insert_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        75,
        66,
        "insert_face",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        77,
        73,
        "active_texture_ref",
        "TextureRef*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        86,
        73,
        "current_insert_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        98,
        73,
        "next_insert_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        110,
        72,
        "swap_source",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        124,
        72,
        "scan_copy_source",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        126,
        73,
        "insert_copy_destination",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        142,
        73,
        "scan_copy_destination",
        "ObjectFaceQuad*",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        146,
        72,
        "insert_index_before_increment",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        150,
        67,
        "grouped_swaps_before_increment",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        154,
        72,
        "incremented_insert_index",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        155,
        67,
        "incremented_grouped_swaps",
        "int32_t",
    ),
    (
        "sort_object_faces_by_texture_group",
        "RegisterVariableSourceType",
        172,
        73,
        "refreshed_facequad_count",
        "int32_t",
    ),
)

# The two-pass rebuild repeatedly borrows Object::facequads and keeps the
# current texture reference in EDX. ECX is a 0x30 byte offset into that bank,
# not a char pointer; only the face-bank reload in EAX and the texture value
# loaded from +0x0c receive record/ref pointer types.
OBJECT_TEXTURE_GROUP_REBUILD_USER_VAR_UPDATES = (
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        4,
        72,
        "retained_object",
        "Object*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        6,
        71,
        "pass_index",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        11,
        67,
        "facequad_count",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        14,
        69,
        "group_index",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        16,
        73,
        "face_index",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        18,
        68,
        "current_texture",
        "TextureRef*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        25,
        67,
        "face_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        31,
        66,
        "facequads",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        37,
        66,
        "active_facequads",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        40,
        66,
        "active_texture",
        "TextureRef*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        67,
        68,
        "texture_group_ends",
        "int32_t*",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        107,
        69,
        "requested_group_count",
        "int32_t",
    ),
    (
        "calc_object_texture_groups",
        "RegisterVariableSourceType",
        108,
        67,
        "request_receiver",
        "Object*",
    ),
    (
        "calc_object_texture_groups",
        "StackVariableSourceType",
        110,
        -20,
        "requested_group_count_argument",
        "int32_t",
    ),
)

# The render consumer does not retain one current TextureRef. Native reloads
# four independent short-lived borrows for opaque filtering, alpha filtering,
# binding, and blend gating. The grouped start/primitive banks are borrowed
# independently at draw and counter-update sites; their indices remain scalar.
OBJECT_TEXTURE_GROUP_RENDER_USER_VAR_UPDATES = (
    (
        "render_object",
        "StackVariableSourceType",
        0,
        -64,
        "world_matrix",
        "TransformMatrix",
    ),
    (
        "render_object",
        "StackVariableSourceType",
        233,
        -84,
        "texture_to_bind",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        121,
        72,
        "texture_group_index",
        "int32_t",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        131,
        69,
        "pass_side",
        "char",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        135,
        73,
        "tint",
        "tColour*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        139,
        67,
        "render_pass_filter",
        "uint8_t",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        160,
        68,
        "opaque_pass_texture",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        192,
        68,
        "alpha_pass_texture",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        213,
        66,
        "group_texture_to_bind",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        230,
        67,
        "override_texture",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        356,
        66,
        "blend_gate_texture",
        "TextureRef*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        449,
        67,
        "render_buffers",
        "ObjectRenderBuffers*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        462,
        67,
        "vertex_buffer",
        "ObjectVertexBuffer*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        496,
        68,
        "index_buffer",
        "ObjectIndexBuffer*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        509,
        68,
        "index_buffer_resource",
        "ObjectIndexBufferResource*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        521,
        68,
        "group_primitive_counts",
        "int32_t*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        532,
        68,
        "primitive_count",
        "int32_t",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        538,
        68,
        "group_index_starts",
        "int32_t*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        544,
        68,
        "start_index",
        "int32_t",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        548,
        68,
        "grouped_vertex_count",
        "int32_t",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        566,
        66,
        "group_primitive_counts_for_stats",
        "int32_t*",
    ),
    (
        "render_object",
        "RegisterVariableSourceType",
        578,
        67,
        "drawn_primitive_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay object texture-group sort, rebuild, and render lifetimes: "
            "borrowed face/texture banks, cumulative ends, integer cursors, "
            "and grouped draw resources."
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
        help="Header documenting the canonical object-render ownership graph.",
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
            "canonical object texture-group ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_texture_group_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [verify_owner_layouts(args.target)]
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_TEXTURE_GROUP_SORT_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_TEXTURE_GROUP_REBUILD_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_TEXTURE_GROUP_RENDER_USER_VAR_UPDATES,
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
