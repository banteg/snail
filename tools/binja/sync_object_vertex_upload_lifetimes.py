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
    "ObjectRenderVertex": 0x18,
    "ObjectRenderBuffers": 0x0C,
    "ObjectVertexBuffer": 0x04,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectRenderVertex": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
        0x10: ("u", "float"),
        0x14: ("v", "float"),
    },
    "ObjectRenderBuffers": {
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "Object": {
        0x38: ("vertices", "Vec3*"),
        0x5C: ("facequads", "ObjectFaceQuad*"),
        0xC0: ("render_buffers", "ObjectRenderBuffers*"),
        0xC4: ("grouped_vertex_count", "int32_t"),
    },
}

# Direct3D's Lock writes the mapped stream pointer into the incoming Object*
# argument's caller-owned stack slot. Binary Ninja cannot split that external
# memory definition, but it does expose the later register reloads as distinct
# lifetimes. At those exact points the slot no longer carries Object ownership:
# it borrows the locked 24-byte ObjectRenderVertex stream until Unlock.
OBJECT_VERTEX_UPLOAD_USER_VAR_UPDATES = (
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        154,
        69,
        "animated_vertices",
        "ObjectRenderVertex*",
    ),
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        152,
        73,
        "animated_source_vertex",
        "Vec3*",
    ),
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        158,
        69,
        "animated_vertex",
        "ObjectRenderVertex*",
    ),
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        282,
        66,
        "dynamic_vertices",
        "ObjectRenderVertex*",
    ),
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        280,
        68,
        "dynamic_source_vertex",
        "Vec3*",
    ),
    (
        "refresh_object_vertex_buffer",
        "RegisterVariableSourceType",
        286,
        66,
        "dynamic_vertex",
        "ObjectRenderVertex*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the locked render-stream reload lifetimes in "
            "refresh_object_vertex_buffer."
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
        help="Header documenting the canonical object render-stream owners.",
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
            "canonical object render-stream ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_object_vertex_upload_owner_layouts",
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
            updates=OBJECT_VERTEX_UPLOAD_USER_VAR_UPDATES,
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
