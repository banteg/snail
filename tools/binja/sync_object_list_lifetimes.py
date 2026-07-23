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
    "ObjectList": 0x0C,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectList": {
        0x00: ("count", "int32_t"),
        0x04: ("capacity", "int32_t"),
        0x08: ("objects", "Object*"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x2C: ("vertex_count", "int32_t"),
    },
}

# ObjectList owns one contiguous Object[capacity] allocation. Native VC6 walks
# it with 0xdc-byte integer offsets, then materializes complete Object* borrows
# for initialization and each build stage. Keep those strength-reduced offsets
# as integers while pinning the allocation, array bases, current slots, cdecl
# argument spills, and returned append slot to their real owners.
OBJECT_LIST_USER_VAR_UPDATES = (
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        1,
        72,
        "remaining_capacity",
        "int32_t",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        6,
        73,
        "owner",
        "ObjectList*",
    ),
    (
        "initialize_object_list",
        "StackVariableSourceType",
        34,
        -16,
        "allocation_byte_count",
        "int32_t",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        35,
        66,
        "allocated_objects",
        "Object*",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        51,
        69,
        "object_byte_offset",
        "int32_t",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        53,
        68,
        "objects",
        "Object*",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        56,
        67,
        "current_object_byte_offset",
        "int32_t",
    ),
    (
        "initialize_object_list",
        "RegisterVariableSourceType",
        58,
        67,
        "current_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        2,
        72,
        "owner",
        "ObjectList*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        4,
        69,
        "object_index",
        "int32_t",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        16,
        73,
        "object_byte_offset",
        "int32_t",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        44,
        67,
        "objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        47,
        67,
        "current_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        61,
        68,
        "sort_objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        64,
        68,
        "sort_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "StackVariableSourceType",
        66,
        -16,
        "sort_object_argument",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        72,
        67,
        "grouping_objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        78,
        67,
        "grouping_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        85,
        66,
        "toon_objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        88,
        67,
        "toon_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        105,
        67,
        "edge_objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        108,
        67,
        "edge_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        115,
        67,
        "buffer_objects",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        118,
        67,
        "buffer_object",
        "Object*",
    ),
    (
        "build_all_objects",
        "StackVariableSourceType",
        120,
        -16,
        "buffer_object_argument",
        "Object*",
    ),
    (
        "build_all_objects",
        "RegisterVariableSourceType",
        129,
        66,
        "object_count",
        "int32_t",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        1,
        72,
        "owner",
        "ObjectList*",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        26,
        66,
        "append_index",
        "int32_t",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        37,
        68,
        "append_index_times_55",
        "int32_t",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        40,
        67,
        "objects",
        "Object*",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        43,
        73,
        "new_object",
        "Object*",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        46,
        67,
        "initialize_receiver",
        "Object*",
    ),
    (
        "add_object_to_list",
        "RegisterVariableSourceType",
        53,
        66,
        "result_object",
        "Object*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay ObjectList allocation, traversal, and append-slot "
            "ownership while preserving native integer byte offsets."
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
        help="Header documenting the canonical ObjectList ownership graph.",
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
            "canonical ObjectList ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_list_owner_layouts",
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
            updates=OBJECT_LIST_USER_VAR_UPDATES,
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
