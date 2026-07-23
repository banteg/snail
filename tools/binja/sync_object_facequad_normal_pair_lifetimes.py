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
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x60: ("facequad_normals", "Vec3*"),
    },
}

# ObjectFaceQuad's flag bytes live in its canonical anonymous union; the
# direct-layout guard therefore sees that union at +0 while pointer typing
# still resolves the nested `flags` member in decompilation.
#
# The exact helper walks face and output banks with native byte offsets while
# borrowing one complete face, four indexed vertices, and two output Vec3
# slots. Preserve those physical roles: the two stride variables stay integer
# byte offsets, and only actual addresses receive pointer types.
OBJECT_FACEQUAD_NORMAL_PAIR_USER_VAR_UPDATES = (
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        31,
        69,
        "face_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        15,
        71,
        "normal_byte_offset",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals_simple",
        "StackVariableSourceType",
        19,
        -88,
        "face_index",
        "int32_t",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        39,
        66,
        "face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        50,
        73,
        "vertex_0_for_lhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        67,
        68,
        "vertex_1",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        127,
        73,
        "vertex_0_for_rhs",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        144,
        66,
        "vertex_2",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "StackVariableSourceType",
        0,
        -36,
        "normal_a",
        "Vec3",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        230,
        66,
        "output_normal_a",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        256,
        66,
        "quad_face",
        "ObjectFaceQuad*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        280,
        68,
        "vertex_0_for_quad",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        297,
        66,
        "vertex_3",
        "Vec3*",
    ),
    (
        "calc_object_facequad_normals_simple",
        "StackVariableSourceType",
        0,
        -12,
        "normal_b",
        "Vec3",
    ),
    (
        "calc_object_facequad_normals_simple",
        "RegisterVariableSourceType",
        385,
        67,
        "output_normal_b",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the exact face-normal pair builder's face, vertex, and "
            "output Vec3 borrow lifetimes."
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
            "canonical object face-normal ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_facequad_normal_pair_owner_layouts",
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
            updates=OBJECT_FACEQUAD_NORMAL_PAIR_USER_VAR_UPDATES,
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
