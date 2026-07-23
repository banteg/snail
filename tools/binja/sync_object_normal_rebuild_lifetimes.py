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
    "Vec3": 0x0C,
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ObjectFaceQuad": {
        0x00: ("", "union"),
        0x02: ("vertex_0", "uint16_t"),
        0x04: ("vertex_1", "uint16_t"),
        0x06: ("vertex_2", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
    },
    "Object": {
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x44: ("vertex_normals", "Vec3*"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x60: ("facequad_normals", "Vec3*"),
    },
}

# The full rebuild owns a temporary float tally, writes one or two face-normal
# Vec3 values, accumulates those values into each referenced vertex-normal
# slot, and then averages/normalizes/inverts every vertex normal. EDI carries a
# byte offset in both loops (0x30 per face, then 0x0c per vertex); it is not a
# pointer despite Binary Ninja's prior inference.
OBJECT_NORMAL_REBUILD_USER_VAR_UPDATES = (
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        26,
        66,
        "allocated_normal_tally",
        "float*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        34,
        69,
        "normal_tally",
        "float*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        63,
        73,
        "geometry_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals",
        "StackVariableSourceType",
        67,
        -104,
        "face_index",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals",
        "StackVariableSourceType",
        77,
        -100,
        "normal_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        87,
        66,
        "primary_face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        98,
        71,
        "primary_vertex_0_for_lhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        116,
        68,
        "primary_vertex_1",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        176,
        71,
        "primary_vertex_0_for_rhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        194,
        67,
        "primary_vertex_2",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "StackVariableSourceType",
        0,
        -84,
        "face_normal",
        "Vec3",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        284,
        66,
        "output_face_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        310,
        66,
        "quad_face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        334,
        71,
        "quad_vertex_0_for_lhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        352,
        68,
        "quad_vertex_2",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        412,
        71,
        "quad_vertex_0_for_rhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        430,
        67,
        "quad_vertex_3",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "StackVariableSourceType",
        0,
        -96,
        "quad_normal",
        "Vec3",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        518,
        68,
        "output_quad_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        545,
        67,
        "accumulation_face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        575,
        66,
        "quad_vertex_0_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        623,
        66,
        "quad_vertex_1_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        671,
        66,
        "quad_vertex_2_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        719,
        66,
        "quad_vertex_3_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        863,
        66,
        "primary_vertex_0_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        911,
        66,
        "primary_vertex_1_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        959,
        66,
        "primary_vertex_2_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1007,
        66,
        "primary_vertex_3_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1136,
        66,
        "validation_face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals",
        "StackVariableSourceType",
        1228,
        -104,
        "vertex_index",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1240,
        71,
        "normal_tally_cursor",
        "float*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1253,
        66,
        "averaged_normal",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1282,
        67,
        "normal_to_normalize",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals",
        "RegisterVariableSourceType",
        1295,
        66,
        "inverted_normal",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the full object normal rebuild's tally owner, face and "
            "vertex borrows, and final normal lifetimes."
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
            "canonical object normal-rebuild ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_normal_rebuild_owner_layouts",
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
            updates=OBJECT_NORMAL_REBUILD_USER_VAR_UPDATES,
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
