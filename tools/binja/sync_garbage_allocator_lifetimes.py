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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_garbage_hazard_types.h"

EXPECTED_TYPE_WIDTHS = {
    "SubGarbage": 0xC4,
    "SubGarbagePool": 0x264C,
    "SubGarbageSlotCursor": 0x359208,
}

EXPECTED_STRUCT_FIELDS = {
    "SubGarbage": {
        0x80: ("next_active", "SubGarbage*"),
        0x84: ("state", "SubGarbageState"),
        0x9C: ("radius", "float"),
        0xB4: ("sprite", "Sprite*"),
        0xB8: ("source_cell", "TrackRowCell*"),
        0xC0: ("owner_player", "Player*"),
    },
    "SubGarbagePool": {
        0x00: ("active_head", "SubGarbage*"),
        0x04: ("slots", "SubGarbage[50]"),
    },
    "SubGarbageSlotCursor": {
        0x359144: ("garbage", "SubGarbage"),
    },
}

# AddGarbage retains ESI at SubgameRuntime + slot_index * sizeof(SubGarbage)
# instead of rebasing it to the selected actor. This analysis-only root-biased
# cursor makes every large displacement resolve through the one pool-owned slot
# without pretending the physical register holds a direct SubGarbage pointer.
GARBAGE_ALLOCATOR_USER_VAR_UPDATES = (
    (
        "spawn_track_garbage_hazard",
        "RegisterVariableSourceType",
        68,
        72,
        "garbage_slot_cursor",
        "SubGarbageSlotCursor*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the selected garbage-slot register lifetime in "
            "spawn_track_garbage_hazard."
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
        help="Header documenting the canonical garbage slot ownership layouts.",
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
            "canonical garbage-slot ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_garbage_allocator_owner_layouts",
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
            updates=GARBAGE_ALLOCATOR_USER_VAR_UPDATES,
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
