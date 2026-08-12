#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_type_renames,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
    types_declare_if_changed,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_loading_bar_types.h"

EXPECTED_TYPE_WIDTHS = {
    "cRLoadingBar": 0x0C,
    "LoadingVertex": 0x14,
    "LoadingQuadVertexView": 0x50,
    "ObjectRenderBuffers": 0x0C,
    "ObjectVertexBuffer": 0x04,
    "ObjectVertexBufferVtbl": 0x34,
    "Direct3DTexture8": 0x04,
    "Direct3DTexture8Vtbl": 0x0C,
}

EXPECTED_STRUCT_FIELDS = {
    "cRLoadingBar": {
        0x00: ("active", "int32_t"),
        0x04: ("previous_percent", "int32_t"),
        0x08: ("last_loading_budget", "int32_t"),
    },
    "LoadingVertex": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
        0x0C: ("u", "float"),
        0x10: ("v", "float"),
    },
    "LoadingQuadVertexView": {
        0x00: ("vertices", "LoadingVertex[4]"),
    },
    "ObjectRenderBuffers": {
        0x00: ("fvf", "uint32_t"),
        0x04: ("unknown_04", "int32_t"),
        0x08: ("vertex_buffer", "ObjectVertexBuffer*"),
    },
    "ObjectVertexBuffer": {
        0x00: ("vtbl", "ObjectVertexBufferVtbl*"),
    },
    "ObjectVertexBufferVtbl": {
        0x2C: (
            "Lock",
            "int32_t(*)(ObjectVertexBuffer*self,int32_toffset,int32_tsize,"
            "void**data,int32_tflags)",
        ),
        0x30: ("Unlock", "int32_t(*)(ObjectVertexBuffer*self)"),
    },
    "Direct3DTexture8": {
        0x00: ("vtbl", "Direct3DTexture8Vtbl*"),
    },
    "Direct3DTexture8Vtbl": {
        0x08: ("Release", "int32_t(*)(Direct3DTexture8*self)"),
    },
}

DATA_SYMBOL_UPDATES = (
    ("0x503280", "g_loading_bar_on_texture"),
    ("0x503284", "g_loading_background_vertex_buffer"),
    ("0x503288", "g_loading_background_texture"),
    ("0x503290", "g_loading_bar"),
    ("0x5032a4", "g_loading_bar_vertex_buffer"),
)

DATA_VAR_UPDATES = (
    ("0x503280", "Direct3DTexture8*"),
    ("0x503284", "ObjectRenderBuffers*"),
    ("0x503288", "Direct3DTexture8*"),
    ("0x503290", "cRLoadingBar"),
    ("0x5032a4", "ObjectRenderBuffers*"),
)

PROTO_UPDATES = (
    (
        "initialize_loading_screen",
        "void __thiscall initialize_loading_screen(cRLoadingBar* loading_bar)",
    ),
    (
        "destroy_loading_screen",
        "void __thiscall destroy_loading_screen(cRLoadingBar* loading_bar)",
    ),
    (
        "update_loading_screen",
        "void __thiscall update_loading_screen(cRLoadingBar* loading_bar)",
    ),
)

LOADING_SCREEN_USER_VAR_UPDATES = (
    (
        "initialize_loading_screen",
        "StackVariableSourceType",
        0,
        -8,
        "background_quad",
        "LoadingQuadVertexView*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact cRLoadingBar owner and void lifecycle ABI."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
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
            "canonical loading-screen resource ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_loading_screen_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=(("LoadingBar", "cRLoadingBar"),),
    )
    operations.extend(
        [
            types_declare_if_changed(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
            ),
            verify_owner_layouts(args.target),
            *apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=DATA_SYMBOL_UPDATES,
                kind="data",
            ),
            *apply_data_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=DATA_VAR_UPDATES,
            ),
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(),
                proto_updates=PROTO_UPDATES,
            ),
            *apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=LOADING_SCREEN_USER_VAR_UPDATES,
            ),
        ]
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
