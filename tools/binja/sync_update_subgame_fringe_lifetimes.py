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
    "BodNode": 0x10,
    "BodBase": 0x38,
    "Fringe": 0x38,
    "tColour": 0x10,
    "TrackRowCell": 0x54,
    "SubgameRuntime": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "BodNode": {
        0x04: ("list_flags", "uint32_t"),
        0x08: ("list_prev", "BodNode*"),
        0x0C: ("list_next", "BodNode*"),
    },
    "BodBase": {
        0x00: ("bod", "BodNode"),
        0x28: ("color", "tColour"),
    },
    "Fringe": {
        0x00: ("bod", "BodBase"),
    },
    "tColour": {
        0x00: ("r", "float"),
        0x04: ("g", "float"),
        0x08: ("b", "float"),
        0x0C: ("a", "float"),
    },
    "TrackRowCell": {
        0x44: ("fringe_front", "Fringe*"),
        0x48: ("fringe_right", "Fringe*"),
        0x4C: ("fringe_left", "Fringe*"),
        0x50: ("fringe_back", "Fringe*"),
    },
    "SubgameRuntime": {
        0x355B64: ("fringe_attachment_list_head", "BodBase"),
        0x3BFAC8: ("runtime_cells", "TrackRowCell[3200][8]"),
    },
}

# update_subgame scans the four directional Fringe pointers embedded in each
# TrackRowCell. The cell owns the pointer slots, while FringeManager retains the
# backing objects. Each non-null object is borrowed into the runtime attachment
# list and then reloaded after get_track_skirt_color before its BodBase colour is
# copied. Keep that explicit reload: the matching scratch proves it is part of
# the native register/frame shape rather than an analyzer-only intermediate.
UPDATE_SUBGAME_FRINGE_USER_VAR_UPDATES = (
    (
        "update_subgame",
        "StackVariableSourceType",
        1730,
        -56,
        "fringe_slots_remaining",
        "uint32_t",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1738,
        69,
        "fringe_slot_cursor",
        "Fringe**",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1738,
        66,
        "current_fringe",
        "Fringe*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1785,
        67,
        "fringe_list_next",
        "BodNode*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1795,
        67,
        "fringe_list_flags",
        "uint32_t",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1821,
        66,
        "skirt_color",
        "tColour*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1826,
        68,
        "reloaded_fringe",
        "Fringe*",
    ),
    (
        "update_subgame",
        "RegisterVariableSourceType",
        1830,
        68,
        "fringe_color",
        "tColour*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the directional Fringe slot, attachment-list, and "
            "colour-copy lifetimes in update_subgame."
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
        help="Header documenting the canonical runtime-cell and Fringe owners.",
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
            "canonical update-subgame Fringe ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_update_subgame_fringe_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=UPDATE_SUBGAME_FRINGE_USER_VAR_UPDATES,
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
