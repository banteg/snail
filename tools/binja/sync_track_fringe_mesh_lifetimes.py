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
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
    "Path": 0xA8,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "BodBase": {
        0x24: ("object", "Object*"),
    },
    "ObjectFaceQuad": {
        0x02: ("vertex_0", "uint16_t"),
        0x0C: ("texture_ref", "TextureRef*"),
        0x10: ("uv", "ObjectUv[4]"),
    },
    "Object": {
        0x38: ("vertices", "Vec3*"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
    },
    "Path": {
        0x00: ("bod", "BodBase"),
        0x44: ("segment_count", "uint32_t"),
        0x54: ("width_cells", "uint32_t"),
        0x60: ("fringe_mesh_bod", "BodBase"),
    },
}

# Both fringe builders borrow the generated Object from Path::fringe_mesh_bod,
# then keep disjoint vertex and face-bank lifetimes after allocation. Native
# additionally strength-reduces the row and face loops to interior cursors;
# those cursors remain non-owning views into the two Object-managed banks.
#
# The SuperTramp tail has two further Vec3 families: the final generated row
# and its two extrapolated cap vertices. Typing the exact register definitions
# keeps the cap copies rooted in the same generated vertex allocation instead
# of presenting them as unrelated float/int pointer arithmetic.
TRACK_FRINGE_MESH_USER_VAR_UPDATES = (
    (
        "build_track_fringe_mesh",
        "RegisterVariableSourceType",
        58,
        69,
        "generated_mesh",
        "Object*",
    ),
    (
        "build_track_fringe_mesh",
        "RegisterVariableSourceType",
        140,
        72,
        "generated_vertices",
        "Vec3*",
    ),
    (
        "build_track_fringe_mesh",
        "RegisterVariableSourceType",
        221,
        69,
        "generated_row",
        "Vec3*",
    ),
    (
        "build_track_fringe_mesh",
        "StackVariableSourceType",
        143,
        -92,
        "generated_facequads",
        "ObjectFaceQuad*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        28,
        69,
        "generated_mesh",
        "Object*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        89,
        73,
        "generated_vertices",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        92,
        69,
        "generated_facequads",
        "ObjectFaceQuad*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        836,
        66,
        "final_row_first_edge",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        852,
        67,
        "first_cap_vertex",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        959,
        66,
        "final_row_second_edge",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        1086,
        68,
        "first_cap_vertex_copy",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        1093,
        66,
        "final_row_copy",
        "Vec3*",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "RegisterVariableSourceType",
        1122,
        73,
        "final_generated_row",
        "Vec3*",
    ),
)

def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the generated vertex, face, row, and cap lifetimes "
            "in the two Path fringe mesh builders."
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
        help="Header documenting the canonical Path and generated Object owners.",
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
            "canonical track-fringe mesh ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_fringe_mesh_owner_layouts",
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
            updates=TRACK_FRINGE_MESH_USER_VAR_UPDATES,
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
