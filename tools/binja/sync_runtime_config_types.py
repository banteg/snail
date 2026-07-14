#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    emit_summary,
    ensure_function_entry,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/runtime_config_types.h"

RUNTIME_CONFIG_FIELD_UPDATES = (
    ("0x00", "sample_volume", "float"),
    ("0x04", "stream_volume", "float"),
    ("0x08", "fullscreen_enabled", "uint8_t"),
    ("0x0c", "reserved_0c", "int32_t"),
    ("0x10", "reserved_10", "int32_t"),
    ("0x14", "reserved_14", "int32_t"),
    ("0x18", "reserved_18", "int32_t"),
    ("0x1c", "render_flags", "RuntimeRenderFlag"),
    ("0x20", "validation_tail", "uint8_t[0x11]"),
    ("0x31", "load_valid_flag", "uint8_t"),
    ("0x34", "display_mode_index", "int32_t"),
    ("0x38", "steering_sensitivity", "float[0x2]"),
    ("0x40", "completion_bonus_x_source", "int32_t"),
    ("0x44", "default_challenge_speed_slider", "float"),
    ("0x48", "completion_bonus_y_source", "int32_t"),
    ("0x4c", "reserved_4c", "uint8_t"),
    ("0x4d", "reserved_4d", "uint8_t"),
    ("0x50", "reserved_50", "int32_t"),
    ("0x54", "reserved_54", "int32_t"),
    ("0x58", "reserved_58", "int32_t"),
    ("0x5c", "reserved_5c", "int32_t"),
    ("0x60", "last_entered_player_name", "char[0x40]"),
    ("0xa0", "highest_galaxy_route_index", "int32_t"),
    ("0xa4", "landscape_backdrop_variant_selector", "int32_t"),
    ("0xa8", "high_score_selected_bank", "int32_t"),
    ("0xac", "last_loading_budget", "int32_t"),
    ("0xb0", "reserved_b0", "float"),
    ("0xb4", "reserved_b4", "float"),
    ("0xb8", "reserved_b8", "float"),
    ("0xbc", "reserved_bc", "float"),
    ("0xc0", "new_game_tutorial_started", "uint8_t"),
)

DATA_SYMBOL_UPDATES = (
    ("0x4df918", "g_runtime_config"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x406c10", "initialize_default_runtime_config_thunk"),
    ("0x406c20", "initialize_default_runtime_config"),
)

DATA_VAR_UPDATES = (
    ("0x4df918", "RuntimeConfig"),
)

PROTO_UPDATES = (
    ("0x406c10", "void __cdecl initialize_default_runtime_config_thunk()"),
    ("0x406c20", "void __cdecl initialize_default_runtime_config()"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the recovered RuntimeConfig owner to Binary Ninja."
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
        help="Checked-in RuntimeConfig type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"RuntimeConfig type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare(REPO_ROOT, target=args.target, header_path=header_path),
        ensure_function_entry(REPO_ROOT, target=args.target, address=0x406C20),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="RuntimeConfig",
            updates=RUNTIME_CONFIG_FIELD_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
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
