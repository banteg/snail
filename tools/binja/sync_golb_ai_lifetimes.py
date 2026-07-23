#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_user_var_updates,
    current_struct_fields_batch,
    current_type_widths,
    emit_summary,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "Sprite": 0xB4,
    "Slug": 0xEC,
    "SlugSlotCursor": 0x35648C,
    "SubGarbage": 0xC4,
    "GolbShot": 0x2E8,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "Sprite": {
        0x48: ("position", "Vec3"),
    },
    "Slug": {
        0x00: ("body", "RenderableBod"),
        0x80: ("state", "SubSlugState"),
    },
    "SlugSlotCursor": {
        0x3563A0: ("slug", "Slug"),
    },
    "SubGarbage": {
        0x00: ("body", "RenderableBod"),
        0x80: ("next_active", "SubGarbage*"),
        0x84: ("state", "SubGarbageState"),
        0x88: ("collision_side", "SubGarbageCollisionSide"),
        0x9C: ("radius", "float"),
    },
    "GolbShot": {
        0x248: ("render_body_owner", "void*"),
        0x27C: ("source_matrix", "TransformMatrix"),
        0x2BC: ("path_follow", "GolbPathFollowState"),
    },
    "SubgameRuntime": {
        0x3563A0: ("slug_hazards", "SlugPool"),
        0x359140: ("garbage_hazards", "SubGarbagePool"),
    },
}

# update_golb_ai borrows three distinct owner families. Kind zero's variant
# render owner is proved to be a Sprite by create_golb and kill_golb. The slug
# scan retains its byte offset and parallel slot index for the native VC6
# schedule, but the offset-rooted pointer is the shared manager-relative
# SlugSlotCursor. The direct and kind-two splash garbage passes walk separate
# lifetimes over one SubGarbagePool active chain. The final wall impact occupies
# one complete Vec3 stack object.
#
# The tempting source-cell cast at register lifetimes 765/770 is intentionally
# omitted. That register also reads `(cell - 8)->tile_id`; forcing a
# TrackRowCell* makes Binary Ninja emit a negative __offset instead of exposing
# the preceding-row relationship.
GOLB_AI_USER_VAR_UPDATES = (
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1119,
        67,
        "render_sprite",
        "Sprite*",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1133,
        67,
        "render_position",
        "Vec3*",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1627,
        72,
        "active_garbage",
        "SubGarbage*",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1862,
        69,
        "slug_pool_byte_offset",
        "int32_t",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1864,
        72,
        "slug_slot_index",
        "int32_t",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1870,
        66,
        "slug_slot_cursor",
        "SlugSlotCursor*",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        1872,
        67,
        "slug_state",
        "SubSlugState",
    ),
    (
        "update_golb_ai",
        "RegisterVariableSourceType",
        2205,
        72,
        "splash_garbage",
        "SubGarbage*",
    ),
    (
        "update_golb_ai",
        "StackVariableSourceType",
        0,
        -12,
        "wall_impact",
        "Vec3",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the proved render, slug, garbage, and wall-impact "
            "lifetimes in update_golb_ai."
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
        help="Header documenting the canonical Golb and subgame owners.",
    )
    return parser.parse_args()


def verify_owner_layouts(target: str) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    layouts = current_struct_fields_batch(
        REPO_ROOT,
        target=target,
        struct_names=EXPECTED_STRUCT_FIELDS,
    )
    mismatches: list[str] = []
    for type_name, expected_width in EXPECTED_TYPE_WIDTHS.items():
        observed_width = widths[type_name]
        if observed_width != expected_width:
            mismatches.append(
                f"{type_name}: expected width {expected_width:#x}, "
                f"observed {observed_width!r}"
            )
    for struct_name, expected_fields in EXPECTED_STRUCT_FIELDS.items():
        observed_fields = layouts[struct_name]
        for offset, expected in expected_fields.items():
            observed = observed_fields.get(offset)
            if observed != expected:
                mismatches.append(
                    f"{struct_name}+{offset:#x}: expected {expected!r}, "
                    f"observed {observed!r}"
                )
    if mismatches:
        raise RuntimeError(
            "canonical Golb AI ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_golb_ai_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Golb ownership header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=GOLB_AI_USER_VAR_UPDATES,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
