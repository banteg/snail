#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/gui_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRGUI": 0x28,
}

OWNER_TYPE_RENAMES = (("GUI", "cRGUI"),)

REANALYSIS_FUNCTIONS = (
    "initialize_game_assets_and_world",
    "initialize_challenge_setup_screen",
    "destroy_challenge_setup_screen",
    "update_challenge_setup_screen",
    "initialize_subgame",
    "update_subgame",
)

GUI_FIELD_UPDATES = (
    ("0x00", "game", "cRSubGame*"),
    ("0x04", "next_level_button", "FrontendWidget*"),
    ("0x08", "previous_level_button", "FrontendWidget*"),
    ("0x0c", "level_name_widget", "FrontendWidget*"),
    ("0x10", "play_button", "FrontendWidget*"),
    ("0x14", "_pad_14", "uint8_t[0x4]"),
    ("0x18", "back_button", "FrontendWidget*"),
    ("0x1c", "speed_slider", "FrontendWidget*"),
    ("0x20", "difficulty_slider", "FrontendWidget*"),
    ("0x24", "replay_button", "FrontendWidget*"),
)

PROTO_UPDATES = (
    (
        "initialize_challenge_setup_screen",
        "void __thiscall initialize_challenge_setup_screen(cRGUI* gui)",
    ),
    (
        "destroy_challenge_setup_screen",
        "void __thiscall destroy_challenge_setup_screen(cRGUI* gui)",
    ),
    (
        "update_challenge_setup_screen",
        "int32_t __thiscall update_challenge_setup_screen(cRGUI* gui)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRGUI ownership lane."
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

    operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=OWNER_TYPE_RENAMES,
    )
    observed_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_STRUCT_SIZES,
    )
    type_equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=args.target,
        header_path=header_path,
    )
    mismatched_structs = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            observed_widths.get(name) != expected_size
            or not type_equivalence.get(name, False)
        )
    )
    if mismatched_structs:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_structs,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_structs
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRGUI owner layout already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend(
        [
            type_operation,
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("cRGUI", GUI_FIELD_UPDATES),
                    (
                        "cRSubGame",
                        (
                            ("0x125ffe0", "gui", "cRGUI"),
                            ("0x1260008", "help", "Help"),
                        ),
                    ),
                ),
                proto_updates=PROTO_UPDATES,
            ),
            *reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=REANALYSIS_FUNCTIONS,
            ),
        ]
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
