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
    apply_symbol_updates,
    current_prototypes,
    emit_summary,
    run_bn,
    struct_exists,
    types_declare_if_missing,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

PRESENTATION_SYMBOL_UPDATES = (
    ("0x4086d0", "initialize_player_presentation_controller"),
    ("0x4ac5c8", "g_default_tip_message"),
    ("0x497354", "g_player_presentation_noop_vtable"),
    ("0x497358", "g_invincible_shell_update_vtable"),
    ("0x49735c", "g_presentation_animation_channel_noop_vtable"),
)

SNAIL_FIELD_UPDATES = (
    ("0x00", "body", "RenderableBod"),
    ("0x80", "previous_live_matrix", "TransformMatrix"),
    ("0xc0", "cached_cutscene_matrix", "TransformMatrix"),
    ("0x100", "owner_player", "Player*"),
    ("0x104", "anim_manager", "AnimManager"),
    ("0x14c", "cutscene_animation_slots", "PresentationAnimationSlot[0xa]"),
    ("0x64c", "weapon_channels", "PresentationAnimationChannel[0x3]"),
    ("0x11e0", "jetpack_channel", "PresentationAnimationChannel"),
    ("0x15cc", "snail_hotspot_source_body", "RenderableBod"),
    ("0x164c", "snail_hotspot_body", "RenderableBod"),
    ("0x1894", "invincible_shell", "Invincible"),
    ("0x1938", "snail_skin", "SnailSkin"),
    ("0x1958", "cutscene", "CutScene"),
)

PRESENTATION_ANIMATION_CHANNEL_FIELD_UPDATES = (
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
    ("0x80", "state", "int32_t"),
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
    ("0x0c", "state", "int32_t"),
    ("0x10", "live_matrix", "TransformMatrix"),
    ("0x50", "progress", "float"),
    ("0x54", "progress_step", "float"),
    ("0x58", "force_camera_update", "uint8_t"),
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
    "BarrierActor",
    "LandscapeManager",
    "GUI",
    "Help",
    "ThanksScreen",
    "GalaxyPoint",
    "Galaxy",
    "EnemyManager",
    "SubgameRuntime",
    "SubHighScore",
    "SubSolution",
    "SubTracks",
    "SlugVoiceManager",
    "TimeTrial",
    "SnailVisual",
    "BodNode",
    "BodBase",
    "Banner",
    "Vapour",
    "JetPack",
    "RenderableBod",
    "FringeObject",
    "FringeManager",
    "SMTracks",
    "SmtrackHeightfieldAnimator",
    "TrackRowCell",
    "TrackAttachmentRuntimeRow",
    "Path",
    "PathPair",
    "DamageGuage",
    "ProgressBar",
    "Warning",
    "Nuke",
    "FireWork",
    "ClickStart",
    "Cameraman",
    "Squidge",
    "Invincible",
    "SnailSkin",
    "Snail",
    "CutScene",
    "ObjectAnimation",
    "PresentationAnimationSlot",
    "AnimManager",
    "PresentationAnimationChannel",
    "GolbShot",
    "Player",
    "JetParticleSlot",
    "SubHover",
    "TipData",
    "Tip",
    "TipManager",
    "Tutorial",
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

SUBGAME_RUNTIME_FIELD_UPDATES = (
    ("0x09", "subgame_pause_gate", "uint8_t"),
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
    ("0x5ccac8", "runtime_rows", "TrackAttachmentRuntimeRow[0xc80]"),
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

SNAIL_VISUAL_FIELD_UPDATES = (
    ("0x10", "flags", "uint32_t"),
    ("0x18", "material_index", "int32_t"),
    ("0x80", "follow_lateral_response", "float"),
    ("0x84", "squidge_primary", "float"),
    ("0x88", "squidge_secondary", "float"),
)

TRACK_ROW_CELL_FIELD_UPDATES = (
    ("0x00", "bod", "BodNode"),
    ("0x10", "anchor_position", "Vec3"),
    ("0x1c", "render_arg_1c", "int32_t"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "Color4f"),
    ("0x38", "attachment_template_record", "Path*"),
    ("0x3c", "tile_id", "uint8_t"),
    ("0x3d", "tile_flags_3d", "uint8_t"),
    ("0x40", "lane_and_flags", "uint32_t"),
    ("0x44", "fringe_front", "FringeObject*"),
    ("0x48", "fringe_right", "FringeObject*"),
    ("0x4c", "fringe_left", "FringeObject*"),
    ("0x50", "fringe_back", "FringeObject*"),
)

TRACK_ATTACHMENT_RUNTIME_ROW_FIELD_UPDATES = (
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

JET_PARTICLE_SLOT_FIELD_UPDATES = (
    ("0x00", "sprite", "Sprite*"),
    ("0x04", "wobble_x", "float"),
    ("0x08", "wobble_y", "float"),
    ("0x0c", "wobble_alpha", "float"),
)

SUB_HOVER_FIELD_UPDATES = (
    ("0x00", "progress", "float"),
    ("0x04", "progress_step", "float"),
    ("0x0c", "state", "int32_t"),
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

# update_golb_ai can retain a no-argument auto prototype in older databases.
# The bridge cannot preview that cdecl-to-thiscall replacement,
# so keep it out of the replay instead of applying an unpreviewable direct override.
GOLB_PROTO_UPDATES = (
    (
        "create_golb",
        "void __thiscall create_golb(GolbShot* shot, Player* player, int32_t spawn_selector, int32_t emitter_index)",
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

PROTO_UPDATES = GOLB_PROTO_UPDATES + (
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
        "invert_matrix_in_place",
        "void __fastcall invert_matrix_in_place(TransformMatrix* transform)",
    ),
    (
        "invert_matrix_from_source",
        "void __fastcall invert_matrix_from_source(TransformMatrix* out, TransformMatrix* source)",
    ),
    (
        "multiply_matrix_in_place",
        "TransformMatrix* __thiscall multiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs)",
    ),
    (
        "premultiply_matrix_in_place",
        "TransformMatrix* __thiscall premultiply_matrix_in_place(TransformMatrix* lhs, TransformMatrix* rhs)",
    ),
    ("set_matrix_identity", "void __fastcall set_matrix_identity(TransformMatrix* transform)"),
    ("set_matrix_rotation_identity", "void __fastcall set_matrix_rotation_identity(TransformMatrix* transform)"),
    ("rotate_matrix_world_x", "void __thiscall rotate_matrix_world_x(TransformMatrix* transform, float angle)"),
    ("rotate_matrix_world_y", "void __thiscall rotate_matrix_world_y(TransformMatrix* transform, float angle)"),
    ("rotate_matrix_world_z", "void __thiscall rotate_matrix_world_z(TransformMatrix* transform, float angle)"),
    ("normalize_vector_from_source", "float __thiscall normalize_vector_from_source(Vec3* out, const Vec3* src)"),
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
        "TransformMatrix* __thiscall interpolate_matrix_rotation(TransformMatrix* transform, float alpha)",
    ),
    (
        "compute_kind42_attachment_transform",
        "void __thiscall compute_kind42_attachment_transform(Path* self, float radius, float x, float y, TransformMatrix* transform, float* out_angle)",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t mode_flags)",
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
    (
        "initialize_cutscene_ai",
        "void __thiscall initialize_cutscene_ai(CutScene* cutscene)",
    ),
    (
        "update_cutscene",
        "void __thiscall update_cutscene(CutScene* cutscene)",
    ),
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
        "void __thiscall apply_damage_gauge_delta(DamageGuage* damage_guage, float delta, uint8_t force)",
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
        "int32_t __thiscall handle_subgoldy_collisions(Player* player)",
    ),
    (
        "initialize_subgoldy_resurrect",
        "int32_t __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss)",
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
        "TrackRowCell* __thiscall update_tutorial(Tutorial* tutorial)",
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

# The full SubgameRuntime field map above is the canonical owner view consumed
# by these lifecycle functions. These two prototypes have stable receiver
# overrides in the live database and are safe to replay with the fields.
CORE_SUBGAME_PROTO_UPDATES = (
    ("reset_subgame", "void __thiscall reset_subgame(SubgameRuntime* game)"),
    (
        "complete_subgame",
        "void __thiscall complete_subgame(SubgameRuntime* game, uint8_t completed)",
    ),
)

# These five lifecycle receivers are already SubgameRuntime methods in the
# exact/working matching sources and in the cross-port cRSubGame symbol
# evidence. The exact runtime-row lookup has the same owner proof through the
# canonical array. Older BN databases pin a separate user-defined Game*
# parameter variable on all six. Both the previewed prototype setter and local
# retype API reject the owner-only correction, so report the drift instead of
# claiming a mutation that analysis immediately restores. Preserve BN's
# inferred calling convention here; the ownership pointer is the only intended
# future change.
DEFERRED_SUBGAME_OWNER_PROTO_UPDATES = (
    ("initialize_subgame", "void __fastcall initialize_subgame(SubgameRuntime* game)"),
    (
        "build_subgame_level",
        "void __thiscall build_subgame_level(SubgameRuntime* game, int32_t level_index)",
    ),
    ("destroy_subgame", "void __fastcall destroy_subgame(SubgameRuntime* game)"),
    ("update_subgame", "void __fastcall update_subgame(SubgameRuntime* game)"),
    ("remove_subgame_bods", "void __fastcall remove_subgame_bods(SubgameRuntime* game)"),
    (
        "get_track_runtime_cell_at_world_z",
        "TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(SubgameRuntime* game, Vec3* position)",
    ),
)


def report_deferred_subgame_owner_prototypes(*, target: str) -> list[dict[str, object]]:
    observed_prototypes = current_prototypes(
        REPO_ROOT,
        target=target,
        identifiers=(
            identifier for identifier, _prototype in DEFERRED_SUBGAME_OWNER_PROTO_UPDATES
        ),
    )
    return [
        {
            "op": "proto_owner_deferred",
            "status": "deferred",
            "reason": "existing user-defined Game* parameter is pinned by Binary Ninja",
            "identifier": identifier,
            "desired_prototype": prototype,
            "observed_prototype": observed_prototypes.get(identifier),
        }
        for identifier, prototype in DEFERRED_SUBGAME_OWNER_PROTO_UPDATES
    ]


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
    parser.add_argument(
        "--golb-only",
        action="store_true",
        help="Replay only the GolbShot/path-follow ownership slice.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    if not args.golb_only:
        operations.append(
            types_declare_if_missing(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                required_structs=REQUIRED_HEADER_STRUCTS,
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
                ("RenderableBod", RENDERABLE_BOD_FIELD_UPDATES),
                ("SubgameRuntime", SUBGAME_RUNTIME_FIELD_UPDATES),
                ("Vapour", VAPOUR_FIELD_UPDATES),
                ("JetPack", JETPACK_FIELD_UPDATES),
                ("SnailVisual", SNAIL_VISUAL_FIELD_UPDATES),
                ("TrackRowCell", TRACK_ROW_CELL_FIELD_UPDATES),
                ("TrackAttachmentRuntimeRow", TRACK_ATTACHMENT_RUNTIME_ROW_FIELD_UPDATES),
                ("Path", PATH_FIELD_UPDATES),
                ("JetParticleSlot", JET_PARTICLE_SLOT_FIELD_UPDATES),
                ("SubHover", SUB_HOVER_FIELD_UPDATES),
                ("TipManager", TIP_MANAGER_FIELD_UPDATES),
                ("Player", PLAYER_FIELD_UPDATES),
                ("Snail", SNAIL_FIELD_UPDATES),
                (
                    "PresentationAnimationChannel",
                    PRESENTATION_ANIMATION_CHANNEL_FIELD_UPDATES,
                ),
                ("AnimManager", ANIM_MANAGER_FIELD_UPDATES),
                ("Invincible", INVINCIBLE_FIELD_UPDATES),
                ("CutScene", CUT_SCENE_FIELD_UPDATES),
                ("SnailSkin", SNAIL_SKIN_FIELD_UPDATES),
            ),
            proto_updates=CORE_SUBGAME_PROTO_UPDATES,
        )
    )
    operations.extend(report_deferred_subgame_owner_prototypes(target=args.target))
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=PRESENTATION_SYMBOL_UPDATES,
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
