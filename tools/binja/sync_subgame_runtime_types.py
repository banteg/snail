#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_symbol_updates,
    apply_struct_and_proto_updates,
    current_struct_size,
    emit_summary,
    struct_exists,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_runtime_types.h"
DEFAULT_CONTACT_HEADER_PATH = REPO_ROOT / "analysis/headers/contact_target_types.h"
DEFAULT_OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"

GALAXY_POINT_FIELD_UPDATES = (
    ("0x00", "x", "float"),
    ("0x04", "y", "float"),
)

GALAXY_ROUTE_RECORD_FIELD_UPDATES = (
    ("0x00", "route_name_index", "int32_t"),
    ("0x08", "map_x", "float"),
    ("0x0c", "map_y", "float"),
    ("0x10", "map_z", "float"),
    ("0x14", "route_tint_alpha", "float"),
    ("0x18", "highlight_target", "float"),
    ("0x1c", "detail_text", "char[0x80]"),
    ("0x9c", "description_text", "char[0x200]"),
)

GALAXY_ROUTE_SLOT_FIELD_UPDATES = (
    ("0x00", "unknown_000", "int32_t"),
    ("0x04", "record", "GalaxyRouteRecord"),
)

GALAXY_ROUTE_NAME_FIELD_UPDATES = (
    ("0x00", "name", "char[0x80]"),
    ("0x80", "star_count", "int32_t"),
    ("0x84", "color", "tColour"),
    ("0x94", "map_x", "float"),
    ("0x98", "map_y", "float"),
    ("0x9c", "map_z", "float"),
)

GALAXY_FIELD_UPDATES = (
    ("0x00", "active", "uint8_t"),
    ("0x04", "route_mode", "int32_t"),
    ("0x08", "route_state", "int32_t"),
    ("0x0c", "record_count", "int32_t"),
    ("0x10", "route_slots", "GalaxyRouteSlot[101]"),
    ("0x10930", "route_names", "GalaxyRouteNameRecord[10]"),
    ("0x10f70", "level_progress_base", "SubgameRuntime*"),
    ("0x10f74", "exit_or_back_widget", "FrontendWidget*"),
    ("0x10f78", "route_title_widget", "FrontendWidget*"),
    ("0x10f7c", "route_icon_widget", "FrontendWidget*"),
    ("0x10f80", "selected_index", "int32_t"),
    ("0x10f84", "hover_state", "int32_t"),
    ("0x10f8c", "bounds_frame_widget", "FrontendWidget*"),
    ("0x10f90", "selected_title_widget", "FrontendWidget*"),
    ("0x10f94", "selected_detail_widget", "FrontendWidget*"),
    ("0x10f98", "selected_description_widget", "FrontendWidget*"),
    ("0x10f9c", "play_or_deliver_widget", "FrontendWidget*"),
    ("0x10fa0", "replay_widget", "FrontendWidget*"),
    ("0x10fa4", "unknown_10fa4", "int32_t"),
)

GALAXY_FUNCTION_SYMBOL_UPDATES = (
    ("0x408880", "initialize_galaxy_route_name_record"),
    ("0x409bd0", "update_galaxy_route_record"),
)

PARCEL_FUNCTION_SYMBOL_UPDATES = (
    ("0x408860", "initialize_track_parcel_runtime"),
    ("0x443130", "update_track_parcels"),
    ("0x443160", "initialize_track_parcel_slots"),
    ("0x443190", "allocate_track_parcel_slot"),
    ("0x4431d0", "update_track_parcel"),
    ("0x443730", "spawn_track_parcel"),
)

PARCEL_EXPECTED_SIZES = {
    "Parcel": 0x8C,
    "ParcelManager": 0x1B58,
}

GALAXY_DATA_SYMBOL_UPDATES = (
    ("0x4a1c4c", "g_galaxy_group_points"),
    ("0x4a1d14", "g_galaxy_route_points"),
)

GALAXY_DATA_VAR_UPDATES = (
    ("0x4a1c4c", "GalaxyPoint[10]"),
    ("0x4a1d14", "GalaxyPoint[101]"),
)

SUBGAME_FIELD_UPDATES = (
    ("0x00", "scan_reset", "uint8_t"),
    ("0x01", "camera_snap_requested", "uint8_t"),
    ("0x02", "track_mirror_enabled", "uint8_t"),
    ("0x04", "track_mirror_repeat_count", "int32_t"),
    ("0x08", "resume_requested", "uint8_t"),
    ("0x09", "subgame_pause_gate", "uint8_t"),
    ("0x0c", "pause_fade", "float"),
    ("0x10", "pause_fade_step", "float"),
    ("0x14", "sub_pause", "SubPause"),
    ("0x20", "runtime_row_scan_begin", "int32_t"),
    ("0x24", "runtime_row_scan_end", "int32_t"),
    ("0x355e64", "jetpack_pickup", "JetPack"),
    ("0x359080", "banners", "BannerPool"),
    ("0x3bb700", "blink_random_index", "int32_t"),
    ("0x3bb704", "blink_random_samples", "float[24]"),
    ("0xff25e0", "time_trial", "TimeTrial"),
    ("0x125e480", "parcel_manager", "ParcelManager"),
    ("0x125ffd8", "garbage_frequency", "float"),
    ("0x125ffdc", "salt_frequency", "float"),
    ("0x125ffe0", "gui", "GUI"),
    ("0x1260008", "help", "Help"),
    ("0x126000c", "thanks_screen", "ThanksScreen"),
    ("0x1260020", "galaxy", "Galaxy"),
    ("0x1270fc8", "subgame_rebuild_selector", "int32_t"),
    ("0x1270fcc", "next_slug_voice_trigger_z", "float"),
    ("0x1270fd0", "slug_voice_trigger_spacing_z", "float"),
    ("0x1270fd4", "enemy_manager", "EnemyManager"),
    ("0x12727d8", "completion", "Completion"),
    ("0x1272828", "times_up", "TimesUp"),
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

COMPLETION_FIELD_UPDATES = (
    ("0x14", "state", "CompletionState"),
    ("0x34", "widget_world", "Vec3"),
)

PARCEL_FIELD_UPDATES = (
    ("0x38", "state", "ParcelState"),
)

JETPACK_FIELD_UPDATES = (
    ("0x38", "state", "TrackPickupState"),
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "SubgameRuntime*"),
)

TIMES_UP_FIELD_UPDATES = (
    ("0x00", "state", "TimesUpState"),
)

GUI_FIELD_UPDATES = (
    ("0x00", "game", "SubgameRuntime*"),
    ("0x04", "next_level_button", "FrontendWidget*"),
    ("0x08", "previous_level_button", "FrontendWidget*"),
    ("0x0c", "level_name_widget", "FrontendWidget*"),
    ("0x10", "play_button", "FrontendWidget*"),
    ("0x18", "back_button", "FrontendWidget*"),
    ("0x1c", "speed_slider", "FrontendWidget*"),
    ("0x20", "difficulty_slider", "FrontendWidget*"),
    ("0x24", "replay_button", "FrontendWidget*"),
)

PROTO_UPDATES = (
    (
        "initialize_galaxy_route_name_record",
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(GalaxyRouteNameRecord* record)",
    ),
    (
        "load_galaxy_layout",
        "void __thiscall load_galaxy_layout(Galaxy* galaxy)",
    ),
    (
        "destroy_galaxy",
        "void __thiscall destroy_galaxy(Galaxy* galaxy)",
    ),
    (
        "initialize_galaxy",
        "void __thiscall initialize_galaxy(Galaxy* galaxy)",
    ),
    (
        "update_galaxy",
        "int32_t __thiscall update_galaxy(Galaxy* galaxy)",
    ),
    (
        "draw_galaxy_line",
        "int32_t __thiscall draw_galaxy_line(Galaxy* galaxy, int32_t texture_id, float x0, float y0, float x1, float y1, float width, tColour* color)",
    ),
    (
        "update_galaxy_route_record",
        "void __thiscall update_galaxy_route_record(GalaxyRouteSlot* slot)",
    ),
    (
        "close_galaxy_route",
        "void __thiscall close_galaxy_route(Galaxy* galaxy)",
    ),
    (
        "open_galaxy_route",
        "void __thiscall open_galaxy_route(Galaxy* galaxy, int32_t selected_level_index)",
    ),
    (
        "galaxy_border_bound",
        "void __thiscall galaxy_border_bound(Galaxy* galaxy, float* min_x, float* max_x, float* min_y, float* max_y, FrontendWidget* widget)",
    ),
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
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* runtime, int32_t level_index)",
    ),
    ("set_subgame_rate", "void __thiscall set_subgame_rate(SubgameRuntime* runtime, float rate)"),
    ("calc_subgame_rate", "void __thiscall calc_subgame_rate(SubgameRuntime* runtime)"),
    ("advance_blink_random", "double __thiscall advance_blink_random(SubgameRuntime* runtime)"),
    ("initialize_blink_random", "int32_t __thiscall initialize_blink_random(SubgameRuntime* runtime)"),
    ("complete_subgame", "void __thiscall complete_subgame(SubgameRuntime* runtime, uint8_t completed)"),
    (
        "initialize_track_parcel_runtime",
        "Parcel* __thiscall initialize_track_parcel_runtime(Parcel* parcel)",
    ),
    (
        "update_track_parcels",
        "void __thiscall update_track_parcels(ParcelManager* manager)",
    ),
    (
        "initialize_track_parcel_slots",
        "void __thiscall initialize_track_parcel_slots(ParcelManager* manager)",
    ),
    (
        "allocate_track_parcel_slot",
        "Parcel* __thiscall allocate_track_parcel_slot(ParcelManager* manager)",
    ),
    (
        "update_track_parcel",
        "void __thiscall update_track_parcel(Parcel* parcel)",
    ),
    (
        "spawn_track_parcel",
        "Parcel* __thiscall spawn_track_parcel(SubgameRuntime* runtime, Vec3* world_position, Player* source_player)",
    ),
    (
        "initialize_completion_screen",
        "void __thiscall initialize_completion_screen(Completion* completion, int32_t delivered_count, uint8_t perfect_delivery)",
    ),
    (
        "flush_row_event_display",
        "void __thiscall flush_row_event_display(Completion* completion)",
    ),
    (
        "update_row_event_display",
        "void __thiscall update_row_event_display(Completion* completion)",
    ),
    (
        "register_parcel_delivery",
        "void __thiscall register_parcel_delivery(Completion* completion)",
    ),
    (
        "update_times_up",
        "void __thiscall update_times_up(TimesUp* times_up)",
    ),
    (
        "uninit_times_up",
        "void __thiscall uninit_times_up(TimesUp* times_up)",
    ),
    (
        "show_times_up_message",
        "void __thiscall show_times_up_message(TimesUp* times_up)",
    ),
    (
        "initialize_challenge_setup_screen",
        "void __thiscall initialize_challenge_setup_screen(GUI* gui)",
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
    (
        "update_subgame_camera",
        "void __thiscall update_subgame_camera(SubgameRuntime* runtime)",
    ),
    (
        "destroy_help_screen",
        "void __thiscall destroy_help_screen(Help* help)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow subgame runtime prototype slice to a Binary Ninja target."
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
            header_path=DEFAULT_OBJECT_HEADER_PATH,
            required_structs=("tColour",),
        ),
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
                "SubPause",
                "TimeTrial",
                "GUI",
                "Help",
                "ThanksScreen",
                "GalaxyPoint",
                "GalaxyRouteRecord",
                "GalaxyRouteSlot",
                "GalaxyRouteNameRecord",
                "Galaxy",
                "Vapour",
                "TrackPickupState",
                "JetPack",
                "Banner",
                "BannerPool",
                "ParcelState",
                "Parcel",
                "ParcelManager",
                "CompletionState",
                "Completion",
                "TimesUpState",
                "TimesUp",
            ),
        ),
    ]
    parcel_sizes = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in PARCEL_EXPECTED_SIZES
    }
    parcel_size_mismatches = {
        name: {"expected": expected, "observed": parcel_sizes[name]}
        for name, expected in PARCEL_EXPECTED_SIZES.items()
        if parcel_sizes[name] != expected
    }
    if parcel_size_mismatches:
        raise RuntimeError(
            f"refusing parcel ownership replay with size mismatches: "
            f"{parcel_size_mismatches!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": parcel_sizes,
        }
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=GALAXY_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=PARCEL_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=GALAXY_DATA_SYMBOL_UPDATES,
            kind="data",
        )
    )
    operations.extend(
        apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=GALAXY_DATA_VAR_UPDATES,
        )
    )
    subgame_updates = [*SUBGAME_FIELD_UPDATES]
    if struct_exists(REPO_ROOT, target=args.target, struct_name="BodBase"):
        subgame_updates.extend(SUBGAME_BOD_FIELD_UPDATES)
    if struct_exists(REPO_ROOT, target=args.target, struct_name="Player"):
        subgame_updates.extend(SUBGAME_PLAYER_FIELD_UPDATES)
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("SubgameRuntime", subgame_updates),
                ("GalaxyPoint", GALAXY_POINT_FIELD_UPDATES),
                ("GalaxyRouteRecord", GALAXY_ROUTE_RECORD_FIELD_UPDATES),
                ("GalaxyRouteSlot", GALAXY_ROUTE_SLOT_FIELD_UPDATES),
                ("GalaxyRouteNameRecord", GALAXY_ROUTE_NAME_FIELD_UPDATES),
                ("Galaxy", GALAXY_FIELD_UPDATES),
                ("JetPack", JETPACK_FIELD_UPDATES),
                ("Banner", BANNER_FIELD_UPDATES),
                ("Completion", COMPLETION_FIELD_UPDATES),
                ("Parcel", PARCEL_FIELD_UPDATES),
                ("TimesUp", TIMES_UP_FIELD_UPDATES),
                ("GUI", GUI_FIELD_UPDATES),
            ),
            # Several legacy analysis aliases are re-inferred during preview.
            # The batch helper applies prototypes through the same verified
            # direct-user-type path, but amortizes analysis across the batch.
            proto_updates=PROTO_UPDATES,
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
