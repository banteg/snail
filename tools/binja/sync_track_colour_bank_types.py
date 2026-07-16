#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/track_colour_bank_types.h"

EXPECTED_STRUCT_SIZES = {
    "tColour": 0x10,
    "TrackFloorSlideColourBanks": 0x660,
}

FUNCTION_SYMBOL_UPDATES = (
    ("0x434980", "initialize_track_colour_bank_a_thunk"),
    ("0x434990", "initialize_track_colour_bank_a"),
    ("0x4349b0", "initialize_track_colour_banks_b_c_thunk"),
    ("0x4349c0", "initialize_track_colour_banks_b_c"),
    ("0x4349e0", "initialize_track_colour_bank_d_thunk"),
    ("0x4349f0", "initialize_track_colour_bank_d"),
    ("0x434a10", "initialize_track_colour_bank_e_thunk"),
    ("0x434a20", "initialize_track_colour_bank_e"),
    ("0x434a40", "initialize_track_colour_bank_f_thunk"),
    ("0x434a50", "initialize_track_colour_bank_f"),
    ("0x434a70", "initialize_track_colour_bank_g_thunk"),
    ("0x434a80", "initialize_track_colour_bank_g"),
    ("0x434aa0", "initialize_track_colour_bank_h_thunk"),
    ("0x434ab0", "initialize_track_colour_bank_h"),
    ("0x434ad0", "initialize_track_colour_bank_i_thunk"),
    ("0x434ae0", "initialize_track_colour_bank_i"),
    ("0x434b00", "initialize_track_colour_bank_j_thunk"),
    ("0x434b10", "initialize_track_colour_bank_j"),
    ("0x434b30", "initialize_track_colour_bank_k_thunk"),
    ("0x434b40", "initialize_track_colour_bank_k"),
    ("0x435d40", "build_track_colours"),
)

PROTO_UPDATES = tuple(
    (name, f"void __cdecl {name}()")
    for _address, name in FUNCTION_SYMBOL_UPDATES
    if name != "build_track_colours"
) + (
    (
        "build_track_colours",
        "void __thiscall build_track_colours(SubgameRuntime* game)",
    ),
)

DATA_SYMBOL_UPDATES = (
    ("0x53c800", "g_loc_colour_lookup_path_worm"),
    ("0x53cb30", "g_loc_colour_lookup_slide_1"),
    ("0x53ce60", "g_loc_colour_lookup_wall"),
    ("0x643198", "g_loc_colour_lookup_path_warp"),
    ("0x6434c8", "g_loc_colour_lookup_trampoline"),
    ("0x6437f8", "g_loc_colour_lookup_floor_slide_0"),
    ("0x643b28", "g_loc_colour_lookup_slide_0"),
    ("0x643e58", "g_loc_colour_lookup_path"),
    ("0x644188", "g_loc_colour_lookup_empty"),
    ("0x6444b8", "g_loc_colour_lookup_ramp"),
    ("0x74e7e8", "g_loc_colour_lookup_check_black"),
)

# Keep the isolated banks narrow in Binary Ninja. A full PathWarp array would
# overlap the independently named parcel count-lane sentinel at 0x643390. The
# Floor/Slide-0 allocation has no competing owner, so applying its complete
# struct is safe and materializes the proved 0x660-byte relationship.
DATA_VAR_UPDATES = (
    ("0x53c800", "tColour"),
    ("0x53cb30", "tColour"),
    ("0x53ce60", "tColour"),
    ("0x643198", "tColour"),
    ("0x6434c8", "tColour"),
    ("0x6437f8", "TrackFloorSlideColourBanks"),
    ("0x643e58", "tColour"),
    ("0x644188", "tColour"),
    ("0x6444b8", "tColour"),
    ("0x74e7e8", "tColour"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the recovered track-colour bank ownership."
    )
    parser.add_argument(
        "--target", default=DEFAULT_TARGET, help="Binary Ninja target selector."
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Shared track-colour ownership header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"track-colour type header not found: {header_path}")

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
            "reason": "track-colour owner sizes already current",
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
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(),
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
