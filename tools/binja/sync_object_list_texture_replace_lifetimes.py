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
REPLACE_OBJECT_GROUP_TEXTURE_REFS_PROTOTYPE = (
    "void __cdecl replace_object_group_texture_refs("
    "Object* object, TextureRef* new_texture, TextureRef* old_texture)"
)

EXPECTED_TYPE_WIDTHS = {
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
    "ObjectList": 0x0C,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectFaceQuad": {
        0x0C: ("texture_ref", "TextureRef*"),
    },
    "Object": {
        0x10: ("flags", "ObjectFlag"),
        0x2C: ("vertex_count", "int32_t"),
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0x64: ("texture_group_count", "int32_t"),
        0xD0: ("group_texture_refs", "TextureRef**"),
    },
    "ObjectList": {
        0x00: ("count", "int32_t"),
        0x08: ("objects", "Object*"),
    },
}

# Native walks the retained ObjectList allocation with a 0xdc byte offset and
# each borrowed face bank with a 0x30 byte offset. Those two cursors remain
# integers. Only the address formed after adding the list base is an Object*;
# the face-bank load is an ObjectFaceQuad* borrow, and the final +0x0c address
# is a TextureRef** slot within that borrowed record. The exact grouped-render
# callee then borrows Object::group_texture_refs and its TextureRef* entries;
# its ABI and register lifetimes complete the same replacement ownership chain.
OBJECT_LIST_TEXTURE_REPLACE_USER_VAR_UPDATES = (
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        4,
        69,
        "retained_object_list",
        "ObjectList*",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        6,
        66,
        "object_byte_offset",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "StackVariableSourceType",
        10,
        -8,
        "object_index",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "StackVariableSourceType",
        29,
        -4,
        "object_byte_offset_spill",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        33,
        66,
        "current_object",
        "Object*",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        36,
        67,
        "vertex_count",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        43,
        67,
        "facequad_count",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        46,
        72,
        "face_index",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        52,
        68,
        "face_byte_offset",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        54,
        67,
        "facequads",
        "ObjectFaceQuad*",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        61,
        67,
        "texture_ref_slot",
        "TextureRef**",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        69,
        67,
        "reloaded_facequad_count",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "StackVariableSourceType",
        82,
        -36,
        "current_object_argument",
        "Object*",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        91,
        67,
        "object_index_for_increment",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        95,
        66,
        "object_byte_offset_for_increment",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        99,
        68,
        "object_count",
        "int32_t",
    ),
    (
        "replace_object_list_texture_refs",
        "RegisterVariableSourceType",
        101,
        67,
        "next_object_index",
        "int32_t",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        524288,
        68,
        "object",
        "Object*",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        16,
        67,
        "group_index",
        "int32_t",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        24,
        72,
        "old_texture",
        "TextureRef*",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        29,
        73,
        "new_texture",
        "TextureRef*",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        33,
        66,
        "group_texture_refs",
        "TextureRef**",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        39,
        69,
        "texture",
        "TextureRef*",
    ),
    (
        "replace_object_group_texture_refs",
        "RegisterVariableSourceType",
        42,
        66,
        "texture_slot",
        "TextureRef**",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the retained ObjectList allocation, borrowed Object and "
            "ObjectFaceQuad records, grouped TextureRef slots, and integer "
            "byte cursors."
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
            "canonical object-list texture ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_list_texture_replace_owner_layouts",
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
            identifier="replace_object_group_texture_refs",
            prototype=REPLACE_OBJECT_GROUP_TEXTURE_REFS_PROTOTYPE,
        ),
    ]
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_LIST_TEXTURE_REPLACE_USER_VAR_UPDATES,
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
