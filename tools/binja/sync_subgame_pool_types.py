#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_user_var_updates,
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_pool_types.h"

REQUIRED_HEADER_STRUCTS = (
    "SubSpeedUp",
    "Vapour",
    "JetPack",
    "SubHealth",
    "Slug",
    "SlugPool",
    "SubRingStar",
    "SubRing",
    "SubRingPool",
)

REQUIRED_POOL_TYPES = (
    "TrackPickupState",
    "SubRingState",
    "SubRingKind",
)

TYPE_REPLACEMENTS = (
    "Slug",
    "SlugPool",
    "SubRingState",
    "SubRingKind",
    "SubRingStar",
    "RingOrSpecialEffectParticle",
    "SubRing",
    "RingOrSpecialEffectParent",
    "SubRingPool",
    "RingOrSpecialEffectPool",
)

SLUG_ALLOCATOR_CURSOR_TYPES = (
    "SlugStateStrideCursor",
    "SlugSlotCursor",
)

SUBGAME_FIELD_UPDATES = (
    ("0x355db0", "speedup_pickup", "SubSpeedUp"),
    ("0x355e64", "jetpack_pickup", "JetPack"),
    ("0x356000", "health_pickups", "SubHealth[0x8]"),
    ("0x3563a0", "slug_hazards", "SlugPool"),
    ("0x35b78c", "ring_effects", "SubRingPool"),
)

SUB_SPEEDUP_FIELD_UPDATES = (
    ("0x10", "bod_position", "Vec3"),
    ("0x1c", "render_arg_1c", "float"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "tColour"),
    ("0x80", "state", "TrackPickupState"),
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
    ("0x38", "state", "TrackPickupState"),
    ("0x44", "owner_game", "SubgameRuntime*"),
    ("0x74", "vapour_a", "Vapour"),
    ("0x108", "vapour_b", "Vapour"),
)

SUB_HEALTH_FIELD_UPDATES = (
    ("0x38", "state", "TrackPickupState"),
    ("0x44", "owner_game", "SubgameRuntime*"),
)

SLUG_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "state", "int32_t"),
    ("0x84", "death_toss_direction", "int32_t"),
    ("0x88", "owner_game", "SubgameRuntime*"),
    ("0x98", "attachment_facing_angle", "float"),
    ("0x9c", "unknown_9c", "uint8_t[0x10]"),
    ("0xac", "sprite", "Sprite*"),
    ("0xb0", "source_cell", "TrackRowCell*"),
    ("0xc0", "owner_player", "Player*"),
)

SUB_RING_FIELD_UPDATES = (
    ("0x80", "state", "SubRingState"),
    ("0x88", "kind", "SubRingKind"),
)

PROTO_UPDATES = (
    ("reset_subgame", "void __thiscall reset_subgame(SubgameRuntime* game)"),
    (
        "initialize_track_speedup_runtime",
        "SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup)",
    ),
    ("update_track_speedup", "void __thiscall update_track_speedup(SubSpeedUp* speedup)"),
    (
        "initialize_slug_hazard_runtime",
        "Slug* __thiscall initialize_slug_hazard_runtime(Slug* slug)",
    ),
    (
        "spawn_slug_hazard",
        "int32_t __thiscall spawn_slug_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* owner_player)",
    ),
    (
        "update_slug_voice_ai",
        "void __thiscall update_slug_voice_ai(Slug* slug)",
    ),
    (
        "play_slug_voice",
        "void __thiscall play_slug_voice(Slug* slug, int32_t sample_index)",
    ),
    (
        "hit_slug_hazard",
        "void __thiscall hit_slug_hazard(Slug* slug, int32_t damage)",
    ),
    (
        "explode_slug_hazard",
        "void __thiscall explode_slug_hazard(Slug* slug)",
    ),
    (
        "kill_slug_hazard",
        "void __thiscall kill_slug_hazard(Slug* slug)",
    ),
    # The slot constructor installs this exact function as Slug's member AI
    # callback; the one-ECX ABI is therefore authored thiscall, not a free
    # fastcall helper.
    (
        "update_slug_hazard_ai",
        "void __thiscall update_slug_hazard_ai(Slug* slug)",
    ),
    (
        "initialize_track_health_pickup_runtime",
        "SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup)",
    ),
    ("update_track_health_pickup", "void __thiscall update_track_health_pickup(SubHealth* pickup)"),
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

# spawn_slug_hazard uses two distinct borrowed cursor shapes. ECX physically
# points at Slug::state and advances by the full slot stride; ESI remains a
# SubgameRuntime-relative biased base for the selected slot. Preserve those
# exact lifetimes instead of pretending either cursor is a direct Slug owner.
SPAWN_SLUG_HAZARD_USER_VAR_UPDATES = (
    (
        "spawn_slug_hazard",
        "RegisterVariableSourceType",
        8,
        67,
        "slug_state_cursor",
        "SlugStateStrideCursor*",
    ),
    (
        "spawn_slug_hazard",
        "RegisterVariableSourceType",
        60,
        72,
        "slug_slot_cursor",
        "SlugSlotCursor*",
    ),
    (
        "spawn_slug_hazard",
        "RegisterVariableSourceType",
        589,
        66,
        "blink_random_value",
        "int32_t",
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

    type_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=(
            *REQUIRED_HEADER_STRUCTS,
            *REQUIRED_POOL_TYPES,
            *SLUG_ALLOCATOR_CURSOR_TYPES,
            "FrameSubgameRuntime",
        ),
    )
    types_present = all(
        (type_widths.get(struct_name) or 0) > 0
        for struct_name in REQUIRED_HEADER_STRUCTS
    )
    pool_types_present = all(
        type_widths.get(type_name) == 4 for type_name in REQUIRED_POOL_TYPES
    )
    type_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "canonical subgame pool structs already present",
            "header": str(header_path),
            "required_structs": REQUIRED_HEADER_STRUCTS,
            "required_types": REQUIRED_POOL_TYPES,
        }
        if types_present and pool_types_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=TYPE_REPLACEMENTS,
        )
    )
    cursor_types_present = all(
        (type_widths.get(struct_name) or 0) > 0
        for struct_name in SLUG_ALLOCATOR_CURSOR_TYPES
    )
    cursor_type_operation = (
        {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "slug allocator cursor views already present",
            "header": str(header_path),
            "required_structs": SLUG_ALLOCATOR_CURSOR_TYPES,
        }
        if cursor_types_present
        else types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=SLUG_ALLOCATOR_CURSOR_TYPES,
            include_types=SLUG_ALLOCATOR_CURSOR_TYPES,
        )
    )

    struct_updates = [
        ("SubgameRuntime", SUBGAME_FIELD_UPDATES),
        ("SubSpeedUp", SUB_SPEEDUP_FIELD_UPDATES),
        ("Vapour", VAPOUR_FIELD_UPDATES),
        ("JetPack", JETPACK_FIELD_UPDATES),
        ("SubHealth", SUB_HEALTH_FIELD_UPDATES),
        ("Slug", SLUG_FIELD_UPDATES),
        ("SubRing", SUB_RING_FIELD_UPDATES),
    ]
    if (type_widths.get("FrameSubgameRuntime") or 0) > 0:
        struct_updates.insert(0, ("FrameSubgameRuntime", SUBGAME_FIELD_UPDATES))

    operations: list[dict[str, object]] = [
        type_operation,
        cursor_type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=struct_updates,
            proto_updates=PROTO_UPDATES,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SPAWN_SLUG_HAZARD_USER_VAR_UPDATES,
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
