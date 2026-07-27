#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_proto_updates,
    apply_symbol_updates,
    emit_summary,
    reanalyze_functions,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "tools/match/include/rtext.h"

FUNCTION_SYMBOL_UPDATES = (
    ("0x431da0", "copy_c_string"),
    ("0x431dc0", "strings_equal_case_insensitive"),
    ("0x431e30", "skip_to_next_line"),
    ("0x431e50", "append_c_string"),
    ("0x431e80", "parse_next_space_delimited_token"),
    ("0x431ec0", "parse_next_int32"),
    ("0x431f20", "parse_next_float32"),
)

PROTO_UPDATES = (
    (
        "copy_c_string",
        "void __cdecl copy_c_string(char* destination, char* source)",
    ),
    (
        "strings_equal_case_insensitive",
        (
            "bool __cdecl strings_equal_case_insensitive("
            "char* left, char* prefix)"
        ),
    ),
    (
        "skip_to_next_line",
        "void __cdecl skip_to_next_line(char** cursor)",
    ),
    (
        "append_c_string",
        "void __cdecl append_c_string(char* destination, char* source)",
    ),
    (
        "parse_next_space_delimited_token",
        (
            "void __cdecl parse_next_space_delimited_token("
            "char** cursor, char* out)"
        ),
    ),
    ("parse_next_int32", "int32_t __cdecl parse_next_int32(char** cursor)"),
    ("parse_next_float32", "float __cdecl parse_next_float32(char** cursor)"),
)

REANALYZE_FUNCTIONS = (
    *(name for _address, name in FUNCTION_SYMBOL_UPDATES),
    "load_x_mesh",
    "load_x_animation_clip",
    "load_landscape_script_by_name",
    "initialize_intro_screen",
    "load_level_definition_file",
    "load_segment_definitions",
    "initialize_voice_manager",
    "load_object_definition",
    "get_or_create_texture_ref",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the mobile-proven RShell RText contracts in Binary Ninja."
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
        help="Path to the canonical matcher RText header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
    ]
    operations.extend(
        apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        )
    )
    operations.extend(
        reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=REANALYZE_FUNCTIONS,
        )
    )

    # A reverted GUI/CLI preview can leave a nearby old user prototype visible
    # until the next analysis pass. Re-read every ABI after caller reanalysis
    # and repair any newly exposed drift before declaring the replay settled.
    settling_operations = apply_proto_updates(
        REPO_ROOT,
        target=args.target,
        updates=PROTO_UPDATES,
    )
    operations.extend(settling_operations)
    if any(
        operation.get("op") == "proto_set_batch"
        for operation in settling_operations
    ):
        operations.extend(
            reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=REANALYZE_FUNCTIONS,
            )
        )
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
