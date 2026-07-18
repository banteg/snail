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
    apply_user_var_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/voice_manager_types.h"

EXPECTED_STRUCT_SIZES = {
    "VoiceSet": 0x18,
    "VoiceManager": 0x188,
}

FUNCTION_SYMBOL_UPDATES = (
    ("0x448df0", "initialize_voice_set"),
    ("0x448e60", "shuffle_voice_set"),
    ("0x448ec0", "reset_voice_manager"),
    ("0x448ee0", "initialize_voice_manager"),
    ("0x4492a0", "update_voice_manager"),
    ("0x4492d0", "play_voice_manager"),
    ("0x449360", "update_voice_set"),
    ("0x449390", "play_voice_set"),
    ("0x449410", "is_voice_playing"),
)

DATA_SYMBOL_UPDATES = (
    ("0x751498", "g_voice_manager"),
)

DATA_VAR_UPDATES = (
    ("0x751498", "VoiceManager"),
)

VOICE_SET_FIELD_UPDATES = (
    ("0x00", "sample_count", "uint32_t"),
    ("0x04", "next_index", "uint32_t"),
    ("0x08", "playlist", "int32_t*"),
    ("0x0c", "bites", "int32_t*"),
    ("0x10", "cooldown", "float"),
    ("0x14", "cooldown_step", "float"),
)

VOICE_MANAGER_FIELD_UPDATES = (
    ("0x000", "sets", "VoiceSet[16]"),
    ("0x180", "global_progress", "float"),
    ("0x184", "global_frequency_seconds", "float"),
)

PROTO_UPDATES = (
    (
        "initialize_voice_set",
        "void __thiscall initialize_voice_set(VoiceSet* set, int32_t count)",
    ),
    ("shuffle_voice_set", "void __thiscall shuffle_voice_set(VoiceSet* set)"),
    (
        "reset_voice_manager",
        "void __thiscall reset_voice_manager(VoiceManager* manager)",
    ),
    (
        "initialize_voice_manager",
        "void __thiscall initialize_voice_manager(VoiceManager* manager)",
    ),
    (
        "update_voice_manager",
        "void __thiscall update_voice_manager(VoiceManager* manager)",
    ),
    (
        "play_voice_manager",
        "bool __thiscall play_voice_manager(VoiceManager* manager, int32_t set_id, uint32_t mode, int32_t sample_override)",
    ),
    (
        "update_voice_set",
        "void __thiscall update_voice_set(VoiceSet* set)",
    ),
    (
        "play_voice_set",
        "bool __thiscall play_voice_set(VoiceSet* set, int32_t sample_override)",
    ),
    (
        "is_voice_playing",
        "int32_t __thiscall is_voice_playing(VoiceManager* manager)",
    ),
)

# These three native cursors borrow elements from VoiceManager's inline bank.
# Their exact MLIL identities prevent BN from promoting a cooldown float or a
# single VoiceSet to a second VoiceManager owner and then synthesizing reverse
# pointer arithmetic around each access.
VOICE_MANAGER_USER_VAR_UPDATES = (
    (
        "reset_voice_manager",
        "RegisterVariableSourceType",
        10,
        66,
        "cooldown_cursor",
        "float*",
    ),
    (
        "update_voice_manager",
        "RegisterVariableSourceType",
        5,
        72,
        "set_cursor",
        "VoiceSet*",
    ),
    (
        "is_voice_playing",
        "RegisterVariableSourceType",
        8,
        73,
        "set_cursor",
        "VoiceSet*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact cRVoiceSet/cRVoiceManager ownership lane."
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
            "reason": "VoiceSet and VoiceManager owner sizes already current",
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
                ("VoiceSet", VOICE_SET_FIELD_UPDATES),
                ("VoiceManager", VOICE_MANAGER_FIELD_UPDATES),
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
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=VOICE_MANAGER_USER_VAR_UPDATES,
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
