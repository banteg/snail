#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_struct_size,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/click_start_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRClickStart": 0xAC,
}

PLAYER_EXPECTED_SIZE = 0x4364

OWNER_TYPE_RENAMES = (("ClickStart", "cRClickStart"),)

REANALYSIS_FUNCTIONS = (
    "initialize_click_start_controller_runtime",
    "initialize_subgoldy",
    "initialize_click_start",
    "update_click_start",
)

CLICK_START_FIELD_UPDATES = (
    ("0x00", "bod", "RenderableBod"),
    ("0x80", "state", "ClickStartState"),
    ("0x84", "prompt", "FrontendWidget*"),
    ("0x88", "teardown_progress", "float"),
    ("0x8c", "teardown_progress_step", "float"),
    ("0x90", "_pad_90", "uint8_t[0x8]"),
    ("0x98", "owner_player", "Player*"),
    ("0x9c", "_pad_9c", "uint8_t[0xc]"),
    ("0xa8", "hide_prompt", "uint8_t"),
    ("0xa9", "_pad_a9", "uint8_t[0x3]"),
)

PLAYER_BOUNDARY_UPDATES = (
    ("0x9c", "ghost_sprite_b", "Sprite*"),
    ("0xa0", "click_start", "cRClickStart"),
    ("0x14c", "row_event_cutscene_started", "uint8_t"),
    ("0x150", "nuke", "cRNuke"),
)

PROTO_UPDATES = (
    (
        "initialize_click_start_controller_runtime",
        "cRClickStart* __thiscall initialize_click_start_controller_runtime(cRClickStart* click_start)",
    ),
    (
        "initialize_click_start",
        "void __thiscall initialize_click_start(cRClickStart* click_start, Player* player)",
    ),
    (
        "update_click_start",
        "void __thiscall update_click_start(cRClickStart* click_start)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRClickStart ownership lane."
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

    player_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="Player",
    )
    if player_size != PLAYER_EXPECTED_SIZE:
        raise RuntimeError(
            "refusing cRClickStart replay with Player-size mismatch: "
            f"expected {PLAYER_EXPECTED_SIZE:#x}, observed {player_size!r}"
        )

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
            "reason": "cRClickStart owner layout already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend(
        [
            {
                "op": "owner_size_verify",
                "status": "verified",
                "owner_sizes": {"Player": player_size},
            },
            type_operation,
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("cRClickStart", CLICK_START_FIELD_UPDATES),
                    ("Player", PLAYER_BOUNDARY_UPDATES),
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
