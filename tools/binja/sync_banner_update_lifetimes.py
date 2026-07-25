#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_split_user_var_update,
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
    "TransformMatrix": 0x40,
    "BodBase": 0x38,
    "RenderableBod": 0x80,
    "Banner": 0x60,
    "Player": 0x4364,
}

EXPECTED_STRUCT_FIELDS = {
    "Vec3": {
        0x08: ("z", "float"),
    },
    "TransformMatrix": {
        0x30: ("position", "Vec3"),
    },
    "BodBase": {
        0x10: ("position", "Vec3"),
    },
    "RenderableBod": {
        0x38: ("transform", "TransformMatrix"),
    },
    "Banner": {
        0x00: ("bod", "BodBase"),
        0x38: ("visibility_mode", "int32_t"),
        0x54: ("owner_player", "Player*"),
        0x58: ("phase", "float"),
        0x5C: ("phase_step", "float"),
    },
    "Player": {
        0x00: ("body", "RenderableBod"),
    },
}

# ECX starts as the Banner receiver, but the start-row visibility branch
# replaces it with Banner::owner_player before reading Player + 0x70. Split
# that definition so the borrowed Player lifetime does not inherit Banner
# ownership and force a raw __offset read.
BANNER_OWNER_PLAYER_DEFINITIONS = (
    ("0x441d5f", "mlil", "RegisterVariableSourceType", 31, 67),
)

BANNER_OWNER_PLAYER_VAR = (
    "RegisterVariableSourceType",
    31,
    67,
)

# EAX first carries visibility_mode and later the inherited BOD list flags.
# Keep the second lifetime unsigned so the flag-byte update remains explicit.
BANNER_UPDATE_USER_VAR_UPDATES = (
    (
        "update_banner",
        "RegisterVariableSourceType",
        11,
        66,
        "list_flags",
        "uint32_t",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay update_banner's borrowed Player and inherited flag "
            "lifetimes."
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
        help="Header documenting the canonical Banner and Player owners.",
    )
    return parser.parse_args()


def verify_banner_update_owner_layout(target: str) -> dict[str, object]:
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
            "canonical Banner update ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_banner_update_owner_layout",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Banner ownership header not found: {header_path}")

    operations = [verify_banner_update_owner_layout(args.target)]
    operations.extend(
        apply_split_user_var_update(
            REPO_ROOT,
            target=args.target,
            identifier="update_banner",
            definitions=BANNER_OWNER_PLAYER_DEFINITIONS,
            target_var=BANNER_OWNER_PLAYER_VAR,
            variable_name="owner_player",
            variable_type="Player*",
        )
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=BANNER_UPDATE_USER_VAR_UPDATES,
        )
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
