#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_proto_updates,
    apply_symbol_updates,
    apply_user_var_updates,
    emit_summary,
    reanalyze_functions,
)
from _target import DEFAULT_TARGET
from sync_galaxy_layout_lifetimes import (
    GALAXY_LAYOUT_USER_VAR_UPDATES,
    verify_galaxy_layout_owners,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "tools/match/include/rstring.h"

FUNCTION_SYMBOL_UPDATES = (
    ("0x44e5a0", "ascii_upper_if_lowercase"),
    ("0x44e5b0", "rstrcpy_checked_ascii"),
    ("0x44e600", "find_case_insensitive_substring"),
    ("0x44e690", "advance_to_next_crlf_line"),
    ("0x44e6c0", "strings_equal_case_insensitive_path"),
    ("0x44e710", "parse_next_signed_int"),
)

PROTO_UPDATES = (
    (
        "ascii_upper_if_lowercase",
        "char __cdecl ascii_upper_if_lowercase(char value)",
    ),
    (
        "rstrcpy_checked_ascii",
        (
            "void __cdecl rstrcpy_checked_ascii("
            "char* destination, const char* source)"
        ),
    ),
    (
        "find_case_insensitive_substring",
        (
            "char* __cdecl find_case_insensitive_substring("
            "char* pattern, char* searched)"
        ),
    ),
    (
        "advance_to_next_crlf_line",
        "char* __cdecl advance_to_next_crlf_line(char* cursor)",
    ),
    (
        "strings_equal_case_insensitive_path",
        (
            "int32_t __cdecl strings_equal_case_insensitive_path("
            "char* left, char* right)"
        ),
    ),
    (
        "parse_next_signed_int",
        "int32_t __cdecl parse_next_signed_int(char** cursor)",
    ),
)

REANALYZE_FUNCTIONS = (
    *(name for _address, name in FUNCTION_SYMBOL_UPDATES),
    "initialize_frontend_widget",
    "border_input_text_init",
    "load_x_mesh",
    "load_or_reuse_cached_x_mesh",
    "load_x_animation_clip",
    "load_galaxy_layout",
    "open_galaxy_route",
    "update_challenge_setup_screen",
    "initialize_high_score_screen",
    "update_high_score_screen",
    "initialize_high_score_entry",
    "load_landscape_script_by_name",
    "initialize_intro_screen",
    "find_segment_path_index_by_name",
    "enumerate_matching_archive_or_fs_entries",
    "read_repeating_text_input_key_code",
    "register_sound_sample",
    "find_registered_sound_sample_id_by_name",
    "initialize_subgame",
    "update_subgame",
    "deserialize_compact_high_score_record",
    "serialize_compact_high_score_record",
    "copy_segment_definition_to_level_slot",
    "load_level_definition_file",
    "load_segment_definitions",
    "initialize_voice_manager",
    "ensure_music_stream_from_path",
    "prepare_music_stream_reload_if_path_changed",
    "play_music_stream_from_bytes",
    "update_options_menu",
    "update_thanks_for_playing_screen",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the mobile-proven RString.o helper contracts in Binary Ninja."
        )
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
        help="Path to the canonical matcher RString header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(
            f"Binary Ninja RString header not found: {header_path}"
        )

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

    # Re-read the family after callers settle. Reverted previews can otherwise
    # leave one stale user prototype visible until the next analysis pass.
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

    # Rstrfind/Rstrint are both hot in load_galaxy_layout. Reanalyzing that
    # caller can invalidate its independently proven point-bank and text
    # cursor presentation, so reassert those borrowed lifetimes only after
    # the RString family and all of its callers have settled.
    operations.append(verify_galaxy_layout_owners(args.target))
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=GALAXY_LAYOUT_USER_VAR_UPDATES,
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
