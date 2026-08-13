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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/snail_skin_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRSnailSkin": 0x20,
}

OWNER_TYPE_RENAMES = (("SnailSkin", "cRSnailSkin"),)

FUNCTION_SYMBOL_UPDATES = (
    ("0x445f60", "initialize_snail_skin"),
    ("0x445f80", "update_snail_skin_transition"),
    ("0x445fd0", "change_snail_skin"),
)

REANALYSIS_FUNCTIONS = (
    "initialize_snail_skin",
    "update_snail_skin_transition",
    "change_snail_skin",
    "initialize_subgoldy",
    "update_snail_presentation",
    "update_damage_gauge",
    "apply_damage_gauge_delta",
    "initialize_invincible_shell",
    "update_invincible_shell",
)

SNAIL_SKIN_FIELD_UPDATES = (
    ("0x00", "selected_slot", "int32_t"),
    ("0x04", "material_overrides", "TextureRef*[0x3]"),
    ("0x10", "owner_snail", "Snail*"),
    ("0x14", "active", "int32_t"),
    ("0x18", "progress", "float"),
    ("0x1c", "progress_step", "float"),
)

PROTO_UPDATES = (
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(cRSnailSkin* snail_skin)",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(cRSnailSkin* snail_skin)",
    ),
    (
        "change_snail_skin",
        "void __thiscall change_snail_skin(cRSnailSkin* snail_skin, int32_t slot_id, float duration_seconds)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRSnailSkin ownership lane."
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
            "reason": "cRSnailSkin owner layout already current",
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
                    ("cRSnailSkin", SNAIL_SKIN_FIELD_UPDATES),
                    (
                        "Snail",
                        (("0x1938", "snail_skin", "cRSnailSkin"),),
                    ),
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
