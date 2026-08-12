#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    emit_summary,
    ensure_function_entry,
    types_declare,
)
from _target import DEFAULT_TARGET

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
    ("0x20", "registration_key", "char[0x11]"),
    ("0x31", "registration_key_valid", "uint8_t"),
    ("0x34", "display_mode_index", "int32_t"),
    ("0x38", "steering_sensitivity", "float[0x2]"),
    ("0x40", "challenge_speed_percent", "int32_t"),
    ("0x44", "default_challenge_speed_slider", "float"),
    ("0x48", "challenge_difficulty_percent", "int32_t"),
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

DATA_SYMBOL_UPDATES = (("0x4df918", "g_runtime_config"),)

FUNCTION_SYMBOL_UPDATES = (
    ("0x406c10", "initialize_default_runtime_config_thunk"),
    ("0x406c20", "initialize_default_runtime_config"),
    ("0x42f470", "load_config_file"),
    ("0x42f490", "load_file_bytes_from_path"),
    ("0x42f540", "save_config_file"),
    ("0x42f5b0", "validate_config_tail_stub"),
)

DATA_VAR_UPDATES = (("0x4df918", "RuntimeConfig"),)

PROTO_UPDATES = (
    ("0x406c10", "void __cdecl initialize_default_runtime_config_thunk()"),
    ("0x406c20", "void __cdecl initialize_default_runtime_config()"),
    ("0x42f470", "void* __cdecl load_config_file(char* file_name, void* buffer)"),
    (
        "0x42f490",
        "void* __cdecl load_file_bytes_from_path(char* file_name, void* buffer, int32_t* out_size, int32_t byte_count)",
    ),
    (
        "0x42f540",
        "char* __cdecl save_config_file(char* file_name, void* bytes, int32_t byte_count)",
    ),
    (
        "0x42f5b0",
        "uint8_t __cdecl validate_config_tail_stub(char* registration_key)",
    ),
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
        ensure_function_entry(REPO_ROOT, target=args.target, address=0x42F5B0),
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
