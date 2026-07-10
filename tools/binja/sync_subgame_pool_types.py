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
PICKUP_OWNER_GAME_VIEW_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_track_pickup_owner_game_view.h"
TARGET = "active"

REQUIRED_HEADER_STRUCTS = (
    "TrackSpeedupRuntime",
    "TrackJetpackPickup",
    "TrackHealthPickup",
    "SlugHazardRuntime",
    "RingOrSpecialEffectParticle",
    "RingOrSpecialEffectParent",
    "RingOrSpecialEffectPool",
)

GAME_FIELD_UPDATES = (
    ("0x355db0", "speedup_pickup", "TrackSpeedupRuntime"),
    ("0x355e64", "jetpack_pickup", "TrackJetpackPickup"),
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
    ("0x8c", "owner_game", "TrackPickupOwnerGameView*"),
)

TRACK_JETPACK_PICKUP_FIELD_UPDATES = (
    ("0x44", "owner_game", "TrackPickupOwnerGameView*"),
)

TRACK_HEALTH_PICKUP_FIELD_UPDATES = (
    ("0x44", "owner_game", "TrackPickupOwnerGameView*"),
)

SLUG_HAZARD_FIELD_UPDATES = (
    ("0x88", "owner_game", "Game*"),
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
    ("reset_subgame", "void __thiscall reset_subgame(Game* game)"),
    (
        "initialize_track_health_pickup_runtime",
        "TrackHealthPickup* __thiscall initialize_track_health_pickup_runtime(TrackHealthPickup* pickup)",
    ),
    ("update_track_health_pickup", "void __thiscall update_track_health_pickup(TrackHealthPickup* pickup)"),
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
            header_path=PICKUP_OWNER_GAME_VIEW_HEADER_PATH,
            required_structs=("TrackPickupOwnerGameView",),
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
            required_structs=REQUIRED_HEADER_STRUCTS,
        ),
        *apply_struct_field_updates(REPO_ROOT, target=TARGET, struct_name="Game", updates=GAME_FIELD_UPDATES),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="TrackSpeedupRuntime",
            updates=TRACK_SPEEDUP_FIELD_UPDATES,
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=TARGET,
            struct_name="TrackJetpackPickup",
            updates=TRACK_JETPACK_PICKUP_FIELD_UPDATES,
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
