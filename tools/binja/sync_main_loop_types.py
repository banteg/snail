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
)

SYMBOL_UPDATES = (
    ("0x4dfad0", "g_mouse_wheel_delta"),
    ("0x4dfad8", "g_application_instance"),
)

DATA_VAR_UPDATES = (
    ("0x4dfad0", "int32_t[2]"),
    ("0x4dfad8", "void*"),
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
