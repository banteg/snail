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
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/sound_effect_manager_types.h"

EXPECTED_STRUCT_SIZES = {
    "SoundEffectManager": 0x01,
    "SoundBankEntry": 0x0C,
}

FUNCTION_SYMBOL_UPDATES = (
    ("0x44dcb0", "initialize_sound_bank"),
    ("0x44dce0", "play_sound_effect_at_position"),
    ("0x44dde0", "play_sound_effect"),
    ("0x44de00", "play_sound_effect_scaled"),
    ("0x44de20", "play_warning_sample_backend"),
    ("0x44de30", "stop_warning_sample_handle"),
)

DATA_SYMBOL_UPDATES = (
    ("0x4a2140", "g_sound_bank_entries"),
    ("0x78ff88", "g_sound_effect_manager"),
)

DATA_VAR_UPDATES = (
    ("0x4a2140", "SoundBankEntry[52]"),
    ("0x78ff88", "SoundEffectManager"),
)

SOUND_EFFECT_MANAGER_FIELD_UPDATES = (
    ("0x00", "empty_object", "uint8_t"),
)

SOUND_BANK_ENTRY_FIELD_UPDATES = (
    ("0x00", "path", "char*"),
    ("0x04", "sample_id", "int32_t"),
    ("0x08", "normalization_class", "int32_t"),
)

PROTO_UPDATES = (
    (
        "initialize_sound_bank",
        "void __thiscall initialize_sound_bank(SoundEffectManager* manager, SoundBankEntry* entries)",
    ),
    (
        "play_sound_effect_at_position",
        "void __thiscall play_sound_effect_at_position(SoundEffectManager* manager, int32_t sound_id, Vec3* position)",
    ),
    (
        "play_sound_effect",
        "void __thiscall play_sound_effect(SoundEffectManager* manager, int32_t sound_id)",
    ),
    (
        "play_sound_effect_scaled",
        "void __thiscall play_sound_effect_scaled(SoundEffectManager* manager, int32_t sound_id, float gain)",
    ),
    (
        "play_warning_sample_backend",
        "int32_t __thiscall play_warning_sample_backend(SoundEffectManager* manager, int32_t sample_id)",
    ),
    (
        "stop_warning_sample_handle",
        "void __thiscall stop_warning_sample_handle(SoundEffectManager* manager, int32_t handle)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRSound/cRSoundBank ownership lane."
    )
    parser.add_argument(
        "--target", default=DEFAULT_TARGET, help="Binary Ninja target selector."
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
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if current_struct_size(
            REPO_ROOT,
            target=args.target,
            struct_name=name,
        )
        != expected_size
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
        )
        type_operation["repaired_types"] = mismatched_types
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "SoundEffectManager and SoundBankEntry owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("SoundEffectManager", SOUND_EFFECT_MANAGER_FIELD_UPDATES),
                ("SoundBankEntry", SOUND_BANK_ENTRY_FIELD_UPDATES),
            ),
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
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
