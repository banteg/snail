#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_player_presentation_types.h"
SPILL_PATH_RE = re.compile(r"^path:\s+(?P<path>.+)$", re.MULTILINE)

PLAYER_FIELD_UPDATES = (
    ("0x38", "live_matrix", "TransformMatrix"),
    ("0x120", "movement_state", "int32_t"),
    ("0x14c", "row_event_cutscene_started", "uint8_t"),
    ("0x2d8", "control_override_active", "uint8_t"),
    ("0x2dc", "cutscene_pitch_cycle", "float"),
    ("0x2e0", "cutscene_pitch_cycle_step", "float"),
    ("0x308", "movement_flag_selector", "int32_t"),
    ("0x338", "movement_flags", "uint32_t"),
    ("0x33c", "previous_movement_flags", "uint32_t"),
    ("0x350", "lane_lean_state", "int32_t"),
    ("0x354", "lane_lean_amplitude", "float"),
    ("0x358", "lane_lean_progress", "float"),
    ("0x35c", "lane_lean_progress_step", "float"),
    ("0x370", "heading_roll", "float"),
    ("0x384", "follow_state", "FollowState"),
    ("0x408", "game", "Game*"),
    ("0x41d", "attachment_exit_pending", "uint8_t"),
    ("0x42c", "post_follow_value_a", "float"),
    ("0x43c", "control_source", "PlayerControlSource*"),
    ("0x2730", "movement_progress", "float"),
    ("0x2734", "movement_rate_scalar", "float"),
    ("0x273c", "track_z_offset", "float"),
    ("0x2740", "track_z_anchor", "float"),
    ("0x2964", "cached_camera_target_world", "Vec3"),
    ("0x2970", "steering_mode_selector", "int32_t"),
    ("0x2980", "interaction_max_z", "float"),
    ("0x2984", "presentation", "PlayerPresentationController"),
    ("0x4344", "squidge", "SquidgeState"),
)

GAME_FIELD_UPDATES = (
    ("0x38", "track_center_x", "float"),
    ("0x50", "first_block_row_count", "int32_t"),
)

SNAIL_VISUAL_FIELD_UPDATES = (
    ("0x80", "follow_lateral_response", "float"),
    ("0x84", "squidge_primary", "float"),
    ("0x88", "squidge_secondary", "float"),
)

PATH_TEMPLATE_FIELD_UPDATES = (
    ("0x38", "kind", "PathTemplateKind"),
    ("0x44", "segment_count", "uint32_t"),
    ("0x4c", "segment_count_f", "float"),
    ("0x58", "primary_samples", "PathTemplateSample*"),
)

PROTO_UPDATES = (
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
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(PlayerPresentationController* presentation, int32_t animation_id, uint8_t immediate, int32_t initial_frame)",
    ),
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

    for offset, name, field_type in PATH_TEMPLATE_FIELD_UPDATES:
        operations.append(
            {
                "op": "struct_field_set",
                "struct_name": "PathTemplate",
                "offset": offset,
                "field_name": name,
                "field_type": field_type,
                "result": run_bn(
                    "struct",
                    "field",
                    "set",
                    "PathTemplate",
                    offset,
                    name,
                    field_type,
                    "--target",
                    args.target,
                ),
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

    for identifier, prototype in PROTO_UPDATES:
        operations.append(
            {
                "op": "proto_set",
                "identifier": identifier,
                "prototype": prototype,
                "result": run_bn(
                    "proto",
                    "set",
                    identifier,
                    prototype,
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
