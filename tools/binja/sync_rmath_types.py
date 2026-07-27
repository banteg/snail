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
DEFAULT_HEADER_PATH = REPO_ROOT / "tools/match/include/rmath_random.h"

FUNCTION_SYMBOL_UPDATES = (
    ("0x44c8d0", "initialize_math_random_table"),
    ("0x44c930", "initialize_trigonometry_tables"),
    ("0x44dc70", "random_signed_float_below"),
    ("0x44dc90", "random_float_below"),
)

# The mobile mangled names preserve both the float return and the otherwise
# unused source-tag parameter: RAND(float, char*) and SRAND(float, char*).
PROTO_UPDATES = (
    (
        "initialize_math_random_table",
        "void __cdecl initialize_math_random_table()",
    ),
    (
        "initialize_trigonometry_tables",
        "void __cdecl initialize_trigonometry_tables()",
    ),
    (
        "random_signed_float_below",
        "float __cdecl random_signed_float_below(float upper_bound, char* tag)",
    ),
    (
        "random_float_below",
        "float __cdecl random_float_below(float upper_bound, char* tag)",
    ),
)

# Prototype changes need their already-materialized caller HLIL refreshed so
# the native source-tag pushes become named second arguments.
RNG_CALLERS = (
    "game_startup_and_main_loop",
    "select_level_track_texture_set",
    "switch_track_mirror",
    "populate_runtime_track_cells_from_segments",
    "build_subgame_level",
    "update_subgame",
    "update_sub_loc",
    "spawn_track_garbage_hazard",
    "spawn_track_ring_or_special_effect",
    "update_garbage_hazard",
    "update_slug_hazard_ai",
    "firework_shoot",
    "release_snail_weapons",
    "place_parcels_on_track",
    "place_challenge_parcels_on_track",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the mobile-proven Windows RMath contracts."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if not DEFAULT_HEADER_PATH.is_file():
        raise FileNotFoundError(
            f"canonical RMath matcher header not found: {DEFAULT_HEADER_PATH}"
        )

    operations: list[dict[str, object]] = [
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        ),
        *reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=RNG_CALLERS,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=DEFAULT_HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
