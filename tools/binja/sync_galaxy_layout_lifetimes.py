#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

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
    "tColour": 0x10,
    "GalaxyPoint": 0x08,
    "GalaxyRouteNameRecord": 0xA0,
    "cRGalaxy": 0x10FA8,
}

EXPECTED_STRUCT_FIELDS = {
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "GalaxyPoint": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
    },
    "GalaxyRouteNameRecord": {
        0x00: ("name", "char[128]"),
        0x80: ("star_count", "int32_t"),
        0x84: ("color", "tColour"),
        0x94: ("map_x", "float"),
        0x98: ("map_y", "float"),
        0x9C: ("map_z", "float"),
    },
    "cRGalaxy": {
        0x10930: ("route_names", "GalaxyRouteNameRecord[10]"),
        0x10F70: ("level_progress_base", "cRSubGame*"),
    },
}

# The first two EAX lifetimes walk the y lanes of the independently owned
# route-point and group-point banks while rescaling both x/y pairs. EBP later
# walks the group y lanes again while the loader copies authored map positions.
# The archive helper is intentionally generic (void*) across binary and text
# callers, so this use site carries the borrowed char* view. EDX is a byte
# cursor into one GalaxyRouteNameRecord::name field; it does not own or denote
# the complete ten-record route-name bank.
GALAXY_LAYOUT_USER_VAR_UPDATES = (
    (
        "load_galaxy_layout",
        "RegisterVariableSourceType",
        6,
        66,
        "route_point_y_cursor",
        "float*",
    ),
    (
        "load_galaxy_layout",
        "RegisterVariableSourceType",
        79,
        66,
        "group_point_rescale_y_cursor",
        "float*",
    ),
    (
        "load_galaxy_layout",
        "RegisterVariableSourceType",
        171,
        71,
        "current_group_point_y_cursor",
        "float*",
    ),
    (
        "load_galaxy_layout",
        "RegisterVariableSourceType",
        166,
        66,
        "file_text",
        "char*",
    ),
    (
        "load_galaxy_layout",
        "RegisterVariableSourceType",
        280,
        68,
        "route_name_character_cursor",
        "char*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay load_galaxy_layout's point-bank, text, and route-name "
            "borrowed cursors."
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
        help="Header documenting the canonical cRGalaxy point and name owners.",
    )
    return parser.parse_args()


def verify_galaxy_layout_owners(target: str) -> dict[str, object]:
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
            "canonical galaxy layout ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_galaxy_layout_owners",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"cRGalaxy ownership header not found: {header_path}")

    operations = [
        verify_galaxy_layout_owners(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=GALAXY_LAYOUT_USER_VAR_UPDATES,
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
