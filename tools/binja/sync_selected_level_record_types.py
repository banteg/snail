#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_selected_level_record_types.h"
SPILL_PATH_RE = re.compile(r"^path:\s+(?P<path>.+)$", re.MULTILINE)

PLAYER_FIELD_UPDATES = (
    ("0x38", "live_matrix", "TransformMatrix"),
    ("0x120", "movement_state", "int32_t"),
    ("0x2d8", "control_override_active", "uint8_t"),
    ("0x370", "heading_roll", "float"),
    ("0x384", "follow_state", "FollowState"),
    ("0x408", "game", "Game*"),
    ("0x41d", "attachment_exit_pending", "uint8_t"),
    ("0x42c", "post_follow_value_a", "float"),
    ("0x43c", "control_source", "PlayerControlSource*"),
    ("0x2734", "movement_rate_scalar", "float"),
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
    ("0xff25dc", "runtime_track_index", "int32_t"),
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


def run_bn(*args: str) -> object:
    completed = subprocess.run(
        ["bn", *args],
        cwd=REPO_ROOT,
        check=False,
        text=True,
        capture_output=True,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"bn {' '.join(args)} failed with exit code {completed.returncode}:\n{completed.stderr.strip()}"
        )
    stdout = completed.stdout.strip()
    stderr = completed.stderr.strip()
    spill_match = SPILL_PATH_RE.search(stdout) or SPILL_PATH_RE.search(stderr)
    if spill_match is not None:
        spill_path = Path(spill_match.group("path")).expanduser()
        return json.loads(spill_path.read_text(encoding="utf-8"))
    if not stdout:
        if not stderr:
            return {}
        return {"stderr": stderr}
    if stdout[0] in "[{":
        return json.loads(stdout)
    result: dict[str, object] = {"stdout": stdout}
    if stderr:
        result["stderr"] = stderr
    return result


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(
        {
            "op": "types_declare",
            "result": run_bn("types", "declare", "--target", args.target, "--file", str(header_path)),
        }
    )

    for offset, name, field_type in PLAYER_FIELD_UPDATES:
        operations.append(
            {
                "op": "struct_field_set",
                "struct_name": "Player",
                "offset": offset,
                "field_name": name,
                "field_type": field_type,
                "result": run_bn(
                    "struct",
                    "field",
                    "set",
                    "Player",
                    offset,
                    name,
                    field_type,
                    "--target",
                    args.target,
                ),
            }
        )

    for offset, name, field_type in GAME_FIELD_UPDATES:
        operations.append(
            {
                "op": "struct_field_set",
                "struct_name": "Game",
                "offset": offset,
                "field_name": name,
                "field_type": field_type,
                "result": run_bn(
                    "struct",
                    "field",
                    "set",
                    "Game",
                    offset,
                    name,
                    field_type,
                    "--target",
                    args.target,
                ),
            }
        )

    for offset, name, field_type in SNAIL_VISUAL_FIELD_UPDATES:
        operations.append(
            {
                "op": "struct_field_set",
                "struct_name": "SnailVisual",
                "offset": offset,
                "field_name": name,
                "field_type": field_type,
                "result": run_bn(
                    "struct",
                    "field",
                    "set",
                    "SnailVisual",
                    offset,
                    name,
                    field_type,
                    "--target",
                    args.target,
                ),
            }
        )

    json.dump(
        {
            "tool": "binary_ninja",
            "target": args.target,
            "header": str(header_path.relative_to(REPO_ROOT)),
            "operations": operations,
        },
        sys.stdout,
        indent=2,
        sort_keys=True,
    )
    sys.stdout.write("\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
