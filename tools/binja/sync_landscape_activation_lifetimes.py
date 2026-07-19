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
    remove_user_var_updates,
    types_declare_if_missing,
)
from _target import DEFAULT_TARGET


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"

EXPECTED_TYPE_WIDTHS = {
    "ActiveLandscapeEntry": 0x90,
    "LandscapeScriptRecord": 0x124,
    "LandscapeManager": 0x97A4,
    "LandscapeScriptStrideAnchor": 0x6C8,
}

EXPECTED_STRUCT_FIELDS = {
    "ActiveLandscapeEntry": {
        0x00: ("bod", "RenderableBod"),
        0x80: ("state", "int32_t"),
        0x88: ("repeat_z_span", "float"),
        0x8C: ("reference_bod", "RenderableBod*"),
    },
    "LandscapeScriptRecord": {
        0x00: ("id", "int32_t"),
        0x84: ("backdrop_texture_id", "int32_t"),
        0x88: ("split_backdrop_texture_pair", "uint8_t"),
        0x10C: ("object_index", "int32_t"),
        0x110: ("fog_color", "tColour"),
        0x120: ("distort", "float"),
    },
    "LandscapeManager": {
        0x000: ("active_entries", "ActiveLandscapeEntry[10]"),
        0x5A0: ("script_count", "int32_t"),
        0x5A4: ("scripts", "LandscapeScriptRecord[128]"),
    },
    "LandscapeScriptStrideAnchor": {
        0x000: ("manager_prefix", "uint8_t[1444]"),
        0x5A4: ("script", "LandscapeScriptRecord"),
    },
}

# activate_landscape_entry computes EDI as
# LandscapeManager + script_index * sizeof(LandscapeScriptRecord), rather than
# rebasing it to scripts[script_index]. This exact overlapping anchor exposes
# the selected record while preserving the register's physical address. The
# ESI loop cursor begins at ActiveLandscapeEntry::bod.list_flags (+4). A user
# variable there suppresses Binary Ninja's correct containing-owner recovery,
# so the replay explicitly removes the rejected experiment and leaves that
# interior borrow automatic.
LANDSCAPE_ACTIVATION_USER_VAR_UPDATES = (
    (
        "activate_landscape_entry",
        "RegisterVariableSourceType",
        111,
        73,
        "selected_script_anchor",
        "LandscapeScriptStrideAnchor*",
    ),
)

REJECTED_ACTIVE_ENTRY_CURSOR_REMOVALS = (
    (
        "activate_landscape_entry",
        "RegisterVariableSourceType",
        114,
        72,
        "active_entry_list_flags_cursor",
        "uint32_t*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the selected script stride anchor while preserving the "
            "automatic active-entry interior borrow in landscape activation."
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
        help="Header documenting the canonical landscape ownership layouts.",
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
            "canonical landscape activation ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_landscape_activation_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"landscape type header not found: {header_path}")

    operations = [
        types_declare_if_missing(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            required_structs=("LandscapeScriptStrideAnchor",),
        ),
        verify_owner_layouts(args.target),
        *remove_user_var_updates(
            REPO_ROOT,
            target=args.target,
            removals=REJECTED_ACTIVE_ENTRY_CURSOR_REMOVALS,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=LANDSCAPE_ACTIVATION_USER_VAR_UPDATES,
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
