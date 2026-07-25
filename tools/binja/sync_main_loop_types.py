#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_symbol_updates,
    emit_summary,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/main_loop_types.h"

PROTO_UPDATES = (
    (
        "game_startup_and_main_loop",
        "int32_t __stdcall game_startup_and_main_loop("
        "HINSTANCE hInstance, HINSTANCE hPrevInstance, "
        "LPSTR lpCmdLine, int32_t nShowCmd)",
    ),
    (
        "read_current_display_resolution",
        "int32_t* __cdecl read_current_display_resolution("
        "int32_t* out_width, int32_t* out_height)",
    ),
    (
        "read_left_mouse_button_state",
        "uint8_t __cdecl read_left_mouse_button_state(int32_t slot)",
    ),
    (
        "read_right_mouse_button_state",
        "uint8_t __cdecl read_right_mouse_button_state(int32_t slot)",
    ),
)

SYMBOL_UPDATES = (
    ("0x4b7230", "g_right_mouse_button_latch"),
    ("0x4b7234", "g_left_mouse_button_state"),
    ("0x4b7236", "g_render_queue_active"),
    ("0x4b7638", "g_mean_update_steps_per_frame"),
    ("0x4b763c", "g_current_frame_update_steps"),
    ("0x4b7640", "g_right_mouse_button_state"),
    ("0x4b7644", "g_estimated_texture_vram_bytes"),
    ("0x4b7654", "g_window_deactivated"),
    ("0x4b7758", "g_fixed_update_abort_requested"),
    ("0x4b7759", "g_frame_render_requested"),
    ("0x4b775c", "g_current_display_height"),
    ("0x4b7760", "g_authored_view_height"),
    ("0x4b7764", "g_left_mouse_button_latch"),
    ("0x4b7768", "g_main_loop_frame_count"),
    ("0x4df858", "g_current_display_width"),
    ("0x4df85c", "g_authored_view_width"),
    ("0x4df860", "g_pending_window_deactivate"),
    ("0x4df864", "g_main_loop_exit_requested"),
    ("0x4df90c", "g_game_initialization_pending"),
    ("0x4dfad0", "g_mouse_wheel_delta"),
    ("0x4dfad8", "g_application_instance"),
    ("0x4dfafc", "g_frame_time_accumulator"),
    ("0x4dfb00", "g_previous_frame_timestamp_seconds"),
    ("0x4dfb04", "g_current_frame_timestamp_seconds"),
)

DATA_VAR_UPDATES = (
    ("0x4b7230", "uint8_t[2]"),
    ("0x4b7234", "uint8_t[2]"),
    ("0x4b7236", "uint8_t"),
    ("0x4b7638", "float"),
    ("0x4b763c", "float"),
    ("0x4b7640", "uint8_t[2]"),
    ("0x4b7644", "int32_t"),
    ("0x4b7654", "uint8_t"),
    ("0x4b7758", "uint8_t"),
    ("0x4b7759", "uint8_t"),
    ("0x4b775c", "int32_t"),
    ("0x4b7760", "float"),
    ("0x4b7764", "uint8_t[2]"),
    ("0x4b7768", "float"),
    ("0x4df858", "int32_t"),
    ("0x4df85c", "float"),
    ("0x4df860", "int32_t"),
    ("0x4df864", "uint8_t"),
    ("0x4df90c", "uint8_t"),
    ("0x4dfad0", "int32_t[2]"),
    ("0x4dfad8", "void*"),
    ("0x4dfafc", "float"),
    ("0x4dfb00", "float"),
    ("0x4dfb04", "float"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the recovered WinMain-shaped startup-loop ABI to Binary Ninja."
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
        help="Path to the checked-in main-loop ABI declaration.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"main-loop type header not found: {header_path}")

    operations = [
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
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
