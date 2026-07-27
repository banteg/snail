#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    current_enum_members,
    emit_summary,
    header_enum_members,
    reanalyze_functions,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/path_template_types.h"
ENUM_NAME = "PathTemplateKind"

LEGACY_ENUM_MEMBERS = (
    ("PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY", 0x00),
    ("PATH_TEMPLATE_KIND_LOOPTHELOOPW", 0x06),
    ("PATH_TEMPLATE_KIND_DETOUR", 0x0F),
    ("PATH_TEMPLATE_KIND_FAMILY_10", 0x10),
    ("PATH_TEMPLATE_KIND_FAMILY_11", 0x11),
    ("PATH_TEMPLATE_KIND_CAGE2", 0x14),
    ("PATH_TEMPLATE_KIND_SCREW", 0x15),
    ("PATH_TEMPLATE_KIND_SLALOM", 0x16),
    ("PATH_TEMPLATE_KIND_SLALOMBIG", 0x17),
    ("PATH_TEMPLATE_KIND_WORM", 0x18),
    ("PATH_TEMPLATE_KIND_LOOPOUT", 0x19),
    ("PATH_TEMPLATE_KIND_SWEEP", 0x1C),
    ("PATH_TEMPLATE_KIND_SNAKE", 0x1D),
    ("PATH_TEMPLATE_KIND_SUPERTRAMP", 0x1F),
    ("PATH_TEMPLATE_KIND_DIP", 0x20),
    ("PATH_TEMPLATE_KIND_START", 0x24),
    ("PATH_TEMPLATE_KIND_TURNOVER", 0x25),
    ("PATH_TEMPLATE_KIND_TURNOVERDOUBLE", 0x26),
    ("PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY", 0x27),
    ("PATH_TEMPLATE_KIND_WIBBLE", 0x28),
    ("PATH_TEMPLATE_KIND_INVERT", 0x29),
    ("PATH_TEMPLATE_KIND_NONLINEAR_42", 0x2A),
    ("PATH_TEMPLATE_KIND_TWISTER", 0x2B),
    ("PATH_TEMPLATE_KIND_TWISTER2", 0x2D),
)

EXPECTED_ENUM_MEMBERS = (
    ("PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY", 0x00),
    ("PATH_TEMPLATE_KIND_LOOPTHELOOPW", 0x06),
    ("PATH_TEMPLATE_KIND_CAGE2", 0x0F),
    ("PATH_TEMPLATE_KIND_FAMILY_10", 0x10),
    ("PATH_TEMPLATE_KIND_FAMILY_11", 0x11),
    ("PATH_TEMPLATE_KIND_DIP", 0x14),
    ("PATH_TEMPLATE_KIND_SCREW", 0x15),
    ("PATH_TEMPLATE_KIND_SLALOM", 0x16),
    ("PATH_TEMPLATE_KIND_SLALOMBIG", 0x17),
    ("PATH_TEMPLATE_KIND_WORM", 0x18),
    ("PATH_TEMPLATE_KIND_LOOPOUT", 0x19),
    ("PATH_TEMPLATE_KIND_SWEEP", 0x1C),
    ("PATH_TEMPLATE_KIND_SNAKE", 0x1D),
    ("PATH_TEMPLATE_KIND_SUPERTRAMP", 0x1F),
    ("PATH_TEMPLATE_KIND_SLALOMDOUBLE", 0x20),
    ("PATH_TEMPLATE_KIND_START", 0x24),
    ("PATH_TEMPLATE_KIND_TURNOVER", 0x25),
    ("PATH_TEMPLATE_KIND_TURNOVERDOUBLE", 0x26),
    ("PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY", 0x27),
    ("PATH_TEMPLATE_KIND_WIBBLE", 0x28),
    ("PATH_TEMPLATE_KIND_INVERT", 0x29),
    ("PATH_TEMPLATE_KIND_NONLINEAR_42", 0x2A),
    ("PATH_TEMPLATE_KIND_TWISTER", 0x2B),
    ("PATH_TEMPLATE_KIND_TWISTER2", 0x2D),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the paired-mobile-authored Cage2, Dip, and SlalomDouble "
            "PathTemplateKind labels."
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
        help="Header supplying the canonical PathTemplateKind definition.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    parsed_members = header_enum_members(
        REPO_ROOT,
        target=args.target,
        header_path=header_path,
        enum_names=(ENUM_NAME,),
    ).get(ENUM_NAME)
    if parsed_members != EXPECTED_ENUM_MEMBERS:
        raise RuntimeError(
            f"{ENUM_NAME} header members do not match the paired-mobile map: "
            f"{parsed_members!r}"
        )

    current_members = current_enum_members(
        REPO_ROOT,
        target=args.target,
        enum_names=(ENUM_NAME,),
    ).get(ENUM_NAME)
    if current_members not in (LEGACY_ENUM_MEMBERS, EXPECTED_ENUM_MEMBERS):
        raise RuntimeError(
            f"refusing to replace unexpected live {ENUM_NAME} members: "
            f"{current_members!r}"
        )

    operations: list[dict[str, object]] = []
    enum_changed = current_members != EXPECTED_ENUM_MEMBERS
    if not enum_changed:
        operations.append(
            {
                "op": "types_declare_missing_only",
                "status": "skipped",
                "reason": "paired-mobile PathTemplateKind labels already current",
                "header": str(header_path),
                "required_types": (ENUM_NAME,),
            }
        )
    else:
        operations.append(
            types_declare_missing_only(
                REPO_ROOT,
                target=args.target,
                header_path=header_path,
                replace_types=(ENUM_NAME,),
                include_types=(ENUM_NAME,),
            )
        )
        operations.extend(
            reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=(
                    "initialize_cage2_path_template_pair",
                    "initialize_dip_path_template_pair",
                    "initialize_slalomdouble_path_template_pair",
                    "update_subgoldy",
                ),
            )
        )

    readback = current_enum_members(
        REPO_ROOT,
        target=args.target,
        enum_names=(ENUM_NAME,),
    ).get(ENUM_NAME)
    if readback != EXPECTED_ENUM_MEMBERS:
        raise RuntimeError(
            f"{ENUM_NAME} readback mismatch after replay: {readback!r}"
        )
    operations.append(
        {
            "op": "verify_enum_members",
            "status": "verified",
            "type": ENUM_NAME,
            "members": readback,
        }
    )
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=header_path,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
