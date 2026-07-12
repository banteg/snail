#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_pool_types.h"
TARGET = "active"

REQUIRED_HEADER_STRUCTS = (
    "TrackSpeedupRuntime",
    "Vapour",
    "JetPack",
    "TrackHealthPickup",
    "SlugHazardRuntime",
    "RingOrSpecialEffectParticle",
    "RingOrSpecialEffectParent",
    "RingOrSpecialEffectPool",
)

SUBGAME_FIELD_UPDATES = (
    ("0x355db0", "speedup_pickup", "TrackSpeedupRuntime"),
    ("0x355e64", "jetpack_pickup", "JetPack"),
    ("0x356000", "health_pickups", "TrackHealthPickup[0x8]"),
    ("0x3563a0", "slug_hazards", "SlugHazardRuntime[0x8]"),
    ("0x35b78c", "ring_effects", "RingOrSpecialEffectPool"),
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
)

RING_RATE_SOURCE_FIELD_UPDATES = (
    ("0x09", "pause_gate", "uint8_t"),
)

RING_PARENT_FIELD_UPDATES = (
    ("0x10", "bod_position", "Vec3"),
    ("0x1c", "render_arg_1c", "int32_t"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "Color4f"),
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
        "emit_ring_star_shower",
        "void __thiscall emit_ring_star_shower(RingOrSpecialEffectParticle* particle, Player* owner)",
    ),
    (
        "update_ring_or_special_effect_particle",
        "void __thiscall update_ring_or_special_effect_particle(RingOrSpecialEffectParticle* particle)",
    ),
)


def main() -> int:
    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
            required_structs=REQUIRED_HEADER_STRUCTS,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="SubgameRuntime",
            updates=SUBGAME_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="TrackSpeedupRuntime",
            updates=TRACK_SPEEDUP_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="Vapour",
            updates=VAPOUR_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="JetPack",
            updates=JETPACK_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="TrackHealthPickup",
            updates=TRACK_HEALTH_PICKUP_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="SlugHazardRuntime",
            updates=SLUG_HAZARD_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="RingEffectRateSource",
            updates=RING_RATE_SOURCE_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="RingOrSpecialEffectParent",
            updates=RING_PARENT_FIELD_UPDATES,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
