#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_split_user_var_update,
    apply_struct_field_updates,
    emit_summary,
    reanalyze_functions,
    types_declare,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_high_score_screen_types.h"
FRONTEND_WIDGET_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_widget_types.h"
TARGET = DEFAULT_TARGET

GAME_ROOT_FIELD_UPDATES = (
    ("0x12e6e50", "high_score", "HighScore"),
)

PROTO_UPDATES = (
    (
        "initialize_high_score_screen",
        "void __thiscall initialize_high_score_screen(HighScore* high_score, int32_t selected_bank, int32_t selected_rank)",
    ),
    (
        "destroy_high_score_screen",
        "void __thiscall destroy_high_score_screen(HighScore* high_score)",
    ),
    (
        "update_high_score_screen",
        "void __thiscall update_high_score_screen(HighScore* high_score)",
    ),
    (
        "exit_high_score_screen",
        "void __thiscall exit_high_score_screen(HighScore* high_score)",
    ),
)

HIGH_SCORE_LIFECYCLE_REANALYSIS_FUNCTIONS = (
    "destroy_high_score_screen",
    "update_high_score_screen",
    "exit_high_score_screen",
)

HIGH_SCORE_REPLAY_CURSOR_DEFINITIONS = (
    ("0x417466", "mlil", "StackVariableSourceType", 518, -4),
    ("0x41746f", "mlil_ssa", "StackVariableSourceType", 527, -4),
    ("0x417523", "mlil", "StackVariableSourceType", 707, -4),
)

HIGH_SCORE_REPLAY_CURSOR_VAR = (
    "StackVariableSourceType",
    518,
    -4,
)


def main() -> int:
    operations = [
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=FRONTEND_WIDGET_HEADER_PATH,
            required_structs=("FrontendWidget",),
        ),
        types_declare(REPO_ROOT, target=TARGET, header_path=HEADER_PATH),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="GameRoot",
            updates=GAME_ROOT_FIELD_UPDATES,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
        *apply_split_user_var_update(
            REPO_ROOT,
            target=TARGET,
            identifier="update_high_score_screen",
            definitions=HIGH_SCORE_REPLAY_CURSOR_DEFINITIONS,
            target_var=HIGH_SCORE_REPLAY_CURSOR_VAR,
            variable_name="replay_widget_cursor",
            variable_type="FrontendWidget**",
        ),
        *reanalyze_functions(
            REPO_ROOT,
            target=TARGET,
            identifiers=HIGH_SCORE_LIFECYCLE_REANALYSIS_FUNCTIONS,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
