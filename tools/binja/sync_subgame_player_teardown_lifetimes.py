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
    "Snail": {
        0x00: ("body", "RenderableBod"),
        0x064C: ("weapon_channels", "Weapon[3]"),
        0x11E0: ("jetpack_channel", "Weapon"),
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

# Player owns the complete body, cRSnail presentation, and its animation
# channels. The root BodList only borrows each inherited zero-offset BodNode.
# Preserve the four independent inline unlink/free-stack operations without
# claiming that the list owns any backing Player, Snail, or Weapon storage.
SUBGAME_PLAYER_TEARDOWN_USER_VAR_UPDATES = (
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1002,
        66,
        "player_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1014,
        67,
        "player_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1059,
        66,
        "player_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1072,
        66,
        "player_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1093,
        68,
        "player_free_top",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1102,
        66,
        "player_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1123,
        68,
        "snail_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1129,
        67,
        "snail_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1172,
        67,
        "snail_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1179,
        73,
        "snail_list_prev_for_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1185,
        67,
        "snail_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1215,
        67,
        "snail_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1230,
        67,
        "jetpack_channel_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1242,
        68,
        "jetpack_channel_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1288,
        67,
        "jetpack_channel_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1295,
        73,
        "jetpack_channel_list_prev_for_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1301,
        67,
        "jetpack_channel_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1331,
        67,
        "jetpack_channel_flags_after_clear",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1346,
        67,
        "weapon_channel_0_list_flags",
        "uint32_t",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1358,
        68,
        "weapon_channel_0_active_list",
        "BodList*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1404,
        67,
        "weapon_channel_0_list_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1411,
        73,
        "weapon_channel_0_list_prev_for_next",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1417,
        67,
        "weapon_channel_0_list_prev",
        "BodNode*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1447,
        67,
        "weapon_channel_0_flags_after_clear",
        "uint32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the Player, Snail, and animation-channel intrusive-"
            "list lifetimes in remove_subgame_bods."
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
        help="Header documenting the canonical Player and list owners.",
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
            "canonical subgame Player-teardown ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_subgame_player_teardown_owner_layouts",
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
            updates=SUBGAME_PLAYER_TEARDOWN_USER_VAR_UPDATES,
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
