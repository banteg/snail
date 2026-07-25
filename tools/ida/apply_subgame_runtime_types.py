import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


HELP_OWNER_EXPECTED_SIZE = 0x04

TRUSTED_NAMES = (
    (0x408860, "initialize_track_parcel_runtime"),
    (0x416800, "initialize_help_screen"),
    (0x4168C0, "destroy_help_screen"),
    (0x4168D0, "update_help_screen"),
    (0x435DF0, "set_subgame_features"),
    (0x437B10, "reset_subgame"),
    (0x440600, "uninit_pause_menu"),
    (0x440660, "initialize_pause_menu"),
    (0x4407A0, "update_pause_menu"),
    (0x443130, "update_track_parcels"),
    (0x443160, "initialize_track_parcel_slots"),
    (0x443190, "allocate_track_parcel_slot"),
    (0x4431D0, "update_track_parcel"),
    (0x443730, "spawn_track_parcel"),
)

SALT_OWNER_EXPECTED_SIZE = 0x98
SALT_OWNER_EXPECTED_MEMBERS = (
    (0x80, 4, "state", "SaltState"),
    (0x88, 4, "owner_game", "SubgameRuntime *"),
    (0x8C, 4, "fade_alpha", "float"),
    (0x90, 4, "spawn_velocity_y", "float"),
    (0x94, 1, "collision_armed", "uint8_t"),
)
SALT_STATE_CURSOR_EXPECTED_SIZE = 0x98
SALT_STATE_CURSOR_EXPECTED_MEMBERS = (
    (0x00, 4, "state", "SaltState"),
)
SALT_OWNER_GAME_CURSOR_EXPECTED_SIZE = 0x98

SUB_LAZER_OWNER_EXPECTED_SIZE = 0xB0
SUB_LAZER_MANAGER_EXPECTED_SIZE = 0xDC0
SUB_LAZER_BODY_OBJECT_CURSOR_EXPECTED_SIZE = 0xB0
SUB_LAZER_OWNER_EXPECTED_MEMBERS = (
    (0x80, 4, "state", "SubLazerState"),
    (0x88, 4, "owner_game", "SubgameRuntime *"),
    (0x8C, 12, "velocity", "Vec3"),
    (0x98, 4, "sprite_bob_phase", "float"),
    (0x9C, 4, "sprite_bob_phase_step", "float"),
)

SUB_GARBAGE_OWNER_EXPECTED_SIZE = 0xC4
SUB_GARBAGE_POOL_EXPECTED_SIZE = 0x264C
SUB_GARBAGE_SLOT_CURSOR_EXPECTED_SIZE = 0x359208
SUB_GARBAGE_OWNER_EXPECTED_MEMBERS = (
    (0x80, 4, "next_active", "SubGarbage *"),
    (0x84, 4, "state", "SubGarbageState"),
    (0x88, 4, "collision_side", "SubGarbageCollisionSide"),
    (0x8C, 4, "owner_game", "SubgameRuntime *"),
    (0x90, 12, "velocity", "Vec3"),
    (0x9C, 4, "radius", "float"),
    (0xA0, 4, "attachment_facing_angle", "float"),
    (0xB4, 4, "sprite", "Sprite *"),
    (0xB8, 4, "source_cell", "TrackRowCell *"),
    (0xC0, 4, "owner_player", "Player *"),
)
SUB_GARBAGE_SLOT_CURSOR_EXPECTED_MEMBERS = (
    (0x359144, 0xC4, "garbage", "SubGarbage"),
)

SLUG_OWNER_EXPECTED_SIZE = 0xEC
SLUG_POOL_EXPECTED_SIZE = 0x760
SLUG_STATE_CURSOR_EXPECTED_SIZE = 0xEC
SLUG_OWNER_EXPECTED_MEMBERS = (
    (0x80, 4, "state", "SubSlugState"),
    (0x84, 4, "death_toss_direction", "SubSlugDeathTossDirection"),
    (0x88, 4, "owner_game", "SubgameRuntime *"),
    (0x8C, 12, "velocity", "Vec3"),
    (0x98, 4, "attachment_facing_angle", "float"),
    (0xAC, 4, "sprite", "Sprite *"),
    (0xB0, 4, "source_cell", "TrackRowCell *"),
    (0xC0, 4, "owner_player", "Player *"),
)
SLUG_STATE_CURSOR_EXPECTED_MEMBERS = (
    (0x00, 4, "state", "SubSlugState"),
)

BANNER_OWNER_EXPECTED_SIZES = {
    "Banner": 0x60,
    "BannerPool": 0xC0,
    "BannerInitStrideView": 0x3CD6F8,
}

PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES = {
    "PresentationAnimationSlot": 0x80,
    "PresentationAnimationObjectStrideCursor": 0x80,
}

BANNER_INITIALIZER_LVAR = {
    "selector": "initialize_game_assets_and_world",
    "definition_address": 0x40BEA8,
    "stack_offset": 84,
    "accepted_names": {"edge_selectord", "banner_stride_view"},
    "accepted_types": {"char *", "BannerInitStrideView *"},
    "target_name": "banner_stride_view",
    "target_struct_name": "BannerInitStrideView",
}

PRESENTATION_ANIMATION_CURSOR_LVARS = (
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40F4F3,
        "stack_offset": 80,
        "accepted_names": {
            "x_offseta",
            "cutscene_animation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "PresentationAnimationObjectStrideCursor *",
        },
        "target_name": "cutscene_animation_object_cursor",
        "target_struct_name": "PresentationAnimationObjectStrideCursor",
    },
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40F604,
        "stack_offset": 80,
        "accepted_names": {
            "x_offsetb",
            "jetpack_animation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "PresentationAnimationObjectStrideCursor *",
        },
        "target_name": "jetpack_animation_object_cursor",
        "target_struct_name": "PresentationAnimationObjectStrideCursor",
    },
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40F794,
        "stack_offset": 80,
        "accepted_names": {
            "x_offsetc",
            "left_weapon_animation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "PresentationAnimationObjectStrideCursor *",
        },
        "target_name": "left_weapon_animation_object_cursor",
        "target_struct_name": "PresentationAnimationObjectStrideCursor",
    },
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40F924,
        "stack_offset": 80,
        "accepted_names": {
            "x_offsetd",
            "right_weapon_animation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "PresentationAnimationObjectStrideCursor *",
        },
        "target_name": "right_weapon_animation_object_cursor",
        "target_struct_name": "PresentationAnimationObjectStrideCursor",
    },
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40FAB4,
        "stack_offset": 80,
        "accepted_names": {
            "x_offsete",
            "top_weapon_animation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "PresentationAnimationObjectStrideCursor *",
        },
        "target_name": "top_weapon_animation_object_cursor",
        "target_struct_name": "PresentationAnimationObjectStrideCursor",
    },
)

SUB_LAZER_STARTUP_CURSOR_LVAR = {
    "selector": "initialize_game_assets_and_world",
    "definition_address": 0x40BD9C,
    "accepted_names": {
        "p_object",
        "sub_lazer_body_object_cursor",
    },
    "accepted_types": {
        "Object **",
        "SubLazerBodyObjectStrideCursor *",
    },
    "target_name": "sub_lazer_body_object_cursor",
    "target_struct_name": "SubLazerBodyObjectStrideCursor",
}

SALT_STARTUP_CURSOR_LVAR = {
    "selector": "initialize_game_assets_and_world",
    "definition_address": 0x40BE32,
    "accepted_names": {
        "p_owner_game",
        "salt_owner_game_cursor",
    },
    "accepted_types": {
        "SubgameRuntime **",
        "SaltOwnerGameStrideCursor *",
    },
    "target_name": "salt_owner_game_cursor",
    "target_struct_name": "SaltOwnerGameStrideCursor",
}


TRUSTED_DECLARATIONS = [
    (
        "uninit_pause_menu",
        "void __thiscall uninit_pause_menu(SubPause* pause);",
    ),
    (
        "initialize_pause_menu",
        "void __thiscall initialize_pause_menu(SubPause* pause);",
    ),
    (
        "update_pause_menu",
        "void __thiscall update_pause_menu(SubPause* pause);",
    ),
    (
        "initialize_galaxy_route_name_record",
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(GalaxyRouteNameRecord* record);",
    ),
    (
        "load_galaxy_layout",
        "void __thiscall load_galaxy_layout(Galaxy* galaxy);",
    ),
    (
        "destroy_galaxy",
        "void __thiscall destroy_galaxy(Galaxy* galaxy);",
    ),
    (
        "initialize_galaxy",
        "void __thiscall initialize_galaxy(Galaxy* galaxy);",
    ),
    (
        "update_galaxy",
        "int32_t __thiscall update_galaxy(Galaxy* galaxy);",
    ),
    (
        "draw_galaxy_line",
        "int32_t __thiscall draw_galaxy_line(Galaxy* galaxy, int32_t texture_id, float x0, float y0, float x1, float y1, float width, tColour* color);",
    ),
    (
        "update_galaxy_route_record",
        "void __thiscall update_galaxy_route_record(GalaxyRouteSlot* slot);",
    ),
    (
        "close_galaxy_route",
        "void __thiscall close_galaxy_route(Galaxy* galaxy);",
    ),
    (
        "open_galaxy_route",
        "void __thiscall open_galaxy_route(Galaxy* galaxy, int32_t selected_level_index);",
    ),
    (
        "galaxy_border_bound",
        "void __thiscall galaxy_border_bound(Galaxy* galaxy, float* min_x, float* max_x, float* min_y, float* max_y, FrontendWidget* widget);",
    ),
    (
        "zero_timer_counters",
        "void __thiscall zero_timer_counters(Time* time);",
    ),
    (
        "advance_timer_counters",
        "void __thiscall advance_timer_counters(Time* time, float delta_ticks);",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner);",
    ),
    (
        "clear_active_landscape_entries",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager);",
    ),
    (
        "initialize_track_jetpack_pickup_runtime",
        "JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);",
    ),
    (
        "update_track_jetpack_pickup",
        "void __thiscall update_track_jetpack_pickup(JetPack* jetpack);",
    ),
    (
        "initialize_vapour",
        "void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);",
    ),
    (
        "reset_vapour",
        "void __thiscall reset_vapour(Vapour* vapour, float* z_floor);",
    ),
    (
        "add_vapour_point",
        "void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);",
    ),
    (
        "update_vapour",
        "void __thiscall update_vapour(Vapour* vapour);",
    ),
    (
        "initialize_slug_hazard_runtime",
        "Slug* __thiscall initialize_slug_hazard_runtime(Slug* slug);",
    ),
    (
        "spawn_slug_hazard",
        "void __thiscall spawn_slug_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* owner_player);",
    ),
    (
        "update_slug_voice_ai",
        "void __thiscall update_slug_voice_ai(Slug* slug);",
    ),
    (
        "play_slug_voice",
        "void __thiscall play_slug_voice(Slug* slug, int32_t sample_index);",
    ),
    (
        "hit_slug_hazard",
        "void __thiscall hit_slug_hazard(Slug* slug, int32_t damage);",
    ),
    (
        "explode_slug_hazard",
        "void __thiscall explode_slug_hazard(Slug* slug);",
    ),
    (
        "kill_slug_hazard",
        "void __thiscall kill_slug_hazard(Slug* slug);",
    ),
    (
        "update_slug_hazard_ai",
        "void __thiscall update_slug_hazard_ai(Slug* slug);",
    ),
    (
        "initialize_sub_lazer_runtime",
        "SubLazer* __thiscall initialize_sub_lazer_runtime(SubLazer* sub_lazer);",
    ),
    (
        "initialize_sub_lazer_pool",
        "void __thiscall initialize_sub_lazer_pool(SubLazerManager* manager);",
    ),
    (
        "spawn_sub_lazer_projectile",
        "void __thiscall spawn_sub_lazer_projectile(SubLazer* sub_lazer, const Vec3* origin, const Vec3* direction);",
    ),
    (
        "deactivate_sub_lazer_projectile",
        "void __thiscall deactivate_sub_lazer_projectile(SubLazer* sub_lazer);",
    ),
    (
        "update_sub_lazer_projectile",
        "void __thiscall update_sub_lazer_projectile(SubLazer* sub_lazer);",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(SubLazerManager* manager, Vec3* origin, const Vec3* direction);",
    ),
    (
        "initialize_salt_hazard_runtime",
        "Salt* __thiscall initialize_salt_hazard_runtime(Salt* salt);",
    ),
    (
        "initialize_salt_hazard_pool",
        "void __thiscall initialize_salt_hazard_pool(SaltManager* manager);",
    ),
    (
        "spawn_salt_hazard",
        "void __thiscall spawn_salt_hazard(SaltManager* manager, const Vec3* position);",
    ),
    (
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(Salt* salt);",
    ),
    (
        "initialize_garbage_hazard",
        "SubGarbage* __thiscall initialize_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "update_garbage_hazard",
        "void __thiscall update_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "destroy_garbage_hazard",
        "SubGarbage* __thiscall destroy_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "spawn_garbage_smoke_particle",
        "void __thiscall spawn_garbage_smoke_particle(SubGarbage* sub_garbage, Vec3* position, Vec3* velocity, Player* owner_player);",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
    ),
    (
        "initialize_track_ring_or_special_effect_runtime",
        "SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing* ring);",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "void __thiscall spawn_track_ring_or_special_effect(SubgameRuntime* game, TrackRowCell* cell, int32_t requested_kind, Player* player, float ring_speed);",
    ),
    (
        "initialize_ring_or_special_effect_particles",
        "int32_t __thiscall initialize_ring_or_special_effect_particles(SubRing* ring, int32_t unused_lives_snapshot);",
    ),
    (
        "emit_ring_star_shower",
        "void __thiscall emit_ring_star_shower(SubRingStar* particle, Player* owner);",
    ),
    (
        "update_ring_or_special_effect_particle",
        "void __thiscall update_ring_or_special_effect_particle(SubRingStar* particle);",
    ),
    (
        "update_ring_or_special_effect_parent",
        "void __thiscall update_ring_or_special_effect_parent(SubRing* ring);",
    ),
    (
        "initialize_enemy_manager",
        # Keep this ICF-shared one-store ABI coarse in IDA so the unrelated
        # tracked-allocation callsite is not assigned the registry owner.
        "void __thiscall initialize_enemy_manager(int* count_owner);",
    ),
    (
        "search_path_for_golb",
        "ContactTargetEntry* __thiscall search_path_for_golb(EnemyManager* manager, const Vec3* position);",
    ),
    (
        "append_subgame_contact_target",
        "void __thiscall append_subgame_contact_target(EnemyManager* manager, const Vec3* position, float radius, int kind, ContactTargetObject* object);",
    ),
    (
        "set_subgame_features",
        "int32_t __thiscall set_subgame_features(SubgameRuntime* runtime);",
    ),
    (
        "switch_track_mirror",
        "bool __thiscall switch_track_mirror(SubgameRuntime* runtime);",
    ),
    (
        "normalize_segment_glyph_for_track_flags",
        "char __thiscall normalize_segment_glyph_for_track_flags(SubgameRuntime* runtime, char glyph, int32_t row, char edge_row);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);",
    ),
    (
        "set_subgame_rate",
        "void __thiscall set_subgame_rate(SubgameRuntime* runtime, float rate);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(SubgameRuntime* game);",
    ),
    (
        "reset_subgame",
        "void __thiscall reset_subgame(SubgameRuntime* game);",
    ),
    (
        "complete_subgame",
        "void __thiscall complete_subgame(SubgameRuntime* runtime, unsigned char completed);",
    ),
    (
        "initialize_track_parcel_runtime",
        "Parcel* __thiscall initialize_track_parcel_runtime(Parcel* parcel);",
    ),
    (
        "update_track_parcels",
        "void __thiscall update_track_parcels(ParcelManager* manager);",
    ),
    (
        "initialize_track_parcel_slots",
        "void __thiscall initialize_track_parcel_slots(ParcelManager* manager);",
    ),
    (
        "allocate_track_parcel_slot",
        "Parcel* __thiscall allocate_track_parcel_slot(ParcelManager* manager);",
    ),
    (
        "update_track_parcel",
        "void __thiscall update_track_parcel(Parcel* parcel);",
    ),
    (
        "spawn_track_parcel",
        "Parcel* __thiscall spawn_track_parcel(SubgameRuntime* runtime, Vec3* world_position, Player* source_player);",
    ),
    (
        "update_times_up",
        "void __thiscall update_times_up(TimesUp* times_up);",
    ),
    (
        "uninit_times_up",
        "void __thiscall uninit_times_up(TimesUp* times_up);",
    ),
    (
        "show_times_up_message",
        "void __thiscall show_times_up_message(TimesUp* times_up);",
    ),
    (
        "initialize_challenge_setup_screen",
        "void __thiscall initialize_challenge_setup_screen(GUI* gui);",
    ),
    (
        "destroy_challenge_setup_screen",
        "void __thiscall destroy_challenge_setup_screen(GUI* gui);",
    ),
    (
        "update_challenge_setup_screen",
        "int __thiscall update_challenge_setup_screen(GUI* gui);",
    ),
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(TimeTrial* time_trial, Time* timer);",
    ),
    (
        "initialize_help_screen",
        "void __thiscall initialize_help_screen(Help* help);",
    ),
    (
        "destroy_help_screen",
        "void __thiscall destroy_help_screen(Help* help);",
    ),
    (
        "update_help_screen",
        "void __thiscall update_help_screen(Help* help);",
    ),
    (
        "bind_subgame_owner",
        "SubgameRuntime* __thiscall bind_subgame_owner(SubgameOwnerLink* owner);",
    ),
]


TRUSTED_DATA_DECLARATIONS = [
    (
        0x4A1C4C,
        "g_galaxy_group_points",
        "GalaxyPoint g_galaxy_group_points[10];",
    ),
    (
        0x4A1D14,
        "g_galaxy_route_points",
        "GalaxyPoint g_galaxy_route_points[101];",
    ),
]

GALAXY_ROUTE_POINT_OWNER_ADDRESS = 0x4A1D14
GALAXY_ROUTE_POINT_OWNER_SIZE = 0x328
GALAXY_ROUTE_POINT_NEXT_OWNER_ADDRESS = 0x4A203C
GALAXY_ROUTE_POINT_OWNER_NAME = "g_galaxy_route_points"
GALAXY_ROUTE_POINT_OWNER_TYPE = "GalaxyPoint[101]"
GALAXY_ROUTE_POINT_OWNER_DECLARATION = (
    "GalaxyPoint g_galaxy_route_points[101];"
)
GALAXY_ROUTE_POINT_INTERIOR_ALIASES = (
    (0x4A1D18, "g_galaxy_initial_map_y_bits"),
    (0x4A1D1C, "g_galaxy_missing_level_map_x_table"),
    (0x4A1D20, "g_galaxy_missing_level_map_y_table"),
)

TIME_TRIAL_COURSE_RECORD_EXPECTED_SIZE = 0x10
TIME_TRIAL_COURSE_RECORD_EXPECTED_MEMBERS = (
    (0x00, 4, "course_name", "char *"),
)
TIME_TRIAL_EXPECTED_SIZE = 0x330
TIME_TRIAL_EXPECTED_MEMBERS = (
    (0x00, 0x330, "course_records", "TimeTrialCourseRecord[51]"),
)


REQUIRED_CANONICAL_OWNER_MARKERS = (
    "SegmentCache segment_cache;",
    "SubRingStar particles[10];",
    "SubRingPool ring_effects;",
    "TrackRowCell runtime_cells[3200][8];",
    "SubRow runtime_rows[3200];",
    "SubSolution* selected_level_record;",
    "TimeTrialCourseRecord course_records[TIME_TRIAL_COURSE_RECORD_COUNT];",
    "Help_must_be_0x04",
    "Parcel_must_be_0x8c",
    "Parcel slots[50];",
    "ParcelManager_must_be_0x1b58",
    "typedef struct SubGarbageSlotCursor {",
    "typedef struct BannerInitStrideView {",
    "uint8_t root_to_banner[0x3cd698];",
    "typedef struct PresentationAnimationObjectStrideCursor {",
    "Object* object;",
    "uint8_t slot_stride_tail[0x7c];",
    "typedef struct SubLazerBodyObjectStrideCursor {",
    "Object* body_object;",
    "tColour body_color;",
    "SubgameRuntime* owner_game;",
    "uint8_t _stride_tail[0x48];",
    "typedef struct SaltOwnerGameStrideCursor {",
    "uint8_t _stride_tail[0x94];",
)

EXPECTED_PARCEL_OWNER_SIZES = {
    "Parcel": 0x8C,
    "ParcelManager": 0x1B58,
}

REANALYSIS_FUNCTIONS = (
    0x404CF0,  # update_row_event_display
    0x408060,  # initialize_runtime_pools_and_path_template_bank
    0x4088E0,  # load_galaxy_layout
    0x408550,  # initialize_garbage_hazard
    0x408530,  # initialize_slug_hazard_runtime
    0x414820,  # update_golb_ai
    0x416800,  # initialize_help_screen
    0x4168C0,  # destroy_help_screen
    0x4168D0,  # update_help_screen
    0x433FC0,  # bind_subgame_owner
    0x408860,  # initialize_track_parcel_runtime
    0x435DF0,  # set_subgame_features
    0x437270,  # normalize_segment_glyph_for_track_flags
    0x437EB0,  # build_subgame_level
    0x437B10,  # reset_subgame
    0x438B90,  # update_subgame
    0x43B120,  # update_subgoldy
    0x43D5A0,  # spawn_garbage_smoke_particle
    0x43DA80,  # spawn_track_garbage_hazard
    0x43DC80,  # spawn_slug_hazard
    0x43F520,  # update_slug_voice_ai
    0x43F560,  # play_slug_voice
    0x43F620,  # hit_slug_hazard
    0x43F680,  # explode_slug_hazard
    0x43F8B0,  # kill_slug_hazard
    0x43F930,  # update_slug_hazard_ai
    0x43F130,  # destroy_garbage_hazard
    0x43F200,  # update_garbage_hazard
    0x440600,  # uninit_pause_menu
    0x440660,  # initialize_pause_menu
    0x4407A0,  # update_pause_menu
    0x441560,  # spawn_salt_hazard
    0x441650,  # initialize_sub_lazer_pool
    0x441670,  # spawn_sub_lazer_projectile
    0x441740,  # deactivate_sub_lazer_projectile
    0x4417D0,  # update_sub_lazer_projectile
    0x441AD0,  # shoot_subgoldy
    0x443130,  # update_track_parcels
    0x443160,  # initialize_track_parcel_slots
    0x443190,  # allocate_track_parcel_slot
    0x4431D0,  # update_track_parcel
    0x443730,  # spawn_track_parcel
    0x444CF0,  # handle_subgoldy_collisions
    0x448960,  # format_time_trial_string
)


def _resolve_function(selector: str) -> tuple[int | None, str]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = normalized.replace("unsigned __int8", "unsigned char")
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _is_auto_data_name(address: int, name: str) -> bool:
    match = re.fullmatch(r"(?:byte|word|dword|qword|unk)_([0-9A-Fa-f]+)", name)
    return match is not None and int(match.group(1), 16) == address


def _sync_galaxy_route_point_owner() -> dict[str, object]:
    address = GALAXY_ROUTE_POINT_OWNER_ADDRESS
    size = GALAXY_ROUTE_POINT_OWNER_SIZE
    next_owner = GALAXY_ROUTE_POINT_NEXT_OWNER_ADDRESS
    expected_type = _normalize_type_text(GALAXY_ROUTE_POINT_OWNER_TYPE)
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    owner_name = idc.get_name(address)
    owner_type = _normalize_type_text(idc.get_type(address))
    next_owner_head = ida_bytes.get_item_head(next_owner)

    if next_owner - address != size:
        return {
            "status": "failed",
            "reason": "invalid_checked_in_galaxy_route_point_boundary",
            "address": hex(address),
            "size": size,
            "next_owner": hex(next_owner),
        }
    if next_owner_head < next_owner:
        return {
            "status": "failed",
            "reason": "overlapping_next_galaxy_route_point_owner",
            "address": hex(address),
            "next_owner": hex(next_owner),
            "next_owner_head": hex(next_owner_head),
        }
    if owner_name != GALAXY_ROUTE_POINT_OWNER_NAME or owner_type != expected_type:
        return {
            "status": "failed",
            "reason": "unexpected_galaxy_route_point_owner",
            "address": hex(address),
            "expected_name": GALAXY_ROUTE_POINT_OWNER_NAME,
            "expected_type": expected_type,
            "observed_name": owner_name,
            "observed_type": owner_type,
            "item_head": hex(item_head),
            "item_size": item_size,
        }

    allowed_aliases = dict(GALAXY_ROUTE_POINT_INTERIOR_ALIASES)
    interior_names = {
        interior_address: idc.get_name(interior_address)
        for interior_address in range(address + 1, next_owner)
        if idc.get_name(interior_address)
    }
    unexpected_names = {
        hex(interior_address): name
        for interior_address, name in interior_names.items()
        if (
            interior_address not in allowed_aliases
            or (
                allowed_aliases[interior_address] != name
                and not _is_auto_data_name(interior_address, name)
            )
        )
    }
    if unexpected_names:
        return {
            "status": "failed",
            "reason": "unexpected_galaxy_route_point_interior_names",
            "address": hex(address),
            "interior_names": unexpected_names,
        }

    if item_head == address and item_size == size and not interior_names:
        return {
            "status": "unchanged",
            "address": hex(address),
            "name": owner_name,
            "type": owner_type,
            "item_size": item_size,
            "next_owner": hex(next_owner),
        }
    if item_head != address or item_size not in (1, 4):
        return {
            "status": "failed",
            "reason": "unexpected_galaxy_route_point_extent_head",
            "address": hex(address),
            "observed_head": hex(item_head),
            "observed_size": item_size,
            "expected_size": size,
        }

    removed_aliases = []
    generated_aliases = []
    for interior_address, expected_name in GALAXY_ROUTE_POINT_INTERIOR_ALIASES:
        observed_name = idc.get_name(interior_address)
        if not observed_name:
            continue
        if _is_auto_data_name(interior_address, observed_name):
            generated_aliases.append(
                {"address": hex(interior_address), "name": observed_name}
            )
            continue
        if observed_name != expected_name or not ida_name.del_global_name(
            interior_address
        ):
            return {
                "status": "failed",
                "reason": "galaxy_route_point_interior_name_delete_failed",
                "address": hex(interior_address),
                "expected": expected_name,
                "observed": observed_name,
            }
        replacement_name = idc.get_name(interior_address)
        if replacement_name and not _is_auto_data_name(
            interior_address, replacement_name
        ):
            return {
                "status": "failed",
                "reason": "galaxy_route_point_interior_name_delete_readback_failed",
                "address": hex(interior_address),
                "expected": expected_name,
                "observed": replacement_name,
            }
        removed_aliases.append(
            {"address": hex(interior_address), "name": observed_name}
        )
        if replacement_name:
            generated_aliases.append(
                {"address": hex(interior_address), "name": replacement_name}
            )

    if not ida_bytes.del_items(address, ida_bytes.DELIT_SIMPLE, size):
        return {
            "status": "failed",
            "reason": "delete_fragmented_galaxy_route_point_owner_failed",
            "address": hex(address),
            "size": size,
        }
    if not ida_bytes.create_byte(address, size, True):
        return {
            "status": "failed",
            "reason": "create_galaxy_route_point_owner_extent_failed",
            "address": hex(address),
            "size": size,
        }
    if idc.get_name(address) != GALAXY_ROUTE_POINT_OWNER_NAME and not idc.set_name(
        address,
        GALAXY_ROUTE_POINT_OWNER_NAME,
        ida_name.SN_NOWARN | ida_name.SN_FORCE,
    ):
        return {
            "status": "failed",
            "reason": "restore_galaxy_route_point_owner_name_failed",
            "address": hex(address),
        }
    if not idc.SetType(address, GALAXY_ROUTE_POINT_OWNER_DECLARATION):
        return {
            "status": "failed",
            "reason": "restore_galaxy_route_point_owner_type_failed",
            "address": hex(address),
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    verified_name = idc.get_name(address)
    verified_type = _normalize_type_text(idc.get_type(address))
    remaining_names = {
        hex(interior_address): idc.get_name(interior_address)
        for interior_address, _expected_name in GALAXY_ROUTE_POINT_INTERIOR_ALIASES
        if idc.get_name(interior_address)
    }
    if (
        verified_head != address
        or verified_size != size
        or verified_name != GALAXY_ROUTE_POINT_OWNER_NAME
        or verified_type != expected_type
        or remaining_names
    ):
        return {
            "status": "failed",
            "reason": "galaxy_route_point_owner_readback_failed",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(verified_head),
            "observed_size": verified_size,
            "observed_name": verified_name,
            "observed_type": verified_type,
            "remaining_interior_names": remaining_names,
        }
    return {
        "status": "applied",
        "address": hex(address),
        "name": verified_name,
        "type": verified_type,
        "item_size": verified_size,
        "removed_aliases": removed_aliases,
        "cleared_generated_aliases": generated_aliases,
        "next_owner": hex(next_owner),
    }


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _normalize_owner_member_type(value: str) -> str:
    normalized = _normalize_type_text(value) or ""
    return re.sub(r"\b(?:struct|class|union|enum)\s+", "", normalized)


def _named_struct_members(name: str) -> list[dict[str, object]] | None:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None
    return [
        {
            "offset": int(member.offset) // 8,
            "size": int(member.size) // 8,
            "name": member.name,
            "type": _normalize_owner_member_type(member.type.dstr()),
        }
        for member in members
    ]


def _time_trial_owner_readback() -> dict[str, object]:
    course_record_members = _named_struct_members("TimeTrialCourseRecord")
    selected_course_record_members = (
        []
        if course_record_members is None
        else [
            member
            for member in course_record_members
            if int(member["offset"])
            in {
                expected[0]
                for expected in TIME_TRIAL_COURSE_RECORD_EXPECTED_MEMBERS
            }
        ]
    )
    observed_course_record_members = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected_course_record_members
    )

    owner_members = _named_struct_members("TimeTrial")
    selected_owner_members = (
        []
        if owner_members is None
        else [
            member
            for member in owner_members
            if int(member["offset"])
            in {expected[0] for expected in TIME_TRIAL_EXPECTED_MEMBERS}
        ]
    )
    observed_owner_members = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected_owner_members
    )
    course_record_size = _named_struct_size("TimeTrialCourseRecord")
    owner_size = _named_struct_size("TimeTrial")
    return {
        "status": (
            "verified"
            if course_record_size == TIME_TRIAL_COURSE_RECORD_EXPECTED_SIZE
            and observed_course_record_members
            == TIME_TRIAL_COURSE_RECORD_EXPECTED_MEMBERS
            and owner_size == TIME_TRIAL_EXPECTED_SIZE
            and observed_owner_members == TIME_TRIAL_EXPECTED_MEMBERS
            else "failed"
        ),
        "course_record_size": course_record_size,
        "course_record_members": selected_course_record_members,
        "owner_size": owner_size,
        "owner_members": selected_owner_members,
        "expected_course_record_size": TIME_TRIAL_COURSE_RECORD_EXPECTED_SIZE,
        "expected_course_record_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type
            in TIME_TRIAL_COURSE_RECORD_EXPECTED_MEMBERS
        ],
        "expected_owner_size": TIME_TRIAL_EXPECTED_SIZE,
        "expected_owner_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type
            in TIME_TRIAL_EXPECTED_MEMBERS
        ],
    }


def _salt_owner_readback() -> dict[str, object]:
    members = _named_struct_members("Salt")
    selected = [] if members is None else [
        member
        for member in members
        if int(member["offset"])
        in {expected[0] for expected in SALT_OWNER_EXPECTED_MEMBERS}
    ]
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected
    )
    size = _named_struct_size("Salt")
    cursor_members = _named_struct_members("SaltStateStrideCursor")
    selected_cursor = [] if cursor_members is None else [
        member
        for member in cursor_members
        if int(member["offset"])
        in {expected[0] for expected in SALT_STATE_CURSOR_EXPECTED_MEMBERS}
    ]
    observed_cursor = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected_cursor
    )
    cursor_size = _named_struct_size("SaltStateStrideCursor")
    return {
        "status": (
            "verified"
            if size == SALT_OWNER_EXPECTED_SIZE
            and observed == SALT_OWNER_EXPECTED_MEMBERS
            and cursor_size == SALT_STATE_CURSOR_EXPECTED_SIZE
            and observed_cursor == SALT_STATE_CURSOR_EXPECTED_MEMBERS
            else "failed"
        ),
        "size": size,
        "cursor_size": cursor_size,
        "members": selected,
        "cursor_members": selected_cursor,
        "expected_size": SALT_OWNER_EXPECTED_SIZE,
        "expected_cursor_size": SALT_STATE_CURSOR_EXPECTED_SIZE,
        "expected_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SALT_OWNER_EXPECTED_MEMBERS
        ],
        "expected_cursor_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type
            in SALT_STATE_CURSOR_EXPECTED_MEMBERS
        ],
    }


def _sub_lazer_owner_readback() -> dict[str, object]:
    members = _named_struct_members("SubLazer")
    selected = [] if members is None else [
        member
        for member in members
        if int(member["offset"])
        in {expected[0] for expected in SUB_LAZER_OWNER_EXPECTED_MEMBERS}
    ]
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected
    )
    size = _named_struct_size("SubLazer")
    manager_size = _named_struct_size("SubLazerManager")
    return {
        "status": (
            "verified"
            if size == SUB_LAZER_OWNER_EXPECTED_SIZE
            and manager_size == SUB_LAZER_MANAGER_EXPECTED_SIZE
            and observed == SUB_LAZER_OWNER_EXPECTED_MEMBERS
            else "failed"
        ),
        "size": size,
        "manager_size": manager_size,
        "members": selected,
        "expected_size": SUB_LAZER_OWNER_EXPECTED_SIZE,
        "expected_manager_size": SUB_LAZER_MANAGER_EXPECTED_SIZE,
        "expected_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SUB_LAZER_OWNER_EXPECTED_MEMBERS
        ],
    }


def _sub_garbage_owner_readback() -> dict[str, object]:
    members = _named_struct_members("SubGarbage")
    selected = [] if members is None else [
        member
        for member in members
        if int(member["offset"])
        in {expected[0] for expected in SUB_GARBAGE_OWNER_EXPECTED_MEMBERS}
    ]
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected
    )
    size = _named_struct_size("SubGarbage")
    pool_size = _named_struct_size("SubGarbagePool")
    cursor_members = _named_struct_members("SubGarbageSlotCursor")
    selected_cursor = [] if cursor_members is None else [
        member
        for member in cursor_members
        if int(member["offset"])
        in {expected[0] for expected in SUB_GARBAGE_SLOT_CURSOR_EXPECTED_MEMBERS}
    ]
    observed_cursor = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected_cursor
    )
    cursor_size = _named_struct_size("SubGarbageSlotCursor")
    return {
        "status": (
            "verified"
            if size == SUB_GARBAGE_OWNER_EXPECTED_SIZE
            and pool_size == SUB_GARBAGE_POOL_EXPECTED_SIZE
            and observed == SUB_GARBAGE_OWNER_EXPECTED_MEMBERS
            and cursor_size == SUB_GARBAGE_SLOT_CURSOR_EXPECTED_SIZE
            and observed_cursor == SUB_GARBAGE_SLOT_CURSOR_EXPECTED_MEMBERS
            else "failed"
        ),
        "size": size,
        "pool_size": pool_size,
        "cursor_size": cursor_size,
        "members": selected,
        "cursor_members": selected_cursor,
        "expected_size": SUB_GARBAGE_OWNER_EXPECTED_SIZE,
        "expected_pool_size": SUB_GARBAGE_POOL_EXPECTED_SIZE,
        "expected_cursor_size": SUB_GARBAGE_SLOT_CURSOR_EXPECTED_SIZE,
        "expected_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SUB_GARBAGE_OWNER_EXPECTED_MEMBERS
        ],
        "expected_cursor_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SUB_GARBAGE_SLOT_CURSOR_EXPECTED_MEMBERS
        ],
    }


def _slug_owner_readback() -> dict[str, object]:
    members = _named_struct_members("Slug")
    selected = [] if members is None else [
        member
        for member in members
        if int(member["offset"])
        in {expected[0] for expected in SLUG_OWNER_EXPECTED_MEMBERS}
    ]
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected
    )
    cursor_members = _named_struct_members("SlugStateStrideCursor")
    selected_cursor = [] if cursor_members is None else [
        member
        for member in cursor_members
        if int(member["offset"])
        in {expected[0] for expected in SLUG_STATE_CURSOR_EXPECTED_MEMBERS}
    ]
    observed_cursor = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
        )
        for member in selected_cursor
    )
    size = _named_struct_size("Slug")
    pool_size = _named_struct_size("SlugPool")
    cursor_size = _named_struct_size("SlugStateStrideCursor")
    return {
        "status": (
            "verified"
            if size == SLUG_OWNER_EXPECTED_SIZE
            and pool_size == SLUG_POOL_EXPECTED_SIZE
            and cursor_size == SLUG_STATE_CURSOR_EXPECTED_SIZE
            and observed == SLUG_OWNER_EXPECTED_MEMBERS
            and observed_cursor == SLUG_STATE_CURSOR_EXPECTED_MEMBERS
            else "failed"
        ),
        "size": size,
        "pool_size": pool_size,
        "cursor_size": cursor_size,
        "members": selected,
        "cursor_members": selected_cursor,
        "expected_size": SLUG_OWNER_EXPECTED_SIZE,
        "expected_pool_size": SLUG_POOL_EXPECTED_SIZE,
        "expected_cursor_size": SLUG_STATE_CURSOR_EXPECTED_SIZE,
        "expected_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SLUG_OWNER_EXPECTED_MEMBERS
        ],
        "expected_cursor_members": [
            {
                "offset": offset,
                "size": member_size,
                "name": member_name,
                "type": member_type,
            }
            for offset, member_size, member_name, member_type in SLUG_STATE_CURSOR_EXPECTED_MEMBERS
        ],
    }


def _normalize_pointer_type(value: str | None) -> str:
    return (_normalize_type_text(value) or "").removeprefix("struct ")


def _sync_allocator_lvar(
    *,
    selector: str,
    definition_address: int,
    accepted_names: set[str],
    accepted_types: set[str],
    target_name: str,
    target_struct_name: str,
) -> dict[str, object]:
    """Persist one exact borrowed-cursor relationship in an allocator."""
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    ida_hexrays.mark_cfunc_dirty(address, True)
    normalized_accepted_types = {
        _normalize_pointer_type(value) for value in accepted_types
    }
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and _normalize_pointer_type(str(lvar.type()))
        in normalized_accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_allocator_lvar_candidates",
            "selector": selector,
            "definition_address": hex(definition_address),
            "target_name": target_name,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    target_pointer_type = _normalize_pointer_type(f"{target_struct_name} *")
    if (
        lvar.name == target_name
        and _normalize_pointer_type(str(lvar.type())) == target_pointer_type
    ):
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_struct_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_allocator_lvar_type",
            "selector": selector,
            "target_struct_name": target_struct_name,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(target_type):
        return {
            "status": "failed",
            "reason": "create_allocator_pointer_type_failed",
            "selector": selector,
            "target_struct_name": target_struct_name,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_allocator_lvar_failed",
            "selector": selector,
            "target_name": target_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and not candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.name == target_name
        and _normalize_pointer_type(str(candidate.type())) == target_pointer_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "allocator_lvar_readback_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "target_name": target_name,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
    }


def _sync_world_initializer_stack_pointer_lvars() -> dict[str, object]:
    """Batch exact field-stride views in the giant world initializer."""
    specs = (BANNER_INITIALIZER_LVAR, *PRESENTATION_ANIMATION_CURSOR_LVARS)
    selectors = {str(spec["selector"]) for spec in specs}
    if len(selectors) != 1:
        return {
            "status": "failed",
            "reason": "world_initializer_selector_mismatch",
            "selectors": sorted(selectors),
        }
    selector = selectors.pop()
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    pending = []
    results = []
    for spec in specs:
        definition_address = int(spec["definition_address"])
        stack_offset = int(spec["stack_offset"])
        accepted_names = set(spec["accepted_names"])
        accepted_types = {
            _normalize_pointer_type(value) for value in spec["accepted_types"]
        }
        target_name = str(spec["target_name"])
        target_struct_name = str(spec["target_struct_name"])
        target_pointer_type = _normalize_pointer_type(f"{target_struct_name} *")
        candidates = [
            lvar
            for lvar in cfunc.get_lvars()
            if not lvar.is_arg_var
            and lvar.is_stk_var()
            and lvar.defea == definition_address
            and lvar.get_stkoff() == stack_offset
            and lvar.name in accepted_names
            and _normalize_pointer_type(str(lvar.type())) in accepted_types
        ]
        if len(candidates) != 1:
            return {
                "status": "failed",
                "reason": "unexpected_world_initializer_lvar_candidates",
                "selector": selector,
                "target_name": target_name,
                "definition_address": hex(definition_address),
                "stack_offset": stack_offset,
                "candidate_count": len(candidates),
            }

        lvar = candidates[0]
        if (
            lvar.name == target_name
            and _normalize_pointer_type(str(lvar.type())) == target_pointer_type
        ):
            results.append(
                {
                    "status": "unchanged",
                    "name": lvar.name,
                    "type": str(lvar.type()),
                    "definition_address": hex(lvar.defea),
                    "stack_offset": lvar.get_stkoff(),
                }
            )
            continue

        target_type = ida_typeinf.tinfo_t()
        if not target_type.get_named_type(
            None,
            target_struct_name,
            ida_typeinf.BTF_STRUCT,
        ):
            return {
                "status": "failed",
                "reason": "missing_world_initializer_lvar_type",
                "selector": selector,
                "target_name": target_name,
                "target_struct_name": target_struct_name,
            }
        pointer_type = ida_typeinf.tinfo_t()
        if not pointer_type.create_ptr(target_type):
            return {
                "status": "failed",
                "reason": "create_world_initializer_pointer_type_failed",
                "selector": selector,
                "target_name": target_name,
                "target_struct_name": target_struct_name,
            }
        pending.append(
            {
                "lvar": lvar,
                "target_name": target_name,
                "pointer_type": pointer_type,
                "target_pointer_type": target_pointer_type,
                "definition_address": definition_address,
                "stack_offset": stack_offset,
                "before_name": lvar.name,
                "before_type": str(lvar.type()),
            }
        )

    for update in pending:
        lvar = update["lvar"]
        info = ida_hexrays.lvar_saved_info_t()
        info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
        info.name = update["target_name"]
        info.type = update["pointer_type"]
        if not ida_hexrays.modify_user_lvar_info(
            address,
            ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
            info,
        ):
            return {
                "status": "failed",
                "reason": "modify_world_initializer_lvar_failed",
                "selector": selector,
                "target_name": update["target_name"],
            }

    if pending:
        ida_hexrays.mark_cfunc_dirty(address, True)
        cfunc = ida_hexrays.decompile(address)
    for update in pending:
        verified = [
            candidate
            for candidate in cfunc.get_lvars()
            if not candidate.is_arg_var
            and candidate.is_stk_var()
            and candidate.defea == update["definition_address"]
            and candidate.get_stkoff() == update["stack_offset"]
            and candidate.name == update["target_name"]
            and _normalize_pointer_type(str(candidate.type()))
            == update["target_pointer_type"]
        ]
        if len(verified) != 1:
            return {
                "status": "failed",
                "reason": "world_initializer_lvar_readback_failed",
                "selector": selector,
                "target_name": update["target_name"],
                "definition_address": hex(update["definition_address"]),
                "stack_offset": update["stack_offset"],
                "candidate_count": len(verified),
            }
        results.append(
            {
                "status": "applied",
                "before_name": update["before_name"],
                "before_type": update["before_type"],
                "name": verified[0].name,
                "type": str(verified[0].type()),
                "definition_address": hex(verified[0].defea),
                "stack_offset": verified[0].get_stkoff(),
            }
        )

    result_by_name = {str(result["name"]): result for result in results}
    ordered_results = [
        result_by_name[str(spec["target_name"])]
        for spec in specs
    ]
    return {
        "status": "applied" if pending else "unchanged",
        "selector": selector,
        "locals": ordered_results,
    }


SPAWN_SLUG_HAZARD_LVAR_SPECS = (
    (
        "state_stride_cursor",
        0x43DC89,
        {"i", "slug_state_cursor"},
        {
            "_DWORD *",
            "int *",
            "int32_t *",
            "unsigned int *",
            "SlugStateStrideCursor *",
        },
        "slug_state_cursor",
        "SlugStateStrideCursor",
    ),
    (
        "selected_slot_cursor",
        0x43DCBD,
        {"v6", "slug_slot_cursor"},
        {"int", "char *", "void *", "SlugSlotCursor *"},
        "slug_slot_cursor",
        "SlugSlotCursor",
    ),
    (
        "sprite",
        0x43DDC8,
        {"sprite"},
        {"_DWORD *", "Sprite *"},
        "sprite",
        "Sprite",
    ),
)

SPAWN_SALT_HAZARD_LVAR_SPECS = (
    (
        "state_stride_cursor",
        0x441564,
        {"i", "salt_state_cursor"},
        {
            "_DWORD *",
            "int *",
            "int32_t *",
            "unsigned int *",
            "SaltState *",
            "SaltStateStrideCursor *",
        },
        "salt_state_cursor",
        "SaltStateStrideCursor",
    ),
)

SPAWN_GARBAGE_HAZARD_LVAR_SPECS = (
    (
        "selected_slot_cursor",
        0x43DAC5,
        {"v6", "garbage_slot_cursor"},
        {"char *", "void *", "SubGarbageSlotCursor *"},
        "garbage_slot_cursor",
        "SubGarbageSlotCursor",
    ),
)


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_CANONICAL_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "applied": 0,
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [
                        {
                            "reason": "noncanonical_subgame_runtime_header",
                            "detail": (
                                "refusing to replace the recovered SubgameRuntime owner "
                                "with a sparse compatibility header"
                            ),
                        }
                    ],
                },
                indent=2,
            )
        )
        return 1

    contact_header_path = header_path.with_name("contact_target_types.h")
    contact_parse_errors = idc.parse_decls(str(contact_header_path), idc.PT_FILE)
    parse_errors = contact_parse_errors + idc.parse_decls(str(header_path), idc.PT_FILE)
    parcel_owner_sizes = {
        name: _named_struct_size(name) for name in EXPECTED_PARCEL_OWNER_SIZES
    }
    banner_owner_sizes = {
        name: _named_struct_size(name) for name in BANNER_OWNER_EXPECTED_SIZES
    }
    presentation_animation_cursor_sizes = {
        name: _named_struct_size(name)
        for name in PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES
    }
    sub_lazer_body_object_cursor_size = _named_struct_size(
        "SubLazerBodyObjectStrideCursor"
    )
    salt_owner_game_cursor_size = _named_struct_size(
        "SaltOwnerGameStrideCursor"
    )
    size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": parcel_owner_sizes[name],
        }
        for name, expected_size in EXPECTED_PARCEL_OWNER_SIZES.items()
        if parcel_owner_sizes[name] != expected_size
    ]
    help_owner_size = _named_struct_size("Help")
    if help_owner_size != HELP_OWNER_EXPECTED_SIZE:
        size_failures.append(
            {
                "selector": "Help",
                "reason": "owner_size_mismatch",
                "expected": HELP_OWNER_EXPECTED_SIZE,
                "observed": help_owner_size,
            }
        )
    size_failures.extend(
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": banner_owner_sizes[name],
        }
        for name, expected_size in BANNER_OWNER_EXPECTED_SIZES.items()
        if banner_owner_sizes[name] != expected_size
    )
    size_failures.extend(
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": presentation_animation_cursor_sizes[name],
        }
        for name, expected_size in (
            PRESENTATION_ANIMATION_CURSOR_EXPECTED_SIZES.items()
        )
        if presentation_animation_cursor_sizes[name] != expected_size
    )
    if (
        sub_lazer_body_object_cursor_size
        != SUB_LAZER_BODY_OBJECT_CURSOR_EXPECTED_SIZE
    ):
        size_failures.append(
            {
                "selector": "SubLazerBodyObjectStrideCursor",
                "reason": "owner_size_mismatch",
                "expected": SUB_LAZER_BODY_OBJECT_CURSOR_EXPECTED_SIZE,
                "observed": sub_lazer_body_object_cursor_size,
            }
        )
    if salt_owner_game_cursor_size != SALT_OWNER_GAME_CURSOR_EXPECTED_SIZE:
        size_failures.append(
            {
                "selector": "SaltOwnerGameStrideCursor",
                "reason": "owner_size_mismatch",
                "expected": SALT_OWNER_GAME_CURSOR_EXPECTED_SIZE,
                "observed": salt_owner_game_cursor_size,
            }
        )
    if parse_errors or size_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "parcel_owner_sizes": parcel_owner_sizes,
                    "help_owner_size": help_owner_size,
                    "banner_owner_sizes": banner_owner_sizes,
                    "presentation_animation_cursor_sizes": (
                        presentation_animation_cursor_sizes
                    ),
                    "sub_lazer_body_object_cursor_size": (
                        sub_lazer_body_object_cursor_size
                    ),
                    "salt_owner_game_cursor_size": salt_owner_game_cursor_size,
                    "failed": size_failures,
                },
                indent=2,
            )
        )
        return 1

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        current_name = idc.get_name(address)
        if current_name == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "reason": "rename_failed",
                }
            )
            continue
        if idc.get_name(address) != name:
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "observed": idc.get_name(address),
                    "reason": "rename_readback_failed",
                }
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue

        applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected_observed = _data_declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_data_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue

        applied += 1

    galaxy_route_point_owner = _sync_galaxy_route_point_owner()
    if galaxy_route_point_owner["status"] == "failed":
        failed.append(
            {
                "selector": GALAXY_ROUTE_POINT_OWNER_NAME,
                "owner_readback": galaxy_route_point_owner,
            }
        )

    world_initializer_stack_pointer_lvars = (
        _sync_world_initializer_stack_pointer_lvars()
    )
    if world_initializer_stack_pointer_lvars.get("status") == "failed":
        banner_initializer_lvar = world_initializer_stack_pointer_lvars
        presentation_animation_cursor_lvars = (
            world_initializer_stack_pointer_lvars
        )
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "lvars": "world_initializer_stack_pointer_lvars",
                "result": world_initializer_stack_pointer_lvars,
            }
        )
    else:
        initializer_locals = world_initializer_stack_pointer_lvars["locals"]
        banner_initializer_lvar = initializer_locals[0]
        animation_locals = initializer_locals[1:]
        presentation_animation_cursor_lvars = {
            "status": (
                "applied"
                if any(local["status"] == "applied" for local in animation_locals)
                else "unchanged"
            ),
            "selector": "initialize_game_assets_and_world",
            "locals": animation_locals,
        }
        applied += sum(
            local["status"] == "applied"
            for local in initializer_locals
        )
        unchanged += sum(
            local["status"] == "unchanged"
            for local in initializer_locals
        )

    sub_lazer_startup_cursor_lvar = _sync_allocator_lvar(
        selector=str(SUB_LAZER_STARTUP_CURSOR_LVAR["selector"]),
        definition_address=int(
            SUB_LAZER_STARTUP_CURSOR_LVAR["definition_address"]
        ),
        accepted_names=set(SUB_LAZER_STARTUP_CURSOR_LVAR["accepted_names"]),
        accepted_types=set(SUB_LAZER_STARTUP_CURSOR_LVAR["accepted_types"]),
        target_name=str(SUB_LAZER_STARTUP_CURSOR_LVAR["target_name"]),
        target_struct_name=str(
            SUB_LAZER_STARTUP_CURSOR_LVAR["target_struct_name"]
        ),
    )
    if sub_lazer_startup_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "sub_lazer_startup_cursor_lvar": sub_lazer_startup_cursor_lvar,
            }
        )
    elif sub_lazer_startup_cursor_lvar.get("status") == "applied":
        applied += 1
    else:
        unchanged += 1

    salt_startup_cursor_lvar = _sync_allocator_lvar(
        selector=str(SALT_STARTUP_CURSOR_LVAR["selector"]),
        definition_address=int(SALT_STARTUP_CURSOR_LVAR["definition_address"]),
        accepted_names=set(SALT_STARTUP_CURSOR_LVAR["accepted_names"]),
        accepted_types=set(SALT_STARTUP_CURSOR_LVAR["accepted_types"]),
        target_name=str(SALT_STARTUP_CURSOR_LVAR["target_name"]),
        target_struct_name=str(SALT_STARTUP_CURSOR_LVAR["target_struct_name"]),
    )
    if salt_startup_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "salt_startup_cursor_lvar": salt_startup_cursor_lvar,
            }
        )
    elif salt_startup_cursor_lvar.get("status") == "applied":
        applied += 1
    else:
        unchanged += 1

    garbage_allocator_lvars = {}
    for (
        result_name,
        definition_address,
        accepted_names,
        accepted_types,
        target_name,
        target_struct_name,
    ) in SPAWN_GARBAGE_HAZARD_LVAR_SPECS:
        result = _sync_allocator_lvar(
            selector="spawn_track_garbage_hazard",
            definition_address=definition_address,
            accepted_names=accepted_names,
            accepted_types=accepted_types,
            target_name=target_name,
            target_struct_name=target_struct_name,
        )
        garbage_allocator_lvars[result_name] = result
        if result.get("status") == "applied":
            applied += 1
        elif result.get("status") == "unchanged":
            unchanged += 1
        else:
            failed.append(
                {
                    "selector": "spawn_track_garbage_hazard",
                    "lvar": result_name,
                    "result": result,
                }
            )

    slug_allocator_lvars = {}
    for (
        result_name,
        definition_address,
        accepted_names,
        accepted_types,
        target_name,
        target_struct_name,
    ) in SPAWN_SLUG_HAZARD_LVAR_SPECS:
        result = _sync_allocator_lvar(
            selector="spawn_slug_hazard",
            definition_address=definition_address,
            accepted_names=accepted_names,
            accepted_types=accepted_types,
            target_name=target_name,
            target_struct_name=target_struct_name,
        )
        slug_allocator_lvars[result_name] = result
        if result.get("status") == "applied":
            applied += 1
        elif result.get("status") == "unchanged":
            unchanged += 1
        else:
            failed.append(
                {
                    "selector": "spawn_slug_hazard",
                    "lvar": result_name,
                    "result": result,
                }
            )

    salt_allocator_lvars = {}
    for (
        result_name,
        definition_address,
        accepted_names,
        accepted_types,
        target_name,
        target_struct_name,
    ) in SPAWN_SALT_HAZARD_LVAR_SPECS:
        result = _sync_allocator_lvar(
            selector="spawn_salt_hazard",
            definition_address=definition_address,
            accepted_names=accepted_names,
            accepted_types=accepted_types,
            target_name=target_name,
            target_struct_name=target_struct_name,
        )
        salt_allocator_lvars[result_name] = result
        if result.get("status") == "applied":
            applied += 1
        elif result.get("status") == "unchanged":
            unchanged += 1
        else:
            failed.append(
                {
                    "selector": "spawn_salt_hazard",
                    "lvar": result_name,
                    "result": result,
                }
            )

    game_root_owner_graph = sync_game_root_owner_graph(require=True)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
        )

    time_trial_owner_readback = _time_trial_owner_readback()
    if time_trial_owner_readback["status"] != "verified":
        failed.append(
            {
                "selector": "TimeTrial",
                "owner_readback": time_trial_owner_readback,
            }
        )

    salt_owner_readback = _salt_owner_readback()
    if salt_owner_readback["status"] != "verified":
        failed.append({"selector": "Salt", "owner_readback": salt_owner_readback})

    sub_lazer_owner_readback = _sub_lazer_owner_readback()
    if sub_lazer_owner_readback["status"] != "verified":
        failed.append(
            {"selector": "SubLazer", "owner_readback": sub_lazer_owner_readback}
        )

    sub_garbage_owner_readback = _sub_garbage_owner_readback()
    if sub_garbage_owner_readback["status"] != "verified":
        failed.append(
            {"selector": "SubGarbage", "owner_readback": sub_garbage_owner_readback}
        )

    slug_owner_readback = _slug_owner_readback()
    if slug_owner_readback["status"] != "verified":
        failed.append(
            {"selector": "Slug", "owner_readback": slug_owner_readback}
        )

    reanalyzed = []
    for address in REANALYSIS_FUNCTIONS:
        function = ida_funcs.get_func(address)
        if function is None:
            failed.append(
                {
                    "selector": hex(address),
                    "reason": "missing_reanalysis_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(function.start_ea, True)
        reanalyzed.append(
            {
                "address": hex(function.start_ea),
                "name": idc.get_func_name(function.start_ea),
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "contact_header": str(contact_header_path),
                "parcel_owner_sizes": parcel_owner_sizes,
                "banner_owner_sizes": banner_owner_sizes,
                "presentation_animation_cursor_sizes": (
                    presentation_animation_cursor_sizes
                ),
                "sub_lazer_body_object_cursor_size": (
                    sub_lazer_body_object_cursor_size
                ),
                "salt_owner_game_cursor_size": salt_owner_game_cursor_size,
                "time_trial_owner_readback": time_trial_owner_readback,
                "salt_owner_readback": salt_owner_readback,
                "sub_lazer_owner_readback": sub_lazer_owner_readback,
                "sub_garbage_owner_readback": sub_garbage_owner_readback,
                "slug_owner_readback": slug_owner_readback,
                "type_sizes": {
                    "SubgameRuntime": _named_struct_size("SubgameRuntime"),
                    "TimeTrialCourseRecord": _named_struct_size(
                        "TimeTrialCourseRecord"
                    ),
                    "TimeTrial": _named_struct_size("TimeTrial"),
                    "SubRingStar": _named_struct_size("SubRingStar"),
                    "SubRing": _named_struct_size("SubRing"),
                    "SubRingPool": _named_struct_size("SubRingPool"),
                    "SlugStateStrideCursor": _named_struct_size("SlugStateStrideCursor"),
                    "SlugSlotCursor": _named_struct_size("SlugSlotCursor"),
                    "EnemyManager": _named_struct_size("EnemyManager"),
                    "GUI": _named_struct_size("GUI"),
                    "Help": _named_struct_size("Help"),
                    "ThanksScreen": _named_struct_size("ThanksScreen"),
                    "Galaxy": _named_struct_size("Galaxy"),
                    "Parcel": _named_struct_size("Parcel"),
                    "ParcelManager": _named_struct_size("ParcelManager"),
                    "Completion": _named_struct_size("Completion"),
                    "TimesUp": _named_struct_size("TimesUp"),
                    "SubLazer": _named_struct_size("SubLazer"),
                    "SubLazerManager": _named_struct_size("SubLazerManager"),
                    "SubLazerBodyObjectStrideCursor": _named_struct_size(
                        "SubLazerBodyObjectStrideCursor"
                    ),
                    "SaltOwnerGameStrideCursor": _named_struct_size(
                        "SaltOwnerGameStrideCursor"
                    ),
                    "SubGarbage": _named_struct_size("SubGarbage"),
                    "SubGarbagePool": _named_struct_size("SubGarbagePool"),
                    "SubGarbageSlotCursor": _named_struct_size(
                        "SubGarbageSlotCursor"
                    ),
                    "Slug": _named_struct_size("Slug"),
                    "SlugPool": _named_struct_size("SlugPool"),
                    "Salt": _named_struct_size("Salt"),
                    "SaltManager": _named_struct_size("SaltManager"),
                    "SaltStateStrideCursor": _named_struct_size(
                        "SaltStateStrideCursor"
                    ),
                    "BannerInitStrideView": _named_struct_size(
                        "BannerInitStrideView"
                    ),
                    "PresentationAnimationObjectStrideCursor": (
                        _named_struct_size(
                            "PresentationAnimationObjectStrideCursor"
                        )
                    ),
                },
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "reanalyzed": reanalyzed,
                "galaxy_route_point_owner": galaxy_route_point_owner,
                "game_root_owner_graph": game_root_owner_graph,
                "garbage_allocator_lvars": garbage_allocator_lvars,
                "slug_allocator_lvars": slug_allocator_lvars,
                "salt_allocator_lvars": salt_allocator_lvars,
                "banner_initializer_lvar": banner_initializer_lvar,
                "presentation_animation_cursor_lvars": (
                    presentation_animation_cursor_lvars
                ),
                "sub_lazer_startup_cursor_lvar": sub_lazer_startup_cursor_lvar,
                "salt_startup_cursor_lvar": salt_startup_cursor_lvar,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if parse_errors or failed or missing:
        return 1
    return 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_subgame_runtime_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
