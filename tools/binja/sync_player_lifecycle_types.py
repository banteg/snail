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
    current_type_widths,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"
OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"
SPRITE_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"
RUNTIME_CONFIG_HEADER_PATH = REPO_ROOT / "analysis/headers/runtime_config_types.h"

EXPECTED_OWNER_SIZES = {
    "ObjectAnimation": 0x14,
    "Object": 0xDC,
    "Sprite": 0xB4,
    "RuntimeConfig": 0xC4,
    "RenderableBod": 0x80,
    "AnimManager": 0x48,
    "SubHealth": 0x74,
    "SubHover": 0x214,
    "GolbShot": 0x2E8,
    "GolbShotFlightStrideCursor": 0x2E8,
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "Snail": 0x19B4,
    "Player": 0x4364,
    "SubgameRuntime": 0x1272838,
}

SYMBOL_UPDATES = (
    ("0x43a010", "health_collect_particles"),
    ("0x43a300", "update_movement_flag_emitters"),
    ("0x43a370", "end_jetpack_hover"),
    ("0x43a9c0", "initialize_subgoldy"),
    ("0x43af10", "show_subgoldy_lives"),
    ("0x43af60", "begin_post_follow_carryover"),
    ("0x43afd0", "play_movement_state_sound"),
    ("0x43d230", "initialize_subgoldy_ghost"),
    ("0x43d3d0", "set_subgoldy_ghost_z"),
)

PROTO_UPDATES = (
    (
        "health_collect_particles",
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup)",
    ),
    (
        "update_movement_flag_emitters",
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source)",
    ),
    (
        "end_jetpack_hover",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover)",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
    ),
    (
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player)",
    ),
    (
        "begin_post_follow_carryover",
        "void __thiscall begin_post_follow_carryover(Player* player)",
    ),
    (
        "play_movement_state_sound",
        "void __thiscall play_movement_state_sound(Player* player)",
    ),
    (
        "initialize_subgoldy_ghost",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner)",
    ),
    (
        "set_subgoldy_ghost_z",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z)",
    ),
)

# Exact EDI lifetime for the 12-element loop rooted at
# Player::golb_shots[0].flight_transform. This is a borrowed field-stride view;
# Player.golb_shots remains the sole owning array.
USER_VAR_UPDATES = (
    (
        "update_movement_flag_emitters",
        "RegisterVariableSourceType",
        49,
        73,
        "golb_shot_cursor",
        "GolbShot*",
    ),
    (
        "initialize_subgoldy",
        "RegisterVariableSourceType",
        1171,
        73,
        "golb_shot_flight_cursor",
        "GolbShotFlightStrideCursor*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the focused Player lifecycle and effects ownership ABIs."
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Canonical Player owner type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Player owner type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=OBJECT_HEADER_PATH,
            required_structs=("Object",),
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=SPRITE_HEADER_PATH,
            required_structs=("Sprite",),
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=RUNTIME_CONFIG_HEADER_PATH,
            required_structs=("RuntimeConfig",),
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=EXPECTED_OWNER_SIZES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=USER_VAR_UPDATES,
        ),
    ]

    observed_sizes = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_OWNER_SIZES,
    )
    mismatches = []
    for name, expected_size in EXPECTED_OWNER_SIZES.items():
        observed_size = observed_sizes.get(name)
        status = "verified" if observed_size == expected_size else "verification_failed"
        operations.append(
            {
                "op": "owner_size_verify",
                "name": name,
                "expected_size": expected_size,
                "observed_size": observed_size,
                "status": status,
            }
        )
        if status == "verification_failed":
            mismatches.append(
                f"{name}: expected {expected_size:#x}, observed {observed_size!r}"
            )

    if mismatches:
        raise RuntimeError("Player lifecycle owner size mismatch: " + "; ".join(mismatches))

    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
