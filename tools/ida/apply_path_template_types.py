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

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_NAMES = [
    (0x4034D0, "update_input_ok"),
    (0x403560, "initialize_input_ok"),
    (0x404030, "update_twinkle_manager"),
    (0x404070, "draw_twinkle"),
    (0x404080, "update_twinkle"),
    (0x404580, "border_mouse_test"),
    (0x4086D0, "initialize_player_presentation_controller"),
    (0x440F80, "update_barrier_ai"),
    (0x440FA0, "initialize_damage_gauge"),
    (0x440FD0, "update_damage_gauge"),
    (0x4413F0, "apply_damage_gauge_delta"),
    (0x447090, "initialize_fringe_manager"),
    (0x4470A0, "allocate_fringe_object"),
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
    (0x44D1A0, "multiply_matrix"),
    (0x44D1D0, "multiply_matrix_in_place_forward_thunk"),
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
    (0x497354, "g_player_presentation_noop_vtable"),
    (0x497358, "g_invincible_shell_update_vtable"),
    (0x49735C, "g_weapon_noop_vtable"),
    (0x503290, "g_loading_bar"),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4AC5C8, "g_default_tip_message", "TipData g_default_tip_message;"),
    (0x503290, "g_loading_bar", "LoadingBar g_loading_bar;"),
]

# Header field-name changes need an explicit Hex-Rays refresh even when the
# owning function prototype itself was already current.
PATH_OWNERSHIP_DIRTY_FUNCTIONS = (
    0x420CB0,  # update_track_attachment_follow_state
    0x42C600,  # finalize_path_template
    0x42C770,  # try_enter_track_attachment_from_swept_motion
    0x434BE0,  # build_track_fringe_objects
    0x435180,  # merge_track_tile_runs
    0x4356F0,  # harmonize_center_lane_floor_slide_variants
    0x435EB0,  # populate_runtime_track_cells_from_segments
    0x438B90,  # update_subgame
    0x43B120,  # update_subgoldy
    0x43DF10,  # spawn_track_ring_or_special_effect
    0x4438E0,  # place_parcels_on_track
    0x444240,  # place_challenge_parcels_on_track
    0x444CF0,  # handle_subgoldy_collisions
    0x447090,  # initialize_fringe_manager
    0x4470A0,  # allocate_fringe_object
)

POPULATE_RUNTIME_LVAR_SPECS = (
    ("segment_row_index", "int32_t segment_row_index;", 0x4362E6, 56),
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
)

PLACE_PARCELS_RUNTIME_LVAR_SPECS = (
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

CHALLENGE_PARCELS_RUNTIME_LVAR_SPECS = (
    (
        "challenge_runtime_row_anchor",
        "RuntimeRowStrideAnchor *challenge_runtime_row_anchor;",
        0x44432E,
        None,
    ),
    (
        "projection_row",
        "SubRow *projection_row;",
        0x4443D8,
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

REMOVE_SUBGAME_BODS_CURSOR_LVAR_SPECS = (
    ("runtime_cell_cursor", "TrackRowCell *runtime_cell_cursor;", 0x44091A, None),
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
)

MERGE_RUNTIME_LVAR_SPECS = (
    ("seed_lane_flags", "uint32_t *seed_lane_flags;", 0x435195, None),
    ("cell_lane_flags", "uint32_t *cell_lane_flags;", 0x4351D8, None),
    ("cell", "TrackRowCell *cell;", 0x4351EA, None),
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
    ("cell", "TrackRowCell *cell;", 0x434C15, None),
    ("row_cursor", "SubRow *row_cursor;", 0x434C1B, 40),
    ("fringe_front_new", "FringeObject *fringe_front_new;", 0x434D44, None),
    ("fringe_right_new", "FringeObject *fringe_right_new;", 0x434E48, None),
    ("fringe_left_new", "FringeObject *fringe_left_new;", 0x434F4C, None),
    ("fringe_back_new", "FringeObject *fringe_back_new;", 0x435050, None),
)

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
# access back into its canonical Player/SubgameRuntime field. Keep the symbol
# names themselves intact and normalize only the seven proven displacement
# operands in the attachment-entry seed tail.
ATTACHMENT_ENTRY_ROOT_OFFSET_OPERANDS = (
    (0x42C98A, 0, 0x430199),  # Player::attachment_exit_pending
    (0x42C99C, 1, 0x4340C0),  # Player::squidge
    (0x42C9B4, 0, 0x430100),  # Player::follow_state.active
    (0x42CA18, 1, 0x42FD7C),  # FollowState::player -> Player
    (0x42CA3D, 1, 0x64118C),  # runtime_rows[row].installed_heading_delta
    (0x42CA5B, 0, 0x430118),  # FollowState::orientation_a
    (0x42CA7B, 1, 0x430100),  # Player::follow_state
)

# The follow updater has the same address-expression collision in two Player
# basis-row publications and seven repeated runtime-row cell loads.
ATTACHMENT_FOLLOW_ROOT_OFFSET_OPERANDS = (
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

# The runtime-row displacement numerically collides with an IDA auto-symbol at
# 0x5ccac8. Normalize this one proven LEA operand so Hex-Rays can fold the
# already typed SubgameRuntime receiver into runtime_rows instead of treating
# the displacement as the address of an unrelated byte global.
FRINGE_RUNTIME_ROW_OFFSET_OPERANDS = (
    (0x434C0C, 1, 0x5CCAC8),
)

# Both parcel-claim loops retain a containing SubgameRuntime base and access a
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
# IDA auto-symbol addresses; the earlier parcel_set_id scan intentionally
# remains a native field cursor rather than a fabricated container-of owner.
CHALLENGE_PARCELS_RUNTIME_ROW_OFFSET_OPERANDS = (
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

# The main tick carries one SubgameRuntime-relative row anchor through a stack
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


TRUSTED_DECLARATIONS = [
    (
        "initialize_fringe_manager",
        "void __thiscall initialize_fringe_manager(FringeManager* manager);",
    ),
    (
        "allocate_fringe_object",
        "FringeObject* __thiscall allocate_fringe_object(FringeManager* manager);",
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
        "void __thiscall create_golb(GolbShot* shot, Player* player, int32_t spawn_selector, int32_t emitter_index);",
    ),
    (
        "update_movement_flag_emitters",
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source);",
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
        "destroy_help_screen",
        "void __thiscall destroy_help_screen(Help* help);",
    ),
    (
        "initialize_loading_screen",
        "void __thiscall initialize_loading_screen(LoadingBar* loading_bar);",
    ),
    (
        "destroy_loading_screen",
        "void __thiscall destroy_loading_screen(LoadingBar* loading_bar);",
    ),
    (
        "update_loading_screen",
        "void __thiscall update_loading_screen(LoadingBar* loading_bar);",
    ),
    (
        "destroy_options_menu",
        "void __thiscall destroy_options_menu(Options* options);",
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
        "SubLoc* __thiscall initialize_sub_loc(SubLoc* cell);",
    ),
    (
        "remove_sub_loc",
        "void __thiscall remove_sub_loc(SubLoc* cell);",
    ),
    (
        "update_sub_loc",
        "void __thiscall update_sub_loc(SubLoc* cell);",
    ),
    (
        "initialize_damage_gauge",
        "void __thiscall initialize_damage_gauge(DamageGuage* damage_guage);",
    ),
    (
        "update_damage_gauge",
        "void __thiscall update_damage_gauge(DamageGuage* damage_guage);",
    ),
    (
        "apply_damage_gauge_delta",
        "void __thiscall apply_damage_gauge_delta(DamageGuage* damage_guage, float delta, bool force);",
    ),
    (
        "get_track_cell_row_index",
        "int32_t __thiscall get_track_cell_row_index(SubLoc* cell);",
    ),
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(PathManager *manager, char *name);",
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
        "TextureRef* __thiscall get_or_create_texture_ref(TextureRefList* texture_list, char* texture_path, int32_t arg3, int16_t arg4);",
    ),
    (
        "allocate_path_template_samples",
        "void __fastcall allocate_path_template_samples(Path* self);",
    ),
    (
        "finalize_path_template",
        "void __fastcall finalize_path_template(Path* self);",
    ),
    (
        "mirror_path_template_pair_x",
        "void __thiscall mirror_path_template_pair_x(Path* self, Path* source);",
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
        "multiply_matrix",
        "void __thiscall multiply_matrix(TransformMatrix* matrix, const TransformMatrix* rhs);",
    ),
    (
        "multiply_matrix_in_place_forward_thunk",
        "void __thiscall multiply_matrix_in_place_forward_thunk(TransformMatrix* matrix, const TransformMatrix* rhs);",
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
        "void __thiscall compute_kind42_attachment_transform(Path* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle);",
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
        "char** __cdecl parse_next_space_delimited_token(char** cursor, char* out);",
    ),
    (
        "parse_next_float32",
        "double __cdecl parse_next_float32(char** cursor);",
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
        "int32_t __fastcall is_sub_loc_floor(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_slide",
        "int32_t __fastcall is_sub_loc_slide(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_ramp",
        "int32_t __fastcall is_sub_loc_ramp(TrackRowCell* cell);",
    ),
    (
        "is_sub_loc_empty",
        "int32_t __fastcall is_sub_loc_empty(TrackRowCell* cell);",
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
        "tColour* __thiscall get_track_skirt_color(SubgameRuntime* game, tColour* out);",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
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
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(Salt* salt);",
    ),
    (
        "initialize_score_stats",
        "void __thiscall initialize_score_stats(Squidge* squidge);",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(Squidge* squidge, float value);",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(Squidge* squidge, float value);",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(Squidge* squidge);",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkin* snail_skin);",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(Snail* snail);",
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
        "void __thiscall advance_frame_sequence(FrameSequence* sequence);",
    ),
    (
        "update_smtracks",
        "void __thiscall update_smtracks(SmtrackHeightfieldAnimator* animator);",
    ),
    (
        "sample_smtrack_heightmap",
        "void __cdecl sample_smtrack_heightmap(Object* source, float base, float scale, TextureRef* replacement, char cubic);",
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
        "void __thiscall kill_tip_widgets(Tip* tip);",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip",
        "void __thiscall update_tip(Tip* tip);",
    ),
    (
        "initialize_tip_manager",
        "void __thiscall initialize_tip_manager(TipManager* manager);",
    ),
    (
        "uninit_tips",
        "void __thiscall uninit_tips(TipManager* manager);",
    ),
    (
        "enqueue_tip_message",
        "Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button);",
    ),
    (
        "update_tip_manager",
        "void __thiscall update_tip_manager(TipManager* manager);",
    ),
    (
        "initialize_tutorial",
        "void __thiscall initialize_tutorial(Tutorial* tutorial);",
    ),
    (
        "uninit_tutorial",
        "void __thiscall uninit_tutorial(Tutorial* tutorial);",
    ),
    (
        "update_tutorial",
        "void __thiscall update_tutorial(Tutorial* tutorial);",
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
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player);",
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
        "play_movement_state_sound",
        "void __thiscall play_movement_state_sound(Player* player);",
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
        "clear_active_landscape_entries",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager);",
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
        "void __thiscall set_snail_weapon(Snail* snail, int32_t movement_flags);",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state);",
    ),
    (
        "initialize_cutscene",
        "void __thiscall initialize_cutscene(Snail* snail);",
    ),
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
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
        "void __thiscall update_progress_bar(ProgressBar* progress_bar);",
    ),
    (
        "initialize_nuke",
        "void __thiscall initialize_nuke(Nuke* nuke);",
    ),
    (
        "update_nuke",
        "void __thiscall update_nuke(Nuke* nuke);",
    ),
    (
        "uninit_nuke",
        "void __thiscall uninit_nuke(Nuke* nuke);",
    ),
    (
        "get_track_grid_cell_at_world_position",
        "TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "SubRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position);",
    ),
    (
        "spawn_track_health_pickup",
        "void __thiscall spawn_track_health_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
    ),
    (
        "spawn_track_jetpack_pickup",
        "void __thiscall spawn_track_jetpack_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "void __thiscall try_enter_track_attachment_from_swept_motion(Path* self, float world_x, float world_y, float world_z, float sweep_dx, float sweep_dy, float sweep_dz, TrackRowCell* source_cell);",
    ),
    (
        "begin_track_attachment_follow_state",
        "void __thiscall begin_track_attachment_follow_state(FollowState* follow_state, TrackRowCell* source_cell, const Vec3* world_position, Player* player);",
    ),
    (
        "update_track_attachment_follow_state",
        "int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion);",
    ),
    (
        "initialize_loopout_path_template_pair",
        "void __thiscall initialize_loopout_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_cage2_path_template_pair",
        "void __thiscall initialize_cage2_path_template_pair(Path* self, int32_t width_cells_, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_supertramp_path_template_pair",
        "int32_t __thiscall initialize_supertramp_path_template_pair(Path* self, float arg2, int32_t arg3, char* texture_a, char* texture_b, char* texture_c);",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "void __thiscall initialize_halfpipe_path_template_pair(Path* self, float scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_hump_path_template_pair",
        "void __thiscall initialize_hump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "void __thiscall initialize_looptheloop_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_looptheloopw_path_template_pair",
        "void __thiscall initialize_looptheloopw_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_dump_path_template_pair",
        "void __thiscall initialize_dump_path_template_pair(Path* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_dip_path_template_pair",
        "void __thiscall initialize_dip_path_template_pair(Path* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_screw_path_template_pair",
        "void __thiscall initialize_screw_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_slalom_path_template_pair",
        "void __thiscall initialize_slalom_path_template_pair(Path* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_worm_path_template_pair",
        "void __thiscall initialize_worm_path_template_pair(Path* self, char* texture_path);",
    ),
    (
        "initialize_slalombig_path_template_pair",
        "void __thiscall initialize_slalombig_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_sweep_path_template_pair",
        "void __thiscall initialize_sweep_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_snake_path_template_pair",
        "void __thiscall initialize_snake_path_template_pair(Path* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_slalomdouble_path_template_pair",
        "void __thiscall initialize_slalomdouble_path_template_pair(Path* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_p_path_template_pair",
        "void __thiscall initialize_p_path_template_pair(Path* self, int32_t variant, float scale_arg, int32_t width_cells_, float start_x, float end_x, int32_t curve_segments, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_start_path_template_pair",
        "void __thiscall initialize_start_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnover_path_template_pair",
        "void __thiscall initialize_turnover_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "void __thiscall initialize_turnoverdouble_path_template_pair(Path* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture);",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "void __thiscall initialize_turnunder_path_template_pair(Path* self, float turns, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_wibble_path_template_pair",
        "void __thiscall initialize_wibble_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_invert_path_template_pair",
        "void __thiscall initialize_invert_path_template_pair(Path* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_twister_path_template_pair",
        "void __thiscall initialize_twister_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_twister2_path_template_pair",
        "void __thiscall initialize_twister2_path_template_pair(Path* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "void __thiscall initialize_loopbow_path_template_pair(Path* self, float curve_scale, uint32_t width_cells_arg, char mode, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_toad_path_template_pair",
        "void __thiscall initialize_toad_path_template_pair(Path* self, char turn_left, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_hill_valley_path_template_pair",
        "int32_t __thiscall initialize_hill_valley_path_template_pair(Path* self, int32_t arg2, float arg3, float arg4, char arg5, char* texture_a, char* texture_b);",
    ),
    (
        "initialize_sbend_path_template_pair",
        "void __thiscall initialize_sbend_path_template_pair(Path* self, int32_t width_cells_, float height, float z_amplitude, char centered, char* texture_a, char* texture_b, char* vertical_texture);",
    ),
    (
        "initialize_subgame",
        "void __thiscall initialize_subgame(SubgameRuntime* game);",
    ),
    (
        "destroy_subgame",
        "void __thiscall destroy_subgame(SubgameRuntime* game);",
    ),
    (
        "update_subgame",
        "void __thiscall update_subgame(SubgameRuntime* game);",
    ),
    (
        "remove_subgame_bods",
        "void __thiscall remove_subgame_bods(SubgameRuntime* game);",
    ),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(SubgameRuntime* game);",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime* game);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);",
    ),
    (
        "place_parcels_on_track",
        "void __thiscall place_parcels_on_track(SubgameRuntime* game);",
    ),
    (
        "place_challenge_parcels_on_track",
        "void __thiscall place_challenge_parcels_on_track(SubgameRuntime* game);",
    ),
    (
        "mark_track_warning_zones",
        "void __thiscall mark_track_warning_zones(SubgameRuntime* game);",
    ),
    (
        "select_track_tile_edge_variants",
        "int32_t __thiscall select_track_tile_edge_variants(SubgameRuntime* game);",
    ),
    (
        "merge_track_tile_runs",
        "int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game);",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "int32_t __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime* game);",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "int32_t __thiscall harmonize_center_lane_floor_slide_variants(SubgameRuntime* game);",
    ),
    (
        "build_track_fringe_objects",
        "int32_t __thiscall build_track_fringe_objects(SubgameRuntime* game);",
    ),
    (
        "update_subgame_camera",
        "void __thiscall update_subgame_camera(SubgameRuntime* runtime);",
    ),
]


def _sync_build_track_render_cache_lvar() -> dict[str, object]:
    address = idc.get_name_ea_simple("build_track_render_caches")
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function"}

    cfunc = ida_hexrays.decompile(address)
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
        expected_type = _normalize_type_text(str(local_type))
        observed_type = _normalize_type_text(str(lvar.type()))
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
            and _normalize_type_text(str(candidate.type())) == update["expected_type"]
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


def _sync_populate_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "populate_runtime_track_cells_from_segments",
        POPULATE_RUNTIME_LVAR_SPECS,
    )


def _sync_place_parcels_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "place_parcels_on_track",
        PLACE_PARCELS_RUNTIME_LVAR_SPECS,
    )


def _sync_challenge_parcels_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "place_challenge_parcels_on_track",
        CHALLENGE_PARCELS_RUNTIME_LVAR_SPECS,
    )


def _sync_update_subgame_runtime_lvars() -> dict[str, object]:
    return _sync_exact_lvars(
        "update_subgame",
        UPDATE_SUBGAME_RUNTIME_LVAR_SPECS,
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
        "SubgameRuntime",
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_SubgameRuntime_type",
            "selector": selector,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(owner_type):
        return {
            "status": "failed",
            "reason": "create_SubgameRuntime_pointer_failed",
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
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=;)", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    missing = []
    failed = []

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

        if ida_funcs.get_func(address) is None:
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

    game_root_owner_graph = sync_game_root_owner_graph(require=True)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
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
    attachment_follow_root_offset_operands = _normalize_root_offset_operands(
        ATTACHMENT_FOLLOW_ROOT_OFFSET_OPERANDS
    )
    for result in attachment_follow_root_offset_operands:
        if result["status"] == "failed":
            failed.append(
                {
                    "selector": "update_track_attachment_follow_state",
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

    lvar_view = _sync_build_track_render_cache_lvar()
    if lvar_view.get("status") == "failed":
        failed.append({"selector": "build_track_render_caches", "lvar_view": lvar_view})
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
    update_subgame_runtime_lvars = _sync_update_subgame_runtime_lvars()
    if update_subgame_runtime_lvars.get("status") == "failed":
        failed.append(
            {
                "selector": "update_subgame",
                "runtime_lvars": update_subgame_runtime_lvars,
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
        if ida_funcs.get_func(address) is not None:
            ida_hexrays.mark_cfunc_dirty(address, True)
            dirty_functions.append(hex(address))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "game_root_owner_graph": game_root_owner_graph,
                "attachment_entry_root_offset_operands": attachment_entry_root_offset_operands,
                "attachment_follow_root_offset_operands": attachment_follow_root_offset_operands,
                "harmonize_root_offset_operands": harmonize_root_offset_operands,
                "fringe_runtime_row_offset_operands": fringe_runtime_row_offset_operands,
                "place_parcels_runtime_row_offset_operands": place_parcels_runtime_row_offset_operands,
                "challenge_parcels_runtime_row_offset_operands": challenge_parcels_runtime_row_offset_operands,
                "update_subgame_runtime_row_offset_operands": update_subgame_runtime_row_offset_operands,
                "lvar_view": lvar_view,
                "frontend_color_lvars": frontend_color_lvars,
                "update_sub_loc_color_lvars": update_sub_loc_color_lvars,
                "get_track_skirt_color_lvars": get_track_skirt_color_lvars,
                "populate_runtime_lvars": populate_runtime_lvars,
                "place_parcels_runtime_lvars": place_parcels_runtime_lvars,
                "challenge_parcels_runtime_lvars": challenge_parcels_runtime_lvars,
                "update_subgame_runtime_lvars": update_subgame_runtime_lvars,
                "remove_subgame_bods_cursor_lvars": remove_subgame_bods_cursor_lvars,
                "spawn_track_ring_lvars": spawn_track_ring_lvars,
                "collision_pool_cursor_lvars": collision_pool_cursor_lvars,
                "merge_runtime_lvars": merge_runtime_lvars,
                "fringe_runtime_lvars": fringe_runtime_lvars,
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
        print("usage: apply_path_template_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    if not header_path.is_file():
        print(f"missing header: {header_path}", file=sys.stderr)
        ida_pro.qexit(2)
        return

    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
