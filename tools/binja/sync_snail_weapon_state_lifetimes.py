#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_away_user_var_update,
    apply_split_user_var_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Weapon": 0x3DC,
    "Snail": 0x19B4,
}

EXPECTED_STRUCT_FIELDS = {
    "Weapon": {
        0x104: ("selected_state", "int32_t"),
    },
    "Snail": {
        0x064C: ("weapon_channels", "Weapon[3]"),
        0x11E0: ("jetpack_channel", "Weapon"),
    },
}

# VC6 spills `this` to the top local stack slot, copies the live receiver to
# ESI, then reuses the dead spill as channel 2's target state. Splitting only
# the prologue definition preserves the real, potentially uninitialized
# default arm while giving the residual slot its scalar lifetime.
SAVED_RECEIVER_DEFINITIONS = (
    ("0x445920", "mlil", "StackVariableSourceType", 524288, -4),
)

TARGET_CHANNEL_2_STATE_VAR = (
    "StackVariableSourceType",
    40,
    -4,
)

# The stack argument remains the movement selector until the dispatcher has
# consumed it. Native then reuses its low byte for three disjoint transition
# flags. Each flag has an initial write, optional clear, and SSA join; keep the
# three authored channel lifetimes independent just as the IDA stack aliases
# and Android control flow do.
CHANNEL_IMMEDIATE_SPLITS = (
    (
        (
            ("0x4459aa", "mlil_ssa", "StackVariableSourceType", 138, 4),
            ("0x4459d6", "mlil_ssa", "StackVariableSourceType", 182, 4),
            ("0x4459db", "mlil_ssa", "StackVariableSourceType", 187, 4),
        ),
        ("StackVariableSourceType", 138, 4),
        "channel_0_immediate",
    ),
    (
        (
            ("0x445a47", "mlil_ssa", "StackVariableSourceType", 295, 4),
            ("0x445a73", "mlil_ssa", "StackVariableSourceType", 339, 4),
            ("0x445a78", "mlil_ssa", "StackVariableSourceType", 344, 4),
        ),
        ("StackVariableSourceType", 295, 4),
        "channel_1_immediate",
    ),
    (
        (
            ("0x445aea", "mlil_ssa", "StackVariableSourceType", 458, 4),
            ("0x445b16", "mlil_ssa", "StackVariableSourceType", 502, 4),
            ("0x445b1b", "mlil_ssa", "StackVariableSourceType", 507, 4),
        ),
        ("StackVariableSourceType", 458, 4),
        "channel_2_immediate",
    ),
)

SNAIL_WEAPON_STATE_USER_VAR_UPDATES = (
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        11,
        67,
        "any_channel_changed",
        "uint8_t",
    ),
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        36,
        73,
        "target_channel_0_state",
        "int32_t",
    ),
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        38,
        71,
        "target_channel_1_state",
        "int32_t",
    ),
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        132,
        66,
        "channel_0_selected_state",
        "int32_t",
    ),
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        289,
        66,
        "channel_1_selected_state",
        "int32_t",
    ),
    (
        "set_snail_weapon",
        "RegisterVariableSourceType",
        446,
        66,
        "channel_2_selected_state",
        "int32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the three cRSnail weapon-channel state and transition-flag "
            "lifetimes without merging them into the receiver or selector."
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
        help="Header documenting the canonical Snail and Weapon owners.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
    for type_name, expected_width in EXPECTED_TYPE_WIDTHS.items():
        observed_width = widths[type_name]
        if observed_width != expected_width:
            mismatches.append(
                f"{type_name}: expected width {expected_width:#x}, "
                f"observed {observed_width!r}"
            )
    for struct_name, expected_fields in EXPECTED_STRUCT_FIELDS.items():
        observed_fields = layouts[struct_name]
        for offset, expected in expected_fields.items():
            observed = observed_fields.get(offset)
            if observed != expected:
                mismatches.append(
                    f"{struct_name}+{offset:#x}: expected {expected!r}, "
                    f"observed {observed!r}"
                )
    if mismatches:
        raise RuntimeError(
            "canonical Snail weapon-channel layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_snail_weapon_channel_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [verify_owner_layouts(args.target)]
    operations.extend(
        apply_split_away_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="set_snail_weapon",
            detached_definitions=SAVED_RECEIVER_DEFINITIONS,
            residual_var=TARGET_CHANNEL_2_STATE_VAR,
            variable_name="target_channel_2_state",
            variable_type="int32_t",
        )
    )
    for definitions, target_var, variable_name in CHANNEL_IMMEDIATE_SPLITS:
        operations.extend(
            apply_split_user_var_update(
                REPO_ROOT,
                target=args.target,
                identifier="set_snail_weapon",
                definitions=definitions,
                target_var=target_var,
                variable_name=variable_name,
                variable_type="uint8_t",
            )
        )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SNAIL_WEAPON_STATE_USER_VAR_UPDATES,
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
