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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/damage_guage_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRDamageGuage": 0x2C,
}

OWNER_TYPE_RENAMES = (("DamageGuage", "cRDamageGuage"),)

EXPECTED_ENUM_WIDTHS = {
    "DamageGuageState": 0x04,
}

FUNCTION_SYMBOL_UPDATES = (
    ("0x440fa0", "initialize_damage_gauge"),
    ("0x440fd0", "update_damage_gauge"),
    ("0x4413f0", "apply_damage_gauge_delta"),
)

REANALYSIS_FUNCTIONS = (
    "initialize_damage_gauge",
    "update_damage_gauge",
    "apply_damage_gauge_delta",
    "build_subgame_level",
    "initialize_subgoldy",
    "update_subgoldy",
    "handle_subgoldy_collisions",
    "calc_subgame_rate",
)

DAMAGE_GUAGE_FIELD_UPDATES = (
    ("0x00", "state", "DamageGuageState"),
    ("0x04", "pulse_progress", "float"),
    ("0x08", "pulse_step", "float"),
    ("0x0c", "unresolved_byte_0c", "uint8_t"),
    ("0x0d", "_pad_0d", "uint8_t[0x3]"),
    ("0x10", "warning_transition_progress", "float"),
    ("0x14", "warning_transition_step", "float"),
    ("0x18", "skin_hold_ticks", "int32_t"),
    ("0x1c", "fill", "float"),
    ("0x20", "display_fill", "float"),
    ("0x24", "hit_flash_progress", "float"),
    ("0x28", "hit_flash_step", "float"),
)

PROTO_UPDATES = (
    (
        "initialize_damage_gauge",
        "void __thiscall initialize_damage_gauge(cRDamageGuage* damage_guage)",
    ),
    (
        "update_damage_gauge",
        "void __thiscall update_damage_gauge(cRDamageGuage* damage_guage)",
    ),
    (
        "apply_damage_gauge_delta",
        "void __thiscall apply_damage_gauge_delta(cRDamageGuage* damage_guage, float delta, bool force)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact Windows cRDamageGuage ownership lane."
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
    enum_widths = current_type_widths(
        REPO_ROOT,
        target=args.target,
        type_names=EXPECTED_ENUM_WIDTHS,
    )
    mismatched_enums = tuple(
        name
        for name, expected_width in EXPECTED_ENUM_WIDTHS.items()
        if enum_widths.get(name) != expected_width
    )
    if mismatched_structs or mismatched_enums:
        repaired_types = (*mismatched_structs, *mismatched_enums)
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=repaired_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = repaired_types
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": (
                "cRDamageGuage owner layout and DamageGuageState width "
                "already current"
            ),
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "expected_enum_widths": EXPECTED_ENUM_WIDTHS,
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
                    ("cRDamageGuage", DAMAGE_GUAGE_FIELD_UPDATES),
                    (
                        "Player",
                        (("0x3c4", "damage_gauge", "cRDamageGuage"),),
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
