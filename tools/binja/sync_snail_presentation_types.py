#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_symbol_updates,
    current_type_widths,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"
OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"
SPRITE_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"

EXPECTED_OWNER_SIZES = {
    "ObjectAnimation": 0x14,
    "Object": 0xDC,
    "Sprite": 0xB4,
    "RenderableBod": 0x80,
    "AnimManager": 0x48,
    "SubHover": 0x214,
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "Snail": 0x19B4,
    "Player": 0x4364,
}

SYMBOL_UPDATES = (
    ("0x43a390", "update_jetpack_gauge"),
    ("0x43a580", "uninit_jet_particles"),
    ("0x43a5b0", "initialize_jet_particles"),
    ("0x43a690", "update_jet_particles"),
    ("0x43a930", "initialize_jetpack_gauge"),
    ("0x43a980", "arm_jetpack_gauge"),
    ("0x442e40", "release_snail_weapons"),
    ("0x444600", "dispatch_cutscene_animation"),
    ("0x4446e0", "set_weapon_animation"),
    ("0x444ac0", "initialize_invincible_shell"),
    ("0x444ae0", "start_invincible_shell"),
    ("0x444b50", "update_invincible_shell"),
    ("0x445cd0", "update_snail_skin"),
    ("0x445d50", "build_snail_hotspots"),
)

PROTO_UPDATES = (
    (
        "update_jetpack_gauge",
        "void __thiscall update_jetpack_gauge(SubHover* sub_hover)",
    ),
    (
        "uninit_jet_particles",
        "void __thiscall uninit_jet_particles(SubHover* sub_hover)",
    ),
    (
        "initialize_jet_particles",
        "void __thiscall initialize_jet_particles(SubHover* sub_hover)",
    ),
    (
        "update_jet_particles",
        "void __thiscall update_jet_particles(SubHover* sub_hover)",
    ),
    (
        "initialize_jetpack_gauge",
        "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot)",
    ),
    (
        "arm_jetpack_gauge",
        "void __thiscall arm_jetpack_gauge(SubHover* sub_hover)",
    ),
    (
        "release_snail_weapons",
        "void __thiscall release_snail_weapons(Snail* snail)",
    ),
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(Invincible* invincible)",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(Invincible* invincible)",
    ),
    (
        "update_invincible_shell",
        "void __thiscall update_invincible_shell(Invincible* invincible)",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(Snail* snail)",
    ),
    (
        "build_snail_hotspots",
        "void __thiscall build_snail_hotspots(Snail* snail)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the focused cRSnail presentation and cRWeapon animation "
            "ownership ABIs to a Binary Ninja target."
        )
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
        help="Canonical owner type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Owner type header not found: {header_path}")

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
        raise RuntimeError("Snail presentation owner size mismatch: " + "; ".join(mismatches))

    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
