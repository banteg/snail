#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    apply_symbol_updates,
    emit_summary,
    types_declare_if_missing,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_player_presentation_types.h"

PRESENTATION_SYMBOL_UPDATES = (
    ("0x4086d0", "initialize_player_presentation_controller"),
    ("0x497354", "g_player_presentation_noop_vtable"),
    ("0x497358", "g_invincible_shell_update_vtable"),
    ("0x49735c", "g_presentation_animation_channel_noop_vtable"),
)

PRESENTATION_CONTROLLER_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x1894", "invincible_shell", "Invincible"),
    ("0x1958", "cutscene", "CutScene"),
)

PRESENTATION_ANIMATION_CHANNEL_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
)

INVINCIBLE_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x28", "color", "Color4f"),
    ("0x38", "transform", "TransformMatrix"),
    ("0x80", "state", "int32_t"),
    ("0x84", "spin_phase", "float"),
    ("0x88", "spin_phase_step", "float"),
    ("0x8c", "fade_progress", "float"),
    ("0x90", "fade_step", "float"),
    ("0x98", "cutscene_roll_progress", "float"),
    ("0x9c", "cutscene_roll_step", "float"),
    ("0xa0", "channel_release_steps_active", "uint8_t"),
)

CUT_SCENE_FIELD_UPDATES = (
    ("0x00", "presentation", "PlayerPresentationController*"),
    ("0x04", "player", "Player*"),
    ("0x08", "camera_mode", "int32_t"),
    ("0x0c", "state", "int32_t"),
    ("0x10", "live_matrix", "TransformMatrix"),
    ("0x50", "progress", "float"),
    ("0x54", "progress_step", "float"),
    ("0x58", "force_camera_update", "uint8_t"),
)
REQUIRED_HEADER_STRUCTS = (
    "PathManager",
    "Game",
    "SnailVisual",
    "BodNode",
    "BodBase",
    "RenderableBod",
    "FringeObject",
    "TrackRowCell",
    "TrackAttachmentRuntimeRow",
    "Path",
    "PathPair",
    "DamageGuage",
    "ProgressBar",
    "Warning",
    "Nuke",
    "Cameraman",
    "Squidge",
    "Invincible",
    "CutScene",
    "Player",
    "JetParticleSlot",
    "JetpackGaugeController",
    "Tutorial",
    "Completion",
    "TimesUp",
)

PLAYER_FIELD_UPDATES = (
    ("0x38", "live_matrix", "TransformMatrix"),
    ("0x80", "resurrect_final_loss", "int32_t"),
    ("0x84", "resurrect_active", "int32_t"),
    ("0x8c", "resurrect_progress", "float"),
    ("0x90", "resurrect_progress_step", "float"),
    ("0x98", "ghost_sprite_a", "Sprite*"),
    ("0x9c", "ghost_sprite_b", "Sprite*"),
    ("0x120", "movement_state", "int32_t"),
    ("0x14c", "row_event_cutscene_started", "uint8_t"),
    ("0x150", "nuke", "Nuke"),
    ("0x1cc", "movement_sound_variant_sample", "int32_t"),
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
    ("0x2e8", "stopwatch", "Stopwatch"),
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
    ("0x370", "heading_roll", "float"),
    ("0x374", "nuke_effect_progress", "float"),
    ("0x378", "nuke_effect_progress_step", "float"),
    ("0x380", "player_slot", "int32_t"),
    ("0x384", "follow_state", "FollowState"),
    ("0x3c4", "damage_gauge", "DamageGuage"),
    ("0x3f0", "progress_bar", "ProgressBar"),
    ("0x3f4", "warning", "Warning"),
    ("0x404", "lives", "int32_t"),
    ("0x408", "game", "Game*"),
    ("0x40c", "movement_mode_selector", "int32_t"),
    ("0x410", "velocity", "Vec3"),
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
    ("0x435c", "slow_commentary_timer", "float"),
    ("0x4360", "slow_commentary_step", "float"),
    ("0x2730", "movement_fire_progress", "float"),
    ("0x2734", "movement_fire_progress_step", "float"),
    ("0x2738", "slide_extension_threshold_z", "float"),
    ("0x273c", "track_z_offset", "float"),
    ("0x2740", "track_z_anchor", "float"),
    ("0x2744", "completion_handoff_cycle_progress", "float"),
    ("0x2748", "completion_handoff_cycle_step", "float"),
    ("0x2750", "jetpack_gauge", "JetpackGaugeController"),
    ("0x2964", "cached_camera_target_world", "Vec3"),
    ("0x2970", "steering_mode_selector", "int32_t"),
    ("0x2980", "interaction_max_z", "float"),
    ("0x2984", "presentation", "PlayerPresentationController"),
    ("0x4340", "visible_life_stock", "int32_t"),
    ("0x4344", "squidge", "Squidge"),
)

GAME_FIELD_UPDATES = (
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
    ("0x74621", "pause_gate", "uint8_t"),
    ("0xa854", "track_state_latch", "uint8_t"),
    ("0xa858", "tutorial", "Tutorial"),
    ("0xa874", "level_segment_count", "int32_t"),
    ("0x356b00", "sub_lazers", "SubLazerSlot[0x14]"),
    ("0x3578c0", "salt_hazards", "SaltHazardSlot[0x28]"),
    ("0x3bba4c", "stopwatch", "Stopwatch"),
    ("0x3bbb58", "warning", "Warning"),
    ("0x432700", "presentation", "PlayerPresentationController"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SelectedLevelRecord*"),
    ("0xff25d8", "selected_level_record_saved_return_owner", "int32_t"),
    ("0xff25dc", "replay_update_cursor", "int32_t"),
    ("0xff25e4", "runtime_track_index", "int32_t"),
    ("0xff2914", "path_pairs", "PathPair[63]"),
    ("0x125e480", "parcel_pool", "TrackParcelRuntime[0x32]"),
    ("0x1270fc8", "subgame_rebuild_selector", "int32_t"),
    ("0x12727d8", "completion", "Completion"),
    ("0x1272828", "times_up", "TimesUp"),
)

SNAIL_VISUAL_FIELD_UPDATES = (
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

# Authored cRPath field overlay. The Windows runtime owns 126 exact 0xa8-byte
# instances as 63 adjacent PathPair records.
PATH_FIELD_UPDATES = (
    ("0x24", "strip_mesh", "Object*"),
    ("0x30", "header_30", "float"),
    ("0x34", "header_34", "float"),
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
    ("0x98", "installed_heading_delta", "float"),
    ("0x9c", "has_entry_mesh_transition", "uint8_t"),
    ("0xa0", "entry_transition_strip_mesh", "Object*"),
    ("0xa4", "entry_base_strip_mesh", "Object*"),
)

SALT_HAZARD_FIELD_UPDATES = (
    ("0x80", "state", "int32_t"),
    ("0x88", "owner_game", "Game*"),
    ("0x8c", "fade_alpha", "float"),
    ("0x90", "spawn_velocity_y", "float"),
    ("0x94", "collision_armed", "uint8_t"),
)

JET_PARTICLE_SLOT_FIELD_UPDATES = (
    ("0x00", "sprite", "Sprite*"),
    ("0x04", "wobble_x", "float"),
    ("0x08", "wobble_y", "float"),
    ("0x0c", "wobble_alpha", "float"),
)

JETPACK_GAUGE_FIELD_UPDATES = (
    ("0x00", "progress", "float"),
    ("0x04", "progress_step", "float"),
    ("0x0c", "state", "int32_t"),
    ("0x10", "player", "Player*"),
    ("0x14", "wobble_x", "float"),
    ("0x18", "wobble_y", "float"),
    ("0x1c", "wobble_alpha", "float"),
    ("0x20", "particle_slots", "JetParticleSlot[0x1e]"),
    ("0x200", "game", "Game*"),
    ("0x20c", "warning_intensity_latch", "float"),
    ("0x210", "warning_intensity", "float"),
)

TIP_MANAGER_FIELD_UPDATES = (
    ("0x00", "bod", "BodBase"),
    ("0x38", "slots", "TipSlot[0x3]"),
)

PROTO_UPDATES = (
    (
        "find_segment_path_index_by_name",
        "int32_t __thiscall find_segment_path_index_by_name(PathManager* manager, char* name)",
    ),
    (
        "initialize_player_presentation_controller",
        "PlayerPresentationController* __thiscall initialize_player_presentation_controller(PlayerPresentationController* presentation)",
    ),
    (
        "initialize_matrix_from_values",
        "TransformMatrix* __thiscall initialize_matrix_from_values(TransformMatrix* transform, float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)",
    ),
    (
        "invert_matrix_from_source",
        "TransformMatrix* __fastcall invert_matrix_from_source(TransformMatrix* out, TransformMatrix* source)",
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
        "get_track_runtime_cell_at_world_z",
        "TrackAttachmentRuntimeRow* __thiscall get_track_runtime_cell_at_world_z(Game* game, Vec3* position)",
    ),
    (
        "set_weapon_animation",
        "int32_t __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t initial_frame)",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(PlayerPresentationController* presentation, int32_t movement_flags)",
    ),
    (
        "initialize_cutscene",
        "void __thiscall initialize_cutscene(PlayerPresentationController* presentation)",
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
        "int32_t __thiscall dispatch_cutscene_animation(PlayerPresentationController* presentation, int32_t animation_id, uint8_t immediate, int32_t initial_frame)",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkinTransitionState* state)",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkinTransitionState* state)",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(PlayerPresentationController* presentation)",
    ),
    (
        "initialize_subgoldy",
        "int32_t __thiscall initialize_subgoldy(Player* player, int32_t player_slot)",
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
        "int32_t __thiscall initialize_jetpack_gauge(JetpackGaugeController* gauge)",
    ),
    (
        "update_jetpack_gauge",
        "int32_t __thiscall update_jetpack_gauge(JetpackGaugeController* gauge)",
    ),
    (
        "arm_jetpack_gauge",
        "int32_t __thiscall arm_jetpack_gauge(JetpackGaugeController* gauge)",
    ),
    (
        "end_jetpack_hover",
        "void __fastcall end_jetpack_hover(JetpackGaugeController* gauge)",
    ),
    (
        "uninit_jet_particles",
        "void __fastcall uninit_jet_particles(JetpackGaugeController* gauge)",
    ),
    (
        "initialize_jet_particles",
        "void __fastcall initialize_jet_particles(JetpackGaugeController* gauge)",
    ),
    (
        "update_jet_particles",
        "void __fastcall update_jet_particles(JetpackGaugeController* gauge)",
    ),
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
        "enqueue_tip_message",
        "TipSlot* __thiscall enqueue_tip_message(TipManager* manager, TipMessageDefinition* definition, int32_t show_disable_button)",
    ),
    (
        "initialize_tip",
        "void __thiscall initialize_tip(TipSlot* slot, TipMessageDefinition* definition, int32_t show_disable_button)",
    ),
    ("update_tip", "void* __fastcall update_tip(TipSlot* slot)"),
    ("update_tip_manager", "void __fastcall update_tip_manager(TipManager* manager)"),
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


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply the narrow player-presentation type slice to the active Binary Ninja target "
            "and replay the proven Player field overlays."
        )
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
    return parser.parse_args()
def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=REQUIRED_HEADER_STRUCTS,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Game",
            updates=GAME_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SnailVisual",
            updates=SNAIL_VISUAL_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="TrackRowCell",
            updates=TRACK_ROW_CELL_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="TrackAttachmentRuntimeRow",
            updates=TRACK_ATTACHMENT_RUNTIME_ROW_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Path",
            updates=PATH_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="SaltHazardSlot",
            updates=SALT_HAZARD_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="JetParticleSlot",
            updates=JET_PARTICLE_SLOT_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="JetpackGaugeController",
            updates=JETPACK_GAUGE_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="TipManager",
            updates=TIP_MANAGER_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Player",
            updates=PLAYER_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="PlayerPresentationController",
            updates=PRESENTATION_CONTROLLER_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="PresentationAnimationChannel",
            updates=PRESENTATION_ANIMATION_CHANNEL_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="Invincible",
            updates=INVINCIBLE_FIELD_UPDATES,
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
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=PRESENTATION_SYMBOL_UPDATES,
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
