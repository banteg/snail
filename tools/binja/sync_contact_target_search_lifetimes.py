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
    "ContactTargetEntry": 0x18,
    "EnemyManager": 0x1804,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "ContactTargetEntry": {
        0x00: ("kind", "int32_t"),
        0x04: ("position", "Vec3"),
        0x10: ("radius", "float"),
        0x14: ("object", "ContactTargetObject*"),
    },
    "EnemyManager": {
        0x00: ("count", "int32_t"),
        0x04: ("entries", "ContactTargetEntry[256]"),
    },
}

# The search borrows a float cursor based at each entry's position.z so VC6 can
# address x/y/z as [-2]/[-1]/[0]. The selected result is one entry borrow from
# EnemyManager's fixed registry, not a pointer to the complete 256-entry bank.
CONTACT_TARGET_SEARCH_USER_VAR_UPDATES = (
    (
        "search_path_for_golb",
        "RegisterVariableSourceType",
        39,
        72,
        "position_z_cursor",
        "float*",
    ),
    (
        "search_path_for_golb",
        "StackVariableSourceType",
        11,
        -28,
        "nearest_entry",
        "ContactTargetEntry*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the borrowed contact-target z cursor and selected entry."
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
        help="Header documenting the canonical EnemyManager registry.",
    )
    return parser.parse_args()


def verify_contact_target_search_owner_layout(target: str) -> dict[str, object]:
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
            "canonical contact-target search ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_contact_target_search_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_contact_target_search_owner_layout(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=CONTACT_TARGET_SEARCH_USER_VAR_UPDATES,
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
