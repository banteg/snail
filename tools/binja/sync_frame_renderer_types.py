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
    current_struct_size,
    emit_summary,
    types_declare_if_missing,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_frame_renderer_types.h"
REQUIRED_STRUCTS = (
    "SpriteDepthNode",
    "FrontendFade",
    "InputState",
    "GameInputBodBase",
    "GameInput",
    "MouseCursorState",
    "FrontendOverlayColorLerp",
    "GamePlayer",
    "FrameBodNode",
    "FrameBodList",
    "FrameBodBase",
    "FrameRenderableBod",
    "FrameRenderCamera",
    "FrameOverlay",
    "FrameRenderCameraSlot",
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
    ("0x4e5510", "g_sprite_depth_nodes"),
    ("0x4f7050", "g_sprite_depth_buckets"),
)

FUNCTION_SYMBOL_UPDATES = (
    ("0x408000", "initialize_game_player"),
    ("0x4107d0", "update_frontend_state_machine"),
    ("0x44c3b0", "is_mouse_captured"),
    ("0x44c3c0", "capture_mouse_cursor"),
    ("0x44c400", "release_mouse_cursor"),
)

DATA_VAR_UPDATES = (
    ("0x4df904", "GameRoot*"),
    ("0x4e5510", "SpriteDepthNode[3000]"),
    ("0x4f7050", "SpriteDepthNode*[256]"),
)

PROTO_UPDATES = (
    (
        "initialize_game_player",
        "GamePlayer* __thiscall initialize_game_player(GamePlayer* player)",
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
        "run_frame_update",
        "int32_t __thiscall run_frame_update(GameRoot* game)",
    ),
    (
        "render_game_frame",
        "void __thiscall render_game_frame(GameRoot* game)",
    ),
    (
        "select_level_track_texture_set",
        "void __thiscall select_level_track_texture_set(Track* track, int32_t texture_set)",
    ),
)

MOUSE_CURSOR_FIELD_UPDATES = (
    ("0x00", "captured", "uint8_t"),
    ("0x04", "live_x", "float"),
    ("0x08", "live_y", "float"),
    ("0x0c", "saved_x", "float"),
    ("0x10", "saved_y", "float"),
    ("0x14", "suppress_next_draw", "uint8_t"),
)

FRONTEND_OVERLAY_FIELD_UPDATES = (
    ("0x00", "state", "int32_t"),
    ("0x04", "target", "FrameColor4f"),
    ("0x14", "current", "FrameColor4f"),
)

GAME_PLAYER_FIELD_UPDATES = (
    ("0x00", "vtable", "void*"),
    ("0x38", "transform", "FrameTransformMatrix"),
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
    ("0x28", "color", "FrameColor4f"),
    ("0x6c", "color_06c", "FrameColor4f"),
    ("0x19c", "created_time", "int32_t"),
    ("0x1a0", "flags", "int32_t"),
    ("0x1ac", "color_1ac", "FrameColor4f"),
    ("0x1bc", "color_1bc", "FrameColor4f"),
    ("0x1cc", "color_1cc", "FrameColor4f"),
    ("0x1dc", "color_1dc", "FrameColor4f"),
    ("0x1ec", "color_1ec", "FrameColor4f"),
    ("0x1fc", "color_1fc", "FrameColor4f"),
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
    ("0x28", "color", "FrameColor4f"),
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
    ("0x14", "fog_color", "FrameColor4f"),
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
    ("0x5a8", "active_bod_list", "FrameBodList"),
    ("0x5b4", "render_camera_slots", "FrameRenderCameraSlot[5]"),
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
            "char __thiscall queue_frontend_widget_flag_after_delay("
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
            header_path=header_path,
            required_structs=REQUIRED_STRUCTS,
        )
    ]
    operations.extend(
        apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("GameInput", GAME_INPUT_FIELD_UPDATES),
                ("MouseCursorState", MOUSE_CURSOR_FIELD_UPDATES),
                ("FrontendOverlayColorLerp", FRONTEND_OVERLAY_FIELD_UPDATES),
                ("GamePlayer", GAME_PLAYER_FIELD_UPDATES),
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
        apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=FUNCTION_SYMBOL_UPDATES,
            kind="function",
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
