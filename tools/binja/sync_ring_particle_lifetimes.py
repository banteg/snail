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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_subgame_pool_types.h"

EXPECTED_TYPE_WIDTHS = {
    "SubRingStar": 0x20,
    "SubRing": 0x1F8,
    "SubRingPool": 0x3F0,
}

EXPECTED_STRUCT_FIELDS = {
    "SubRingStar": {
        0x00: ("sprite", "Sprite*"),
        0x04: ("parent", "SubRing*"),
        0x08: ("base_position", "Vec3"),
        0x14: ("phase", "float"),
        0x18: ("phase_step", "float"),
        0x1C: ("radius", "float"),
    },
    "SubRing": {
        0x80: ("state", "SubRingState"),
        0x88: ("kind", "SubRingKind"),
        0x90: ("particles", "SubRingStar[10]"),
    },
    "SubRingPool": {
        0x00: ("slots", "SubRing[2]"),
    },
}

# Init carries ESI as one SubRingStar* and advances it by the exact 0x20 child
# stride. Binary Ninja otherwise promotes &ring->particles to a pointer to the
# complete ten-element array, forcing every child access through a false
# parent-relative subtraction. Keep this exact physical cursor separate from
# the broad type/prototype replay.
RING_PARTICLE_USER_VAR_UPDATES = (
    (
        "initialize_ring_or_special_effect_particles",
        "RegisterVariableSourceType",
        34,
        72,
        "particle",
        "SubRingStar*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay only the carried SubRingStar cursor in "
            "initialize_ring_or_special_effect_particles."
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
        help="Header documenting the canonical SubRing parent/child layouts.",
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
            "canonical ring particle ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_ring_particle_owner_layouts",
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
            updates=RING_PARTICLE_USER_VAR_UPDATES,
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
