#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_away_user_var_update,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "ObjectAnimation": 0x14,
    "Object": 0xDC,
    "RenderableBod": 0x80,
    "PresentationAnimationSlot": 0x80,
    "AnimManager": 0x48,
}

EXPECTED_STRUCT_FIELDS = {
    "Object": {
        0xBC: ("animation", "ObjectAnimation*"),
    },
    "PresentationAnimationSlot": {
        0x00: ("body", "RenderableBod"),
    },
    "AnimManager": {
        0x00: ("state", "int32_t"),
        0x04: ("progress", "float"),
        0x08: ("progress_step", "float"),
        0x0C: ("active_animation", "ObjectAnimation*"),
        0x10: ("completed", "uint8_t"),
        0x14: ("queued_animations", "int32_t[10]"),
        0x3C: ("queue_count", "int32_t"),
        0x40: ("target_model", "RenderableBod*"),
        0x44: ("animation_slots", "PresentationAnimationSlot*"),
    },
}

# VC6 spills `this` to the top local stack slot for the zero-state return,
# then reuses the dead slot for the computed progress. Split only the prologue
# definition away before typing the residual float lifetime.
SAVED_MANAGER_DEFINITIONS = (
    ("0x4447d0", "mlil", "StackVariableSourceType", 524288, -4),
)

NEXT_PROGRESS_VAR = (
    "StackVariableSourceType",
    58,
    -4,
)

# EAX walks one queued animation id at a time during compaction. ESI borrows
# the Object* field inside the selected inline PresentationAnimationSlot.
ANIM_MANAGER_QUEUE_USER_VAR_UPDATES = (
    (
        "update_anim_manager",
        "RegisterVariableSourceType",
        289,
        66,
        "queue_cursor",
        "int32_t*",
    ),
    (
        "update_anim_manager",
        "RegisterVariableSourceType",
        333,
        72,
        "slot_object",
        "Object**",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the animation-manager progress, queue, and slot-link "
            "lifetimes."
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
        help="Header documenting the canonical AnimManager owner.",
    )
    return parser.parse_args()


def verify_anim_manager_queue_owner_layout(target: str) -> dict[str, object]:
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
            "canonical animation-manager queue ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_anim_manager_queue_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [verify_anim_manager_queue_owner_layout(args.target)]
    operations.extend(
        apply_split_away_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_anim_manager",
            detached_definitions=SAVED_MANAGER_DEFINITIONS,
            residual_var=NEXT_PROGRESS_VAR,
            variable_name="next_progress",
            variable_type="float",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=ANIM_MANAGER_QUEUE_USER_VAR_UPDATES,
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
