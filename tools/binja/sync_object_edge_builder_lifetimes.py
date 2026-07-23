#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_user_var_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "TransformMatrix": 0x40,
    "ObjectFaceQuad": 0x30,
    "ObjectToonEdge": 0x24,
    "ObjectVertexBuffer": 0x04,
    "ObjectRenderBuffers": 0x0C,
    "ObjectIndexBufferResource": 0x04,
    "ObjectIndexBuffer": 0x04,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "TransformMatrix": {
        0x30: ("position", "Vec3"),
    },
    "ObjectFaceQuad": {
        0x00: ("", "union"),
        0x02: ("vertex_0", "uint16_t"),
        0x04: ("vertex_1", "uint16_t"),
        0x06: ("vertex_2", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
    },
    "ObjectToonEdge": {
        0x00: ("flags", "ObjectToonEdgeFlag"),
        0x04: ("vertex_a", "int32_t"),
        0x08: ("vertex_b", "int32_t"),
        0x0C: ("normal_a", "int32_t"),
        0x10: ("normal_b", "int32_t"),
        0x14: ("direction", "Vec3"),
        0x20: ("length", "float"),
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
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x60: ("facequad_normals", "Vec3*"),
        0x70: ("edge_count", "int32_t"),
        0x74: ("edges", "ObjectToonEdge*"),
        0xC0: ("render_buffers", "ObjectRenderBuffers*"),
        0xC4: ("grouped_vertex_count", "int32_t"),
        0xD8: ("toon_index_buffer", "ObjectIndexBuffer*"),
    },
}

# Native allocates calc_object_edges' sole local with `push ecx`, initially
# preserving the receiver. The face loop overwrites that slot with its index,
# and the optional boundary-edge compactor later overwrites it with a byte
# offset. Split those two scalar definitions away from the retained Object*
# lifetime instead of allowing the shared physical slot to infect both loops.
FACE_INDEX_DEFINITIONS = (
    ("0x4308dc", "mlil_ssa", "StackVariableSourceType", 44, -4),
    ("0x4308ea", "mlil_ssa", "StackVariableSourceType", 58, -4),
    ("0x430986", "mlil_ssa", "StackVariableSourceType", 214, -4),
)

FACE_INDEX_VAR = (
    "StackVariableSourceType",
    44,
    -4,
)

EDGE_OFFSET_SPILL_DEFINITIONS = (
    ("0x4309ac", "mlil_ssa", "StackVariableSourceType", 252, -4),
    ("0x4309b4", "mlil_ssa", "StackVariableSourceType", 260, -4),
    ("0x4309f8", "mlil_ssa", "StackVariableSourceType", 328, -4),
)

EDGE_OFFSET_SPILL_VAR = (
    "StackVariableSourceType",
    252,
    -4,
)

# EDX and its stack spill are byte offsets into the borrowed temporary bank.
# ESI/EDI become ObjectToonEdge* only after adding those offsets to the bank.
# The final REP MOVS cursors are byte-oriented one-past borrows, not new banks.
OBJECT_EDGE_BUILDER_USER_VAR_UPDATES = (
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        16,
        72,
        "face_cursor",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        25,
        73,
        "build_edges",
        "ObjectToonEdge*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        27,
        67,
        "edge_count",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        244,
        66,
        "edge_index",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        250,
        68,
        "edge_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        262,
        72,
        "last_edge_index",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        265,
        69,
        "shift_index",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        271,
        72,
        "shift_source_edge",
        "ObjectToonEdge*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        275,
        73,
        "shift_destination_edge",
        "ObjectToonEdge*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        300,
        72,
        "last_edge_index_after_reload",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        347,
        72,
        "copy_source_edges",
        "ObjectToonEdge*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        353,
        73,
        "copy_destination_edges",
        "ObjectToonEdge*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        356,
        67,
        "edge_dword_count",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        359,
        67,
        "edge_byte_count",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        362,
        66,
        "saved_edge_byte_count",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        364,
        67,
        "copy_dword_count",
        "uint32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        367,
        72,
        "copy_source_tail",
        "uint8_t*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        367,
        73,
        "copy_destination_tail",
        "uint8_t*",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        369,
        67,
        "edge_byte_count_for_tail",
        "int32_t",
    ),
    (
        "calc_object_edges",
        "RegisterVariableSourceType",
        371,
        67,
        "copy_tail_byte_count",
        "uint32_t",
    ),
)

# The consumer keeps two independent scalar loop owners: a stack edge index
# and EBP's byte offset into the ObjectToonEdge bank. The index-buffer Lock
# output is the only uint16_t bank; the current edge and vertex become typed
# borrows only after their respective address calculations.
OBJECT_TOON_CONSUMER_USER_VAR_UPDATES = (
    (
        "render_object_toon",
        "StackVariableSourceType",
        0,
        -176,
        "toon_indices",
        "uint16_t*",
    ),
    (
        "render_object_toon",
        "StackVariableSourceType",
        271,
        -160,
        "edge_index",
        "int32_t",
    ),
    (
        "render_object_toon",
        "StackVariableSourceType",
        0,
        -156,
        "view_vector",
        "Vec3",
    ),
    (
        "render_object_toon",
        "StackVariableSourceType",
        461,
        -144,
        "side_b",
        "float",
    ),
    (
        "render_object_toon",
        "StackVariableSourceType",
        0,
        -140,
        "edge_delta",
        "Vec3",
    ),
    (
        "render_object_toon",
        "StackVariableSourceType",
        0,
        -128,
        "projection",
        "TransformMatrix",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        288,
        71,
        "edge_byte_offset",
        "int32_t",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        296,
        72,
        "emitted_index_count",
        "int32_t",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        303,
        66,
        "toon_index_buffer",
        "ObjectIndexBufferResource*",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        322,
        66,
        "edge",
        "ObjectToonEdge*",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        361,
        68,
        "normal_a_index",
        "int32_t",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        374,
        73,
        "normal_a",
        "Vec3*",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        389,
        67,
        "normal_b",
        "Vec3*",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        403,
        66,
        "vertex",
        "Vec3*",
    ),
    (
        "render_object_toon",
        "RegisterVariableSourceType",
        534,
        66,
        "toon_index_buffer_for_unlock",
        "ObjectIndexBufferResource*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay calc_object_edges' reused local slot, temporary edge bank, "
            "compaction offsets, record borrows, final copy cursors, and "
            "render_object_toon's downstream edge/index-buffer borrows."
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
        help="Header documenting the canonical object topology ownership graph.",
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
            "canonical object topology ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_edge_builder_owner_layouts",
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
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="calc_object_edges",
            definitions=FACE_INDEX_DEFINITIONS,
            target_var=FACE_INDEX_VAR,
            variable_name="face_index",
            variable_type="int32_t",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="calc_object_edges",
            definitions=EDGE_OFFSET_SPILL_DEFINITIONS,
            target_var=EDGE_OFFSET_SPILL_VAR,
            variable_name="edge_byte_offset_spill",
            variable_type="int32_t",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_EDGE_BUILDER_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_TOON_CONSUMER_USER_VAR_UPDATES,
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
