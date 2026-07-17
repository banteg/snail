#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_struct_and_proto_updates,
    apply_struct_field_updates,
    apply_split_user_var_update,
    apply_symbol_updates,
    apply_user_var_updates,
    current_header_type_equivalence,
    current_prototypes,
    emit_summary,
    normalize_prototype,
    run_bn,
    struct_exists,
    types_declare_if_missing,
    types_declare_missing_only,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

SYMBOL_UPDATES = (
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
    ("0x44d1a0", "multiply_matrix"),
    ("0x44d1d0", "multiply_matrix_in_place_forward_thunk"),
    ("0x44d1e0", "premultiply_matrix_in_place"),
    ("0x44d530", "initialize_quaternion_from_axis"),
    ("0x44d580", "initialize_axis_from_quaternion"),
    ("0x44d5d0", "initialize_quaternion_from_matrix"),
    ("0x44d820", "initialize_matrix_from_quaternion"),
    ("0x44d920", "interpolate_matrix_rotation"),
    ("0x44dbd0", "set_color_rgb"),
    ("0x4086d0", "initialize_player_presentation_controller"),
    ("0x4ac5c8", "g_default_tip_message"),
    ("0x497354", "g_player_presentation_noop_vtable"),
    ("0x497358", "g_invincible_shell_update_vtable"),
    ("0x49735c", "g_weapon_noop_vtable"),
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
    ("0x98", "cutscene_roll_progress", "float"),
    ("0x9c", "cutscene_roll_step", "float"),
    ("0xa0", "channel_release_steps_active", "uint8_t"),
)

RENDERABLE_BOD_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "transform", "TransformMatrix"),
    ("0x78", "render_animation_manager", "AnimManager*"),
    ("0x7c", "unknown_7c", "uint8_t[0x4]"),
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
    ("0x04", "template_record", "Path*"),
    ("0x08", "source_cell", "TrackRowCell*"),
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
    Path* template_record;
    TrackRowCell* source_cell;
    int32_t sample_index;
    float progress;
    float vertical_offset;
    Vec3 output_position;
    GolbShot* shot;
} GolbPathFollowState;
""".strip()

GOLB_SHOT_FIELD_UPDATES = (
    # GolbShot +0x000..+0x197 is an overlapping body/vapour/live-matrix
    # union in the import header. Do not flatten it with field updates here:
    # installing the +0x118 body view would evict the +0x150 matrix view.
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
    ("0x248", "render_body_owner", "void*"),
    ("0x24c", "velocity", "Vec3"),
    ("0x258", "direction", "Vec3"),
    ("0x264", "path_factor", "float"),
    ("0x268", "lifetime", "float"),
    ("0x26c", "lifetime_step", "float"),
    ("0x270", "game", "SubgameRuntime*"),
    ("0x274", "object_ref", "void*"),
    ("0x278", "owner_player", "Player*"),
    ("0x27c", "source_matrix", "TransformMatrix"),
    ("0x2bc", "path_follow", "GolbPathFollowState"),
    ("0x2e4", "path_entry_z_latch", "float"),
)

REQUIRED_HEADER_STRUCTS = (
    "PathManager",
    "FrontendWidgetFlag",
    "TextureRefFlags",
    "Twinkle",
    "TwinkleManager",
    "InputOkState",
    "BarrierActor",
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
    "SubRingSlotCursor",
    "SubHealthSlotCursor",
    "SlugSlotCursor",
    "SubLazerSlotCursor",
    "SaltSlotCursor",
    "ParcelSlotCursor",
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
    "Vapour",
    "TrackPickupState",
    "JetPack",
    "ParcelState",
    "CompletionState",
    "TimesUpState",
    "AxisAngle",
    "Quaternion",
    "RenderableBod",
    "FringeObject",
    "FringeManager",
    "SMTracks",
    "SmtrackHeightfieldAnimator",
    "AuthoredSegmentRowFlag",
    "SubSegmentRowStrideAnchor",
    "SubLocOpenEdgeFlag",
    "SubLocFlag",
    "TrackRowCell",
    "SubRowFlag",
    "SubRow",
    "RuntimeRowStrideAnchor",
    "RuntimeCellStrideAnchor",
    "Path",
    "PathPair",
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
    "AnimManager",
    "Weapon",
    "GolbShot",
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
    """Replace mutable analysis views whenever their parsed shape changes."""
    type_names = ("PresentationWobbleController", "RuntimeCellStrideAnchor")
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
    ("0x1cc", "movement_sound_variant_sample", "int32_t"),
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
    ("0x304", "startup_track_index", "int32_t"),
    ("0x308", "movement_flag_selector", "int32_t"),
    ("0x310", "score_buckets", "int32_t[0x6]"),
    ("0x338", "movement_flags", "uint32_t"),
    ("0x33c", "previous_movement_flags", "uint32_t"),
    ("0x328", "barrier_hold_progress", "float"),
    ("0x32c", "barrier_hold_step", "float"),
    ("0x330", "startup_voice_timer", "float"),
    ("0x334", "startup_voice_step", "float"),
    ("0x350", "lane_lean_state", "int32_t"),
    ("0x354", "lane_lean_amplitude", "float"),
    ("0x358", "lane_lean_progress", "float"),
    ("0x35c", "lane_lean_progress_step", "float"),
    ("0x360", "timer_360_state", "int32_t"),
    ("0x364", "unknown_364", "int32_t"),
    ("0x368", "timer_360_progress", "float"),
    ("0x36c", "timer_360_step", "float"),
    ("0x370", "heading_roll", "float"),
    ("0x374", "nuke_effect_progress", "float"),
    ("0x378", "nuke_effect_progress_step", "float"),
    ("0x37c", "last_ring_spawn_z", "float"),
    ("0x380", "player_slot", "int32_t"),
    ("0x384", "follow_state", "FollowState"),
    ("0x3c4", "damage_gauge", "DamageGuage"),
    ("0x3f0", "progress_bar", "ProgressBar"),
    ("0x3f4", "warning", "Warning"),
    ("0x404", "lives", "int32_t"),
    ("0x408", "game", "SubgameRuntime*"),
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
    ("0x2730", "movement_fire_progress", "float"),
    ("0x2734", "movement_fire_progress_step", "float"),
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

# The native row-event block computes three pre-biased addresses from the
# SubgameRuntime base. HLIL otherwise chooses nearby named members before it
# proves event_id > 0, falsely rendering the message lanes inside SegmentCache
# and Tutorial. These bounded register views preserve the honest byte arithmetic
# until Binary Ninja can express level_definition.segment_slots[event_id - 1].
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
        "game_bytes_for_message",
        "uint8_t*",
    ),
    (
        "update_subgoldy",
        "RegisterVariableSourceType",
        1688,
        68,
        "game_bytes_for_duration",
        "uint8_t*",
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

# build_subgame_level inlines BodList::add_bod for the presentation's jetpack,
# three weapon channels, invincibility shell, Snail body, and Player body. The
# active-list anchor is the same BodNode** owner at all seven sites, but BN
# otherwise inherits FrameBodBase** at the first lifetime and void** after the
# register changes. Preserve those exact anchor identities and only the native
# jetpack/Player lifetimes where register reuse prevents the BodNode* type from
# propagating through otherwise full-width pointer loads and stores.
BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES = (
    (
        "build_subgame_level",
        "RegisterVariableSourceType",
        1261,
        73,
        "initialized_player",
        "Player*",
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
        1397,
        66,
        "active_first_ref_weapon_0",
        "BodNode**",
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
        1573,
        66,
        "active_first_ref_weapon_2",
        "BodNode**",
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
        1764,
        66,
        "active_first_ref_presentation",
        "BodNode**",
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

# place_parcels_on_track retains a containing SubgameRuntime base while its two
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
        "TrackRowCell*",
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
# cursor does not own another SubgameRuntime, and the root list owns neither the
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

# The collision dispatcher keeps byte offsets in EDI and repeatedly forms a
# temporary `SubgameRuntime + slot_offset` pointer in EAX. These analysis-only
# cursor views name the embedded slot reached by each large displacement while
# retaining the real SubgameRuntime owner and the native byte-strided lifetime.
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

# VC6 retains containing-owner bases while advancing one authored row, one
# runtime row, and one runtime cell at their native 0x38/0xf4/0x54 strides.
# Binary Ninja otherwise flattens all three into void-pointer displacement
# arithmetic. The stack slot is the matching authored-row ordinal, not the
# SubgameRuntime pointer inferred from an earlier compiler-reused lifetime.
POPULATE_RUNTIME_USER_VAR_UPDATES = (
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
        "TrackRowCell*",
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

# MakeFringe owns a plain SubRow cursor and advances one TrackRowCell at a
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
        "TrackRowCell*",
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

# SlideSmoothTrack carries the same SubgameRuntime-relative cell cursor in two
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

# The entry-mesh milestone branches repeatedly reload
# SubRow::primary_attachment_cell. BN's SSA split loses the TrackRowCell*/Path*
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
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        196,
        72,
        "entry_base_template",
        "Path*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        218,
        67,
        "primary_attachment_cell_restore_object",
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        256,
        67,
        "primary_attachment_cell_restore_alpha",
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        327,
        66,
        "primary_attachment_cell_transition_flags",
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        364,
        67,
        "primary_attachment_cell_transition_template",
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        371,
        72,
        "entry_transition_template",
        "Path*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        397,
        68,
        "primary_attachment_cell_transition_object",
        "TrackRowCell*",
    ),
    (
        "update_track_attachment_follow_state",
        "RegisterVariableSourceType",
        435,
        67,
        "primary_attachment_cell_transition_alpha",
        "TrackRowCell*",
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
    ("0x28", "completion_bonus_x_source", "int32_t"),
    ("0x2c", "completion_bonus_y_source", "int32_t"),
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
    ("0x3bfac8", "runtime_cells", "TrackRowCell[0xc80][8]"),
    ("0x5ccac8", "runtime_rows", "SubRow[0xc80]"),
    ("0x68b4c8", "sub_high_score", "SubHighScore"),
    ("0xfd2b10", "current_high_score_record", "SubSolution"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SubSolution*"),
    ("0xff25d8", "selected_level_record_cursor", "int32_t"),
    ("0xff25dc", "replay_update_cursor", "int32_t"),
    ("0xff25e0", "time_trial", "TimeTrial"),
    ("0xff2910", "path_manager", "PathManager"),
    ("0xff2914", "path_pairs", "PathPair[63]"),
    ("0xff7bc4", "barrier", "BarrierActor"),
    ("0xff7c00", "landscape_manager", "LandscapeManager"),
    ("0x10013a4", "smtrack_heightfield", "SmtrackHeightfieldAnimator"),
    ("0x10014cc", "sm_tracks", "SMTracks"),
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
    ("0x12e6f58", "tip_manager", "TipManager"),
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

BANNER_FIELD_UPDATES = (
    ("0x48", "owner_game", "SubgameRuntime*"),
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
    ("0x24", "object", "Object*"),
)

FRINGE_OBJECT_FIELD_UPDATES = (
    ("0x24", "object", "Object*"),
)

TRACK_ROW_CELL_FIELD_UPDATES = (
    ("0x00", "bod", "BodNode"),
    ("0x10", "anchor_position", "Vec3"),
    ("0x1c", "render_arg_1c", "int32_t"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "Object*"),
    ("0x28", "color", "tColour"),
    ("0x38", "attachment_template_record", "Path*"),
    ("0x3c", "tile_id", "uint8_t"),
    ("0x3d", "open_edge_mask", "uint8_t"),
    ("0x40", "lane_and_flags", "uint32_t"),
    ("0x44", "fringe_front", "FringeObject*"),
    ("0x48", "fringe_right", "FringeObject*"),
    ("0x4c", "fringe_left", "FringeObject*"),
    ("0x50", "fringe_back", "FringeObject*"),
)

SUB_ROW_FIELD_UPDATES = (
    ("0x00", "flags", "uint32_t"),
    ("0x04", "primary_body", "RenderableBod"),
    ("0x84", "authored_object_velocity", "Vec3"),
    ("0x90", "projection_payload", "Vec3"),
    ("0x9c", "parcel_set_id", "int32_t"),
    ("0xa0", "attachment_template_index", "int32_t"),
    ("0xa4", "primary_attachment_cell", "TrackRowCell*"),
    ("0xa8", "secondary_attachment_cell", "TrackRowCell*"),
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
    ("0xa4", "lateral_source", "float"),
)

FOLLOW_STATE_FIELD_UPDATES = (
    # Reset by populate_runtime_track_cells_from_segments and read by
    # update_subgoldy. No nonzero producer is proved yet.
    ("0x3c", "flag_3c", "uint8_t"),
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
    ("0x200", "game", "SubgameRuntime*"),
    ("0x20c", "warning_intensity_latch", "float"),
    ("0x210", "warning_intensity", "float"),
)

TIP_MANAGER_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "tips", "Tip[0x3]"),
)

TUTORIAL_FIELD_UPDATES = (
    ("0x0c", "game", "SubgameRuntime*"),
)

TIP_DATA_VAR_UPDATES = (
    ("0x4ac5c8", "TipData"),
)


def ensure_sub_loc_alias(*, target: str) -> dict[str, object]:
    try:
        current = run_bn(
            REPO_ROOT,
            "types",
            "show",
            "SubLoc",
            "--target",
            target,
            "--format",
            "json",
        )
    except RuntimeError:
        current = None

    if isinstance(current, dict) and current.get("name") == "SubLoc":
        return {
            "op": "types_declare",
            "status": "skipped",
            "reason": "SubLoc alias already present",
            "declaration": "typedef struct TrackRowCell SubLoc;",
        }

    return {
        "op": "types_declare",
        "declaration": "typedef struct TrackRowCell SubLoc;",
        "result": run_bn(
            REPO_ROOT,
            "types",
            "declare",
            "--target",
            target,
            "typedef struct TrackRowCell SubLoc;",
        ),
    }


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
        "update_movement_flag_emitters",
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source)",
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
        "int32_t __thiscall initialize_path_follow_golb(GolbPathFollowState* state, TrackRowCell* source_cell, const Vec3* position, GolbShot* shot)",
    ),
    (
        "calc_path_length_z",
        "int32_t __thiscall calc_path_length_z(GolbPathFollowState* state, float path_factor, Vec3* position, Vec3* velocity)",
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

PROTO_UPDATES = GOLB_PROTO_UPDATES + (
    (
        "set_bod_object",
        "int32_t __thiscall set_bod_object(BodBase* bod, Object* object)",
    ),
    (
        "initialize_bod_base",
        "BodBase* __thiscall initialize_bod_base(BodBase* bod)",
    ),
    (
        "initialize_fringe_manager",
        "void __thiscall initialize_fringe_manager(FringeManager* manager)",
    ),
    (
        "allocate_fringe_object",
        "FringeObject* __thiscall allocate_fringe_object(FringeManager* manager)",
    ),
    (
        "apply_bod_position",
        "Object* __thiscall apply_bod_position(BodBase* bod, TransformMatrix* matrix)",
    ),
    (
        "build_track_fringe_mesh",
        "void __thiscall build_track_fringe_mesh(Path* self, char* texture_path, float clamp_side)",
    ),
    (
        "build_track_fringe_supertramp_mesh",
        "void __thiscall build_track_fringe_supertramp_mesh(Path* self, char* texture_path)",
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
        "tColour* __thiscall get_track_skirt_color(SubgameRuntime* game, tColour* out)",
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
        "SubLoc* __thiscall initialize_sub_loc(SubLoc* cell)",
    ),
    (
        "remove_sub_loc",
        "void __thiscall remove_sub_loc(SubLoc* cell)",
    ),
    (
        "update_sub_loc",
        "void __thiscall update_sub_loc(SubLoc* cell)",
    ),
    (
        "get_track_cell_row_index",
        "int32_t __thiscall get_track_cell_row_index(SubLoc* cell)",
    ),
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(PathManager* manager, char* name)",
    ),
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
        "multiply_matrix",
        "void __thiscall multiply_matrix(TransformMatrix* matrix, const TransformMatrix* rhs)",
    ),
    (
        "multiply_matrix_in_place_forward_thunk",
        "void __thiscall multiply_matrix_in_place_forward_thunk(TransformMatrix* matrix, const TransformMatrix* rhs)",
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
        "void __thiscall compute_kind42_attachment_transform(Path* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle)",
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
        "void __thiscall advance_frame_sequence(FrameSequence* sequence)",
    ),
    (
        "update_smtracks",
        "void __thiscall update_smtracks(SmtrackHeightfieldAnimator* animator)",
    ),
    (
        "sample_smtrack_heightmap",
        "void __cdecl sample_smtrack_heightmap(Object* source, float base, float scale, TextureRef* replacement, char cubic)",
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
        "void __thiscall set_snail_weapon(Snail* snail, int32_t movement_flags)",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state)",
    ),
    (
        "initialize_cutscene",
        "void __thiscall initialize_cutscene(Snail* snail)",
    ),
    *CUT_SCENE_PROTO_UPDATES,
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
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
        "update_snail_skin",
        "void __thiscall update_snail_skin(Snail* snail)",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
    ),
    (
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player)",
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
        "play_movement_state_sound",
        "void __thiscall play_movement_state_sound(Player* player)",
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
        "initialize_score_stats",
        "void __thiscall initialize_score_stats(Squidge* squidge)",
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

# The full SubgameRuntime and Player field maps above are the canonical owner
# views consumed by these lifecycle and level-builder functions. These
# prototypes are replayed through the direct verified batch because older BN
# analysis can otherwise restore an inferred but ABI-equivalent fastcall label.
CORE_SUBGAME_PROTO_UPDATES = (
    (
        "update_subgoldy_resurrect",
        "void __thiscall update_subgoldy_resurrect(Player* player)",
    ),
    ("reset_subgame", "void __thiscall reset_subgame(SubgameRuntime* game)"),
    (
        "complete_subgame",
        "void __thiscall complete_subgame(SubgameRuntime* game, uint8_t completed)",
    ),
    (
        "mark_track_warning_zones",
        "void __thiscall mark_track_warning_zones(SubgameRuntime* game)",
    ),
    (
        "try_enter_track_attachment_from_swept_motion",
        "void __thiscall try_enter_track_attachment_from_swept_motion(Path* self, float world_x, float world_y, float world_z, float sweep_dx, float sweep_dy, float sweep_dz, TrackRowCell* source_cell)",
    ),
    (
        "update_track_attachment_follow_state",
        "int32_t __thiscall update_track_attachment_follow_state(FollowState* follow_state, float path_factor, Vec3* out_position, Vec3* motion)",
    ),
    (
        "populate_runtime_track_cells_from_segments",
        "void __thiscall populate_runtime_track_cells_from_segments(SubgameRuntime* game)",
    ),
    (
        "place_parcels_on_track",
        "void __thiscall place_parcels_on_track(SubgameRuntime* game)",
    ),
    (
        "place_challenge_parcels_on_track",
        "void __thiscall place_challenge_parcels_on_track(SubgameRuntime* game)",
    ),
)

# These lifecycle and track-normalization receivers are already SubgameRuntime
# methods in the exact/working matching sources and in the cross-port cRSubGame
# symbol evidence. The exact runtime-row lookup has the same owner proof through
# the canonical array. Older BN databases pin a separate user-defined Game*
# parameter variable on these functions. Both the previewed prototype setter and local
# retype API reject the owner-only correction, so report the drift instead of
# claiming a mutation that analysis immediately restores. The guarded repair
# catalog handles only the exact known stale identities and defaults to a
# read-only inspection because function recreation is not covered by ordinary
# Binary Ninja undo.
DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (
    ("initialize_subgame", "void __thiscall initialize_subgame(SubgameRuntime* game)"),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index)",
    ),
    ("destroy_subgame", "void __thiscall destroy_subgame(SubgameRuntime* game)"),
    ("update_subgame", "void __thiscall update_subgame(SubgameRuntime* game)"),
    ("remove_subgame_bods", "void __thiscall remove_subgame_bods(SubgameRuntime* game)"),
    (
        "merge_track_tile_runs",
        "int32_t __thiscall merge_track_tile_runs(SubgameRuntime* game)",
    ),
    (
        "build_track_fringe_objects",
        "int32_t __thiscall build_track_fringe_objects(SubgameRuntime* game)",
    ),
    (
        "promote_track_tiles_to_fringe_variants",
        "int32_t __thiscall promote_track_tiles_to_fringe_variants(SubgameRuntime* game)",
    ),
    (
        "harmonize_center_lane_floor_slide_variants",
        "int32_t __thiscall harmonize_center_lane_floor_slide_variants(SubgameRuntime* game)",
    ),
    (
        "select_track_tile_edge_variants",
        "int32_t __thiscall select_track_tile_edge_variants(SubgameRuntime* game)",
    ),
    (
        "get_track_grid_cell_at_world_position",
        "TrackRowCell* __thiscall get_track_grid_cell_at_world_position(SubgameRuntime* game, Vec3* position)",
    ),
    (
        "sample_track_floor_height_at_position",
        "double __thiscall sample_track_floor_height_at_position(SubgameRuntime* game, Vec3* position)",
    ),
    (
        "spawn_track_health_pickup",
        "void __thiscall spawn_track_health_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player)",
    ),
    (
        "spawn_track_jetpack_pickup",
        "void __thiscall spawn_track_jetpack_pickup(SubgameRuntime* game, TrackRowCell* cell, Player* player)",
    ),
    (
        "get_track_runtime_cell_at_world_z",
        "SubRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position)",
    ),
)


DEFERRED_PATH_OWNER_PROTO_UPDATES = (
    (
        "allocate_path_template_samples",
        "void __fastcall allocate_path_template_samples(Path* self)",
    ),
    (
        "finalize_path_template",
        "void __fastcall finalize_path_template(Path* self)",
    ),
    (
        "initialize_worm_path_template_pair",
        "void __thiscall initialize_worm_path_template_pair(Path* self, char* texture_path)",
    ),
    (
        "mirror_path_template_pair_x",
        "void __thiscall mirror_path_template_pair_x(Path* self, Path* source)",
    ),
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


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the authoritative path/presentation ownership slice to a Binary Ninja "
            "target and replay the proven Player and SubgameRuntime field overlays."
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
        "--golb-only",
        action="store_true",
        help="Replay only the GolbShot/path-follow ownership slice.",
    )
    focused_group.add_argument(
        "--cut-scene-only",
        action="store_true",
        help="Replay only the CutScene state owner and its two method prototypes.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
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

    if not args.golb_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=REQUIRED_HEADER_STRUCTS,
            )
        )
        operations.append(
            ensure_path_analysis_views(
                target=args.target,
                header_path=header_path,
            )
        )
        operations.extend(
            apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=SYMBOL_UPDATES,
            )
        )
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

    operations.append(ensure_sub_loc_alias(target=args.target))
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
                ("ReplayRunRecord", REPLAY_RUN_RECORD_FIELD_UPDATES),
                ("SubPause", SUB_PAUSE_FIELD_UPDATES),
                ("RenderableBod", RENDERABLE_BOD_FIELD_UPDATES),
                ("SubgameRuntime", SUBGAME_RUNTIME_FIELD_UPDATES),
                ("Vapour", VAPOUR_FIELD_UPDATES),
                ("JetPack", JETPACK_FIELD_UPDATES),
                ("Banner", BANNER_FIELD_UPDATES),
                ("Warning", WARNING_FIELD_UPDATES),
                ("DamageGuage", DAMAGE_GUAGE_FIELD_UPDATES),
                ("Nuke", NUKE_FIELD_UPDATES),
                ("ClickStart", CLICK_START_FIELD_UPDATES),
                ("TextureRef", TEXTURE_REF_FIELD_UPDATES),
                ("SnailVisual", SNAIL_VISUAL_FIELD_UPDATES),
                ("BodBase", BOD_BASE_FIELD_UPDATES),
                ("FringeObject", FRINGE_OBJECT_FIELD_UPDATES),
                ("TrackRowCell", TRACK_ROW_CELL_FIELD_UPDATES),
                ("SubRow", SUB_ROW_FIELD_UPDATES),
                ("PathTemplateSample", PATH_TEMPLATE_SAMPLE_FIELD_UPDATES),
                ("Path", PATH_FIELD_UPDATES),
                ("FollowState", FOLLOW_STATE_FIELD_UPDATES),
                ("JetParticleSlot", JET_PARTICLE_SLOT_FIELD_UPDATES),
                ("SubHover", SUB_HOVER_FIELD_UPDATES),
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
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=(
                *UPDATE_SUBGOLDY_USER_VAR_UPDATES,
                *UPDATE_BANNER_USER_VAR_UPDATES,
                *BUILD_SUBGAME_ACTIVE_BOD_USER_VAR_UPDATES,
                *CREATE_GOLB_ACTIVE_BOD_USER_VAR_UPDATES,
                *PLACE_PARCELS_RUNTIME_USER_VAR_UPDATES,
                *CHALLENGE_PARCELS_RUNTIME_USER_VAR_UPDATES,
                *UPDATE_SUBGAME_RUNTIME_USER_VAR_UPDATES,
                *REMOVE_SUBGAME_BODS_CURSOR_USER_VAR_UPDATES,
                *SPAWN_TRACK_RING_USER_VAR_UPDATES,
                *COLLISION_POOL_CURSOR_USER_VAR_UPDATES,
                *POPULATE_RUNTIME_USER_VAR_UPDATES,
                *MERGE_RUNTIME_USER_VAR_UPDATES,
                *FRINGE_RUNTIME_USER_VAR_UPDATES,
                *HARMONIZE_RUNTIME_USER_VAR_UPDATES,
                *ATTACHMENT_FOLLOW_USER_VAR_UPDATES,
            ),
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
            updates=TIP_DATA_VAR_UPDATES,
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
