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
    remove_user_var_updates,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0xC,
    "tColour": 0x10,
    "JetParticleSlot": 0x10,
    "SubHover": 0x214,
    "RenderableBod": 0x80,
    "Weapon": 0x3DC,
    "Snail": 0x19B4,
    "Player": 0x4364,
    "Sprite": 0xB4,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "JetParticleSlot": {
        0x00: ("sprite", "Sprite*"),
        0x04: ("wobble_x", "float"),
        0x08: ("wobble_y", "float"),
        0x0C: ("wobble_alpha", "float"),
    },
    "SubHover": {
        0x0C: ("state", "SubHoverState"),
        0x10: ("player", "Player*"),
        0x20: ("particle_slots", "JetParticleSlot[30]"),
        0x200: ("game", "SubgameRuntime*"),
        0x210: ("warning_intensity", "float"),
    },
    "RenderableBod": {
        0x38: ("transform", "TransformMatrix"),
    },
    "Weapon": {
        0x108: ("anim_manager", "AnimManager"),
        0x150: ("animation_slots", "PresentationAnimationSlot[5]"),
    },
    "Snail": {
        0x00: ("body", "RenderableBod"),
        0x11E0: ("jetpack_channel", "Weapon"),
        0x17B0: ("snail_hotspots_world", "Vec3[19]"),
    },
    "Player": {
        0x380: ("player_slot", "int32_t"),
        0x410: ("velocity", "Vec3"),
        0x2750: ("sub_hover", "SubHover"),
        0x2984: ("presentation", "Snail"),
    },
    "Sprite": {
        0x04: ("flags", "SpriteFlag"),
        0x2C: ("color", "tColour"),
        0x48: ("position", "Vec3"),
        0x54: ("velocity", "Vec3"),
        0x60: ("size_start", "float"),
        0x64: ("size_end", "float"),
        0x68: ("progress", "float"),
        0x6C: ("progress_step", "float"),
        0x70: ("lifetime", "float"),
        0x74: ("lifetime_step", "float"),
        0x78: ("gravity_step", "float"),
    },
    "SubgameRuntime": {
        0x3BB764: ("player", "Player"),
    },
}

# JetInit and JetUnInit flatten the owned 15-by-2 bank into one borrowed slot
# cursor. Jets retains separate row and nozzle-column lifetimes while borrowing
# the two authored nozzle positions, the Player forward basis, each inline slot,
# and an occasional detached Sprite whose lifetime transfers to SpriteManager.
JET_PARTICLE_BANK_USER_VAR_UPDATES = (
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        7,
        72,
        "particle_slot_cursor",
        "JetParticleSlot*",
    ),
    (
        "initialize_jet_particles",
        "StackVariableSourceType",
        10,
        -20,
        "rows_remaining",
        "int32_t",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        30,
        69,
        "columns_remaining",
        "int32_t",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        46,
        66,
        "particle_sprite",
        "Sprite*",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        118,
        66,
        "particle_velocity",
        "Vec3*",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        134,
        66,
        "initial_color",
        "tColour*",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        143,
        67,
        "particle_color",
        "tColour*",
    ),
    (
        "initialize_jet_particles",
        "RegisterVariableSourceType",
        173,
        67,
        "current_particle_sprite",
        "Sprite*",
    ),
    (
        "uninit_jet_particles",
        "RegisterVariableSourceType",
        3,
        72,
        "particle_slot_cursor",
        "JetParticleSlot*",
    ),
    (
        "uninit_jet_particles",
        "RegisterVariableSourceType",
        6,
        69,
        "rows_remaining",
        "int32_t",
    ),
    (
        "uninit_jet_particles",
        "RegisterVariableSourceType",
        16,
        73,
        "columns_remaining",
        "int32_t",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        74,
        -60,
        "random_back_seed",
        "float",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        87,
        72,
        "trail_index",
        "int32_t",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        93,
        -80,
        "trail_index_latch",
        "int32_t",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        109,
        -64,
        "random_width_seed",
        "float",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        123,
        67,
        "nozzle_index",
        "int32_t",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        125,
        -76,
        "nozzle_index_latch",
        "int32_t",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        135,
        -72,
        "trail_fraction",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        159,
        -68,
        "particle_size",
        "float",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        173,
        66,
        "left_nozzle_position",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        206,
        68,
        "right_nozzle_position",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        247,
        66,
        "player_forward_basis",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        180,
        -52,
        "nozzle_position_x",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        187,
        -48,
        "nozzle_position_y",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        194,
        -44,
        "nozzle_position_z",
        "float",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        295,
        66,
        "particle_slot",
        "JetParticleSlot*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        337,
        66,
        "particle_position",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        297,
        -52,
        "particle_position_x",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        321,
        -48,
        "particle_position_y",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        350,
        -44,
        "particle_position_z",
        "float",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        429,
        66,
        "trail_puff",
        "Sprite*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        487,
        66,
        "white_color",
        "tColour*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        538,
        66,
        "player_velocity",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        557,
        -40,
        "trail_velocity_x",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        574,
        -36,
        "trail_velocity_y",
        "float",
    ),
    (
        "update_jet_particles",
        "StackVariableSourceType",
        602,
        -32,
        "trail_velocity_z",
        "float",
    ),
)

# An early live probe typed these two interior Sprite pointers as standalone
# Vec3 owners. That obscures the enclosing Sprite::gravity_step access, so the
# durable replay explicitly retires those annotations if it encounters them.
STALE_JET_PARTICLE_USER_VARS = (
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        543,
        67,
        "trail_velocity",
        "Vec3*",
    ),
    (
        "update_jet_particles",
        "RegisterVariableSourceType",
        546,
        72,
        "trail_position",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the owned SubHover jet-particle bank and borrowed update "
            "lifetimes across JetInit, Jets, and JetUnInit."
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
        help="Header documenting the canonical SubHover and Sprite owners.",
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
            "canonical jet-particle ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_jet_particle_bank_owner_layouts",
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
        *remove_user_var_updates(
            REPO_ROOT,
            target=args.target,
            removals=STALE_JET_PARTICLE_USER_VARS,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=JET_PARTICLE_BANK_USER_VAR_UPDATES,
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
