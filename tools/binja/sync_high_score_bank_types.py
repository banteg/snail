#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_symbol_updates,
    apply_user_var_updates,
    emit_summary,
    types_declare,
)


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
    (
        "deserialize_compact_high_score_record",
        "uint8_t __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
    ),
    (
        "serialize_compact_high_score_record",
        "int32_t __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
    ),
)

SYMBOL_UPDATES = (
    ("0x417af0", "mini_delete_high_score_entry"),
    ("0x4df904", "g_game_base"),
    ("0x4df9c0", "g_high_score_selected_bank"),
)

PERSISTENCE_USER_VAR_UPDATES = (
    (
        "load_high_scores_from_file",
        "RegisterVariableSourceType",
        39,
        72,
        "compact",
        "CompactHighScoreRecord*",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        210,
        67,
        "source_lateral",
        "int16_t*",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        220,
        68,
        "lateral_run",
        "ReplayRunRecord*",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        250,
        68,
        "source_delta_z",
        "int16_t*",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        259,
        67,
        "delta_z_destination",
        "int16_t*",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        285,
        66,
        "flag_index",
        "int32_t",
    ),
    (
        "deserialize_compact_high_score_record",
        "RegisterVariableSourceType",
        300,
        67,
        "flag_destination",
        "uint16_t*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        199,
        68,
        "out_lateral",
        "int16_t*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        209,
        67,
        "lateral_run",
        "ReplayRunRecord*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        239,
        68,
        "out_delta_z",
        "int16_t*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        248,
        67,
        "delta_z_source",
        "int16_t*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        278,
        73,
        "out_flags",
        "uint8_t*",
    ),
    (
        "serialize_compact_high_score_record",
        "RegisterVariableSourceType",
        287,
        72,
        "flag_source",
        "uint16_t*",
    ),
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
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=PERSISTENCE_USER_VAR_UPDATES,
        )
    )
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
