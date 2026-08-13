#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/anim_manager_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRAnimManager": 0x48,
}

OWNER_TYPE_RENAMES = (("AnimManager", "cRAnimManager"),)

FUNCTION_SYMBOL_UPDATES = (
    ("0x4447c0", "initialize_anim_manager"),
    ("0x4447d0", "update_anim_manager"),
)

REANALYSIS_FUNCTIONS = (
    "initialize_anim_manager",
    "update_anim_manager",
    "initialize_subgoldy",
    "update_subgoldy",
    "render_game_frame",
    "dispatch_cutscene_animation",
    "set_weapon_animation",
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

PROTO_UPDATES = (
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(cRAnimManager* manager)",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(cRAnimManager* manager)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRAnimManager ownership lane."
    )
    parser.add_argument(
        "--target", default=DEFAULT_TARGET, help="Binary Ninja target selector."
    )
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

    operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=OWNER_TYPE_RENAMES,
    )
    observed_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_STRUCT_SIZES,
    )
    type_equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=args.target,
        header_path=header_path,
    )
    mismatched_structs = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            observed_widths.get(name) != expected_size
            or not type_equivalence.get(name, False)
        )
    )
    if mismatched_structs:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_structs,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_structs
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "cRAnimManager owner layout already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": {
                name: type_equivalence.get(name, False)
                for name in EXPECTED_STRUCT_SIZES
            },
        }

    operations.extend(
        [
            type_operation,
            *apply_symbol_updates(
                REPO_ROOT,
                target=args.target,
                updates=FUNCTION_SYMBOL_UPDATES,
                kind="function",
            ),
            *apply_struct_and_proto_updates(
                REPO_ROOT,
                target=args.target,
                struct_updates=(
                    ("cRAnimManager", ANIM_MANAGER_FIELD_UPDATES),
                    (
                        "RenderableBod",
                        (("0x78", "render_animation_manager", "cRAnimManager*"),),
                    ),
                    ("Weapon", (("0x108", "anim_manager", "cRAnimManager"),)),
                    ("Snail", (("0x104", "anim_manager", "cRAnimManager"),)),
                ),
                proto_updates=PROTO_UPDATES,
            ),
            *reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=REANALYSIS_FUNCTIONS,
            ),
        ]
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
