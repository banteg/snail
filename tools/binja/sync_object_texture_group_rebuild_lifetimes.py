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
    "TextureRef": 0xA4,
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "TextureRef": {
        0x00: ("flags", "TextureRefFlags"),
    },
    "ObjectFaceQuad": {
        0x00: ("", "union"),
        0x0C: ("texture_ref", "TextureRef*"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x6C: ("texture_group_ends", "int32_t*"),
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


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the object texture-group sort and rebuild passes' borrowed "
            "face banks, TextureRef values, cumulative ends, and byte cursors."
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
        "op": "verify_object_texture_group_rebuild_owner_layouts",
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
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
