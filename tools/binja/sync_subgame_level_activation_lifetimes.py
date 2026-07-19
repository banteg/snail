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
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "Snail": 0x19B4,
    "Player": 0x4364,
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
    "Weapon": {
        0x00: ("body", "RenderableBod"),
    },
    "Invincible": {
        0x00: ("body", "RenderableBod"),
    },
    "Snail": {
        0x00: ("body", "RenderableBod"),
        0x064C: ("weapon_channels", "Weapon[3]"),
        0x11E0: ("jetpack_channel", "Weapon"),
        0x1894: ("invincible_shell", "Invincible"),
    },
    "Player": {
        0x0000: ("body", "RenderableBod"),
        0x2984: ("presentation", "Snail"),
    },
    "SubgameRuntime": {
        0x3BB764: ("player", "Player"),
    },
    "GameRoot": {
        0x05A8: ("active_bod_list", "BodList"),
    },
}

# build_subgame_level reactivates the Player and five embedded presentation
# actors by splicing their inherited zero-offset BodNodes into the root active
# list. The list only borrows those nodes; Player/Snail retain storage
# ownership. The jetpack block is already fully named by the broad replay, so
# this narrow pass covers only the remaining visible list-node lifetimes and
# leaves analyzer-folded SSA intermediates untouched.
SUBGAME_LEVEL_ACTIVATION_USER_VAR_UPDATES = (
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1402,
        68,
        "active_first_weapon_0",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1423,
        68,
        "active_first_link_weapon_0",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1438,
        68,
        "active_new_first_weapon_0",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1490,
        68,
        "active_first_weapon_1",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1511,
        68,
        "active_first_link_weapon_1",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1526,
        68,
        "active_new_first_weapon_1",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1578,
        68,
        "active_first_weapon_2",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1599,
        68,
        "active_first_link_weapon_2",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1614,
        68,
        "active_new_first_weapon_2",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1666,
        68,
        "active_first_invincible_shell",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1687,
        68,
        "active_first_link_invincible_shell",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1702,
        68,
        "active_new_first_invincible_shell",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1769,
        68,
        "active_first_presentation",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1790,
        68,
        "active_first_link_presentation",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1805,
        68,
        "active_new_first_presentation",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1846,
        67,
        "active_first_player",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1867,
        67,
        "active_first_link_player",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1875,
        67,
        "active_first_reload_player",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1877,
        67,
        "active_new_first_player_reloaded",
        "BodNode*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the remaining Player/Snail active-list insertion "
            "lifetimes in build_subgame_level."
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
        help="Header documenting the canonical Player and active-list owners.",
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
            "canonical subgame-level activation ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_subgame_level_activation_owner_layouts",
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
            updates=SUBGAME_LEVEL_ACTIVATION_USER_VAR_UPDATES,
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
