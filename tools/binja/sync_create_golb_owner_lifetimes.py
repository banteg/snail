#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_user_var_update,
    apply_struct_field_updates,
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "tColour": 0x10,
    "BodNode": 0x10,
    "BodBase": 0x38,
    "Sprite": 0xB4,
    "ContactTargetObject": 0x08,
    "ContactTargetEntry": 0x18,
    "Snail": 0x19B4,
    "GolbShot": 0x2E8,
    "Player": 0x4364,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
        0x08: ("list_prev", "BodNode*"),
        0x0C: ("list_next", "BodNode*"),
    },
    "BodBase": {
        0x00: ("bod", "BodNode"),
    },
    "Sprite": {
        0x04: ("flags", "SpriteFlag"),
        0x2C: ("color", "tColour"),
        0x48: ("position", "Vec3"),
        0x60: ("size_start", "float"),
        0x64: ("size_end", "float"),
        0x68: ("progress", "float"),
        0x6C: ("progress_step", "float"),
        0x78: ("gravity_step", "float"),
        0x7C: ("facing_angle", "float"),
        0x80: ("facing_angle_step", "float"),
    },
    "ContactTargetObject": {
        0x04: ("list_flags", "int32_t"),
    },
    "ContactTargetEntry": {
        0x00: ("kind", "int32_t"),
        0x04: ("position", "Vec3"),
        0x14: ("object", "ContactTargetObject*"),
    },
    "Snail": {
        0x17B0: ("snail_hotspots_world", "Vec3[19]"),
    },
    "GolbShot": {
        0x0198: ("homing_target_object", "ContactTargetObject*"),
        0x019C: ("homing_target", "Vec3"),
        0x0248: ("render_sprite", "Sprite*"),
        0x024C: ("velocity", "Vec3"),
        0x0270: ("game", "SubgameRuntime*"),
        0x0278: ("owner_player", "Player*"),
    },
    "Player": {
        0x0000: ("body", "RenderableBod"),
        0x0338: ("shoot_flags", "uint32_t"),
        0x0380: ("player_slot", "int32_t"),
        0x0384: ("follow_state", "cRPathFollowGoldy"),
        0x0410: ("velocity", "Vec3"),
        0x2984: ("presentation", "Snail"),
    },
    "SubgameRuntime": {
        0x0038: ("subgame_rate", "float"),
        0x355D24: ("golb_vapour_list_head", "BodBase"),
        0x1270FD4: ("enemy_manager", "EnemyManager"),
    },
}

GOLB_SHOT_RENDER_SPRITE_FIELD = (
    ("0x248", "render_sprite", "Sprite*"),
)

# These are complete borrowed owners already proved independently by the
# Player/Snail layout, the intrusive vapour sentinel, and the shared Sprite
# emitter family. The velocity lifetime is one source local reused in two
# mutually exclusive movement branches; the spawn anchor selects one element
# from the owned 19-entry Snail hotspot array.
CREATE_GOLB_USER_VAR_UPDATES = (
    (
        "create_golb",
        "RegisterVariableSourceType",
        406,
        66,
        "shot_velocity",
        "Vec3*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        904,
        68,
        "spawn_anchor",
        "Vec3*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1714,
        66,
        "vapour_list_head",
        "BodBase*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1900,
        66,
        "render_sprite",
        "Sprite*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1987,
        67,
        "render_color",
        "tColour*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        2043,
        66,
        "render_position",
        "Vec3*",
    ),
)

# Binary Ninja merges three unrelated EAX definitions across the kind
# dispatch: the kind-minus-one scalar, shot->game in the Sprite branch, and
# search_path_for_golb's ContactTargetEntry* result. Split only the two proved
# pointer definitions. The integer residual remains automatic.
CREATE_GOLB_SPRITE_GAME_DEFINITIONS = (
    ("0x415aae", "mlil", "RegisterVariableSourceType", 2094, 66),
)
CREATE_GOLB_SPRITE_GAME_VAR = (
    "RegisterVariableSourceType",
    2094,
    66,
)

CREATE_GOLB_TARGET_ENTRY_DEFINITIONS = (
    ("0x4158ad", "mlil", "RegisterVariableSourceType", 1581, 66),
)
CREATE_GOLB_TARGET_ENTRY_VAR = (
    "RegisterVariableSourceType",
    1581,
    66,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay create_golb's hotspot, velocity, presentation, vapour, "
            "subgame-rate, and contact-target owner lifetimes."
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
        help="Header documenting the canonical Golb creation owners.",
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
            "canonical Golb creation ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_create_golb_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Golb ownership header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GolbShot",
            updates=GOLB_SHOT_RENDER_SPRITE_FIELD,
        )
    )
    operations.append(verify_owner_layouts(args.target))
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=CREATE_GOLB_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="create_golb",
            definitions=CREATE_GOLB_SPRITE_GAME_DEFINITIONS,
            target_var=CREATE_GOLB_SPRITE_GAME_VAR,
            variable_name="sprite_game",
            variable_type="SubgameRuntime*",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="create_golb",
            definitions=CREATE_GOLB_TARGET_ENTRY_DEFINITIONS,
            target_var=CREATE_GOLB_TARGET_ENTRY_VAR,
            variable_name="target_entry",
            variable_type="ContactTargetEntry*",
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
