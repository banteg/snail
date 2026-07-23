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
    ensure_function_analysis,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

EXPECTED_TYPE_WIDTHS = {
    "ObjectRenderVertex": 0x18,
    "ImmediateQuadVertexBlock": 0x60,
    "ObjectVertexBuffer": 0x04,
    "ObjectRenderBuffers": 0x0C,
    "Direct3DRenderer": 0xBCC0,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectRenderVertex": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
        0x0C: ("diffuse", "uint32_t"),
        0x10: ("u", "float"),
        0x14: ("v", "float"),
    },
    "ImmediateQuadVertexBlock": {
        0x00: ("vertices", "ObjectRenderVertex[4]"),
    },
    "ObjectRenderBuffers": {
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "Direct3DRenderer": {
        0xBB88: ("renderer_state", "ObjectRenderBuffers*"),
        0xBB94: ("device", "Direct3DDevice8*"),
    },
}

# Lock returns a borrowed pointer to exactly four shared 0x18-byte FVF 0x142
# records. The wrapper is an analysis-only view of that transient 0x60-byte
# region; Direct3DRenderer.renderer_state retains the actual vertex-buffer
# owner before and after Lock/Unlock.
IMMEDIATE_QUAD_USER_VAR_UPDATES = (
    (
        "draw_textured_quad_immediate",
        "StackVariableSourceType",
        0,
        -8,
        "quad",
        "ImmediateQuadVertexBlock*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the borrowed four-vertex staging lifetime in "
            "draw_textured_quad_immediate."
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
        help="Header documenting the canonical immediate-quad vertex view.",
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
            "canonical immediate-quad ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_immediate_quad_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            include_types=("ImmediateQuadVertexBlock",),
        ),
        verify_owner_layouts(args.target),
        *ensure_function_analysis(
            REPO_ROOT,
            target=args.target,
            identifiers=("draw_textured_quad_immediate",),
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=IMMEDIATE_QUAD_USER_VAR_UPDATES,
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
