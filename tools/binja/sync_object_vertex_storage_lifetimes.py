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
    "tColour": 0x10,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "Object": {
        0x2C: ("vertex_count", "int32_t"),
        0x38: ("vertices", "Vec3*"),
        0x3C: ("copied_vertices", "Vec3*"),
        0x48: ("vertex_colours", "tColour*"),
    },
}

# Object owns the live/copy Vec3 banks and the tColour bank. VC6 walks both
# loops with byte offsets in EAX; those values are integers, not element
# pointers. Only the complete array bases and completed Vec3 addresses receive
# record-pointer types.
OBJECT_VERTEX_STORAGE_USER_VAR_UPDATES = (
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        524288,
        66,
        "vertex_count",
        "int32_t",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        3,
        68,
        "vertex_index",
        "int32_t",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        12,
        66,
        "vertex_byte_offset",
        "int32_t",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        14,
        73,
        "source_vertices",
        "Vec3*",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        17,
        72,
        "source_vertex_byte_offset",
        "int32_t",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        19,
        72,
        "source_vertex",
        "Vec3*",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        21,
        73,
        "copied_vertices",
        "Vec3*",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        24,
        73,
        "copied_vertex",
        "Vec3*",
    ),
    (
        "copy_object_vertices",
        "RegisterVariableSourceType",
        46,
        72,
        "refreshed_vertex_count",
        "int32_t",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        1,
        72,
        "owner",
        "Object*",
    ),
    (
        "request_object_vertex_colours",
        "StackVariableSourceType",
        14,
        -12,
        "allocation_byte_count",
        "int32_t",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        15,
        66,
        "allocated_colours",
        "tColour*",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        29,
        67,
        "vertex_index",
        "int32_t",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        36,
        66,
        "colour_byte_offset",
        "int32_t",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        43,
        73,
        "red_colour_bank",
        "tColour*",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        50,
        73,
        "green_colour_bank",
        "tColour*",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        57,
        73,
        "blue_colour_bank",
        "tColour*",
    ),
    (
        "request_object_vertex_colours",
        "RegisterVariableSourceType",
        64,
        73,
        "refreshed_vertex_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay Object vertex-copy and colour-bank ownership while "
            "preserving native 0xc/0x10 integer byte cursors."
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
        help="Header documenting the canonical Object vertex storage graph.",
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
            "canonical Object vertex storage layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_vertex_storage_owner_layouts",
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
            updates=OBJECT_VERTEX_STORAGE_USER_VAR_UPDATES,
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
