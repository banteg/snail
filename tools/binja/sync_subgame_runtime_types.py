#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    emit_summary,
    struct_exists,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_runtime_types.h"
DEFAULT_CONTACT_HEADER_PATH = REPO_ROOT / "analysis/headers/contact_target_types.h"

SUBGAME_FIELD_UPDATES = (
    ("0x359080", "banners", "BannerPool"),
    ("0x3bb700", "blink_random_index", "int32_t"),
    ("0x3bb704", "blink_random_samples", "float[24]"),
    ("0xff25e0", "time_trial", "TimeTrial"),
    ("0x125ffd8", "garbage_frequency", "float"),
    ("0x125ffdc", "salt_frequency", "float"),
    ("0x125ffe0", "gui", "GUI"),
    ("0x1270fd4", "enemy_manager", "EnemyManager"),
)

# These richer nested types are supplied by later ownership slices. Preserve
# them when present instead of letting the intentionally sparse bootstrap
# header flatten their ranges back into byte arrays.
SUBGAME_BOD_FIELD_UPDATES = (
    ("0x355bd4", "sub_lazer_list_head", "BodBase"),
    ("0x355c0c", "salt_hazard_list_head", "BodBase"),
)

SUBGAME_PLAYER_FIELD_UPDATES = (
    ("0x3bb764", "player", "Player"),
)

PROTO_UPDATES = (
    (
        "zero_timer_counters",
        "void __thiscall zero_timer_counters(Time* time)",
    ),
    (
        "advance_timer_counters",
        "void __thiscall advance_timer_counters(Time* time, float delta_ticks)",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner)",
    ),
    (
        "initialize_enemy_manager",
        "void __thiscall initialize_enemy_manager(EnemyManager* manager)",
    ),
    (
        "search_path_for_golb",
        "ContactTargetEntry* __thiscall search_path_for_golb(EnemyManager* manager, const Vec3* position)",
    ),
    (
        "append_subgame_contact_target",
        "void __thiscall append_subgame_contact_target(EnemyManager* manager, const Vec3* position, float radius, int32_t kind, ContactTargetObject* object)",
    ),
    ("set_subgame_features", "int32_t __thiscall set_subgame_features(SubgameRuntime* runtime)"),
    ("switch_track_mirror", "bool __thiscall switch_track_mirror(SubgameRuntime* runtime)"),
    (
        "rebuild_track_runtime_from_segments",
        "int32_t __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* runtime, int32_t level_index)",
    ),
    ("set_subgame_rate", "void __thiscall set_subgame_rate(SubgameRuntime* runtime, float rate)"),
    ("calc_subgame_rate", "void __thiscall calc_subgame_rate(SubgameRuntime* runtime)"),
    ("advance_blink_random", "double __thiscall advance_blink_random(SubgameRuntime* runtime)"),
    ("initialize_blink_random", "int32_t __thiscall initialize_blink_random(SubgameRuntime* runtime)"),
    ("complete_subgame", "void __thiscall complete_subgame(SubgameRuntime* runtime, uint8_t completed)"),
    (
        "initialize_challenge_setup_screen",
        "int32_t __thiscall initialize_challenge_setup_screen(GUI* gui)",
    ),
    (
        "destroy_challenge_setup_screen",
        "void __thiscall destroy_challenge_setup_screen(GUI* gui)",
    ),
    (
        "update_challenge_setup_screen",
        "int32_t __thiscall update_challenge_setup_screen(GUI* gui)",
    ),
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(TimeTrial* time_trial, Time* timer)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow subgame runtime prototype slice to the active Binary Ninja target."
    )
    parser.add_argument(
        "--target",
        default="active",
        help="Binary Ninja target selector. Defaults to the active target.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Path to the narrow Binary Ninja type-import header.",
    )
    parser.add_argument(
        "--contact-header",
        type=Path,
        default=DEFAULT_CONTACT_HEADER_PATH,
        help="Path to the shared contact-target type-import header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    contact_header_path = args.contact_header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")
    if not contact_header_path.is_file():
        raise FileNotFoundError(f"contact-target type header not found: {contact_header_path}")

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=contact_header_path,
            required_structs=(
                "ContactTargetObject",
                "ContactTargetEntry",
                "EnemyManager",
            ),
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=(
                "SubgameRuntime",
                "TimeTrial",
                "GUI",
                "Banner",
                "BannerPool",
            ),
        ),
        *apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SubgameRuntime",
            updates=SUBGAME_FIELD_UPDATES,
        ),
    ]
    if struct_exists(REPO_ROOT, target=args.target, struct_name="BodBase"):
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="SubgameRuntime",
                updates=SUBGAME_BOD_FIELD_UPDATES,
            )
        )
    if struct_exists(REPO_ROOT, target=args.target, struct_name="Player"):
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="SubgameRuntime",
                updates=SUBGAME_PLAYER_FIELD_UPDATES,
            )
        )
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
