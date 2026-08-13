#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_type_renames,
    apply_user_var_updates,
    current_header_type_equivalence,
    current_struct_size,
    emit_summary,
    reanalyze_functions,
    remove_user_var_updates,
    struct_exists,
    types_declare_if_missing,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

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

GALAXY_STAR_FIELD_UPDATES = (
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
    ("0x10", "route_slots", "GalaxyStar[101]"),
    ("0x10930", "route_names", "GalaxyRouteNameRecord[10]"),
    ("0x10f70", "level_progress_base", "cRSubGame*"),
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

PAUSE_FUNCTION_SYMBOL_UPDATES = (
    ("0x440600", "uninit_pause_menu"),
    ("0x440660", "initialize_pause_menu"),
    ("0x4407a0", "update_pause_menu"),
)

SUBGAME_FUNCTION_SYMBOL_UPDATES = (
    ("0x416800", "initialize_help_screen"),
    ("0x4168c0", "destroy_help_screen"),
    ("0x4168d0", "update_help_screen"),
    ("0x435df0", "set_subgame_features"),
    ("0x437e80", "calc_slider_to_rate"),
    ("0x4404d0", "calc_subgame_rate"),
    ("0x4408a0", "advance_blink_random"),
    ("0x4408c0", "initialize_blink_random"),
    ("0x445f10", "hide_gameplay_scores"),
    ("0x445f40", "unhide_gameplay_scores"),
)

HELP_EXPECTED_SIZE = 0x04

TIMES_UP_EXPECTED_SIZE = 0x10

TIMES_UP_TYPE_RENAMES = (("TimesUp", "cRTimesUp"),)

TIME_TRIAL_TYPE_RENAMES = (("TimeTrial", "cRTimeTrial"),)

GUI_TYPE_RENAMES = (("GUI", "cRGUI"),)

TIME_TRIAL_FIELD_UPDATES = (
    ("0x00", "course_records", "TimeTrialCourseRecord[0x33]"),
)

TIME_TRIAL_REANALYSIS_FUNCTIONS = (
    "format_time_trial_string",
    "update_challenge_setup_screen",
    "initialize_subgame",
    "update_subgame",
)

TIMES_UP_REANALYSIS_FUNCTIONS = (
    "initialize_subgame",
    "build_subgame_level",
    "destroy_subgame",
    "update_subgoldy",
    "update_times_up",
    "uninit_times_up",
    "show_times_up_message",
)

PARCEL_EXPECTED_SIZES = {
    "Parcel": 0x8C,
    "ParcelManager": 0x1B58,
}

BANNER_EXPECTED_SIZES = {
    "Banner": 0x60,
    "BannerPool": 0xC0,
    "BannerInitStrideView": 0x3CD6F8,
}

PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES = {
    "PresentationAnimationObjectStrideCursor": 0x80,
}

SUB_LAZER_STARTUP_CURSOR_EXPECTED_SIZES = {
    "SubLazer": 0xB0,
    "SubLazerBodyObjectStrideCursor": 0xB0,
}

SALT_STARTUP_CURSOR_EXPECTED_SIZES = {
    "SaltOwnerGameStrideCursor": 0x98,
}

GALAXY_ROUTE_CURSOR_EXPECTED_SIZES = {
    "GalaxyStar": 0x2A0,
    "cRGalaxy": 0x10FA8,
}

BANNER_INITIALIZER_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        4535,
        -296,
        "banner_stride_view",
        "BannerInitStrideView*",
    ),
)

# Five startup cleanup loops carry the address of the Object* field inside an
# owned 0x80-byte PresentationAnimationSlot. Preserve that field-first stride
# instead of rebasing the values to fabricated whole-slot or GameRoot owners.
PRESENTATION_ANIMATION_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        18434,
        -300,
        "cutscene_animation_object_cursor",
        "PresentationAnimationObjectStrideCursor*",
    ),
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        18707,
        -300,
        "jetpack_animation_object_cursor",
        "PresentationAnimationObjectStrideCursor*",
    ),
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        19107,
        -300,
        "left_weapon_animation_object_cursor",
        "PresentationAnimationObjectStrideCursor*",
    ),
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        19507,
        -300,
        "right_weapon_animation_object_cursor",
        "PresentationAnimationObjectStrideCursor*",
    ),
    (
        "initialize_game_assets_and_world",
        "StackVariableSourceType",
        19907,
        -300,
        "top_weapon_animation_object_cursor",
        "PresentationAnimationObjectStrideCursor*",
    ),
)

# The twenty-slot startup loop carries SubLazer::body.bod.object in EDI, uses
# the adjacent body color and owner-game backlink, and advances by the exact
# 0xb0-byte SubLazer stride. Keep the field-first lifetime explicit without
# replacing SubLazerManager::slots as the owning array.
SUB_LAZER_STARTUP_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        4267,
        73,
        "sub_lazer_body_object_cursor",
        "SubLazerBodyObjectStrideCursor*",
    ),
)

# The forty-slot startup loop carries Salt::owner_game in EDI and reaches the
# earlier body fields through fixed negative offsets before advancing by one
# exact 0x98-byte Salt stride. Keep SaltManager::slots as the owning array.
SALT_STARTUP_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        4417,
        73,
        "salt_owner_game_cursor",
        "SaltOwnerGameStrideCursor*",
    ),
)

# update_galaxy's first route pass borrows one GalaxyStar at a time from
# cRGalaxy::route_slots. Native advances EBX by exactly sizeof(GalaxyStar);
# without this bounded lifetime Binary Ninja promotes the borrow to a pointer
# to the complete 101-slot owner and renders a misleading owner-sized step.
#
# Two later passes carry the address of GalaxyRouteRecord::highlight_target
# and advance it by the same slot stride. The hover pass needs an explicit
# float borrow because bit-pattern stores otherwise degrade it to int32_t*
# after reanalysis. The earlier reset pass is deliberately left automatic:
# annotating its interior address suppresses Binary Ninja's more useful
# containing GalaxyStar recovery and expands each dword store into bytes.
GALAXY_ROUTE_CURSOR_USER_VAR_UPDATES = (
    (
        "update_galaxy",
        "RegisterVariableSourceType",
        40,
        69,
        "route_slot_cursor",
        "GalaxyStar*",
    ),
    (
        "update_galaxy",
        "RegisterVariableSourceType",
        1352,
        73,
        "highlight_target_cursor",
        "float*",
    ),
)

REJECTED_GALAXY_HIGHLIGHT_RESET_CURSOR_REMOVALS = (
    (
        "update_galaxy",
        "RegisterVariableSourceType",
        1086,
        67,
        "highlight_reset_cursor",
        "float*",
    ),
)

COMPLETION_REANALYSIS_FUNCTIONS = (
    "flush_row_event_display",
    "initialize_completion_screen",
    "update_row_event_display",
    "register_parcel_delivery",
)

HELP_REANALYSIS_FUNCTIONS = (
    "initialize_help_screen",
    "destroy_help_screen",
    "update_help_screen",
)

TRACK_MIRROR_REANALYSIS_FUNCTIONS = (
    "populate_runtime_track_cells_from_segments",
)

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
    ("0x40", "level_mode", "int32_t"),
    ("0x4c", "runtime_flags", "uint32_t"),
    ("0x355e64", "jetpack_pickup", "JetPack"),
    ("0x359080", "banners", "BannerPool"),
    ("0x3bb700", "blink_random_index", "int32_t"),
    ("0x3bb704", "blink_random_samples", "float[24]"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SubSolution*"),
    ("0xff25d8", "selected_level_record_cursor", "int32_t"),
    ("0xff25dc", "replay_update_cursor", "int32_t"),
    ("0xff25e0", "time_trial", "cRTimeTrial"),
    ("0x125e480", "parcel_manager", "ParcelManager"),
    ("0x125ffd8", "garbage_frequency", "float"),
    ("0x125ffdc", "salt_frequency", "float"),
    ("0x125ffe0", "gui", "cRGUI"),
    ("0x1260008", "help", "Help"),
    ("0x126000c", "splash", "cRSplash"),
    ("0x1260020", "galaxy", "cRGalaxy"),
    ("0x1270fc8", "subgame_rebuild_selector", "int32_t"),
    ("0x1270fcc", "next_slug_voice_trigger_z", "float"),
    ("0x1270fd0", "slug_voice_trigger_spacing_z", "float"),
    ("0x1270fd4", "enemy_manager", "EnemyManager"),
    ("0x12727d8", "completion", "Completion"),
    ("0x1272828", "times_up", "cRTimesUp"),
)

# These richer nested types are supplied by later ownership slices. Preserve
# them when present instead of letting the intentionally sparse bootstrap
# header flatten their ranges back into byte arrays.
SUBGAME_BOD_FIELD_UPDATES = (
    ("0x355bd4", "barrier_sub_lazer_list_head", "BodBase"),
    ("0x355c0c", "salt_hazard_list_head", "BodBase"),
)

SUBGAME_PLAYER_FIELD_UPDATES = (
    ("0x3bb764", "player", "Player"),
)

COMPLETION_FIELD_UPDATES = (
    ("0x00", "title_widget", "FrontendWidget*"),
    ("0x04", "delivered_count_widget", "FrontendWidget*"),
    ("0x08", "bonus_summary_widget", "FrontendWidget*"),
    ("0x0c", "bonus_icon_widget", "FrontendWidget*"),
    ("0x10", "continue_widget", "FrontendWidget*"),
    ("0x14", "state", "CompletionState"),
    ("0x18", "fast_forward_enabled", "uint8_t"),
    ("0x34", "widget_world", "Vec3"),
)

PARCEL_FIELD_UPDATES = (
    ("0x38", "state", "ParcelState"),
    ("0x3c", "owner_subgame", "cRSubGame*"),
)

JETPACK_FIELD_UPDATES = (
    ("0x38", "state", "TrackPickupState"),
    ("0x44", "owner_game", "cRSubGame*"),
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "cRSubGame*"),
)

SUB_LAZER_STARTUP_CURSOR_FIELD_UPDATES = (
    ("0x64", "owner_game", "cRSubGame*"),
)

SALT_STARTUP_CURSOR_FIELD_UPDATES = (
    ("0x00", "owner_game", "cRSubGame*"),
)

TIMES_UP_FIELD_UPDATES = (
    ("0x00", "state", "TimesUpState"),
    ("0x04", "border", "FrontendWidget*"),
    ("0x08", "progress", "float"),
    ("0x0c", "progress_step", "float"),
)

GUI_FIELD_UPDATES = (
    ("0x00", "game", "cRSubGame*"),
    ("0x04", "next_level_button", "FrontendWidget*"),
    ("0x08", "previous_level_button", "FrontendWidget*"),
    ("0x0c", "level_name_widget", "FrontendWidget*"),
    ("0x10", "play_button", "FrontendWidget*"),
    ("0x14", "_pad_14", "uint8_t[0x4]"),
    ("0x18", "back_button", "FrontendWidget*"),
    ("0x1c", "speed_slider", "FrontendWidget*"),
    ("0x20", "difficulty_slider", "FrontendWidget*"),
    ("0x24", "replay_button", "FrontendWidget*"),
)

HELP_FIELD_UPDATES = (
    ("0x00", "back_button", "FrontendWidget*"),
)

SPLASH_FIELD_UPDATES = (
    ("0x00", "game", "cRSubGame*"),
)

PROTO_UPDATES = (
    (
        "uninit_pause_menu",
        "void __thiscall uninit_pause_menu(SubPause* pause)",
    ),
    (
        "initialize_pause_menu",
        "void __thiscall initialize_pause_menu(SubPause* pause)",
    ),
    (
        "update_pause_menu",
        "void __thiscall update_pause_menu(SubPause* pause)",
    ),
    (
        "initialize_galaxy_route_name_record",
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(GalaxyRouteNameRecord* record)",
    ),
    (
        "load_galaxy_layout",
        "void __thiscall load_galaxy_layout(cRGalaxy* galaxy)",
    ),
    (
        "destroy_galaxy",
        "void __thiscall destroy_galaxy(cRGalaxy* galaxy)",
    ),
    (
        "initialize_galaxy",
        "void __thiscall initialize_galaxy(cRGalaxy* galaxy)",
    ),
    (
        "update_galaxy",
        "int32_t __thiscall update_galaxy(cRGalaxy* galaxy)",
    ),
    (
        "draw_galaxy_line",
        "void __thiscall draw_galaxy_line(cRGalaxy* galaxy, int32_t texture_id, float x0, float y0, float x1, float y1, float width, tColour* color)",
    ),
    (
        "update_galaxy_route_record",
        "void __thiscall update_galaxy_route_record(GalaxyStar* star)",
    ),
    (
        "close_galaxy_route",
        "void __thiscall close_galaxy_route(cRGalaxy* galaxy)",
    ),
    (
        "open_galaxy_route",
        "void __thiscall open_galaxy_route(cRGalaxy* galaxy, int32_t selected_level_index)",
    ),
    (
        "galaxy_border_bound",
        "void __thiscall galaxy_border_bound(cRGalaxy* galaxy, float* min_x, float* max_x, float* min_y, float* max_y, FrontendWidget* widget)",
    ),
    (
        "zero_timer_counters",
        "void __thiscall zero_timer_counters(cRTime* time)",
    ),
    (
        "advance_timer_counters",
        "void __thiscall advance_timer_counters(cRTime* time, float delta_ticks)",
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
    ("set_subgame_features", "void __thiscall set_subgame_features(cRSubGame* runtime)"),
    ("switch_track_mirror", "void __thiscall switch_track_mirror(cRSubGame* runtime)"),
    (
        "normalize_segment_glyph_for_track_flags",
        "char __thiscall normalize_segment_glyph_for_track_flags(cRSubGame* runtime, char glyph, int32_t row, char edge_row)",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "void __thiscall rebuild_track_runtime_from_segments(cRSubGame* runtime, int32_t level_index)",
    ),
    (
        "calc_slider_to_rate",
        "float __thiscall calc_slider_to_rate(cRSubGame* runtime, float slider)",
    ),
    ("set_subgame_rate", "void __thiscall set_subgame_rate(cRSubGame* runtime, float rate)"),
    ("calc_subgame_rate", "void __thiscall calc_subgame_rate(cRSubGame* runtime)"),
    ("advance_blink_random", "double __thiscall advance_blink_random(cRSubGame* runtime)"),
    ("initialize_blink_random", "void __thiscall initialize_blink_random(cRSubGame* runtime)"),
    ("hide_gameplay_scores", "void __thiscall hide_gameplay_scores(cRSubGame* runtime)"),
    (
        "unhide_gameplay_scores",
        "void __thiscall unhide_gameplay_scores(cRSubGame* runtime)",
    ),
    ("complete_subgame", "void __thiscall complete_subgame(cRSubGame* runtime, uint8_t completed)"),
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
        "Parcel* __thiscall spawn_track_parcel(cRSubGame* runtime, Vec3* world_position, Player* source_player)",
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
        "void __thiscall update_times_up(cRTimesUp* times_up)",
    ),
    (
        "uninit_times_up",
        "void __thiscall uninit_times_up(cRTimesUp* times_up)",
    ),
    (
        "show_times_up_message",
        "void __thiscall show_times_up_message(cRTimesUp* times_up)",
    ),
    (
        "initialize_challenge_setup_screen",
        "void __thiscall initialize_challenge_setup_screen(cRGUI* gui)",
    ),
    (
        "destroy_challenge_setup_screen",
        "void __thiscall destroy_challenge_setup_screen(cRGUI* gui)",
    ),
    (
        "update_challenge_setup_screen",
        "int32_t __thiscall update_challenge_setup_screen(cRGUI* gui)",
    ),
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(cRTimeTrial* time_trial, cRTime* timer)",
    ),
    (
        "update_subgame_camera",
        "void __thiscall update_subgame_camera(cRSubGame* runtime)",
    ),
    (
        "initialize_help_screen",
        "void __thiscall initialize_help_screen(Help* help)",
    ),
    (
        "destroy_help_screen",
        "void __thiscall destroy_help_screen(Help* help)",
    ),
    (
        "update_help_screen",
        "void __thiscall update_help_screen(Help* help)",
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
    parser.add_argument(
        "--galaxy-route-cursor-only",
        action="store_true",
        help=(
            "Replay only update_galaxy's borrowed route-slot cursor after "
            "verifying the existing cRGalaxy owner layouts."
        ),
    )
    return parser.parse_args()


def require_galaxy_route_cursor_dependencies(*, target: str) -> dict[str, object]:
    observed_sizes = {
        name: current_struct_size(REPO_ROOT, target=target, struct_name=name)
        for name in GALAXY_ROUTE_CURSOR_EXPECTED_SIZES
    }
    mismatches = {
        name: {
            "expected": expected,
            "observed": observed_sizes[name],
        }
        for name, expected in GALAXY_ROUTE_CURSOR_EXPECTED_SIZES.items()
        if observed_sizes[name] != expected
    }
    if mismatches:
        raise RuntimeError(
            "refusing cRGalaxy route cursor replay with size mismatches: "
            f"{mismatches!r}"
        )
    return {
        "op": "verify_galaxy_route_cursor_dependencies",
        "status": "verified",
        "owner_sizes": observed_sizes,
    }


def ensure_time_trial_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Replay the recovered inline course records when either owner is stale."""
    type_names = ("TimeTrialCourseRecord", "cRTimeTrial")
    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    stale_types = tuple(
        type_name for type_name in type_names if not equivalence.get(type_name, False)
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRTimeTrial owner types already match the header",
            "header": str(header_path),
            "replace_types": (),
            "include_types": type_names,
        }
    return types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=type_names,
    )


def ensure_times_up_owner_type(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Repair cRTimesUp only when its complete 0x10-byte layout is stale."""
    observed_size = current_struct_size(
        REPO_ROOT,
        target=target,
        struct_name="cRTimesUp",
    )
    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    if (
        observed_size == TIMES_UP_EXPECTED_SIZE
        and equivalence.get("cRTimesUp", False)
    ):
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRTimesUp owner type already matches the header",
            "header": str(header_path),
            "replace_types": (),
            "include_types": ("cRTimesUp",),
        }
    operation = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=("cRTimesUp",),
        include_types={"cRTimesUp": TIMES_UP_EXPECTED_SIZE},
    )
    operation["expected_size"] = TIMES_UP_EXPECTED_SIZE
    return operation


def verify_times_up_owner_size(*, target: str) -> dict[str, object]:
    observed_size = current_struct_size(
        REPO_ROOT,
        target=target,
        struct_name="cRTimesUp",
    )
    if observed_size != TIMES_UP_EXPECTED_SIZE:
        raise RuntimeError(
            "refusing cRTimesUp method replay with owner-size mismatch: "
            f"expected {TIMES_UP_EXPECTED_SIZE:#x}, observed {observed_size!r}"
        )
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "times_up",
        "owner_sizes": {"cRTimesUp": observed_size},
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    contact_header_path = args.contact_header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")
    if not contact_header_path.is_file():
        raise FileNotFoundError(f"contact-target type header not found: {contact_header_path}")

    if args.galaxy_route_cursor_only:
        operations = [
            require_galaxy_route_cursor_dependencies(target=args.target),
            *remove_user_var_updates(
                REPO_ROOT,
                target=args.target,
                removals=REJECTED_GALAXY_HIGHLIGHT_RESET_CURSOR_REMOVALS,
            ),
            *apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=GALAXY_ROUTE_CURSOR_USER_VAR_UPDATES,
            ),
        ]
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    type_rename_operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=(
            ("SubgameRuntime", "cRSubGame"),
            ("GalaxyRouteSlot", "GalaxyStar"),
            ("Galaxy", "cRGalaxy"),
            ("Time", "cRTime"),
            *TIME_TRIAL_TYPE_RENAMES,
            *GUI_TYPE_RENAMES,
            *TIMES_UP_TYPE_RENAMES,
        ),
    )

    operations: list[dict[str, object]] = [
        *type_rename_operations,
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
                "cRSubGame",
                "SubgameRuntime",
                "SubPause",
                "cRTime",
                "TimeTrialCourseRecord",
                "cRTimeTrial",
                "cRGUI",
                "Help",
                "cRSplash",
                "GalaxyPoint",
                "GalaxyRouteRecord",
                "GalaxyStar",
                "GalaxyRouteNameRecord",
                "cRGalaxy",
                "Vapour",
                "TrackPickupState",
                "JetPack",
                "Banner",
                "BannerPool",
                "BannerInitStrideView",
                "PresentationAnimationObjectStrideCursor",
                "SubLazerBodyObjectStrideCursor",
                "SaltOwnerGameStrideCursor",
                "ParcelState",
                "Parcel",
                "ParcelManager",
                "CompletionState",
                "Completion",
                "TimesUpState",
                "cRTimesUp",
            ),
        ),
    ]
    operations.append(
        ensure_times_up_owner_type(
            target=args.target,
            header_path=header_path,
        )
    )
    operations.append(verify_times_up_owner_size(target=args.target))
    operations.append(
        ensure_time_trial_owner_types(
            target=args.target,
            header_path=header_path,
        )
    )
    operations.append(
        require_galaxy_route_cursor_dependencies(target=args.target)
    )
    help_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="Help",
    )
    if help_size != HELP_EXPECTED_SIZE:
        raise RuntimeError(
            "refusing Help lifecycle replay with owner-size mismatch: "
            f"expected {HELP_EXPECTED_SIZE:#x}, observed {help_size!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": {"Help": help_size},
        }
    )
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
    banner_sizes = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in BANNER_EXPECTED_SIZES
    }
    banner_size_mismatches = {
        name: {"expected": expected, "observed": banner_sizes[name]}
        for name, expected in BANNER_EXPECTED_SIZES.items()
        if banner_sizes[name] != expected
    }
    if banner_size_mismatches:
        raise RuntimeError(
            "refusing Banner initializer replay with size mismatches: "
            f"{banner_size_mismatches!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": banner_sizes,
        }
    )
    presentation_animation_cursor_sizes = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES
    }
    presentation_animation_cursor_size_mismatches = {
        name: {"expected": expected, "observed": presentation_animation_cursor_sizes[name]}
        for name, expected in PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES.items()
        if presentation_animation_cursor_sizes[name] != expected
    }
    if presentation_animation_cursor_size_mismatches:
        raise RuntimeError(
            "refusing presentation-animation cursor replay with size mismatches: "
            f"{presentation_animation_cursor_size_mismatches!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": presentation_animation_cursor_sizes,
        }
    )
    sub_lazer_startup_cursor_sizes = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in SUB_LAZER_STARTUP_CURSOR_EXPECTED_SIZES
    }
    sub_lazer_startup_cursor_size_mismatches = {
        name: {
            "expected": expected,
            "observed": sub_lazer_startup_cursor_sizes[name],
        }
        for name, expected in SUB_LAZER_STARTUP_CURSOR_EXPECTED_SIZES.items()
        if sub_lazer_startup_cursor_sizes[name] != expected
    }
    if sub_lazer_startup_cursor_size_mismatches:
        raise RuntimeError(
            "refusing SubLazer startup cursor replay with size mismatches: "
            f"{sub_lazer_startup_cursor_size_mismatches!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": sub_lazer_startup_cursor_sizes,
        }
    )
    salt_startup_cursor_sizes = {
        name: current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
        for name in SALT_STARTUP_CURSOR_EXPECTED_SIZES
    }
    salt_startup_cursor_size_mismatches = {
        name: {
            "expected": expected,
            "observed": salt_startup_cursor_sizes[name],
        }
        for name, expected in SALT_STARTUP_CURSOR_EXPECTED_SIZES.items()
        if salt_startup_cursor_sizes[name] != expected
    }
    if salt_startup_cursor_size_mismatches:
        raise RuntimeError(
            "refusing Salt startup cursor replay with size mismatches: "
            f"{salt_startup_cursor_size_mismatches!r}"
        )
    operations.append(
        {
            "op": "owner_size_verify",
            "status": "verified",
            "owner_sizes": salt_startup_cursor_sizes,
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
            updates=PAUSE_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SUBGAME_FUNCTION_SYMBOL_UPDATES,
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
                ("cRSubGame", subgame_updates),
                ("GalaxyPoint", GALAXY_POINT_FIELD_UPDATES),
                ("GalaxyRouteRecord", GALAXY_ROUTE_RECORD_FIELD_UPDATES),
                ("GalaxyStar", GALAXY_STAR_FIELD_UPDATES),
                ("GalaxyRouteNameRecord", GALAXY_ROUTE_NAME_FIELD_UPDATES),
                ("cRGalaxy", GALAXY_FIELD_UPDATES),
                ("JetPack", JETPACK_FIELD_UPDATES),
                ("Banner", BANNER_FIELD_UPDATES),
                (
                    "SubLazerBodyObjectStrideCursor",
                    SUB_LAZER_STARTUP_CURSOR_FIELD_UPDATES,
                ),
                ("SaltOwnerGameStrideCursor", SALT_STARTUP_CURSOR_FIELD_UPDATES),
                ("Completion", COMPLETION_FIELD_UPDATES),
                ("Parcel", PARCEL_FIELD_UPDATES),
                ("cRTimeTrial", TIME_TRIAL_FIELD_UPDATES),
                ("cRTimesUp", TIMES_UP_FIELD_UPDATES),
                ("cRGUI", GUI_FIELD_UPDATES),
                ("Help", HELP_FIELD_UPDATES),
                ("cRSplash", SPLASH_FIELD_UPDATES),
            ),
            # Several legacy analysis aliases are re-inferred during preview.
            # The batch helper applies prototypes through the same verified
            # direct-user-type path, but amortizes analysis across the batch.
            proto_updates=PROTO_UPDATES,
        )
    )
    operations.extend(
        remove_user_var_updates(
            REPO_ROOT,
            target=args.target,
            removals=REJECTED_GALAXY_HIGHLIGHT_RESET_CURSOR_REMOVALS,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=(
                *BANNER_INITIALIZER_USER_VAR_UPDATES,
                *PRESENTATION_ANIMATION_CURSOR_USER_VAR_UPDATES,
                *SUB_LAZER_STARTUP_CURSOR_USER_VAR_UPDATES,
                *SALT_STARTUP_CURSOR_USER_VAR_UPDATES,
                *GALAXY_ROUTE_CURSOR_USER_VAR_UPDATES,
            ),
        )
    )
    operations.extend(
        reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            # apply_user_var_updates already performs and verifies the root
            # initializer's reanalysis. Repeating that large function here
            # adds several minutes to the replay without changing its state.
            identifiers=(
                *COMPLETION_REANALYSIS_FUNCTIONS,
                *TIME_TRIAL_REANALYSIS_FUNCTIONS,
                *TIMES_UP_REANALYSIS_FUNCTIONS,
                *HELP_REANALYSIS_FUNCTIONS,
                *TRACK_MIRROR_REANALYSIS_FUNCTIONS,
            ),
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
