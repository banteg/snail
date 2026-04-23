#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, apply_struct_field_updates, emit_summary, types_declare

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_player_presentation_types.h"

PLAYER_FIELD_UPDATES = (
    ("0x38", "live_matrix", "TransformMatrix"),
    ("0x80", "resurrect_final_loss", "int32_t"),
    ("0x84", "flag84", "int32_t"),
    ("0x8c", "resurrect_progress", "float"),
    ("0x90", "resurrect_progress_step", "float"),
    ("0x120", "movement_state", "int32_t"),
    ("0x14c", "row_event_cutscene_started", "uint8_t"),
    ("0x2d8", "control_override_active", "uint8_t"),
    ("0x2dc", "cutscene_pitch_cycle", "float"),
    ("0x2e0", "cutscene_pitch_cycle_step", "float"),
    ("0x2e8", "stopwatch", "Stopwatch"),
    ("0x308", "movement_flag_selector", "int32_t"),
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
    ("0x384", "follow_state", "FollowState"),
    ("0x408", "game", "Game*"),
    ("0x40c", "movement_mode_selector", "int32_t"),
    ("0x410", "velocity", "Vec3"),
    ("0x41d", "attachment_exit_pending", "uint8_t"),
    ("0x420", "attachment_exit_anchor_z", "float"),
    ("0x42c", "post_follow_value_a", "float"),
    ("0x430", "post_follow_value_b", "float"),
    ("0x434", "attachment_exit_progress", "float"),
    ("0x438", "attachment_exit_progress_step", "float"),
    ("0x43c", "control_source", "PlayerControlSource*"),
    ("0x440", "completion_handoff_active", "int32_t"),
    ("0x444", "completion_handoff_timer", "float"),
    ("0x448", "completion_handoff_timer_step", "float"),
    ("0x44c", "attachment_exit_gate_a", "uint8_t"),
    ("0x44d", "attachment_exit_gate_b", "uint8_t"),
    ("0x44e", "completion_handoff_voice_gate", "uint8_t"),
    ("0x435c", "slow_commentary_timer", "float"),
    ("0x4360", "slow_commentary_step", "float"),
    ("0x2730", "movement_progress", "float"),
    ("0x2734", "movement_rate_scalar", "float"),
    ("0x273c", "track_z_offset", "float"),
    ("0x2740", "track_z_anchor", "float"),
    ("0x2964", "cached_camera_target_world", "Vec3"),
    ("0x2970", "steering_mode_selector", "int32_t"),
    ("0x2980", "interaction_max_z", "float"),
    ("0x2984", "presentation", "PlayerPresentationController"),
    ("0x4340", "visible_life_stock", "int32_t"),
    ("0x4344", "squidge", "SquidgeState"),
)

GAME_FIELD_UPDATES = (
    ("0x34", "challenge_difficulty_scalar", "float"),
    ("0x38", "track_center_x", "float"),
    ("0x40", "level_mode", "int32_t"),
    ("0x44", "level_mode_arg", "int32_t"),
    ("0x48", "base_subgame_rate", "float"),
    ("0x4c", "runtime_flags", "uint32_t"),
    ("0x50", "first_block_row_count", "int32_t"),
    ("0x54", "runtime_row_count", "int32_t"),
    ("0x58", "completion_row_start", "int32_t"),
    ("0x74621", "pause_gate", "uint8_t"),
    ("0xa854", "track_state_latch", "uint8_t"),
    ("0xa874", "level_segment_count", "int32_t"),
    ("0x356b00", "sub_lazer_pool", "SubLazerSlot[0x14]"),
    ("0x3578c0", "salt_pool", "SaltHazardSlot[0x28]"),
    ("0x3bba4c", "stopwatch", "Stopwatch"),
    ("0x3bbb58", "warning_actor", "WarningActor"),
    ("0x432700", "presentation", "PlayerPresentationController"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SelectedLevelRecord*"),
    ("0xff25d8", "selected_level_record_saved_return_owner", "int32_t"),
    ("0xff25dc", "runtime_track_index", "int32_t"),
    ("0x125e480", "parcel_pool", "TrackParcelRuntime[0x32]"),
    ("0x1270fc8", "subgame_rebuild_selector", "int32_t"),
    ("0x12727d8", "row_event_display", "RowEventDisplayController"),
    ("0x1272828", "times_up", "TimesUpController"),
)

SNAIL_VISUAL_FIELD_UPDATES = (
    ("0x80", "follow_lateral_response", "float"),
    ("0x84", "squidge_primary", "float"),
    ("0x88", "squidge_secondary", "float"),
)

TRACK_ROW_CELL_FIELD_UPDATES = (
    ("0x10", "anchor_position", "Vec3"),
    ("0x38", "attachment_template_record", "PathTemplate*"),
    ("0x3c", "tile_id", "uint8_t"),
    ("0x3d", "tile_flags_3d", "uint8_t"),
)

PATH_TEMPLATE_FIELD_UPDATES = (
    ("0x24", "strip_mesh", "PathTemplateStripMesh*"),
    ("0x30", "header_30", "float"),
    ("0x34", "header_34", "float"),
    ("0x38", "kind", "PathTemplateKind"),
    ("0x3c", "is_mirrored_x", "uint8_t"),
    ("0x40", "side_exit_mode", "uint32_t"),
    ("0x44", "segment_count", "uint32_t"),
    ("0x4c", "segment_count_f", "float"),
    ("0x50", "width_or_scale", "float"),
    ("0x54", "width_cells", "uint32_t"),
    ("0x58", "primary_samples", "PathTemplateSample*"),
    ("0x5c", "secondary_samples", "PathTemplateSample*"),
    ("0x98", "installed_heading_delta", "float"),
    ("0x9c", "special_runtime_flag_9c", "uint8_t"),
    ("0xa0", "header_a0", "float"),
    ("0xa4", "header_a4", "float"),
)

PROTO_UPDATES = (
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
        "set_weapon_animation",
        "int32_t __thiscall set_weapon_animation(PresentationAnimationChannel* channel, int32_t animation_id, uint8_t immediate, int32_t initial_frame)",
    ),
    (
        "set_snail_weapon",
        "void __thiscall set_snail_weapon(PlayerPresentationController* presentation, int32_t movement_flags)",
    ),
    (
        "initialize_cutscene",
        "int32_t __thiscall initialize_cutscene(PlayerPresentationController* presentation)",
    ),
    (
        "initialize_cutscene_ai",
        "int32_t __fastcall initialize_cutscene_ai(CutsceneAI* cutscene_ai)",
    ),
    (
        "update_cutscene",
        "int32_t __thiscall update_cutscene(CutsceneAI* cutscene_ai)",
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
        "handle_subgoldy_collisions",
        "int32_t __thiscall handle_subgoldy_collisions(Player* player)",
    ),
    (
        "initialize_subgoldy_resurrect",
        "int32_t __thiscall initialize_subgoldy_resurrect(Player* player, int32_t final_loss)",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(InvincibleShellController* shell)",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(InvincibleShellController* shell)",
    ),
    ("update_invincible_shell", "void __thiscall update_invincible_shell(InvincibleShellController* shell)"),
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
    operations.append(types_declare(REPO_ROOT, target=args.target, header_path=header_path))
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
            struct_name="PathTemplate",
            updates=PATH_TEMPLATE_FIELD_UPDATES,
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
        apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        )
    )
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
