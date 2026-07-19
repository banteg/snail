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
    "ObjectUv": 0x08,
    "ObjectFaceQuad": 0x30,
    "Object": 0xDC,
    "SegmentCache": 0xA7F8,
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
        0x04: ("vertex_1", "uint16_t"),
        0x06: ("vertex_2", "uint16_t"),
        0x08: ("vertex_3", "uint16_t"),
        0x10: ("uv", "ObjectUv[4]"),
    },
    "Object": {
        0x54: ("facequad_count", "int32_t"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
    },
    "SegmentCache": {
        0x54: ("owner_subgame", "SubgameRuntime*"),
    },
}

# The loop retains its 0x30-byte face offset in EBP and reloads the Object-owned
# face bank before each vertex emission. The four EAX lifetimes are the
# resulting borrowed face records; the source indices are their zero-extended
# uint16_t members, and the joined count is the next manager staging cursor.
# None is a new retained pointer, field, or pool owner.
TRACK_CACHE_FACE_USER_VAR_UPDATES = (
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        9,
        71,
        "face_byte_offset",
        "int32_t",
    ),
    (
        "append_track_cache_object",
        "StackVariableSourceType",
        25,
        -16,
        "face_index",
        "int32_t",
    ),
    (
        "append_track_cache_object",
        "StackVariableSourceType",
        0,
        -12,
        "local_position",
        "Vec3",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        71,
        66,
        "face_vertex_0",
        "ObjectFaceQuad*",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        143,
        66,
        "face_vertex_1",
        "ObjectFaceQuad*",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        216,
        66,
        "face_vertex_2",
        "ObjectFaceQuad*",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        340,
        66,
        "face_vertex_3",
        "ObjectFaceQuad*",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        107,
        68,
        "source_vertex_0",
        "uint16_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        179,
        67,
        "source_vertex_1",
        "uint16_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        253,
        67,
        "source_vertex_2",
        "uint16_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        356,
        67,
        "source_vertex_3",
        "uint16_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        289,
        66,
        "triangle_index_base",
        "int32_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        302,
        66,
        "quad_index_base",
        "int32_t",
    ),
    (
        "append_track_cache_object",
        "RegisterVariableSourceType",
        388,
        66,
        "next_index_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the borrowed ObjectFaceQuad lifetimes in "
            "append_track_cache_object."
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
        help="Header documenting the canonical track-cache face owners.",
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
            "canonical track-cache face ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_track_cache_face_owner_layouts",
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
            updates=TRACK_CACHE_FACE_USER_VAR_UPDATES,
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
