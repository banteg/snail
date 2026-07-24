#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_user_var_updates,
    current_struct_size,
    emit_summary,
    reanalyze_functions,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frame_renderer_types.h"
OBJECT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_object_render_types.h"
SPRITE_HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"
OBJECT_REQUIRED_STRUCTS = (
    "tColour",
    "Vec3",
    "TransformMatrix",
    "RenderableBod",
)
SPRITE_REQUIRED_STRUCTS = (
    "Sprite",
)
REQUIRED_STRUCTS = (
    "SpriteDepthNode",
    "FrontendFadeCallback",
    "FrontendFade",
    "InputState",
    "GameInputBodBase",
    "GameInput",
    "MouseCursorState",
    "FrontendOverlayColorLerp",
    "GamePlayer",
    "GamePlayerInitStrideView",
    "FrameBodNode",
    "FrameBodList",
    "BodNode",
    "BodList",
    "FrameBodBase",
    "FrameRenderableBod",
    "FrameRenderCamera",
    "FrameOverlay",
    "Viewport",
    "FrameContactTargetRegistry",
    "FrameSubgameRuntime",
    "Track",
    "BorderStackEntry",
    "BorderStack",
    "BorderRecord",
    "BorderManager",
    "GameRoot",
)

SYMBOL_UPDATES = (
    ("0x4972f4", "g_game_player_callback_table"),
    ("0x4dfb10", "g_post_sprite_bods"),
    ("0x4e5510", "g_sprite_depth_nodes"),
    ("0x4f7050", "g_sprite_depth_buckets"),
    ("0x814c94", "g_sprite_active_heads"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x404350", "initialize_border_stack"),
    ("0x408000", "initialize_game_player"),
    ("0x40ab00", "initialize_frontend_overlay_color_lerp"),
    ("0x40ab40", "draw_frontend_overlay_color_lerp"),
    ("0x40abc0", "begin_frontend_fade_out"),
    ("0x40abe0", "begin_frontend_fade_in"),
    ("0x40abf0", "update_frontend_transition_overlay"),
    ("0x4107d0", "update_frontend_state_machine"),
    ("0x4119c0", "initialize_game_window_and_input_wrapper"),
    ("0x4119d0", "initialize_game_window_and_input"),
    ("0x413670", "configure_sprite_render_state"),
    ("0x44c3b0", "is_mouse_captured"),
    ("0x44c3c0", "capture_mouse_cursor"),
    ("0x44c400", "release_mouse_cursor"),
    ("0x44e410", "update_sprite_facing_angle"),
    ("0x44e900", "attach_render_camera_source"),
    ("0x44e920", "initialize_render_camera_slot"),
    ("0x48ba3f", "operator_new"),
)

DATA_VAR_UPDATES = (
    ("0x4972f4", "void*"),
    ("0x4df904", "GameRoot*"),
    ("0x4dfb10", "RenderableBod*"),
    ("0x4e5510", "SpriteDepthNode[3000]"),
    ("0x4f7050", "SpriteDepthNode*[256]"),
    ("0x814c94", "Sprite*[5]"),
)

PROTO_UPDATES = (
    (
        "operator_new",
        "void* __cdecl operator_new(uint32_t size)",
    ),
    (
        "initialize_game_window_and_input_wrapper",
        "int32_t __cdecl initialize_game_window_and_input_wrapper(char* window_name)",
    ),
    (
        "initialize_game_window_and_input",
        "int32_t __cdecl initialize_game_window_and_input(char* window_name)",
    ),
    (
        "initialize_game_player",
        "GamePlayer* __thiscall initialize_game_player(GamePlayer* player)",
    ),
    (
        "initialize_border_stack",
        "void __thiscall initialize_border_stack(BorderStack* stack)",
    ),
    (
        "initialize_frontend_overlay_color_lerp",
        "void __thiscall initialize_frontend_overlay_color_lerp("
        "FrontendOverlayColorLerp* overlay, int32_t state)",
    ),
    (
        "draw_frontend_overlay_color_lerp",
        "void __thiscall draw_frontend_overlay_color_lerp("
        "FrontendOverlayColorLerp* overlay)",
    ),
    (
        "begin_frontend_fade_out",
        "void __thiscall begin_frontend_fade_out("
        "FrontendFade* fade, FrontendFadeCallback completion_callback)",
    ),
    (
        "begin_frontend_fade_in",
        "void __thiscall begin_frontend_fade_in(FrontendFade* fade)",
    ),
    (
        "update_frontend_transition_overlay",
        "void __thiscall update_frontend_transition_overlay(FrontendFade* fade)",
    ),
    (
        "update_frontend_state_machine",
        "void __thiscall update_frontend_state_machine(GamePlayer* player)",
    ),
    (
        "is_mouse_captured",
        "uint8_t __thiscall is_mouse_captured(MouseCursorState* mouse)",
    ),
    (
        "capture_mouse_cursor",
        "void __thiscall capture_mouse_cursor(MouseCursorState* mouse)",
    ),
    (
        "release_mouse_cursor",
        "void __thiscall release_mouse_cursor(MouseCursorState* mouse)",
    ),
    (
        "attach_render_camera_source",
        "int32_t __thiscall attach_render_camera_source("
        "Viewport* viewport, FrameRenderCamera* camera)",
    ),
    (
        "initialize_render_camera_slot",
        "Viewport* __thiscall initialize_render_camera_slot(Viewport* viewport)",
    ),
    (
        "run_frame_update",
        "int32_t __thiscall run_frame_update(GameRoot* game)",
    ),
    (
        "render_game_frame",
        "void __thiscall render_game_frame(GameRoot* game)",
    ),
    (
        "draw_sprite_quad",
        "int32_t __cdecl draw_sprite_quad(Vec3* position, Sprite* sprite)",
    ),
    (
        "configure_sprite_render_state",
        "int32_t __cdecl configure_sprite_render_state(Sprite* sprite)",
    ),
    (
        "update_sprite_facing_angle",
        "void __thiscall update_sprite_facing_angle("
        "Sprite* sprite, const TransformMatrix* matrix)",
    ),
    (
        "select_level_track_texture_set",
        "void __thiscall select_level_track_texture_set(Track* track, int32_t texture_set)",
    ),
)

BORDER_KILL_REANALYSIS_FUNCTIONS = (
    "initialize_border_stack",
    "kill_border",
    "queue_frontend_widget_flag_after_delay",
    "border_input_text",
    "reset_tooltip",
    "update_tooltip",
    "flush_row_event_display",
    "destroy_completion_screen",
    "destroy_galaxy",
    "destroy_challenge_setup_screen",
    "destroy_options_menu",
    "uninit_thanks_screen",
    "destroy_subgame",
    "uninit_pause_menu",
    "update_click_start",
    "uninit_times_up",
    "uninit_warning",
    "kill_tip_widgets",
)

MOUSE_CURSOR_FIELD_UPDATES = (
    ("0x00", "captured", "uint8_t"),
    ("0x04", "live_x", "float"),
    ("0x08", "live_y", "float"),
    ("0x0c", "saved_x", "float"),
    ("0x10", "saved_y", "float"),
    ("0x14", "suppress_next_draw", "uint8_t"),
)

FRONTEND_FADE_FIELD_UPDATES = (
    ("0x00", "state", "int32_t"),
    ("0x04", "alpha", "float"),
    ("0x08", "hold_progress", "float"),
    ("0x0c", "hold_progress_step", "float"),
    ("0x10", "completion_callback", "FrontendFadeCallback"),
)

FRONTEND_OVERLAY_FIELD_UPDATES = (
    ("0x00", "state", "int32_t"),
    ("0x04", "target", "tColour"),
    ("0x14", "current", "tColour"),
)

FRAME_RENDER_CAMERA_FIELD_UPDATES = (
    ("0x00", "body", "FrameRenderableBod"),
    ("0x80", "view_matrix", "FrameTransformMatrix"),
    ("0xc0", "fov_degrees", "float"),
    ("0xc4", "render_mask", "uint32_t"),
)

VIEWPORT_FIELD_UPDATES = (
    ("0x00", "unknown_00", "int32_t"),
    ("0x04", "sort_key", "int32_t"),
    ("0x08", "flags", "uint32_t"),
    ("0x0c", "viewport_x", "float"),
    ("0x10", "viewport_y", "float"),
    ("0x14", "viewport_width", "float"),
    ("0x18", "viewport_height", "float"),
    ("0x1c", "unknown_1c", "float"),
    ("0x20", "camera", "FrameRenderCamera*"),
    ("0x24", "draw_world", "uint8_t"),
    ("0x25", "unknown_25", "uint8_t[3]"),
)

SPRITE_DEPTH_NODE_FIELD_UPDATES = (
    ("0x00", "next", "SpriteDepthNode*"),
    ("0x04", "position", "FrameVec3"),
    ("0x10", "depth_key", "float"),
    ("0x14", "sprite", "Sprite*"),
)

# The native root constructor allocates one exact 0x12e6ff4-byte GameRoot and
# keeps that owner in ESI through publication to g_game_base. Once the root is
# typed, Binary Ninja initially promotes &array to pointer-to-array values for
# the three fixed constructor loops. Preserve their physical element cursors,
# plus the zero-offset BodBase walk through RootBodCatalog, as distinct exact
# lifetimes instead of accepting false parent-relative expressions.
ROOT_CONSTRUCTOR_USER_VAR_UPDATES = (
    (
        "construct_game_runtime",
        "RegisterVariableSourceType",
        534,
        72,
        "game",
        "GameRoot*",
    ),
    (
        "construct_game_runtime",
        "RegisterVariableSourceType",
        569,
        73,
        "game_input_cursor",
        "GameInput*",
    ),
    (
        "construct_game_runtime",
        "RegisterVariableSourceType",
        596,
        73,
        "player_cursor",
        "GamePlayer*",
    ),
    (
        "construct_game_runtime",
        "RegisterVariableSourceType",
        634,
        73,
        "viewport_cursor",
        "Viewport*",
    ),
    (
        "construct_game_runtime",
        "RegisterVariableSourceType",
        824,
        73,
        "root_bod_cursor",
        "BodBase*",
    ),
)

# The world initializer computes `game + player_index * 0x1f8`, then reaches
# GameRoot::players through the fixed +0x124 bias. Preserve that shifted
# borrowed view instead of falsely retyping the carried address as GamePlayer*.
WORLD_INITIALIZER_USER_VAR_UPDATES = (
    (
        "initialize_game_assets_and_world",
        "RegisterVariableSourceType",
        21460,
        72,
        "player_initializer_stride_view",
        "GamePlayerInitStrideView*",
    ),
)

# The root list intentionally retains its generic BodNode* contract. Render()
# performs the source-level zero-offset downcast before consuming the complete
# RenderableBod prefix. Its reverse replay cursor borrows the same owner from
# the transient pointer stack without asserting that stack's unknown capacity.
RENDER_USER_VAR_UPDATES = (
    (
        "render_game_frame",
        "StackVariableSourceType",
        299,
        -128,
        "post_sprite_count",
        "int32_t",
    ),
    (
        "render_game_frame",
        "StackVariableSourceType",
        303,
        -124,
        "rendered_bod_count",
        "int32_t",
    ),
    (
        "render_game_frame",
        "StackVariableSourceType",
        321,
        -116,
        "camera_order_cursor",
        "int32_t*",
    ),
    (
        "render_game_frame",
        "StackVariableSourceType",
        55,
        -112,
        "rendered_sprite_count",
        "int32_t",
    ),
    (
        "render_game_frame",
        "StackVariableSourceType",
        317,
        -104,
        "remaining_camera_count",
        "int32_t",
    ),
    (
        "render_game_frame",
        "RegisterVariableSourceType",
        445,
        72,
        "bod",
        "RenderableBod*",
    ),
    (
        "render_game_frame",
        "RegisterVariableSourceType",
        912,
        67,
        "bucket_node",
        "SpriteDepthNode*",
    ),
    (
        "render_game_frame",
        "RegisterVariableSourceType",
        1280,
        73,
        "post_cursor",
        "RenderableBod**",
    ),
)

GAME_PLAYER_FIELD_UPDATES = (
    ("0x00", "body", "FrameRenderableBod"),
    ("0x80", "player_name", "char[0x14]"),
    ("0x94", "frontend_state", "int32_t"),
    ("0x98", "saved_frontend_state", "int32_t"),
    ("0xa0", "camera", "FrameRenderCamera"),
    ("0x168", "game_input", "GameInput*"),
    ("0x16c", "mouse_cursor", "MouseCursorState"),
    ("0x184", "frontend_overlay", "FrontendOverlayColorLerp"),
    ("0x1a8", "completion_handoff_transform", "FrameTransformMatrix"),
    ("0x1e8", "redispatch_requested", "uint8_t"),
    ("0x1e9", "high_score_entry_pending", "uint8_t"),
    ("0x1ec", "selected_high_score_rank", "int32_t"),
    ("0x1f0", "selected_high_score_mode", "int32_t"),
)

GAME_PLAYER_INIT_STRIDE_VIEW_FIELD_UPDATES = (
    ("0x00", "root_to_player", "uint8_t[0x124]"),
    ("0x124", "player", "GamePlayer"),
)

GAME_INPUT_FIELD_UPDATES = (
    ("0x00", "bod", "GameInputBodBase"),
    ("0x38", "input", "InputState"),
)

FRAME_SUBGAME_RUNTIME_FIELD_UPDATES = (
    ("0x00", "scan_reset", "uint8_t"),
    ("0x01", "camera_snap_requested", "uint8_t"),
    ("0x02", "track_mirror_enabled", "uint8_t"),
    ("0x04", "track_mirror_repeat_count", "int32_t"),
    ("0x08", "resume_requested", "uint8_t"),
    ("0x09", "subgame_pause_gate", "uint8_t"),
    ("0x0c", "pause_fade", "float"),
    ("0x10", "pause_fade_step", "float"),
    ("0x3c", "subgame_state", "int32_t"),
    ("0x40", "level_mode", "int32_t"),
)

BORDER_STACK_ENTRY_FIELD_UPDATES = (
    ("0x00", "generation", "int32_t"),
    ("0x04", "widget", "FrontendWidget*"),
)

BORDER_STACK_FIELD_UPDATES = (
    ("0x00", "generation", "int32_t"),
    ("0x04", "entry_count", "int32_t"),
    ("0x08", "entries", "BorderStackEntry[200]"),
    ("0x648", "owner", "BorderManager*"),
)

BORDER_RECORD_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x04", "list_flags", "uint32_t"),
    ("0x08", "list_prev", "FrameBodBase*"),
    ("0x0c", "list_next", "FrameBodBase*"),
    ("0x10", "position", "FrameVec3"),
    ("0x1c", "render_arg_1c", "float"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "tColour"),
    ("0x6c", "color_06c", "tColour"),
    ("0x19c", "created_time", "int32_t"),
    ("0x1a0", "flags", "int32_t"),
    ("0x1ac", "color_1ac", "tColour"),
    ("0x1bc", "color_1bc", "tColour"),
    ("0x1cc", "color_1cc", "tColour"),
    ("0x1dc", "color_1dc", "tColour"),
    ("0x1ec", "color_1ec", "tColour"),
    ("0x1fc", "color_1fc", "tColour"),
    ("0x20c", "hover_blend_target", "float"),
    ("0x210", "hover_blend_current", "float"),
    ("0x214", "idle_padding", "float"),
    ("0x218", "hot_padding", "float"),
    ("0x21c", "target_padding", "float"),
    ("0x220", "active_padding", "float"),
)

BORDER_MANAGER_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x04", "list_flags", "uint32_t"),
    ("0x08", "list_prev", "FrameBodBase*"),
    ("0x0c", "list_next", "FrameBodBase*"),
    ("0x10", "position", "FrameVec3"),
    ("0x1c", "render_arg_1c", "float"),
    ("0x20", "render_arg_20", "float"),
    ("0x24", "object", "void*"),
    ("0x28", "color", "tColour"),
    ("0x38", "border_stack", "BorderStack"),
    ("0x684", "borders", "BorderRecord[150]"),
    ("0x4359c", "delayed_widget_flags", "int32_t"),
    ("0x435a0", "delayed_widget_active", "uint8_t"),
    ("0x435a4", "delayed_widget_progress", "float"),
    ("0x435a8", "delayed_widget_progress_step", "float"),
    ("0x435ac", "delayed_widget", "FrontendWidget*"),
    ("0x435b0", "justify_centre", "float"),
)

GAME_ROOT_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x04", "fog_enabled", "uint8_t"),
    ("0x08", "fog_start", "float"),
    ("0x0c", "fog_end", "float"),
    ("0x10", "fog_density", "float"),
    ("0x14", "fog_color", "tColour"),
    ("0x24", "fade", "FrontendFade"),
    ("0x38", "frontend_quit_requested", "int32_t"),
    ("0x3c", "fixed_update_count", "int32_t"),
    ("0x40", "player_count", "int32_t"),
    ("0x44", "game_inputs", "GameInput[2]"),
    ("0x124", "players", "GamePlayer[2]"),
    ("0x514", "unknown_000514", "int32_t"),
    ("0x518", "fixed_update_accumulator", "float"),
    ("0x51c", "frame_counter", "int32_t"),
    ("0x520", "input_sampling_gate", "uint8_t"),
    ("0x568", "frontend_link_latch", "uint8_t"),
    ("0x56c", "render_skip_count", "int32_t"),
    ("0x570", "inactive_bod_sentinel", "FrameBodBase"),
    ("0x5a8", "active_bod_list", "BodList"),
    ("0x5b4", "viewports", "Viewport[5]"),
    ("0x67c", "overlay_0", "FrameOverlay"),
    ("0x7c8", "overlay_1", "FrameOverlay"),
    ("0x914", "overlay_2", "FrameOverlay"),
    ("0xa60", "root_noop_renderable", "FrameRenderableBod"),
    ("0xb24", "track", "Track"),
    ("0xb48", "unknown_000b48", "int32_t"),
    ("0xb4c", "border_manager", "BorderManager"),
    ("0x74618", "subgame", "FrameSubgameRuntime"),
)


def resolved_game_root_field_updates(*, target: str) -> tuple[tuple[str, str, str], ...]:
    """Prefer complete root subowners after their canonical types are available."""
    border_manager_type = resolved_border_manager_struct_name(target=target)
    subgame_type = (
        "SubgameRuntime"
        if current_struct_size(
            REPO_ROOT, target=target, struct_name="SubgameRuntime"
        )
        == 0x1272838
        else "FrameSubgameRuntime"
    )
    overlay_type = (
        "Overlay"
        if current_struct_size(REPO_ROOT, target=target, struct_name="Overlay")
        == 0x14C
        else "FrameOverlay"
    )
    root_renderable_type = (
        "RenderableBod"
        if current_struct_size(
            REPO_ROOT, target=target, struct_name="RenderableBod"
        )
        == 0x80
        else "FrameRenderableBod"
    )
    return tuple(
        (
            offset,
            name,
            border_manager_type
            if name == "border_manager"
            else subgame_type
            if name == "subgame"
            else overlay_type
            if name in {"overlay_0", "overlay_1", "overlay_2"}
            else root_renderable_type
            if name == "root_noop_renderable"
            else field_type,
        )
        for offset, name, field_type in GAME_ROOT_FIELD_UPDATES
    )


def resolved_border_manager_struct_name(*, target: str) -> str:
    """Require the exact canonical manager instead of silently degrading ownership."""
    size = current_struct_size(
        REPO_ROOT, target=target, struct_name="BorderManager"
    )
    if size != 0x435B4:
        raise RuntimeError(
            "BorderManager must be exactly 0x435b4 bytes after header replay; "
            f"observed {size!r}"
        )
    return "BorderManager"


def resolved_sprite_struct_name(*, target: str) -> str:
    """Require the canonical sprite owner before borrowing it in render state."""
    size = current_struct_size(REPO_ROOT, target=target, struct_name="Sprite")
    if size != 0xB4:
        raise RuntimeError(
            "Sprite must be exactly 0xb4 bytes before renderer replay; "
            f"observed {size!r}"
        )
    return "Sprite"


def resolved_renderable_bod_struct_name(*, target: str) -> str:
    """Require the canonical renderable owner used after the root-list cast."""
    size = current_struct_size(
        REPO_ROOT, target=target, struct_name="RenderableBod"
    )
    if size != 0x80:
        raise RuntimeError(
            "RenderableBod must be exactly 0x80 bytes before renderer replay; "
            f"observed {size!r}"
        )
    return "RenderableBod"


def verify_game_player_initializer_stride_view(*, target: str) -> dict[str, object]:
    """Fail closed unless the shifted player borrow lands on one exact owner."""
    observed_sizes = {
        "GamePlayer": current_struct_size(
            REPO_ROOT, target=target, struct_name="GamePlayer"
        ),
        "GamePlayerInitStrideView": current_struct_size(
            REPO_ROOT, target=target, struct_name="GamePlayerInitStrideView"
        ),
    }
    expected_sizes = {
        "GamePlayer": 0x1F8,
        "GamePlayerInitStrideView": 0x31C,
    }
    mismatches = {
        name: {"expected": expected_sizes[name], "observed": observed}
        for name, observed in observed_sizes.items()
        if observed != expected_sizes[name]
    }
    if mismatches:
        raise RuntimeError(
            "refusing player-initializer stride replay with size mismatches: "
            f"{mismatches!r}"
        )
    return {
        "op": "owner_size_verify",
        "status": "verified",
        "owner_sizes": observed_sizes,
    }


def resolved_proto_updates(*, target: str) -> tuple[tuple[str, str], ...]:
    """Keep the border lifecycle receiver on the best available exact owner."""
    border_manager_type = resolved_border_manager_struct_name(target=target)
    return (
        *PROTO_UPDATES,
        (
            "kill_all_borders",
            f"void __thiscall kill_all_borders({border_manager_type}* manager)",
        ),
        (
            "kill_border",
            "void __thiscall kill_border("
            f"{border_manager_type}* manager, FrontendWidget* widget)",
        ),
        (
            "allocate_border",
            f"FrontendWidget* __thiscall allocate_border({border_manager_type}* manager)",
        ),
        (
            "activate_all_borders",
            f"void __thiscall activate_all_borders({border_manager_type}* manager)",
        ),
        (
            "hide_all_borders",
            f"void __thiscall hide_all_borders({border_manager_type}* manager)",
        ),
        (
            "unhide_all_borders",
            f"void __thiscall unhide_all_borders({border_manager_type}* manager)",
        ),
        (
            "queue_frontend_widget_flag_after_delay",
            "void __thiscall queue_frontend_widget_flag_after_delay("
            f"{border_manager_type}* manager, FrontendWidget* widget, "
            "int32_t queued_flags)",
        ),
        (
            "update_border_manager",
            f"void __thiscall update_border_manager({border_manager_type}* manager)",
        ),
        (
            "initialize_border_record",
            "BorderRecord* __thiscall initialize_border_record(BorderRecord* record)",
        ),
        (
            "set_border_justify_centre",
            "void __thiscall set_border_justify_centre("
            f"{border_manager_type}* manager, float justify_centre)",
        ),
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the root frame-renderer ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=OBJECT_HEADER_PATH,
            required_structs=OBJECT_REQUIRED_STRUCTS,
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=SPRITE_HEADER_PATH,
            required_structs=SPRITE_REQUIRED_STRUCTS,
        ),
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=REQUIRED_STRUCTS,
        )
    ]

    resolved_sprite_struct_name(target=args.target)
    resolved_renderable_bod_struct_name(target=args.target)
    operations.append(
        verify_game_player_initializer_stride_view(target=args.target)
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
        )
    )
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("GameInput", GAME_INPUT_FIELD_UPDATES),
                ("MouseCursorState", MOUSE_CURSOR_FIELD_UPDATES),
                ("FrontendFade", FRONTEND_FADE_FIELD_UPDATES),
                ("FrontendOverlayColorLerp", FRONTEND_OVERLAY_FIELD_UPDATES),
                ("FrameRenderCamera", FRAME_RENDER_CAMERA_FIELD_UPDATES),
                ("Viewport", VIEWPORT_FIELD_UPDATES),
                ("SpriteDepthNode", SPRITE_DEPTH_NODE_FIELD_UPDATES),
                ("GamePlayer", GAME_PLAYER_FIELD_UPDATES),
                (
                    "GamePlayerInitStrideView",
                    GAME_PLAYER_INIT_STRIDE_VIEW_FIELD_UPDATES,
                ),
                ("FrameSubgameRuntime", FRAME_SUBGAME_RUNTIME_FIELD_UPDATES),
                ("BorderStackEntry", BORDER_STACK_ENTRY_FIELD_UPDATES),
                ("BorderStack", BORDER_STACK_FIELD_UPDATES),
                ("BorderRecord", BORDER_RECORD_FIELD_UPDATES),
                (
                    resolved_border_manager_struct_name(target=args.target),
                    BORDER_MANAGER_FIELD_UPDATES,
                ),
                ("GameRoot", resolved_game_root_field_updates(target=args.target)),
            ),
            proto_updates=resolved_proto_updates(target=args.target),
        )
    )
    operations.extend(
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=SYMBOL_UPDATES,
            kind="data",
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
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=(
                *ROOT_CONSTRUCTOR_USER_VAR_UPDATES,
                *WORLD_INITIALIZER_USER_VAR_UPDATES,
                *RENDER_USER_VAR_UPDATES,
            ),
        )
    )
    operations.extend(
        reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=(
                "construct_game_runtime",
                "initialize_game_assets_and_world",
                "initialize_frontend_overlay_color_lerp",
                "draw_frontend_overlay_color_lerp",
                "begin_frontend_fade_out",
                "begin_frontend_fade_in",
                "update_frontend_transition_overlay",
                "activate_landscape_entry",
                "render_game_frame",
                "attach_render_camera_source",
                "initialize_render_camera_slot",
                *BORDER_KILL_REANALYSIS_FUNCTIONS,
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
