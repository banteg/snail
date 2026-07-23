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
    "ObjectRenderVertex": 0x18,
    "Object": 0xDC,
    "SegmentCache": 0xA7F8,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ObjectRenderVertex": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
        0x0C: ("diffuse", "uint32_t"),
        0x10: ("u", "float"),
        0x14: ("v", "float"),
    },
    "Object": {
        0x38: ("vertices", "Vec3*"),
    },
    "SegmentCache": {
        0x2C: ("shared_vertex_buffers", "ObjectRenderVertex*[5]"),
        0xA7EC: ("build_cache_row_base", "float"),
    },
}

# VC6 keeps transformed X in x87 while materializing transformed Y/Z in the
# tail of one optimized Vec3 stack home. It walks existing 0x18-byte staging
# records through a float* cursor anchored at each record's Z lane, then
# materializes a typed ObjectRenderVertex* only after emitting the new X
# component. These are borrowed physical lifetimes, not new retained owners.
TRACK_CACHE_VERTEX_USER_VAR_UPDATES = (
    (
        "add_track_cache_vertex",
        "StackVariableSourceType",
        0,
        -12,
        "transformed",
        "Vec3",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        11,
        68,
        "source_vertices",
        "Vec3*",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        14,
        66,
        "source_vertex_component_index",
        "int32_t",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        20,
        66,
        "source_vertex",
        "Vec3*",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        23,
        68,
        "position_offset",
        "Vec3*",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        106,
        67,
        "vertex_index",
        "int32_t",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        108,
        72,
        "existing_vertex_count",
        "int32_t",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        114,
        68,
        "existing_vertex_z_cursor",
        "float*",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        196,
        66,
        "staged_vertex_component_index",
        "int32_t",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        220,
        66,
        "staged_vertex",
        "ObjectRenderVertex*",
    ),
    (
        "add_track_cache_vertex",
        "RegisterVariableSourceType",
        252,
        68,
        "next_vertex_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the borrowed source and staging vertex lifetimes in "
            "add_track_cache_vertex."
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
        help="Header documenting the canonical track-cache vertex owners.",
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
            "canonical track-cache vertex ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_vertex_owner_layouts",
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
            updates=TRACK_CACHE_VERTEX_USER_VAR_UPDATES,
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
