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
    reanalyze_functions,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = (
    REPO_ROOT / "analysis/headers/win32_window_state_types.h"
)

SYMBOL_UPDATES = (
    ("0x4b776c", "g_controller_count_view"),
    ("0x4dfaec", "g_main_window_dc"),
    ("0x4dfaf0", "g_main_window"),
    ("0x4dfaf4", "g_fullscreen_active"),
    ("0x4dfaf8", "g_bass_window"),
    ("0x503268", "g_saved_window_rect"),
    ("0x503278", "g_saved_window_rect_valid"),
    ("0x50327c", "g_game_window_instance"),
)

DATA_VAR_UPDATES = (
    ("0x4b776c", "int32_t"),
    ("0x4dfaec", "HDC"),
    ("0x4dfaf0", "HWND"),
    ("0x4dfaf4", "uint8_t"),
    ("0x4dfaf8", "HWND"),
    ("0x503268", "RECT"),
    ("0x503278", "uint8_t"),
    ("0x50327c", "HINSTANCE"),
)

PROTO_UPDATES = (
    (
        "initialize_game_window_and_input",
        "int32_t __cdecl initialize_game_window_and_input(char* window_name)",
    ),
    (
        "enumerate_input_controllers",
        "int32_t __cdecl enumerate_input_controllers("
        "HWND window, int32_t* out_count)",
    ),
    (
        "game_window_proc",
        "LRESULT __stdcall game_window_proc("
        "HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)",
    ),
)

DEPENDENT_FUNCTIONS = (
    "initialize_game_window_and_input",
    "direct3d_renderer_set_fullscreen_mode",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the recovered process-owned Win32 window state to "
            "Binary Ninja."
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
        help="Checked-in Win32 window-state ownership header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(
            f"Win32 window-state header not found: {header_path}"
        )

    operations: list[dict[str, object]] = [
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
            kind="data",
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
        *reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=DEPENDENT_FUNCTIONS,
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
