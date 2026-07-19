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
    "ObjectRenderBuffers": 0x0C,
    "VertexBufferFactory": 0x8CA4,
    "Direct3DRenderer": 0xBCC0,
}

EXPECTED_STRUCT_FIELDS = {
    "ObjectRenderBuffers": {
        0x00: ("fvf", "uint32_t"),
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "VertexBufferFactory": {
        0x00: ("count", "int32_t"),
        0x04: ("buffers", "ObjectRenderBuffers[3000]"),
    },
    "Direct3DRenderer": {
        0x00: ("vertex_buffer_factory", "VertexBufferFactory"),
        0xBB94: ("device", "Direct3DDevice8*"),
    },
}

# The native function reuses EDI for the result from CreateVertexBuffer and EDX
# for the incremented pool cursor. Exact lifetime names prevent those values
# from decaying into a false vertex-count owner and an anonymous slot index.
VERTEX_BUFFER_FACTORY_USER_VAR_UPDATES = (
    (
        "create_vertex_buffer",
        "RegisterVariableSourceType",
        80,
        73,
        "create_result",
        "int32_t",
    ),
    (
        "create_vertex_buffer",
        "RegisterVariableSourceType",
        247,
        68,
        "next_count",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the D3D result and incremented pool-cursor lifetimes in "
            "create_vertex_buffer."
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
        help="Header documenting the canonical renderer buffer owners.",
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
            "canonical vertex-buffer factory ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_vertex_buffer_factory_owner_layouts",
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
            updates=VERTEX_BUFFER_FACTORY_USER_VAR_UPDATES,
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
