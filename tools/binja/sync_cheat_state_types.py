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
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/cheat_state_types.h"

EXPECTED_CHEAT_STATE_SIZE = 0x10

FUNCTION_SYMBOL_UPDATES = (
    ("0x404740", "initialize_cheat"),
    ("0x404750", "update_cheat"),
    ("0x4047d0", "match_cheat_text"),
)

DATA_SYMBOL_UPDATES = (
    ("0x4b2f40", "g_cheat_state"),
)

DATA_VAR_UPDATES = (
    ("0x4b2f40", "CheatState"),
)

CHEAT_STATE_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "unused_04", "uint32_t"),
    ("0x08", "recent_text", "CheatTextBuffer"),
)

PROTO_UPDATES = (
    (
        "initialize_cheat",
        "void __thiscall initialize_cheat(CheatState* cheat)",
    ),
    (
        "update_cheat",
        "void __thiscall update_cheat(CheatState* cheat)",
    ),
    (
        "match_cheat_text",
        "bool __thiscall match_cheat_text(CheatState* cheat, char* text)",
    ),
)

# Both cursors are char* borrows into CheatState.recent_text.bytes. Their exact
# MLIL identities keep the reverse rolling-buffer loops attached to that owner
# without inventing a second allocation or widening the eight-byte buffer.
USER_VAR_UPDATES = (
    (
        "update_cheat",
        "RegisterVariableSourceType",
        33,
        67,
        "recent_text_cursor",
        "char*",
    ),
    (
        "match_cheat_text",
        "RegisterVariableSourceType",
        57,
        68,
        "recent_text_cursor",
        "char*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact cRCheat global owner and lifecycle ABIs."
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
        raise FileNotFoundError(f"CheatState type header not found: {header_path}")

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
            struct_updates=(("CheatState", CHEAT_STATE_FIELD_UPDATES),),
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
            updates=USER_VAR_UPDATES,
        ),
    ]

    observed_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="CheatState",
    )
    operations.append(
        {
            "op": "owner_size_verify",
            "name": "CheatState",
            "expected_size": EXPECTED_CHEAT_STATE_SIZE,
            "observed_size": observed_size,
            "status": (
                "verified"
                if observed_size == EXPECTED_CHEAT_STATE_SIZE
                else "verification_failed"
            ),
        }
    )
    if observed_size != EXPECTED_CHEAT_STATE_SIZE:
        raise RuntimeError(
            "CheatState owner size mismatch: "
            f"expected {EXPECTED_CHEAT_STATE_SIZE:#x}, observed {observed_size!r}"
        )

    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
