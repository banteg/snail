#!/usr/bin/env python3

from __future__ import annotations

import sys
from pathlib import Path

from _narrow_sync import (
    apply_proto_updates,
    apply_split_user_var_update,
    apply_struct_field_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_if_missing,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_high_score_screen_types.h"
FRONTEND_WIDGET_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frontend_widget_types.h"
TARGET = DEFAULT_TARGET

GAME_ROOT_FIELD_UPDATES = (
    ("0x12e6e50", "high_score", "cRHighScore"),
)

EXPECTED_STRUCT_SIZES = {"cRHighScore": 0xF4}

TYPE_RENAMES = (("HighScore", "cRHighScore"),)

HIGH_SCORE_INIT_PROTO_UPDATE = (
    "initialize_high_score_screen",
    "void __thiscall initialize_high_score_screen(cRHighScore* high_score, int32_t selected_bank, int32_t selected_rank)",
)

PROTO_UPDATES = (
    HIGH_SCORE_INIT_PROTO_UPDATE,
    (
        "destroy_high_score_screen",
        "void __thiscall destroy_high_score_screen(cRHighScore* high_score)",
    ),
    (
        "update_high_score_screen",
        "void __thiscall update_high_score_screen(cRHighScore* high_score)",
    ),
    (
        "exit_high_score_screen",
        "void __thiscall exit_high_score_screen(cRHighScore* high_score)",
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
    frontend_widget_operation = types_declare_if_missing(
        REPO_ROOT,
        target=TARGET,
        header_path=FRONTEND_WIDGET_HEADER_PATH,
        required_structs=("FrontendWidget",),
    )
    type_rename_operations = apply_type_renames(
        REPO_ROOT,
        target=TARGET,
        renames=TYPE_RENAMES,
    )
    observed_widths = current_type_widths(
        REPO_ROOT,
        target=TARGET,
        type_names=EXPECTED_STRUCT_SIZES,
    )
    type_equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
    )
    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            observed_widths.get(name) != expected_size
            or not type_equivalence.get(name, False)
        )
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
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
            "reason": "cRHighScore owner layout already current",
            "header": str(HEADER_PATH),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": type_equivalence,
        }

    operations = [
        frontend_widget_operation,
        *type_rename_operations,
        type_operation,
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
