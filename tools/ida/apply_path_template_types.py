import json
import pathlib
import re
import sys

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

from game_root_owner import sync_game_root_owner_graph
from type_alias_migration import migrate_equivalent_struct_aliases

REPLAY_START_CURSOR_FIELD_SPECS = (
    ("Player", 0x4364, 0x304, ("startup_track_index", "replay_start_cursor")),
    ("SubSolution", 0x1FAC0, 0x24, ("source_tail", "replay_start_cursor")),
    (
        "CompactHighScoreRecord",
        0x8C,
        0x24,
        ("source_tail", "replay_start_cursor"),
    ),
)
REPLAY_START_CURSOR_RUNTIME_OWNER_SIZE = 0x1272838
REPLAY_START_CURSOR_RUNTIME_OFFSET = 0x3BBA68
REPLAY_START_CURSOR_PLAYER_OFFSET = 0x3BB764


TRUSTED_NAMES = [
    (0x4034D0, "update_input_ok"),
    (0x403560, "initialize_input_ok"),
    (0x404030, "update_twinkle_manager"),
    (0x404070, "draw_twinkle"),
    (0x404080, "update_twinkle"),
    (0x404580, "border_mouse_test"),
    (0x408040, "initialize_noop_renderable_bod"),
    (0x408060, "initialize_runtime_pools_and_path_template_bank"),
    (0x4084B0, "initialize_track_speedup_runtime"),
    (0x4084D0, "initialize_track_jetpack_pickup_runtime"),
    (0x408510, "initialize_track_health_pickup_runtime"),
    (0x408590, "initialize_track_row_runtime"),
    (0x4085E0, "initialize_active_bod"),
    (0x408650, "initialize_fringe_object"),
    (0x4086D0, "initialize_player_presentation_controller"),
    (0x4113B0, "add_bod_to_front"),
    (0x411420, "append_bod_to_end"),
    (0x43A010, "health_collect_particles"),
    (0x43A1A0, "set_subgoldy_shoot_flags"),
    (0x43A300, "shoot_subgoldy"),
    (0x43A370, "end_jetpack_hover"),
    (0x4182E0, "reset_landscape_manager"),
    (0x4182F0, "load_landscape_script_by_name"),
    (0x41B0A0, "get_path_nodes"),
    (0x421770, "initialize_path_follow_golb"),
    (0x4217B0, "traverse_path_follow_golb"),
    (0x421DC0, "mirror_path"),
    (0x429AE0, "find_segment_path_index_by_name"),
    (0x42B9C0, "get_path_position_at_node"),
    (0x42C600, "calc_path_length_z"),
    (0x42CA90, "is_point_inside_track_attachment"),
    (0x42F6E0, "initialize_object_constructor_thunk"),
    (0x42F5C0, "is_bod_after_sprites"),
    (0x42F5D0, "set_bod_object"),
    (0x42F5F0, "initialize_bod_base"),
    (0x42F650, "initialize_renderable_bod"),
    (0x42F680, "apply_bod_position"),
    (0x433060, "initialize_track_render_cache_manager"),
    (0x433220, "build_track_render_caches"),
    (0x433830, "add_track_cache_vertex"),
    (0x433960, "append_track_cache_object"),
    (0x433B30, "update_track_render_cache_rows"),
    (0x433E80, "update_active_bod"),
    (0x433F20, "remove_track_render_cache_bods"),
    (0x433FD0, "initialize_thanks_for_playing_screen"),
    (0x4340C0, "uninit_thanks_screen"),
    (0x4340F0, "update_thanks_for_playing_screen"),
    (0x434B60, "is_neighbor_cell_solid"),
    (0x437E80, "calc_slider_to_rate"),
    (0x439B00, "refresh_fringe_object_draw_list"),
    (0x43A390, "update_jetpack_gauge"),
    (0x43A580, "uninit_jet_particles"),
    (0x43A5B0, "initialize_jet_particles"),
    (0x43A690, "update_jet_particles"),
    (0x43A930, "initialize_jetpack_gauge"),
    (0x43A980, "arm_jetpack_gauge"),
    (0x43A9C0, "initialize_subgoldy"),
    (0x43AF10, "show_subgoldy_lives"),
    (0x43AF60, "begin_post_follow_carryover"),
    (0x43AFD0, "play_subgoldy_shoot_sfx"),
    (0x43B120, "update_subgoldy"),
    (0x43D230, "initialize_subgoldy_ghost"),
    (0x43D3D0, "set_subgoldy_ghost_z"),
    (0x43D410, "get_track_grid_cell_at_world_position"),
    (0x43D480, "get_track_runtime_cell_at_world_z"),
    (0x43D4D0, "sample_track_floor_height_at_position"),
    (0x43F5C0, "initialize_slug_voice_manager"),
    (0x43F5E0, "update_slug_voice_manager"),
    (0x4403A0, "clear_subgoldy_score_buckets"),
    (0x4404D0, "calc_subgame_rate"),
    (0x4408A0, "advance_blink_random"),
    (0x4408C0, "initialize_blink_random"),
    (0x440F80, "update_barrier_ai"),
    (0x440FA0, "initialize_damage_gauge"),
    (0x440FD0, "update_damage_gauge"),
    (0x4413F0, "apply_damage_gauge_delta"),
    (0x442500, "initialize_vapour"),
    (0x442540, "reset_vapour"),
    (0x442560, "add_vapour_point"),
    (0x4425F0, "update_vapour"),
    (0x4428D0, "update_snail_presentation"),
    (0x442E40, "release_snail_weapons"),
    (0x444600, "dispatch_cutscene_animation"),
    (0x4446E0, "set_weapon_animation"),
    (0x444960, "initialize_squidge"),
    (0x444980, "start_squidge_y"),
    (0x4449A0, "start_squidge_z"),
    (0x4449C0, "update_squidge"),
    (0x445840, "kill_subgoldy"),
    (0x445F10, "hide_gameplay_scores"),
    (0x445F40, "unhide_gameplay_scores"),
    (0x445CD0, "build_snail_world_hotspots"),
    (0x445D50, "extract_snail_local_hotspots"),
    (0x446E80, "initialize_warning"),
    (0x446F10, "uninit_warning"),
    (0x446F30, "start_warning"),
    (0x446F50, "stop_warning"),
    (0x446F60, "stop_warning_sample"),
    (0x446F80, "update_warning"),
    (0x447090, "initialize_fringe_manager"),
    (0x4470A0, "allocate_fringe_object"),
    (0x447290, "recycle_bod_to_free_list"),
    (0x44C870, "initialize_global_identity_matrix_thunk"),
    (0x44C880, "initialize_global_identity_matrix"),
    (0x44CAC0, "multiply_vector_by_matrix_copy"),
    (0x44CB50, "dot_vectors"),
    (0x44CB70, "dot_vector"),
    (0x44CB90, "multiply_vector_by_matrix"),
    (0x44CC20, "rotate_vector_by_matrix"),
    (0x44CCA0, "normalize_vector"),
    (0x44CCF0, "vector_magnitude"),
    (0x44CD20, "normalize_vector_from_source"),
    (0x44CD40, "cross_vectors"),
    (0x44CDE0, "initialize_uniform_scale_matrix"),
    (0x44CE30, "rotate_matrix_local_x"),
    (0x44CEC0, "rotate_matrix_local_y"),
    (0x44CF50, "rotate_matrix_local_z"),
    (0x44CFE0, "initialize_matrix_from_values"),
    (0x44D060, "multiply_matrices"),
    (0x44D1A0, "multiply_matrix_assign"),
    (0x44D1D0, "multiply_matrix"),
    (0x44D1E0, "premultiply_matrix_in_place"),
    (0x44D530, "initialize_quaternion_from_axis"),
    (0x44D580, "initialize_axis_from_quaternion"),
    (0x44D5D0, "initialize_quaternion_from_matrix"),
    (0x44D820, "initialize_matrix_from_quaternion"),
    (0x44D920, "interpolate_matrix_rotation"),
    (0x4533C4, "d3dx_create_texture_from_file_in_memory_ex"),
    (0x453404, "d3dx_create_texture_from_file_ex"),
    (0x453467, "d3dx_create_texture_from_file"),
    (0x4AC5C8, "g_default_tip_message"),
    (0x4972B0, "g_noop_runtime_callback_table"),
    (0x4972F8, "g_face_callback_table"),
    (0x497314, "g_sub_speed_up_vtable"),
    (0x497318, "g_jet_pack_vtable"),
    (0x49731C, "g_vapour_vtable"),
    (0x497320, "g_sub_health_vtable"),
    (0x497338, "g_active_bod_vtable"),
    (0x4974FC, "g_bod_base_vtable"),
    (0x497500, "g_renderable_bod_vtable"),
    (0x497330, "g_row_model_vtable"),
    (0x497344, "g_fringe_vtable"),
    (0x497354, "g_player_presentation_noop_vtable"),
    (0x497358, "g_invincible_shell_update_vtable"),
    (0x49735C, "g_weapon_noop_vtable"),
    (0x50331C, "g_bod_base_init_count"),
    (0x503280, "g_loading_bar_on_texture"),
    (0x503284, "g_loading_background_vertex_buffer"),
    (0x503288, "g_loading_background_texture"),
    (0x503290, "g_loading_bar"),
    (0x5032A4, "g_loading_bar_vertex_buffer"),
    (0x643190, "g_subgoldy_ghost_z"),
    (0x643194, "g_replay_accum_z"),
]

TRUSTED_DATA_DECLARATIONS = [
    (
        0x4972B0,
        "g_noop_runtime_callback_table",
        "void *g_noop_runtime_callback_table;",
    ),
    (0x4972F8, "g_face_callback_table", "void *g_face_callback_table;"),
    (0x497314, "g_sub_speed_up_vtable", "void *g_sub_speed_up_vtable;"),
    (0x497318, "g_jet_pack_vtable", "void *g_jet_pack_vtable;"),
    (0x49731C, "g_vapour_vtable", "void *g_vapour_vtable;"),
    (0x497320, "g_sub_health_vtable", "void *g_sub_health_vtable;"),
    (0x497344, "g_fringe_vtable", "void *g_fringe_vtable;"),
    (0x497338, "g_active_bod_vtable", "void *g_active_bod_vtable;"),
    (0x4974FC, "g_bod_base_vtable", "void *g_bod_base_vtable;"),
    (0x497500, "g_renderable_bod_vtable", "void *g_renderable_bod_vtable;"),
    (0x50331C, "g_bod_base_init_count", "int32_t g_bod_base_init_count;"),
    (0x4AC5C8, "g_default_tip_message", "cRTipData g_default_tip_message;"),
    (
        0x503280,
        "g_loading_bar_on_texture",
        "Direct3DTexture8 *g_loading_bar_on_texture;",
    ),
    (
        0x503284,
        "g_loading_background_vertex_buffer",
        "ObjectRenderBuffers *g_loading_background_vertex_buffer;",
    ),
    (
        0x503288,
        "g_loading_background_texture",
        "Direct3DTexture8 *g_loading_background_texture;",
    ),
    (0x503290, "g_loading_bar", "cRLoadingBar g_loading_bar;"),
    (
        0x5032A4,
        "g_loading_bar_vertex_buffer",
        "ObjectRenderBuffers *g_loading_bar_vertex_buffer;",
    ),
    (0x643190, "g_subgoldy_ghost_z", "float g_subgoldy_ghost_z;"),
    (0x643194, "g_replay_accum_z", "float g_replay_accum_z;"),
]

TRACK_RENDER_CACHE_OWNER_MARKERS = (
    "typedef struct TrackRenderCacheSlot {",
    "BodBase bod;",
    "float cache_row_base;",
    "typedef struct SegmentCache {",
    "cRSubGame* owner_subgame;",
    "TrackRenderCacheSlot slots[0x8f][5];",
    "void __thiscall initialize_track_render_cache_manager(SegmentCache* manager);",
    "void __thiscall build_track_render_caches(",
    "void __thiscall update_track_render_cache_rows(SegmentCache* manager);",
    "void __thiscall remove_track_render_cache_bods(SegmentCache* manager);",
)

SUB_LOC_OWNER_MARKERS = (
    "typedef struct cRSubLoc cRSubLoc;",
    "typedef cRSubLoc SubLoc;",
    "typedef cRSubLoc TrackRowCell;",
    "typedef struct cRSubLoc {",
    "} cRSubLoc;",
    "cRSubLoc_must_be_0x54",
    "cRSubLoc runtime_cells[3200][8];",
    "cRSubLoc* __thiscall initialize_sub_loc(cRSubLoc* cell);",
    "void __thiscall remove_sub_loc(cRSubLoc* cell);",
    "void __thiscall update_sub_loc(cRSubLoc* cell);",
    "int32_t __thiscall get_track_cell_row_index(cRSubLoc* cell);",
)

SUB_LOC_OWNER_SIZES = {
    "cRSubLoc": 0x54,
}

SUBGAME_OWNER_MARKERS = (
    "typedef struct cRSubGame cRSubGame;",
    "typedef cRSubGame SubgameRuntime;",
    "typedef struct cRSubGame {",
    "} cRSubGame;",
    "cRSubLoc runtime_cells[3200][8];",
    "SubRow runtime_rows[3200];",
    "cRSubGame* __thiscall initialize_runtime_pools_and_path_template_bank(",
    "void __thiscall populate_runtime_track_cells_from_segments(cRSubGame* game);",
    "void __thiscall initialize_subgame(cRSubGame* game);",
    "void __thiscall build_subgame_level(cRSubGame* game, int32_t level_index);",
)

SUBGAME_OWNER_SIZES = {
    "cRSubGame": 0x1272838,
}

PATH_OWNER_MARKERS = (
    "typedef struct cRPath {",
    "} cRPath;",
    "typedef cRPath Path;",
    "cRPath primary;",
    "cRPath secondary;",
    "struct cRPath* attachment_template_record;",
    "cRPath* template_record;",
    "void __fastcall get_path_nodes(cRPath* self);",
    "void __thiscall mirror_path(cRPath* self, cRPath* source);",
)

PATH_OWNER_SIZES = {
    "cRPath": 0xA8,
    "PathPair": 0x150,
}

PATH_MANAGER_OWNER_MARKERS = (
    "typedef struct cRPathManager {",
    "} cRPathManager;",
    "typedef cRPathManager PathManager;",
    "cRPathManager path_manager;",
    "int32_t __thiscall find_segment_path_index_by_name(",
    "cRPathManager* manager,",
)

PATH_MANAGER_OWNER_SIZES = {
    "cRPathManager": 0x1,
}

BOD_CORE_OWNER_MARKERS = (
    "BodNode_must_be_0x10",
    "BodList_must_be_0x0c",
    "BodBase_must_be_0x38",
    "RenderableBod_must_be_0x80",
    "int32_t frame_number;",
    "void __thiscall add_bod_to_front(BodList* list, BodNode* node);",
    "void __thiscall append_bod_to_end(BodList* list, BodNode* node);",
    "bool __thiscall is_bod_after_sprites(BodBase* bod);",
    "void __thiscall recycle_bod_to_free_list(BodList* list, BodNode* node);",
)

BOD_CORE_OWNER_SIZES = {
    "BodNode": 0x10,
    "BodList": 0x0C,
    "BodBase": 0x38,
    "RenderableBod": 0x80,
}

FRINGE_OWNER_MARKERS = (
    "cRFringe_must_be_0x38",
    "cRFringeManager_must_be_0x5fb44",
    "cRFringe objects[7000];",
    "cRFringe* __thiscall initialize_fringe_object(cRFringe* fringe);",
    "void __thiscall refresh_fringe_object_draw_list(cRFringe* fringe);",
    "void __thiscall initialize_fringe_manager(cRFringeManager* manager);",
    "cRFringe* __thiscall allocate_fringe_object(cRFringeManager* manager);",
)

FRINGE_OWNER_SIZES = {
    "cRFringe": 0x38,
    "cRFringeManager": 0x5FB44,
}

FRINGE_OWNER_TYPE_ALIASES = (
    ("Fringe", "cRFringe", 0x38),
    ("FringeManager", "cRFringeManager", 0x5FB44),
)

NUKE_OWNER_MARKERS = (
    "typedef struct cRNuke {",
    "} cRNuke;",
    "cRNuke_must_be_0x7c",
    "cRNuke nuke;",
    "void __thiscall initialize_nuke(cRNuke* nuke);",
    "void __thiscall update_nuke(cRNuke* nuke);",
    "void __thiscall uninit_nuke(cRNuke* nuke);",
)

NUKE_OWNER_SIZES = {
    "cRNuke": 0x7C,
}

NUKE_OWNER_TYPE_ALIASES = (("Nuke", "cRNuke", 0x7C),)

EXPECTED_NUKE_OWNER_LAYOUT = {
    "size": 0x7C,
    "members": {
        0x00: (0x04, "state", "NukeState"),
        0x04: (0x04, "owner_player", "Player *"),
        0x08: (0x04, "orbit_center_z_step", "float"),
        0x0C: (0x04, "orbit_center_z", "float"),
        0x10: (0x04, "orbit_phase", "float"),
        0x14: (0x04, "orbit_phase_step", "float"),
        0x18: (0x64, "sprite_slots", "Sprite *[25]"),
    },
}

EXPECTED_NUKE_PLAYER_EMBED = {
    "offset": "0x150",
    "size": 0x7C,
    "name": "nuke",
    "type": "cRNuke",
}

DAMAGE_GUAGE_OWNER_MARKERS = (
    "typedef struct cRDamageGuage {",
    "} cRDamageGuage;",
    "cRDamageGuage_must_be_0x2c",
    "cRDamageGuage damage_gauge;",
    "void __thiscall initialize_damage_gauge(cRDamageGuage* damage_guage);",
    "void __thiscall update_damage_gauge(cRDamageGuage* damage_guage);",
    "void __thiscall apply_damage_gauge_delta(",
    "cRDamageGuage* damage_guage,",
)

DAMAGE_GUAGE_OWNER_SIZES = {
    "cRDamageGuage": 0x2C,
}

DAMAGE_GUAGE_OWNER_TYPE_ALIASES = (
    ("DamageGuage", "cRDamageGuage", 0x2C),
)

EXPECTED_DAMAGE_GUAGE_OWNER_LAYOUT = {
    "size": 0x2C,
    "members": {
        0x00: (0x04, "state", "DamageGuageState"),
        0x04: (0x04, "pulse_progress", "float"),
        0x08: (0x04, "pulse_step", "float"),
        0x0C: (0x01, "unresolved_byte_0c", "uint8_t"),
        0x0D: (0x03, "_pad_0d", "uint8_t[3]"),
        0x10: (0x04, "warning_transition_progress", "float"),
        0x14: (0x04, "warning_transition_step", "float"),
        0x18: (0x04, "skin_hold_ticks", "int32_t"),
        0x1C: (0x04, "fill", "float"),
        0x20: (0x04, "display_fill", "float"),
        0x24: (0x04, "hit_flash_progress", "float"),
        0x28: (0x04, "hit_flash_step", "float"),
    },
}

EXPECTED_DAMAGE_GUAGE_PLAYER_EMBED = {
    "offset": "0x3c4",
    "size": 0x2C,
    "name": "damage_gauge",
    "type": "cRDamageGuage",
}

PROGRESS_BAR_OWNER_MARKERS = (
    "typedef struct cRProgressBar {",
    "} cRProgressBar;",
    "cRProgressBar_must_be_0x1",
    "cRProgressBar progress_bar;",
    "void __thiscall update_progress_bar(cRProgressBar* progress_bar);",
)

PROGRESS_BAR_OWNER_SIZES = {
    "cRProgressBar": 0x01,
}

PROGRESS_BAR_OWNER_TYPE_ALIASES = (("ProgressBar", "cRProgressBar", 0x01),)

EXPECTED_PROGRESS_BAR_OWNER_LAYOUT = {
    "size": 0x01,
    "members": {
        0x00: (0x01, "_empty", "uint8_t"),
    },
}

EXPECTED_PROGRESS_BAR_PLAYER_EMBED = {
    "offset": "0x3f0",
    "size": 0x01,
    "name": "progress_bar",
    "type": "cRProgressBar",
}

SQUIDGE_OWNER_MARKERS = (
    "typedef struct cRSquidge {",
    "} cRSquidge;",
    "cRSquidge_must_be_0x18",
    "cRSquidge squidge;",
    "void __thiscall initialize_squidge(cRSquidge* squidge);",
    "void __thiscall start_squidge_y(cRSquidge* squidge, float value);",
    "void __thiscall start_squidge_z(cRSquidge* squidge, float value);",
    "void __thiscall update_squidge(cRSquidge* squidge);",
)

SQUIDGE_OWNER_SIZES = {
    "cRSquidge": 0x18,
}

SQUIDGE_OWNER_TYPE_ALIASES = (("Squidge", "cRSquidge", 0x18),)

EXPECTED_SQUIDGE_OWNER_LAYOUT = {
    "size": 0x18,
    "members": {
        0x00: (0x04, "y_output", "float"),
        0x04: (0x04, "y_velocity", "float"),
        0x08: (0x04, "y_phase", "float"),
        0x0C: (0x04, "z_output", "float"),
        0x10: (0x04, "z_velocity", "float"),
        0x14: (0x04, "z_phase", "float"),
    },
}

EXPECTED_SQUIDGE_PLAYER_EMBED = {
    "offset": "0x4344",
    "size": 0x18,
    "name": "squidge",
    "type": "cRSquidge",
}

WARNING_OWNER_MARKERS = (
    "typedef struct cRWarning {",
    "} cRWarning;",
    "cRWarning_must_be_0x10",
    "cRWarning warning;",
    "void __thiscall initialize_warning(cRWarning* warning);",
    "void __thiscall uninit_warning(cRWarning* warning);",
    "void __thiscall start_warning(cRWarning* warning);",
    "void __thiscall stop_warning(cRWarning* warning);",
    "void __thiscall stop_warning_sample(cRWarning* warning);",
    "void __thiscall update_warning(cRWarning* warning);",
)

WARNING_OWNER_SIZES = {
    "cRWarning": 0x10,
}

WARNING_OWNER_TYPE_ALIASES = (("Warning", "cRWarning", 0x10),)

EXPECTED_WARNING_OWNER_LAYOUT = {
    "size": 0x10,
    "members": {
        0x00: (0x04, "state", "WarningState"),
        0x04: (0x04, "phase", "float"),
        0x08: (0x04, "phase_step", "float"),
        0x0C: (0x04, "border", "FrontendWidget *"),
    },
}

EXPECTED_WARNING_PLAYER_EMBED = {
    "offset": "0x3f4",
    "size": 0x10,
    "name": "warning",
    "type": "cRWarning",
}

TIP_OWNER_MARKERS = (
    "cRTipData_must_be_0x14",
    "cRTip_must_be_0x20",
    "cRTipManager_must_be_0x98",
    "cRTipData* definition;",
    "cRTip tips[3];",
    "cRTip* __thiscall enqueue_tip_message(cRTipManager* manager, cRTipData* definition, int32_t hide_disable_button);",
)

TIP_OWNER_SIZES = {
    "cRTipData": 0x14,
    "cRTip": 0x20,
    "cRTipManager": 0x98,
}

TIP_OWNER_TYPE_ALIASES = (
    ("TipData", "cRTipData", 0x14),
    ("Tip", "cRTip", 0x20),
    ("TipManager", "cRTipManager", 0x98),
)

EXPECTED_TIP_OWNER_LAYOUTS = {
    "cRTipData": {
        "size": 0x14,
        "members": {
            0x00: (0x04, "flags", "uint32_t"),
            0x04: (0x04, "anchor_x", "float"),
            0x08: (0x04, "layout_y", "float"),
            0x0C: (0x04, "dismiss_seconds", "float"),
            0x10: (0x04, "text", "char *"),
        },
    },
    "cRTip": {
        "size": 0x20,
        "members": {
            0x00: (0x04, "active", "int32_t"),
            0x04: (0x04, "previous_outer_owner", "int32_t"),
            0x08: (0x04, "definition", "cRTipData *"),
            0x0C: (0x04, "widget_main", "FrontendWidget *"),
            0x10: (0x04, "widget_ok", "FrontendWidget *"),
            0x14: (0x04, "widget_disable", "FrontendWidget *"),
            0x18: (0x04, "dismiss_progress", "float"),
            0x1C: (0x04, "dismiss_step", "float"),
        },
    },
    "cRTipManager": {
        "size": 0x98,
        "members": {
            0x00: (0x38, "bod", "BodBase"),
            0x38: (0x60, "tips", "cRTip[3]"),
        },
    },
}

TUTORIAL_OWNER_MARKERS = (
    "typedef struct cRTutorial {",
    "} cRTutorial;",
    "cRTutorial_must_be_0x1c",
    "cRTutorial tutorial;",
    "void __thiscall initialize_tutorial(cRTutorial* tutorial);",
    "void __thiscall uninit_tutorial(cRTutorial* tutorial);",
    "void __thiscall update_tutorial(cRTutorial* tutorial);",
)

TUTORIAL_OWNER_SIZES = {
    "cRTutorial": 0x1C,
}

TUTORIAL_OWNER_TYPE_ALIASES = (("Tutorial", "cRTutorial", 0x1C),)

EXPECTED_TUTORIAL_OWNER_LAYOUT = {
    "size": 0x1C,
    "members": {
        0x00: (0x04, "state", "int32_t"),
        0x04: (0x04, "_pad_04", "int32_t"),
        0x08: (0x04, "_pad_08", "int32_t"),
        0x0C: (0x04, "game", "cRSubGame *"),
        0x10: (0x0C, "_pad_10", "uint8_t[12]"),
    },
}

TRACK_RENDER_CACHE_OWNER_SIZES = {
    "TrackRenderCacheSlot": 0x3C,
    "SegmentCache": 0xA7F8,
}

# Header field-name changes need an explicit Hex-Rays refresh even when the
# owning function prototype itself was already current.
PATH_OWNERSHIP_DIRTY_FUNCTIONS = (
    0x404830,  # flush_row_event_display
    0x404CF0,  # update_row_event_display
    0x405040,  # register_parcel_delivery
    0x406DC0,  # game_startup_and_main_loop
    0x407B60,  # construct_game_runtime
    0x408040,  # initialize_noop_renderable_bod
    0x408060,  # initialize_runtime_pools_and_path_template_bank
    0x4084B0,  # initialize_track_speedup_runtime
    0x4084D0,  # initialize_track_jetpack_pickup_runtime
    0x408510,  # initialize_track_health_pickup_runtime
    0x408590,  # initialize_track_row_runtime
    0x4085E0,  # initialize_active_bod
    0x408650,  # initialize_fringe_object
    0x408670,  # initialize_click_start_controller_runtime
    0x408690,  # initialize_golb_shot
    0x408820,  # initialize_active_landscape_entry
    0x40A2A0,  # run_frame_update
    0x40A490,  # render_game_frame
    0x40ACF0,  # initialize_game_assets_and_world
    0x4113B0,  # add_bod_to_front
    0x411420,  # append_bod_to_end
    0x414670,  # kill_golb
    0x414820,  # update_golb_ai
    0x415280,  # create_golb
    0x417EB0,  # update_new_game_menu
    0x4182E0,  # reset_landscape_manager
    0x4182F0,  # load_landscape_script_by_name
    0x418870,  # activate_landscape_entry
    0x418A30,  # clear_active_landscape_entries
    0x418AC0,  # update_active_landscape_entry
    0x418B50,  # initialize_loading_screen
    0x420C40,  # begin_track_attachment_follow_state
    0x420CB0,  # update_track_attachment_follow_state
    0x421770,  # initialize_path_follow_golb
    0x4217B0,  # traverse_path_follow_golb
    0x4246A0,  # build_track_fringe_mesh
    0x424AD0,  # build_track_fringe_supertramp_mesh
    0x429AE0,  # find_segment_path_index_by_name
    0x42B9C0,  # get_path_position_at_node
    0x42C600,  # calc_path_length_z
    0x42C770,  # try_enter_track_attachment_from_swept_motion
    0x42CA90,  # is_point_inside_track_attachment
    0x42F5C0,  # is_bod_after_sprites
    0x42F5D0,  # set_bod_object
    0x42F650,  # initialize_renderable_bod
    0x42F5F0,  # initialize_bod_base
    0x42F680,  # apply_bod_position
    0x42F6E0,  # initialize_object_constructor_thunk
    0x433060,  # initialize_track_render_cache_manager
    0x433220,  # build_track_render_caches
    0x433830,  # add_track_cache_vertex
    0x433960,  # append_track_cache_object
    0x433B30,  # update_track_render_cache_rows
    0x433E80,  # update_active_bod
    0x433F20,  # remove_track_render_cache_bods
    0x433FD0,  # initialize_thanks_for_playing_screen
    0x4340C0,  # uninit_thanks_screen
    0x4340F0,  # update_thanks_for_playing_screen
    0x434B60,  # is_neighbor_cell_solid
    0x434BE0,  # build_track_fringe_objects
    0x435180,  # merge_track_tile_runs
    0x4354F0,  # mark_track_warning_zones
    0x4355F0,  # promote_track_tiles_to_fringe_variants
    0x4356F0,  # harmonize_center_lane_floor_slide_variants
    0x435A80,  # select_track_tile_edge_variants
    0x435D40,  # build_track_colours
    0x435DF0,  # set_subgame_features
    0x435E60,  # switch_track_mirror
    0x435EB0,  # populate_runtime_track_cells_from_segments
    0x437270,  # normalize_segment_glyph_for_track_flags
    0x4374B0,  # initialize_subgame
    0x437B10,  # reset_subgame
    0x437C40,  # update_progress_bar
    0x437DE0,  # rebuild_track_runtime_from_segments
    0x437E80,  # calc_slider_to_rate
    0x437EB0,  # build_subgame_level
    0x438700,  # complete_subgame
    0x438850,  # destroy_subgame
    0x438B90,  # update_subgame
    0x439B00,  # refresh_fringe_object_draw_list
    0x439BC0,  # remove_sub_loc
    0x439D50,  # update_sub_loc
    0x43A010,  # health_collect_particles
    0x43A1A0,  # set_subgoldy_shoot_flags
    0x43A300,  # shoot_subgoldy
    0x43A370,  # end_jetpack_hover
    0x43A390,  # update_jetpack_gauge
    0x43A580,  # uninit_jet_particles
    0x43A5B0,  # initialize_jet_particles
    0x43A690,  # update_jet_particles
    0x43A930,  # initialize_jetpack_gauge
    0x43A980,  # arm_jetpack_gauge
    0x43A9C0,  # initialize_subgoldy
    0x43AF10,  # show_subgoldy_lives
    0x43AF60,  # begin_post_follow_carryover
    0x43AFD0,  # play_subgoldy_shoot_sfx
    0x43B120,  # update_subgoldy
    0x43D230,  # initialize_subgoldy_ghost
    0x43D3D0,  # set_subgoldy_ghost_z
    0x43D410,  # get_track_grid_cell_at_world_position
    0x43D480,  # get_track_runtime_cell_at_world_z
    0x43D4D0,  # sample_track_floor_height_at_position
    0x43D6C0,  # spawn_track_health_pickup
    0x43D880,  # spawn_track_speedup
    0x43D890,  # spawn_track_jetpack_pickup
    0x43DA80,  # spawn_track_garbage_hazard
    0x43DC80,  # spawn_slug_hazard
    0x43DF10,  # spawn_track_ring_or_special_effect
    0x43E830,  # update_ring_or_special_effect_parent
    0x43ECC0,  # update_track_health_pickup
    0x43EE50,  # update_track_speedup
    0x43EFB0,  # update_track_jetpack_pickup
    0x43F5C0,  # initialize_slug_voice_manager
    0x43F5E0,  # update_slug_voice_manager
    0x4404C0,  # set_subgame_rate
    0x4404D0,  # calc_subgame_rate
    0x4408A0,  # advance_blink_random
    0x4408C0,  # initialize_blink_random
    0x440910,  # remove_subgame_bods
    0x440FA0,  # initialize_damage_gauge
    0x440FD0,  # update_damage_gauge
    0x4413F0,  # apply_damage_gauge_delta
    0x4417D0,  # update_sub_lazer_projectile
    0x442120,  # get_track_skirt_color
    0x442170,  # initialize_click_start
    0x442290,  # update_click_start
    0x442500,  # initialize_vapour
    0x442540,  # reset_vapour
    0x442560,  # add_vapour_point
    0x4425F0,  # update_vapour
    0x442E40,  # release_snail_weapons
    0x443730,  # spawn_track_parcel
    0x4438E0,  # place_parcels_on_track
    0x444240,  # place_challenge_parcels_on_track
    0x4444B0,  # project_position_onto_track_attachment
    0x444600,  # dispatch_cutscene_animation
    0x4446E0,  # set_weapon_animation
    0x444960,  # initialize_squidge
    0x444980,  # start_squidge_y
    0x4449A0,  # start_squidge_z
    0x4449C0,  # update_squidge
    0x444CF0,  # handle_subgoldy_collisions
    0x445840,  # kill_subgoldy
    0x445CD0,  # build_snail_world_hotspots
    0x445D50,  # extract_snail_local_hotspots
    0x445E20,  # update_times_up
    0x445F10,  # hide_gameplay_scores
    0x445F40,  # unhide_gameplay_scores
    0x446020,  # update_subgame_camera
    0x446130,  # initialize_cutscene_ai
    0x446160,  # initialize_cameraman
    0x4466D0,  # update_cutscene
    0x446E80,  # initialize_warning
    0x446F10,  # uninit_warning
    0x446F30,  # start_warning
    0x446F50,  # stop_warning
    0x446F60,  # stop_warning_sample
    0x446F80,  # update_warning
    0x447090,  # initialize_fringe_manager
    0x4470A0,  # allocate_fringe_object
    0x4470E0,  # uninit_nuke
    0x447110,  # initialize_nuke
    0x4471E0,  # update_nuke
    0x447290,  # recycle_bod_to_free_list
    0x448160,  # load_segment_definitions
    0x4489E0,  # kill_tip_widgets
    0x448A40,  # initialize_tip
    0x448C40,  # update_tip
    0x448CF0,  # initialize_tip_manager
    0x448D10,  # uninit_tips
    0x448D30,  # enqueue_tip_message
    0x448D80,  # update_tip_manager
    0x448DA0,  # initialize_tutorial
    0x448DD0,  # uninit_tutorial
    0x448DE0,  # update_tutorial
)

GOLB_SHOT_EXPECTED_SIZE = 0x2E8
GOLB_SHOT_ASSET_CURSOR_EXPECTED_SIZE = 0x2E8
SUB_LAZER_ASSET_CURSOR_EXPECTED_SIZE = 0xB0
SALT_ASSET_CURSOR_EXPECTED_SIZE = 0x98
TRACK_ROW_CELL_LANE_FLAGS_CURSOR_EXPECTED_SIZE = 0x54
TRACK_ROW_CELL_FRINGE_CURSOR_EXPECTED_SIZE = 0x54
SUB_ROW_PARCEL_SPAWN_Y_CURSOR_EXPECTED_SIZE = 0xF4
FRINGE_VERTEX_ROW_CURSOR_EXPECTED_SIZE = 0x30
FRINGE_FACE_PAIR_CURSOR_EXPECTED_SIZE = 0x60
GOLB_SHOT_PREFIX_END = 0x198
GOLB_SHOT_PREFIX_MEMBERS = (
    (0x000, 0x080, "RenderableBod", "RenderableBod", True),
    (0x080, 0x094, "vapour", "Vapour", False),
    (0x114, 0x004, "vapour_owner_shot", "GolbShot *", False),
    (0x118, 0x080, "tertiary_body", "cRGolbRocket", False),
)
GOLB_SHOT_COMPOSED_PREFIX_MEMBERS = (
    (0x000, 0x080, "primary_body", "RenderableBod", False),
    (0x080, 0x094, "vapour", "Vapour", False),
    (0x114, 0x004, "vapour_owner_shot", "GolbShot *", False),
    (0x118, 0x080, "tertiary_body", "cRGolbRocket", False),
)
GOLB_SHOT_HEADER_COMPOSED_PREFIX_MEMBERS = (
    (0x000, 0x080, "body", "RenderableBod", False),
    (0x080, 0x094, "vapour", "Vapour", False),
    (0x114, 0x004, "vapour_owner_shot", "GolbShot *", False),
    (0x118, 0x080, "tertiary_body", "cRGolbRocket", False),
)
PLAYER_SHOOT_EXPECTED_MEMBERS = {
    0x0308: {
        "offset": "0x308",
        "size": 4,
        "name": "shooting_tier",
        # IDA 9.4 canonicalizes this signed fixed-width typedef to plain int.
        "type": "int",
    },
    0x0338: {
        "offset": "0x338",
        "size": 4,
        "name": "shoot_flags",
        "type": "uint32_t",
    },
    0x033C: {
        "offset": "0x33c",
        "size": 4,
        "name": "previous_shoot_flags",
        "type": "uint32_t",
    },
    0x2730: {
        "offset": "0x2730",
        "size": 4,
        "name": "shoot_cooldown_progress",
        "type": "float",
    },
    0x2734: {
        "offset": "0x2734",
        "size": 4,
        "name": "shoot_cooldown_step",
        "type": "float",
    },
}
GOLB_SHOT_HEADER_MARKERS = (
    "typedef struct __base(RenderableBod, 0x00) GolbShot {",
    "__inherited RenderableBod body;",
    "Vapour vapour;",
    "struct GolbShot* vapour_owner_shot;",
    "cRGolbRocket tertiary_body;",
    "typedef GolbShot cRSubGolb;",
    "typedef GolbPathFollowState cRPathFollowGolb;",
    "typedef struct GolbShotVapourObjectStrideCursor {",
    "Object* vapour_object;",
    "uint8_t _stride_tail[0x1f4];",
)

SUB_LAZER_ASSET_CURSOR_HEADER_MARKERS = (
    "typedef struct SubLazerBodyObjectStrideCursor {",
    "Object* body_object;",
    "tColour body_color;",
    "cRSubGame* owner_game;",
    "uint8_t _stride_tail[0x48];",
)

SALT_ASSET_CURSOR_HEADER_MARKERS = (
    "typedef struct SaltOwnerGameStrideCursor {",
    "cRSubGame* owner_game;",
    "uint8_t _stride_tail[0x94];",
)

RUNTIME_GRID_CLEAR_CURSOR_HEADER_MARKERS = (
    "typedef struct TrackRowCellLaneAndFlagsStrideCursor {",
    "uint32_t lane_and_flags;",
    "typedef struct TrackRowCellFringeFrontStrideCursor {",
    "cRFringe* fringe_front;",
    "typedef struct SubRowParcelSpawnYStrideCursor {",
    "float parcel_spawn_y;",
    "BodBase attachment_body;",
    "uint8_t _stride_tail[0x94];",
)

FRINGE_MESH_CURSOR_HEADER_MARKERS = (
    "typedef struct __ptr_offset(0x14)",
    "__base(Vec3, 0x0c) FringeVertexRowCursorView {",
    "__inherited Vec3 inner_a;",
    "FringeVertexRowCursorView_must_be_0x30",
    "typedef struct __ptr_offset(0x02)",
    "__base(ObjectFaceQuad, 0x00) FringeFaceQuadPairCursorView {",
    "__inherited ObjectFaceQuad first_face;",
    "FringeFaceQuadPairCursorView_must_be_0x60",
)

GOLB_PATH_FOLLOW_DIRECTION_LVAR_DEFINITION = 0x421D22

POPULATE_RUNTIME_LVAR_SPECS = (
    ("segment_cursor", "int32_t segment_cursor;", 0x435EB0, 72),
    ("trampoline_counter", "int32_t trampoline_counter;", 0x4360D6, 76),
    ("first_or_last_row", "char first_or_last_row;", 0x4360DA, 42),
    ("row_event_owner", "int32_t row_event_owner;", 0x4360DF, 64),
    (
        "segment_row_count_cursor",
        "int32_t *segment_row_count_cursor;",
        0x436073,
        None,
    ),
    (
        "row_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor *row_fringe_front_cursor;",
        0x4360EA,
        68,
    ),
    (
        "parcel_spawn_y_cursor",
        "SubRowParcelSpawnYStrideCursor *parcel_spawn_y_cursor;",
        0x4360EE,
        None,
    ),
    ("rows_remaining", "int32_t rows_remaining;", 0x4360F4, 60),
    ("cell_lanes_remaining", "int32_t cell_lanes_remaining;", 0x4360FE, None),
    (
        "lane_and_flags_cursor",
        "TrackRowCellLaneAndFlagsStrideCursor *lane_and_flags_cursor;",
        0x43612A,
        None,
    ),
    (
        "cell_lane_and_flags",
        "uint32_t cell_lane_and_flags;",
        0x43612D,
        None,
    ),
    ("cell_list_flags", "uint32_t cell_list_flags;", 0x43614E, None),
    (
        "next_row_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor *next_row_fringe_front_cursor;",
        0x436162,
        None,
    ),
    (
        "remaining_cell_lanes",
        "int32_t remaining_cell_lanes;",
        0x436166,
        None,
    ),
    (
        "cell_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor *cell_fringe_front_cursor;",
        0x43616B,
        None,
    ),
    ("visited_cursor", "uint8_t *visited_cursor;", 0x4361AE, None),
    ("visited_segment_index", "int32_t visited_segment_index;", 0x4361A8, None),
    ("build_row", "int32_t build_row;", 0x4361CB, 44),
    ("runtime_row_index", "int32_t runtime_row_index;", 0x4361DB, None),
    (
        "build_runtime_owner",
        "cRSubGame *build_runtime_owner;",
        0x4361DF,
        None,
    ),
    ("selected_segment", "SubSegment *selected_segment;", 0x4361E7, None),
    ("active_segment", "SubSegment *active_segment;", 0x4361F2, 48),
    (
        "selected_segment_row_count",
        "int32_t selected_segment_row_count;",
        0x4362CD,
        None,
    ),
    ("segment_row_index", "int32_t segment_row_index;", 0x4362E6, 56),
    ("source_segment", "SubSegment *source_segment;", 0x43632C, None),
    (
        "segment_row_anchor",
        "SubSegmentRowStrideAnchor *segment_row_anchor;",
        0x436404,
        None,
    ),
    (
        "runtime_row_anchor",
        "RuntimeRowStrideAnchor *runtime_row_anchor;",
        0x436459,
        None,
    ),
    (
        "runtime_cell_anchor",
        "RuntimeCellStrideAnchor *runtime_cell_anchor;",
        0x436683,
        None,
    ),
    (
        "attachment_entry_installed",
        "char attachment_entry_installed;",
        0x436632,
        43,
    ),
    ("lane", "int32_t lane;", 0x436637, 60),
    (
        "runtime_cell",
        "cRSubLoc *runtime_cell;",
        0x4366C5,
        None,
    ),
    (
        "selected_attachment_path",
        "cRPath *selected_attachment_path;",
        0x436D17,
        None,
    ),
    (
        "attachment_span_index",
        "int32_t attachment_span_index;",
        0x436DB5,
        None,
    ),
    (
        "stamped_row",
        "SubRow *stamped_row;",
        0x436DC2,
        None,
    ),
    (
        "fringe_slot",
        "cRFringe **fringe_slot;",
        0x437101,
        None,
    ),
    (
        "remaining_fringe_slots",
        "int32_t remaining_fringe_slots;",
        0x437105,
        None,
    ),
    (
        "fringe_object",
        "cRFringe *fringe_object;",
        0x43710A,
        None,
    ),
    (
        "fringe_position",
        "Vec3 *fringe_position;",
        0x43711F,
        None,
    ),
)

PLACE_PARCELS_RUNTIME_LVAR_SPECS = (
    (
        "segment_row_count_anchor",
        "SubSegmentParcelScanAnchor *segment_row_count_anchor;",
        0x443953,
        None,
    ),
    (
        "authored_parcel_position",
        "Vec3 *authored_parcel_position;",
        0x44399F,
        None,
    ),
    (
        "parcel_set_runtime_row_anchor",
        "RuntimeRowStrideAnchor *parcel_set_runtime_row_anchor;",
        0x443DB8,
        None,
    ),
    (
        "zero_runtime_row_anchor",
        "RuntimeRowStrideAnchor *zero_runtime_row_anchor;",
        0x444009,
        None,
    ),
    (
        "projection_row",
        "SubRow *projection_row;",
        0x444162,
        None,
    ),
)

PLACE_PARCELS_REJECTED_STACK_LVAR_OVERRIDES = (
    ("saved_segment_row_count_anchor", 0x44395D, 36),
    ("glyph_row_cursor", 0x44399B, 72),
    ("glyph_lane_cursor", 0x443A95, 76),
)

CHALLENGE_PARCELS_RUNTIME_LVAR_SPECS = (
    (
        "zero_bucket_count_lane",
        "int32_t *zero_bucket_count_lane;",
        0x444276,
        None,
    ),
    ("candidate_count", "int32_t candidate_count;", 0x444290, None),
    ("runtime_row_index", "int32_t runtime_row_index;", 0x444292, None),
    (
        "survival_row_index_write",
        "int32_t *survival_row_index_write;",
        0x44429C,
        None,
    ),
    (
        "parcel_set_id_cursor",
        "int32_t *parcel_set_id_cursor;",
        0x4442A1,
        None,
    ),
    (
        "remaining_candidate_count",
        "int32_t remaining_candidate_count;",
        0x444294,
        36,
    ),
    ("placed_count", "int32_t placed_count;", 0x4442D3, None),
    (
        "last_candidate_index",
        "int32_t last_candidate_index;",
        0x4442DD,
        None,
    ),
    (
        "selected_row_index_entry",
        "int32_t *selected_row_index_entry;",
        0x44430F,
        None,
    ),
    (
        "challenge_runtime_row_anchor",
        "RuntimeRowStrideAnchor *challenge_runtime_row_anchor;",
        0x44432E,
        None,
    ),
    ("entries_to_shift", "int32_t entries_to_shift;", 0x44438C, None),
    (
        "projection_row",
        "SubRow *projection_row;",
        0x4443D8,
        None,
    ),
    (
        "projection_scan_index",
        "int32_t projection_scan_index;",
        0x4443CA,
        36,
    ),
    ("path_node", "int32_t path_node;", 0x44440A, None),
)

PROJECT_ATTACHMENT_LVAR_SPECS = (
    ("runtime_row", "SubRow *runtime_row;", 0x4444D5, None),
    (
        "primary_attachment_cell",
        "cRSubLoc *primary_attachment_cell;",
        0x4444EB,
        None,
    ),
    (
        "attachment_template_record",
        "cRPath *attachment_template_record;",
        0x4444F4,
        None,
    ),
    ("sample", "PathTemplateSample *sample;", 0x44451E, None),
    ("projected_position", "Vec3 projected_position;", 0x4445C9, None),
)

REMOVE_SUB_LOC_RUNTIME_LVAR_SPECS = (
    (
        "runtime_row_anchor",
        "GameRootRuntimeRowStrideAnchor *runtime_row_anchor;",
        0x439BFB,
        None,
    ),
)

UPDATE_SUBGAME_RUNTIME_LVAR_SPECS = (
    (
        "runtime_row_anchor",
        "RuntimeRowStrideAnchor *runtime_row_anchor;",
        0x439035,
        None,
    ),
    (
        "runtime_row_anchor_saved",
        "RuntimeRowStrideAnchor *runtime_row_anchor_saved;",
        0x439038,
        76,
    ),
    (
        "runtime_cell_anchor",
        "RuntimeCellStrideAnchor *runtime_cell_anchor;",
        0x4390F9,
        None,
    ),
    (
        "time_trial_route_cursor",
        "TimeTrialRouteRecordCursor *time_trial_route_cursor;",
        0x4398CB,
        None,
    ),
)

UPDATE_SUBGOLDY_LVAR_SPECS = (
    (
        "row_event_cell",
        "cRSubLoc *row_event_cell;",
        0x43B6EB,
        None,
    ),
    (
        "row_event_game",
        "cRSubGame *row_event_game;",
        0x43B6F0,
        None,
    ),
    # Stack +0x2c is reused for unrelated float lifetimes later in the function;
    # use a unique semantic name so Hex-Rays can persist this exact early split.
    (
        "row_event_source_cell",
        "cRSubLoc *row_event_source_cell;",
        0x43B6F8,
        44,
    ),
    (
        "row_event_row_index",
        "int32_t row_event_row_index;",
        0x43B707,
        None,
    ),
    (
        "runtime_row",
        "SubRow *runtime_row;",
        0x43B70A,
        None,
    ),
    (
        "row_event_id",
        "int32_t row_event_id;",
        0x43B711,
        None,
    ),
    (
        "sample_segment_view",
        "SubSegmentEventBiasView *sample_segment_view;",
        0x43B823,
        None,
    ),
    (
        "current_cell",
        "cRSubLoc *current_cell;",
        0x43BCCE,
        None,
    ),
    (
        "attachment_game",
        "cRSubGame *attachment_game;",
        0x43BCDE,
        None,
    ),
    (
        "primary_attachment_cell",
        "cRSubLoc *primary_attachment_cell;",
        0x43BDA4,
        24,
    ),
    (
        "primary_row_index",
        "int32_t primary_row_index;",
        0x43BDD3,
        None,
    ),
    (
        "secondary_attachment_cell",
        "cRSubLoc *secondary_attachment_cell;",
        0x43BE79,
        24,
    ),
    (
        "secondary_row_index",
        "int32_t secondary_row_index;",
        0x43BEA8,
        None,
    ),
    (
        "time_trial_route_cursor",
        "TimeTrialRouteRecordCursor *time_trial_route_cursor;",
        0x43CD08,
        None,
    ),
)

INITIALIZE_SUBGOLDY_LVAR_SPECS = (
    (
        "golb_shot_flight_cursor",
        "GolbShotFlightStrideCursor *golb_shot_flight_cursor;",
        0x43AE54,
        None,
    ),
)

SHOOT_SUBGOLDY_LVAR_SPECS = (
    ("spawn_selector", "int32_t spawn_selector;", 0x43A31D, None),
    ("shot_slot_index", "int32_t shot_slot_index;", 0x43A330, None),
    ("golb_shot_cursor", "GolbShot *golb_shot_cursor;", 0x43A332, None),
)

WORLD_INITIALIZER_GOLB_ASSET_LVAR_SPECS = (
    (
        "golb_shot_vapour_object_cursor",
        "GolbShotVapourObjectStrideCursor *golb_shot_vapour_object_cursor;",
        0x40FBE8,
        None,
    ),
)

WORLD_INITIALIZER_SUB_LAZER_ASSET_LVAR_SPECS = (
    (
        "sub_lazer_body_object_cursor",
        "SubLazerBodyObjectStrideCursor *sub_lazer_body_object_cursor;",
        0x40BD9C,
        None,
    ),
)

WORLD_INITIALIZER_SALT_ASSET_LVAR_SPECS = (
    (
        "salt_owner_game_cursor",
        "SaltOwnerGameStrideCursor *salt_owner_game_cursor;",
        0x40BE32,
        None,
    ),
)

REMOVE_SUBGAME_BODS_CURSOR_LVAR_SPECS = (
    ("runtime_cell_cursor", "cRSubLoc *runtime_cell_cursor;", 0x44091A, None),
    (
        "row_list_next_cursor",
        "BodNode **row_list_next_cursor;",
        0x440920,
        None,
    ),
    (
        "health_list_next_cursor",
        "BodNode **health_list_next_cursor;",
        0x4409C6,
        None,
    ),
    (
        "garbage_list_next_cursor",
        "BodNode **garbage_list_next_cursor;",
        0x440B51,
        None,
    ),
    (
        "slug_list_next_cursor",
        "BodNode **slug_list_next_cursor;",
        0x440BD9,
        None,
    ),
    (
        "ring_list_next_cursor",
        "BodNode **ring_list_next_cursor;",
        0x440C61,
        None,
    ),
    ("golb_shot_cursor", "GolbShot *golb_shot_cursor;", 0x440F15, None),
)

# This four-byte stack slot holds row indices during the build pass and is
# reused for cache-family format strings afterward. IDA 9.4 cannot split the
# branch-merged late stores, so keep the exact early integer owners only.
BUILD_TRACK_RENDER_CACHE_COUNTER_LVAR_SPECS = (
    (
        "current_row_index",
        "int32_t current_row_index;",
        0x433251,
        None,
    ),
    (
        "row_index",
        "int32_t row_index;",
        0x433253,
        60,
    ),
)

SPAWN_TRACK_RING_LVAR_SPECS = (
    ("slot_index", "int32_t slot_index;", 0x43DF14, None),
    ("state_cursor", "SubRingState *state_cursor;", 0x43DF1C, None),
    ("slot_cursor", "SubRingSlotCursor *slot_cursor;", 0x43DF5D, None),
    ("default_phase_step", "float default_phase_step;", 0x43DF83, 32),
    ("effective_kind", "int32_t effective_kind;", 0x43DF8C, None),
    ("selected_ring", "SubRing *selected_ring;", 0x43E3DB, None),
    ("active_head", "BodNode **active_head;", 0x43E400, None),
    ("active_first", "BodNode *active_first;", 0x43E405, None),
    ("promoted_head", "BodNode *promoted_head;", 0x43E424, None),
)

RING_PARENT_RADIUS_LVAR_SPECS = (
    (
        "collect_radius_cursor",
        "float *collect_radius_cursor;",
        0x43EAE8,
        None,
    ),
    (
        "expand_radius_cursor",
        "float *expand_radius_cursor;",
        0x43EC61,
        None,
    ),
)

RING_PARTICLE_POSITION_CURSOR_LVAR_SPECS = (
    (
        "parent_position_cursor",
        "SubRingPositionAdvanceCursor *parent_position_cursor;",
        0x43E7D1,
        None,
    ),
)

SPAWN_TRACK_HEALTH_LVAR_SPECS = (
    (
        "health_cursor",
        "SubHealthSlotCursor *health_cursor;",
        0x43D6FD,
        None,
    ),
    ("health_node", "BodNode *health_node;", 0x43D749, None),
    ("sprite", "Sprite *sprite;", 0x43D7C1, None),
)

SPAWN_TRACK_JETPACK_LVAR_SPECS = (
    (
        "jetpack_cursor",
        "JetPackSlotCursor *jetpack_cursor;",
        0x43D8CE,
        None,
    ),
    ("position_x", "float *position_x;", 0x43D8F0, None),
    ("jetpack_node", "BodNode *jetpack_node;", 0x43D95A, None),
    ("sprite", "Sprite *sprite;", 0x43D9CC, None),
    ("sprite_position", "Vec3 *sprite_position;", 0x43DA1A, None),
)

FIREWORK_SHOOT_LVAR_SPECS = (
    ("flags", "SpriteFlag flags;", 0x441E17, None),
    ("duration_random", "double duration_random;", 0x441E37, None),
    ("green", "float green;", 0x441E86, 8),
    ("remaining", "int32_t remaining;", 0x441DFB, 32),
    ("velocity_x", "float velocity_x;", 0x441F13, 36),
    ("velocity_z", "float velocity_z;", 0x441EB6, 56),
    ("velocity_y", "float velocity_y;", 0x441ED9, 60),
    ("red", "float red;", 0x441E71, 64),
    (
        "velocity_x_random",
        "int32_t velocity_x_random;",
        0x441EE2,
        64,
    ),
)

SPAWN_SALT_HAZARD_LVAR_SPECS = (
    (
        "salt_state_cursor",
        "SaltStateStrideCursor *salt_state_cursor;",
        0x441564,
        None,
    ),
)

COLLISION_POOL_CURSOR_LVAR_SPECS = (
    ("salt_cursor", "SaltSlotCursor *salt_cursor;", 0x444D41, None),
    (
        "sub_lazer_cursor",
        "SubLazerSlotCursor *sub_lazer_cursor;",
        0x444E27,
        None,
    ),
    ("slug_cursor", "SlugSlotCursor *slug_cursor;", 0x44502D, None),
    ("parcel_cursor", "ParcelSlotCursor *parcel_cursor;", 0x44525A, None),
    (
        "health_cursor",
        "SubHealthSlotCursor *health_cursor;",
        0x445370,
        None,
    ),
    ("ring_cursor", "SubRingSlotCursor *ring_cursor;", 0x445622, None),
    ("ring_kind", "SubRingKind ring_kind;", 0x4456C5, None),
    ("effect_kind", "SubRingKind effect_kind;", 0x4456FE, None),
)

MERGE_RUNTIME_LVAR_SPECS = (
    ("seed_lane_flags", "uint32_t *seed_lane_flags;", 0x435195, None),
    ("cell_lane_flags", "uint32_t *cell_lane_flags;", 0x4351D8, None),
    ("cell", "cRSubLoc *cell;", 0x4351EA, None),
    ("floor_tile_cursor", "uint8_t *floor_tile_cursor;", 0x43521C, None),
    (
        "floor_cleanup_lane_flags",
        "uint32_t *floor_cleanup_lane_flags;",
        0x43529A,
        None,
    ),
    (
        "slide_lane_flags_cursor",
        "uint32_t *slide_lane_flags_cursor;",
        0x4352EE,
        None,
    ),
    (
        "slide_cleanup_lane_flags",
        "uint32_t *slide_cleanup_lane_flags;",
        0x43535C,
        None,
    ),
    ("wall_tile_cursor", "uint8_t *wall_tile_cursor;", 0x4353E6, None),
    (
        "wall_cleanup_lane_flags",
        "uint32_t *wall_cleanup_lane_flags;",
        0x435486,
        None,
    ),
    (
        "row_attachment_flags",
        "uint32_t *row_attachment_flags;",
        0x4351D4,
        32,
    ),
)

FRINGE_RUNTIME_LVAR_SPECS = (
    ("row", "SubRow *row;", 0x434C0D, None),
    ("cell", "cRSubLoc *cell;", 0x434C15, None),
    ("row_cursor", "SubRow *row_cursor;", 0x434C1B, 40),
    ("fringe_front_new", "cRFringe *fringe_front_new;", 0x434D44, None),
    ("fringe_right_new", "cRFringe *fringe_right_new;", 0x434E48, None),
    ("fringe_left_new", "cRFringe *fringe_left_new;", 0x434F4C, None),
    ("fringe_back_new", "cRFringe *fringe_back_new;", 0x435050, None),
)

FRINGE_MESH_LVAR_SPECS = {
    "build_track_fringe_mesh": (
        (
            "row_cursor",
            "float *__shifted(FringeVertexRowCursorView, 0x14) row_cursor;",
            0x424744,
            None,
        ),
        (
            "face_pair_cursor",
            "uint16_t *__shifted(FringeFaceQuadPairCursorView, 0x02) face_pair_cursor;",
            0x4249FD,
            None,
        ),
    ),
    "build_track_fringe_supertramp_mesh": (
        (
            "row_cursor",
            "float *__shifted(FringeVertexRowCursorView, 0x14) row_cursor;",
            0x424B3E,
            None,
        ),
        (
            "face_pair_cursor",
            "uint16_t *__shifted(FringeFaceQuadPairCursorView, 0x02) face_pair_cursor;",
            0x424D37,
            None,
        ),
    ),
}

HARMONIZE_RUNTIME_LVAR_SPECS = (
    (
        "forward_cell_anchor",
        "RuntimeCellStrideAnchor *forward_cell_anchor;",
        0x435753,
        None,
    ),
    (
        "backward_cell_anchor",
        "RuntimeCellStrideAnchor *backward_cell_anchor;",
        0x4358DD,
        None,
    ),
)

BUILD_SUBGAME_ACTIVE_BOD_LVAR_SPECS = (
    (
        "player",
        "Player *player;",
        0x438335,
        None,
    ),
    (
        "jetpack_channel",
        "Weapon *jetpack_channel;",
        0x4383A9,
        None,
    ),
    (
        "active_first_ref_jetpack",
        "BodNode **active_first_ref_jetpack;",
        0x4383CD,
        None,
    ),
    (
        "active_first_jetpack",
        "BodNode *active_first_jetpack;",
        0x4383D3,
        None,
    ),
    (
        "active_new_first_jetpack",
        "BodNode *active_new_first_jetpack;",
        0x4383F7,
        None,
    ),
    (
        "weapon_channel_0",
        "Weapon *weapon_channel_0;",
        0x438408,
        None,
    ),
    (
        "active_first_ref_weapon_0",
        "BodNode **active_first_ref_weapon_0;",
        0x438426,
        None,
    ),
    (
        "active_first_weapon_0",
        "BodNode *active_first_weapon_0;",
        0x43842B,
        None,
    ),
    (
        "active_new_first_weapon_0",
        "BodNode *active_new_first_weapon_0;",
        0x43844F,
        None,
    ),
    (
        "weapon_channel_1",
        "Weapon *weapon_channel_1;",
        0x438460,
        None,
    ),
    (
        "active_first_ref_weapon_1",
        "BodNode **active_first_ref_weapon_1;",
        0x43847E,
        None,
    ),
    (
        "active_first_weapon_1",
        "BodNode *active_first_weapon_1;",
        0x438483,
        None,
    ),
    (
        "active_new_first_weapon_1",
        "BodNode *active_new_first_weapon_1;",
        0x4384A7,
        None,
    ),
    (
        "weapon_channel_2",
        "Weapon *weapon_channel_2;",
        0x4384B8,
        None,
    ),
    (
        "active_first_ref_weapon_2",
        "BodNode **active_first_ref_weapon_2;",
        0x4384D6,
        None,
    ),
    (
        "active_first_weapon_2",
        "BodNode *active_first_weapon_2;",
        0x4384DB,
        None,
    ),
    (
        "active_new_first_weapon_2",
        "BodNode *active_new_first_weapon_2;",
        0x4384FF,
        None,
    ),
    (
        "invincible_shell",
        "Invincible *invincible_shell;",
        0x438510,
        None,
    ),
    (
        "active_first_ref_invincible_shell",
        "BodNode **active_first_ref_invincible_shell;",
        0x43852E,
        None,
    ),
    (
        "active_first_invincible_shell",
        "BodNode *active_first_invincible_shell;",
        0x438533,
        None,
    ),
    (
        "active_new_first_invincible_shell",
        "BodNode *active_new_first_invincible_shell;",
        0x438557,
        None,
    ),
    (
        "presentation",
        "Snail *presentation;",
        0x438577,
        None,
    ),
    (
        "active_first_ref_presentation",
        "BodNode **active_first_ref_presentation;",
        0x438595,
        None,
    ),
    (
        "active_first_presentation",
        "BodNode *active_first_presentation;",
        0x43859A,
        None,
    ),
    (
        "active_new_first_presentation",
        "BodNode *active_new_first_presentation;",
        0x4385BE,
        None,
    ),
    (
        "active_first_ref_player",
        "BodNode **active_first_ref_player;",
        0x4385E2,
        None,
    ),
    (
        "active_first_player",
        "BodNode *active_first_player;",
        0x4385E7,
        None,
    ),
    (
        "active_new_first_player",
        "BodNode *active_new_first_player;",
        0x438606,
        None,
    ),
)

# These displacement values are relocatable offsets into GameRoot, but several
# of their numeric values also land on named code or historical offset-symbol
# addresses. IDA then renders the individual instruction operand as an address
# expression and prevents Hex-Rays from folding the already typed GameRoot*
# access back into its canonical Player/cRSubGame field. Keep the symbol
# names themselves intact and normalize only the seven proven displacement
# operands in the attachment-entry seed tail.
ATTACHMENT_ENTRY_ROOT_OFFSET_OPERANDS = (
    (0x42C98A, 0, 0x430199),  # Player::attachment_exit_pending
    (0x42C99C, 1, 0x4340C0),  # Player::squidge
    (0x42C9B4, 0, 0x430100),  # Player::follow_state.active
    (0x42CA18, 1, 0x42FD7C),  # cRPathFollowGoldy::player -> Player
    (0x42CA3D, 1, 0x64118C),  # runtime_rows[row].installed_heading_delta
    (0x42CA5B, 0, 0x430118),  # cRPathFollowGoldy::orientation_a
    (0x42CA7B, 1, 0x430100),  # Player::follow_state
)

# The world initializer keeps GameRoot in EBP while constructing the complete
# Player-owned presentation graph. Every displacement below is a proven
# GameRoot-relative field, but each numeric value also lands inside .text.
# IDA consequently promotes the displacement to a loc_* address and prevents
# Hex-Rays from following the already measured
# GameRoot -> cRSubGame -> Player -> Snail ownership chain. Normalize only
# these exact memory operands; the code symbols at the colliding addresses stay
# intact.
WORLD_INITIALIZER_ROOT_OFFSET_OPERANDS = (
    # Player::cameraman.
    (0x40AEFC, 1, 0x42FF7C),
    # Snail body, ten owned cutscene-animation slots, and hotspot body.
    (0x40F28F, 1, 0x43284C),
    (0x40F2FB, 1, 0x432870),
    (0x40F313, 1, 0x432700),
    (0x40F326, 1, 0x432724),
    (0x40F344, 1, 0x4328CC),
    (0x40F34F, 1, 0x4328F0),
    (0x40F36D, 1, 0x43294C),
    (0x40F378, 1, 0x432970),
    (0x40F396, 1, 0x4329CC),
    (0x40F3A1, 1, 0x4329F0),
    (0x40F3BF, 1, 0x432A4C),
    (0x40F3CA, 1, 0x432A70),
    (0x40F3E8, 1, 0x432ACC),
    (0x40F3F3, 1, 0x432AF0),
    (0x40F411, 1, 0x432B4C),
    (0x40F41C, 1, 0x432B70),
    (0x40F43A, 1, 0x432BCC),
    (0x40F445, 1, 0x432BF0),
    (0x40F463, 1, 0x432C4C),
    (0x40F46E, 1, 0x432C70),
    (0x40F48C, 1, 0x432CCC),
    (0x40F497, 1, 0x432CF0),
    (0x40F4B5, 1, 0x433D4C),
    (0x40F4C0, 1, 0x433D70),
    (0x40F4D9, 1, 0x432700),
    (0x40F4E4, 1, 0x432870),
    (0x40F53F, 1, 0x432724),
    (0x40F54F, 1, 0x432724),
    (0x40F55A, 1, 0x432724),
    (0x40F566, 1, 0x432724),
    (0x40F572, 1, 0x432724),
    # Jetpack presentation channel and its two active animation slots.
    (0x40F589, 1, 0x4338E0),
    (0x40F594, 1, 0x433904),
    (0x40F5B2, 1, 0x433A30),
    (0x40F5BD, 1, 0x433A54),
    (0x40F5DB, 1, 0x433AB0),
    (0x40F5E6, 1, 0x433AD4),
    (0x40F5F9, 1, 0x433A54),
    (0x40F650, 1, 0x433904),
    (0x40F660, 1, 0x433904),
    (0x40F66B, 1, 0x433904),
    (0x40F677, 1, 0x433904),
    (0x40F683, 1, 0x433904),
    # Left weapon channel and its five inline animation slots.
    (0x40F69A, 1, 0x432D4C),
    (0x40F6A5, 1, 0x432D70),
    (0x40F6C3, 1, 0x432E9C),
    (0x40F6CE, 1, 0x432EC0),
    (0x40F6EC, 1, 0x432F1C),
    (0x40F6F7, 1, 0x432F40),
    (0x40F715, 1, 0x432F9C),
    (0x40F720, 1, 0x432FC0),
    (0x40F73E, 1, 0x43301C),
    (0x40F749, 1, 0x433040),
    (0x40F767, 1, 0x43309C),
    (0x40F772, 1, 0x4330C0),
    (0x40F785, 1, 0x432EC0),
    (0x40F7E0, 1, 0x432D70),
    (0x40F7F0, 1, 0x432D70),
    (0x40F7FB, 1, 0x432D70),
    (0x40F807, 1, 0x432D70),
    (0x40F813, 1, 0x432D70),
    # Right weapon channel and its five inline animation slots.
    (0x40F82A, 1, 0x433128),
    (0x40F835, 1, 0x43314C),
    (0x40F853, 1, 0x433278),
    (0x40F85E, 1, 0x43329C),
    (0x40F87C, 1, 0x4332F8),
    (0x40F887, 1, 0x43331C),
    (0x40F8A5, 1, 0x433378),
    (0x40F8B0, 1, 0x43339C),
    (0x40F8CE, 1, 0x4333F8),
    (0x40F8D9, 1, 0x43341C),
    (0x40F8F7, 1, 0x433478),
    (0x40F902, 1, 0x43349C),
    (0x40F915, 1, 0x43329C),
    (0x40F970, 1, 0x43314C),
    (0x40F980, 1, 0x43314C),
    (0x40F98B, 1, 0x43314C),
    (0x40F997, 1, 0x43314C),
    (0x40F9A3, 1, 0x43314C),
    # Top weapon channel and its five inline animation slots.
    (0x40F9BA, 1, 0x433504),
    (0x40F9C5, 1, 0x433528),
    (0x40F9E3, 1, 0x433654),
    (0x40F9EE, 1, 0x433678),
    (0x40FA0C, 1, 0x4336D4),
    (0x40FA17, 1, 0x4336F8),
    (0x40FA35, 1, 0x433754),
    (0x40FA40, 1, 0x433778),
    (0x40FA5E, 1, 0x4337D4),
    (0x40FA69, 1, 0x4337F8),
    (0x40FA87, 1, 0x433854),
    (0x40FA92, 1, 0x433878),
    (0x40FAA5, 1, 0x433678),
    (0x40FB00, 1, 0x433528),
    (0x40FB10, 1, 0x433528),
    (0x40FB1B, 1, 0x433528),
    (0x40FB2E, 1, 0x433528),
    (0x40FB3A, 1, 0x433528),
    # SnailSkin's three borrowed material refs and invincibility body.
    (0x40FB5C, 0, 0x43403C),
    (0x40FB73, 0, 0x434040),
    (0x40FB83, 0, 0x434044),
    (0x40FB8F, 1, 0x433F94),
    (0x40FB9A, 1, 0x433FB8),
    (0x40FBAF, 1, 0x433FB8),
    # Player-owned Golb shot body, vapour-object cursor, and shared rocket body.
    (0x40FBC7, 1, 0x4302E4),
    (0x40FBD2, 1, 0x430308),
    (0x40FBE7, 1, 0x430270),
    (0x40FC3F, 1, 0x430308),
    # Subgame-owned high-score tracker used by the initializer tail.
    (0x4101CB, 1, 0x6FFAE0),
)

# Three lifecycle sites borrow the same embedded high-score bank from different
# receiver depths. The shutdown tail addresses SubHighScore at
# GameRoot +0x6ffae0, the New Game attract loop addresses its postal_records at
# GameRoot +0x6ffae8, and Complete addresses the bank at
# cRSubGame +0x68b4c8. Each numeric displacement falls inside the unrelated
# g_parcel_set_buckets symbol, so IDA substitutes that global and hides the
# already measured GameRoot -> cRSubGame -> SubHighScore owner chain.
# Normalize only these ten exact operands; the parcel-bank symbol itself stays
# intact for its real consumers.
HIGH_SCORE_LIFECYCLE_OFFSET_OPERANDS = (
    # game_startup_and_main_loop shutdown saves.
    (0x407234, 1, 0x6FFAE0),
    (0x407247, 1, 0x6FFAE0),
    (0x407259, 1, 0x6FFAE0),
    (0x40726C, 1, 0x6FFAE0),
    (0x40727F, 1, 0x6FFAE0),
    # update_new_game_menu postal-record selection and active check.
    (0x418219, 1, 0x6FFAE8),
    (0x418220, 1, 0x6FFAE8),
    # complete_subgame score insertion.
    (0x43880D, 1, 0x68B4C8),
    (0x43881E, 1, 0x68B4C8),
    (0x438831, 1, 0x68B4C8),
)

# These frontend, landscape, and presentation sites all borrow the one embedded
# Player at GameRoot +0x42fd7c. The numeric displacement is also the tracked
# address of the g_player_block evidence symbol, so IDA promotes it to a global
# expression and hides the already recovered
# GameRoot -> cRSubGame -> Player owner graph. Normalize only these ten
# exact operands; g_player_block remains intact as a bounded offset symbol.
PLAYER_ROOT_BORROW_OFFSET_OPERANDS = (
    # Completion teardown and row-event scoring.
    (0x404853, 1, 0x42FD7C),
    (0x404881, 1, 0x42FD7C),
    (0x404D9A, 1, 0x42FD7C),
    (0x404E5D, 1, 0x42FD7C),
    (0x405057, 1, 0x42FD7C),
    (0x405092, 1, 0x42FD7C),
    # Landscape reference body and presentation lifecycle.
    (0x4189AD, 1, 0x42FD7C),
    (0x445E3A, 1, 0x42FD7C),
    (0x446142, 1, 0x42FD7C),
    (0x446168, 1, 0x42FD7C),
)

# These damage and cutscene gates are byte-sized fields inside the same embedded
# Player. Their numeric GameRoot displacements collide with bounded evidence
# symbols, so IDA renders false global-plus-root expressions instead of the
# recovered owner path. Normalize only the six exact operands: three reads of
# Player::completion_handoff_active, one Player::attachment_exit_pending read,
# the low-byte Player::shoot_flags sign-bit test, and the intro path's
# Player::click_start.hide_prompt clear. The evidence symbols remain named for
# every other consumer.
PLAYER_STATE_GATE_OFFSET_OPERANDS = (
    # update_damage_gauge.
    (0x441074, 1, 0x4301BC),  # Player::completion_handoff_active
    (0x441114, 1, 0x4301BC),  # Player::completion_handoff_active
    (0x441174, 1, 0x430199),  # Player::attachment_exit_pending
    (0x44117E, 1, 0x4301BC),  # Player::completion_handoff_active
    # apply_damage_gauge_delta and update_cutscene.
    (0x4413F9, 0, 0x4300B4),  # low byte of Player::shoot_flags
    (0x4467B1, 0, 0x42FEC4),  # Player::click_start.hide_prompt
)

# Tutorial::Init borrows the containing cRSubGame and ORs the authored
# tutorial feature mask into runtime_flags. IDA can promote both immediate
# operands to address expressions because their values also land inside the
# image, which blocks the typed GameRoot/cRSubGame folds. UnInit has the
# same collision for the root-owned cRTipManager displacement. Keep the global
# symbols and normalize only these three proven instruction operands.
TUTORIAL_NUMERIC_OPERANDS = (
    (0x448DAB, 1, 0x74618),  # GameRoot::subgame
    (0x448DB6, 1, 0x600000),  # tutorial runtime_flags OR mask
    (0x448DD5, 1, 0x12E6F58),  # GameRoot::tip_manager
)

# The attachment entry and follow updater have the same address-expression
# collision in one installed-heading load, two Player basis-row publications,
# and seven repeated runtime-row cell loads.
ATTACHMENT_FOLLOW_ROOT_OFFSET_OPERANDS = (
    (0x420C92, 1, 0x64118C),  # SubRow::installed_heading_delta
    (0x4212A3, 1, 0x42FDC4),  # Player::body.transform.basis_up
    (0x4214DB, 1, 0x42FDC4),  # Player::body.transform.basis_up
    (0x420D6A, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420D8A, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420DB0, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420DF7, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420E1C, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420E3D, 1, 0x641184),  # SubRow::primary_attachment_cell
    (0x420E63, 1, 0x641184),  # SubRow::primary_attachment_cell
)

# Four catalog banks are loaded repeatedly by SlideSmoothTrack. Their numeric
# GameRoot displacements collide with named addresses, so normalize only these
# exact operands and let the typed root owner fold them into the catalog.
HARMONIZE_ROOT_OFFSET_OPERANDS = (
    (0x4357A0, 1, 0x447B4),  # floor_slices[0].object compare
    (0x4357A8, 1, 0x44B34),  # slide_slices[0].object replacement
    (0x4357D1, 1, 0x4423C),  # floor_corners[0].object compare
    (0x4357DC, 1, 0x443FC),  # slide_corners[0].object replacement
    (0x435856, 1, 0x44B34),  # slide_slices[0].object compare
    (0x43585E, 1, 0x447B4),  # floor_slices[0].object replacement
    (0x435887, 1, 0x443FC),  # slide_corners[0].object compare
    (0x435892, 1, 0x4423C),  # floor_corners[0].object replacement
    (0x435931, 1, 0x447B4),  # floor_slices[0].object compare
    (0x435939, 1, 0x44B34),  # slide_slices[0].object replacement
    (0x435962, 1, 0x4423C),  # floor_corners[0].object compare
    (0x43596D, 1, 0x443FC),  # slide_corners[0].object replacement
    (0x4359E3, 1, 0x44B34),  # slide_slices[0].object compare
    (0x4359EB, 1, 0x447B4),  # floor_slices[0].object replacement
    (0x435A14, 1, 0x443FC),  # slide_corners[0].object compare
    (0x435A1F, 1, 0x4423C),  # floor_corners[0].object replacement
)

# The pool constructor's runtime-row displacement numerically collides with an
# IDA auto-symbol at 0x5ccac8. Normalize this one proven LEA operand so
# Hex-Rays can fold the typed cRSubGame receiver into runtime_rows instead
# of treating the displacement as the address of an unrelated byte global.
RUNTIME_POOL_ROW_OFFSET_OPERANDS = (
    (0x4082EC, 1, 0x5CCAC8),
)

# The fringe builder has the same runtime-row displacement collision. Normalize
# only its proven LEA operand and preserve the surrounding typed owner graph.
FRINGE_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x434C0C, 1, 0x5CCAC8),
)

# Four small consumers retain a typed cRSubGame base while taking a
# borrowed pointer into runtime_rows. Their proven displacements numerically
# collide with IDA auto-symbol addresses, so normalize only these exact
# operands and let the receiver type recover the shared SubRow owner.
RUNTIME_ROW_LOOKUP_OFFSET_OPERANDS = (
    (0x43D49E, 1, 0x5CCAC8),
    (0x43D4BE, 1, 0x5CCAC8),
)

PROJECT_ATTACHMENT_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x4444D4, 1, 0x5CCAC8),
)

REMOVE_SUBGAME_BODS_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x44091F, 1, 0x5CCAD8),  # runtime_rows[0].row_model list_next
)

MERGE_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x4351CB, 1, 0x5CCB7C),  # runtime_rows[0].attachment_body list_flags
)

# cRSubLoc teardown obtains the containing GameRoot and addresses one borrowed
# SubRow through a row-stride byte offset. These four root-relative
# displacements numerically collide with IDA auto-symbols, so normalize only
# the proven row flag and attachment-body operands. The typed GameRoot and
# cRSubGame owners can then recover runtime_rows[row] without installing
# overlapping globals.
REMOVE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x439BF0, 1, 0x6410E0),  # runtime_rows[row].flags
    (0x439BFF, 1, 0x641194),  # attachment_body list_flags precheck
    (0x439C0A, 1, 0x641194),  # attachment_body list_flags
    (0x439C10, 1, 0x641190),  # attachment_body list node
)

# The entry-tile update stores a borrowed skirt colour into the same row's
# embedded attachment body. Its root-relative displacement has the same
# auto-symbol collision and is normalized independently.
UPDATE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x439FC2, 1, 0x6411B8),  # runtime_rows[row].attachment_body.color
)

# BuildLevel carries the owning cRSubGame base while advancing one
# 0xf4-byte SubRow lane. IDA otherwise interprets the large structure
# displacements as addresses of byte_5CCAC8/unk_5CCBxx globals, even after the
# exact RuntimeRowStrideAnchor local is typed. Normalize every proven row-field
# operand, plus the clear loop's projection-payload cursor, so Hex-Rays can
# render the same borrowed SubRow ownership already preserved by Binary Ninja.
POPULATE_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x4360ED, 1, 0x5CCB5C),  # clear cursor at runtime_rows[0].parcel_spawn_position.y
    (0x4363D9, 1, 0x5CCAC8),  # mirrored row flags pointer
    (0x4363E0, 1, 0x5CCAC8),  # mirrored row flags load
    (0x436411, 1, 0x5CCAC8),  # no-fall row flags pointer
    (0x436418, 1, 0x5CCAC8),  # no-fall row flags load
    (0x436438, 1, 0x5CCAC8),  # jetpack-off row flags pointer
    (0x43643F, 1, 0x5CCAC8),  # jetpack-off row flags load
    (0x43645C, 0, 0x5CCBB4),  # source_segment
    (0x436462, 0, 0x5CCBB8),  # row_event_id
    (0x436475, 1, 0x5CCAC8),  # row flags load
    (0x43647D, 0, 0x5CCAC8),  # row flags store
    (0x43649E, 1, 0x5CCACC),  # row_model body
    (0x4364AA, 1, 0x5CCB04),  # row_model transform
    (0x4364BB, 1, 0x5CCB34),  # row_model position
    (0x4364D5, 1, 0x5CCB3C),  # row_model position.z load; x87 st0 is operand 0
    (0x4364DB, 1, 0x5CCB3C),  # row_model position.z store; x87 st0 is operand 0
    (0x4364EA, 1, 0x5CCAC8),  # velocity-present row flags load
    (0x4364F8, 0, 0x5CCAC8),  # velocity-present row flags store
    (0x436500, 1, 0x5CCB4C),  # row_model velocity pointer
    (0x436506, 0, 0x5CCB4C),  # row_model velocity.x
    (0x43651C, 0, 0x5CCB54),  # row_model velocity.z clear
    (0x436522, 0, 0x5CCB50),  # row_model velocity.y clear
    (0x436528, 0, 0x5CCB4C),  # row_model velocity.x clear
    (0x43653B, 1, 0x5CCAC8),  # parcel row flags load
    (0x436546, 0, 0x5CCAC8),  # parcel row flags store
    (0x436565, 1, 0x5CCB58),  # parcel_spawn_position
    (0x43656B, 0, 0x5CCB64),  # parcel_set_id
    (0x43658A, 1, 0x5CCAC8),  # path row flags load
    (0x436592, 0, 0x5CCAC8),  # path row flags store
    (0x43659E, 0, 0x5CCB68),  # attachment_template_index
    (0x4365AD, 1, 0x5CCAC8),  # star-marker row flags load
    (0x4365B5, 0, 0x5CCAC8),  # star-marker row flags store
    (0x4365CA, 0, 0x5CCAC8),  # ring-none row flag
    (0x4365DF, 0, 0x5CCAC8),  # ring-normal row flag
    (0x4365F4, 0, 0x5CCAC8),  # ring-power-up row flag
    (0x436609, 0, 0x5CCAC8),  # ring-explode row flag
    (0x43661E, 0, 0x5CCAC8),  # ring-slow row flag
    (0x436CFA, 1, 0x5CCB68),  # attachment_template_index load
    (0x436D84, 1, 0x5CCB78),  # attachment_body
    (0x436D90, 1, 0x5CCB7C),  # attachment_body list flags load
    (0x436D9C, 0, 0x5CCB7C),  # attachment_body list flags store
    (0x436DA8, 0, 0x5CCB74),  # installed_heading_delta
    (0x436DC1, 1, 0x5CCAC8),  # stamped-row cursor
    (0x436E08, 1, 0x5CCAC8),  # digit-zero row flags load
    (0x436E1A, 0, 0x5CCAC8),  # digit-zero row flags store
    (0x436E20, 0, 0x5CCB64),  # digit-zero parcel_set_id
    (0x436E30, 1, 0x5CCB58),  # digit-zero projection x; x87 st0 is operand 0
    (0x436E40, 0, 0x5CCB5C),  # digit-zero projection y
    (0x436E4C, 1, 0x5CCB60),  # digit-zero projection z; x87 st0 is operand 0
    (0x436E59, 1, 0x5CCB58),  # mirrored projection x load; x87 st0 is operand 0
    (0x436E65, 1, 0x5CCB58),  # mirrored projection x store; x87 st0 is operand 0
    (0x436E6B, 0, 0x5CCAC8),  # attachment-row flags test
    (0x436EF2, 0, 0x5CCB90),  # attachment_body position.z clear
    (0x436EF8, 0, 0x5CCB8C),  # attachment_body position.y clear
    (0x436EFE, 0, 0x5CCB88),  # attachment_body position.x clear
    (0x436F88, 0, 0x5CCB88),  # attachment_body position.x
    (0x436F92, 1, 0x5CCB90),  # attachment_body position.z; x87 st0 is operand 0
    (0x436FAB, 1, 0x5CCBA0),  # attachment_body color
    (0x436FE2, 1, 0x5CCB9C),  # attachment_body object
    (0x436FF3, 1, 0x5CCB7C),  # attachment_body list flags load
    (0x436FFD, 0, 0x5CCB7C),  # attachment_body list flags store
)

# Both parcel-claim loops retain a containing cRSubGame base and access a
# borrowed SubRow through the 0x5ccac8 runtime-row slab offset. Those numeric
# displacements collide with IDA auto-symbol addresses, so Hex-Rays otherwise
# prints byte_5CCAC8/unk_5CCB58 even after the exact locals are typed. Normalize
# only the proven row-field operands; the surrounding registers keep their
# native RuntimeRowStrideAnchor identities and the final pass keeps SubRow*.
PLACE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x443DBA, 0, 0x5CCAC8),  # parcel-set row flags test
    (0x443DDB, 1, 0x5CCAC8),  # parcel-set row flags load
    (0x443DE6, 1, 0x5CCB58),  # parcel-set projection payload
    (0x443DF0, 0, 0x5CCAC8),  # parcel-set row flags store
    (0x443E2E, 0, 0x5CCAC8),  # parcel-set mirrored-row test
    (0x443FFF, 1, 0x5CCAC8),  # zero-bucket row flags test
    (0x444024, 1, 0x5CCAC8),  # zero-bucket row flags load
    (0x44402A, 1, 0x5CCB58),  # zero-bucket projection payload
    (0x44403D, 0, 0x5CCAC8),  # zero-bucket row flags store
    (0x444079, 0, 0x5CCAC8),  # zero-bucket mirrored-row test
    (0x444161, 1, 0x5CCAC8),  # final direct SubRow cursor
)

# Challenge placement has the same containing-anchor and direct-row cursor
# ownership as normal placement. Normalize only the selected-row field
# operands and final runtime_rows LEA whose numeric displacements collide with
# IDA auto-symbol addresses. The earlier parcel_set_id scan remains a native
# field cursor rather than a fabricated container-of owner, but its exact
# displacement is normalized so the typed receiver exposes its real origin.
CHALLENGE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x4442A0, 1, 0x5CCB64),  # runtime_rows[0].parcel_set_id field cursor
    (0x444323, 1, 0x5CCAC8),  # selected row flags load before anchor LEA
    (0x444331, 0, 0x5CCAC8),  # selected row flags store
    (0x444337, 1, 0x5CCB5C),  # selected row projection y load
    (0x444343, 1, 0x5CCB5C),  # selected row projection y store
    (0x444349, 0, 0x5CCAC8),  # selected row mirrored test
    (0x444352, 1, 0x5CCB58),  # selected row projection x load
    (0x44435E, 1, 0x5CCB58),  # selected row projection x store
    (0x444364, 1, 0x5CCAC8),  # selected row parcel-coordinate flags load
    (0x444373, 1, 0x5CCB60),  # selected row projection z load
    (0x44437F, 1, 0x5CCB60),  # selected row projection z store
    (0x4443D7, 1, 0x5CCAC8),  # final direct SubRow cursor
)

# The main tick carries one cRSubGame-relative row anchor through a stack
# save while EDI is reused for the eight-cell scan. These are the only row
# displacements whose numeric values collide with IDA address symbols; the
# cell and projected-ring offsets remain ordinary structure displacements.
UPDATE_SUBGAME_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x43902B, 1, 0x5CCAC8),  # row flags load before anchor LEA
    (0x43903D, 1, 0x5CCAD0),  # row primary-body list flags
    (0x439043, 1, 0x5CCACC),  # row primary-body base
    (0x43909F, 0, 0x5CCAC8),  # row parcel-spawn flag
    (0x4390B7, 1, 0x5CCB58),  # row projection payload
    (0x4391D4, 1, 0x5CCB78),  # row attachment-body base
    (0x439228, 1, 0x5CCB88),  # row attachment-body position
    (0x439569, 1, 0x5CCAC8),  # authored-ring row flags
    (0x439827, 1, 0x5CCAC8),  # ambient-ring row flags
)

# The parcel-spawn runtime flag is an immediate mask, not a data reference.
# Its numeric value falls inside IDA's address space and can therefore inherit
# an unrelated global symbol (currently a SpriteManager array element) after
# caller reanalysis. Preserve the evidenced 0x800000 mask as a number so the
# decompiler cannot fabricate ownership for this bit test.
UPDATE_SUBGAME_RUNTIME_FLAG_OPERANDS = (
    (0x4390A8, 1, 0x800000),
)

# The player tick first resolves a row-event cell, then revisits the current
# runtime row for attachment entry. In both blocks Hex-Rays inherits false
# globals because the exact SubRow slab displacements are also valid image
# addresses. Normalize only those nine evidenced operands: the typed
# cRSubGame receiver and cRSubLoc locals can then recover the borrowed
# SubRow fields without installing an overlapping global or convenience view.
UPDATE_SUBGOLDY_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x43B709, 1, 0x5CCAC8),  # row-event SubRow base / flags
    (0x43B710, 1, 0x5CCBB8),  # row_event_id
    (0x43BCF3, 1, 0x5CCAC8),  # current-row flags load
    (0x43BD44, 0, 0x5CCAC8),  # primary attachment flag
    (0x43BD98, 1, 0x5CCB6C),  # primary_attachment_cell
    (0x43BDE6, 1, 0x5CCB6C),  # primary attachment source-cell reload
    (0x43BE19, 0, 0x5CCAC8),  # secondary attachment flag
    (0x43BE6D, 1, 0x5CCB70),  # secondary_attachment_cell
    (0x43BEBB, 1, 0x5CCB70),  # secondary attachment source-cell reload
)

# initialize_subgame selects one of the three embedded SubHighScore record
# banks, then publishes that borrowed pointer through active_record_bank. The
# five native displacements numerically collide with unrelated named globals,
# causing Hex-Rays to print parcel/sprite owners even though EBP is the typed
# cRSubGame receiver. Normalize only these proven operands so the shared
# SubHighScore layout can fold the postal, survival, time-trial, and active-bank
# accesses without changing any global symbol.
INITIALIZE_SUBGAME_RECORD_BANK_OFFSET_OPERANDS = (
    (0x43757E, 1, 0x68B4D0),  # SubHighScore::postal_records
    (0x437567, 1, 0x7E7B10),  # SubHighScore::survival_records
    (0x43755F, 1, 0x944150),  # SubHighScore::time_trial_route_records
    (0x43756D, 0, 0x68B4C8),  # SubHighScore::active_record_bank (survival)
    (0x437584, 0, 0x68B4C8),  # SubHighScore::active_record_bank (shared)
)

# The Init method stores its borrowed Player backlink from a relocatable root
# displacement that numerically collides with the tracked g_player_block offset
# symbol. Normalize only that ADD operand so the typed root folds to the exact
# GameRoot::subgame.player child.
SUBHOVER_PLAYER_ROOT_OFFSET_OPERANDS = (
    (0x43A953, 1, 0x42FD7C),
)


TRUSTED_DECLARATIONS = [
    (
        "add_bod_to_front",
        "void __thiscall add_bod_to_front(BodList* list, BodNode* node);",
    ),
    (
        "append_bod_to_end",
        "void __thiscall append_bod_to_end(BodList* list, BodNode* node);",
    ),
    (
        "is_bod_after_sprites",
        "bool __thiscall is_bod_after_sprites(BodBase* bod);",
    ),
    (
        "set_bod_object",
        "int32_t __thiscall set_bod_object(BodBase* bod, Object* object);",
    ),
    (
        "initialize_bod_base",
        "BodBase* __thiscall initialize_bod_base(BodBase* bod);",
    ),
    (
        "initialize_renderable_bod",
        "RenderableBod* __thiscall initialize_renderable_bod(RenderableBod* body);",
    ),
    (
        "apply_bod_position",
        "void __thiscall apply_bod_position(BodBase* bod, TransformMatrix* matrix);",
    ),
    (
        "recycle_bod_to_free_list",
        "void __thiscall recycle_bod_to_free_list(BodList* list, BodNode* node);",
    ),
    (
        "initialize_active_bod",
        "TrackRenderCacheSlot* __thiscall initialize_active_bod(TrackRenderCacheSlot* slot);",
    ),
    (
        "update_active_bod",
        "void __thiscall update_active_bod(TrackRenderCacheSlot* slot);",
    ),
    (
        "update_row_model",
        "void __thiscall update_row_model(RowModel* row_model);",
    ),
    (
        "reset_landscape_manager",
        "void __thiscall reset_landscape_manager(LandscapeManager* manager);",
    ),
    (
        "load_landscape_script_by_name",
        "int32_t __thiscall load_landscape_script_by_name(LandscapeManager* manager, char* script_name);",
    ),
    (
        "initialize_slug_voice_manager",
        "void __thiscall initialize_slug_voice_manager(SlugVoiceManager* manager);",
    ),
    (
        "update_slug_voice_manager",
        "void __thiscall update_slug_voice_manager(SlugVoiceManager* manager);",
    ),
    (
        "initialize_thanks_for_playing_screen",
        "void __thiscall initialize_thanks_for_playing_screen(cRSplash* splash);",
    ),
    (
        "uninit_thanks_screen",
        "void __thiscall uninit_thanks_screen(cRSplash* splash);",
    ),
    (
        "update_thanks_for_playing_screen",
        "void __thiscall update_thanks_for_playing_screen(cRSplash* splash);",
    ),
    (
        "initialize_noop_renderable_bod",
        "RenderableBod* __thiscall initialize_noop_renderable_bod(RenderableBod* body);",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "cRSubGame* __thiscall initialize_runtime_pools_and_path_template_bank(cRSubGame* game);",
    ),
    (
        "initialize_track_row_runtime",
        "SubRow* __thiscall initialize_track_row_runtime(SubRow* row);",
    ),
    (
        "initialize_fringe_object",
        "cRFringe* __thiscall initialize_fringe_object(cRFringe* fringe);",
    ),
    (
        "refresh_fringe_object_draw_list",
        "void __thiscall refresh_fringe_object_draw_list(cRFringe* fringe);",
    ),
    (
        "initialize_object_constructor_thunk",
        "Object* __thiscall initialize_object_constructor_thunk(Object* object);",
    ),
    (
        "initialize_click_start_controller_runtime",
        "ClickStart* __thiscall initialize_click_start_controller_runtime(ClickStart* click_start);",
    ),
    (
        "initialize_click_start",
        "void __thiscall initialize_click_start(ClickStart* click_start, Player* player);",
    ),
    (
        "update_click_start",
        "void __thiscall update_click_start(ClickStart* click_start);",
    ),
    (
        "initialize_active_landscape_entry",
        "ActiveLandscapeEntry* __thiscall initialize_active_landscape_entry(ActiveLandscapeEntry* active_entry);",
    ),
    (
        "activate_landscape_entry",
        "void __thiscall activate_landscape_entry(LandscapeManager* manager, int32_t script_index);",
    ),
    (
        "clear_active_landscape_entries",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager);",
    ),
    (
        "update_active_landscape_entry",
        "void __thiscall update_active_landscape_entry(ActiveLandscapeEntry* active_entry);",
    ),
    (
        "initialize_fringe_manager",
        "void __thiscall initialize_fringe_manager(cRFringeManager* manager);",
    ),
    (
        "allocate_fringe_object",
        "cRFringe* __thiscall allocate_fringe_object(cRFringeManager* manager);",
    ),
    (
        "initialize_golb_shot",
        "GolbShot* __thiscall initialize_golb_shot(GolbShot* shot);",
    ),
    (
        "kill_golb",
        "void __thiscall kill_golb(GolbShot* shot);",
    ),
    (
        "update_golb_ai",
        "void __thiscall update_golb_ai(GolbShot* shot);",
    ),
    (
        "create_golb",
        "void __thiscall create_golb(GolbShot* shot, Player* player, int32_t spawn_selector, int32_t shot_slot_index);",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(Player* owner, Player* shoot_source);",
    ),
    (
        "spawn_golb_trail_sprite",
        "Sprite* __thiscall spawn_golb_trail_sprite(GolbShot* shot, Vec3* position);",
    ),
    (
        "spawn_golb_smoke",
        "void __thiscall spawn_golb_smoke(GolbShot* shot, Vec3* position);",
    ),
    (
        "spawn_golb_impact_sprite",
        "void __thiscall spawn_golb_impact_sprite(GolbShot* shot, Vec3* position);",
    ),
    (
        "initialize_path_follow_golb",
        "int32_t __thiscall initialize_path_follow_golb(GolbPathFollowState* state, cRSubLoc* source_cell, const Vec3* position, GolbShot* shot);",
    ),
    (
        "traverse_path_follow_golb",
        "int32_t __thiscall traverse_path_follow_golb(GolbPathFollowState* state, float path_factor, Vec3* position, Vec3* velocity);",
    ),
    (
        "d3dx_create_texture_from_file_in_memory_ex",
        "int32_t __stdcall d3dx_create_texture_from_file_in_memory_ex(void* device, void* source_data, uint32_t source_size, uint32_t width, uint32_t height, uint32_t mip_levels, uint32_t usage, uint32_t format, uint32_t pool, uint32_t filter, uint32_t mip_filter, uint32_t color_key, void* source_info, void* palette, void** texture);",
    ),
    (
        "d3dx_create_texture_from_file_ex",
        "int32_t __stdcall d3dx_create_texture_from_file_ex(void* device, char* path, uint32_t width, uint32_t height, uint32_t mip_levels, uint32_t usage, uint32_t format, uint32_t pool, uint32_t filter, uint32_t mip_filter, uint32_t color_key, void* source_info, void* palette, void** texture);",
    ),
    (
        "d3dx_create_texture_from_file",
        "int32_t __stdcall d3dx_create_texture_from_file(void* device, char* path, void** texture);",
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
        "initialize_loading_screen",
        "void __thiscall initialize_loading_screen(cRLoadingBar* loading_bar);",
    ),
    (
        "destroy_loading_screen",
        "void __thiscall destroy_loading_screen(cRLoadingBar* loading_bar);",
    ),
    (
        "update_loading_screen",
        "void __thiscall update_loading_screen(cRLoadingBar* loading_bar);",
    ),
    (
        "destroy_options_menu",
        "void __thiscall destroy_options_menu(cROptions* options);",
    ),
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
        "initialize_sub_loc",
        "cRSubLoc* __thiscall initialize_sub_loc(cRSubLoc* cell);",
    ),
    (
        "remove_sub_loc",
        "void __thiscall remove_sub_loc(cRSubLoc* cell);",
    ),
    (
        "update_sub_loc",
        "void __thiscall update_sub_loc(cRSubLoc* cell);",
    ),
    (
        "initialize_damage_gauge",
        "void __thiscall initialize_damage_gauge(cRDamageGuage* damage_guage);",
    ),
    (
        "update_damage_gauge",
        "void __thiscall update_damage_gauge(cRDamageGuage* damage_guage);",
    ),
    (
        "apply_damage_gauge_delta",
        "void __thiscall apply_damage_gauge_delta(cRDamageGuage* damage_guage, float delta, bool force);",
    ),
    (
        "get_track_cell_row_index",
        "int32_t __thiscall get_track_cell_row_index(cRSubLoc* cell);",
    ),
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(cRPathManager *manager, char *name);",
    ),
    (
        "border_mouse_test",
        "uint8_t __thiscall border_mouse_test(FrontendWidget* widget);",
    ),
    (
        "initialize_player_presentation_controller",
        "Snail* __thiscall initialize_player_presentation_controller(Snail* snail);",
    ),
    (
        "initialize_global_identity_matrix_thunk",
        "void __cdecl initialize_global_identity_matrix_thunk();",
    ),
    (
        "initialize_global_identity_matrix",
        "void __cdecl initialize_global_identity_matrix();",
    ),
    (
        "initialize_uniform_scale_matrix",
        "TransformMatrix* __thiscall initialize_uniform_scale_matrix(TransformMatrix* transform, float scale);",
    ),
    (
        "multiply_vector_by_matrix_copy",
        "Vec3* __thiscall multiply_vector_by_matrix_copy(const Vec3* vector, Vec3* out, const TransformMatrix* matrix);",
    ),
    (
        "multiply_vector_by_matrix",
        "void __thiscall multiply_vector_by_matrix(Vec3* vector, TransformMatrix matrix);",
    ),
    (
        "rotate_vector_by_matrix",
        "Vec3* __thiscall rotate_vector_by_matrix(Vec3* vector, const TransformMatrix* matrix);",
    ),
    (
        "dot_vectors",
        "double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs);",
    ),
    (
        "dot_vector",
        "float __thiscall dot_vector(const Vec3* vector, const Vec3* rhs);",
    ),
    (
        "normalize_vector",
        "float __thiscall normalize_vector(Vec3* vector);",
    ),
    (
        "vector_magnitude",
        "float __thiscall vector_magnitude(const Vec3* vector);",
    ),
    (
        "normalize_vector_from_source",
        "float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src);",
    ),
    (
        "cross_vectors",
        "void __thiscall cross_vectors(Vec3* out, const Vec3* lhs, const Vec3* rhs);",
    ),
    (
        "noop_this_constructor",
        "void* __thiscall noop_this_constructor(void* self);",
    ),
    (
        "get_or_create_texture_ref",
        "TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, void* payload, int32_t flags);",
    ),
    (
        "get_path_nodes",
        "void __fastcall get_path_nodes(cRPath* self);",
    ),
    (
        "calc_path_length_z",
        "void __fastcall calc_path_length_z(cRPath* self);",
    ),
    (
        "mirror_path",
        "void __thiscall mirror_path(cRPath* self, cRPath* source);",
    ),
    (
        "set_matrix_identity",
        "void __thiscall set_matrix_identity(TransformMatrix* transform);",
    ),
    (
        "set_matrix_rotation_identity",
        "void __thiscall set_matrix_rotation_identity(TransformMatrix* transform);",
    ),
    (
        "initialize_matrix_from_values",
        "TransformMatrix* __thiscall initialize_matrix_from_values(TransformMatrix* transform, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);",
    ),
    (
        "initialize_quaternion_from_axis",
        "void __thiscall initialize_quaternion_from_axis(Quaternion* out, const AxisAngle* axis);",
    ),
    (
        "initialize_axis_from_quaternion",
        "void __thiscall initialize_axis_from_quaternion(AxisAngle* out, const Quaternion* quaternion);",
    ),
    (
        "initialize_quaternion_from_matrix",
        "Quaternion* __thiscall initialize_quaternion_from_matrix(Quaternion* out, const TransformMatrix* matrix);",
    ),
    (
        "initialize_matrix_from_quaternion",
        "TransformMatrix* __thiscall initialize_matrix_from_quaternion(TransformMatrix* out, const Quaternion* quaternion);",
    ),
    (
        "rotate_matrix_local_x",
        "void __thiscall rotate_matrix_local_x(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_local_y",
        "void __thiscall rotate_matrix_local_y(TransformMatrix* transform, float angle);",
    ),
    (
        "rotate_matrix_local_z",
        "void __thiscall rotate_matrix_local_z(TransformMatrix* transform, float angle);",
    ),
    (
        "orthogonalize_matrix",
        "void __thiscall orthogonalize_matrix(TransformMatrix* transform);",
    ),
    (
        "invert_matrix_in_place",
        "void __thiscall invert_matrix_in_place(TransformMatrix* transform);",
    ),
    (
        "invert_matrix_from_source",
        "void __thiscall invert_matrix_from_source(TransformMatrix* out, const TransformMatrix* source);",
    ),
    (
        "multiply_matrices",
        "void __thiscall multiply_matrices(TransformMatrix* out, const TransformMatrix* lhs, const TransformMatrix* rhs);",
    ),
    (
        "multiply_matrix_assign",
        "void __thiscall multiply_matrix_assign(TransformMatrix* matrix, const TransformMatrix* rhs);",
    ),
    (
        "multiply_matrix",
        "void __thiscall multiply_matrix(TransformMatrix* matrix, const TransformMatrix* rhs);",
    ),
    (
        "premultiply_matrix_in_place",
        "void __thiscall premultiply_matrix_in_place(TransformMatrix* matrix, const TransformMatrix* lhs);",
    ),
    (
        "set_matrix_z_direction",
        "void __thiscall set_matrix_z_direction(TransformMatrix* transform, const Vec3* direction);",
    ),
    (
        "look_at_point",
        "void __thiscall look_at_point(TransformMatrix* transform, const Vec3* target);",
    ),
    (
        "interpolate_matrix_rotation",
        "void __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha);",
    ),
    (
        "linear_interpolate_matrix",
        "void __thiscall linear_interpolate_matrix(TransformMatrix* out, const TransformMatrix* from, const TransformMatrix* to, float alpha);",
    ),
    (
        "compute_kind42_attachment_transform",
        "void __thiscall compute_kind42_attachment_transform(cRPath* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle);",
    ),
    (
        "request_object_vertices",
        "void __thiscall request_object_vertices(Object* object, int32_t vertex_count);",
    ),
    (
        "request_object_vertex_colours",
        "void __fastcall request_object_vertex_colours(Object* object);",
    ),
    (
        "request_object_facequads",
        "void __thiscall request_object_facequads(Object* object, int32_t facequad_count);",
    ),
    (
        "set_color_rgba",
        "tColour* __thiscall set_color_rgba(tColour* color, float r, float g, float b, float a);",
    ),
    (
        "parse_next_int32",
        "int32_t __cdecl parse_next_int32(char** cursor);",
    ),
    (
        "parse_next_space_delimited_token",
        "void __cdecl parse_next_space_delimited_token(char** cursor, char* out);",
    ),
    (
        "parse_next_float32",
        "float __cdecl parse_next_float32(char** cursor);",
    ),
    (
        "initialize_track_render_cache_manager",
        "void __thiscall initialize_track_render_cache_manager(SegmentCache* manager);",
    ),
    (
        "build_track_render_caches",
        "void __thiscall build_track_render_caches(SegmentCache* manager, tColour skirt_color);",
    ),
    (
        "add_track_cache_vertex",
        "int32_t __thiscall add_track_cache_vertex(SegmentCache* manager, Object* source, Vec3* position, int32_t source_index, float u, float v, ObjectRenderVertex* vertices, int32_t* vertex_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv);",
    ),
    (
        "append_track_cache_object",
        "int32_t __thiscall append_track_cache_object(SegmentCache* manager, int32_t row_index, Object* source, Vec3* position, ObjectRenderVertex* vertices, int32_t* vertex_count, uint16_t* indices, int32_t* index_count, int32_t max_vertices, int32_t max_indices, uint32_t color, uint8_t project_uv);",
    ),
    (
        "update_track_render_cache_rows",
        "void __thiscall update_track_render_cache_rows(SegmentCache* manager);",
    ),
    (
        "remove_track_render_cache_bods",
        "void __thiscall remove_track_render_cache_bods(SegmentCache* manager);",
    ),
    (
        "is_sub_loc_floor",
        "int32_t __fastcall is_sub_loc_floor(cRSubLoc* cell);",
    ),
    (
        "is_sub_loc_slide",
        "int32_t __fastcall is_sub_loc_slide(cRSubLoc* cell);",
    ),
    (
        "is_sub_loc_ramp",
        "int32_t __fastcall is_sub_loc_ramp(cRSubLoc* cell);",
    ),
    (
        "is_sub_loc_empty",
        "int32_t __fastcall is_sub_loc_empty(cRSubLoc* cell);",
    ),
    (
        "set_color_alpha",
        "void __thiscall set_color_alpha(tColour* color, float alpha);",
    ),
    (
        "set_color_grayscale",
        "void __thiscall set_color_grayscale(tColour* color, float intensity);",
    ),
    (
        "set_color_rgb",
        "void __thiscall set_color_rgb(tColour* color, float r, float g, float b);",
    ),
    (
        "set_color_white",
        "void __thiscall set_color_white(tColour* color);",
    ),
    (
        "set_color_black",
        "void __thiscall set_color_black(tColour* color);",
    ),
    (
        "get_track_skirt_color",
        "tColour* __thiscall get_track_skirt_color(cRSubGame* game, tColour* out);",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(cRSubGame* game, cRSubLoc* cell, Player* player);",
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
        "initialize_squidge",
        "void __thiscall initialize_squidge(cRSquidge* squidge);",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(cRSquidge* squidge, float value);",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(cRSquidge* squidge, float value);",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(cRSquidge* squidge);",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkin* snail_skin);",
    ),
    (
        "build_snail_world_hotspots",
        "void __thiscall build_snail_world_hotspots(Snail* snail);",
    ),
    (
        "extract_snail_local_hotspots",
        "void __thiscall extract_snail_local_hotspots(Snail* snail);",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(Invincible* invincible);",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(Invincible* invincible);",
    ),
    (
        "update_invincible_shell",
        "void __thiscall update_invincible_shell(Invincible* invincible);",
    ),
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(AnimManager* manager);",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(AnimManager* manager);",
    ),
    (
        "advance_frame_sequence",
        "void __thiscall advance_frame_sequence(Movie* movie);",
    ),
    (
        "update_smtracks",
        "void __thiscall update_smtracks(Face* face);",
    ),
    (
        "sample_smtrack_heightmap",
        "void __cdecl sample_smtrack_heightmap(Object* source, float base, float scale, TextureRef* replacement, bool cubic);",
    ),
    (
        "deserialize_compact_high_score_record",
        "unsigned char __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
    ),
    (
        "serialize_compact_high_score_record",
        "int __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkin* snail_skin);",
    ),
    (
        "change_snail_skin",
        "void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds);",
    ),
    (
        "store_color4f",
        "void __thiscall store_color4f(tColour* color, float r, float g, float b, float a);",
    ),
    (
        "pack_color_rgba_u8",
        "tColourSmall* __thiscall pack_color_rgba_u8(tColourSmall* out, tColour* color);",
    ),
    (
        "kill_tip_widgets",
        "void __thiscall kill_tip_widgets(cRTip* tip);",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(cRTip* tip, cRTipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip",
        "void __thiscall update_tip(cRTip* tip);",
    ),
    (
        "initialize_tip_manager",
        "void __thiscall initialize_tip_manager(cRTipManager* manager);",
    ),
    (
        "uninit_tips",
        "void __thiscall uninit_tips(cRTipManager* manager);",
    ),
    (
        "enqueue_tip_message",
        "cRTip* __thiscall enqueue_tip_message(cRTipManager* manager, cRTipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip_manager",
        "void __thiscall update_tip_manager(cRTipManager* manager);",
    ),
    (
        "initialize_tutorial",
        "void __thiscall initialize_tutorial(cRTutorial* tutorial);",
    ),
    (
        "uninit_tutorial",
        "void __thiscall uninit_tutorial(cRTutorial* tutorial);",
    ),
    (
        "update_tutorial",
        "void __thiscall update_tutorial(cRTutorial* tutorial);",
    ),
    (
        "update_input_ok",
        "void __thiscall update_input_ok(InputOkState* input_ok);",
    ),
    (
        "initialize_input_ok",
        "void __thiscall initialize_input_ok(InputOkState* input_ok);",
    ),
    (
        "update_twinkle_manager",
        "void __thiscall update_twinkle_manager(TwinkleManager* manager);",
    ),
    (
        "draw_twinkle",
        "void __thiscall draw_twinkle(Twinkle* twinkle);",
    ),
    (
        "update_twinkle",
        "void __thiscall update_twinkle(Twinkle* twinkle);",
    ),
    (
        "update_barrier_ai",
        "void __thiscall update_barrier_ai(BarrierActor* barrier);",
    ),
    (
        "initialize_frontend_widget",
        "void __thiscall initialize_frontend_widget(FrontendWidget* widget, uint32_t widget_flags, char* text, int32_t widget_type, float x, float y, tColour* color, int32_t text_alignment, float anchor_x);",
    ),
    (
        "layout_frontend_widget",
        "void __thiscall layout_frontend_widget(FrontendWidget* widget);",
    ),
    (
        "set_frontend_widget_shortcut_key",
        "void __thiscall set_frontend_widget_shortcut_key(FrontendWidget* widget, int32_t shortcut_key_code);",
    ),
    (
        "stack_widget_below",
        "void __thiscall stack_widget_below(FrontendWidget* widget, FrontendWidget* previous_widget);",
    ),
    (
        "hide_border_init",
        "void __thiscall hide_border_init(FrontendWidget* widget);",
    ),
    (
        "unhide_border_init",
        "void __thiscall unhide_border_init(FrontendWidget* widget);",
    ),
    (
        "unhighlight_border",
        "void __thiscall unhighlight_border(FrontendWidget* widget);",
    ),
    (
        "highlight_border",
        "void __thiscall highlight_border(FrontendWidget* widget);",
    ),
    (
        "border_sprite_extend",
        "void __thiscall border_sprite_extend(FrontendWidget* widget, int32_t sprite_a, int32_t sprite_c, int32_t sprite_b, uint8_t wobble_positive);",
    ),
    (
        "border_input_text_init",
        "void __thiscall border_input_text_init(FrontendWidget* widget, int32_t capacity, char* text, int32_t flags);",
    ),
    (
        "update_frontend_widget_interaction",
        "void __thiscall update_frontend_widget_interaction(FrontendWidget* widget);",
    ),
    (
        "border_input_text",
        "void __thiscall border_input_text(FrontendWidget* widget);",
    ),
    (
        "reset_tooltip",
        "void __thiscall reset_tooltip(FrontendWidgetTooltip* tooltip);",
    ),
    (
        "update_tooltip",
        "void __thiscall update_tooltip(FrontendWidgetTooltip* tooltip);",
    ),
    (
        "initialize_cameraman",
        "void __thiscall initialize_cameraman(Cameraman* cameraman);",
    ),
    (
        "update_cameraman",
        "void __thiscall update_cameraman(Cameraman* cameraman);",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot);",
    ),
    (
        "health_collect_particles",
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup);",
    ),
    (
        "set_subgoldy_shoot_flags",
        "void __thiscall set_subgoldy_shoot_flags(Player* player);",
    ),
    (
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player);",
    ),
    (
        "begin_post_follow_carryover",
        "void __thiscall begin_post_follow_carryover(Player* player);",
    ),
    (
        "initialize_subgoldy_ghost",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner);",
    ),
    (
        "update_subgoldy",
        "void __thiscall update_subgoldy(Player* player);",
    ),
    (
        "play_subgoldy_shoot_sfx",
        "void __thiscall play_subgoldy_shoot_sfx(Player* player);",
    ),
    (
        "set_subgoldy_ghost_z",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z);",
    ),
    (
        "add_subgoldy_score",
        "void __thiscall add_subgoldy_score(Player* player, int32_t score_kind, int32_t bonus_score);",
    ),
    (
        "clear_subgoldy_score_buckets",
        "void __thiscall clear_subgoldy_score_buckets(Player* player);",
    ),
    (
        "display_score_stats",
        "void __thiscall display_score_stats(Player* player);",
    ),
    (
        "initialize_subgoldy_resurrect",
        "void __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss);",
    ),
    (
        "update_subgoldy_resurrect",
        "void __thiscall update_subgoldy_resurrect(Player* player);",
    ),
    (
        "kill_subgoldy",
        "void __thiscall kill_subgoldy(Player* player);",
    ),
    (
        "initialize_subgoldy_death",
        "void __thiscall initialize_subgoldy_death(Player* player);",
    ),
    (
        "end_jetpack_hover",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover);",
    ),
    (
        "update_jetpack_gauge",
        "void __thiscall update_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "uninit_jet_particles",
        "void __thiscall uninit_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jet_particles",
        "void __thiscall initialize_jet_particles(SubHover* sub_hover);",
    ),
    (
        "update_jet_particles",
        "void __thiscall update_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jetpack_gauge",
        "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot);",
    ),
    (
        "arm_jetpack_gauge",
        "void __thiscall arm_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "firework_shoot",
        "void __thiscall firework_shoot(FireWork* firework, Vec3* position, int32_t owner, int32_t texture_id, int32_t count);",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner);",
    ),
    (
        "initialize_track_speedup_runtime",
        "SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup);",
    ),
    (
        "update_track_speedup",
        "void __thiscall update_track_speedup(SubSpeedUp* speedup);",
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
        "initialize_track_health_pickup_runtime",
        "SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup);",
    ),
    (
        "update_track_health_pickup",
        "void __thiscall update_track_health_pickup(SubHealth* pickup);",
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
        "handle_subgoldy_collisions",
        "void __thiscall handle_subgoldy_collisions(Player* player);",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(Snail* snail, int32_t shoot_flags);",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state);",
    ),
    (
        "release_snail_weapons",
        "void __thiscall release_snail_weapons(Snail* snail);",
    ),
    (
        "update_snail_presentation",
        "void __thiscall update_snail_presentation(Snail* snail);",
    ),
    (
        "dispatch_cutscene_animation",
        "void __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "initialize_cutscene_ai",
        "void __thiscall initialize_cutscene_ai(CutScene* cutscene);",
    ),
    (
        "update_cutscene",
        "void __thiscall update_cutscene(CutScene* cutscene);",
    ),
    (
        "update_progress_bar",
        "void __thiscall update_progress_bar(cRProgressBar* progress_bar);",
    ),
    (
        "initialize_warning",
        "void __thiscall initialize_warning(cRWarning* warning);",
    ),
    (
        "uninit_warning",
        "void __thiscall uninit_warning(cRWarning* warning);",
    ),
    (
        "start_warning",
        "void __thiscall start_warning(cRWarning* warning);",
    ),
    (
        "stop_warning",
        "void __thiscall stop_warning(cRWarning* warning);",
    ),
    (
        "stop_warning_sample",
        "void __thiscall stop_warning_sample(cRWarning* warning);",
    ),
    (
        "update_warning",
        "void __thiscall update_warning(cRWarning* warning);",
    ),
    (
        "initialize_nuke",
        "void __thiscall initialize_nuke(cRNuke* nuke);",
    ),
    (
        "update_nuke",
        "void __thiscall update_nuke(cRNuke* nuke);",
    ),
    (
        "uninit_nuke",
        "void __thiscall uninit_nuke(cRNuke* nuke);",
    ),
    (
        "get_track_grid_cell_at_world_position",
        "cRSubLoc* __thiscall get_track_grid_cell_at_world_position(cRSubGame* game, Vec3* position);",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "SubRow* __thiscall get_track_runtime_cell_at_world_z(cRSubGame* game, Vec3* position);",
    ),
    (
        "project_position_onto_track_attachment",
        "void __thiscall project_position_onto_track_attachment(cRSubGame* game, Vec3* position, float* out_angle);",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(cRSubGame* game, Vec3* position);",
    ),
    (
        "spawn_track_health_pickup",
        "void __thiscall spawn_track_health_pickup(cRSubGame* game, cRSubLoc* cell, Player* player);",
    ),
    (
        "spawn_track_jetpack_pickup",
        "void __thiscall spawn_track_jetpack_pickup(cRSubGame* game, cRSubLoc* cell, Player* player);",
    ),
    (
        "is_neighbor_cell_solid",
        "bool __thiscall is_neighbor_cell_solid(cRSubGame* game, cRSubLoc* cell, int32_t lane_offset, int32_t row_offset);",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "void __thiscall try_enter_track_attachment_from_swept_motion(cRPath* self, float world_x, float world_y, float world_z, float sweep_dx, float sweep_dy, float sweep_dz, cRSubLoc* source_cell);",
    ),
    (
        "get_path_position_at_node",
        "void __thiscall get_path_position_at_node(cRPath* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local);",
    ),
    (
        "is_point_inside_track_attachment",
        "bool __thiscall is_point_inside_track_attachment(cRPath* self, Vec3 probe, Vec3 swept_motion, cRSubLoc* cell);",
    ),
    (
        "begin_track_attachment_follow_state",
        "void __thiscall begin_track_attachment_follow_state(cRPathFollowGoldy* follow_state, cRSubLoc* source_cell, const Vec3* world_position, Player* player);",
    ),
    (
        "update_track_attachment_follow_state",
        "int32_t __thiscall update_track_attachment_follow_state(cRPathFollowGoldy* follow_state, float path_factor, Vec3* out_position, Vec3* motion);",
    ),
    (
        "initialize_loopout_path_template_pair",
        "void __thiscall initialize_loopout_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_cage2_path_template_pair",
        "void __thiscall initialize_cage2_path_template_pair(cRPath* self, int32_t width_cells_, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_supertramp_path_template_pair",
        "void __thiscall initialize_supertramp_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture);",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "void __thiscall initialize_halfpipe_path_template_pair(cRPath* self, float scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_hump_path_template_pair",
        "void __thiscall initialize_hump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "void __thiscall initialize_looptheloop_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_looptheloopw_path_template_pair",
        "void __thiscall initialize_looptheloopw_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_dump_path_template_pair",
        "void __thiscall initialize_dump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_dip_path_template_pair",
        "void __thiscall initialize_dip_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_screw_path_template_pair",
        "void __thiscall initialize_screw_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_slalom_path_template_pair",
        "void __thiscall initialize_slalom_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_worm_path_template_pair",
        "void __thiscall initialize_worm_path_template_pair(cRPath* self, char* texture_path);",
    ),
    (
        "initialize_slalombig_path_template_pair",
        "void __thiscall initialize_slalombig_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_sweep_path_template_pair",
        "void __thiscall initialize_sweep_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_snake_path_template_pair",
        "void __thiscall initialize_snake_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_slalomdouble_path_template_pair",
        "void __thiscall initialize_slalomdouble_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_p_path_template_pair",
        "void __thiscall initialize_p_path_template_pair(cRPath* self, int32_t variant, float scale_arg, int32_t width_cells_, float start_x, float end_x, int32_t curve_segments, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_start_path_template_pair",
        "void __thiscall initialize_start_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnover_path_template_pair",
        "void __thiscall initialize_turnover_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "void __thiscall initialize_turnoverdouble_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "void __thiscall initialize_turnunder_path_template_pair(cRPath* self, float turns, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_wibble_path_template_pair",
        "void __thiscall initialize_wibble_path_template_pair(cRPath* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_invert_path_template_pair",
        "void __thiscall initialize_invert_path_template_pair(cRPath* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_twister_path_template_pair",
        "void __thiscall initialize_twister_path_template_pair(cRPath* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_twister2_path_template_pair",
        "void __thiscall initialize_twister2_path_template_pair(cRPath* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "void __thiscall initialize_loopbow_path_template_pair(cRPath* self, float curve_scale, uint32_t width_cells_arg, bool mode, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_toad_path_template_pair",
        "void __thiscall initialize_toad_path_template_pair(cRPath* self, bool turn_left, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_hill_valley_path_template_pair",
        "void __thiscall initialize_hill_valley_path_template_pair(cRPath* self, int32_t width_cells_, float height, float length, bool centered, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_sbend_path_template_pair",
        "void __thiscall initialize_sbend_path_template_pair(cRPath* self, int32_t width_cells_, float height, float z_amplitude, bool centered, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_subgame",
        "void __thiscall initialize_subgame(cRSubGame* game);",
    ),
    (
        "destroy_subgame",
        "void __thiscall destroy_subgame(cRSubGame* game);",
    ),
    (
        "update_subgame",
        "void __thiscall update_subgame(cRSubGame* game);",
    ),
    (
        "remove_subgame_bods",
        "void __thiscall remove_subgame_bods(cRSubGame* game);",
    ),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(cRSubGame* game, int32_t level_index);",
    ),
    (
        "calc_slider_to_rate",
        "float __thiscall calc_slider_to_rate(cRSubGame* game, float slider);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(cRSubGame* game);",
    ),
    (
        "advance_blink_random",
        "double __thiscall advance_blink_random(cRSubGame* game);",
    ),
    (
        "initialize_blink_random",
        "void __thiscall initialize_blink_random(cRSubGame* game);",
    ),
    (
        "hide_gameplay_scores",
        "void __thiscall hide_gameplay_scores(cRSubGame* game);",
    ),
    (
        "unhide_gameplay_scores",
        "void __thiscall unhide_gameplay_scores(cRSubGame* game);",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(cRSubGame* game);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "void __thiscall rebuild_track_runtime_from_segments(cRSubGame* game, int32_t level_index);",
    ),
    (
        "place_parcels_on_track",
        "void __thiscall place_parcels_on_track(cRSubGame* game);",
    ),
    (
        "place_challenge_parcels_on_track",
        "void __thiscall place_challenge_parcels_on_track(cRSubGame* game);",
    ),
    (
        "mark_track_warning_zones",
        "void __thiscall mark_track_warning_zones(cRSubGame* game);",
    ),
    (
        "select_track_tile_edge_variants",
        "void __thiscall select_track_tile_edge_variants(cRSubGame* game);",
    ),
    (
        "merge_track_tile_runs",
        "void __thiscall merge_track_tile_runs(cRSubGame* game);",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "void __thiscall promote_track_tiles_to_fringe_variants(cRSubGame* game);",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "void __thiscall harmonize_center_lane_floor_slide_variants(cRSubGame* game);",
    ),
    (
        "build_track_fringe_objects",
        "void __thiscall build_track_fringe_objects(cRSubGame* game);",
    ),
    (
        "update_subgame_camera",
        "void __thiscall update_subgame_camera(cRSubGame* runtime);",
    ),
]


def _sync_build_track_render_cache_lvar() -> dict[str, object]:
    address = idc.get_name_ea_simple("build_track_render_caches")
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function"}

    # IDA 9.4 can decline to regenerate this large function immediately after
    # a broad type import even though the durable local override is already
    # correct. Verify that saved fact first instead of needlessly requiring a
    # fresh cfunc.
    settings = ida_hexrays.lvar_uservec_t()
    saved_matches = []
    saved_conflicts = []
    if ida_hexrays.restore_user_lvar_settings(settings, address):
        for index in range(settings.lvvec.size()):
            saved = settings.lvvec.at(index)
            if not saved.ll.is_stk_var() or saved.ll.get_stkoff() != 64:
                continue
            if (
                saved.name == "locals"
                and "TrackRenderCacheBuildLocals" in str(saved.type)
            ):
                saved_matches.append(saved)
            else:
                saved_conflicts.append(saved)
    if len(saved_matches) == 1 and not saved_conflicts:
        return {
            "status": "unchanged",
            "name": saved_matches[0].name,
            "type": str(saved_matches[0].type),
            "verification_mode": "saved_lvar",
        }
    if saved_matches or saved_conflicts:
        return {
            "status": "failed",
            "reason": "unexpected_saved_local_overrides",
            "matching_count": len(saved_matches),
            "conflicting_count": len(saved_conflicts),
        }

    try:
        cfunc = ida_hexrays.decompile(address)
    except ida_hexrays.DecompilationFailure as exc:
        return {
            "status": "failed",
            "reason": "decompile_failed",
            "error": str(exc),
        }
    if cfunc is None:
        return {
            "status": "failed",
            "reason": "decompile_failed",
            "error": "Hex-Rays returned no cfunc",
        }
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var() and lvar.get_stkoff() == 64 and lvar.width == 52
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_local_candidates",
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    if lvar.name == "locals" and "TrackRenderCacheBuildLocals" in str(lvar.type()):
        return {"status": "unchanged", "name": lvar.name, "type": str(lvar.type())}

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(
        None,
        "TrackRenderCacheBuildLocals",
        ida_typeinf.BTF_STRUCT,
    ):
        return {"status": "failed", "reason": "missing_local_view_type"}

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "locals"
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {"status": "failed", "reason": "modify_user_lvar_info_failed"}

    return {"status": "applied", "name": "locals", "type": "TrackRenderCacheBuildLocals"}


def _read_renderable_bod_frame_number() -> tuple[
    ida_typeinf.tinfo_t | None,
    dict[str, object],
]:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, "RenderableBod", ida_typeinf.BTF_STRUCT):
        return None, {
            "status": "failed",
            "reason": "missing_RenderableBod_type",
        }
    if owner.get_size() != BOD_CORE_OWNER_SIZES["RenderableBod"]:
        return None, {
            "status": "failed",
            "reason": "owner_size_mismatch",
            "expected_size": BOD_CORE_OWNER_SIZES["RenderableBod"],
            "observed_size": owner.get_size(),
        }

    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None, {
            "status": "failed",
            "reason": "missing_RenderableBod_members",
        }
    candidates = [
        (index, member)
        for index, member in enumerate(members)
        if int(member.offset) // 8 == 0x7C
    ]
    if len(candidates) != 1:
        return None, {
            "status": "failed",
            "reason": "unexpected_frame_number_candidates",
            "candidate_count": len(candidates),
        }

    index, member = candidates[0]
    return owner, {
        "status": "verified",
        "index": index,
        "offset": "0x7c",
        "size": int(member.size) // 8,
        "name": member.name,
        "type": member.type.dstr(),
        "integral": bool(member.type.is_integral()),
    }


def _sync_renderable_bod_frame_number(
    header_path: pathlib.Path,
) -> dict[str, object]:
    header_text = header_path.read_text(encoding="utf-8")
    if "int32_t frame_number;" not in header_text:
        return {
            "status": "failed",
            "reason": "noncanonical_RenderableBod_header",
        }

    owner, field = _read_renderable_bod_frame_number()
    if owner is None:
        return field
    if field["size"] != 4 or field["name"] not in (
        "unknown_7c",
        "frame_number",
    ):
        return {
            "status": "failed",
            "reason": "unexpected_RenderableBod_tail_lane",
            "field": field,
        }
    if (
        field["name"] == "frame_number"
        and field["type"] == "int32_t"
        and field["integral"]
    ):
        return {
            "status": "unchanged",
            "field": {
                key: value for key, value in field.items() if key != "index"
            },
        }

    old_member = {
        "name": str(field["name"]),
        "type": str(field["type"]),
        "offset_bits": 0x7C * 8,
    }
    code = owner.del_udm(int(field["index"]))
    if code != ida_typeinf.TERR_OK:
        return {
            "status": "failed",
            "reason": "delete_RenderableBod_tail_lane_failed",
            "error": ida_typeinf.tinfo_errstr(code),
            "field": field,
        }

    code = owner.add_udm(
        ida_typeinf.udm_t("frame_number", "int32_t", 0x7C * 8)
    )
    if code != ida_typeinf.TERR_OK:
        rollback_code = owner.add_udm(
            ida_typeinf.udm_t(
                old_member["name"],
                old_member["type"],
                old_member["offset_bits"],
            )
        )
        return {
            "status": "failed",
            "reason": "add_RenderableBod_frame_number_failed",
            "error": ida_typeinf.tinfo_errstr(code),
            "rollback": ida_typeinf.tinfo_errstr(rollback_code),
        }

    _owner, readback = _read_renderable_bod_frame_number()
    if (
        readback.get("status") != "verified"
        or readback.get("size") != 4
        or readback.get("name") != "frame_number"
        or readback.get("type") != "int32_t"
        or not readback.get("integral")
    ):
        rollback_owner, rollback_field = _read_renderable_bod_frame_number()
        rollback = []
        if rollback_owner is not None:
            delete_code = rollback_owner.del_udm(int(rollback_field["index"]))
            rollback.append(ida_typeinf.tinfo_errstr(delete_code))
            add_code = rollback_owner.add_udm(
                ida_typeinf.udm_t(
                    old_member["name"],
                    old_member["type"],
                    old_member["offset_bits"],
                )
            )
            rollback.append(ida_typeinf.tinfo_errstr(add_code))
        return {
            "status": "failed",
            "reason": "RenderableBod_frame_number_readback_failed",
            "readback": readback,
            "rollback": rollback,
        }

    return {
        "status": "applied",
        "field": {
            key: value for key, value in readback.items() if key != "index"
        },
    }


def _read_replay_start_cursor_field(
    owner_name: str,
    expected_owner_size: int,
    offset: int,
) -> tuple[ida_typeinf.tinfo_t | None, dict[str, object]]:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, owner_name, ida_typeinf.BTF_STRUCT):
        return None, {
            "status": "failed",
            "owner": owner_name,
            "reason": "missing_owner",
        }
    if owner.get_size() != expected_owner_size:
        return None, {
            "status": "failed",
            "owner": owner_name,
            "reason": "owner_size_mismatch",
            "expected_size": expected_owner_size,
            "observed_size": owner.get_size(),
        }

    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None, {
            "status": "failed",
            "owner": owner_name,
            "reason": "missing_owner_members",
        }
    candidates = [
        (index, member)
        for index, member in enumerate(members)
        if int(member.offset) // 8 == offset
    ]
    if len(candidates) != 1:
        return None, {
            "status": "failed",
            "owner": owner_name,
            "reason": "unexpected_member_candidates",
            "offset": hex(offset),
            "candidate_count": len(candidates),
        }

    index, member = candidates[0]
    field = {
        "status": "verified",
        "owner": owner_name,
        "owner_size": owner.get_size(),
        "index": index,
        "offset": hex(offset),
        "size": int(member.size) // 8,
        "name": member.name,
        "type": member.type.dstr(),
        "integral": bool(member.type.is_integral()),
    }
    return owner, field


def _read_replay_start_cursor_runtime_path(
) -> tuple[ida_typeinf.tinfo_t | None, dict[str, object]]:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, "cRSubGame", ida_typeinf.BTF_STRUCT):
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "missing_owner",
        }
    if owner.get_size() != REPLAY_START_CURSOR_RUNTIME_OWNER_SIZE:
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "owner_size_mismatch",
            "expected_size": REPLAY_START_CURSOR_RUNTIME_OWNER_SIZE,
            "observed_size": owner.get_size(),
        }

    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "missing_owner_members",
        }
    direct = [
        (index, member)
        for index, member in enumerate(members)
        if int(member.offset) // 8 == REPLAY_START_CURSOR_RUNTIME_OFFSET
    ]
    if len(direct) == 1:
        index, member = direct[0]
        return owner, {
            "status": "verified",
            "owner": "cRSubGame",
            "owner_size": owner.get_size(),
            "mode": "direct_overlay",
            "index": index,
            "offset": hex(REPLAY_START_CURSOR_RUNTIME_OFFSET),
            "size": int(member.size) // 8,
            "name": member.name,
            "type": member.type.dstr(),
            "integral": bool(member.type.is_integral()),
        }
    if direct:
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "unexpected_direct_member_candidates",
            "candidate_count": len(direct),
        }

    player_members = [
        member
        for member in members
        if int(member.offset) // 8 == REPLAY_START_CURSOR_PLAYER_OFFSET
    ]
    if len(player_members) != 1:
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "missing_embedded_player_path",
            "candidate_count": len(player_members),
        }
    player = player_members[0]
    if (
        int(player.size) // 8 != 0x4364
        or "Player" not in player.type.dstr()
    ):
        return None, {
            "status": "failed",
            "owner": "cRSubGame",
            "reason": "unexpected_embedded_player_path",
            "offset": hex(REPLAY_START_CURSOR_PLAYER_OFFSET),
            "size": int(player.size) // 8,
            "name": player.name,
            "type": player.type.dstr(),
        }
    return None, {
        "status": "verified",
        "owner": "cRSubGame",
        "owner_size": owner.get_size(),
        "mode": "embedded_player",
        "offset": hex(REPLAY_START_CURSOR_PLAYER_OFFSET),
        "size": int(player.size) // 8,
        "name": player.name,
        "type": player.type.dstr(),
    }


def _sync_replay_start_cursor_fields() -> dict[str, object]:
    plans = []
    for owner_name, owner_size, offset, allowed_names in REPLAY_START_CURSOR_FIELD_SPECS:
        owner, field = _read_replay_start_cursor_field(owner_name, owner_size, offset)
        if owner is None:
            return field
        if (
            field["size"] != 4
            or not field["integral"]
            or field["name"] not in allowed_names
        ):
            return {
                "status": "failed",
                "reason": "unexpected_replay_start_cursor_field",
                "field": field,
                "allowed_names": list(allowed_names),
            }
        plans.append((owner, field))

    runtime_owner, runtime_path = _read_replay_start_cursor_runtime_path()
    if runtime_path["status"] != "verified":
        return runtime_path
    if runtime_path["mode"] == "direct_overlay":
        if (
            runtime_path["size"] != 4
            or not runtime_path["integral"]
            or runtime_path["name"] not in ("source_tail", "replay_start_cursor")
        ):
            return {
                "status": "failed",
                "reason": "unexpected_replay_start_cursor_runtime_field",
                "field": runtime_path,
            }
        plans.append((runtime_owner, runtime_path))

    renamed = []
    for owner, field in plans:
        if field["name"] == "replay_start_cursor":
            continue
        code = owner.rename_udm(int(field["index"]), "replay_start_cursor")
        if code != ida_typeinf.TERR_OK:
            rollback = []
            for prior_owner, prior_field in reversed(renamed):
                rollback_code = prior_owner.rename_udm(
                    int(prior_field["index"]),
                    str(prior_field["name"]),
                )
                rollback.append(
                    {
                        "owner": prior_field["owner"],
                        "status": ida_typeinf.tinfo_errstr(rollback_code),
                    }
                )
            return {
                "status": "failed",
                "reason": "rename_member_failed",
                "field": field,
                "error": ida_typeinf.tinfo_errstr(code),
                "rollback": rollback,
            }
        renamed.append((owner, field))

    readback = []
    for owner_name, owner_size, offset, _allowed_names in REPLAY_START_CURSOR_FIELD_SPECS:
        _owner, field = _read_replay_start_cursor_field(owner_name, owner_size, offset)
        readback.append(field)
    _runtime_owner, runtime_readback = _read_replay_start_cursor_runtime_path()
    if any(
        field.get("status") != "verified"
        or field.get("name") != "replay_start_cursor"
        for field in readback
    ) or (
        runtime_readback.get("status") != "verified"
        or (
            runtime_readback.get("mode") == "direct_overlay"
            and runtime_readback.get("name") != "replay_start_cursor"
        )
    ):
        rollback = []
        for prior_owner, prior_field in reversed(renamed):
            rollback_code = prior_owner.rename_udm(
                int(prior_field["index"]),
                str(prior_field["name"]),
            )
            rollback.append(
                {
                    "owner": prior_field["owner"],
                    "status": ida_typeinf.tinfo_errstr(rollback_code),
                }
            )
        return {
            "status": "failed",
            "reason": "rename_readback_failed",
            "readback": readback,
            "runtime_readback": runtime_readback,
            "rollback": rollback,
        }

    return {
        "status": "applied" if renamed else "unchanged",
        "renamed_count": len(renamed),
        "fields": [
            {key: value for key, value in field.items() if key != "index"}
            for field in readback
        ],
        "runtime_path": {
            key: value
            for key, value in runtime_readback.items()
            if key != "index"
        },
    }


def _sync_color_lvars(selector: str) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var() and "Color4f" in str(lvar.type())
    ]
    if not candidates:
        return {"status": "unchanged", "updated_count": 0, "selector": selector}

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(None, "tColour", ida_typeinf.BTF_STRUCT):
        return {
            "status": "failed",
            "reason": "missing_tColour_type",
            "selector": selector,
        }

    updated = []
    for lvar in candidates:
        info = ida_hexrays.lvar_saved_info_t()
        info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
        info.type = local_type
        if not ida_hexrays.modify_user_lvar_info(address, ida_hexrays.MLI_TYPE, info):
            return {
                "status": "failed",
                "reason": "modify_user_lvar_info_failed",
                "local": lvar.name,
                "selector": selector,
            }
        updated.append(lvar.name)

    return {
        "status": "applied",
        "updated_count": len(updated),
        "locals": updated,
        "type": "tColour",
        "selector": selector,
    }


def _sync_exact_lvars(
    selector: str,
    specs: tuple[tuple[str, str, int, int | None], ...],
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    pending = []
    results = []
    for expected_name, declaration, definition_address, stack_offset in specs:
        candidates = [
            lvar
            for lvar in cfunc.get_lvars()
            if not lvar.is_arg_var
            and lvar.defea == definition_address
            and (
                (stack_offset is None and not lvar.is_stk_var())
                or (
                    stack_offset is not None
                    and lvar.is_stk_var()
                    and lvar.get_stkoff() == stack_offset
                )
            )
        ]
        if len(candidates) != 1:
            return {
                "status": "failed",
                "reason": "unexpected_local_candidates",
                "selector": selector,
                "expected_name": expected_name,
                "definition_address": hex(definition_address),
                "stack_offset": stack_offset,
                "candidate_count": len(candidates),
            }

        local_type = ida_typeinf.tinfo_t()
        if not ida_typeinf.parse_decl(
            local_type,
            None,
            declaration,
            ida_typeinf.PT_SIL,
        ):
            return {
                "status": "failed",
                "reason": "parse_local_type_failed",
                "selector": selector,
                "expected_name": expected_name,
                "declaration": declaration,
            }

        lvar = candidates[0]
        expected_type = _normalize_lvar_type_text(str(local_type))
        observed_type = _normalize_lvar_type_text(str(lvar.type()))
        if lvar.name == expected_name and observed_type == expected_type:
            results.append(
                {
                    "status": "unchanged",
                    "name": lvar.name,
                    "type": str(lvar.type()),
                    "definition_address": hex(definition_address),
                }
            )
            continue

        pending.append(
            {
                "lvar": lvar,
                "expected_name": expected_name,
                "expected_type": expected_type,
                "local_type": local_type,
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
        info.name = update["expected_name"]
        info.type = update["local_type"]
        if not ida_hexrays.modify_user_lvar_info(
            address,
            ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
            info,
        ):
            return {
                "status": "failed",
                "reason": "modify_user_lvar_info_failed",
                "selector": selector,
                "expected_name": update["expected_name"],
            }

    if pending:
        ida_hexrays.mark_cfunc_dirty(address, True)
        cfunc = ida_hexrays.decompile(address)

    for update in pending:
        verified = [
            candidate
            for candidate in cfunc.get_lvars()
            if not candidate.is_arg_var
            and candidate.name == update["expected_name"]
            and candidate.defea == update["definition_address"]
            and _normalize_lvar_type_text(str(candidate.type()))
            == update["expected_type"]
            and (
                (update["stack_offset"] is None and not candidate.is_stk_var())
                or (
                    update["stack_offset"] is not None
                    and candidate.is_stk_var()
                    and candidate.get_stkoff() == update["stack_offset"]
                )
            )
        ]
        if len(verified) != 1:
            return {
                "status": "failed",
                "reason": "local_readback_failed",
                "selector": selector,
                "expected_name": update["expected_name"],
                "candidate_count": len(verified),
            }
        results.append(
            {
                "status": "applied",
                "before_name": update["before_name"],
                "before_type": update["before_type"],
                "name": verified[0].name,
                "type": str(verified[0].type()),
                "definition_address": hex(update["definition_address"]),
            }
        )

    return {
        "status": "applied" if pending else "unchanged",
        "selector": selector,
        "locals": results,
    }


def _sync_build_track_render_cache_counter_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "build_track_render_caches",
        BUILD_TRACK_RENDER_CACHE_COUNTER_LVAR_SPECS,
    )


def _sync_loading_quad_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "initialize_loading_screen",
        (
            (
                "background_quad",
                "LoadingQuadVertexView *background_quad;",
                0x418D89,
                140,
            ),
        ),
    )


def _clear_exact_lvar_override(
    selector: str,
    expected_name: str,
    definition_address: int,
    stack_offset: int | None,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.name == expected_name
        and lvar.defea == definition_address
        and (
            (stack_offset is None and not lvar.is_stk_var())
            or (
                stack_offset is not None
                and lvar.is_stk_var()
                and lvar.get_stkoff() == stack_offset
            )
        )
    ]
    if not candidates:
        return {
            "status": "unchanged",
            "name": expected_name,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
        }
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_override_candidates",
            "selector": selector,
            "name": expected_name,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    locator = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(settings, address):
        return {
            "status": "failed",
            "reason": "restore_user_lvar_settings_failed",
            "selector": selector,
            "name": expected_name,
        }

    saved_info = settings.find_info(locator)
    if saved_info is None:
        return {
            "status": "unchanged",
            "name": expected_name,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "reason": "no_saved_override",
        }
    if saved_info.name != expected_name:
        return {
            "status": "failed",
            "reason": "saved_lvar_override_mismatch",
            "selector": selector,
            "name": expected_name,
        }
    removed_type = str(saved_info.type)
    if not settings.lvvec._del(saved_info):
        return {
            "status": "failed",
            "reason": "delete_saved_lvar_override_failed",
            "selector": selector,
            "name": expected_name,
        }

    ida_hexrays.save_user_lvar_settings(address, settings)
    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(verified_settings, address):
        return {
            "status": "failed",
            "reason": "restore_verified_lvar_settings_failed",
            "selector": selector,
            "name": expected_name,
        }
    if verified_settings.find_info(locator) is not None:
        return {
            "status": "failed",
            "reason": "lvar_override_readback_failed",
            "selector": selector,
            "name": expected_name,
        }

    return {
        "status": "applied",
        "name": expected_name,
        "type": removed_type,
        "definition_address": hex(definition_address),
        "stack_offset": stack_offset,
    }


def _sync_populate_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "populate_runtime_track_cells_from_segments",
        POPULATE_RUNTIME_LVAR_SPECS,
    )


def _sync_golb_path_follow_copy_ownership() -> dict[str, object]:
    selector = "traverse_path_follow_golb"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func_start(address) == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    declaration = "Vec3 *direction_source;"
    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_direction_source_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    expected_type = _normalize_type_text(str(local_type))
    cfunc = ida_hexrays.decompile(address)
    settings = ida_hexrays.lvar_uservec_t()
    ida_hexrays.restore_user_lvar_settings(settings, address)
    matching_saved = []
    conflicting_saved = []
    for index in range(settings.lvvec.size()):
        saved = settings.lvvec.at(index)
        if (
            saved.ll.defea != GOLB_PATH_FOLLOW_DIRECTION_LVAR_DEFINITION
            or not saved.ll.is_reg1()
            or ida_hexrays.get_mreg_name(saved.ll.get_reg1(), 4) != "edi"
        ):
            continue
        if (
            saved.name == "direction_source"
            and _normalize_type_text(str(saved.type)) == expected_type
        ):
            matching_saved.append(saved)
        else:
            conflicting_saved.append(saved)

    folded_copy = "state->shot->velocity = state->shot->direction;" in str(cfunc)
    false_interior_owner = "shot->primary_body" in str(cfunc)
    if len(matching_saved) == 1 and not conflicting_saved:
        if not folded_copy or false_interior_owner:
            return {
                "status": "failed",
                "reason": "golb_copy_ownership_readback_failed",
                "selector": selector,
                "folded_copy": folded_copy,
                "false_interior_owner": false_interior_owner,
            }
        return {
            "status": "unchanged",
            "selector": selector,
            "direction_source": {
                "name": matching_saved[0].name,
                "type": str(matching_saved[0].type),
                "definition_address": hex(matching_saved[0].ll.defea),
                "register": "edi",
            },
            "folded_copy": True,
        }
    if matching_saved or conflicting_saved:
        return {
            "status": "failed",
            "reason": "unexpected_direction_source_overrides",
            "selector": selector,
            "matching_count": len(matching_saved),
            "conflicting_count": len(conflicting_saved),
        }

    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == GOLB_PATH_FOLLOW_DIRECTION_LVAR_DEFINITION
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_direction_source_candidates",
            "selector": selector,
            "candidate_count": len(candidates),
        }

    source = candidates[0]
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(source.location, source.defea)
    info.name = "direction_source"
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_direction_source_lvar_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_settings = ida_hexrays.lvar_uservec_t()
    if not ida_hexrays.restore_user_lvar_settings(verified_settings, address):
        return {
            "status": "failed",
            "reason": "restore_direction_source_override_failed",
            "selector": selector,
        }
    verified_saved = [
        verified_settings.lvvec.at(index)
        for index in range(verified_settings.lvvec.size())
        if verified_settings.lvvec.at(index).name == "direction_source"
        and _normalize_type_text(str(verified_settings.lvvec.at(index).type))
        == expected_type
        and verified_settings.lvvec.at(index).ll.defea
        == GOLB_PATH_FOLLOW_DIRECTION_LVAR_DEFINITION
        and verified_settings.lvvec.at(index).ll.is_reg1()
        and ida_hexrays.get_mreg_name(
            verified_settings.lvvec.at(index).ll.get_reg1(),
            4,
        )
        == "edi"
    ]
    verified_text = str(verified_cfunc)
    folded_copy = "state->shot->velocity = state->shot->direction;" in verified_text
    false_interior_owner = "shot->primary_body" in verified_text
    if len(verified_saved) != 1 or not folded_copy or false_interior_owner:
        return {
            "status": "failed",
            "reason": "golb_copy_ownership_readback_failed",
            "selector": selector,
            "saved_override_count": len(verified_saved),
            "folded_copy": folded_copy,
            "false_interior_owner": false_interior_owner,
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": source.name,
        "before_type": str(source.type()),
        "direction_source": {
            "name": verified_saved[0].name,
            "type": str(verified_saved[0].type),
            "definition_address": hex(verified_saved[0].ll.defea),
            "register": "edi",
        },
        "folded_copy": True,
    }


def _sync_place_parcels_runtime_lvars() -> dict[str, object]:
    rejected_stack_overrides = [
        _clear_exact_lvar_override(
            "place_parcels_on_track",
            expected_name,
            definition_address,
            stack_offset,
        )
        for expected_name, definition_address, stack_offset in (
            PLACE_PARCELS_REJECTED_STACK_LVAR_OVERRIDES
        )
    ]
    failed = [
        result
        for result in rejected_stack_overrides
        if result.get("status") == "failed"
    ]
    if failed:
        return {
            "status": "failed",
            "selector": "place_parcels_on_track",
            "rejected_stack_overrides": rejected_stack_overrides,
        }

    result = _sync_exact_lvars(
        "place_parcels_on_track",
        PLACE_PARCELS_RUNTIME_LVAR_SPECS,
    )
    result["rejected_stack_overrides"] = rejected_stack_overrides
    if any(
        rejected.get("status") == "applied"
        for rejected in rejected_stack_overrides
    ):
        result["status"] = "applied"
    return result


def _sync_challenge_parcels_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "place_challenge_parcels_on_track",
        CHALLENGE_PARCELS_RUNTIME_LVAR_SPECS,
    )


def _sync_project_attachment_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "project_position_onto_track_attachment",
        PROJECT_ATTACHMENT_LVAR_SPECS,
    )


def _sync_remove_sub_loc_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "remove_sub_loc",
        REMOVE_SUB_LOC_RUNTIME_LVAR_SPECS,
    )


def _sync_update_subgame_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "update_subgame",
        UPDATE_SUBGAME_RUNTIME_LVAR_SPECS,
    )


def _sync_update_subgoldy_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "update_subgoldy",
        UPDATE_SUBGOLDY_LVAR_SPECS,
    )


def _sync_initialize_subgoldy_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "initialize_subgoldy",
        INITIALIZE_SUBGOLDY_LVAR_SPECS,
    )


def _sync_shoot_subgoldy_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "shoot_subgoldy",
        SHOOT_SUBGOLDY_LVAR_SPECS,
    )


def _sync_world_initializer_golb_asset_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "initialize_game_assets_and_world",
        WORLD_INITIALIZER_GOLB_ASSET_LVAR_SPECS,
    )


def _sync_world_initializer_sub_lazer_asset_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "initialize_game_assets_and_world",
        WORLD_INITIALIZER_SUB_LAZER_ASSET_LVAR_SPECS,
    )

def _sync_world_initializer_salt_asset_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "initialize_game_assets_and_world",
        WORLD_INITIALIZER_SALT_ASSET_LVAR_SPECS,
    )


def _sync_remove_subgame_bods_cursor_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "remove_subgame_bods",
        REMOVE_SUBGAME_BODS_CURSOR_LVAR_SPECS,
    )


def _sync_spawn_track_ring_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "spawn_track_ring_or_special_effect",
        SPAWN_TRACK_RING_LVAR_SPECS,
    )


def _sync_ring_parent_radius_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "update_ring_or_special_effect_parent",
        RING_PARENT_RADIUS_LVAR_SPECS,
    )


def _sync_ring_particle_parent_position_lvar() -> dict[str, object]:
    return _sync_exact_lvars(
        "update_ring_or_special_effect_particle",
        RING_PARTICLE_POSITION_CURSOR_LVAR_SPECS,
    )


def _sync_spawn_track_health_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "spawn_track_health_pickup",
        SPAWN_TRACK_HEALTH_LVAR_SPECS,
    )


def _sync_spawn_track_jetpack_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "spawn_track_jetpack_pickup",
        SPAWN_TRACK_JETPACK_LVAR_SPECS,
    )


def _sync_firework_shoot_lvars() -> dict[str, object]:
    # A persisted type override on the ESI result of allocate_sprite became
    # harmful once the canonical Sprite/cRSprite alias was installed: Hex-Rays
    # stopped folding the final three stores back into `sprite->position`.
    # Keep the automatic pointer owner and replay only the genuinely split
    # scalar lifetimes.
    cleared_sprite_override = _clear_exact_lvar_override(
        "firework_shoot",
        "sprite",
        0x441E0F,
        None,
    )
    if cleared_sprite_override.get("status") == "failed":
        return {
            "status": "failed",
            "selector": "firework_shoot",
            "cleared_sprite_override": cleared_sprite_override,
        }

    lvars = _sync_exact_lvars(
        "firework_shoot",
        FIREWORK_SHOOT_LVAR_SPECS,
    )
    if lvars.get("status") == "failed":
        return {
            "status": "failed",
            "selector": "firework_shoot",
            "cleared_sprite_override": cleared_sprite_override,
            "lvars": lvars,
        }
    return {
        "status": (
            "applied"
            if "applied"
            in {cleared_sprite_override.get("status"), lvars.get("status")}
            else "unchanged"
        ),
        "selector": "firework_shoot",
        "cleared_sprite_override": cleared_sprite_override,
        "lvars": lvars,
    }


def _sync_spawn_salt_hazard_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "spawn_salt_hazard",
        SPAWN_SALT_HAZARD_LVAR_SPECS,
    )


def _sync_collision_pool_cursor_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "handle_subgoldy_collisions",
        COLLISION_POOL_CURSOR_LVAR_SPECS,
    )


def _sync_merge_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "merge_track_tile_runs",
        MERGE_RUNTIME_LVAR_SPECS,
    )


def _sync_fringe_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "build_track_fringe_objects",
        FRINGE_RUNTIME_LVAR_SPECS,
    )


def _sync_fringe_mesh_lvars() -> dict[str, object]:
    results = {
        selector: _sync_exact_lvars(selector, specs)
        for selector, specs in FRINGE_MESH_LVAR_SPECS.items()
    }
    failed = {
        selector: result
        for selector, result in results.items()
        if result.get("status") == "failed"
    }
    return {
        "status": "failed" if failed else (
            "applied"
            if any(result.get("status") == "applied" for result in results.values())
            else "unchanged"
        ),
        "builders": results,
        "failed": failed,
    }


def _sync_harmonize_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "harmonize_center_lane_floor_slide_variants",
        HARMONIZE_RUNTIME_LVAR_SPECS,
    )


def _sync_build_subgame_active_bod_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "build_subgame_level",
        BUILD_SUBGAME_ACTIVE_BOD_LVAR_SPECS,
    )


def _sync_subgame_receiver_lvar(
    selector: str,
    *,
    argument_count: int,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [lvar for lvar in cfunc.get_lvars() if lvar.is_arg_var]
    if len(candidates) != argument_count:
        return {
            "status": "failed",
            "reason": "unexpected_argument_candidates",
            "candidate_count": len(candidates),
            "expected_argument_count": argument_count,
            "selector": selector,
        }

    owner_type = ida_typeinf.tinfo_t()
    if not owner_type.get_named_type(
        None,
        "cRSubGame",
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_cRSubGame_type",
            "selector": selector,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(owner_type):
        return {
            "status": "failed",
            "reason": "create_cRSubGame_pointer_failed",
            "selector": selector,
        }

    lvar = candidates[0]
    expected_type = (_normalize_type_text(str(pointer_type)) or "").removeprefix(
        "struct "
    )
    observed_type = (_normalize_type_text(str(lvar.type())) or "").removeprefix(
        "struct "
    )
    if lvar.name == "game" and observed_type == expected_type:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "selector": selector,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "game"
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_user_lvar_info_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_candidates = [
        candidate for candidate in verified_cfunc.get_lvars() if candidate.is_arg_var
    ]
    if len(verified_candidates) != argument_count:
        return {
            "status": "failed",
            "reason": "unexpected_verified_argument_candidates",
            "candidate_count": len(verified_candidates),
            "expected_argument_count": argument_count,
            "selector": selector,
        }

    verified = verified_candidates[0]
    verified_type = (_normalize_type_text(str(verified.type())) or "").removeprefix(
        "struct "
    )
    if verified.name != "game" or verified_type != expected_type:
        return {
            "status": "failed",
            "reason": "lvar_verification_failed",
            "observed_name": verified.name,
            "observed_type": str(verified.type()),
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified.name,
        "type": str(verified.type()),
        "selector": selector,
    }


def _resolve_function(selector: str) -> tuple[int | None, str]:
    if selector.startswith("0x"):
        address = int(selector, 16)
        name = idc.get_func_name(address) or selector
        return address, name

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
    normalized = re.sub(r"\buint8_t\b", "unsigned char", normalized)
    normalized = re.sub(r"\bint32_t\b", "int", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    return normalized.strip()


def _normalize_lvar_type_text(value: str | None) -> str | None:
    """Compare Hex-Rays locals without churning equivalent typedef spelling."""
    normalized = _normalize_type_text(value)
    if normalized is None:
        return None
    return re.sub(r"\bstruct\s+(?=[A-Za-z_]\w*\b)", "", normalized)


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=;)", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _named_struct_member_readback(
    struct_name: str, offset: int
) -> dict[str, object] | None:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, struct_name, ida_typeinf.BTF_STRUCT):
        return None
    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None
    for member in members:
        member_offset = int(member.offset) // 8
        if member_offset == offset:
            return {
                "offset": hex(member_offset),
                "size": int(member.size) // 8,
                "name": member.name,
                "type": _normalize_udt_type(member.type.dstr()),
            }
    return None


def _sync_face_movie_owner() -> dict[str, object]:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, "Face", ida_typeinf.BTF_STRUCT):
        return {"status": "failed", "reason": "missing_Face_type"}
    if owner.get_size() != 0x128:
        return {
            "status": "failed",
            "reason": "owner_size_mismatch",
            "expected": 0x128,
            "observed": owner.get_size(),
        }

    expected = {
        "offset": "0x38",
        "size": 0xF0,
        "name": "movie",
        "type": "Movie",
    }
    before = _named_struct_member_readback("Face", 0x38)
    if before == expected:
        return {"status": "unchanged", "readback": before}

    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return {"status": "failed", "reason": "missing_Face_members"}
    candidates = [
        (index, member)
        for index, member in enumerate(members)
        if int(member.offset) // 8 == 0x38
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_movie_member_count",
            "readback": before,
        }

    old_index, old_member = candidates[0]
    if int(old_member.size) // 8 != 0xF0:
        return {
            "status": "failed",
            "reason": "unexpected_movie_member_size",
            "readback": before,
        }
    old_name = old_member.name
    old_type = ida_typeinf.tinfo_t(old_member.type)
    code = owner.del_udm(old_index)
    if code != ida_typeinf.TERR_OK:
        return {
            "status": "failed",
            "reason": "delete_legacy_movie_owner_failed",
            "error": ida_typeinf.tinfo_errstr(code),
        }

    code = owner.add_udm(ida_typeinf.udm_t("movie", "Movie", 0x38 * 8))
    if code != ida_typeinf.TERR_OK:
        rollback_code = owner.add_udm(
            ida_typeinf.udm_t(old_name, old_type, 0x38 * 8)
        )
        return {
            "status": "failed",
            "reason": "add_movie_owner_failed",
            "error": ida_typeinf.tinfo_errstr(code),
            "rollback": ida_typeinf.tinfo_errstr(rollback_code),
        }

    after = _named_struct_member_readback("Face", 0x38)
    if after != expected:
        return {
            "status": "failed",
            "reason": "verification_failed",
            "before": before,
            "readback": after,
        }
    return {"status": "applied", "before": before, "readback": after}


def _normalize_root_offset_operands(
    operand_specs: tuple[tuple[int, int, int], ...],
) -> list[dict[str, object]]:
    results = []
    for address, operand_index, expected_offset in operand_specs:
        before = idc.print_operand(address, operand_index)
        idc.op_num(address, operand_index)
        after = idc.print_operand(address, operand_index)
        observed_offset = idc.get_operand_value(address, operand_index)
        normalized = (
            observed_offset == expected_offset
            and f"{expected_offset:X}H" in after.upper()
        )
        results.append(
            {
                "status": (
                    "applied"
                    if normalized and before != after
                    else "unchanged"
                    if normalized
                    else "failed"
                ),
                "address": hex(address),
                "operand_index": operand_index,
                "expected_offset": hex(expected_offset),
                "observed_offset": hex(observed_offset),
                "before": before,
                "after": after,
            }
        )
    return results


def _normalize_udt_type(value: str) -> str:
    normalized = _normalize_type_text(value) or ""
    return re.sub(r"\b(?:struct|class|union)\s+", "", normalized)


def _nuke_owner_layout_readback() -> dict[str, object]:
    """Verify the complete canonical cRNuke owner before its method ABIs."""
    type_name = "cRNuke"
    expected = EXPECTED_NUKE_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "nuke",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "nuke",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x150)
    if player_embed != EXPECTED_NUKE_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.nuke",
                "owner_group": "nuke",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_NUKE_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
        "failures": failures,
    }


def _damage_guage_owner_layout_readback() -> dict[str, object]:
    """Verify the complete canonical cRDamageGuage owner and Player embed."""
    type_name = "cRDamageGuage"
    expected = EXPECTED_DAMAGE_GUAGE_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "damage_guage",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "damage_guage",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x3C4)
    if player_embed != EXPECTED_DAMAGE_GUAGE_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.damage_gauge",
                "owner_group": "damage_guage",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_DAMAGE_GUAGE_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
        "failures": failures,
    }


def _progress_bar_owner_layout_readback() -> dict[str, object]:
    """Verify the canonical empty cRProgressBar owner and Player embed."""
    type_name = "cRProgressBar"
    expected = EXPECTED_PROGRESS_BAR_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "progress_bar",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "progress_bar",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x3F0)
    if player_embed != EXPECTED_PROGRESS_BAR_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.progress_bar",
                "owner_group": "progress_bar",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_PROGRESS_BAR_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
        "failures": failures,
    }


def _squidge_owner_layout_readback() -> dict[str, object]:
    """Verify the complete canonical cRSquidge owner and Player embed."""
    type_name = "cRSquidge"
    expected = EXPECTED_SQUIDGE_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "squidge",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "squidge",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x4344)
    if player_embed != EXPECTED_SQUIDGE_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.squidge",
                "owner_group": "squidge",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_SQUIDGE_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
        "failures": failures,
    }


def _warning_owner_layout_readback() -> dict[str, object]:
    """Verify the complete canonical cRWarning owner and Player embed."""
    type_name = "cRWarning"
    expected = EXPECTED_WARNING_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "warning",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "warning",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x3F4)
    if player_embed != EXPECTED_WARNING_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.warning",
                "owner_group": "warning",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_WARNING_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
        "failures": failures,
    }


def _tip_owner_layout_readback() -> dict[str, object]:
    """Verify every canonical tip owner before applying its method ABIs."""
    readback: dict[str, object] = {}
    failures: list[dict[str, object]] = []
    for type_name, expected in EXPECTED_TIP_OWNER_LAYOUTS.items():
        observed_size = _named_struct_size(type_name)
        observed_members = {
            hex(offset): _named_struct_member_readback(type_name, offset)
            for offset in expected["members"]
        }
        readback[type_name] = {
            "size": observed_size,
            "members": observed_members,
        }
        if observed_size != expected["size"]:
            failures.append(
                {
                    "selector": type_name,
                    "owner_group": "tip",
                    "reason": "owner_size_mismatch",
                    "expected": expected["size"],
                    "observed": observed_size,
                }
            )
        for offset, (size, name, type_text) in expected["members"].items():
            expected_member = {
                "offset": hex(offset),
                "size": size,
                "name": name,
                "type": _normalize_udt_type(type_text),
            }
            observed_member = observed_members[hex(offset)]
            if observed_member != expected_member:
                failures.append(
                    {
                        "selector": f"{type_name}.{name}",
                        "owner_group": "tip",
                        "reason": "owner_member_mismatch",
                        "expected": expected_member,
                        "observed": observed_member,
                    }
                )
    return {"types": readback, "failures": failures}


def _tutorial_owner_layout_readback() -> dict[str, object]:
    """Verify the complete canonical cRTutorial owner before its method ABIs."""
    type_name = "cRTutorial"
    expected = EXPECTED_TUTORIAL_OWNER_LAYOUT
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in expected["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != expected["size"]:
        failures.append(
            {
                "selector": type_name,
                "owner_group": "tutorial",
                "reason": "owner_size_mismatch",
                "expected": expected["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in expected["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"{type_name}.{name}",
                    "owner_group": "tutorial",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "failures": failures,
    }


def _golb_shot_prefix_snapshot(owner: ida_typeinf.tinfo_t) -> list[dict[str, object]] | None:
    udt = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(udt):
        return None
    return [
        {
            "index": index,
            "offset": int(member.offset) // 8,
            "size": int(member.size) // 8,
            "name": member.name,
            "type": _normalize_udt_type(member.type.dstr()),
            "baseclass": bool(member.is_baseclass()),
        }
        for index, member in enumerate(udt)
        if int(member.offset) // 8 < GOLB_SHOT_PREFIX_END
    ]


def _golb_shot_prefix_readback(owner: ida_typeinf.tinfo_t) -> dict[str, object]:
    return {
        "size": owner.get_size(),
        "members": _golb_shot_prefix_snapshot(owner),
    }


def _golb_shot_inheritance_decompile_readback() -> dict[str, object]:
    texts = {}
    for selector in ("initialize_golb_shot", "kill_golb", "create_golb"):
        address = idc.get_name_ea_simple(selector)
        if (
            address == idc.BADADDR
            or ida_funcs.get_func_start(address) == idc.BADADDR
        ):
            return {
                "verified": False,
                "reason": "missing_function",
                "selector": selector,
            }
        try:
            ida_hexrays.mark_cfunc_dirty(address, True)
            texts[selector] = str(ida_hexrays.decompile(address))
        except Exception as exc:
            return {
                "verified": False,
                "reason": "decompile_failed",
                "selector": selector,
                "error": str(exc),
            }

    checks = {
        "initialize_inherited_vtable": (
            "shot->bod.bod.vtable = &g_golb_shot_vtable"
            in texts["initialize_golb_shot"]
        ),
        "kill_inherited_list": (
            "shot->bod.bod.list_flags" in texts["kill_golb"]
        ),
        "create_inherited_list": (
            "shot->bod.bod.list_flags" in texts["create_golb"]
        ),
        "create_inherited_dispatch": (
            "shot->bod.bod.vtable" in texts["create_golb"]
        ),
        "no_primary_body_alias": all(
            "primary_body" not in text for text in texts.values()
        ),
    }
    return {
        "verified": all(checks.values()),
        "checks": checks,
    }


def _golb_shot_prefix_is_canonical(owner: ida_typeinf.tinfo_t) -> bool:
    snapshot = _golb_shot_prefix_snapshot(owner)
    if owner.get_size() != GOLB_SHOT_EXPECTED_SIZE or snapshot is None:
        return False
    observed = tuple(
        (
            int(member["offset"]),
            int(member["size"]),
            str(member["name"]),
            str(member["type"]),
            bool(member["baseclass"]),
        )
        for member in snapshot
    )
    return observed == GOLB_SHOT_PREFIX_MEMBERS


def _sync_golb_shot_prefix_owner(header_path: pathlib.Path) -> dict[str, object]:
    """Recover the inherited cRBodPos base and proved presentation children."""

    header_text = header_path.read_text(encoding="utf-8")
    missing_markers = [
        marker for marker in GOLB_SHOT_HEADER_MARKERS if marker not in header_text
    ]
    if missing_markers:
        return {
            "status": "failed",
            "reason": "noncanonical_golb_shot_header",
            "missing_markers": missing_markers,
        }

    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, "GolbShot", ida_typeinf.BTF_STRUCT):
        return {"status": "failed", "reason": "missing_GolbShot_type"}
    if owner.get_size() != GOLB_SHOT_EXPECTED_SIZE:
        return {
            "status": "failed",
            "reason": "owner_size_mismatch",
            "expected": GOLB_SHOT_EXPECTED_SIZE,
            "observed": owner.get_size(),
        }
    if _golb_shot_prefix_is_canonical(owner):
        decompile_readback = _golb_shot_inheritance_decompile_readback()
        if not decompile_readback.get("verified"):
            return {
                "status": "failed",
                "reason": "decompile_readback_failed",
                "readback": _golb_shot_prefix_readback(owner),
                "decompile_readback": decompile_readback,
            }
        return {
            "status": "unchanged",
            "readback": _golb_shot_prefix_readback(owner),
            "decompile_readback": decompile_readback,
        }

    udt = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(udt):
        return {"status": "failed", "reason": "missing_GolbShot_members"}
    overlapping = [
        (index, member)
        for index, member in enumerate(udt)
        if int(member.offset) // 8 < GOLB_SHOT_PREFIX_END
    ]
    current_snapshot = _golb_shot_prefix_snapshot(owner)
    current_members = (
        tuple(
            (
                int(member["offset"]),
                int(member["size"]),
                str(member["name"]),
                str(member["type"]),
                bool(member["baseclass"]),
            )
            for member in current_snapshot
        )
        if current_snapshot is not None
        else ()
    )
    legacy_union = (
        len(overlapping) == 1
        and int(overlapping[0][1].offset) // 8 == 0
        and int(overlapping[0][1].size) // 8 == GOLB_SHOT_PREFIX_END
        and not overlapping[0][1].name
        and overlapping[0][1].type.is_union()
    )
    composed_prefix = current_members in {
        GOLB_SHOT_COMPOSED_PREFIX_MEMBERS,
        GOLB_SHOT_HEADER_COMPOSED_PREFIX_MEMBERS,
    }
    if not legacy_union and not composed_prefix:
        return {
            "status": "failed",
            "reason": "unexpected_prefix_owner",
            "readback": _golb_shot_prefix_readback(owner),
        }

    old_members = [
        {
            "name": member.name,
            "type": ida_typeinf.tinfo_t(member.type),
            "offset_bits": int(member.offset),
            "baseclass": bool(member.is_baseclass()),
        }
        for _index, member in overlapping
    ]

    for index, _member in reversed(overlapping):
        code = owner.del_udm(index)
        if code != ida_typeinf.TERR_OK:
            return {
                "status": "failed",
                "reason": "delete_existing_prefix_failed",
                "error": ida_typeinf.tinfo_errstr(code),
                "readback": _golb_shot_prefix_readback(owner),
            }

    try:
        for offset, _size, name, type_name, baseclass in GOLB_SHOT_PREFIX_MEMBERS:
            member = ida_typeinf.udm_t(name, type_name, offset * 8)
            if baseclass:
                member.set_baseclass()
            code = owner.add_udm(member)
            if code != ida_typeinf.TERR_OK:
                raise RuntimeError(
                    f"add {name}: {ida_typeinf.tinfo_errstr(code)}"
                )
    except (RuntimeError, ValueError) as exc:
        rollback_udt = ida_typeinf.udt_type_data_t()
        if owner.get_udt_details(rollback_udt):
            for index in reversed(
                [
                    index
                    for index, member in enumerate(rollback_udt)
                    if int(member.offset) // 8 < GOLB_SHOT_PREFIX_END
                ]
            ):
                owner.del_udm(index)
        rollback = []
        for old_member in old_members:
            member = ida_typeinf.udm_t(
                old_member["name"],
                old_member["type"],
                old_member["offset_bits"],
            )
            if old_member["baseclass"]:
                member.set_baseclass()
            rollback_code = owner.add_udm(member)
            rollback.append(ida_typeinf.tinfo_errstr(rollback_code))
        return {
            "status": "failed",
            "reason": "mutation_failed",
            "error": str(exc),
            "rollback": rollback,
            "readback": _golb_shot_prefix_readback(owner),
        }

    if not _golb_shot_prefix_is_canonical(owner):
        return {
            "status": "failed",
            "reason": "verification_failed",
            "readback": _golb_shot_prefix_readback(owner),
        }
    decompile_readback = _golb_shot_inheritance_decompile_readback()
    if not decompile_readback.get("verified"):
        return {
            "status": "failed",
            "reason": "decompile_readback_failed",
            "readback": _golb_shot_prefix_readback(owner),
            "decompile_readback": decompile_readback,
        }
    return {
        "status": "applied",
        "readback": _golb_shot_prefix_readback(owner),
        "decompile_readback": decompile_readback,
    }


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_subgame_owner_markers = [
        marker
        for marker in SUBGAME_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_sub_loc_owner_markers = [
        marker
        for marker in SUB_LOC_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_path_owner_markers = [
        marker
        for marker in PATH_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_path_manager_owner_markers = [
        marker
        for marker in PATH_MANAGER_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_bod_core_owner_markers = [
        marker
        for marker in BOD_CORE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_fringe_owner_markers = [
        marker
        for marker in FRINGE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_nuke_owner_markers = [
        marker
        for marker in NUKE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_damage_guage_owner_markers = [
        marker
        for marker in DAMAGE_GUAGE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_progress_bar_owner_markers = [
        marker
        for marker in PROGRESS_BAR_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_squidge_owner_markers = [
        marker
        for marker in SQUIDGE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_warning_owner_markers = [
        marker
        for marker in WARNING_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_tip_owner_markers = [
        marker
        for marker in TIP_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_tutorial_owner_markers = [
        marker
        for marker in TUTORIAL_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_track_render_cache_owner_markers = [
        marker
        for marker in TRACK_RENDER_CACHE_OWNER_MARKERS
        if marker not in header_text
    ]
    missing_sub_lazer_asset_cursor_markers = [
        marker
        for marker in SUB_LAZER_ASSET_CURSOR_HEADER_MARKERS
        if marker not in header_text
    ]
    missing_salt_asset_cursor_markers = [
        marker
        for marker in SALT_ASSET_CURSOR_HEADER_MARKERS
        if marker not in header_text
    ]
    missing_runtime_grid_clear_cursor_markers = [
        marker
        for marker in RUNTIME_GRID_CLEAR_CURSOR_HEADER_MARKERS
        if marker not in header_text
    ]
    missing_fringe_mesh_cursor_markers = [
        marker
        for marker in FRINGE_MESH_CURSOR_HEADER_MARKERS
        if marker not in header_text
    ]
    if (
        missing_subgame_owner_markers
        or missing_sub_loc_owner_markers
        or missing_path_owner_markers
        or missing_path_manager_owner_markers
        or missing_bod_core_owner_markers
        or missing_fringe_owner_markers
        or missing_nuke_owner_markers
        or missing_damage_guage_owner_markers
        or missing_progress_bar_owner_markers
        or missing_squidge_owner_markers
        or missing_warning_owner_markers
        or missing_tip_owner_markers
        or missing_tutorial_owner_markers
        or missing_track_render_cache_owner_markers
        or missing_sub_lazer_asset_cursor_markers
        or missing_salt_asset_cursor_markers
        or missing_runtime_grid_clear_cursor_markers
        or missing_fringe_mesh_cursor_markers
    ):
        marker_failures = []
        if missing_subgame_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_subgame_owner_header"}
            )
        if missing_sub_loc_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_sub_loc_owner_header"}
            )
        if missing_path_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_path_owner_header"}
            )
        if missing_path_manager_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_path_manager_owner_header"}
            )
        if missing_bod_core_owner_markers:
            marker_failures.append({"reason": "noncanonical_bod_core_header"})
        if missing_fringe_owner_markers:
            marker_failures.append({"reason": "noncanonical_fringe_header"})
        if missing_nuke_owner_markers:
            marker_failures.append({"reason": "noncanonical_nuke_owner_header"})
        if missing_damage_guage_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_damage_guage_owner_header"}
            )
        if missing_progress_bar_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_progress_bar_owner_header"}
            )
        if missing_squidge_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_squidge_owner_header"}
            )
        if missing_warning_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_warning_owner_header"}
            )
        if missing_tip_owner_markers:
            marker_failures.append({"reason": "noncanonical_tip_owner_header"})
        if missing_tutorial_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_tutorial_owner_header"}
            )
        if missing_track_render_cache_owner_markers:
            marker_failures.append(
                {"reason": "noncanonical_track_render_cache_header"}
            )
        if missing_sub_lazer_asset_cursor_markers:
            marker_failures.append(
                {"reason": "noncanonical_sub_lazer_asset_cursor_header"}
            )
        if missing_salt_asset_cursor_markers:
            marker_failures.append(
                {"reason": "noncanonical_salt_asset_cursor_header"}
            )
        if missing_runtime_grid_clear_cursor_markers:
            marker_failures.append(
                {"reason": "noncanonical_runtime_grid_clear_cursor_header"}
            )
        if missing_fringe_mesh_cursor_markers:
            marker_failures.append(
                {"reason": "noncanonical_fringe_mesh_cursor_header"}
            )
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_subgame_owner_markers": (
                        missing_subgame_owner_markers
                    ),
                    "missing_sub_loc_owner_markers": (
                        missing_sub_loc_owner_markers
                    ),
                    "missing_path_owner_markers": missing_path_owner_markers,
                    "missing_path_manager_owner_markers": (
                        missing_path_manager_owner_markers
                    ),
                    "missing_bod_core_owner_markers": missing_bod_core_owner_markers,
                    "missing_fringe_owner_markers": missing_fringe_owner_markers,
                    "missing_nuke_owner_markers": missing_nuke_owner_markers,
                    "missing_damage_guage_owner_markers": (
                        missing_damage_guage_owner_markers
                    ),
                    "missing_progress_bar_owner_markers": (
                        missing_progress_bar_owner_markers
                    ),
                    "missing_squidge_owner_markers": (
                        missing_squidge_owner_markers
                    ),
                    "missing_warning_owner_markers": (
                        missing_warning_owner_markers
                    ),
                    "missing_tip_owner_markers": missing_tip_owner_markers,
                    "missing_tutorial_owner_markers": (
                        missing_tutorial_owner_markers
                    ),
                    "missing_track_render_cache_owner_markers": (
                        missing_track_render_cache_owner_markers
                    ),
                    "missing_sub_lazer_asset_cursor_markers": (
                        missing_sub_lazer_asset_cursor_markers
                    ),
                    "missing_salt_asset_cursor_markers": (
                        missing_salt_asset_cursor_markers
                    ),
                    "missing_runtime_grid_clear_cursor_markers": (
                        missing_runtime_grid_clear_cursor_markers
                    ),
                    "missing_fringe_mesh_cursor_markers": (
                        missing_fringe_mesh_cursor_markers
                    ),
                    "failed": marker_failures,
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    fringe_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(FRINGE_OWNER_TYPE_ALIASES)
    )
    fringe_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "fringe",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in fringe_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    nuke_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(NUKE_OWNER_TYPE_ALIASES)
    )
    nuke_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "nuke",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in nuke_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    damage_guage_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(DAMAGE_GUAGE_OWNER_TYPE_ALIASES)
    )
    damage_guage_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "damage_guage",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in damage_guage_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    progress_bar_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(PROGRESS_BAR_OWNER_TYPE_ALIASES)
    )
    progress_bar_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "progress_bar",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in progress_bar_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    squidge_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(SQUIDGE_OWNER_TYPE_ALIASES)
    )
    squidge_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "squidge",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in squidge_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    warning_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(WARNING_OWNER_TYPE_ALIASES)
    )
    warning_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "warning",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in warning_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    tip_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(TIP_OWNER_TYPE_ALIASES)
    )
    tip_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "tip",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in tip_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    tutorial_owner_type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(TUTORIAL_OWNER_TYPE_ALIASES)
    )
    tutorial_owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "owner_group": "tutorial",
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in tutorial_owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    subgame_owner_sizes = {
        name: _named_struct_size(name)
        for name in SUBGAME_OWNER_SIZES
    }
    sub_loc_owner_sizes = {
        name: _named_struct_size(name)
        for name in SUB_LOC_OWNER_SIZES
    }
    path_owner_sizes = {
        name: _named_struct_size(name)
        for name in PATH_OWNER_SIZES
    }
    path_manager_owner_sizes = {
        name: _named_struct_size(name)
        for name in PATH_MANAGER_OWNER_SIZES
    }
    bod_core_owner_sizes = {
        name: _named_struct_size(name)
        for name in BOD_CORE_OWNER_SIZES
    }
    fringe_owner_sizes = {
        name: _named_struct_size(name)
        for name in FRINGE_OWNER_SIZES
    }
    nuke_owner_sizes = {
        name: _named_struct_size(name)
        for name in NUKE_OWNER_SIZES
    }
    nuke_owner_layout_readback = (
        {
            "type": "cRNuke",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or nuke_owner_type_alias_failures
        else _nuke_owner_layout_readback()
    )
    damage_guage_owner_sizes = {
        name: _named_struct_size(name)
        for name in DAMAGE_GUAGE_OWNER_SIZES
    }
    damage_guage_owner_layout_readback = (
        {
            "type": "cRDamageGuage",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or damage_guage_owner_type_alias_failures
        else _damage_guage_owner_layout_readback()
    )
    progress_bar_owner_sizes = {
        name: _named_struct_size(name)
        for name in PROGRESS_BAR_OWNER_SIZES
    }
    progress_bar_owner_layout_readback = (
        {
            "type": "cRProgressBar",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or progress_bar_owner_type_alias_failures
        else _progress_bar_owner_layout_readback()
    )
    squidge_owner_sizes = {
        name: _named_struct_size(name)
        for name in SQUIDGE_OWNER_SIZES
    }
    squidge_owner_layout_readback = (
        {
            "type": "cRSquidge",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or squidge_owner_type_alias_failures
        else _squidge_owner_layout_readback()
    )
    warning_owner_sizes = {
        name: _named_struct_size(name)
        for name in WARNING_OWNER_SIZES
    }
    warning_owner_layout_readback = (
        {
            "type": "cRWarning",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or warning_owner_type_alias_failures
        else _warning_owner_layout_readback()
    )
    tip_owner_sizes = {
        name: _named_struct_size(name)
        for name in TIP_OWNER_SIZES
    }
    tip_owner_layout_readback = (
        {"types": {}, "failures": []}
        if parse_errors or tip_owner_type_alias_failures
        else _tip_owner_layout_readback()
    )
    tutorial_owner_sizes = {
        name: _named_struct_size(name)
        for name in TUTORIAL_OWNER_SIZES
    }
    tutorial_owner_layout_readback = (
        {"type": "cRTutorial", "size": None, "members": {}, "failures": []}
        if parse_errors or tutorial_owner_type_alias_failures
        else _tutorial_owner_layout_readback()
    )
    track_render_cache_owner_sizes = {
        name: _named_struct_size(name)
        for name in TRACK_RENDER_CACHE_OWNER_SIZES
    }
    golb_shot_asset_cursor_size = _named_struct_size(
        "GolbShotVapourObjectStrideCursor"
    )
    sub_lazer_asset_cursor_size = _named_struct_size(
        "SubLazerBodyObjectStrideCursor"
    )
    salt_asset_cursor_size = _named_struct_size(
        "SaltOwnerGameStrideCursor"
    )
    track_row_cell_lane_flags_cursor_size = _named_struct_size(
        "TrackRowCellLaneAndFlagsStrideCursor"
    )
    track_row_cell_fringe_cursor_size = _named_struct_size(
        "TrackRowCellFringeFrontStrideCursor"
    )
    sub_row_parcel_spawn_y_cursor_size = _named_struct_size(
        "SubRowParcelSpawnYStrideCursor"
    )
    fringe_vertex_row_cursor_size = _named_struct_size(
        "FringeVertexRowCursorView"
    )
    fringe_face_pair_cursor_size = _named_struct_size(
        "FringeFaceQuadPairCursorView"
    )
    track_row_cell_tile_owner = _named_struct_member_readback("cRSubLoc", 0x3C)
    expected_track_row_cell_tile_owner = {
        "offset": "0x3c",
        "size": 1,
        "name": "tile_id",
        "type": "SubLocTileId",
    }
    player_shoot_members = {
        hex(offset): _named_struct_member_readback("Player", offset)
        for offset in PLAYER_SHOOT_EXPECTED_MEMBERS
    }
    subgame_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "subgame",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": subgame_owner_sizes[name],
        }
        for name, expected_size in SUBGAME_OWNER_SIZES.items()
        if subgame_owner_sizes[name] != expected_size
    ]
    sub_loc_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "sub_loc",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": sub_loc_owner_sizes[name],
        }
        for name, expected_size in SUB_LOC_OWNER_SIZES.items()
        if sub_loc_owner_sizes[name] != expected_size
    ]
    path_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "path",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": path_owner_sizes[name],
        }
        for name, expected_size in PATH_OWNER_SIZES.items()
        if path_owner_sizes[name] != expected_size
    ]
    path_manager_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "path_manager",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": path_manager_owner_sizes[name],
        }
        for name, expected_size in PATH_MANAGER_OWNER_SIZES.items()
        if path_manager_owner_sizes[name] != expected_size
    ]
    bod_core_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "bod_core",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": bod_core_owner_sizes[name],
        }
        for name, expected_size in BOD_CORE_OWNER_SIZES.items()
        if bod_core_owner_sizes[name] != expected_size
    ]
    fringe_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "fringe",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": fringe_owner_sizes[name],
        }
        for name, expected_size in FRINGE_OWNER_SIZES.items()
        if fringe_owner_sizes[name] != expected_size
    ]
    nuke_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "nuke",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": nuke_owner_sizes[name],
        }
        for name, expected_size in NUKE_OWNER_SIZES.items()
        if nuke_owner_sizes[name] != expected_size
    ]
    damage_guage_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "damage_guage",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": damage_guage_owner_sizes[name],
        }
        for name, expected_size in DAMAGE_GUAGE_OWNER_SIZES.items()
        if damage_guage_owner_sizes[name] != expected_size
    ]
    progress_bar_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "progress_bar",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": progress_bar_owner_sizes[name],
        }
        for name, expected_size in PROGRESS_BAR_OWNER_SIZES.items()
        if progress_bar_owner_sizes[name] != expected_size
    ]
    squidge_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "squidge",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": squidge_owner_sizes[name],
        }
        for name, expected_size in SQUIDGE_OWNER_SIZES.items()
        if squidge_owner_sizes[name] != expected_size
    ]
    warning_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "warning",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": warning_owner_sizes[name],
        }
        for name, expected_size in WARNING_OWNER_SIZES.items()
        if warning_owner_sizes[name] != expected_size
    ]
    tip_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "tip",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": tip_owner_sizes[name],
        }
        for name, expected_size in TIP_OWNER_SIZES.items()
        if tip_owner_sizes[name] != expected_size
    ]
    tutorial_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "tutorial",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": tutorial_owner_sizes[name],
        }
        for name, expected_size in TUTORIAL_OWNER_SIZES.items()
        if tutorial_owner_sizes[name] != expected_size
    ]
    track_render_cache_owner_size_failures = [
        {
            "selector": name,
            "owner_group": "track_render_cache",
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": track_render_cache_owner_sizes[name],
        }
        for name, expected_size in TRACK_RENDER_CACHE_OWNER_SIZES.items()
        if track_render_cache_owner_sizes[name] != expected_size
    ]
    owner_size_failures = (
        subgame_owner_size_failures
        + sub_loc_owner_size_failures
        + path_owner_size_failures
        + path_manager_owner_size_failures
        + bod_core_owner_size_failures
        + fringe_owner_size_failures
        + nuke_owner_size_failures
        + nuke_owner_layout_readback["failures"]
        + damage_guage_owner_size_failures
        + damage_guage_owner_layout_readback["failures"]
        + progress_bar_owner_size_failures
        + progress_bar_owner_layout_readback["failures"]
        + squidge_owner_size_failures
        + squidge_owner_layout_readback["failures"]
        + warning_owner_size_failures
        + warning_owner_layout_readback["failures"]
        + tip_owner_size_failures
        + tip_owner_layout_readback["failures"]
        + tutorial_owner_size_failures
        + tutorial_owner_layout_readback["failures"]
        + track_render_cache_owner_size_failures
    )
    if golb_shot_asset_cursor_size != GOLB_SHOT_ASSET_CURSOR_EXPECTED_SIZE:
        owner_size_failures.append(
            {
                "selector": "GolbShotVapourObjectStrideCursor",
                "owner_group": "golb_shot_asset_cursor",
                "reason": "owner_size_mismatch",
                "expected": GOLB_SHOT_ASSET_CURSOR_EXPECTED_SIZE,
                "observed": golb_shot_asset_cursor_size,
            }
        )
    if sub_lazer_asset_cursor_size != SUB_LAZER_ASSET_CURSOR_EXPECTED_SIZE:
        owner_size_failures.append(
            {
                "selector": "SubLazerBodyObjectStrideCursor",
                "owner_group": "sub_lazer_asset_cursor",
                "reason": "owner_size_mismatch",
                "expected": SUB_LAZER_ASSET_CURSOR_EXPECTED_SIZE,
                "observed": sub_lazer_asset_cursor_size,
            }
        )
    if salt_asset_cursor_size != SALT_ASSET_CURSOR_EXPECTED_SIZE:
        owner_size_failures.append(
            {
                "selector": "SaltOwnerGameStrideCursor",
                "owner_group": "salt_asset_cursor",
                "reason": "owner_size_mismatch",
                "expected": SALT_ASSET_CURSOR_EXPECTED_SIZE,
                "observed": salt_asset_cursor_size,
            }
        )
    if (
        track_row_cell_lane_flags_cursor_size
        != TRACK_ROW_CELL_LANE_FLAGS_CURSOR_EXPECTED_SIZE
    ):
        owner_size_failures.append(
            {
                "selector": "TrackRowCellLaneAndFlagsStrideCursor",
                "owner_group": "runtime_grid_clear_cursor",
                "reason": "owner_size_mismatch",
                "expected": TRACK_ROW_CELL_LANE_FLAGS_CURSOR_EXPECTED_SIZE,
                "observed": track_row_cell_lane_flags_cursor_size,
            }
        )
    if (
        track_row_cell_fringe_cursor_size
        != TRACK_ROW_CELL_FRINGE_CURSOR_EXPECTED_SIZE
    ):
        owner_size_failures.append(
            {
                "selector": "TrackRowCellFringeFrontStrideCursor",
                "owner_group": "runtime_grid_clear_cursor",
                "reason": "owner_size_mismatch",
                "expected": TRACK_ROW_CELL_FRINGE_CURSOR_EXPECTED_SIZE,
                "observed": track_row_cell_fringe_cursor_size,
            }
        )
    if (
        sub_row_parcel_spawn_y_cursor_size
        != SUB_ROW_PARCEL_SPAWN_Y_CURSOR_EXPECTED_SIZE
    ):
        owner_size_failures.append(
            {
                "selector": "SubRowParcelSpawnYStrideCursor",
                "owner_group": "runtime_grid_clear_cursor",
                "reason": "owner_size_mismatch",
                "expected": SUB_ROW_PARCEL_SPAWN_Y_CURSOR_EXPECTED_SIZE,
                "observed": sub_row_parcel_spawn_y_cursor_size,
            }
        )
    if fringe_vertex_row_cursor_size != FRINGE_VERTEX_ROW_CURSOR_EXPECTED_SIZE:
        owner_size_failures.append(
            {
                "selector": "FringeVertexRowCursorView",
                "owner_group": "fringe_mesh_cursor",
                "reason": "owner_size_mismatch",
                "expected": FRINGE_VERTEX_ROW_CURSOR_EXPECTED_SIZE,
                "observed": fringe_vertex_row_cursor_size,
            }
        )
    if fringe_face_pair_cursor_size != FRINGE_FACE_PAIR_CURSOR_EXPECTED_SIZE:
        owner_size_failures.append(
            {
                "selector": "FringeFaceQuadPairCursorView",
                "owner_group": "fringe_mesh_cursor",
                "reason": "owner_size_mismatch",
                "expected": FRINGE_FACE_PAIR_CURSOR_EXPECTED_SIZE,
                "observed": fringe_face_pair_cursor_size,
            }
        )
    if track_row_cell_tile_owner != expected_track_row_cell_tile_owner:
        owner_size_failures.append(
            {
                "selector": "cRSubLoc.tile_id",
                "owner_group": "track_row_cell",
                "reason": "tile_owner_mismatch",
                "expected": expected_track_row_cell_tile_owner,
                "observed": track_row_cell_tile_owner,
            }
        )
    for offset, expected in PLAYER_SHOOT_EXPECTED_MEMBERS.items():
        observed = player_shoot_members[hex(offset)]
        if observed != expected:
            owner_size_failures.append(
                {
                    "selector": f"Player.{expected['name']}",
                    "owner_group": "player_shoot_state",
                    "reason": "member_mismatch",
                    "expected": expected,
                    "observed": observed,
                }
            )
    if (
        parse_errors
        or fringe_owner_type_alias_failures
        or nuke_owner_type_alias_failures
        or damage_guage_owner_type_alias_failures
        or progress_bar_owner_type_alias_failures
        or squidge_owner_type_alias_failures
        or warning_owner_type_alias_failures
        or tip_owner_type_alias_failures
        or tutorial_owner_type_alias_failures
        or owner_size_failures
    ):
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "fringe_owner_type_alias_migrations": (
                        fringe_owner_type_alias_migrations
                    ),
                    "nuke_owner_type_alias_migrations": (
                        nuke_owner_type_alias_migrations
                    ),
                    "damage_guage_owner_type_alias_migrations": (
                        damage_guage_owner_type_alias_migrations
                    ),
                    "progress_bar_owner_type_alias_migrations": (
                        progress_bar_owner_type_alias_migrations
                    ),
                    "squidge_owner_type_alias_migrations": (
                        squidge_owner_type_alias_migrations
                    ),
                    "warning_owner_type_alias_migrations": (
                        warning_owner_type_alias_migrations
                    ),
                    "tip_owner_type_alias_migrations": (
                        tip_owner_type_alias_migrations
                    ),
                    "tutorial_owner_type_alias_migrations": (
                        tutorial_owner_type_alias_migrations
                    ),
                    "subgame_owner_sizes": subgame_owner_sizes,
                    "sub_loc_owner_sizes": sub_loc_owner_sizes,
                    "path_owner_sizes": path_owner_sizes,
                    "path_manager_owner_sizes": path_manager_owner_sizes,
                    "bod_core_owner_sizes": bod_core_owner_sizes,
                    "fringe_owner_sizes": fringe_owner_sizes,
                    "nuke_owner_sizes": nuke_owner_sizes,
                    "nuke_owner_layout_readback": nuke_owner_layout_readback,
                    "damage_guage_owner_sizes": damage_guage_owner_sizes,
                    "damage_guage_owner_layout_readback": (
                        damage_guage_owner_layout_readback
                    ),
                    "progress_bar_owner_sizes": progress_bar_owner_sizes,
                    "progress_bar_owner_layout_readback": (
                        progress_bar_owner_layout_readback
                    ),
                    "squidge_owner_sizes": squidge_owner_sizes,
                    "squidge_owner_layout_readback": (
                        squidge_owner_layout_readback
                    ),
                    "warning_owner_sizes": warning_owner_sizes,
                    "warning_owner_layout_readback": (
                        warning_owner_layout_readback
                    ),
                    "tip_owner_sizes": tip_owner_sizes,
                    "tip_owner_layout_readback": tip_owner_layout_readback,
                    "tutorial_owner_sizes": tutorial_owner_sizes,
                    "tutorial_owner_layout_readback": (
                        tutorial_owner_layout_readback
                    ),
                    "track_render_cache_owner_sizes": track_render_cache_owner_sizes,
                    "golb_shot_asset_cursor_size": golb_shot_asset_cursor_size,
                    "sub_lazer_asset_cursor_size": sub_lazer_asset_cursor_size,
                    "salt_asset_cursor_size": salt_asset_cursor_size,
                    "fringe_vertex_row_cursor_size": (
                        fringe_vertex_row_cursor_size
                    ),
                    "fringe_face_pair_cursor_size": fringe_face_pair_cursor_size,
                    "track_row_cell_tile_owner": track_row_cell_tile_owner,
                    "player_shoot_members": player_shoot_members,
                    "failed": (
                        fringe_owner_type_alias_failures
                        + nuke_owner_type_alias_failures
                        + damage_guage_owner_type_alias_failures
                        + progress_bar_owner_type_alias_failures
                        + squidge_owner_type_alias_failures
                        + warning_owner_type_alias_failures
                        + tip_owner_type_alias_failures
                        + tutorial_owner_type_alias_failures
                        + owner_size_failures
                    ),
                },
                indent=2,
            )
        )
        return 1

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    type_changes = []
    missing = []
    failed = []

    renderable_bod_frame_owner = _sync_renderable_bod_frame_number(
        header_path
    )
    if renderable_bod_frame_owner.get("status") == "failed":
        failed.append(
            {"renderable_bod_frame_owner": renderable_bod_frame_owner}
        )

    face_movie_owner = _sync_face_movie_owner()
    if face_movie_owner.get("status") == "failed":
        failed.append({"face_movie_owner": face_movie_owner})

    golb_shot_prefix_owner = _sync_golb_shot_prefix_owner(header_path)
    if golb_shot_prefix_owner.get("status") == "failed":
        failed.append({"golb_shot_prefix_owner": golb_shot_prefix_owner})

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "selector": name, "reason": "rename_failed"})
            continue
        renamed += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected_observed = _data_declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))
        if normalized_current == expected_observed:
            data_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "data_type_failed",
                }
            )
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected_observed:
            failed.append(
                {
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue
        data_applied += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func_start(address) == idc.BADADDR:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        current_type = idc.get_type(address)
        normalized_current = _normalize_type_text(current_type)

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
        type_changes.append(
            {
                "selector": selector,
                "address": hex(address),
                "before": current_type,
                "after": observed,
            }
        )

    game_root_owner_graph = sync_game_root_owner_graph(require=True)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
        )

    tutorial_numeric_operands = _normalize_root_offset_operands(
        TUTORIAL_NUMERIC_OPERANDS
    )
    for result in tutorial_numeric_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "Tutorial lifecycle",
                    "numeric_operand": result,
                }
            )

    attachment_entry_root_offset_operands = (
        _normalize_root_offset_operands(ATTACHMENT_ENTRY_ROOT_OFFSET_OPERANDS)
    )
    for result in attachment_entry_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "try_enter_track_attachment_from_swept_motion",
                    "root_offset_operand": result,
                }
            )
    world_initializer_root_offset_operands = _normalize_root_offset_operands(
        WORLD_INITIALIZER_ROOT_OFFSET_OPERANDS
    )
    for result in world_initializer_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "initialize_game_assets_and_world",
                    "root_offset_operand": result,
                }
            )
    high_score_lifecycle_offset_operands = _normalize_root_offset_operands(
        HIGH_SCORE_LIFECYCLE_OFFSET_OPERANDS
    )
    for result in high_score_lifecycle_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "high-score lifecycle",
                    "root_offset_operand": result,
                }
            )
    player_root_borrow_offset_operands = _normalize_root_offset_operands(
        PLAYER_ROOT_BORROW_OFFSET_OPERANDS
    )
    for result in player_root_borrow_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "Player root borrows",
                    "root_offset_operand": result,
                }
            )
    player_state_gate_offset_operands = _normalize_root_offset_operands(
        PLAYER_STATE_GATE_OFFSET_OPERANDS
    )
    for result in player_state_gate_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "Player state gates",
                    "root_offset_operand": result,
                }
            )
    attachment_follow_root_offset_operands = _normalize_root_offset_operands(
        ATTACHMENT_FOLLOW_ROOT_OFFSET_OPERANDS
    )
    for result in attachment_follow_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "attachment follow lifecycle",
                    "root_offset_operand": result,
                }
            )
    harmonize_root_offset_operands = _normalize_root_offset_operands(
        HARMONIZE_ROOT_OFFSET_OPERANDS
    )
    for result in harmonize_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "harmonize_center_lane_floor_slide_variants",
                    "root_offset_operand": result,
                }
            )
    runtime_pool_row_offset_operands = _normalize_root_offset_operands(
        RUNTIME_POOL_ROW_OFFSET_OPERANDS
    )
    for result in runtime_pool_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "initialize_runtime_pools_and_path_template_bank",
                    "root_offset_operand": result,
                }
            )
    fringe_runtime_row_offset_operands = _normalize_root_offset_operands(
        FRINGE_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in fringe_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "build_track_fringe_objects",
                    "root_offset_operand": result,
                }
            )
    runtime_row_lookup_offset_operands = _normalize_root_offset_operands(
        RUNTIME_ROW_LOOKUP_OFFSET_OPERANDS
    )
    for result in runtime_row_lookup_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "get_track_runtime_cell_at_world_z",
                    "root_offset_operand": result,
                }
            )
    project_attachment_runtime_row_offset_operands = (
        _normalize_root_offset_operands(
            PROJECT_ATTACHMENT_RUNTIME_ROW_OFFSET_OPERANDS
        )
    )
    for result in project_attachment_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "project_position_onto_track_attachment",
                    "root_offset_operand": result,
                }
            )
    remove_subgame_bods_runtime_row_offset_operands = (
        _normalize_root_offset_operands(
            REMOVE_SUBGAME_BODS_RUNTIME_ROW_OFFSET_OPERANDS
        )
    )
    for result in remove_subgame_bods_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "remove_subgame_bods",
                    "root_offset_operand": result,
                }
            )
    merge_runtime_row_offset_operands = _normalize_root_offset_operands(
        MERGE_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in merge_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "merge_track_tile_runs",
                    "root_offset_operand": result,
                }
            )
    remove_sub_loc_runtime_row_offset_operands = _normalize_root_offset_operands(
        REMOVE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in remove_sub_loc_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "remove_sub_loc",
                    "root_offset_operand": result,
                }
            )
    update_sub_loc_runtime_row_offset_operands = _normalize_root_offset_operands(
        UPDATE_SUB_LOC_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in update_sub_loc_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "update_sub_loc",
                    "root_offset_operand": result,
                }
            )
    populate_runtime_row_offset_operands = _normalize_root_offset_operands(
        POPULATE_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in populate_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "populate_runtime_track_cells_from_segments",
                    "root_offset_operand": result,
                }
            )
    place_parcels_runtime_row_offset_operands = _normalize_root_offset_operands(
        PLACE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in place_parcels_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "place_parcels_on_track",
                    "root_offset_operand": result,
                }
            )
    challenge_parcels_runtime_row_offset_operands = _normalize_root_offset_operands(
        CHALLENGE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in challenge_parcels_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "place_challenge_parcels_on_track",
                    "root_offset_operand": result,
                }
            )
    update_subgame_runtime_row_offset_operands = _normalize_root_offset_operands(
        UPDATE_SUBGAME_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in update_subgame_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "update_subgame",
                    "root_offset_operand": result,
                }
            )
    update_subgame_runtime_flag_operands = _normalize_root_offset_operands(
        UPDATE_SUBGAME_RUNTIME_FLAG_OPERANDS
    )
    for result in update_subgame_runtime_flag_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "update_subgame",
                    "runtime_flag_operand": result,
                }
            )
    update_subgoldy_runtime_row_offset_operands = _normalize_root_offset_operands(
        UPDATE_SUBGOLDY_RUNTIME_ROW_OFFSET_OPERANDS
    )
    for result in update_subgoldy_runtime_row_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "update_subgoldy",
                    "root_offset_operand": result,
                }
            )
    initialize_subgame_record_bank_offset_operands = (
        _normalize_root_offset_operands(
            INITIALIZE_SUBGAME_RECORD_BANK_OFFSET_OPERANDS
        )
    )
    for result in initialize_subgame_record_bank_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "initialize_subgame",
                    "record_bank_offset_operand": result,
                }
            )
    subhover_player_root_offset_operands = _normalize_root_offset_operands(
        SUBHOVER_PLAYER_ROOT_OFFSET_OPERANDS
    )
    for result in subhover_player_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "initialize_jetpack_gauge",
                    "root_offset_operand": result,
                }
            )

    lvar_view = _sync_build_track_render_cache_lvar()
    if lvar_view.get("status") == "failed":
        failed.append({"selector": "build_track_render_caches", "lvar_view": lvar_view})
    build_track_render_cache_counter_lvars = (
        _sync_build_track_render_cache_counter_lvars()
    )
    if build_track_render_cache_counter_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "build_track_render_caches",
                "counter_lvars": build_track_render_cache_counter_lvars,
            }
        )
    frontend_color_lvars = _sync_color_lvars("initialize_frontend_widget")
    if frontend_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_frontend_widget",
                "color_lvars": frontend_color_lvars,
            }
        )
    update_sub_loc_color_lvars = _sync_color_lvars("update_sub_loc")
    if update_sub_loc_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_sub_loc",
                "color_lvars": update_sub_loc_color_lvars,
            }
        )
    get_track_skirt_color_lvars = _sync_color_lvars("get_track_skirt_color")
    if get_track_skirt_color_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "get_track_skirt_color",
                "color_lvars": get_track_skirt_color_lvars,
            }
        )
    populate_runtime_lvars = _sync_populate_runtime_lvars()
    if populate_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "populate_runtime_track_cells_from_segments",
                "runtime_lvars": populate_runtime_lvars,
            }
        )
    golb_path_follow_copy_ownership = _sync_golb_path_follow_copy_ownership()
    if golb_path_follow_copy_ownership.get("status") == "failed":
        failed.append(
            {
                "selector": "traverse_path_follow_golb",
                "copy_ownership": golb_path_follow_copy_ownership,
            }
        )
    place_parcels_runtime_lvars = _sync_place_parcels_runtime_lvars()
    if place_parcels_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "place_parcels_on_track",
                "runtime_lvars": place_parcels_runtime_lvars,
            }
        )
    challenge_parcels_runtime_lvars = _sync_challenge_parcels_runtime_lvars()
    if challenge_parcels_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "place_challenge_parcels_on_track",
                "runtime_lvars": challenge_parcels_runtime_lvars,
            }
        )
    project_attachment_lvars = _sync_project_attachment_lvars()
    if project_attachment_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "project_position_onto_track_attachment",
                "ownership_lvars": project_attachment_lvars,
            }
        )
    remove_sub_loc_runtime_lvars = _sync_remove_sub_loc_runtime_lvars()
    if remove_sub_loc_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "remove_sub_loc",
                "runtime_lvars": remove_sub_loc_runtime_lvars,
            }
        )
    update_subgame_runtime_lvars = _sync_update_subgame_runtime_lvars()
    if update_subgame_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_subgame",
                "runtime_lvars": update_subgame_runtime_lvars,
            }
        )
    update_subgoldy_lvars = _sync_update_subgoldy_lvars()
    if update_subgoldy_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_subgoldy",
                "ownership_lvars": update_subgoldy_lvars,
            }
        )
    initialize_subgoldy_lvars = _sync_initialize_subgoldy_lvars()
    if initialize_subgoldy_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_subgoldy",
                "ownership_lvars": initialize_subgoldy_lvars,
            }
        )
    shoot_subgoldy_lvars = _sync_shoot_subgoldy_lvars()
    if shoot_subgoldy_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "shoot_subgoldy",
                "ownership_lvars": shoot_subgoldy_lvars,
            }
        )
    world_initializer_golb_asset_lvars = (
        _sync_world_initializer_golb_asset_lvars()
    )
    if world_initializer_golb_asset_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "asset_cursor_lvars": world_initializer_golb_asset_lvars,
            }
        )
    world_initializer_sub_lazer_asset_lvars = (
        _sync_world_initializer_sub_lazer_asset_lvars()
    )
    if world_initializer_sub_lazer_asset_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "sub_lazer_asset_cursor_lvars": (
                    world_initializer_sub_lazer_asset_lvars
                ),
            }
        )
    world_initializer_salt_asset_lvars = (
        _sync_world_initializer_salt_asset_lvars()
    )
    if world_initializer_salt_asset_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_game_assets_and_world",
                "salt_asset_cursor_lvars": (
                    world_initializer_salt_asset_lvars
                ),
            }
        )
    remove_subgame_bods_cursor_lvars = _sync_remove_subgame_bods_cursor_lvars()
    if remove_subgame_bods_cursor_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "remove_subgame_bods",
                "cursor_lvars": remove_subgame_bods_cursor_lvars,
            }
        )
    spawn_track_ring_lvars = _sync_spawn_track_ring_lvars()
    if spawn_track_ring_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "spawn_track_ring_or_special_effect",
                "ownership_lvars": spawn_track_ring_lvars,
            }
        )
    ring_parent_radius_lvars = _sync_ring_parent_radius_lvars()
    if ring_parent_radius_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_ring_or_special_effect_parent",
                "radius_lvars": ring_parent_radius_lvars,
            }
        )
    ring_particle_parent_position_lvar = (
        _sync_ring_particle_parent_position_lvar()
    )
    if ring_particle_parent_position_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "update_ring_or_special_effect_particle",
                "parent_position_lvar": ring_particle_parent_position_lvar,
            }
        )
    spawn_track_health_lvars = _sync_spawn_track_health_lvars()
    if spawn_track_health_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "spawn_track_health_pickup",
                "ownership_lvars": spawn_track_health_lvars,
            }
        )
    spawn_track_jetpack_lvars = _sync_spawn_track_jetpack_lvars()
    if spawn_track_jetpack_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "spawn_track_jetpack_pickup",
                "ownership_lvars": spawn_track_jetpack_lvars,
            }
        )
    firework_shoot_lvars = _sync_firework_shoot_lvars()
    if firework_shoot_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "firework_shoot",
                "particle_lvars": firework_shoot_lvars,
            }
        )
    loading_quad_lvars = _sync_loading_quad_lvars()
    if loading_quad_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "loading_screen",
                "quad_lvars": loading_quad_lvars,
            }
        )
    spawn_salt_hazard_lvars = _sync_spawn_salt_hazard_lvars()
    if spawn_salt_hazard_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "spawn_salt_hazard",
                "ownership_lvars": spawn_salt_hazard_lvars,
            }
        )
    collision_pool_cursor_lvars = _sync_collision_pool_cursor_lvars()
    if collision_pool_cursor_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "handle_subgoldy_collisions",
                "cursor_lvars": collision_pool_cursor_lvars,
            }
        )
    merge_runtime_lvars = _sync_merge_runtime_lvars()
    if merge_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "merge_track_tile_runs",
                "runtime_lvars": merge_runtime_lvars,
            }
        )
    fringe_runtime_lvars = _sync_fringe_runtime_lvars()
    if fringe_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "build_track_fringe_objects",
                "runtime_lvars": fringe_runtime_lvars,
            }
        )
    fringe_mesh_lvars = _sync_fringe_mesh_lvars()
    if fringe_mesh_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "fringe_mesh_builders",
                "cursor_lvars": fringe_mesh_lvars,
            }
        )
    harmonize_runtime_lvars = _sync_harmonize_runtime_lvars()
    if harmonize_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "harmonize_center_lane_floor_slide_variants",
                "runtime_lvars": harmonize_runtime_lvars,
            }
        )
    build_subgame_active_bod_lvars = _sync_build_subgame_active_bod_lvars()
    if build_subgame_active_bod_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "build_subgame_level",
                "active_bod_lvars": build_subgame_active_bod_lvars,
            }
        )
    subgame_receiver_lvar_specs = {
        "initialize_subgame": 1,
        "destroy_subgame": 1,
        "update_subgame": 1,
        "remove_subgame_bods": 1,
        "build_track_fringe_objects": 1,
        "promote_track_tiles_to_fringe_variants": 1,
        "harmonize_center_lane_floor_slide_variants": 1,
        "select_track_tile_edge_variants": 1,
        "get_track_grid_cell_at_world_position": 2,
        "sample_track_floor_height_at_position": 2,
        "project_position_onto_track_attachment": 3,
        "spawn_track_health_pickup": 3,
        "spawn_track_jetpack_pickup": 3,
    }
    subgame_receiver_lvars = {
        selector: _sync_subgame_receiver_lvar(
            selector,
            argument_count=argument_count,
        )
        for selector, argument_count in subgame_receiver_lvar_specs.items()
    }
    for selector, receiver_lvar in subgame_receiver_lvars.items():
        if receiver_lvar.get("status") == "failed":
            failed.append({"selector": selector, "receiver_lvar": receiver_lvar})

    dirty_functions = []
    for address in PATH_OWNERSHIP_DIRTY_FUNCTIONS:
        if ida_funcs.get_func_start(address) != idc.BADADDR:
            ida_hexrays.mark_cfunc_dirty(address, True)
            dirty_functions.append(hex(address))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "fringe_owner_type_alias_migrations": (
                    fringe_owner_type_alias_migrations
                ),
                "nuke_owner_type_alias_migrations": (
                    nuke_owner_type_alias_migrations
                ),
                "damage_guage_owner_type_alias_migrations": (
                    damage_guage_owner_type_alias_migrations
                ),
                "progress_bar_owner_type_alias_migrations": (
                    progress_bar_owner_type_alias_migrations
                ),
                "squidge_owner_type_alias_migrations": (
                    squidge_owner_type_alias_migrations
                ),
                "warning_owner_type_alias_migrations": (
                    warning_owner_type_alias_migrations
                ),
                "tip_owner_type_alias_migrations": (
                    tip_owner_type_alias_migrations
                ),
                "tutorial_owner_type_alias_migrations": (
                    tutorial_owner_type_alias_migrations
                ),
                "subgame_owner_sizes": subgame_owner_sizes,
                "sub_loc_owner_sizes": sub_loc_owner_sizes,
                "path_owner_sizes": path_owner_sizes,
                "path_manager_owner_sizes": path_manager_owner_sizes,
                "bod_core_owner_sizes": bod_core_owner_sizes,
                "fringe_owner_sizes": fringe_owner_sizes,
                "nuke_owner_sizes": nuke_owner_sizes,
                "nuke_owner_layout_readback": nuke_owner_layout_readback,
                "damage_guage_owner_sizes": damage_guage_owner_sizes,
                "damage_guage_owner_layout_readback": (
                    damage_guage_owner_layout_readback
                ),
                "progress_bar_owner_sizes": progress_bar_owner_sizes,
                "progress_bar_owner_layout_readback": (
                    progress_bar_owner_layout_readback
                ),
                "squidge_owner_sizes": squidge_owner_sizes,
                "squidge_owner_layout_readback": squidge_owner_layout_readback,
                "warning_owner_sizes": warning_owner_sizes,
                "warning_owner_layout_readback": warning_owner_layout_readback,
                "tip_owner_sizes": tip_owner_sizes,
                "tip_owner_layout_readback": tip_owner_layout_readback,
                "tutorial_owner_sizes": tutorial_owner_sizes,
                "tutorial_owner_layout_readback": (
                    tutorial_owner_layout_readback
                ),
                "track_render_cache_owner_sizes": track_render_cache_owner_sizes,
                "golb_shot_asset_cursor_size": golb_shot_asset_cursor_size,
                "sub_lazer_asset_cursor_size": sub_lazer_asset_cursor_size,
                "salt_asset_cursor_size": salt_asset_cursor_size,
                "track_row_cell_lane_flags_cursor_size": (
                    track_row_cell_lane_flags_cursor_size
                ),
                "track_row_cell_fringe_cursor_size": (
                    track_row_cell_fringe_cursor_size
                ),
                "sub_row_parcel_spawn_y_cursor_size": (
                    sub_row_parcel_spawn_y_cursor_size
                ),
                "fringe_vertex_row_cursor_size": fringe_vertex_row_cursor_size,
                "fringe_face_pair_cursor_size": fringe_face_pair_cursor_size,
                "track_row_cell_tile_owner": track_row_cell_tile_owner,
                "player_shoot_members": player_shoot_members,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "type_changes": type_changes,
                "renderable_bod_frame_owner": renderable_bod_frame_owner,
                "face_movie_owner": face_movie_owner,
                "golb_shot_prefix_owner": golb_shot_prefix_owner,
                "game_root_owner_graph": game_root_owner_graph,
                "tutorial_numeric_operands": tutorial_numeric_operands,
                "attachment_entry_root_offset_operands": attachment_entry_root_offset_operands,
                "world_initializer_root_offset_operands": world_initializer_root_offset_operands,
                "high_score_lifecycle_offset_operands": high_score_lifecycle_offset_operands,
                "player_root_borrow_offset_operands": player_root_borrow_offset_operands,
                "player_state_gate_offset_operands": player_state_gate_offset_operands,
                "attachment_follow_root_offset_operands": attachment_follow_root_offset_operands,
                "harmonize_root_offset_operands": harmonize_root_offset_operands,
                "runtime_pool_row_offset_operands": runtime_pool_row_offset_operands,
                "fringe_runtime_row_offset_operands": fringe_runtime_row_offset_operands,
                "runtime_row_lookup_offset_operands": runtime_row_lookup_offset_operands,
                "project_attachment_runtime_row_offset_operands": project_attachment_runtime_row_offset_operands,
                "remove_subgame_bods_runtime_row_offset_operands": remove_subgame_bods_runtime_row_offset_operands,
                "merge_runtime_row_offset_operands": merge_runtime_row_offset_operands,
                "remove_sub_loc_runtime_row_offset_operands": remove_sub_loc_runtime_row_offset_operands,
                "update_sub_loc_runtime_row_offset_operands": update_sub_loc_runtime_row_offset_operands,
                "populate_runtime_row_offset_operands": populate_runtime_row_offset_operands,
                "place_parcels_runtime_row_offset_operands": place_parcels_runtime_row_offset_operands,
                "challenge_parcels_runtime_row_offset_operands": challenge_parcels_runtime_row_offset_operands,
                "update_subgame_runtime_row_offset_operands": update_subgame_runtime_row_offset_operands,
                "update_subgame_runtime_flag_operands": update_subgame_runtime_flag_operands,
                "update_subgoldy_runtime_row_offset_operands": update_subgoldy_runtime_row_offset_operands,
                "initialize_subgame_record_bank_offset_operands": initialize_subgame_record_bank_offset_operands,
                "subhover_player_root_offset_operands": subhover_player_root_offset_operands,
                "lvar_view": lvar_view,
                "build_track_render_cache_counter_lvars": build_track_render_cache_counter_lvars,
                "frontend_color_lvars": frontend_color_lvars,
                "update_sub_loc_color_lvars": update_sub_loc_color_lvars,
                "get_track_skirt_color_lvars": get_track_skirt_color_lvars,
                "populate_runtime_lvars": populate_runtime_lvars,
                "golb_path_follow_copy_ownership": golb_path_follow_copy_ownership,
                "place_parcels_runtime_lvars": place_parcels_runtime_lvars,
                "challenge_parcels_runtime_lvars": challenge_parcels_runtime_lvars,
                "project_attachment_lvars": project_attachment_lvars,
                "remove_sub_loc_runtime_lvars": remove_sub_loc_runtime_lvars,
                "update_subgame_runtime_lvars": update_subgame_runtime_lvars,
                "update_subgoldy_lvars": update_subgoldy_lvars,
                "initialize_subgoldy_lvars": initialize_subgoldy_lvars,
                "shoot_subgoldy_lvars": shoot_subgoldy_lvars,
                "world_initializer_golb_asset_lvars": (
                    world_initializer_golb_asset_lvars
                ),
                "world_initializer_sub_lazer_asset_lvars": (
                    world_initializer_sub_lazer_asset_lvars
                ),
                "world_initializer_salt_asset_lvars": (
                    world_initializer_salt_asset_lvars
                ),
                "remove_subgame_bods_cursor_lvars": remove_subgame_bods_cursor_lvars,
                "spawn_track_ring_lvars": spawn_track_ring_lvars,
                "ring_parent_radius_lvars": ring_parent_radius_lvars,
                "ring_particle_parent_position_lvar": (
                    ring_particle_parent_position_lvar
                ),
                "spawn_track_health_lvars": spawn_track_health_lvars,
                "spawn_track_jetpack_lvars": spawn_track_jetpack_lvars,
                "firework_shoot_lvars": firework_shoot_lvars,
                "loading_quad_lvars": loading_quad_lvars,
                "spawn_salt_hazard_lvars": spawn_salt_hazard_lvars,
                "collision_pool_cursor_lvars": collision_pool_cursor_lvars,
                "merge_runtime_lvars": merge_runtime_lvars,
                "fringe_runtime_lvars": fringe_runtime_lvars,
                "fringe_mesh_lvars": fringe_mesh_lvars,
                "harmonize_runtime_lvars": harmonize_runtime_lvars,
                "build_subgame_active_bod_lvars": build_subgame_active_bod_lvars,
                "subgame_receiver_lvars": subgame_receiver_lvars,
                "dirty_functions": dirty_functions,
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
        print(
            "usage: apply_path_template_types.py <header-path> "
            "[--bod-core-only|--replay-start-cursor-only|--golb-base-only]",
            file=sys.stderr,
        )
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    if not header_path.is_file():
        print(f"missing header: {header_path}", file=sys.stderr)
        ida_pro.qexit(2)
        return

    mode_args = set(argv[2:])
    if mode_args == {"--bod-core-only"}:
        result = _sync_renderable_bod_frame_number(header_path)
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "mode": "bod_core_only",
                    "result": result,
                },
                indent=2,
            )
        )
        exit_code = 1 if result.get("status") == "failed" else 0
    elif mode_args == {"--replay-start-cursor-only"}:
        result = _sync_replay_start_cursor_fields()
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "mode": "replay_start_cursor_only",
                    "result": result,
                },
                indent=2,
            )
        )
        exit_code = 1 if result.get("status") == "failed" else 0
    elif mode_args == {"--golb-base-only"}:
        result = _sync_golb_shot_prefix_owner(header_path)
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "mode": "golb_base_only",
                    "result": result,
                },
                indent=2,
            )
        )
        exit_code = 1 if result.get("status") == "failed" else 0
    elif mode_args:
        print(f"unsupported mode arguments: {sorted(mode_args)!r}", file=sys.stderr)
        exit_code = 2
    else:
        exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
