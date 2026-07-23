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

OBJECT_LOADER_PROTOTYPE = (
    "void __cdecl load_object_definition(char* path, Object* object)"
)

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "ObjectUv": 0x08,
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ObjectUv": {
        0x00: ("u", "float"),
        0x04: ("v", "float"),
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
}

# The exact native 0x23c-byte frame carries three authored text buffers. The
# 0x100-byte object path is followed by two disjoint 0x80-byte texture buffers;
# byte_count is the archive loader's out parameter. The main cursor advances
# through the file, while line_cursor is a borrowed copy used to count and
# parse the current section without consuming the outer cursor.
OBJECT_LOADER_USER_VAR_UPDATES = (
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -572,
        "line_cursor",
        "char*",
    ),
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -568,
        "cursor",
        "char*",
    ),
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -516,
        "byte_count",
        "int32_t",
    ),
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -512,
        "texture_name",
        "char[0x80]",
    ),
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -384,
        "texture_path",
        "char[0x80]",
    ),
    (
        "load_object_definition",
        "StackVariableSourceType",
        0,
        -256,
        "object_file_path",
        "char[0x100]",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay load_object_definition's authored ABI, frame buffers, "
            "and parser cursor lifetimes."
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
        help="Header documenting the canonical Object owners.",
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
            "canonical object-loader ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_loader_owner_layouts",
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
            identifier="load_object_definition",
            prototype=OBJECT_LOADER_PROTOTYPE,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=OBJECT_LOADER_USER_VAR_UPDATES,
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
