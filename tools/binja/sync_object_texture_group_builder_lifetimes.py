#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_direct_proto_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

TEXTURE_GROUP_BUILDER_PROTOTYPE = (
    "void __cdecl build_object_texture_group_buffers(Object* object)"
)

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "ObjectUv": 0x08,
    "ObjectGroupedVertex": 0x1C,
    "ObjectRenderVertex": 0x18,
    "ObjectFaceQuad": 0x30,
    "ObjectVertexBuffer": 0x04,
    "ObjectRenderBuffers": 0x0C,
    "ObjectIndexBufferResource": 0x04,
    "ObjectIndexBuffer": 0x04,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectGroupedVertex": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
        0x0C: ("diffuse", "uint32_t"),
        0x10: ("u", "float"),
        0x14: ("v", "float"),
        0x18: ("source_vertex", "int32_t"),
    },
    "ObjectRenderVertex": {
        0x00: ("x", "float"),
        0x0C: ("diffuse", "uint32_t"),
        0x10: ("u", "float"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
    "ObjectRenderBuffers": {
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "ObjectVertexBuffer": {
        0x00: ("vtbl", "ObjectVertexBufferVtbl*"),
    },
    "ObjectIndexBuffer": {
        0x00: ("buffer", "ObjectIndexBufferResource*"),
    },
    "ObjectIndexBufferResource": {
        0x00: ("vtbl", "ObjectIndexBufferResourceVtbl*"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x48: ("vertex_colours", "tColour*"),
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
        0xD8: ("toon_index_buffer", "ObjectIndexBuffer*"),
    },
}

# The private grouped-vertex helper borrows one Vec3 from Object::vertices,
# scans builder-owned ObjectGroupedVertex workspace through an interior float
# cursor, and appends by integer 0x1c byte offset. Only the source vertex and
# workspace reloads are pointers; the ESI strength-reduction chain remains
# scalar arithmetic.
GROUPED_VERTEX_HELPER_USER_VAR_UPDATES = (
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        4,
        69,
        "object_owner",
        "Object*",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        14,
        73,
        "source_vertex_index",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        35,
        67,
        "source_vertices",
        "Vec3*",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        38,
        66,
        "source_float_index",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        41,
        72,
        "grouped_vertex_count",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        47,
        68,
        "source_vertex",
        "Vec3*",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        50,
        66,
        "source_x",
        "float",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        57,
        67,
        "source_y",
        "float",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        64,
        68,
        "source_z",
        "float",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        71,
        68,
        "grouped_vertex_index",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        81,
        66,
        "grouped_vertices",
        "ObjectGroupedVertex*",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        92,
        67,
        "grouped_vertex_y_cursor",
        "float*",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        245,
        72,
        "append_index_times_eight",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        252,
        72,
        "append_index_times_seven",
        "int32_t",
    ),
    (
        "get_or_append_object_texture_group_vertex",
        "RegisterVariableSourceType",
        254,
        72,
        "append_byte_offset",
        "int32_t",
    ),
)

# The exact builder owns three group-metadata allocations and retains the two
# D3D wrappers on Object. Its archive workspace and both Lock outputs are
# borrowed only for the duration of this build. Native also carries six
# independently advancing uint16 index lanes; preserving those physical
# lifetimes makes the triangle/quad topology visible without inventing a
# retained index-stream object.
TEXTURE_GROUP_BUILDER_USER_VAR_UPDATES = (
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        13,
        73,
        "scan_face_byte_offset",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        80,
        66,
        "allocated_group_index_starts",
        "int32_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        103,
        66,
        "allocated_group_texture_refs",
        "TextureRef**",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        150,
        66,
        "index_scratch",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        168,
        67,
        "group_face_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        172,
        -20,
        "face_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        191,
        72,
        "source_vertex_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        204,
        -12,
        "scan_face_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        217,
        66,
        "scan_face",
        "ObjectFaceQuad*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        347,
        66,
        "group_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        351,
        -12,
        "current_group_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        378,
        -28,
        "primitive_count",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        385,
        73,
        "face_byte_offset",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        424,
        72,
        "index_0_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        427,
        -24,
        "index_5_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        435,
        71,
        "index_2_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        441,
        66,
        "index_count_base",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        445,
        -32,
        "index_4_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        457,
        -36,
        "index_3_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        461,
        -40,
        "index_1_cursor",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        472,
        66,
        "face_for_vertex_0",
        "ObjectFaceQuad*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        499,
        66,
        "face_for_vertex_1",
        "ObjectFaceQuad*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        532,
        66,
        "face_for_vertex_2",
        "ObjectFaceQuad*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        599,
        66,
        "face_for_vertex_3",
        "ObjectFaceQuad*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        690,
        66,
        "next_primitive_count",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        874,
        66,
        "allocated_index_buffer",
        "ObjectIndexBuffer*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        896,
        66,
        "locked_vertex_buffer",
        "ObjectVertexBuffer*",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        0,
        -16,
        "locked_vertices",
        "ObjectRenderVertex*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        925,
        68,
        "upload_index",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        931,
        66,
        "locked_vertex_byte_offset",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        933,
        67,
        "grouped_vertex_byte_offset",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        963,
        72,
        "grouped_vertex_uv",
        "ObjectUv*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        994,
        72,
        "grouped_vertex_position",
        "Vec3*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        996,
        73,
        "locked_vertex",
        "ObjectRenderVertex*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        1043,
        66,
        "unlock_vertex_buffer",
        "ObjectVertexBuffer*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        1058,
        72,
        "index_byte_count",
        "int32_t",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        1063,
        66,
        "locked_index_buffer_resource",
        "ObjectIndexBufferResource*",
    ),
    (
        "build_object_texture_group_buffers",
        "StackVariableSourceType",
        0,
        -4,
        "locked_indices",
        "uint16_t*",
    ),
    (
        "build_object_texture_group_buffers",
        "RegisterVariableSourceType",
        1108,
        66,
        "unlock_index_buffer_resource",
        "ObjectIndexBufferResource*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the exact object texture-group builder's retained resource, "
            "face/index cursor, and borrowed D3D lock lifetimes."
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
        help="Header documenting the canonical Object and D3D buffer owners.",
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
        "op": "verify_object_texture_group_builder_owner_layouts",
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
        apply_direct_proto_update(
            REPO_ROOT,
            target=args.target,
            identifier="build_object_texture_group_buffers",
            prototype=TEXTURE_GROUP_BUILDER_PROTOTYPE,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=GROUPED_VERTEX_HELPER_USER_VAR_UPDATES,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=TEXTURE_GROUP_BUILDER_USER_VAR_UPDATES,
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
