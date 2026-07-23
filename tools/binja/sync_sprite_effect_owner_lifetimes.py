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
    "Vec3": 0x0C,
    "tColour": 0x10,
    "Sprite": 0xB4,
    "GolbShot": 0x2E8,
    "Player": 0x4364,
    "SubGarbage": 0xC4,
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
    "Sprite": {
        0x00: ("object_ref", "void*"),
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
    "GolbShot": {
        0x24C: ("velocity", "Vec3"),
        0x270: ("game", "SubgameRuntime*"),
        0x274: ("object_ref", "void*"),
        0x278: ("owner_player", "Player*"),
    },
    "Player": {
        0x380: ("player_slot", "int32_t"),
    },
    "SubGarbage": {
        0x8C: ("owner_game", "SubgameRuntime*"),
    },
    "SubgameRuntime": {
        0x38: ("subgame_rate", "float"),
    },
}

# These four helpers allocate and fill the same Sprite owner shape. The two
# smoke emitters advance a derived register to Sprite::position, then reuse that
# cursor for both the position/velocity vectors and gravity_step at +0x30.
# Binary Ninja infers the derived lifetime too narrowly as Vec3*. Keeping it as
# an honest byte cursor lets the enclosing Sprite owner recover all fields
# without inventing a synthetic motion-tail object.
#
# A SpriteMotionTail overlay is intentionally omitted: transactional preview
# replaced __offset with position.x:0x30 and position.x.12.x expressions, which
# hid the real enclosing Sprite ownership instead of clarifying it.
SPRITE_EFFECT_OWNER_USER_VAR_UPDATES = (
    (
        "spawn_golb_trail_sprite",
        "RegisterVariableSourceType",
        28,
        66,
        "trail_sprite",
        "Sprite*",
    ),
    (
        "spawn_golb_smoke",
        "RegisterVariableSourceType",
        34,
        66,
        "smoke_sprite",
        "Sprite*",
    ),
    (
        "spawn_golb_smoke",
        "RegisterVariableSourceType",
        184,
        72,
        "sprite_motion_cursor",
        "uint8_t*",
    ),
    (
        "spawn_golb_impact_sprite",
        "RegisterVariableSourceType",
        41,
        66,
        "impact_sprite",
        "Sprite*",
    ),
    (
        "spawn_garbage_smoke_particle",
        "RegisterVariableSourceType",
        42,
        66,
        "smoke_sprite",
        "Sprite*",
    ),
    (
        "spawn_garbage_smoke_particle",
        "RegisterVariableSourceType",
        184,
        72,
        "sprite_motion_cursor",
        "uint8_t*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved Sprite owner and smoke-motion cursor lifetimes "
            "across the Golb and garbage effect emitters."
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
        help="Header documenting the canonical Sprite and emitter owners.",
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
            "canonical Sprite effect ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_sprite_effect_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Sprite ownership header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SPRITE_EFFECT_OWNER_USER_VAR_UPDATES,
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
