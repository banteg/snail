#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/display_mode_types.h"

EXPECTED_STRUCT_SIZES = (
    ("DisplayModeRecord", 0x10),
    ("DisplayModeViewSample", 0x10),
    ("DisplayModeState", 0x1C),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x406d70", "initialize_main_loop_display_state"),
    ("0x407910", "clear_display_mode_state"),
    ("0x407920", "reset_display_mode_probe_count"),
    ("0x407930", "read_next_display_mode_view_sample"),
    ("0x412940", "update_display_mode_view_state"),
    ("0x4134c0", "render_game_frame_scene"),
    ("0x433030", "get_authored_view_width"),
    ("0x433040", "get_authored_view_height"),
)

DATA_SYMBOL_UPDATES = (
    ("0x4df9e0", "g_display_mode_state"),
)

DATA_VAR_UPDATES = (
    ("0x4df9e0", "DisplayModeState"),
)

STRUCT_UPDATES = (
    (
        "DisplayModeRecord",
        (
            ("0x00", "unknown_00", "uint8_t[12]"),
            ("0x0c", "width", "uint16_t"),
            ("0x0e", "height", "uint16_t"),
        ),
    ),
    (
        "DisplayModeViewSample",
        (
            ("0x00", "x", "float"),
            ("0x04", "y", "float"),
            ("0x08", "width", "float"),
            ("0x0c", "height", "float"),
        ),
    ),
    (
        "DisplayModeState",
        (
            ("0x00", "queued_view_sample_count", "int32_t"),
            ("0x04", "probe_count", "int32_t"),
            ("0x08", "current_mode", "DisplayModeRecord*"),
            ("0x0c", "view_samples", "DisplayModeViewSample[1]"),
        ),
    ),
)

PROTO_UPDATES = (
    (
        "initialize_main_loop_display_state",
        "void __cdecl initialize_main_loop_display_state()",
    ),
    (
        "clear_display_mode_state",
        "void __thiscall clear_display_mode_state(DisplayModeState* state)",
    ),
    (
        "reset_display_mode_probe_count",
        "void __thiscall reset_display_mode_probe_count(DisplayModeState* state)",
    ),
    (
        "read_next_display_mode_view_sample",
        "uint8_t __thiscall read_next_display_mode_view_sample("
        "DisplayModeState* state, float* x, float* y, "
        "float* width, float* height)",
    ),
    (
        "update_display_mode_view_state",
        "uint8_t __thiscall update_display_mode_view_state(DisplayModeState* state)",
    ),
    (
        "render_game_frame_scene",
        "void __cdecl render_game_frame_scene()",
    ),
    (
        "get_authored_view_width",
        "float __cdecl get_authored_view_width()",
    ),
    (
        "get_authored_view_height",
        "float __cdecl get_authored_view_height()",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the exact display-mode helper ABIs and minimum state prefix "
            "to Binary Ninja."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(
            f"display-mode type header not found: {header_path}"
        )

    operations: list[dict[str, object]] = [
        types_declare_if_changed(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=STRUCT_UPDATES,
            proto_updates=PROTO_UPDATES,
        ),
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
    ]

    failed_sizes = []
    for struct_name, expected_size in EXPECTED_STRUCT_SIZES:
        observed_size = current_struct_size(
            REPO_ROOT,
            target=args.target,
            struct_name=struct_name,
        )
        verified = observed_size == expected_size
        operations.append(
            {
                "op": "owner_size_verify",
                "name": struct_name,
                "expected_size": expected_size,
                "observed_size": observed_size,
                "status": "verified" if verified else "verification_failed",
            }
        )
        if not verified:
            failed_sizes.append((struct_name, expected_size, observed_size))

    if failed_sizes:
        raise RuntimeError(
            "display-mode owner size mismatch: "
            + ", ".join(
                f"{name} expected {expected:#x}, observed {observed!r}"
                for name, expected, observed in failed_sizes
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
