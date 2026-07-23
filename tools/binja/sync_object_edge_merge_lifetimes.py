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
    "ObjectToonEdge": 0x24,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
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
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x38: ("vertices", "Vec3*"),
        0x60: ("facequad_normals", "Vec3*"),
    },
}

# Native overwrites the incoming vertex_b stack slot with the corresponding
# Vec3 address before searching the reverse edge. Split that post-store
# lifetime away from the still-int32_t formal rather than changing the ABI.
TARGET_VERTEX_DEFINITIONS = (
    ("0x4305f8", "mlil_ssa", "StackVariableSourceType", 88, 8),
)

TARGET_VERTEX_VAR = (
    "StackVariableSourceType",
    88,
    8,
)

# Search EBP is intentionally an int32_t* interior cursor to each edge's
# vertex_b field. The merge/shift ESI and EAX values are byte offsets, not
# ObjectToonEdge owners. Only complete edge and Vec3 addresses receive their
# corresponding pointer types.
OBJECT_EDGE_MERGE_USER_VAR_UPDATES = (
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        24,
        67,
        "source_face_normal",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        97,
        71,
        "edge_vertex_b_cursor",
        "int32_t*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        109,
        73,
        "existing_vertex_a",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        168,
        73,
        "existing_vertex_b",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        177,
        69,
        "candidate_vertex_a",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        344,
        66,
        "new_edge_vertex_a",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        355,
        67,
        "new_edge_vertex_b",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "StackVariableSourceType",
        0,
        -48,
        "direction",
        "Vec3",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        446,
        66,
        "output_direction",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        504,
        72,
        "edge_byte_offset",
        "int32_t",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        573,
        67,
        "face_normal_a",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        603,
        66,
        "face_normal_b",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "StackVariableSourceType",
        0,
        -12,
        "normal_cross",
        "Vec3",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        672,
        67,
        "edge_direction",
        "Vec3*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        714,
        66,
        "shift_byte_offset",
        "int32_t",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        723,
        72,
        "shift_source_edge",
        "ObjectToonEdge*",
    ),
    (
        "add_object_edge",
        "RegisterVariableSourceType",
        727,
        73,
        "shift_destination_edge",
        "ObjectToonEdge*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay add_object_edge's parameter-slot reuse, vertex borrows, "
            "edge offsets, normals, and whole-record shift lifetimes."
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
        help="Header documenting the canonical object edge ownership graph.",
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
            "canonical object edge ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_edge_merge_owner_layouts",
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
            identifier="add_object_edge",
            definitions=TARGET_VERTEX_DEFINITIONS,
            target_var=TARGET_VERTEX_VAR,
            variable_name="target_vertex",
            variable_type="Vec3*",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_EDGE_MERGE_USER_VAR_UPDATES,
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
