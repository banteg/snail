#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_menu_types.h"

EXPECTED_STRUCT_SIZES = {
    "MainMenu": 0x18,
    "Options": 0x24,
    "Exit": 0x1C,
}

BOD_BASE_EXPECTED_SIZE = 0x38

GAME_ROOT_FIELD_UPDATES = (
    ("0x4f324", "main_menu", "MainMenu"),
    ("0x4f388", "options", "Options"),
    ("0x4f3ac", "exit_controller", "Exit"),
    ("0x4f3c8", "root_bod_4f3c8", "BodBase"),
)

MAIN_MENU_FIELD_UPDATES = (
    ("0x00", "new_game_widget", "FrontendWidget*"),
    ("0x04", "high_scores_widget", "FrontendWidget*"),
    ("0x08", "options_widget", "FrontendWidget*"),
    ("0x0c", "credits_widget", "FrontendWidget*"),
    ("0x14", "exit_widget", "FrontendWidget*"),
)

OPTIONS_FIELD_UPDATES = (
    ("0x00", "previous_frontend_state", "int32_t"),
    ("0x04", "active", "uint8_t"),
    ("0x10", "back_widget", "FrontendWidget*"),
    ("0x14", "fullscreen_widget", "FrontendWidget*"),
    ("0x18", "sound_volume_widget", "FrontendWidget*"),
    ("0x1c", "music_volume_widget", "FrontendWidget*"),
    ("0x20", "previous_sample_volume", "float"),
)

EXIT_FIELD_UPDATES = (
    ("0x00", "state", "int32_t"),
    ("0x08", "previous_frontend_state", "int32_t"),
    ("0x0c", "prompt_y", "float"),
    ("0x10", "prompt_title", "FrontendWidget*"),
    ("0x14", "yes_button", "FrontendWidget*"),
    ("0x18", "no_button", "FrontendWidget*"),
)

PROTO_UPDATES = (
    ("destroy_main_menu", "void __thiscall destroy_main_menu(MainMenu* menu)"),
    ("initialize_main_menu", "void __thiscall initialize_main_menu(MainMenu* menu)"),
    ("update_main_menu", "void __thiscall update_main_menu(MainMenu* menu)"),
    (
        "initialize_options_menu",
        "void __thiscall initialize_options_menu(Options* options)",
    ),
    (
        "destroy_options_menu",
        "void __thiscall destroy_options_menu(Options* options)",
    ),
    ("update_options_menu", "void __thiscall update_options_menu(Options* options)"),
    (
        "apply_audio_config_volumes",
        "void __thiscall apply_audio_config_volumes(Options* options)",
    ),
    (
        "destroy_completion_screen",
        "void __thiscall destroy_completion_screen(Exit* exit_controller)",
    ),
    (
        "initialize_exit_prompt",
        "void __thiscall initialize_exit_prompt(Exit* exit_controller)",
    ),
    (
        "update_completion_screen",
        "void __thiscall update_completion_screen(Exit* exit_controller)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the contiguous cRMainMenu/cROptions/cRExit ownership slice."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
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

    observed_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=(*EXPECTED_STRUCT_SIZES, "BodBase"),
    )
    if observed_widths.get("BodBase") != BOD_BASE_EXPECTED_SIZE:
        raise RuntimeError(
            "refusing root BOD replay: "
            f"BodBase width is {observed_widths.get('BodBase')!r}, "
            f"expected {BOD_BASE_EXPECTED_SIZE:#x}"
        )
    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if observed_widths.get(name) != expected_size
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["expected_sizes"] = {
            name: EXPECTED_STRUCT_SIZES[name] for name in mismatched_types
        }
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "front-end menu owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
        }

    struct_updates = (
        ("MainMenu", MAIN_MENU_FIELD_UPDATES),
        ("Options", OPTIONS_FIELD_UPDATES),
        ("Exit", EXIT_FIELD_UPDATES),
        ("GameRoot", GAME_ROOT_FIELD_UPDATES),
    )
    operations: list[dict[str, object]] = [
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=struct_updates,
            proto_updates=PROTO_UPDATES,
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
