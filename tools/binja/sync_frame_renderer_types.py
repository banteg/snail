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
    "FrameRenderCamera",
    "FrameRenderCameraSlot",
    "FrameContactTargetRegistry",
    "FrameSubgameRuntime",
    "TextureSetSelector",
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

GAME_ROOT_FIELD_UPDATES = (
    ("0x24", "fade", "FrontendFade"),
    ("0x38", "frontend_quit_requested", "int32_t"),
    ("0x3c", "fixed_update_count", "int32_t"),
    ("0x40", "player_count", "int32_t"),
    ("0x44", "game_inputs", "GameInput[2]"),
    ("0x124", "players", "GamePlayer[2]"),
    ("0x518", "fixed_update_accumulator", "float"),
    ("0x51c", "frame_counter", "int32_t"),
    ("0x520", "input_sampling_gate", "uint8_t"),
    ("0x56c", "render_skip_count", "int32_t"),
    ("0x570", "inactive_bod_sentinel", "FrameBodBase"),
    ("0x5a8", "active_bod_list", "FrameBodList"),
    ("0x5b4", "render_camera_slots", "FrameRenderCameraSlot[5]"),
    ("0xb24", "texture_set_selector", "TextureSetSelector"),
    ("0x74618", "subgame", "FrameSubgameRuntime"),
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
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
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
