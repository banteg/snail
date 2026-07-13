#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    emit_summary,
    struct_exists,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_pool_types.h"

REQUIRED_HEADER_STRUCTS = (
    "TrackSpeedupRuntime",
    "Vapour",
    "JetPack",
    "TrackHealthPickup",
    "SlugHazardRuntime",
    "SlugPool",
    "SubRingStar",
    "SubRing",
    "SubRingPool",
)

RING_TYPE_REPLACEMENTS = (
    "SubRingStar",
    "RingOrSpecialEffectParticle",
    "SubRing",
    "RingOrSpecialEffectParent",
    "SubRingPool",
    "RingOrSpecialEffectPool",
)

SUBGAME_FIELD_UPDATES = (
    ("0x355db0", "speedup_pickup", "TrackSpeedupRuntime"),
    ("0x355e64", "jetpack_pickup", "JetPack"),
    ("0x356000", "health_pickups", "TrackHealthPickup[0x8]"),
    ("0x3563a0", "slug_hazards", "SlugPool"),
    ("0x35b78c", "ring_effects", "SubRingPool"),
)

TRACK_SPEEDUP_FIELD_UPDATES = (
    ("0x10", "bod_position", "Vec3"),
    ("0x1c", "render_arg_1c", "int32_t"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "Color4f"),
    ("0x8c", "owner_game", "SubgameRuntime*"),
)

VAPOUR_FIELD_UPDATES = (
    ("0x24", "owner", "Object*"),
    ("0x80", "point_count", "int32_t"),
    ("0x84", "capacity", "int32_t"),
    ("0x88", "half_width", "float"),
    ("0x8c", "z_floor", "float*"),
    ("0x90", "points", "TransformMatrix*"),
)

JETPACK_FIELD_UPDATES = (
    ("0x44", "owner_game", "SubgameRuntime*"),
    ("0x74", "vapour_a", "Vapour"),
    ("0x108", "vapour_b", "Vapour"),
)

TRACK_HEALTH_PICKUP_FIELD_UPDATES = (
    ("0x44", "owner_game", "SubgameRuntime*"),
)

SLUG_HAZARD_FIELD_UPDATES = (
    ("0x88", "owner_game", "SubgameRuntime*"),
    ("0x98", "attachment_facing_angle", "float"),
    ("0x9c", "unknown_9c", "uint8_t[0x10]"),
)

PROTO_UPDATES = (
    ("reset_subgame", "void __thiscall reset_subgame(SubgameRuntime* game)"),
    (
        "initialize_track_health_pickup_runtime",
        "TrackHealthPickup* __thiscall initialize_track_health_pickup_runtime(TrackHealthPickup* pickup)",
    ),
    ("update_track_health_pickup", "void __thiscall update_track_health_pickup(TrackHealthPickup* pickup)"),
    (
        "initialize_track_jetpack_pickup_runtime",
        "JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack)",
    ),
    (
        "update_track_jetpack_pickup",
        "void __thiscall update_track_jetpack_pickup(JetPack* jetpack)",
    ),
    (
        "initialize_vapour",
        "void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width)",
    ),
    ("reset_vapour", "void __thiscall reset_vapour(Vapour* vapour, float* z_floor)"),
    (
        "add_vapour_point",
        "void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point)",
    ),
    ("update_vapour", "void __thiscall update_vapour(Vapour* vapour)"),
    (
        "initialize_track_ring_or_special_effect_runtime",
        "SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing* ring)",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "void __thiscall spawn_track_ring_or_special_effect(SubgameRuntime* game, TrackRowCell* cell, int32_t requested_kind, Player* player, float ring_speed)",
    ),
    (
        "initialize_ring_or_special_effect_particles",
        "int32_t __thiscall initialize_ring_or_special_effect_particles(SubRing* ring, int32_t unused_lives_snapshot)",
    ),
    (
        "emit_ring_star_shower",
        "void __thiscall emit_ring_star_shower(SubRingStar* particle, Player* owner)",
    ),
    (
        "update_ring_or_special_effect_particle",
        "void __thiscall update_ring_or_special_effect_particle(SubRingStar* particle)",
    ),
    (
        "update_ring_or_special_effect_parent",
        "void __thiscall update_ring_or_special_effect_parent(SubRing* ring)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the canonical subgame pickup, hazard, and cRSubRing ownership slice."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    types_present = all(
        struct_exists(REPO_ROOT, target=args.target, struct_name=struct_name)
        for struct_name in REQUIRED_HEADER_STRUCTS
    )
    type_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical subgame pool structs already present",
            "header": str(header_path),
            "required_structs": REQUIRED_HEADER_STRUCTS,
        }
        if types_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=RING_TYPE_REPLACEMENTS,
        )
    )

    struct_updates = [
        ("SubgameRuntime", SUBGAME_FIELD_UPDATES),
        ("TrackSpeedupRuntime", TRACK_SPEEDUP_FIELD_UPDATES),
        ("Vapour", VAPOUR_FIELD_UPDATES),
        ("JetPack", JETPACK_FIELD_UPDATES),
        ("TrackHealthPickup", TRACK_HEALTH_PICKUP_FIELD_UPDATES),
        ("SlugHazardRuntime", SLUG_HAZARD_FIELD_UPDATES),
    ]
    if struct_exists(REPO_ROOT, target=args.target, struct_name="FrameSubgameRuntime"):
        struct_updates.insert(0, ("FrameSubgameRuntime", SUBGAME_FIELD_UPDATES))

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=struct_updates,
            proto_updates=PROTO_UPDATES,
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
