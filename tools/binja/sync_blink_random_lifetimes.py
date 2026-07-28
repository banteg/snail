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
    "Player": 0x4364,
    "cRSubGame": 0x1272838,
}

EXPECTED_STRUCT_FIELDS = {
    "cRSubGame": {
        0x3BB700: ("blink_random_index", "int32_t"),
        0x3BB704: ("blink_random_samples", "float[24]"),
        0x3BB764: ("player", "Player"),
    },
}

# The initializer borrows one float at a time from the 24-entry cadence table.
# ESI advances by four bytes and does not own the complete array or the
# enclosing cRSubGame.
BLINK_RANDOM_SAMPLE_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_blink_random",
        "RegisterVariableSourceType",
        13,
        72,
        "blink_sample_cursor",
        "float*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Replay the borrowed blink-random sample cursor."
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
        help="Header documenting the canonical cRSubGame owner.",
    )
    return parser.parse_args()


def verify_blink_random_owner_layout(target: str) -> dict[str, object]:
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
            "canonical blink-random ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_blink_random_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_blink_random_owner_layout(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=BLINK_RANDOM_SAMPLE_CURSOR_USER_VAR_UPDATES,
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
