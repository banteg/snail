#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "BodNode": 0x10,
    "BodList": 0x0C,
    "BodBase": 0x38,
    "RenderableBod": 0x80,
    "SubSpeedUp": 0xB4,
    "JetPack": 0x19C,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
        0x08: ("list_prev", "BodNode*"),
        0x0C: ("list_next", "BodNode*"),
    },
    "BodList": {
        0x04: ("first", "BodNode*"),
        0x08: ("free_top", "BodNode*"),
    },
    "BodBase": {
        0x00: ("bod", "BodNode"),
    },
    "RenderableBod": {
        0x00: ("bod", "BodBase"),
    },
    "SubSpeedUp": {
        0x00: ("body", "RenderableBod"),
        0x80: ("state", "TrackPickupState"),
    },
    "JetPack": {
        0x00: ("bod", "BodBase"),
        0x38: ("state", "TrackPickupState"),
    },
    "SubgameRuntime": {
        0x355DB0: ("speedup_pickup", "SubSpeedUp"),
        0x355E64: ("jetpack_pickup", "JetPack"),
    },
    "GameRoot": {
        0x05A8: ("active_bod_list", "BodList"),
    },
}

# The pickup records remain embedded in SubgameRuntime. These two blocks only
# borrow their inherited BodNode links, remove that membership from the root
# active list, and push the same node onto the root free stack before clearing
# the pickup state. Preserve the two independent list-operation lifetimes; do
# not invent a shared owner or force the analyzer's partial-register display.
SUBGAME_PICKUP_TEARDOWN_USER_VAR_UPDATES = (
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        336,
        68,
        "speedup_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        342,
        67,
        "speedup_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        385,
        67,
        "speedup_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        392,
        72,
        "speedup_list_prev_for_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        398,
        67,
        "speedup_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        428,
        67,
        "speedup_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        460,
        67,
        "jetpack_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        472,
        68,
        "jetpack_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        518,
        67,
        "jetpack_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        525,
        72,
        "jetpack_list_prev_for_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        531,
        67,
        "jetpack_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        561,
        67,
        "jetpack_flags_after_clear",
        "uint32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the embedded speedup and JetPack intrusive-list "
            "lifetimes in remove_subgame_bods."
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
        help="Header documenting the canonical pickup and list owners.",
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
            "canonical subgame pickup-teardown ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_subgame_pickup_teardown_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SUBGAME_PICKUP_TEARDOWN_USER_VAR_UPDATES,
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
