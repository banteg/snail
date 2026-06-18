#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_struct_field_updates, emit_summary, types_declare_if_missing


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_selected_level_record_types.h"
REQUIRED_HEADER_STRUCTS = (
    "SelectedLevelRecord",
    "SelectedLevelReplaySample",
    "TransformMatrix",
    "Vec4",
)

PLAYER_FIELD_UPDATES = (
    ("0x38", "live_matrix", "TransformMatrix"),
    ("0x120", "movement_state", "int32_t"),
    ("0x2d8", "control_override_active", "uint8_t"),
    ("0x370", "heading_roll", "float"),
    ("0x384", "follow_state", "FollowState"),
    ("0x408", "game", "Game*"),
    ("0x41d", "attachment_exit_pending", "uint8_t"),
    ("0x42c", "post_follow_exit_roll", "float"),
    ("0x43c", "control_source", "PlayerControlSource*"),
    ("0x2730", "movement_fire_progress", "float"),
    ("0x2734", "movement_fire_progress_step", "float"),
    ("0x273c", "track_z_offset", "float"),
    ("0x2740", "track_z_anchor", "float"),
    ("0x2970", "steering_mode_selector", "int32_t"),
)

GAME_FIELD_UPDATES = (
    ("0xa854", "track_state_latch", "uint8_t"),
    ("0xff25d0", "selected_level_record_active", "uint8_t"),
    ("0xff25d1", "selected_level_record_persistent", "uint8_t"),
    ("0xff25d4", "selected_level_record", "SelectedLevelRecord*"),
    ("0xff25d8", "selected_level_record_saved_return_owner", "int32_t"),
    ("0xff25dc", "replay_update_cursor", "int32_t"),
    ("0xff25e4", "runtime_track_index", "int32_t"),
)

SNAIL_VISUAL_FIELD_UPDATES = (
    ("0x80", "follow_lateral_response", "float"),
    ("0x84", "squidge_primary", "float"),
    ("0x88", "squidge_secondary", "float"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow selected replay/high-score record slice to the active Binary Ninja target."
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
            struct_name="Player",
            updates=PLAYER_FIELD_UPDATES,
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
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
