#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_instruction_comment_updates,
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_and_proto_updates,
    apply_struct_field_updates,
    apply_split_user_var_update,
    apply_symbol_updates,
    apply_user_var_updates,
    current_header_type_equivalence,
    current_prototypes,
    current_type_widths,
    emit_summary,
    normalize_prototype,
    reanalyze_functions,
    remove_user_var_updates,
    run_bn,
    struct_exists,
    types_declare_if_missing,
    types_declare_missing_only,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

BOD_CORE_SYMBOL_UPDATES = (
    ("0x4113b0", "add_bod_to_front"),
    ("0x411420", "append_bod_to_end"),
    ("0x42f5c0", "is_bod_after_sprites"),
    ("0x42f5d0", "set_bod_object"),
    ("0x42f5f0", "initialize_bod_base"),
    ("0x42f650", "initialize_renderable_bod"),
    ("0x42f680", "apply_bod_position"),
    ("0x447290", "recycle_bod_to_free_list"),
    ("0x4974fc", "g_bod_base_vtable"),
    ("0x497500", "g_renderable_bod_vtable"),
    ("0x50331c", "g_bod_base_init_count"),
)

BOD_CORE_OWNER_SIZES = {
    "BodNode": 0x10,
    "BodList": 0x0C,
    "BodBase": 0x38,
    "RenderableBod": 0x80,
}

FRINGE_SYMBOL_UPDATES = (
    ("0x408650", "initialize_fringe_object"),
    ("0x439b00", "refresh_fringe_object_draw_list"),
    ("0x447090", "initialize_fringe_manager"),
    ("0x4470a0", "allocate_fringe_object"),
    ("0x497344", "g_fringe_vtable"),
)

FRINGE_OWNER_SIZES = {
    "Fringe": 0x38,
    "FringeManager": 0x5FB44,
}

NUKE_OWNER_SIZES = {
    "Nuke": 0x7C,
}

TIP_OWNER_SIZES = {
    "TipData": 0x14,
    "Tip": 0x20,
    "TipManager": 0x98,
}

AUTHORED_ROW_CURSOR_SIZES = {
    "AuthoredSegmentRow": 0x38,
    "AuthoredSegmentRowPositionCursorView": 0x38,
}

FRINGE_MESH_CURSOR_SIZES = {
    "FringeVertexRowCursorView": 0x30,
    "FringeFaceQuadPairCursorView": 0x60,
}

RUNTIME_GRID_CLEAR_CURSOR_SIZES = {
    "cRSubLoc": 0x54,
    "TrackRowCellLaneAndFlagsStrideCursor": 0x54,
    "TrackRowCellFringeFrontStrideCursor": 0x54,
    "SubRow": 0xF4,
    "SubRowParcelSpawnYStrideCursor": 0xF4,
}

PRESENTATION_ANIMATION_CURSOR_SIZES = {
    "PresentationAnimationSlot": 0x80,
    "PresentationAnimationObjectStrideCursor": 0x80,
}

GOLB_SHOT_ASSET_CURSOR_SIZES = {
    "GolbShot": 0x2E8,
    "GolbShotVapourObjectStrideCursor": 0x2E8,
}

SUB_LAZER_ASSET_CURSOR_SIZES = {
    "SubLazer": 0xB0,
    "SubLazerBodyObjectStrideCursor": 0xB0,
}

SALT_ASSET_CURSOR_SIZES = {
    "Salt": 0x98,
    "SaltOwnerGameStrideCursor": 0x98,
}

TIP_FUNCTION_SYMBOL_UPDATES = (
    ("0x4489e0", "kill_tip_widgets"),
    ("0x448a40", "initialize_tip"),
    ("0x448c40", "update_tip"),
    ("0x448cf0", "initialize_tip_manager"),
    ("0x448d10", "uninit_tips"),
    ("0x448d30", "enqueue_tip_message"),
    ("0x448d80", "update_tip_manager"),
)

TIP_DATA_SYMBOL_UPDATES = (
    ("0x4ac5c8", "g_default_tip_message"),
)

TRACK_RENDER_CACHE_SYMBOL_UPDATES = (
    ("0x4085e0", "initialize_active_bod"),
    ("0x433e80", "update_active_bod"),
    ("0x497338", "g_active_bod_vtable"),
)

GOLB_PATH_FOLLOW_SYMBOL_UPDATES = (
    ("0x421770", "initialize_path_follow_golb"),
    ("0x4217b0", "traverse_path_follow_golb"),
)

PATH_FUNCTION_SYMBOL_UPDATES = (
    ("0x41b0a0", "get_path_nodes"),
    ("0x421dc0", "mirror_path"),
    ("0x42c600", "calc_path_length_z"),
)

SYMBOL_UPDATES = (
    ("0x408040", "initialize_noop_renderable_bod"),
    ("0x408060", "initialize_runtime_pools_and_path_template_bank"),
    ("0x4084b0", "initialize_track_speedup_runtime"),
    ("0x4084d0", "initialize_track_jetpack_pickup_runtime"),
    ("0x408510", "initialize_track_health_pickup_runtime"),
    ("0x408590", "initialize_track_row_runtime"),
    *BOD_CORE_SYMBOL_UPDATES,
    *TRACK_RENDER_CACHE_SYMBOL_UPDATES,
    *FRINGE_SYMBOL_UPDATES,
    *GOLB_PATH_FOLLOW_SYMBOL_UPDATES,
    *PATH_FUNCTION_SYMBOL_UPDATES,
    ("0x42f6e0", "initialize_object_constructor_thunk"),
    ("0x442500", "initialize_vapour"),
    ("0x442540", "reset_vapour"),
    ("0x442560", "add_vapour_point"),
    ("0x4425f0", "update_vapour"),
    ("0x4182e0", "reset_landscape_manager"),
    ("0x4182f0", "load_landscape_script_by_name"),
    ("0x433fd0", "initialize_thanks_for_playing_screen"),
    ("0x4340c0", "uninit_thanks_screen"),
    ("0x4340f0", "update_thanks_for_playing_screen"),
    ("0x434b60", "is_neighbor_cell_solid"),
    ("0x4972b0", "g_noop_runtime_callback_table"),
    ("0x4972f8", "g_face_callback_table"),
    ("0x497314", "g_sub_speed_up_vtable"),
    ("0x497318", "g_jet_pack_vtable"),
    ("0x49731c", "g_vapour_vtable"),
    ("0x497320", "g_sub_health_vtable"),
    ("0x497330", "g_row_model_vtable"),
    ("0x44c870", "initialize_global_identity_matrix_thunk"),
    ("0x44c880", "initialize_global_identity_matrix"),
    ("0x44cac0", "multiply_vector_by_matrix_copy"),
    ("0x44cb50", "dot_vectors"),
    ("0x44cb70", "dot_vector"),
    ("0x44cb90", "multiply_vector_by_matrix"),
    ("0x44cc20", "rotate_vector_by_matrix"),
    ("0x44cca0", "normalize_vector"),
    ("0x44ccf0", "vector_magnitude"),
    ("0x44cd20", "normalize_vector_from_source"),
    ("0x44cd40", "cross_vectors"),
    ("0x44cde0", "initialize_uniform_scale_matrix"),
    ("0x44ce30", "rotate_matrix_local_x"),
    ("0x44cec0", "rotate_matrix_local_y"),
    ("0x44cf50", "rotate_matrix_local_z"),
    ("0x44cfe0", "initialize_matrix_from_values"),
    ("0x44d060", "multiply_matrices"),
    ("0x44d1a0", "multiply_matrix_assign"),
    ("0x44d1d0", "multiply_matrix"),
    ("0x44d1e0", "premultiply_matrix_in_place"),
    ("0x44d530", "initialize_quaternion_from_axis"),
    ("0x44d580", "initialize_axis_from_quaternion"),
    ("0x44d5d0", "initialize_quaternion_from_matrix"),
    ("0x44d820", "initialize_matrix_from_quaternion"),
    ("0x44d920", "interpolate_matrix_rotation"),
    ("0x44dbd0", "set_color_rgb"),
    ("0x42b9c0", "get_path_position_at_node"),
    ("0x42ca90", "is_point_inside_track_attachment"),
    ("0x4086d0", "initialize_player_presentation_controller"),
    ("0x43a010", "health_collect_particles"),
    ("0x43a1a0", "set_subgoldy_shoot_flags"),
    ("0x43a300", "shoot_subgoldy"),
    ("0x43a370", "end_jetpack_hover"),
    ("0x43a390", "update_jetpack_gauge"),
    ("0x43a580", "uninit_jet_particles"),
    ("0x43a5b0", "initialize_jet_particles"),
    ("0x43a690", "update_jet_particles"),
    ("0x43a930", "initialize_jetpack_gauge"),
    ("0x43a980", "arm_jetpack_gauge"),
    ("0x43a9c0", "initialize_subgoldy"),
    ("0x43af10", "show_subgoldy_lives"),
    ("0x43af60", "begin_post_follow_carryover"),
    ("0x43afd0", "play_subgoldy_shoot_sfx"),
    ("0x43b120", "update_subgoldy"),
    ("0x43d230", "initialize_subgoldy_ghost"),
    ("0x43d3d0", "set_subgoldy_ghost_z"),
    ("0x437e80", "calc_slider_to_rate"),
    ("0x43d410", "get_track_grid_cell_at_world_position"),
    ("0x43d480", "get_track_runtime_cell_at_world_z"),
    ("0x43d4d0", "sample_track_floor_height_at_position"),
    ("0x4403a0", "clear_subgoldy_score_buckets"),
    ("0x4404d0", "calc_subgame_rate"),
    ("0x4408a0", "advance_blink_random"),
    ("0x4408c0", "initialize_blink_random"),
    ("0x4428d0", "update_snail_presentation"),
    ("0x442e40", "release_snail_weapons"),
    ("0x444600", "dispatch_cutscene_animation"),
    ("0x4446e0", "set_weapon_animation"),
    ("0x444960", "initialize_squidge"),
    ("0x445840", "kill_subgoldy"),
    ("0x445f10", "hide_gameplay_scores"),
    ("0x445f40", "unhide_gameplay_scores"),
    ("0x445cd0", "build_snail_world_hotspots"),
    ("0x445d50", "extract_snail_local_hotspots"),
    ("0x4ac5c8", "g_default_tip_message"),
    ("0x497354", "g_player_presentation_noop_vtable"),
    ("0x497358", "g_invincible_shell_update_vtable"),
    ("0x49735c", "g_weapon_noop_vtable"),
    ("0x643190", "g_subgoldy_ghost_z"),
    ("0x643194", "g_replay_accum_z"),
)

SNAIL_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "previous_live_matrix", "TransformMatrix"),
    ("0xc0", "cached_cutscene_matrix", "TransformMatrix"),
    ("0x100", "owner_player", "Player*"),
    ("0x104", "anim_manager", "AnimManager"),
    ("0x14c", "cutscene_animation_slots", "PresentationAnimationSlot[0xa]"),
    ("0x64c", "weapon_channels", "Weapon[0x3]"),
    ("0x11e0", "jetpack_channel", "Weapon"),
    ("0x15bc", "wobble", "PresentationWobbleController"),
    ("0x15cc", "snail_hotspot_source_body", "RenderableBod"),
    ("0x164c", "snail_hotspot_body", "RenderableBod"),
    ("0x1894", "invincible_shell", "Invincible"),
    ("0x192c", "cutscene_roll_progress", "float"),
    ("0x1930", "cutscene_roll_step", "float"),
    ("0x1934", "channel_release_steps_active", "uint8_t"),
    ("0x1938", "snail_skin", "SnailSkin"),
    ("0x1958", "cutscene", "CutScene"),
)

PRESENTATION_WOBBLE_CONTROLLER_FIELD_UPDATES = (
    ("0x00", "roll_phase", "float"),
    ("0x04", "roll_phase_step", "float"),
    ("0x08", "lift_phase", "float"),
    ("0x0c", "lift_phase_step", "float"),
)

WEAPON_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x104", "selected_state", "int32_t"),
    ("0x108", "anim_manager", "AnimManager"),
    ("0x150", "animation_slots", "PresentationAnimationSlot[0x5]"),
)

ANIM_MANAGER_FIELD_UPDATES = (
    ("0x00", "state", "int32_t"),
    ("0x04", "progress", "float"),
    ("0x08", "progress_step", "float"),
    ("0x0c", "active_animation", "ObjectAnimation*"),
    ("0x10", "completed", "uint8_t"),
    ("0x14", "queued_animations", "int32_t[0xa]"),
    ("0x3c", "queue_count", "int32_t"),
    ("0x40", "target_model", "RenderableBod*"),
    ("0x44", "animation_slots", "PresentationAnimationSlot*"),
)

INVINCIBLE_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "state", "InvincibleState"),
    ("0x84", "spin_phase", "float"),
    ("0x88", "spin_phase_step", "float"),
    ("0x8c", "fade_progress", "float"),
    ("0x90", "fade_step", "float"),
)

RENDERABLE_BOD_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "transform", "TransformMatrix"),
    ("0x78", "render_animation_manager", "AnimManager*"),
    ("0x7c", "frame_number", "int32_t"),
)

BOD_NODE_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x04", "list_flags", "uint32_t"),
    ("0x08", "list_prev", "BodNode*"),
    ("0x0c", "list_next", "BodNode*"),
)

BOD_LIST_FIELD_UPDATES = (
    ("0x00", "unknown_00", "int32_t"),
    ("0x04", "first", "BodNode*"),
    ("0x08", "free_top", "BodNode*"),
)

TRACK_RENDER_CACHE_SLOT_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "cache_row_base", "float"),
)

ACTIVE_LANDSCAPE_ENTRY_FIELD_UPDATES = (
    ("0x00", "bod", "RenderableBod"),
    ("0x80", "state", "int32_t"),
    ("0x88", "repeat_z_span", "float"),
    ("0x8c", "reference_bod", "RenderableBod*"),
)

FACE_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "movie", "Movie"),
)

CUT_SCENE_FIELD_UPDATES = (
    ("0x00", "presentation", "Snail*"),
    ("0x04", "player", "Player*"),
    ("0x08", "camera_mode", "int32_t"),
    ("0x0c", "state", "CutSceneState"),
    ("0x10", "live_matrix", "TransformMatrix"),
    ("0x50", "progress", "float"),
    ("0x54", "progress_step", "float"),
    ("0x58", "force_camera_update", "uint8_t"),
)

CAMERAMAN_FIELD_UPDATES = (
    ("0xcc", "force_camera_update", "uint8_t"),
)

SNAIL_SKIN_FIELD_UPDATES = (
    ("0x00", "selected_slot", "int32_t"),
    ("0x04", "material_overrides", "TextureRef*[0x3]"),
    ("0x10", "owner_snail", "Snail*"),
    ("0x14", "active", "int32_t"),
    ("0x18", "progress", "float"),
    ("0x1c", "progress_step", "float"),
)

GOLB_PATH_FOLLOW_STATE_FIELD_UPDATES = (
    ("0x00", "active", "uint8_t"),
    ("0x04", "template_record", "cRPath*"),
    ("0x08", "source_cell", "cRSubLoc*"),
    ("0x0c", "sample_index", "int32_t"),
    ("0x10", "progress", "float"),
    ("0x14", "vertical_offset", "float"),
    ("0x18", "output_position", "Vec3"),
    ("0x24", "shot", "GolbShot*"),
)

GOLB_PATH_FOLLOW_STATE_DECLARATION = """
typedef struct GolbPathFollowState {
    uint8_t active;
    uint8_t _pad_01[0x3];
    cRPath* template_record;
    cRSubLoc* source_cell;
    int32_t sample_index;
    float progress;
    float vertical_offset;
    Vec3 output_position;
    GolbShot* shot;
} GolbPathFollowState;
""".strip()

GOLB_SHOT_FIELD_UPDATES = (
    # GolbShot's zero-offset RenderableBod is an inherited cRBodPos base, not
    # a separately owned child. The constructor then seeds presentation
    # children at +0x080 and +0x118. The middle owner is the complete
    # 0x94-byte Vapour; the old +0x150 live_matrix alias is
    # tertiary_body.transform.
    ("0x080", "vapour", "Vapour"),
    ("0x114", "vapour_owner_shot", "GolbShot*"),
    ("0x118", "tertiary_body", "cRGolbRocket"),
    ("0x198", "homing_target_object", "ContactTargetObject*"),
    ("0x19c", "homing_target", "Vec3"),
    ("0x1a8", "rocket_owner_shot", "GolbShot*"),
    ("0x1ac", "homing_blend", "float"),
    ("0x1b0", "homing_blend_step", "float"),
    ("0x1b4", "spin", "float"),
    ("0x1b8", "spin_step", "float"),
    ("0x1bc", "skip_one_tick", "uint8_t"),
    ("0x1bd", "slug_bounce_armed", "uint8_t"),
    ("0x1c0", "kind", "int32_t"),
    ("0x1c4", "flight_transform", "TransformMatrix"),
    ("0x204", "previous_flight_transform", "TransformMatrix"),
    ("0x244", "state", "int32_t"),
    ("0x248", "render_sprite", "Sprite*"),
    ("0x24c", "velocity", "Vec3"),
    ("0x258", "direction", "Vec3"),
    ("0x264", "path_factor", "float"),
    ("0x268", "lifetime", "float"),
    ("0x26c", "lifetime_step", "float"),
    ("0x270", "game", "cRSubGame*"),
    ("0x274", "object_ref", "void*"),
    ("0x278", "owner_player", "Player*"),
    ("0x27c", "source_matrix", "TransformMatrix"),
    ("0x2bc", "path_follow", "GolbPathFollowState"),
    ("0x2e4", "path_entry_z_latch", "float"),
)

GOLB_AUTHORED_TYPE_NAMES = (
    "GolbShot",
    "cRSubGolb",
    "cRPathFollowGolb",
)

PATH_MANAGER_FIELD_UPDATES = (
    ("0x00", "_empty", "uint8_t"),
)

PATH_MANAGER_OWNER_TYPE_NAMES = (
    "cRPathManager",
    "PathManager",
)

PATH_MANAGER_PROTO_UPDATES = (
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(cRPathManager* manager, char* name)",
    ),
)

PATH_OWNER_TYPE_NAMES = (
    "cRPath",
    "Path",
    "PathPair",
)

PATH_PAIR_FIELD_UPDATES = (
    ("0x00", "primary", "cRPath"),
    ("0xa8", "secondary", "cRPath"),
)

SUB_LOC_OWNER_TYPE_NAMES = (
    "cRSubLoc",
    "SubLoc",
    "TrackRowCell",
)

SUBGAME_OWNER_TYPE_NAMES = (
    "cRSubGame",
    "SubgameRuntime",
)

SUB_LOC_DEPENDENT_VIEW_TYPE_NAMES = (
    "TrackRowCellSameLaneCursorView",
    "SubRowParcelSpawnYStrideCursor",
    "RuntimeCellStrideAnchor",
)

REQUIRED_HEADER_STRUCTS = (
    "cRPathManager",
    "FrontendWidgetFlag",
    "TextureRefFlags",
    "Twinkle",
    "TwinkleManager",
    "InputOkState",
    "BarrierActor",
    "ActiveLandscapeEntry",
    "LandscapeManager",
    "GUI",
    "Help",
    "ThanksScreen",
    "GalaxyPoint",
    "Galaxy",
    "EnemyManager",
    "RuntimeRateOrLevelArg",
    "SubgameRuntimeFlag",
    "SubgameRuntimeFlagPreset",
    "SubRingState",
    "SubRingKind",
    "SubSlugState",
    "SubSlugDeathTossDirection",
    "Slug",
    "SlugStateStrideCursor",
    "SaltStateStrideCursor",
    "SubRingSlotCursor",
    "JetPackSlotCursor",
    "SubHealthSlotCursor",
    "SubGarbageSlotCursor",
    "SlugSlotCursor",
    "SubLazerSlotCursor",
    "SaltSlotCursor",
    "ParcelSlotCursor",
    "cRSubGame",
    "SubgameRuntime",
    "SubHighScore",
    "SubSolution",
    "TimeTrialRouteRecordCursor",
    "CompactHighScoreRecord",
    "SubTracks",
    "SlugVoiceManager",
    "TimeTrial",
    "SnailVisual",
    "BodNode",
    "BodList",
    "BodBase",
    "Banner",
    "BannerInitStrideView",
    "Vapour",
    "TrackPickupState",
    "SubLazerState",
    "SaltState",
    "SubGarbageState",
    "SubGarbageCollisionSide",
    "JetPack",
    "ParcelState",
    "CompletionState",
    "TimesUpState",
    "AxisAngle",
    "Quaternion",
    "RenderableBod",
    "TrackRenderCacheSlot",
    "Fringe",
    "FringeManager",
    "cRSMTracks",
    "Movie",
    "Face",
    "AuthoredSegmentRowFlag",
    "AuthoredSegmentRowPositionCursorView",
    "FringeVertexRowCursorView",
    "FringeFaceQuadPairCursorView",
    "SubSegment",
    "SubSegmentParcelScanAnchor",
    "SubSegmentRowStrideAnchor",
    "SubSegmentEventBiasView",
    "SubLocOpenEdgeFlag",
    "SubLocTileId",
    "SubLocFlag",
    "cRSubLoc",
    "TrackRowCellLaneAndFlagsStrideCursor",
    "TrackRowCellFringeFrontStrideCursor",
    "TrackRowCellSameLaneCursorView",
    "SubRowFlag",
    "RowModel",
    "SubRow",
    "SubRowParcelSpawnYStrideCursor",
    "RuntimeRowStrideAnchor",
    "RuntimeCellStrideAnchor",
    "cRPath",
    "Path",
    "PathPair",
    "cRPathFollowGoldy",
    "DamageGuageState",
    "DamageGuage",
    "ProgressBar",
    "WarningState",
    "Warning",
    "SubPause",
    "NukeState",
    "Nuke",
    "FireWork",
    "ClickStartState",
    "ClickStart",
    "Cameraman",
    "cRCameraman",
    "Squidge",
    "InvincibleState",
    "Invincible",
    "SnailSkin",
    "Snail",
    "CutSceneState",
    "CutScene",
    "PresentationWobbleController",
    "ObjectAnimation",
    "PresentationAnimationSlot",
    "PresentationAnimationObjectStrideCursor",
    "AnimManager",
    "Weapon",
    "GolbShot",
    "GolbShotVapourObjectStrideCursor",
    "SubLazerBodyObjectStrideCursor",
    "SaltOwnerGameStrideCursor",
    "Player",
    "JetParticleSlot",
    "SubHoverState",
    "SubHover",
    "TipData",
    "Tip",
    "TipManager",
    "Tutorial",
)


def ensure_path_analysis_views(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Replace mutable views and recovered inline owners when their shape changes."""
    type_names = (
        "TimeTrialCourseRecord",
        "TimeTrial",
        "PresentationWobbleController",
        "PresentationAnimationObjectStrideCursor",
        "PathTemplateSamplePairCursorView",
        "SnailHotspotLocalZCursorView",
        "ObjectFaceQuadTextureCursorView",
        "GolbShotVapourObjectStrideCursor",
        "SubLazerBodyObjectStrideCursor",
        "SaltOwnerGameStrideCursor",
        "RuntimeCellStrideAnchor",
        "TrackRowCellSameLaneCursorView",
        "TrackRowCellLaneAndFlagsStrideCursor",
        "TrackRowCellFringeFrontStrideCursor",
        "SubRowParcelSpawnYStrideCursor",
        "AuthoredSegmentRowPositionCursorView",
        "FringeVertexRowCursorView",
        "FringeFaceQuadPairCursorView",
        "SubSegmentParcelScanAnchor",
        "SubSegmentEventBiasView",
        "SubLocTileId",
        "SubSlugState",
        "SubSlugDeathTossDirection",
        "SaltStateStrideCursor",
        "SubLazerState",
        "SaltState",
        "SubGarbageState",
        "SubGarbageCollisionSide",
    )
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
            "reason": "mutable path analysis views already match the header",
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


def verify_bod_core_owner_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before applying method ABIs to incompatible BOD owners."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=BOD_CORE_OWNER_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in BOD_CORE_OWNER_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"BOD core owner size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_sizes": observed,
    }


def verify_fringe_owner_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before applying method ABIs to incompatible Fringe owners."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=FRINGE_OWNER_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in FRINGE_OWNER_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"Fringe owner size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "fringe",
        "owner_sizes": observed,
    }


def verify_nuke_owner_size(*, target: str) -> dict[str, object]:
    """Fail closed before applying the cRNuke lifecycle ABIs."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=NUKE_OWNER_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in NUKE_OWNER_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"Nuke owner size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "nuke",
        "owner_sizes": observed,
    }


def verify_tip_owner_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before applying the cRTip and cRTipManager ABIs."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=TIP_OWNER_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in TIP_OWNER_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"Tip owner size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "tip",
        "owner_sizes": observed,
    }


def verify_authored_row_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before applying the field-first authored-row cursor."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=AUTHORED_ROW_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in AUTHORED_ROW_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"authored row cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "authored_row_cursor",
        "owner_sizes": observed,
    }


def verify_fringe_mesh_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the borrowed fringe row and face cursors."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=FRINGE_MESH_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in FRINGE_MESH_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"fringe mesh cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "fringe_mesh_cursor",
        "owner_sizes": observed,
    }


def verify_runtime_grid_clear_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the borrowed runtime-grid clear cursors."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=RUNTIME_GRID_CLEAR_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in RUNTIME_GRID_CLEAR_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"runtime-grid clear cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "runtime_grid_clear_cursor",
        "owner_sizes": observed,
    }


def verify_presentation_animation_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the animation-object field cursors."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=PRESENTATION_ANIMATION_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in PRESENTATION_ANIMATION_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"presentation animation cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "presentation_animation_cursor",
        "owner_sizes": observed,
    }


def verify_golb_shot_asset_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the GolbShot vapour-object cursor."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=GOLB_SHOT_ASSET_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in GOLB_SHOT_ASSET_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"GolbShot asset cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "golb_shot_asset_cursor",
        "owner_sizes": observed,
    }


def verify_sub_lazer_asset_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the SubLazer body-object cursor."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=SUB_LAZER_ASSET_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in SUB_LAZER_ASSET_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"SubLazer asset cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "sub_lazer_asset_cursor",
        "owner_sizes": observed,
    }


def verify_salt_asset_cursor_sizes(*, target: str) -> dict[str, object]:
    """Fail closed before replaying the Salt owner-game field cursor."""
    observed = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=SALT_ASSET_CURSOR_SIZES,
    )
    failures = {
        name: {"expected": expected, "observed": observed.get(name)}
        for name, expected in SALT_ASSET_CURSOR_SIZES.items()
        if observed.get(name) != expected
    }
    if failures:
        raise RuntimeError(f"Salt asset cursor size mismatch: {failures}")
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_group": "salt_asset_cursor",
        "owner_sizes": observed,
    }


SUB_PAUSE_FIELD_UPDATES = (
    ("0x00", "options_widget", "FrontendWidget*"),
    ("0x04", "end_game_widget", "FrontendWidget*"),
    ("0x08", "resume_widget", "FrontendWidget*"),
)

PLAYER_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "resurrect_final_loss", "int32_t"),
    ("0x84", "resurrect_active", "int32_t"),
    ("0x8c", "resurrect_progress", "float"),
    ("0x90", "resurrect_progress_step", "float"),
    ("0x98", "ghost_sprite_a", "Sprite*"),
    ("0x9c", "ghost_sprite_b", "Sprite*"),
    ("0xa0", "click_start", "ClickStart"),
    ("0x14c", "row_event_cutscene_started", "uint8_t"),
    ("0x150", "nuke", "Nuke"),
    ("0x1cc", "shoot_sfx_variant_sample", "int32_t"),
    ("0x1d0", "firework", "FireWork"),
    ("0x1d4", "damage_retrigger_timer", "float"),
    ("0x1d8", "damage_retrigger_step", "float"),
    ("0x1dc", "surface_reaction_timer", "float"),
    ("0x1e0", "surface_reaction_step", "float"),
    ("0x1e4", "trampoline_bounce_active", "uint8_t"),
    ("0x1e8", "row_event", "PlayerRowEventState"),
    ("0x200", "cameraman", "Cameraman"),
    ("0x2d8", "control_override_active", "uint8_t"),
    ("0x2dc", "cutscene_pitch_cycle", "float"),
    ("0x2e0", "cutscene_pitch_cycle_step", "float"),
    ("0x2e4", "total_score", "int32_t"),
    ("0x2e8", "stopwatch", "Time"),
    ("0x300", "score_tail", "int32_t"),
    ("0x304", "replay_start_cursor", "int32_t"),
    ("0x308", "shooting_tier", "int32_t"),
    ("0x310", "score_buckets", "int32_t[0x6]"),
    ("0x338", "shoot_flags", "uint32_t"),
    ("0x33c", "previous_shoot_flags", "uint32_t"),
    ("0x328", "barrier_hold_progress", "float"),
    ("0x32c", "barrier_hold_step", "float"),
    ("0x330", "startup_voice_timer", "float"),
    ("0x334", "startup_voice_step", "float"),
    ("0x350", "lane_lean_state", "int32_t"),
    ("0x354", "lane_lean_amplitude", "float"),
    ("0x358", "lane_lean_progress", "float"),
    ("0x35c", "lane_lean_progress_step", "float"),
    ("0x360", "timer_360_state", "int32_t"),
    ("0x364", "timer_360_amplitude", "float"),
    ("0x368", "timer_360_progress", "float"),
    ("0x36c", "timer_360_step", "float"),
    ("0x370", "heading_roll", "float"),
    ("0x374", "nuke_effect_progress", "float"),
    ("0x378", "nuke_effect_progress_step", "float"),
    ("0x37c", "last_ring_spawn_z", "float"),
    ("0x380", "player_slot", "int32_t"),
    ("0x384", "follow_state", "cRPathFollowGoldy"),
    ("0x3c4", "damage_gauge", "DamageGuage"),
    ("0x3f0", "progress_bar", "ProgressBar"),
    ("0x3f4", "warning", "Warning"),
    ("0x404", "lives", "int32_t"),
    ("0x408", "game", "cRSubGame*"),
    ("0x40c", "movement_mode_selector", "int32_t"),
    ("0x410", "velocity", "Vec3"),
    ("0x41c", "boost_one_tick", "uint8_t"),
    ("0x41d", "attachment_exit_pending", "uint8_t"),
    ("0x420", "_pad_420", "uint8_t[0x4]"),
    ("0x424", "attachment_exit_anchor_z", "float"),
    ("0x42c", "post_follow_exit_roll", "float"),
    ("0x430", "post_follow_heading_carryover", "int32_t"),
    ("0x434", "attachment_exit_progress", "float"),
    ("0x438", "attachment_exit_progress_step", "float"),
    ("0x43c", "control_source", "PlayerControlSource*"),
    ("0x440", "completion_handoff_active", "uint8_t"),
    ("0x444", "completion_handoff_timer", "float"),
    ("0x448", "completion_handoff_timer_step", "float"),
    ("0x44c", "attachment_exit_gate_a", "uint8_t"),
    ("0x44d", "attachment_exit_gate_b", "uint8_t"),
    ("0x44e", "completion_handoff_voice_gate", "uint8_t"),
    ("0x450", "golb_shots", "GolbShot[0xc]"),
    ("0x435c", "slow_commentary_timer", "float"),
    ("0x4360", "slow_commentary_step", "float"),
    ("0x2730", "shoot_cooldown_progress", "float"),
    ("0x2734", "shoot_cooldown_step", "float"),
    ("0x2738", "slide_extension_threshold_z", "float"),
    ("0x273c", "track_z_offset", "float"),
    ("0x2740", "track_z_anchor", "float"),
    ("0x2744", "completion_handoff_cycle_progress", "float"),
    ("0x2748", "completion_handoff_cycle_step", "float"),
    ("0x274c", "unused_274c", "int32_t"),
    ("0x2750", "sub_hover", "SubHover"),
    ("0x2964", "cached_camera_target_world", "Vec3"),
    ("0x2970", "steering_mode_selector", "int32_t"),
    ("0x2980", "interaction_max_z", "float"),
    ("0x2984", "presentation", "Snail"),
    ("0x4338", "parcels_collected", "int32_t"),
    ("0x4340", "visible_life_stock", "int32_t"),
    ("0x4344", "squidge", "Squidge"),
)

# The row-event ID and the direct message probe share EAX at different native
# definitions. Split the later game-base definition before typing it: applying
# a pointer type to the merged lifetime would falsely turn row_event_id into an
# owner pointer. The resulting one-based view is a borrowed alias of
# level_definition.segment_slots[event_id - 1].
UPDATE_SUBGOLDY_EVENT_VIEW_SPLIT_DEFINITIONS = (
    ("0x43b752", "mlil", "RegisterVariableSourceType", 1586, 66),
)

UPDATE_SUBGOLDY_EVENT_VIEW_TARGET_VAR = (
    "RegisterVariableSourceType",
    1586,
    66,
)

# The remaining message, duration, and sample loads each receive their own
# short-lived copy of Player.game. Typing only those exact definitions keeps
# the scalar stride arithmetic honest while recovering the shared SubSegment
# owner in HLIL.
UPDATE_SUBGOLDY_USER_VAR_UPDATES = (
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1520,
        66,
        "row_event_id",
        "int32_t",
    ),
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1628,
        68,
        "message_segment_view",
        "SubSegmentEventBiasView*",
    ),
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1688,
        68,
        "duration_segment_view",
        "SubSegmentEventBiasView*",
    ),
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1794,
        68,
        "sample_segment_view",
        "SubSegmentEventBiasView*",
    ),
)

# The time-trial ghost path preserves the native
# `game + route_index * sizeof(SubSolution)` expression in EAX. This exact
# lifetime borrows one SubHighScore::time_trial_route_records element through
# a cRSubGame-relative analytical view; it does not own another record.
UPDATE_SUBGOLDY_REPLAY_USER_VAR_UPDATES = (
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        7143,
        66,
        "time_trial_route_cursor",
        "TimeTrialRouteRecordCursor*",
    ),
)

# initialize_subgoldy walks the 12 Player-owned GolbShot records from each
# shot's flight_transform field. The exact EDI MLIL identity is a borrowed
# field-stride cursor, not a replacement owner for Player.golb_shots.
INITIALIZE_SUBGOLDY_USER_VAR_UPDATES = (
    (
        "initialize_subgoldy",
        "RegisterVariableSourceType",
        1171,
        73,
        "golb_shot_flight_cursor",
        "GolbShotFlightStrideCursor*",
    ),
)

# The emitter search borrows one GolbShot at a time from Player.golb_shots.
# Fixing the exact EDI lifetime prevents HLIL from widening it to a pointer to
# the entire 12-element array and inventing a compensating owner subtraction.
MOVEMENT_FLAG_EMITTER_USER_VAR_UPDATES = (
    (
        "shoot_subgoldy",
        "RegisterVariableSourceType",
        49,
        73,
        "golb_shot_cursor",
        "GolbShot*",
    ),
)

# EAX first carries Banner::visibility_mode and later the inherited BOD flags.
# Keep the second SSA owner unsigned so Player* flow through ECX cannot taint
# the independent bitfield update in HLIL.
UPDATE_BANNER_USER_VAR_UPDATES = (
    (
        "update_banner",
        "RegisterVariableSourceType",
        11,
        66,
        "list_flags",
        "uint32_t",
    ),
)

# The startup loop carries a GameRoot-relative pointer biased before the
# embedded Banner, then advances it by one exact 0x60-byte Banner stride. Keep
# that physical view explicit instead of falsely naming the temporary Banner*.
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

# The twelve-shot asset loop carries the borrowed
# GolbShot::vapour.body.bod.object field in ESI and advances it by the exact
# 0x2e8 GolbShot stride. The cursor also reaches tertiary_body at +0x74; it
# does not replace Player::golb_shots as the owning array.
WORLD_INITIALIZER_GOLB_ASSET_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        20215,
        72,
        "golb_shot_vapour_object_cursor",
        "GolbShotVapourObjectStrideCursor*",
    ),
)

# The twenty-slot asset loop carries the borrowed Object* inside SubLazer's
# body and advances it by one exact 0xb0-byte slot while reaching body color
# and owner_game. The view does not replace SubLazerManager::slots.
WORLD_INITIALIZER_SUB_LAZER_ASSET_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        4267,
        73,
        "sub_lazer_body_object_cursor",
        "SubLazerBodyObjectStrideCursor*",
    ),
)

# The forty-slot asset loop carries the Salt::owner_game field in EDI, reaches
# body fields through fixed negative offsets, and advances by sizeof(Salt).
# Preserve the physical field-first cursor without replacing SaltManager.
WORLD_INITIALIZER_SALT_ASSET_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        4417,
        73,
        "salt_owner_game_cursor",
        "SaltOwnerGameStrideCursor*",
    ),
)

# The native cRNuke methods walk the embedded 25-element sprite array through
# a Sprite** cursor. BN otherwise promotes ESI to a pointer-to-array and then
# invents a compensating Nuke subtraction. The updater also shares its integer
# loop index with the one stack slot used as the x87 conversion source.
NUKE_USER_VAR_UPDATES = (
    (
        "uninit_nuke",
        "RegisterVariableSourceType",
        10,
        72,
        "sprite_slots",
        "Sprite**",
    ),
    (
        "initialize_nuke",
        "RegisterVariableSourceType",
        19,
        72,
        "sprite_slots",
        "Sprite**",
    ),
    (
        "update_nuke",
        "RegisterVariableSourceType",
        75,
        72,
        "sprite_slots",
        "Sprite**",
    ),
    (
        "update_nuke",
        "RegisterVariableSourceType",
        68,
        69,
        "i",
        "int32_t",
    ),
    (
        "update_nuke",
        "StackVariableSourceType",
        71,
        -4,
        "loop_index_float_source",
        "int32_t",
    ),
)

# TipManager owns three adjacent 0x20-byte Tip records. BN otherwise promotes
# each native cursor register to Tip (*)[3] and invents a subtraction back to
# the manager before every access. Preserve the exact borrowed Tip* walks.
TIP_MANAGER_USER_VAR_UPDATES = (
    (
        "initialize_tip_manager",
        "RegisterVariableSourceType",
        8,
        66,
        "tip",
        "Tip*",
    ),
    (
        "uninit_tips",
        "RegisterVariableSourceType",
        2,
        72,
        "tip",
        "Tip*",
    ),
    (
        "enqueue_tip_message",
        "RegisterVariableSourceType",
        3,
        68,
        "tip",
        "Tip*",
    ),
    (
        "update_tip_manager",
        "RegisterVariableSourceType",
        2,
        72,
        "tip",
        "Tip*",
    ),
)

# build_subgame_level inlines BodList::add_bod for the presentation's jetpack,
# three weapon channels, invincibility shell, Snail body, and Player body. The
# active-list anchor is the same BodNode** owner at all seven sites, but BN
# otherwise inherits FrameBodBase** at the first lifetime and void** after the
# register changes. Preserve those exact anchor identities together with the
# borrowed embedded-object receivers. In particular, the first Weapon lifetime
# otherwise remains a pointer-to-array and hides its inherited BodNode fields.
# The former initialized_player override is intentionally absent: the canonical
# cRSubGame receiver now keeps `&game->player` typed without an SSA patch.
BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES = (
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1272,
        66,
        "jetpack_channel",
        "Weapon*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1308,
        67,
        "active_first_ref_jetpack",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1314,
        68,
        "active_first_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1325,
        68,
        "active_first_empty_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1335,
        68,
        "active_first_link_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1337,
        71,
        "active_previous_first_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1343,
        68,
        "active_first_reload_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1350,
        68,
        "active_new_first_jetpack",
        "BodNode*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1367,
        67,
        "weapon_channel_0",
        "Weapon*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1397,
        66,
        "active_first_ref_weapon_0",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1455,
        67,
        "weapon_channel_1",
        "Weapon*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1485,
        66,
        "active_first_ref_weapon_1",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1543,
        67,
        "weapon_channel_2",
        "Weapon*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1573,
        66,
        "active_first_ref_weapon_2",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1631,
        67,
        "invincible_shell",
        "Invincible*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1661,
        66,
        "active_first_ref_invincible_shell",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1734,
        67,
        "presentation",
        "Snail*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1764,
        66,
        "active_first_ref_presentation",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1156,
        73,
        "player",
        "Player*",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1841,
        66,
        "active_first_ref_player",
        "BodNode**",
    ),
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1869,
        68,
        "active_new_first_player",
        "BodNode*",
    ),
)

# create_golb inlines BodList::add_bod twice: first for the zero-offset primary
# body and later for the embedded tertiary body at +0x118. The root list only
# borrows those intrusive BodNode links; it does not own either GolbShot. Pin
# the native register lifetimes so the primary splice stays rooted at
# GameRoot::active_bod_list.first and the tertiary splice does not collapse
# into an offset-GolbShot pointer after ECX/EAX/EDX reuse.
CREATE_GOLB_ACTIVE_BOD_USER_VAR_UPDATES = (
    (
        "create_golb",
        "RegisterVariableSourceType",
        52,
        66,
        "active_first_ref_primary",
        "BodNode**",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        57,
        67,
        "active_first_primary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        78,
        67,
        "active_first_link_primary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        80,
        73,
        "active_previous_first_primary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        86,
        67,
        "active_first_empty_primary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        88,
        67,
        "active_new_first_primary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1431,
        67,
        "tertiary_node",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1500,
        66,
        "active_first_ref_tertiary",
        "BodNode**",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1506,
        68,
        "active_first_tertiary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1521,
        66,
        "active_first_empty_tertiary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1531,
        68,
        "active_first_link_tertiary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1533,
        71,
        "active_previous_first_tertiary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1539,
        68,
        "active_first_reload_tertiary",
        "BodNode*",
    ),
    (
        "create_golb",
        "RegisterVariableSourceType",
        1541,
        68,
        "active_new_first_tertiary",
        "BodNode*",
    ),
)

# kill_golb moves the GolbShot receiver from ECX into ESI before its three
# inlined intrusive-list removals. Keep that callee-saved lifetime typed as the
# enclosing shot so the +0x80 Vapour and +0x118 tertiary body remain visible.
KILL_GOLB_OWNER_USER_VAR_UPDATES = (
    (
        "kill_golb",
        "RegisterVariableSourceType",
        6,
        72,
        "shot_cursor",
        "GolbShot*",
    ),
)

# place_parcels_on_track retains a containing cRSubGame base while its two
# candidate-claim loops advance one 0xf4 SubRow lane. The final projection pass
# instead carries a direct borrowed SubRow cursor. Pin those native register
# lifetimes so the row fields do not collapse back into absolute data symbols;
# neither cursor owns the runtime-row slab.
PLACE_PARCELS_RUNTIME_USER_VAR_UPDATES = (
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1239,
        72,
        "parcel_set_runtime_row_anchor",
        "RuntimeRowStrideAnchor*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        1832,
        73,
        "zero_runtime_row_anchor",
        "RuntimeRowStrideAnchor*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        2177,
        72,
        "projection_row",
        "SubRow*",
    ),
)

# The authored candidate scan begins at SubSegment::row_count, not at the
# enclosing SubSegment base. Its EBX induction advances by the exact 0x4220
# segment stride, while the two stack cursors walk the current row across the
# lane-major glyph grid and the EDI cursor borrows that row's local_position.
# The anchor's trailing word overlaps the next segment's row_base solely to
# preserve the native stride. The EDI type is a +0x08 pointer-offset view of
# the complete authored row, so its negative flag/set-id reads retain the real
# row owner without claiming independent storage.
PLACE_PARCELS_SCAN_USER_VAR_UPDATES = (
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        114,
        69,
        "segment_row_count_anchor",
        "SubSegmentParcelScanAnchor*",
    ),
    (
        "place_parcels_on_track",
        "StackVariableSourceType",
        124,
        -532,
        "saved_segment_row_count_anchor",
        "SubSegmentParcelScanAnchor*",
    ),
    (
        "place_parcels_on_track",
        "StackVariableSourceType",
        186,
        -496,
        "glyph_row_cursor",
        "char*",
    ),
    (
        "place_parcels_on_track",
        "StackVariableSourceType",
        436,
        -492,
        "glyph_lane_cursor",
        "char*",
    ),
    (
        "place_parcels_on_track",
        "RegisterVariableSourceType",
        190,
        73,
        "authored_parcel_row",
        "AuthoredSegmentRowPositionCursorView*",
    ),
)

# The challenge placer reuses ECX for the runtime count, the native
# parcel_set_id field cursor, one selected-row containing anchor, and the
# candidate-bank compaction count. Split only the selected-row definition;
# typing the merged ECX lifetime would falsely claim the unrelated integer and
# field-cursor values. The final ESI loop is a stable borrowed SubRow cursor.
CHALLENGE_PARCELS_RUNTIME_ANCHOR_SPLIT_DEFINITIONS = (
    ("0x44432d", "mlil", "RegisterVariableSourceType", 237, 67),
)

CHALLENGE_PARCELS_RUNTIME_ANCHOR_TARGET_VAR = (
    "RegisterVariableSourceType",
    237,
    67,
)

CHALLENGE_PARCELS_RUNTIME_USER_VAR_UPDATES = (
    (
        "place_challenge_parcels_on_track",
        "RegisterVariableSourceType",
        407,
        72,
        "projection_row",
        "SubRow*",
    ),
)

# The main subgame tick carries the same containing-owner bases while scanning
# one runtime row and its eight cells. EDI's two disjoint MLIL identities are
# already split cleanly by Binary Ninja. The terminal time-trial HUD path also
# retains `game + route_index * sizeof(SubSolution)` as a native EAX cursor;
# type that exact lifetime as an alias of the SubHighScore-owned route record.
# Leave the surrounding row/cell/record index arithmetic as native integers.
UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES = (
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1203,
        67,
        "row_model",
        "RowModel*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1235,
        66,
        "active_first_ref_row",
        "BodNode**",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1241,
        68,
        "active_first_row",
        "BodNode*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1266,
        68,
        "active_first_row_reload",
        "BodNode*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1278,
        68,
        "active_new_first_row",
        "BodNode*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1188,
        73,
        "runtime_row_anchor",
        "RuntimeRowStrideAnchor*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1384,
        73,
        "runtime_cell_anchor",
        "RuntimeCellStrideAnchor*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        3386,
        66,
        "time_trial_route_cursor",
        "TimeTrialRouteRecordCursor*",
    ),
)

# VC6 computes the runtime-row ring-speed address as a dword index relative to
# the complete cRSubGame base, so there is no honest SubRow* lifetime for
# Binary Ninja to type. Preserve the exact owner at the eight load
# instructions instead. The Windows identity below is algebraically
# `runtime_rows + row * 0xf4 + 0xe8`; Android and iOS independently pass their
# current authored row's corresponding scalar to cRSubGame::AddRing.
UPDATE_SUBGAME_RING_SPEED_COMMENT = (
    "Owner: cRSubGame::runtime_rows[runtime_row_scan_begin].ring_speed "
    "(+0x5ccac8 + row * 0xf4 + 0xe8). Android cRSubGame::AI @ 0x82214 and "
    "iOS cRSubGame::AI @ 0x33a50 independently pass the current authored "
    "row speed to AddRing; Windows offsets remain authoritative."
)

UPDATE_SUBGAME_RING_SPEED_COMMENT_UPDATES = (
    (
        "update_subgame",
        "0x4395a3",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x4395cb",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x4395f3",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x43961f",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x43968f",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x4396cb",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x439707",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
    (
        "update_subgame",
        "0x4397fc",
        "8b 14 8e",
        UPDATE_SUBGAME_RING_SPEED_COMMENT,
    ),
)

# The replay-exit branch at 0x4399b8 loads g_game_base into EAX before storing
# front-end state 27. Its sibling branch uses EAX for the previous integer
# state, so Binary Ninja merges the two values and renders only this store as
# raw GameRoot +0x1b8. Split the pointer-producing definition alone; retyping
# the shared EAX lifetime would falsely claim the sibling integer as GameRoot*.
UPDATE_SUBGAME_FRONTEND_ROOT_SPLIT_DEFINITIONS = (
    ("0x4399b8", "mlil", "RegisterVariableSourceType", 3624, 66),
)

UPDATE_SUBGAME_FRONTEND_ROOT_TARGET_VAR = (
    "RegisterVariableSourceType",
    3624,
    66,
)

# remove_subgame_bods advances through one runtime cell at a time, then borrows
# the intrusive BodNode::list_next field from each embedded row/pickup/hazard
# owner. Binary Ninja otherwise promotes the cell and Golb-shot iterators to
# pointers to their complete backing arrays, and infers SubHealth** for the
# health field cursor. Pin only the exact native register lifetimes: none of the
# list-next cursors owns the embedded pools, while the Golb cursor walks the
# Player-owned fixed array one record at a time.
REMOVE_SUBGAME_BODS_CURSOR_USER_VAR_UPDATES = (
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        9,
        73,
        "runtime_cell_cursor",
        "cRSubLoc*",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        15,
        72,
        "row_list_next_cursor",
        "BodNode**",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        181,
        72,
        "health_list_next_cursor",
        "BodNode**",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        587,
        72,
        "garbage_list_next_cursor",
        "BodNode**",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        712,
        72,
        "slug_list_next_cursor",
        "BodNode**",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        848,
        72,
        "ring_list_next_cursor",
        "BodNode**",
    ),
    (
        "remove_subgame_bods",
        "RegisterVariableSourceType",
        1562,
        72,
        "golb_shot_cursor",
        "GolbShot*",
    ),
)

# The ring spawner retains a manager-relative ESI cursor until activation is
# complete, then borrows the embedded SubRing's BodNode prefix for insertion in
# the root active list. Preserve those two ownership domains explicitly: the
# cursor does not own another cRSubGame, and the root list owns neither the
# selected ring nor any other embedded bod.
SPAWN_TRACK_RING_USER_VAR_UPDATES = (
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        3,
        66,
        "slot_index",
        "int32_t",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        11,
        67,
        "state_cursor",
        "SubRingState*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        76,
        72,
        "slot_cursor",
        "SubRingSlotCursor*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "StackVariableSourceType",
        114,
        -16,
        "default_phase_step",
        "float",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        123,
        71,
        "effective_kind",
        "int32_t",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1263,
        66,
        "active_head",
        "BodNode**",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1268,
        67,
        "active_first",
        "BodNode*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1289,
        67,
        "first_for_link",
        "BodNode*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1291,
        71,
        "linked_head",
        "BodNode*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1297,
        67,
        "first_for_promote",
        "BodNode*",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "RegisterVariableSourceType",
        1299,
        67,
        "promoted_head",
        "BodNode*",
    ),
)

# The pickup spawners retain a cRSubGame-relative cursor while advancing
# the fixed-size slot stride. These prefix views make the inline JetPack and
# SubHealth owners visible without pretending the cursor owns another runtime.
SPAWN_TRACK_PICKUP_CURSOR_USER_VAR_UPDATES = (
    (
        "spawn_track_health_pickup",
        "RegisterVariableSourceType",
        60,
        72,
        "health_cursor",
        "SubHealthSlotCursor*",
    ),
    (
        "spawn_track_jetpack_pickup",
        "RegisterVariableSourceType",
        61,
        72,
        "jetpack_cursor",
        "JetPackSlotCursor*",
    ),
)

# The collision dispatcher keeps byte offsets in EDI and repeatedly forms a
# temporary `cRSubGame + slot_offset` pointer in EAX. These analysis-only
# cursor views name the embedded slot reached by each large displacement while
# retaining the real cRSubGame owner and the native byte-strided lifetime.
COLLISION_POOL_CURSOR_USER_VAR_UPDATES = (
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        80,
        66,
        "salt_cursor",
        "SaltSlotCursor*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        310,
        66,
        "sub_lazer_cursor",
        "SubLazerSlotCursor*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        828,
        66,
        "slug_cursor",
        "SlugSlotCursor*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1385,
        66,
        "parcel_cursor",
        "ParcelSlotCursor*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        1663,
        66,
        "health_cursor",
        "SubHealthSlotCursor*",
    ),
    (
        "handle_subgoldy_collisions",
        "RegisterVariableSourceType",
        2353,
        66,
        "ring_cursor",
        "SubRingSlotCursor*",
    ),
)

# spawn_salt_hazard scans from Salt::state with a full 0x98-byte actor stride,
# then keeps the selected manager-owned Salt in ESI. Preserve both borrowed
# lifetimes across broad path-template replays.
SPAWN_SALT_HAZARD_USER_VAR_UPDATES = (
    (
        "spawn_salt_hazard",
        "RegisterVariableSourceType",
        3,
        68,
        "salt_state_cursor",
        "SaltStateStrideCursor*",
    ),
    (
        "spawn_salt_hazard",
        "RegisterVariableSourceType",
        37,
        72,
        "salt",
        "Salt*",
    ),
)

# VC6 retains containing-owner bases while advancing one authored row, one
# runtime row, and one runtime cell at their native 0x38/0xf4/0x54 strides.
# Binary Ninja otherwise flattens all three into void-pointer displacement
# arithmetic. The stack slot is the matching authored-row ordinal, not the
# cRSubGame pointer inferred from an earlier compiler-reused lifetime.
# The attachment-entry span has a separate exact SubRow lifetime: it begins at
# runtime_row_anchor->row and advances by the native 0xf4 SubRow stride.
# The four-pointer fringe tail likewise has exact slot, object-reload, and
# inherited BodBase::position lifetimes; keep the physical-register reuse
# split instead of weakening those values to void* or integer pointers.
# The surrounding stack slots are also single-role source state: the authored
# segment cursor, runtime-row/lane ordinals, trampoline counter, row-event
# owner, and per-row first/last and attachment latches. Do not name the reused
# random-length/edge-row slot, whose two lifetimes still overlap in HLIL.
POPULATE_RUNTIME_CLEAR_CURSOR_USER_VAR_UPDATES = (
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        569,
        -40,
        "row_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        573,
        73,
        "parcel_spawn_y_cursor",
        "SubRowParcelSpawnYStrideCursor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        633,
        72,
        "lane_and_flags_cursor",
        "TrackRowCellLaneAndFlagsStrideCursor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        689,
        66,
        "next_row_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        698,
        72,
        "cell_fringe_front_cursor",
        "TrackRowCellFringeFrontStrideCursor*",
    ),
)

POPULATE_RUNTIME_SPLIT_USER_VAR_UPDATES = (
    (
        (
            ("0x436165", "mlil", "RegisterVariableSourceType", 693, 67),
            ("0x43616a", "mlil_ssa", "RegisterVariableSourceType", 698, 67),
            ("0x436171", "mlil_ssa", "RegisterVariableSourceType", 705, 67),
        ),
        ("RegisterVariableSourceType", 693, 67),
        "remaining_cell_lanes",
        "int32_t",
    ),
    (
        (("0x4361a1", "mlil", "RegisterVariableSourceType", 753, 67),),
        ("RegisterVariableSourceType", 753, 67),
        "segment_count",
        "int32_t",
    ),
    (
        (
            ("0x4361ad", "mlil", "RegisterVariableSourceType", 765, 67),
            ("0x4361b3", "mlil_ssa", "RegisterVariableSourceType", 771, 67),
            ("0x4361bd", "mlil_ssa", "RegisterVariableSourceType", 781, 67),
        ),
        ("RegisterVariableSourceType", 765, 67),
        "visited_cursor",
        "uint8_t*",
    ),
    (
        (("0x43714d", "mlil", "RegisterVariableSourceType", 4765, 67),),
        ("RegisterVariableSourceType", 4765, 67),
        "runtime_owner",
        "cRSubGame*",
    ),
)

# The outer BuildLevel loop has three distinct borrowed SubSegment stages.
# ESI selects a complete segment owned by level_definition, the stack slot
# carries that active segment across row iterations, and EDX carries the
# possibly overridden completion-row source into the authored-row copy.
# Preserve those complete-record borrows and the exact row/slot ordinals;
# none of these cursors owns segment storage.
POPULATE_SEGMENT_SELECTION_USER_VAR_UPDATES = (
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        759,
        66,
        "visited_segment_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        810,
        73,
        "runtime_row_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        814,
        71,
        "build_runtime_owner",
        "cRSubGame*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        822,
        72,
        "selected_segment",
        "SubSegment*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        971,
        66,
        "random_segment_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        1012,
        66,
        "sequential_segment_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        1052,
        66,
        "selected_segment_row_count",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        1147,
        68,
        "source_segment",
        "SubSegment*",
    ),
)

# The P/p glyph arm borrows one complete Path record from the runtime-owned
# PathPair bank. The mirror branch chooses primary or secondary; it never
# transfers the pair or either path. The selected path is retained by the
# current cell, whose borrowed pointer is then stamped across its row span.
POPULATE_ATTACHMENT_INSTALL_USER_VAR_UPDATES = (
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        3686,
        67,
        "selected_attachment_path",
        "cRPath*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        3844,
        68,
        "attachment_span_index",
        "int32_t",
    ),
)

# This short-lived EDI alias is already auto-typed as cRSubLoc*. Persisting
# it as a user variable makes no ownership visible in HLIL and weakens several
# set_bod_object call arguments to BodVtable**. Keep it automatic.
REJECTED_POPULATE_RUNTIME_CELL_ALIAS_REMOVALS = (
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        2068,
        73,
        "runtime_cell",
        "cRSubLoc*",
    ),
)

POPULATE_RUNTIME_USER_VAR_UPDATES = (
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        0,
        -36,
        "segment_cursor",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        549,
        -32,
        "trampoline_counter",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        553,
        -66,
        "first_or_last_row",
        "char",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        558,
        -44,
        "row_event_owner",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        794,
        -64,
        "build_row",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        833,
        -60,
        "active_segment",
        "SubSegment*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        1077,
        -52,
        "segment_row_index",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        1921,
        -65,
        "attachment_entry_installed",
        "char",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "StackVariableSourceType",
        1926,
        -48,
        "lane",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        1363,
        72,
        "segment_row_anchor",
        "SubSegmentRowStrideAnchor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        1448,
        69,
        "runtime_row_anchor",
        "RuntimeRowStrideAnchor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        2002,
        72,
        "runtime_cell_anchor",
        "RuntimeCellStrideAnchor*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        3857,
        67,
        "stamped_row",
        "SubRow*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        4697,
        67,
        "fringe_slot",
        "Fringe**",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        4692,
        68,
        "remaining_fringe_slots",
        "int32_t",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        4697,
        66,
        "fringe_object",
        "Fringe*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        4714,
        66,
        "fringe_object_reloaded",
        "Fringe*",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "RegisterVariableSourceType",
        4718,
        66,
        "fringe_position",
        "Vec3*",
    ),
)

POPULATE_FRINGE_USER_VAR_NAMES = frozenset(
    {
        "fringe_slot",
        "remaining_fringe_slots",
        "fringe_object",
        "fringe_object_reloaded",
        "fringe_position",
    }
)
POPULATE_FRINGE_USER_VAR_UPDATES = tuple(
    update
    for update in POPULATE_RUNTIME_USER_VAR_UPDATES
    if update[4] in POPULATE_FRINGE_USER_VAR_NAMES
)

# CondenseTrack carries field-first cursors for the row attachment flags and
# every cell lane-and-flags lifetime. The three scanners deliberately use
# different element types: floor and wall advance the tile byte at +0x3c,
# while slide advances the uint32_t lane-and-flags field at +0x40. Preserve
# those exact native identities so BN does not re-home the reused registers in
# an unrelated GameRoot field or flatten the continuation cleanup ownership.
MERGE_RUNTIME_USER_VAR_UPDATES = (
    (
        "merge_track_tile_runs",
        "StackVariableSourceType",
        83,
        -4,
        "row_attachment_flags",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        20,
        66,
        "seed_lane_flags",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        87,
        69,
        "cell_lane_flags",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        105,
        73,
        "cell",
        "cRSubLoc*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        155,
        67,
        "floor_tile_cursor",
        "uint8_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        281,
        66,
        "floor_cleanup_lane_flags",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        365,
        73,
        "slide_lane_flags_cursor",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        475,
        66,
        "slide_cleanup_lane_flags",
        "uint32_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        613,
        68,
        "wall_tile_cursor",
        "uint8_t*",
    ),
    (
        "merge_track_tile_runs",
        "RegisterVariableSourceType",
        773,
        66,
        "wall_cleanup_lane_flags",
        "uint32_t*",
    ),
)

# MakeFringe owns a plain SubRow cursor and advances one cRSubLoc at a
# time. BN otherwise interprets both register lifetimes as pointers to the
# complete embedded arrays and compensates with GameRoot-sized subtraction.
# Preserve the exact register and spill identities recovered from the native
# loop so the row, cell, and final-row increment retain their real owners.
FRINGE_RUNTIME_USER_VAR_UPDATES = (
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        44,
        68,
        "row",
        "SubRow*",
    ),
    (
        "build_track_fringe_objects",
        "RegisterVariableSourceType",
        52,
        72,
        "cell",
        "cRSubLoc*",
    ),
    (
        "build_track_fringe_objects",
        "StackVariableSourceType",
        58,
        -68,
        "row_cursor",
        "SubRow*",
    ),
)

# SlideSmoothTrack carries the same cRSubGame-relative cell cursor in two
# disjoint ESI lifetimes. The first compares the current cell with the next
# same-lane row; the second compares it with the previous same-lane row.
HARMONIZE_RUNTIME_USER_VAR_UPDATES = (
    (
        "harmonize_center_lane_floor_slide_variants",
        "RegisterVariableSourceType",
        98,
        72,
        "forward_cell_anchor",
        "RuntimeCellStrideAnchor*",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "RegisterVariableSourceType",
        492,
        72,
        "backward_cell_anchor",
        "RuntimeCellStrideAnchor*",
    ),
)

# calc_path_length_z produces the inverse transform for each 0xa8-byte
# sample, while the swept-entry scan consumes two sample bases carried in
# transient ECX definitions. Preserve the containing sample owner instead of
# letting the matrix calls collapse those variables to TransformMatrix*/void*.
PATH_SAMPLE_INVERSE_USER_VAR_UPDATES = (
    (
        "calc_path_length_z",
        "StackVariableSourceType",
        74,
        -32,
        "primary_sample",
        "PathTemplateSample*",
    ),
    (
        "calc_path_length_z",
        "StackVariableSourceType",
        89,
        -32,
        "secondary_sample",
        "PathTemplateSample*",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "RegisterVariableSourceType",
        69,
        67,
        "sample",
        "PathTemplateSample*",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "RegisterVariableSourceType",
        332,
        67,
        "swept_sample",
        "PathTemplateSample*",
    ),
)

# The two alpha publications reload g_game_base into a physical register
# lifetime that BN otherwise merges with nearby cRPath* template reloads. Split
# just those two definitions and merge them as the shared process root. A
# transactional preview proves that this restores both complete
# GameRoot::subgame.runtime_rows[..].primary_attachment_cell owners without
# disturbing the surrounding Path lifetime.
ATTACHMENT_FOLLOW_ROOT_SPLIT_DEFINITIONS = (
    (
        "0x420dab",
        "mlil",
        "RegisterVariableSourceType",
        251,
        66,
    ),
    (
        "0x420e5e",
        "mlil",
        "RegisterVariableSourceType",
        430,
        66,
    ),
)
ATTACHMENT_FOLLOW_ROOT_TARGET_VAR = (
    "RegisterVariableSourceType",
    251,
    66,
)

# The entry-mesh milestone branches repeatedly reload
# SubRow::primary_attachment_cell. BN's SSA split loses the cRSubLoc*/cRPath*
# field types after the indexed 0xf4-byte row calculation even though the
# canonical owner graph proves every load. Reapply the exact nine variable
# identities so the milestone writes retain their real cell and Path owners.
ATTACHMENT_FOLLOW_USER_VAR_UPDATES = (
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        186,
        68,
        "primary_attachment_cell_restore",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        196,
        72,
        "entry_base_template",
        "cRPath*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        218,
        67,
        "primary_attachment_cell_restore_object",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        256,
        67,
        "primary_attachment_cell_restore_alpha",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        327,
        66,
        "primary_attachment_cell_transition_flags",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        364,
        67,
        "primary_attachment_cell_transition_template",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        371,
        72,
        "entry_transition_template",
        "cRPath*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        397,
        68,
        "primary_attachment_cell_transition_object",
        "cRSubLoc*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        435,
        67,
        "primary_attachment_cell_transition_alpha",
        "cRSubLoc*",
    ),
)

REPLAY_RUN_RECORD_FIELD_UPDATES = (
    ("0x00", "lateral_x", "int16_t"),
    ("0x02", "delta_z", "int16_t"),
    ("0x04", "flags", "uint16_t"),
)

SUBGAME_RUNTIME_FIELD_UPDATES = (
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
    ("0x28", "challenge_speed_value", "int32_t"),
    ("0x2c", "challenge_difficulty_value", "int32_t"),
    ("0x30", "rate_or_level_arg", "RuntimeRateOrLevelArg"),
    ("0x34", "challenge_difficulty_scalar", "float"),
    ("0x38", "subgame_rate", "float"),
    ("0x3c", "subgame_state", "int32_t"),
    ("0x40", "level_mode", "int32_t"),
    ("0x44", "level_mode_arg", "int32_t"),
    ("0x48", "base_subgame_rate", "float"),
    ("0x4c", "runtime_flags", "uint32_t"),
    ("0x50", "first_block_row_count", "int32_t"),
    ("0x54", "runtime_row_count", "int32_t"),
    ("0x58", "completion_row_start", "int32_t"),
    ("0x5c", "segment_cache", "SegmentCache"),
    ("0xa854", "track_state_latch", "uint8_t"),
    ("0xa858", "tutorial", "Tutorial"),
    ("0xa874", "level_definition", "SubTracks"),
    ("0x1b01ec", "level_definition_scratch", "SubTracks"),
    ("0x355b64", "fringe_attachment_list_head", "BodBase"),
    ("0x355b9c", "track_body_list_head", "BodBase"),
    ("0x355bd4", "barrier_sub_lazer_list_head", "BodBase"),
    ("0x355c0c", "salt_hazard_list_head", "BodBase"),
    ("0x355c44", "landscape_slice_list_head", "BodBase"),
    ("0x355c7c", "unknown_bod_355c7c", "BodBase"),
    ("0x355cb4", "special_track_cell_list_head", "BodBase"),
    ("0x355cec", "unknown_bod_355cec", "BodBase"),
    ("0x355d24", "golb_vapour_list_head", "BodBase"),
    ("0x355d5c", "unknown_bod_355d5c", "BodBase"),
    ("0x355d94", "active_level_score", "int32_t"),
    ("0x355d98", "active_level_timer", "Time"),
    # The speedup, jetpack, health, slug, lazer, salt, banner, garbage, and
    # ring pools are owned by their newer canonical replay lanes. Do not
    # reinstall the historical presentation-header aliases here.
    ("0x35bb7c", "slug_voice_manager", "SlugVoiceManager"),
    ("0x35bb88", "top_score_widget", "FrontendWidget*"),
    ("0x35bb8c", "bottom_score_widget", "FrontendWidget*"),
    ("0x35bb90", "lives_icon_widget", "FrontendWidget*"),
    ("0x35bb94", "lives_text_widget", "FrontendWidget*"),
    ("0x35bb98", "life_stock_widgets", "FrontendWidget*[0x9]"),
    ("0x35bbbc", "fringe_manager", "FringeManager"),
    ("0x3bb700", "blink_random_index", "int32_t"),
    ("0x3bb704", "blink_random_samples", "float[0x18]"),
    ("0x3bb764", "player", "Player"),
    ("0x3bfac8", "runtime_cells", "cRSubLoc[0xc80][8]"),
    ("0x5ccac8", "runtime_rows", "SubRow[0xc80]"),
    ("0x68b4c8", "sub_high_score", "SubHighScore"),
    ("0xfd2b10", "current_high_score_record", "SubSolution"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SubSolution*"),
    ("0xff25d8", "selected_level_record_cursor", "int32_t"),
    ("0xff25dc", "replay_update_cursor", "int32_t"),
    ("0xff25e0", "time_trial", "TimeTrial"),
    ("0xff2910", "path_manager", "cRPathManager"),
    ("0xff2914", "path_pairs", "PathPair[63]"),
    ("0xff7bc4", "barrier", "BarrierActor"),
    ("0xff7c00", "landscape_manager", "LandscapeManager"),
    ("0x10013a4", "smtrack_heightfield", "Face"),
    ("0x10014cc", "sm_tracks", "cRSMTracks"),
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
)

# The frame-renderer bootstrap uses a renderer-local list view at +0x5a8 and
# leaves the post-subgame root tail opaque. Gameplay proves that the root list
# stores BodNode links, and this replay lane owns TipManager, so promote both
# canonical owners after importing their authoritative types.
GAME_ROOT_FIELD_UPDATES = (
    ("0x5a8", "active_bod_list", "BodList"),
    ("0x74618", "subgame", "cRSubGame"),
    ("0x12e6f58", "tip_manager", "TipManager"),
)

VAPOUR_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "point_count", "int32_t"),
    ("0x84", "capacity", "int32_t"),
    ("0x88", "half_width", "float"),
    ("0x8c", "z_floor", "float*"),
    ("0x90", "points", "TransformMatrix*"),
)

JETPACK_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x44", "owner_game", "cRSubGame*"),
    ("0x74", "vapour_a", "Vapour"),
    ("0x108", "vapour_b", "Vapour"),
)

SUB_HEALTH_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
)

SLUG_FIELD_UPDATES = (
    ("0x80", "state", "SubSlugState"),
    ("0x84", "death_toss_direction", "SubSlugDeathTossDirection"),
    ("0x9c", "death_toss_progress", "float"),
    ("0xa0", "death_toss_progress_step", "float"),
    ("0xa4", "death_toss_secondary_progress", "float"),
    ("0xa8", "death_toss_secondary_progress_step", "float"),
)

SLUG_STATE_CURSOR_FIELD_UPDATES = (
    ("0x00", "state", "SubSlugState"),
)

SALT_STATE_CURSOR_FIELD_UPDATES = (
    ("0x00", "state", "SaltState"),
)

SUB_SPEED_UP_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
)

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "cRSubGame*"),
)

WARNING_FIELD_UPDATES = (
    ("0x00", "state", "WarningState"),
)

DAMAGE_GUAGE_FIELD_UPDATES = (
    ("0x00", "state", "DamageGuageState"),
)

NUKE_FIELD_UPDATES = (
    ("0x00", "state", "NukeState"),
)

CLICK_START_FIELD_UPDATES = (
    ("0x00", "bod", "RenderableBod"),
    ("0x80", "state", "ClickStartState"),
    ("0x84", "prompt", "FrontendWidget*"),
    ("0x88", "teardown_progress", "float"),
    ("0x8c", "teardown_progress_step", "float"),
    ("0x98", "owner_player", "Player*"),
    ("0xa8", "hide_prompt", "uint8_t"),
)

TEXTURE_REF_FIELD_UPDATES = (
    ("0x00", "flags", "TextureRefFlags"),
    ("0x04", "loaded_width", "int32_t"),
    ("0x08", "loaded_height", "int32_t"),
    ("0x0c", "name", "char[0x80]"),
    ("0x8c", "slot_index", "int32_t"),
    ("0x90", "frame_count", "int32_t"),
    ("0x94", "frame_progress_step", "float"),
    ("0x98", "texture_ref", "void*"),
    ("0xa0", "mip_levels", "int32_t"),
)

SNAIL_VISUAL_FIELD_UPDATES = (
    ("0x10", "flags", "uint32_t"),
    ("0x18", "material_index", "int32_t"),
    ("0x80", "follow_lateral_response", "float"),
    ("0x84", "squidge_primary", "float"),
    ("0x88", "squidge_secondary", "float"),
)

BOD_BASE_FIELD_UPDATES = (
    ("0x00", "bod", "BodNode"),
    ("0x10", "position", "Vec3"),
    ("0x1c", "render_arg_1c", "float"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "Object*"),
    ("0x28", "color", "tColour"),
)

FRINGE_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
)

FRINGE_MANAGER_FIELD_UPDATES = (
    ("0x00000", "objects", "Fringe[7000]"),
    ("0x5fb40", "count", "int32_t"),
)

SUB_LOC_FIELD_UPDATES = (
    ("0x00", "bod", "BodNode"),
    ("0x10", "anchor_position", "Vec3"),
    ("0x1c", "render_arg_1c", "float"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "Object*"),
    ("0x28", "color", "tColour"),
    ("0x38", "attachment_template_record", "cRPath*"),
    ("0x3c", "tile_id", "SubLocTileId"),
    ("0x3d", "open_edge_mask", "uint8_t"),
    ("0x40", "lane_and_flags", "uint32_t"),
    ("0x44", "fringe_front", "Fringe*"),
    ("0x48", "fringe_right", "Fringe*"),
    ("0x4c", "fringe_left", "Fringe*"),
    ("0x50", "fringe_back", "Fringe*"),
)

ROW_MODEL_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "velocity", "Vec3"),
)

THANKS_SCREEN_FIELD_UPDATES = (
    ("0x00", "game", "cRSubGame*"),
    ("0x04", "message_widget", "FrontendWidget*"),
    ("0x08", "message_state", "int32_t"),
    ("0x0c", "message_progress", "float"),
    ("0x10", "message_progress_step", "float"),
)

SUB_ROW_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "row_model", "RowModel"),
    ("0x90", "parcel_spawn_position", "Vec3"),
    ("0x9c", "parcel_set_id", "int32_t"),
    ("0xa0", "attachment_template_index", "int32_t"),
    ("0xa4", "primary_attachment_cell", "cRSubLoc*"),
    ("0xa8", "secondary_attachment_cell", "cRSubLoc*"),
    ("0xac", "installed_heading_delta", "float"),
    ("0xb0", "attachment_body", "BodBase"),
    ("0xe8", "ring_speed", "float"),
    ("0xec", "source_segment", "SubSegment*"),
    ("0xf0", "row_event_id", "int32_t"),
)

# Authored cRPath field overlay. Its leading render body and the +0x60 fringe
# body are both constructor-proven BodBase owners. Windows stores 126 exact
# 0xa8-byte instances as 63 adjacent PathPair records.
PATH_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "kind", "PathTemplateKind"),
    ("0x3c", "is_mirrored_x", "uint8_t"),
    ("0x40", "side_exit_mode", "uint32_t"),
    ("0x44", "segment_count", "uint32_t"),
    ("0x48", "row_span_count", "uint32_t"),
    ("0x4c", "segment_count_f", "float"),
    ("0x50", "width_or_scale", "float"),
    ("0x54", "width_cells", "uint32_t"),
    ("0x58", "primary_samples", "PathTemplateSample*"),
    ("0x5c", "secondary_samples", "PathTemplateSample*"),
    ("0x60", "fringe_mesh_bod", "BodBase"),
    ("0x98", "installed_heading_delta", "float"),
    ("0x9c", "has_entry_mesh_transition", "uint8_t"),
    ("0xa0", "entry_transition_strip_mesh", "Object*"),
    ("0xa4", "entry_base_strip_mesh", "Object*"),
)

PATH_TEMPLATE_SAMPLE_FIELD_UPDATES = (
    ("0x40", "inverse_matrix", "TransformMatrix"),
    ("0xa4", "lateral_source", "float"),
)

GOLDY_PATH_FOLLOW_FIELD_UPDATES = (
    ("0x04", "template_record", "cRPath*"),
    # Reset by populate_runtime_track_cells_from_segments and read by
    # update_subgoldy. No nonzero producer is proved yet.
    ("0x3c", "flag_3c", "uint8_t"),
)

GOLDY_PATH_FOLLOW_OWNER_TYPE_NAMES = (
    "cRPathFollowGoldy",
    "FollowState",
)

GOLDY_PATH_FOLLOW_PLAYER_FIELD_UPDATES = (
    ("0x384", "follow_state", "cRPathFollowGoldy"),
)

JET_PARTICLE_SLOT_FIELD_UPDATES = (
    ("0x00", "sprite", "Sprite*"),
    ("0x04", "wobble_x", "float"),
    ("0x08", "wobble_y", "float"),
    ("0x0c", "wobble_alpha", "float"),
)

SUB_HOVER_FIELD_UPDATES = (
    ("0x00", "progress", "float"),
    ("0x04", "progress_step", "float"),
    ("0x0c", "state", "SubHoverState"),
    ("0x10", "player", "Player*"),
    ("0x14", "wobble_x", "float"),
    ("0x18", "wobble_y", "float"),
    ("0x1c", "wobble_alpha", "float"),
    ("0x20", "particle_slots", "JetParticleSlot[0x1e]"),
    ("0x200", "game", "cRSubGame*"),
    ("0x20c", "warning_intensity_latch", "float"),
    ("0x210", "warning_intensity", "float"),
)

TIP_DATA_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "anchor_x", "float"),
    ("0x08", "layout_y", "float"),
    ("0x0c", "dismiss_seconds", "float"),
    ("0x10", "text", "char*"),
)

TIP_FIELD_UPDATES = (
    ("0x00", "active", "int32_t"),
    ("0x04", "previous_outer_owner", "int32_t"),
    ("0x08", "definition", "TipData*"),
    ("0x0c", "widget_main", "FrontendWidget*"),
    ("0x10", "widget_ok", "FrontendWidget*"),
    ("0x14", "widget_disable", "FrontendWidget*"),
    ("0x18", "dismiss_progress", "float"),
    ("0x1c", "dismiss_step", "float"),
)

TIP_MANAGER_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "tips", "Tip[0x3]"),
)

TUTORIAL_FIELD_UPDATES = (
    ("0x0c", "game", "cRSubGame*"),
)

BOD_CORE_DATA_VAR_UPDATES = (
    ("0x4974fc", "void*"),
    ("0x497500", "void*"),
    ("0x50331c", "int32_t"),
)

FRINGE_DATA_VAR_UPDATES = (
    ("0x497344", "void*"),
)

TRACK_RENDER_CACHE_DATA_VAR_UPDATES = (
    ("0x497338", "void*"),
)

DATA_VAR_UPDATES = (
    ("0x4972b0", "void*"),
    ("0x4972f8", "void*"),
    ("0x497314", "void*"),
    ("0x497318", "void*"),
    ("0x49731c", "void*"),
    ("0x497320", "void*"),
    *BOD_CORE_DATA_VAR_UPDATES,
    *FRINGE_DATA_VAR_UPDATES,
    *TRACK_RENDER_CACHE_DATA_VAR_UPDATES,
    ("0x4ac5c8", "TipData"),
    ("0x643190", "float"),
    ("0x643194", "float"),
)


def ensure_c_r_sub_loc_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Promote the exact mobile-authored cRSubLoc class identity."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name for name in SUB_LOC_OWNER_TYPE_NAMES if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted cRSubLoc owner types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name for name in SUB_LOC_OWNER_TYPE_NAMES if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRSubLoc owner types already equivalent",
            "types": SUB_LOC_OWNER_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=SUB_LOC_OWNER_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_c_r_subgame_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Promote the cross-port authored cRSubGame identity over the old alias."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name for name in SUBGAME_OWNER_TYPE_NAMES if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted cRSubGame owner types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name for name in SUBGAME_OWNER_TYPE_NAMES if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRSubGame owner types already equivalent",
            "types": SUBGAME_OWNER_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=SUBGAME_OWNER_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_c_r_sub_loc_dependent_view_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Keep cell-bearing analysis views aligned with the primary owner."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name
        for name in SUB_LOC_DEPENDENT_VIEW_TYPE_NAMES
        if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted cRSubLoc-dependent views: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name
        for name in SUB_LOC_DEPENDENT_VIEW_TYPE_NAMES
        if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRSubLoc-dependent views already equivalent",
            "types": SUB_LOC_DEPENDENT_VIEW_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=SUB_LOC_DEPENDENT_VIEW_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_golb_path_follow_state(*, target: str) -> dict[str, object]:
    if struct_exists(
        REPO_ROOT,
        target=target,
        struct_name="GolbPathFollowState",
    ):
        return {
            "op": "types_declare",
            "status": "skipped",
            "reason": "GolbPathFollowState already present",
            "declaration": GOLB_PATH_FOLLOW_STATE_DECLARATION,
        }

    return {
        "op": "types_declare",
        "declaration": GOLB_PATH_FOLLOW_STATE_DECLARATION,
        "result": run_bn(
            REPO_ROOT,
            "types",
            "declare",
            "--target",
            target,
            GOLB_PATH_FOLLOW_STATE_DECLARATION,
        ),
    }


def ensure_c_r_path_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Promote the exact dual-mobile-authored cRPath class identity."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name for name in PATH_OWNER_TYPE_NAMES if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted cRPath owner types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name for name in PATH_OWNER_TYPE_NAMES if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRPath owner types already equivalent",
            "types": PATH_OWNER_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=PATH_OWNER_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_c_r_path_manager_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Promote the exact mobile-authored cRPathManager class identity."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name for name in PATH_MANAGER_OWNER_TYPE_NAMES if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted cRPathManager owner types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name for name in PATH_MANAGER_OWNER_TYPE_NAMES if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRPathManager owner types already equivalent",
            "types": PATH_MANAGER_OWNER_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=PATH_MANAGER_OWNER_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_goldy_path_follow_owner_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Promote the exact mobile-authored cRPathFollowGoldy class identity."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name
        for name in GOLDY_PATH_FOLLOW_OWNER_TYPE_NAMES
        if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted Goldy path-follow types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name
        for name in GOLDY_PATH_FOLLOW_OWNER_TYPE_NAMES
        if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRPathFollowGoldy owner types already equivalent",
            "types": GOLDY_PATH_FOLLOW_OWNER_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=GOLDY_PATH_FOLLOW_OWNER_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def ensure_golb_authored_types(
    *, target: str, header_path: Path
) -> dict[str, object]:
    """Replay the mobile-proven cRSubGolb base and authored type aliases."""

    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    missing_from_header = [
        name for name in GOLB_AUTHORED_TYPE_NAMES if name not in equivalence
    ]
    if missing_from_header:
        raise RuntimeError(
            "authoritative header omitted Golb authored types: "
            + ", ".join(missing_from_header)
        )

    stale_types = tuple(
        name for name in GOLB_AUTHORED_TYPE_NAMES if not equivalence[name]
    )
    if not stale_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "Golb authored types already equivalent",
            "types": GOLB_AUTHORED_TYPE_NAMES,
        }

    result = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=stale_types,
        include_types=GOLB_AUTHORED_TYPE_NAMES,
    )
    result["stale_types"] = stale_types
    return result


def verify_golb_shot_inheritance(*, target: str) -> dict[str, object]:
    """Fail closed unless GolbShot has one zero-offset RenderableBod base."""

    response = run_bn(
        REPO_ROOT,
        "py",
        "exec",
        "--target",
        target,
        "--format",
        "json",
        "--code",
        """
shot = bv.get_type_by_name("GolbShot")
decompiles = {}
for function_name in ("initialize_golb_shot", "kill_golb", "create_golb"):
    functions = list(bv.get_functions_by_name(function_name))
    decompiles[function_name] = (
        ""
        if len(functions) != 1 or functions[0].hlil is None
        else str(functions[0].hlil)
    )
result = None if shot is None else {
    "width": int(shot.width),
    "bases": [
        {
            "type": str(base.type),
            "offset": int(base.offset),
            "width": int(base.width),
        }
        for base in shot.base_structures
    ],
    "direct_members": [
        {
            "name": str(member.name),
            "type": str(member.type),
            "offset": int(member.offset),
        }
        for member in shot.members
        if int(member.offset) < 0x198
    ],
    "aliases": {
        name: (
            None
            if (alias := bv.get_type_by_name(name)) is None
            else {"width": int(alias.width), "type": str(alias)}
        )
        for name in ("cRSubGolb", "cRPathFollowGolb")
    },
    "decompile_checks": {
        "initialize_inherited_vtable": (
            "shot->bod.bod.vtable = &g_golb_shot_vtable"
            in decompiles["initialize_golb_shot"]
        ),
        "kill_inherited_list": (
            "shot->bod.bod.list_flags" in decompiles["kill_golb"]
        ),
        "create_inherited_list": (
            "shot->bod.bod.list_flags" in decompiles["create_golb"]
        ),
        "create_inherited_dispatch": (
            "(*shot->bod.bod.vtable)()" in decompiles["create_golb"]
        ),
        "no_primary_body_alias": all(
            "primary_body" not in decompile
            for decompile in decompiles.values()
        ),
    },
}
""",
    )
    observed = response.get("result") if isinstance(response, dict) else None
    expected_bases = [
        {
            "type": "struct RenderableBod",
            "offset": 0,
            "width": 0x80,
        }
    ]
    expected_members = [
        {"name": "vapour", "type": "struct Vapour", "offset": 0x80},
        {
            "name": "vapour_owner_shot",
            "type": "struct GolbShot*",
            "offset": 0x114,
        },
        {
            "name": "tertiary_body",
            "type": "cRGolbRocket",
            "offset": 0x118,
        },
    ]
    aliases = observed.get("aliases") if isinstance(observed, dict) else None
    decompile_checks = (
        observed.get("decompile_checks")
        if isinstance(observed, dict)
        else None
    )
    verified = (
        isinstance(observed, dict)
        and observed.get("width") == 0x2E8
        and observed.get("bases") == expected_bases
        and observed.get("direct_members") == expected_members
        and isinstance(aliases, dict)
        and isinstance(aliases.get("cRSubGolb"), dict)
        and aliases["cRSubGolb"].get("width") == 0x2E8
        and isinstance(aliases.get("cRPathFollowGolb"), dict)
        and aliases["cRPathFollowGolb"].get("width") == 0x28
        and isinstance(decompile_checks, dict)
        and all(decompile_checks.values())
    )
    if not verified:
        raise RuntimeError(
            f"GolbShot inheritance readback failed: {observed!r}"
        )
    return {
        "op": "verify_golb_shot_inheritance",
        "status": "verified",
        "observed": observed,
    }


GOLB_PROTO_UPDATES = (
    (
        "initialize_golb_shot",
        "GolbShot* __thiscall initialize_golb_shot(GolbShot* shot)",
    ),
    (
        "kill_golb",
        "void __thiscall kill_golb(GolbShot* shot)",
    ),
    (
        "update_golb_ai",
        "void __thiscall update_golb_ai(GolbShot* shot)",
    ),
    (
        "create_golb",
        "void __thiscall create_golb(GolbShot* shot, Player* player, int32_t spawn_selector, int32_t emitter_index)",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(Player* owner, Player* shoot_source)",
    ),
    (
        "spawn_golb_trail_sprite",
        "Sprite* __thiscall spawn_golb_trail_sprite(GolbShot* shot, Vec3* position)",
    ),
    (
        "spawn_golb_smoke",
        "void __thiscall spawn_golb_smoke(GolbShot* shot, Vec3* position)",
    ),
    (
        "spawn_golb_impact_sprite",
        "void __thiscall spawn_golb_impact_sprite(GolbShot* shot, Vec3* position)",
    ),
    (
        "initialize_path_follow_golb",
        "int32_t __thiscall initialize_path_follow_golb(GolbPathFollowState* state, cRSubLoc* source_cell, const Vec3* position, GolbShot* shot)",
    ),
    (
        "traverse_path_follow_golb",
        "int32_t __thiscall traverse_path_follow_golb(GolbPathFollowState* state, float path_factor, Vec3* position, Vec3* velocity)",
    ),
)

CUT_SCENE_PROTO_UPDATES = (
    (
        "initialize_cutscene_ai",
        "void __thiscall initialize_cutscene_ai(CutScene* cutscene)",
    ),
    (
        "update_cutscene",
        "void __thiscall update_cutscene(CutScene* cutscene)",
    ),
)

BOD_CORE_PROTO_UPDATES = (
    (
        "add_bod_to_front",
        "void __thiscall add_bod_to_front(BodList* list, BodNode* node)",
    ),
    (
        "append_bod_to_end",
        "void __thiscall append_bod_to_end(BodList* list, BodNode* node)",
    ),
    (
        "is_bod_after_sprites",
        "bool __thiscall is_bod_after_sprites(BodBase* bod)",
    ),
    (
        "set_bod_object",
        "int32_t __thiscall set_bod_object(BodBase* bod, Object* object)",
    ),
    (
        "initialize_bod_base",
        "BodBase* __thiscall initialize_bod_base(BodBase* bod)",
    ),
    (
        "initialize_renderable_bod",
        "RenderableBod* __thiscall initialize_renderable_bod(RenderableBod* body)",
    ),
    (
        "apply_bod_position",
        "Object* __thiscall apply_bod_position(BodBase* bod, TransformMatrix* matrix)",
    ),
    (
        "recycle_bod_to_free_list",
        "void __thiscall recycle_bod_to_free_list(BodList* list, BodNode* node)",
    ),
)

FRINGE_PROTO_UPDATES = (
    (
        "initialize_fringe_object",
        "Fringe* __thiscall initialize_fringe_object(Fringe* fringe)",
    ),
    (
        "refresh_fringe_object_draw_list",
        "void __thiscall refresh_fringe_object_draw_list(Fringe* fringe)",
    ),
    (
        "initialize_fringe_manager",
        "void __thiscall initialize_fringe_manager(FringeManager* manager)",
    ),
    (
        "allocate_fringe_object",
        "Fringe* __thiscall allocate_fringe_object(FringeManager* manager)",
    ),
)

TRACK_RENDER_CACHE_PROTO_UPDATES = (
    (
        "initialize_active_bod",
        "TrackRenderCacheSlot* __thiscall initialize_active_bod(TrackRenderCacheSlot* slot)",
    ),
    (
        "update_active_bod",
        "void __thiscall update_active_bod(TrackRenderCacheSlot* slot)",
    ),
)

ROW_MODEL_PROTO_UPDATES = (
    (
        "update_row_model",
        "void __thiscall update_row_model(RowModel* row_model)",
    ),
)

LANDSCAPE_MANAGER_PROTO_UPDATES = (
    (
        "reset_landscape_manager",
        "void __thiscall reset_landscape_manager(LandscapeManager* manager)",
    ),
    (
        "load_landscape_script_by_name",
        "int32_t __thiscall load_landscape_script_by_name(LandscapeManager* manager, char* script_name)",
    ),
)

SLUG_VOICE_MANAGER_PROTO_UPDATES = (
    (
        "initialize_slug_voice_manager",
        "void __thiscall initialize_slug_voice_manager(SlugVoiceManager* manager)",
    ),
    (
        "update_slug_voice_manager",
        "void __thiscall update_slug_voice_manager(SlugVoiceManager* manager)",
    ),
)

THANKS_SCREEN_PROTO_UPDATES = (
    (
        "initialize_thanks_for_playing_screen",
        "void __thiscall initialize_thanks_for_playing_screen(ThanksScreen* thanks_screen)",
    ),
    (
        "uninit_thanks_screen",
        "void __thiscall uninit_thanks_screen(ThanksScreen* thanks_screen)",
    ),
    (
        "update_thanks_for_playing_screen",
        "void __thiscall update_thanks_for_playing_screen(ThanksScreen* thanks_screen)",
    ),
)

NUKE_PROTO_UPDATES = (
    (
        "initialize_nuke",
        "void __thiscall initialize_nuke(Nuke* nuke)",
    ),
    (
        "update_nuke",
        "void __thiscall update_nuke(Nuke* nuke)",
    ),
    (
        "uninit_nuke",
        "void __thiscall uninit_nuke(Nuke* nuke)",
    ),
)

TIP_PROTO_UPDATES = (
    (
        "kill_tip_widgets",
        "void __thiscall kill_tip_widgets(Tip* tip)",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(Tip* tip, TipData* definition, int32_t hide_disable_button)",
    ),
    ("update_tip", "void __thiscall update_tip(Tip* tip)"),
    (
        "initialize_tip_manager",
        "void __thiscall initialize_tip_manager(TipManager* manager)",
    ),
    (
        "uninit_tips",
        "void __thiscall uninit_tips(TipManager* manager)",
    ),
    (
        "enqueue_tip_message",
        "Tip* __thiscall enqueue_tip_message(TipManager* manager, TipData* definition, int32_t hide_disable_button)",
    ),
    (
        "update_tip_manager",
        "void __thiscall update_tip_manager(TipManager* manager)",
    ),
)

TRACK_NORMALIZATION_VOID_PROTO_UPDATES = (
    (
        "merge_track_tile_runs",
        "void __thiscall merge_track_tile_runs(cRSubGame* game)",
    ),
    (
        "select_track_tile_edge_variants",
        "void __thiscall select_track_tile_edge_variants(cRSubGame* game)",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "void __thiscall promote_track_tiles_to_fringe_variants(cRSubGame* game)",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "void __thiscall harmonize_center_lane_floor_slide_variants(cRSubGame* game)",
    ),
)

PROTO_UPDATES = (
    *GOLB_PROTO_UPDATES,
    *ROW_MODEL_PROTO_UPDATES,
    *LANDSCAPE_MANAGER_PROTO_UPDATES,
    *SLUG_VOICE_MANAGER_PROTO_UPDATES,
    *THANKS_SCREEN_PROTO_UPDATES,
    *NUKE_PROTO_UPDATES,
    *TIP_PROTO_UPDATES,
    *BOD_CORE_PROTO_UPDATES,
    *FRINGE_PROTO_UPDATES,
    *TRACK_RENDER_CACHE_PROTO_UPDATES,
    *TRACK_NORMALIZATION_VOID_PROTO_UPDATES,
    (
        "initialize_noop_renderable_bod",
        "RenderableBod* __thiscall initialize_noop_renderable_bod(RenderableBod* body)",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "cRSubGame* __thiscall initialize_runtime_pools_and_path_template_bank(cRSubGame* game)",
    ),
    (
        "initialize_track_row_runtime",
        "SubRow* __thiscall initialize_track_row_runtime(SubRow* row)",
    ),
    (
        "initialize_object_constructor_thunk",
        "Object* __thiscall initialize_object_constructor_thunk(Object* object)",
    ),
    (
        "initialize_click_start_controller_runtime",
        "ClickStart* __thiscall initialize_click_start_controller_runtime(ClickStart* click_start)",
    ),
    (
        "initialize_click_start",
        "void __thiscall initialize_click_start(ClickStart* click_start, Player* player)",
    ),
    (
        "update_click_start",
        "void __thiscall update_click_start(ClickStart* click_start)",
    ),
    (
        "initialize_active_landscape_entry",
        "ActiveLandscapeEntry* __thiscall initialize_active_landscape_entry(ActiveLandscapeEntry* active_entry)",
    ),
    (
        "activate_landscape_entry",
        "void __thiscall activate_landscape_entry(LandscapeManager* manager, int32_t script_index)",
    ),
    (
        "clear_active_landscape_entries",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager)",
    ),
    (
        "update_active_landscape_entry",
        "void __thiscall update_active_landscape_entry(ActiveLandscapeEntry* active_entry)",
    ),
    (
        "build_track_fringe_mesh",
        "void __thiscall build_track_fringe_mesh(cRPath* self, char* texture_path, float clamp_side)",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "void __thiscall build_track_fringe_supertramp_mesh(cRPath* self, char* texture_path)",
    ),
    (
        "set_color_rgba",
        "tColour* __thiscall set_color_rgba(tColour* color, float r, float g, float b, float a)",
    ),
    (
        "set_color_alpha",
        "void __thiscall set_color_alpha(tColour* color, float alpha)",
    ),
    (
        "set_color_grayscale",
        "void __thiscall set_color_grayscale(tColour* color, float intensity)",
    ),
    (
        "store_color4f",
        "void __thiscall store_color4f(tColour* color, float r, float g, float b, float a)",
    ),
    (
        "set_color_rgb",
        "void __thiscall set_color_rgb(tColour* color, float r, float g, float b)",
    ),
    ("set_color_white", "void __thiscall set_color_white(tColour* color)"),
    ("set_color_black", "void __thiscall set_color_black(tColour* color)"),
    (
        "get_track_skirt_color",
        "tColour* __thiscall get_track_skirt_color(cRSubGame* game, tColour* out)",
    ),
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
        "initialize_sub_loc",
        "cRSubLoc* __thiscall initialize_sub_loc(cRSubLoc* cell)",
    ),
    (
        "remove_sub_loc",
        "void __thiscall remove_sub_loc(cRSubLoc* cell)",
    ),
    (
        "update_sub_loc",
        "void __thiscall update_sub_loc(cRSubLoc* cell)",
    ),
    (
        "get_track_cell_row_index",
        "int32_t __thiscall get_track_cell_row_index(cRSubLoc* cell)",
    ),
    *PATH_MANAGER_PROTO_UPDATES,
    (
        "initialize_player_presentation_controller",
        "Snail* __thiscall initialize_player_presentation_controller(Snail* snail)",
    ),
    (
        "initialize_matrix_from_values",
        "TransformMatrix* __thiscall initialize_matrix_from_values(TransformMatrix* transform, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)",
    ),
    (
        "initialize_quaternion_from_axis",
        "void __thiscall initialize_quaternion_from_axis(Quaternion* out, const AxisAngle* axis)",
    ),
    (
        "initialize_axis_from_quaternion",
        "void __thiscall initialize_axis_from_quaternion(AxisAngle* out, const Quaternion* quaternion)",
    ),
    (
        "initialize_quaternion_from_matrix",
        "Quaternion* __thiscall initialize_quaternion_from_matrix(Quaternion* out, const TransformMatrix* matrix)",
    ),
    (
        "initialize_matrix_from_quaternion",
        "TransformMatrix* __thiscall initialize_matrix_from_quaternion(TransformMatrix* out, const Quaternion* quaternion)",
    ),
    (
        "initialize_global_identity_matrix_thunk",
        "void __cdecl initialize_global_identity_matrix_thunk()",
    ),
    (
        "initialize_global_identity_matrix",
        "void __cdecl initialize_global_identity_matrix()",
    ),
    (
        "initialize_uniform_scale_matrix",
        "TransformMatrix* __thiscall initialize_uniform_scale_matrix(TransformMatrix* transform, float scale)",
    ),
    (
        "multiply_vector_by_matrix_copy",
        "Vec3* __thiscall multiply_vector_by_matrix_copy(const Vec3* vector, Vec3* out, const TransformMatrix* matrix)",
    ),
    (
        "multiply_vector_by_matrix",
        "void __thiscall multiply_vector_by_matrix(Vec3* vector, TransformMatrix matrix)",
    ),
    (
        "rotate_vector_by_matrix",
        "Vec3* __thiscall rotate_vector_by_matrix(Vec3* vector, const TransformMatrix* matrix)",
    ),
    (
        "dot_vectors",
        "double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs)",
    ),
    (
        "dot_vector",
        "float __thiscall dot_vector(const Vec3* vector, const Vec3* rhs)",
    ),
    ("normalize_vector", "float __thiscall normalize_vector(Vec3* vector)"),
    ("vector_magnitude", "float __thiscall vector_magnitude(const Vec3* vector)"),
    (
        "normalize_vector_from_source",
        "float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src)",
    ),
    (
        "cross_vectors",
        "void __thiscall cross_vectors(Vec3* out, const Vec3* lhs, const Vec3* rhs)",
    ),
    (
        "orthogonalize_matrix",
        "void __thiscall orthogonalize_matrix(TransformMatrix* transform)",
    ),
    (
        "invert_matrix_in_place",
        "void __thiscall invert_matrix_in_place(TransformMatrix* transform)",
    ),
    (
        "invert_matrix_from_source",
        "void __thiscall invert_matrix_from_source(TransformMatrix* out, const TransformMatrix* source)",
    ),
    (
        "multiply_matrices",
        "void __thiscall multiply_matrices(TransformMatrix* out, const TransformMatrix* lhs, const TransformMatrix* rhs)",
    ),
    (
        "multiply_matrix_assign",
        "void __thiscall multiply_matrix_assign(TransformMatrix* matrix, const TransformMatrix* rhs)",
    ),
    (
        "multiply_matrix",
        "void __thiscall multiply_matrix(TransformMatrix* matrix, const TransformMatrix* rhs)",
    ),
    (
        "premultiply_matrix_in_place",
        "void __thiscall premultiply_matrix_in_place(TransformMatrix* matrix, const TransformMatrix* lhs)",
    ),
    ("set_matrix_identity", "void __thiscall set_matrix_identity(TransformMatrix* transform)"),
    (
        "set_matrix_rotation_identity",
        "void __thiscall set_matrix_rotation_identity(TransformMatrix* transform)",
    ),
    ("rotate_matrix_local_x", "void __thiscall rotate_matrix_local_x(TransformMatrix* transform, float angle)"),
    ("rotate_matrix_local_y", "void __thiscall rotate_matrix_local_y(TransformMatrix* transform, float angle)"),
    ("rotate_matrix_local_z", "void __thiscall rotate_matrix_local_z(TransformMatrix* transform, float angle)"),
    (
        "set_matrix_z_direction",
        "void __thiscall set_matrix_z_direction(TransformMatrix* transform, const Vec3* direction)",
    ),
    ("look_at_point", "void __thiscall look_at_point(TransformMatrix* transform, const Vec3* target)"),
    (
        "linear_interpolate_matrix",
        "void __thiscall linear_interpolate_matrix(TransformMatrix* out, const TransformMatrix* from, const TransformMatrix* to, float alpha)",
    ),
    (
        "interpolate_matrix_rotation",
        "void __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha)",
    ),
    (
        "compute_kind42_attachment_transform",
        "void __thiscall compute_kind42_attachment_transform(cRPath* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle)",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
    ),
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(AnimManager* manager)",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(AnimManager* manager)",
    ),
    (
        "advance_frame_sequence",
        "void __thiscall advance_frame_sequence(Movie* movie)",
    ),
    (
        "update_smtracks",
        "void __thiscall update_smtracks(Face* face)",
    ),
    (
        "sample_smtrack_heightmap",
        "void __cdecl sample_smtrack_heightmap(Object* source, float base, float scale, TextureRef* replacement, bool cubic)",
    ),
    (
        "deserialize_compact_high_score_record",
        "uint8_t __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
    ),
    (
        "serialize_compact_high_score_record",
        "int32_t __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact)",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(Snail* snail, int32_t shoot_flags)",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state)",
    ),
    (
        "release_snail_weapons",
        "void __thiscall release_snail_weapons(Snail* snail)",
    ),
    (
        "update_snail_presentation",
        "void __thiscall update_snail_presentation(Snail* snail)",
    ),
    *CUT_SCENE_PROTO_UPDATES,
    (
        "dispatch_cutscene_animation",
        "void __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkin* snail_skin)",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkin* snail_skin)",
    ),
    (
        "change_snail_skin",
        "void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds)",
    ),
    (
        "build_snail_world_hotspots",
        "void __thiscall build_snail_world_hotspots(Snail* snail)",
    ),
    (
        "extract_snail_local_hotspots",
        "void __thiscall extract_snail_local_hotspots(Snail* snail)",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
    ),
    (
        "health_collect_particles",
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup)",
    ),
    (
        "set_subgoldy_shoot_flags",
        "void __thiscall set_subgoldy_shoot_flags(Player* player)",
    ),
    (
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player)",
    ),
    (
        "begin_post_follow_carryover",
        "void __thiscall begin_post_follow_carryover(Player* player)",
    ),
    (
        "initialize_subgoldy_ghost",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner)",
    ),
    (
        "update_subgoldy",
        "void __thiscall update_subgoldy(Player* player)",
    ),
    (
        "play_subgoldy_shoot_sfx",
        "void __thiscall play_subgoldy_shoot_sfx(Player* player)",
    ),
    (
        "set_subgoldy_ghost_z",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z)",
    ),
    (
        "add_subgoldy_score",
        "void __thiscall add_subgoldy_score(Player* player, int32_t score_kind, int32_t bonus_score)",
    ),
    (
        "clear_subgoldy_score_buckets",
        "void __thiscall clear_subgoldy_score_buckets(Player* player)",
    ),
    (
        "display_score_stats",
        "void __thiscall display_score_stats(Player* player)",
    ),
    (
        "kill_subgoldy",
        "void __thiscall kill_subgoldy(Player* player)",
    ),
    (
        "initialize_subgoldy_death",
        "void __thiscall initialize_subgoldy_death(Player* player)",
    ),
    (
        "initialize_squidge",
        "void __thiscall initialize_squidge(Squidge* squidge)",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(Squidge* squidge, float value)",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(Squidge* squidge, float value)",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(Squidge* squidge)",
    ),
    (
        "initialize_damage_gauge",
        "void __thiscall initialize_damage_gauge(DamageGuage* damage_guage)",
    ),
    (
        "update_damage_gauge",
        "void __thiscall update_damage_gauge(DamageGuage* damage_guage)",
    ),
    (
        "apply_damage_gauge_delta",
        "void __thiscall apply_damage_gauge_delta(DamageGuage* damage_guage, float delta, bool force)",
    ),
    (
        "update_progress_bar",
        "void __thiscall update_progress_bar(ProgressBar* progress_bar)",
    ),
    (
        "initialize_cameraman",
        "void __thiscall initialize_cameraman(Cameraman* cameraman)",
    ),
    (
        "update_cameraman",
        "void __thiscall update_cameraman(Cameraman* cameraman)",
    ),
    (
        "initialize_warning",
        "void __thiscall initialize_warning(Warning* warning)",
    ),
    (
        "uninit_warning",
        "void __thiscall uninit_warning(Warning* warning)",
    ),
    (
        "start_warning",
        "void __thiscall start_warning(Warning* warning)",
    ),
    (
        "stop_warning",
        "void __thiscall stop_warning(Warning* warning)",
    ),
    (
        "stop_warning_sample",
        "void __thiscall stop_warning_sample(Warning* warning)",
    ),
    (
        "update_warning",
        "void __thiscall update_warning(Warning* warning)",
    ),
    (
        "initialize_jetpack_gauge",
        "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot)",
    ),
    (
        "update_jetpack_gauge",
        "void __thiscall update_jetpack_gauge(SubHover* sub_hover)",
    ),
    (
        "arm_jetpack_gauge",
        "void __thiscall arm_jetpack_gauge(SubHover* sub_hover)",
    ),
    (
        "end_jetpack_hover",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover)",
    ),
    (
        "uninit_jet_particles",
        "void __thiscall uninit_jet_particles(SubHover* sub_hover)",
    ),
    (
        "initialize_jet_particles",
        "void __thiscall initialize_jet_particles(SubHover* sub_hover)",
    ),
    (
        "update_jet_particles",
        "void __thiscall update_jet_particles(SubHover* sub_hover)",
    ),
    (
        "firework_shoot",
        "void __thiscall firework_shoot(FireWork* firework, Vec3* position, int32_t owner, int32_t texture_id, int32_t count)",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner)",
    ),
    (
        "update_barrier_ai",
        "void __thiscall update_barrier_ai(BarrierActor* barrier)",
    ),
    ("update_input_ok", "void __thiscall update_input_ok(InputOkState* input_ok)"),
    (
        "initialize_input_ok",
        "void __thiscall initialize_input_ok(InputOkState* input_ok)",
    ),
    ("draw_twinkle", "void __thiscall draw_twinkle(Twinkle* twinkle)"),
    ("update_twinkle", "void __thiscall update_twinkle(Twinkle* twinkle)"),
    (
        "update_twinkle_manager",
        "void __thiscall update_twinkle_manager(TwinkleManager* manager)",
    ),
    (
        "initialize_track_speedup_runtime",
        "SubSpeedUp* __thiscall initialize_track_speedup_runtime(SubSpeedUp* speedup)",
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
        "initialize_track_health_pickup_runtime",
        "SubHealth* __thiscall initialize_track_health_pickup_runtime(SubHealth* pickup)",
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
        "handle_subgoldy_collisions",
        "void __thiscall handle_subgoldy_collisions(Player* player)",
    ),
    (
        "initialize_subgoldy_resurrect",
        "void __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss)",
    ),
    (
        "initialize_tutorial",
        "void __thiscall initialize_tutorial(Tutorial* tutorial)",
    ),
    (
        "uninit_tutorial",
        "void __thiscall uninit_tutorial(Tutorial* tutorial)",
    ),
    (
        "update_tutorial",
        "void __thiscall update_tutorial(Tutorial* tutorial)",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(Invincible* invincible)",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(Invincible* invincible)",
    ),
    ("update_invincible_shell", "void __thiscall update_invincible_shell(Invincible* invincible)"),
)

# The full cRSubGame and Player field maps above are the canonical owner
# views consumed by these lifecycle and level-builder functions. These
# prototypes are replayed through the direct verified batch because older BN
# analysis can otherwise restore an inferred but ABI-equivalent fastcall label.
GOLDY_PATH_FOLLOW_PROTO_UPDATES = (
    (
        "begin_track_attachment_follow_state",
        "void __thiscall begin_track_attachment_follow_state(cRPathFollowGoldy* follow_state, cRSubLoc* source_cell, const Vec3* world_position, Player* player)",
    ),
    (
        "update_track_attachment_follow_state",
        "int32_t __thiscall update_track_attachment_follow_state(cRPathFollowGoldy* follow_state, float path_factor, Vec3* out_position, Vec3* motion)",
    ),
)

CORE_SUBGAME_PROTO_UPDATES = (
    (
        "calc_slider_to_rate",
        "float __thiscall calc_slider_to_rate(cRSubGame* game, float slider)",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(cRSubGame* game)",
    ),
    (
        "advance_blink_random",
        "double __thiscall advance_blink_random(cRSubGame* game)",
    ),
    (
        "initialize_blink_random",
        "void __thiscall initialize_blink_random(cRSubGame* game)",
    ),
    (
        "hide_gameplay_scores",
        "void __thiscall hide_gameplay_scores(cRSubGame* game)",
    ),
    (
        "unhide_gameplay_scores",
        "void __thiscall unhide_gameplay_scores(cRSubGame* game)",
    ),
    (
        "update_subgoldy_resurrect",
        "void __thiscall update_subgoldy_resurrect(Player* player)",
    ),
    ("reset_subgame", "void __thiscall reset_subgame(cRSubGame* game)"),
    (
        "complete_subgame",
        "void __thiscall complete_subgame(cRSubGame* game, uint8_t completed)",
    ),
    (
        "mark_track_warning_zones",
        "void __thiscall mark_track_warning_zones(cRSubGame* game)",
    ),
    (
        "is_neighbor_cell_solid",
        "bool __thiscall is_neighbor_cell_solid(cRSubGame* game, cRSubLoc* cell, int32_t lane_offset, int32_t row_offset)",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "void __thiscall try_enter_track_attachment_from_swept_motion(cRPath* self, float world_x, float world_y, float world_z, float sweep_dx, float sweep_dy, float sweep_dz, cRSubLoc* source_cell)",
    ),
    (
        "get_path_position_at_node",
        "void __thiscall get_path_position_at_node(cRPath* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local)",
    ),
    (
        "is_point_inside_track_attachment",
        "bool __thiscall is_point_inside_track_attachment(cRPath* self, Vec3 probe, Vec3 swept_motion, cRSubLoc* cell)",
    ),
    *GOLDY_PATH_FOLLOW_PROTO_UPDATES,
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(cRSubGame* game)",
    ),
    (
        "place_parcels_on_track",
        "void __thiscall place_parcels_on_track(cRSubGame* game)",
    ),
    (
        "place_challenge_parcels_on_track",
        "void __thiscall place_challenge_parcels_on_track(cRSubGame* game)",
    ),
)

# These remaining lifecycle, track-cache, and runtime lookup receivers already
# have their semantic owners in the matching/cross-port evidence. Older BN
# databases pin a separate user-defined Game* parameter variable on them. Both
# the previewed prototype setter and local retype API reject the owner-only
# correction, so report the drift instead of claiming a mutation that analysis
# immediately restores. The guarded repair catalog handles only the exact known
# stale identities and defaults to a read-only inspection because function
# recreation is not covered by ordinary Binary Ninja undo.
DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (
    ("initialize_subgame", "void __thiscall initialize_subgame(cRSubGame* game)"),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(cRSubGame* game, int32_t level_index)",
    ),
    ("destroy_subgame", "void __thiscall destroy_subgame(cRSubGame* game)"),
    ("update_subgame", "void __thiscall update_subgame(cRSubGame* game)"),
    ("remove_subgame_bods", "void __thiscall remove_subgame_bods(cRSubGame* game)"),
    (
        "build_track_fringe_objects",
        "void __thiscall build_track_fringe_objects(cRSubGame* game)",
    ),
    (
        "get_track_grid_cell_at_world_position",
        "cRSubLoc* __thiscall get_track_grid_cell_at_world_position(cRSubGame* game, Vec3* position)",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(cRSubGame* game, Vec3* position)",
    ),
    (
        "spawn_track_health_pickup",
        "void __thiscall spawn_track_health_pickup(cRSubGame* game, cRSubLoc* cell, Player* player)",
    ),
    (
        "spawn_track_jetpack_pickup",
        "void __thiscall spawn_track_jetpack_pickup(cRSubGame* game, cRSubLoc* cell, Player* player)",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "SubRow* __thiscall get_track_runtime_cell_at_world_z(cRSubGame* game, Vec3* position)",
    ),
    (
        "project_position_onto_track_attachment",
        "void __thiscall project_position_onto_track_attachment(cRSubGame* game, Vec3* position, float* out_angle)",
    ),
)

SUBGAME_OWNER_COMPAT_PROTO_UPDATES = (
    (
        "bind_subgame_owner",
        "cRSubGame* __thiscall bind_subgame_owner(SubgameOwnerLink* owner)",
    ),
    (
        "build_track_colours",
        "void __thiscall build_track_colours(cRSubGame* game)",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(cRSubGame* game, cRSubLoc* cell, Player* player)",
    ),
    (
        "spawn_slug_hazard",
        "void __thiscall spawn_slug_hazard(cRSubGame* game, cRSubLoc* cell, Player* owner_player)",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "void __thiscall spawn_track_ring_or_special_effect(cRSubGame* game, cRSubLoc* cell, int32_t requested_kind, Player* player, float ring_speed)",
    ),
)

# Every Windows child owner/backpointer currently proved to reach the embedded
# GameRoot::subgame object. Some types live in separate narrow headers, so the
# focused migration updates each one only when that owner has already been
# recovered in the target database. Their own replay scripts use cRSubGame too,
# keeping a fresh database canonical when those slices are introduced later.
SUBGAME_BACKPOINTER_STRUCT_UPDATES = (
    ("Cameraman", (("0xc4", "game", "cRSubGame*"),)),
    ("GarbageHazardRuntime", (("0x8c", "game", "cRSubGame*"),)),
    ("GarbageHazardSlot", (("0x8c", "owner_game", "cRSubGame*"),)),
    ("GolbShot", (("0x270", "game", "cRSubGame*"),)),
    ("GolbShotFlightStrideCursor", (("0xac", "game", "cRSubGame*"),)),
    ("Player", (("0x408", "game", "cRSubGame*"),)),
    ("Salt", (("0x88", "owner_game", "cRSubGame*"),)),
    ("SegmentCache", (("0x54", "owner_subgame", "cRSubGame*"),)),
    ("Slug", (("0x88", "owner_game", "cRSubGame*"),)),
    ("SlugHazardRuntime", (("0x88", "owner_game", "cRSubGame*"),)),
    ("SubGarbage", (("0x8c", "owner_game", "cRSubGame*"),)),
    ("SubHealth", (("0x44", "owner_game", "cRSubGame*"),)),
    ("SubHover", (("0x200", "game", "cRSubGame*"),)),
    ("SubLazer", (("0x88", "owner_game", "cRSubGame*"),)),
    ("SubRing", (("0x1d0", "rate_source", "cRSubGame*"),)),
    ("SubSpeedUp", (("0x8c", "owner_game", "cRSubGame*"),)),
    ("SubgameOwnerLink", (("0x00", "game", "cRSubGame*"),)),
    ("TrackHealthPickup", (("0x44", "owner_game", "cRSubGame*"),)),
    ("TrackJetpackPickup", (("0x44", "owner_game", "cRSubGame*"),)),
    ("TrackSpeedupRuntime", (("0x8c", "owner_game", "cRSubGame*"),)),
    ("Tutorial", (("0x0c", "game", "cRSubGame*"),)),
    ("Parcel", (("0x3c", "owner_subgame", "cRSubGame*"),)),
    ("JetPack", (("0x44", "owner_game", "cRSubGame*"),)),
    ("Banner", (("0x48", "owner_game", "cRSubGame*"),)),
    (
        "SubLazerBodyObjectStrideCursor",
        (("0x64", "owner_game", "cRSubGame*"),),
    ),
    ("SaltOwnerGameStrideCursor", (("0x00", "owner_game", "cRSubGame*"),)),
    ("GUI", (("0x00", "game", "cRSubGame*"),)),
    ("ThanksScreen", (("0x00", "game", "cRSubGame*"),)),
    ("Galaxy", (("0x10f70", "level_progress_base", "cRSubGame*"),)),
)

# These functions retain a user-defined ECX parameter even after their owner
# UDT becomes a compatibility alias. Once cRSubGame is present, retyping only
# that exact receiver preserves every independently audited local lifetime and
# lets Binary Ninja render the canonical member ABI without function recreation.
SUBGAME_RECEIVER_USER_VAR_UPDATES = tuple(
    (
        identifier,
        "RegisterVariableSourceType",
        0,
        67,
        "game",
        "cRSubGame*",
    )
    for identifier, _prototype in DEFERRED_SUBGAME_OWNER_PROTO_UPDATES
) + tuple(
    (
        identifier,
        "RegisterVariableSourceType",
        0,
        67,
        "game",
        "cRSubGame*",
    )
    for identifier, _prototype in SUBGAME_OWNER_COMPAT_PROTO_UPDATES
    if identifier != "bind_subgame_owner"
)

REFINED_PATH_OWNER_PROTO_UPDATES = (
    (
        "initialize_looptheloop_path_template_pair",
        "void __thiscall initialize_looptheloop_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_looptheloop_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_looptheloopw_path_template_pair",
        "void __thiscall initialize_looptheloopw_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_looptheloopw_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_loopout_path_template_pair",
        "void __thiscall initialize_loopout_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_loopout_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_hump_path_template_pair",
        "void __thiscall initialize_hump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_hump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_dump_path_template_pair",
        "void __thiscall initialize_dump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_dump_path_template_pair(cRPath* self, float curve_source, float height_scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "void __thiscall initialize_halfpipe_path_template_pair(cRPath* self, float scale, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_halfpipe_path_template_pair(cRPath* self, float scale, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_dip_path_template_pair",
        "void __thiscall initialize_dip_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_dip_path_template_pair(cRPath* self, float curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_screw_path_template_pair",
        "void __thiscall initialize_screw_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_screw_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_slalom_path_template_pair",
        "void __thiscall initialize_slalom_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_slalom_path_template_pair(cRPath* self, int32_t curve_source, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_slalombig_path_template_pair",
        "void __thiscall initialize_slalombig_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_slalombig_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_sweep_path_template_pair",
        "void __thiscall initialize_sweep_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_sweep_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_snake_path_template_pair",
        "void __thiscall initialize_snake_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_snake_path_template_pair(cRPath* self, float scale_arg, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_slalomdouble_path_template_pair",
        "void __thiscall initialize_slalomdouble_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_slalomdouble_path_template_pair(cRPath* self, int32_t curve_segments, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_start_path_template_pair",
        "void __thiscall initialize_start_path_template_pair(cRPath* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_start_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_turnover_path_template_pair",
        "void __thiscall initialize_turnover_path_template_pair(cRPath* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_turnover_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_turnoverdouble_path_template_pair",
        "void __thiscall initialize_turnoverdouble_path_template_pair(cRPath* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* cap_texture)",
        "void __thiscall initialize_turnoverdouble_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "initialize_turnunder_path_template_pair",
        "void __thiscall initialize_turnunder_path_template_pair(cRPath* self, float turns, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_turnunder_path_template_pair(cRPath* self, float turns, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_wibble_path_template_pair",
        "void __thiscall initialize_wibble_path_template_pair(cRPath* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_wibble_path_template_pair(cRPath* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_invert_path_template_pair",
        "void __thiscall initialize_invert_path_template_pair(cRPath* self, float radius, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_invert_path_template_pair(cRPath* self, float radius, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_supertramp_path_template_pair",
        "void __thiscall initialize_supertramp_path_template_pair(cRPath* self, float length, int32_t width_cells_, int32_t side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture)",
        "void __thiscall initialize_supertramp_path_template_pair(cRPath* self, float length, int32_t width_cells_, bool side_exit, char* texture_a, char* texture_b, char* unused_texture, char* cap_texture)",
    ),
    (
        "initialize_twister_path_template_pair",
        "void __thiscall initialize_twister_path_template_pair(cRPath* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_twister_path_template_pair(cRPath* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_twister2_path_template_pair",
        "void __thiscall initialize_twister2_path_template_pair(cRPath* self, float height, int32_t width_cells_, char handedness, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_twister2_path_template_pair(cRPath* self, float height, int32_t width_cells_, bool handedness, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_loopbow_path_template_pair",
        "void __thiscall initialize_loopbow_path_template_pair(cRPath* self, float curve_scale, uint32_t width_cells_arg, char mode, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_loopbow_path_template_pair(cRPath* self, float curve_scale, uint32_t width_cells_arg, bool mode, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_toad_path_template_pair",
        "void __thiscall initialize_toad_path_template_pair(cRPath* self, char turn_left, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_toad_path_template_pair(cRPath* self, bool turn_left, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_hill_valley_path_template_pair",
        "void __thiscall initialize_hill_valley_path_template_pair(cRPath* self, int32_t width_cells_, float height, float length, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_hill_valley_path_template_pair(cRPath* self, int32_t width_cells_, float height, float length, bool centered, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "initialize_sbend_path_template_pair",
        "void __thiscall initialize_sbend_path_template_pair(cRPath* self, int32_t width_cells_, float height, float z_amplitude, char centered, char* texture_a, char* texture_b, char* vertical_texture)",
        "void __thiscall initialize_sbend_path_template_pair(cRPath* self, int32_t width_cells_, float height, float z_amplitude, bool centered, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
)

DEFERRED_PATH_OWNER_PROTO_UPDATES = (
    (
        "initialize_p_path_template_pair",
        "void __thiscall initialize_p_path_template_pair(cRPath* self, int32_t variant, float scale_arg, int32_t width_cells_, float start_x, float end_x, int32_t curve_segments, char* texture_a, char* texture_b, char* cap_texture)",
    ),
    (
        "get_path_nodes",
        "void __fastcall get_path_nodes(cRPath* self)",
    ),
    (
        "calc_path_length_z",
        "void __fastcall calc_path_length_z(cRPath* self)",
    ),
    (
        "initialize_worm_path_template_pair",
        "void __thiscall initialize_worm_path_template_pair(cRPath* self, char* texture_path)",
    ),
    (
        "initialize_cage2_path_template_pair",
        "void __thiscall initialize_cage2_path_template_pair(cRPath* self, int32_t width_cells_, char* texture_a, char* texture_b, char* vertical_texture)",
    ),
    (
        "mirror_path",
        "void __thiscall mirror_path(cRPath* self, cRPath* source)",
    ),
)

PATH_OWNER_REANALYSIS_CONSUMERS = (
    "initialize_runtime_pools_and_path_template_bank",
    "initialize_game_assets_and_world",
    "begin_track_attachment_follow_state",
    "update_track_attachment_follow_state",
    "initialize_path_follow_golb",
    "traverse_path_follow_golb",
    "populate_runtime_track_cells_from_segments",
    "load_segment_definitions",
    "project_position_onto_track_attachment",
    "place_parcels_on_track",
    "place_challenge_parcels_on_track",
    "update_subgoldy",
    "update_cameraman",
)

SUB_LOC_OWNER_REANALYSIS_CONSUMERS = (
    "initialize_runtime_pools_and_path_template_bank",
    "initialize_sub_loc",
    "is_sub_loc_floor",
    "is_sub_loc_ramp",
    "is_sub_loc_empty",
    "is_sub_loc_slide",
    "remove_sub_loc",
    "update_sub_loc",
    "get_track_cell_row_index",
    "get_track_grid_cell_at_world_position",
    "is_neighbor_cell_solid",
    "sample_track_floor_height_at_position",
    "begin_track_attachment_follow_state",
    "update_track_attachment_follow_state",
    "initialize_path_follow_golb",
    "try_enter_track_attachment_from_swept_motion",
    "is_point_inside_track_attachment",
    "populate_runtime_track_cells_from_segments",
    "build_track_render_caches",
    "build_track_fringe_objects",
    "remove_subgame_bods",
    "update_subgoldy",
    "update_golb_ai",
)

SUBGAME_OWNER_REANALYSIS_CONSUMERS = (
    "construct_game_runtime",
    "run_frame_update",
    "initialize_game_assets_and_world",
    "initialize_runtime_pools_and_path_template_bank",
    "build_track_render_caches",
    "initialize_jetpack_gauge",
    "initialize_tutorial",
    "create_golb",
    "update_golb_ai",
    "update_subgoldy",
    "handle_subgoldy_collisions",
    "update_ring_or_special_effect_parent",
    "update_slug_hazard_ai",
    "update_garbage_hazard",
    "update_track_health_pickup",
    "update_track_jetpack_pickup",
    "update_track_parcel",
    "update_tutorial",
)


def collect_c_r_path_owner_proto_updates() -> tuple[tuple[str, str], ...]:
    """Collect every Windows cRPath receiver ABI from the canonical replay."""

    updates: dict[str, str] = {
        identifier: prototype
        for identifier, prototype in PROTO_UPDATES
        if "cRPath*" in prototype
    }
    updates.update(
        {
            identifier: prototype
            for identifier, prototype in CORE_SUBGAME_PROTO_UPDATES
            if "cRPath*" in prototype
        }
    )
    updates.update(
        {
            identifier: refined_prototype
            for identifier, _stale_prototype, refined_prototype
            in REFINED_PATH_OWNER_PROTO_UPDATES
        }
    )
    updates.update(dict(DEFERRED_PATH_OWNER_PROTO_UPDATES))
    return tuple(updates.items())


def collect_c_r_subgame_owner_proto_updates() -> tuple[tuple[str, str], ...]:
    """Collect every directly replayable Windows cRSubGame receiver ABI."""

    updates: dict[str, str] = dict(SUBGAME_OWNER_COMPAT_PROTO_UPDATES)
    for proto_updates in (
        PROTO_UPDATES,
        CORE_SUBGAME_PROTO_UPDATES,
    ):
        updates.update(
            {
                identifier: prototype
                for identifier, prototype in proto_updates
                if "cRSubGame*" in prototype
            }
        )
    return tuple(updates.items())


def collect_c_r_subgame_backpointer_struct_updates(
    *, target: str
) -> tuple[tuple[str, tuple[tuple[str, str, str], ...]], ...]:
    """Collect canonical child backpointers from owner types present in BN."""

    return tuple(
        (struct_name, updates)
        for struct_name, updates in SUBGAME_BACKPOINTER_STRUCT_UPDATES
        if struct_exists(REPO_ROOT, target=target, struct_name=struct_name)
    )


def collect_c_r_sub_loc_owner_proto_updates() -> tuple[tuple[str, str], ...]:
    """Collect every directly replayable Windows cRSubLoc ABI."""

    updates: dict[str, str] = {}
    for proto_updates in (
        PROTO_UPDATES,
        GOLB_PROTO_UPDATES,
        CORE_SUBGAME_PROTO_UPDATES,
    ):
        updates.update(
            {
                identifier: prototype
                for identifier, prototype in proto_updates
                if "cRSubLoc*" in prototype
            }
        )
    return tuple(updates.items())


def collect_deferred_c_r_sub_loc_owner_proto_updates(
) -> tuple[tuple[str, str], ...]:
    """Collect guarded owner ABIs that require the established repair lane."""

    return tuple(
        (identifier, prototype)
        for identifier, prototype in DEFERRED_SUBGAME_OWNER_PROTO_UPDATES
        if "cRSubLoc*" in prototype
    )


def report_deferred_owner_prototypes(
    *,
    target: str,
    updates: tuple[tuple[str, str], ...],
    stale_identity_reason: str,
) -> list[dict[str, object]]:
    observed_prototypes = current_prototypes(
        REPO_ROOT,
        target=target,
        identifiers=(identifier for identifier, _prototype in updates),
    )
    results = []
    for identifier, prototype in updates:
        observed = observed_prototypes.get(identifier)
        current = observed is not None and normalize_prototype(
            observed,
            identifier=identifier,
        ) == normalize_prototype(prototype, identifier=identifier)
        result = {
            "op": "proto_owner_current" if current else "proto_owner_deferred",
            "status": "skipped" if current else "deferred",
            "reason": (
                "already current"
                if current
                else stale_identity_reason
            ),
            "identifier": identifier,
            "desired_prototype": prototype,
            "observed_prototype": observed,
        }
        if not current:
            result["repair_command"] = (
                "uv run tools/binja/repair_deferred_owner_abi.py "
                f"--target {target} --function {identifier} --apply"
            )
        results.append(result)
    return results


def apply_refined_owner_prototypes(
    *,
    target: str,
    updates: tuple[tuple[str, str, str], ...],
) -> list[dict[str, object]]:
    observed_prototypes = current_prototypes(
        REPO_ROOT,
        target=target,
        identifiers=(identifier for identifier, _previous, _desired in updates),
    )
    results: list[dict[str, object]] = []
    for identifier, previous_prototype, desired_prototype in updates:
        observed = observed_prototypes.get(identifier)
        observed_normalized = (
            normalize_prototype(observed, identifier=identifier)
            if observed is not None
            else None
        )
        desired_normalized = normalize_prototype(
            desired_prototype,
            identifier=identifier,
        )
        previous_normalized = normalize_prototype(
            previous_prototype,
            identifier=identifier,
        )
        if observed_normalized == desired_normalized:
            results.append(
                {
                    "op": "proto_owner_refinement",
                    "status": "skipped",
                    "reason": "already current",
                    "identifier": identifier,
                    "prototype": desired_prototype,
                }
            )
        elif observed_normalized == previous_normalized:
            results.extend(
                apply_proto_updates(
                    REPO_ROOT,
                    target=target,
                    updates=((identifier, desired_prototype),),
                )
            )
        else:
            results.append(
                {
                    "op": "proto_owner_refinement",
                    "status": "deferred",
                    "reason": (
                        "owner ABI is not the exact previously recovered form; "
                        "guarded function recreation remains required"
                    ),
                    "identifier": identifier,
                    "previous_prototype": previous_prototype,
                    "desired_prototype": desired_prototype,
                    "observed_prototype": observed,
                    "repair_command": (
                        "uv run tools/binja/repair_deferred_owner_abi.py "
                        f"--target {target} --function {identifier} --apply"
                    ),
                }
            )
    return results


def _has_verified_mutation(results: list[dict[str, object]]) -> bool:
    """Report whether a narrow replay changed an owner or prototype."""

    def contains_verified_mutation(value: object) -> bool:
        if isinstance(value, dict):
            if value.get("status") == "verified" or value.get("verified") is True:
                return True
            return any(contains_verified_mutation(item) for item in value.values())
        if isinstance(value, list):
            return any(contains_verified_mutation(item) for item in value)
        return False

    return contains_verified_mutation(results)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the authoritative path/presentation ownership slice to a Binary Ninja "
            "target and replay the proven Player and cRSubGame field overlays."
        )
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
        help="Path to the authoritative ownership type-import header.",
    )
    focused_group = parser.add_mutually_exclusive_group()
    focused_group.add_argument(
        "--bod-core-only",
        action="store_true",
        help=(
            "Replay only the intrusive BodNode/BodList layouts and shared "
            "BodBase lifecycle ABIs."
        ),
    )
    focused_group.add_argument(
        "--fringe-only",
        action="store_true",
        help=(
            "Replay only the authored Fringe/FringeManager layouts, borrowed "
            "cell pointers, and lifecycle method ABIs."
        ),
    )
    focused_group.add_argument(
        "--golb-only",
        action="store_true",
        help="Replay only the GolbShot/path-follow ownership slice.",
    )
    focused_group.add_argument(
        "--goldy-path-follow-only",
        action="store_true",
        help=(
            "Replay only the authored cRPathFollowGoldy type, embedded Player "
            "field, and Init/Traverse method ABIs."
        ),
    )
    focused_group.add_argument(
        "--path-owner-only",
        action="store_true",
        help=(
            "Replay only the authored cRPath type, embedded path borrows, "
            "and Windows path-member ABIs."
        ),
    )
    focused_group.add_argument(
        "--subgame-owner-only",
        action="store_true",
        help=(
            "Replay only the authored cRSubGame type, compatibility alias, "
            "GameRoot embed, and directly writable Windows member ABIs."
        ),
    )
    focused_group.add_argument(
        "--sub-loc-owner-only",
        action="store_true",
        help=(
            "Replay only the authored cRSubLoc type, runtime-grid embeds, "
            "borrowed cell links, and directly writable Windows member ABIs."
        ),
    )
    focused_group.add_argument(
        "--path-manager-only",
        action="store_true",
        help=(
            "Replay only the authored cRPathManager type, embedded "
            "cRSubGame field, and NameCode(char*) method ABI."
        ),
    )
    focused_group.add_argument(
        "--cut-scene-only",
        action="store_true",
        help="Replay only the CutScene state owner and its two method prototypes.",
    )
    focused_group.add_argument(
        "--nuke-only",
        action="store_true",
        help="Replay only the exact cRNuke owner and its lifecycle method ABIs.",
    )
    focused_group.add_argument(
        "--tip-only",
        action="store_true",
        help="Replay only the exact cRTip/cRTipManager owner graph and lifecycle ABIs.",
    )
    focused_group.add_argument(
        "--track-cache-only",
        action="store_true",
        help=(
            "Replay only the TrackRenderCacheSlot layout, lifecycle prototypes, "
            "and callback table."
        ),
    )
    focused_group.add_argument(
        "--row-model-only",
        action="store_true",
        help="Replay only the RowModel layout and per-frame callback ABI.",
    )
    focused_group.add_argument(
        "--thanks-screen-only",
        action="store_true",
        help="Replay only the ThanksScreen layout and lifecycle method ABIs.",
    )
    focused_group.add_argument(
        "--landscape-loader-only",
        action="store_true",
        help="Replay only the LandscapeManager reset and cache-loader method ABIs.",
    )
    focused_group.add_argument(
        "--update-subgoldy-only",
        action="store_true",
        help=(
            "Replay only update_subgoldy's one-based row-event segment view "
            "and its existing time-trial record cursor."
        ),
    )
    focused_group.add_argument(
        "--update-subgame-only",
        action="store_true",
        help=(
            "Replay only update_subgame's runtime row/cell cursors, active-list "
            "row borrow, and time-trial route cursor."
        ),
    )
    focused_group.add_argument(
        "--build-subgame-only",
        action="store_true",
        help=(
            "Replay only build_subgame_level's embedded presentation owners "
            "and borrowed active-Bod list lifetimes."
        ),
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    if args.subgame_owner_only:
        subgame_owner_type_result = ensure_c_r_subgame_owner_types(
            target=args.target,
            header_path=header_path,
        )
        operations.append(subgame_owner_type_result)
        subgame_owner_proto_updates = collect_c_r_subgame_owner_proto_updates()
        subgame_backpointer_updates = (
            collect_c_r_subgame_backpointer_struct_updates(target=args.target)
        )
        subgame_owner_results = apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("cRSubGame", SUBGAME_RUNTIME_FIELD_UPDATES),
                ("GameRoot", (("0x74618", "subgame", "cRSubGame"),)),
                *subgame_backpointer_updates,
            ),
            proto_updates=subgame_owner_proto_updates,
        )
        operations.extend(subgame_owner_results)
        subgame_receiver_results = apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SUBGAME_RECEIVER_USER_VAR_UPDATES,
        )
        operations.extend(subgame_receiver_results)
        operations.extend(
            report_deferred_owner_prototypes(
                target=args.target,
                updates=DEFERRED_SUBGAME_OWNER_PROTO_UPDATES,
                stale_identity_reason=(
                    "the legacy SubgameRuntime or Game receiver needs the "
                    "guarded recreation lane before cRSubGame can persist"
                ),
            )
        )
        if _has_verified_mutation(
            [
                subgame_owner_type_result,
                *subgame_owner_results,
                *subgame_receiver_results,
            ]
        ):
            operations.extend(
                reanalyze_functions(
                    REPO_ROOT,
                    target=args.target,
                    identifiers=tuple(
                        dict.fromkeys(
                            (
                                *(
                                    identifier
                                    for identifier, _prototype
                                    in subgame_owner_proto_updates
                                ),
                                *(
                                    identifier
                                    for identifier, _prototype
                                    in DEFERRED_SUBGAME_OWNER_PROTO_UPDATES
                                ),
                                *SUBGAME_OWNER_REANALYSIS_CONSUMERS,
                            )
                        )
                    ),
                )
            )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.path_owner_only:
        path_owner_type_result = ensure_c_r_path_owner_types(
            target=args.target,
            header_path=header_path,
        )
        operations.append(path_owner_type_result)
        path_owner_proto_updates = collect_c_r_path_owner_proto_updates()
        path_owner_results = apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("cRPath", PATH_FIELD_UPDATES),
                ("PathPair", PATH_PAIR_FIELD_UPDATES),
                (
                    "cRSubLoc",
                    (("0x38", "attachment_template_record", "cRPath*"),),
                ),
                (
                    "GolbPathFollowState",
                    (("0x04", "template_record", "cRPath*"),),
                ),
                (
                    "cRPathFollowGoldy",
                    (("0x04", "template_record", "cRPath*"),),
                ),
            ),
            proto_updates=path_owner_proto_updates,
        )
        operations.extend(path_owner_results)
        if _has_verified_mutation(
            [path_owner_type_result, *path_owner_results]
        ):
            operations.extend(
                reanalyze_functions(
                    REPO_ROOT,
                    target=args.target,
                    identifiers=tuple(
                        dict.fromkeys(
                            (
                                *(
                                    identifier
                                    for identifier, _prototype
                                    in path_owner_proto_updates
                                ),
                                *PATH_OWNER_REANALYSIS_CONSUMERS,
                            )
                        )
                    ),
                )
            )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.sub_loc_owner_only:
        sub_loc_owner_type_result = ensure_c_r_sub_loc_owner_types(
            target=args.target,
            header_path=header_path,
        )
        operations.append(sub_loc_owner_type_result)
        sub_loc_dependent_view_result = (
            ensure_c_r_sub_loc_dependent_view_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(sub_loc_dependent_view_result)
        sub_loc_owner_proto_updates = collect_c_r_sub_loc_owner_proto_updates()
        sub_loc_owner_results = apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("cRSubLoc", SUB_LOC_FIELD_UPDATES),
                (
                    "cRSubGame",
                    (("0x3bfac8", "runtime_cells", "cRSubLoc[0xc80][8]"),),
                ),
                (
                    "SubRow",
                    (
                        ("0xa4", "primary_attachment_cell", "cRSubLoc*"),
                        ("0xa8", "secondary_attachment_cell", "cRSubLoc*"),
                    ),
                ),
                (
                    "GolbPathFollowState",
                    (("0x08", "source_cell", "cRSubLoc*"),),
                ),
                (
                    "cRPathFollowGoldy",
                    (("0x08", "source_cell", "cRSubLoc*"),),
                ),
                ("JetPack", (("0x68", "source_cell", "cRSubLoc*"),)),
                ("SubHealth", (("0x68", "source_cell", "cRSubLoc*"),)),
                ("Slug", (("0xb0", "source_cell", "cRSubLoc*"),)),
                ("SubGarbage", (("0xb8", "source_cell", "cRSubLoc*"),)),
            ),
            proto_updates=sub_loc_owner_proto_updates,
        )
        operations.extend(sub_loc_owner_results)
        operations.extend(
            report_deferred_owner_prototypes(
                target=args.target,
                updates=collect_deferred_c_r_sub_loc_owner_proto_updates(),
                stale_identity_reason=(
                    "the exact cRSubGame receiver needs the established "
                    "guarded recreation lane before its cRSubLoc borrow can "
                    "be persisted"
                ),
            )
        )
        if _has_verified_mutation(
            [
                sub_loc_owner_type_result,
                sub_loc_dependent_view_result,
                *sub_loc_owner_results,
            ]
        ):
            operations.extend(
                reanalyze_functions(
                    REPO_ROOT,
                    target=args.target,
                    identifiers=SUB_LOC_OWNER_REANALYSIS_CONSUMERS,
                )
            )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.path_manager_only:
        operations.append(
            ensure_c_r_path_manager_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        path_manager_results = apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("cRPathManager", PATH_MANAGER_FIELD_UPDATES),
                (
                    "cRSubGame",
                    (("0xff2910", "path_manager", "cRPathManager"),),
                ),
            ),
            proto_updates=PATH_MANAGER_PROTO_UPDATES,
        )
        operations.extend(path_manager_results)
        if _has_verified_mutation(path_manager_results):
            operations.extend(
                reanalyze_functions(
                    REPO_ROOT,
                    target=args.target,
                    identifiers=(
                        "find_segment_path_index_by_name",
                        "load_segment_definitions",
                    ),
                )
            )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.goldy_path_follow_only:
        operations.append(
            ensure_goldy_path_follow_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.extend(
            apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    (
                        "cRPathFollowGoldy",
                        GOLDY_PATH_FOLLOW_FIELD_UPDATES,
                    ),
                    (
                        "Player",
                        GOLDY_PATH_FOLLOW_PLAYER_FIELD_UPDATES,
                    ),
                ),
                proto_updates=GOLDY_PATH_FOLLOW_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.bod_core_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=tuple(BOD_CORE_OWNER_SIZES),
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=BOD_CORE_SYMBOL_UPDATES,
            )
        )
        operations.extend(
            apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("BodNode", BOD_NODE_FIELD_UPDATES),
                    ("BodList", BOD_LIST_FIELD_UPDATES),
                    ("BodBase", BOD_BASE_FIELD_UPDATES),
                    ("RenderableBod", RENDERABLE_BOD_FIELD_UPDATES),
                ),
                proto_updates=BOD_CORE_PROTO_UPDATES,
            )
        )
        operations.extend(
            apply_data_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=BOD_CORE_DATA_VAR_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.fringe_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=(
                    *BOD_CORE_OWNER_SIZES,
                    *FRINGE_OWNER_SIZES,
                    "cRSubLoc",
                ),
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.append(verify_fringe_owner_sizes(target=args.target))
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=FRINGE_SYMBOL_UPDATES,
            )
        )
        operations.extend(
            apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("Fringe", FRINGE_FIELD_UPDATES),
                    ("FringeManager", FRINGE_MANAGER_FIELD_UPDATES),
                    ("cRSubLoc", SUB_LOC_FIELD_UPDATES),
                ),
                proto_updates=FRINGE_PROTO_UPDATES,
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=(
                    *POPULATE_FRINGE_USER_VAR_UPDATES,
                    *FRINGE_RUNTIME_USER_VAR_UPDATES,
                ),
            )
        )
        operations.extend(
            apply_data_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=FRINGE_DATA_VAR_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.landscape_loader_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("LandscapeManager",),
            )
        )
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=(
                    ("0x4182e0", "reset_landscape_manager"),
                    ("0x4182f0", "load_landscape_script_by_name"),
                ),
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=LANDSCAPE_MANAGER_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.update_subgoldy_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=(
                    "SubSegment",
                    "SubSegmentEventBiasView",
                    "TimeTrialRouteRecordCursor",
                ),
            )
        )
        operations.append(
            ensure_path_analysis_views(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(verify_authored_row_cursor_sizes(target=args.target))
        operations.append(verify_fringe_mesh_cursor_sizes(target=args.target))
        operations.append(
            verify_runtime_grid_clear_cursor_sizes(target=args.target)
        )
        operations.append(
            verify_presentation_animation_cursor_sizes(target=args.target)
        )
        operations.extend(
            apply_split_user_var_update(
                REPO_ROOT,
                target=args.target,
                identifier="update_subgoldy",
                definitions=UPDATE_SUBGOLDY_EVENT_VIEW_SPLIT_DEFINITIONS,
                target_var=UPDATE_SUBGOLDY_EVENT_VIEW_TARGET_VAR,
                variable_name="row_event_segment_view",
                variable_type="SubSegmentEventBiasView*",
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=(
                    *UPDATE_SUBGOLDY_USER_VAR_UPDATES,
                    *UPDATE_SUBGOLDY_REPLAY_USER_VAR_UPDATES,
                ),
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.build_subgame_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=(
                    *BOD_CORE_OWNER_SIZES,
                    "Weapon",
                    "Invincible",
                    "Snail",
                    "Player",
                    "cRSubGame",
                ),
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.update_subgame_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=(
                    *BOD_CORE_OWNER_SIZES,
                    "GameRoot",
                    "RowModel",
                    "SubRow",
                    "RuntimeRowStrideAnchor",
                    "RuntimeCellStrideAnchor",
                    "TimeTrialRouteRecordCursor",
                    "cRSubGame",
                ),
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.append(verify_authored_row_cursor_sizes(target=args.target))
        operations.extend(
            apply_split_user_var_update(
                REPO_ROOT,
                target=args.target,
                identifier="update_subgame",
                definitions=UPDATE_SUBGAME_FRONTEND_ROOT_SPLIT_DEFINITIONS,
                target_var=UPDATE_SUBGAME_FRONTEND_ROOT_TARGET_VAR,
                variable_name="frontend_game_base",
                variable_type="GameRoot*",
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES,
            )
        )
        operations.extend(
            apply_instruction_comment_updates(
                REPO_ROOT,
                target=args.target,
                updates=UPDATE_SUBGAME_RING_SPEED_COMMENT_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.thanks_screen_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("ThanksScreen",),
            )
        )
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=(
                    ("0x433fd0", "initialize_thanks_for_playing_screen"),
                    ("0x4340c0", "uninit_thanks_screen"),
                    ("0x4340f0", "update_thanks_for_playing_screen"),
                ),
            )
        )
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="ThanksScreen",
                updates=THANKS_SCREEN_FIELD_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=THANKS_SCREEN_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.row_model_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("RowModel",),
            )
        )
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="RowModel",
                updates=ROW_MODEL_FIELD_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=ROW_MODEL_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.track_cache_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=(*BOD_CORE_OWNER_SIZES, "TrackRenderCacheSlot"),
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=BOD_CORE_SYMBOL_UPDATES + TRACK_RENDER_CACHE_SYMBOL_UPDATES,
            )
        )
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="TrackRenderCacheSlot",
                updates=TRACK_RENDER_CACHE_SLOT_FIELD_UPDATES,
            )
        )
        operations.extend(
            apply_data_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=BOD_CORE_DATA_VAR_UPDATES
                + TRACK_RENDER_CACHE_DATA_VAR_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=BOD_CORE_PROTO_UPDATES + TRACK_RENDER_CACHE_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.cut_scene_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("CutSceneState", "CutScene"),
            )
        )
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="CutScene",
                updates=CUT_SCENE_FIELD_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=CUT_SCENE_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.nuke_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("NukeState", "Nuke"),
            )
        )
        operations.append(verify_nuke_owner_size(target=args.target))
        operations.extend(
            apply_struct_field_updates(
                REPO_ROOT,
                target=args.target,
                struct_name="Nuke",
                updates=NUKE_FIELD_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=NUKE_PROTO_UPDATES,
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=NUKE_USER_VAR_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if args.tip_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=("FrontendWidget", *TIP_OWNER_SIZES),
            )
        )
        operations.append(verify_tip_owner_sizes(target=args.target))
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=TIP_FUNCTION_SYMBOL_UPDATES,
                kind="function",
            )
        )
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=TIP_DATA_SYMBOL_UPDATES,
                kind="data",
            )
        )
        operations.extend(
            apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("TipData", TIP_DATA_FIELD_UPDATES),
                    ("Tip", TIP_FIELD_UPDATES),
                    ("TipManager", TIP_MANAGER_FIELD_UPDATES),
                ),
                proto_updates=TIP_PROTO_UPDATES,
            )
        )
        operations.extend(
            apply_data_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=(("0x4ac5c8", "TipData"),),
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=TIP_MANAGER_USER_VAR_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    if not args.golb_only:
        operations.append(
            ensure_c_r_sub_loc_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(
            ensure_c_r_path_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(
            ensure_c_r_path_manager_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(
            ensure_c_r_subgame_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=REQUIRED_HEADER_STRUCTS,
            )
        )
        operations.append(verify_bod_core_owner_sizes(target=args.target))
        operations.append(verify_fringe_owner_sizes(target=args.target))
        operations.append(
            ensure_path_analysis_views(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.append(verify_authored_row_cursor_sizes(target=args.target))
        operations.append(verify_fringe_mesh_cursor_sizes(target=args.target))
        operations.append(
            verify_runtime_grid_clear_cursor_sizes(target=args.target)
        )
        operations.append(
            verify_presentation_animation_cursor_sizes(target=args.target)
        )
        operations.append(verify_golb_shot_asset_cursor_sizes(target=args.target))
        operations.append(verify_sub_lazer_asset_cursor_sizes(target=args.target))
        operations.append(verify_salt_asset_cursor_sizes(target=args.target))
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=SYMBOL_UPDATES,
            )
        )
    if not args.golb_only:
        operations.append(
            ensure_goldy_path_follow_owner_types(
                target=args.target,
                header_path=header_path,
            )
        )
    operations.append(
        ensure_golb_authored_types(
            target=args.target,
            header_path=header_path,
        )
    )
    operations.append(verify_golb_shot_inheritance(target=args.target))
    operations.append(ensure_golb_path_follow_state(target=args.target))
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GolbPathFollowState",
            updates=GOLB_PATH_FOLLOW_STATE_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GolbShot",
            updates=GOLB_SHOT_FIELD_UPDATES,
        )
    )
    if args.golb_only:
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=GOLB_PATH_FOLLOW_SYMBOL_UPDATES,
            )
        )
        operations.extend(
            apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=KILL_GOLB_OWNER_USER_VAR_UPDATES,
            )
        )
        operations.extend(
            apply_proto_updates(
                REPO_ROOT,
                target=args.target,
                updates=GOLB_PROTO_UPDATES,
            )
        )
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("BodNode", BOD_NODE_FIELD_UPDATES),
                ("BodList", BOD_LIST_FIELD_UPDATES),
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
                ("ReplayRunRecord", REPLAY_RUN_RECORD_FIELD_UPDATES),
                ("SubPause", SUB_PAUSE_FIELD_UPDATES),
                ("RenderableBod", RENDERABLE_BOD_FIELD_UPDATES),
                (
                    "TrackRenderCacheSlot",
                    TRACK_RENDER_CACHE_SLOT_FIELD_UPDATES,
                ),
                (
                    "ActiveLandscapeEntry",
                    ACTIVE_LANDSCAPE_ENTRY_FIELD_UPDATES,
                ),
                ("Face", FACE_FIELD_UPDATES),
                ("cRPathManager", PATH_MANAGER_FIELD_UPDATES),
                ("cRSubGame", SUBGAME_RUNTIME_FIELD_UPDATES),
                ("Vapour", VAPOUR_FIELD_UPDATES),
                ("JetPack", JETPACK_FIELD_UPDATES),
                ("SubHealth", SUB_HEALTH_FIELD_UPDATES),
                ("Slug", SLUG_FIELD_UPDATES),
                ("SlugStateStrideCursor", SLUG_STATE_CURSOR_FIELD_UPDATES),
                ("SaltStateStrideCursor", SALT_STATE_CURSOR_FIELD_UPDATES),
                ("SubSpeedUp", SUB_SPEED_UP_FIELD_UPDATES),
                ("Banner", BANNER_FIELD_UPDATES),
                ("Warning", WARNING_FIELD_UPDATES),
                ("DamageGuage", DAMAGE_GUAGE_FIELD_UPDATES),
                ("Nuke", NUKE_FIELD_UPDATES),
                ("ClickStart", CLICK_START_FIELD_UPDATES),
                ("TextureRef", TEXTURE_REF_FIELD_UPDATES),
                ("SnailVisual", SNAIL_VISUAL_FIELD_UPDATES),
                ("BodBase", BOD_BASE_FIELD_UPDATES),
                ("Fringe", FRINGE_FIELD_UPDATES),
                ("FringeManager", FRINGE_MANAGER_FIELD_UPDATES),
                ("cRSubLoc", SUB_LOC_FIELD_UPDATES),
                ("RowModel", ROW_MODEL_FIELD_UPDATES),
                ("SubRow", SUB_ROW_FIELD_UPDATES),
                ("PathTemplateSample", PATH_TEMPLATE_SAMPLE_FIELD_UPDATES),
                ("cRPath", PATH_FIELD_UPDATES),
                ("PathPair", PATH_PAIR_FIELD_UPDATES),
                (
                    "cRPathFollowGoldy",
                    GOLDY_PATH_FOLLOW_FIELD_UPDATES,
                ),
                ("JetParticleSlot", JET_PARTICLE_SLOT_FIELD_UPDATES),
                ("SubHover", SUB_HOVER_FIELD_UPDATES),
                ("TipData", TIP_DATA_FIELD_UPDATES),
                ("Tip", TIP_FIELD_UPDATES),
                ("TipManager", TIP_MANAGER_FIELD_UPDATES),
                ("Tutorial", TUTORIAL_FIELD_UPDATES),
                ("Player", PLAYER_FIELD_UPDATES),
                (
                    "PresentationWobbleController",
                    PRESENTATION_WOBBLE_CONTROLLER_FIELD_UPDATES,
                ),
                ("Snail", SNAIL_FIELD_UPDATES),
                ("Weapon", WEAPON_FIELD_UPDATES),
                ("AnimManager", ANIM_MANAGER_FIELD_UPDATES),
                ("Invincible", INVINCIBLE_FIELD_UPDATES),
                ("Cameraman", CAMERAMAN_FIELD_UPDATES),
                ("CutScene", CUT_SCENE_FIELD_UPDATES),
                ("SnailSkin", SNAIL_SKIN_FIELD_UPDATES),
                *collect_c_r_subgame_backpointer_struct_updates(
                    target=args.target
                ),
            ),
            proto_updates=CORE_SUBGAME_PROTO_UPDATES,
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="place_challenge_parcels_on_track",
            definitions=CHALLENGE_PARCELS_RUNTIME_ANCHOR_SPLIT_DEFINITIONS,
            target_var=CHALLENGE_PARCELS_RUNTIME_ANCHOR_TARGET_VAR,
            variable_name="challenge_runtime_row_anchor",
            variable_type="RuntimeRowStrideAnchor*",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_subgoldy",
            definitions=UPDATE_SUBGOLDY_EVENT_VIEW_SPLIT_DEFINITIONS,
            target_var=UPDATE_SUBGOLDY_EVENT_VIEW_TARGET_VAR,
            variable_name="row_event_segment_view",
            variable_type="SubSegmentEventBiasView*",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_subgame",
            definitions=UPDATE_SUBGAME_FRONTEND_ROOT_SPLIT_DEFINITIONS,
            target_var=UPDATE_SUBGAME_FRONTEND_ROOT_TARGET_VAR,
            variable_name="frontend_game_base",
            variable_type="GameRoot*",
        )
    )
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_track_attachment_follow_state",
            definitions=ATTACHMENT_FOLLOW_ROOT_SPLIT_DEFINITIONS,
            target_var=ATTACHMENT_FOLLOW_ROOT_TARGET_VAR,
            variable_name="attachment_game_base",
            variable_type="GameRoot*",
        )
    )
    for definitions, target_var, variable_name, variable_type in (
        POPULATE_RUNTIME_SPLIT_USER_VAR_UPDATES
    ):
        operations.extend(
            apply_split_user_var_update(
                REPO_ROOT,
                target=args.target,
                identifier="populate_runtime_track_cells_from_segments",
                definitions=definitions,
                target_var=target_var,
                variable_name=variable_name,
                variable_type=variable_type,
            )
        )
    operations.extend(
        remove_user_var_updates(
            REPO_ROOT,
            target=args.target,
            removals=REJECTED_POPULATE_RUNTIME_CELL_ALIAS_REMOVALS,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=(
                *UPDATE_SUBGOLDY_USER_VAR_UPDATES,
                *UPDATE_SUBGOLDY_REPLAY_USER_VAR_UPDATES,
                *INITIALIZE_SUBGOLDY_USER_VAR_UPDATES,
                *MOVEMENT_FLAG_EMITTER_USER_VAR_UPDATES,
                *UPDATE_BANNER_USER_VAR_UPDATES,
                *BANNER_INITIALIZER_USER_VAR_UPDATES,
                *PRESENTATION_ANIMATION_CURSOR_USER_VAR_UPDATES,
                *WORLD_INITIALIZER_GOLB_ASSET_CURSOR_USER_VAR_UPDATES,
                *WORLD_INITIALIZER_SUB_LAZER_ASSET_CURSOR_USER_VAR_UPDATES,
                *WORLD_INITIALIZER_SALT_ASSET_CURSOR_USER_VAR_UPDATES,
                *NUKE_USER_VAR_UPDATES,
                *TIP_MANAGER_USER_VAR_UPDATES,
                *BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES,
                *CREATE_GOLB_ACTIVE_BOD_USER_VAR_UPDATES,
                *KILL_GOLB_OWNER_USER_VAR_UPDATES,
                *PLACE_PARCELS_SCAN_USER_VAR_UPDATES,
                *PLACE_PARCELS_RUNTIME_USER_VAR_UPDATES,
                *CHALLENGE_PARCELS_RUNTIME_USER_VAR_UPDATES,
                *UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES,
                *REMOVE_SUBGAME_BODS_CURSOR_USER_VAR_UPDATES,
                *SPAWN_TRACK_RING_USER_VAR_UPDATES,
                *SPAWN_TRACK_PICKUP_CURSOR_USER_VAR_UPDATES,
                *COLLISION_POOL_CURSOR_USER_VAR_UPDATES,
                *SPAWN_SALT_HAZARD_USER_VAR_UPDATES,
                *POPULATE_SEGMENT_SELECTION_USER_VAR_UPDATES,
                *POPULATE_ATTACHMENT_INSTALL_USER_VAR_UPDATES,
                *POPULATE_RUNTIME_CLEAR_CURSOR_USER_VAR_UPDATES,
                *POPULATE_RUNTIME_USER_VAR_UPDATES,
                *MERGE_RUNTIME_USER_VAR_UPDATES,
                *FRINGE_RUNTIME_USER_VAR_UPDATES,
                *HARMONIZE_RUNTIME_USER_VAR_UPDATES,
                *PATH_SAMPLE_INVERSE_USER_VAR_UPDATES,
                *ATTACHMENT_FOLLOW_USER_VAR_UPDATES,
            ),
        )
    )
    operations.extend(
        apply_instruction_comment_updates(
            REPO_ROOT,
            target=args.target,
            updates=UPDATE_SUBGAME_RING_SPEED_COMMENT_UPDATES,
        )
    )
    operations.extend(
        apply_refined_owner_prototypes(
            target=args.target,
            updates=REFINED_PATH_OWNER_PROTO_UPDATES,
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SUBGAME_RECEIVER_USER_VAR_UPDATES,
        )
    )
    operations.extend(
        report_deferred_owner_prototypes(
            target=args.target,
            updates=DEFERRED_SUBGAME_OWNER_PROTO_UPDATES,
            stale_identity_reason=(
                "stale user-defined Game* identity requires guarded function recreation"
            ),
        )
    )
    operations.extend(
        report_deferred_owner_prototypes(
            target=args.target,
            updates=DEFERRED_PATH_OWNER_PROTO_UPDATES,
            stale_identity_reason=(
                "stale user-defined PathTemplate* identity or result ABI requires "
                "guarded function recreation"
            ),
        )
    )
    operations.extend(
        apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        )
    )
    operations.extend(
        apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        )
    )
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
