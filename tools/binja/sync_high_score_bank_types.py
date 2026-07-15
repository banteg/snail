#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import apply_proto_updates, apply_symbol_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_high_score_bank_types.h"

PROTO_UPDATES = (
    (
        "initialize_high_score_tables",
        "void __thiscall initialize_high_score_tables(SubHighScore* bank)",
    ),
    (
        "load_high_scores_from_file",
        "void __thiscall load_high_scores_from_file(SubHighScore* bank, char* file_name)",
    ),
    (
        "initialize_high_score_entry",
        "void __thiscall initialize_high_score_entry(SubSolution* record, int32_t runtime_build_seed, int32_t replay_level_index, int32_t replay_speed_scalar_bits, uint32_t runtime_build_flags, int32_t high_score_mode_tag, int32_t route_or_rank_index)",
    ),
    (
        "add_arcade_high_score",
        "void __thiscall add_arcade_high_score(SubHighScore* bank, SubSolution* record, int32_t level_arg)",
    ),
    (
        "add_survival_high_score",
        "void __thiscall add_survival_high_score(SubHighScore* bank, SubSolution* record)",
    ),
    (
        "add_time_trial_high_score",
        "void __thiscall add_time_trial_high_score(SubHighScore* bank, SubSolution* record, int32_t route_index, uint8_t route_active)",
    ),
    (
        "mini_delete_high_score_entry",
        "void __thiscall mini_delete_high_score_entry(SubHighScore* bank, int32_t rank)",
    ),
    (
        "save_high_scores_and_config",
        "void __thiscall save_high_scores_and_config(SubHighScore* bank, uint8_t save_mask)",
    ),
)

SYMBOL_UPDATES = (
    ("0x417af0", "mini_delete_high_score_entry"),
    ("0x4df904", "g_game_base"),
    ("0x4df9c0", "g_high_score_selected_bank"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow high-score bank type/prototype/name slice to a Binary Ninja target."
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
        help="Path to the narrow Binary Ninja type-import header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = [types_declare(REPO_ROOT, target=args.target, header_path=header_path)]
    operations.extend(apply_symbol_updates(REPO_ROOT, target=args.target, updates=SYMBOL_UPDATES))
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
