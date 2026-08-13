#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_type_renames,
    apply_user_var_updates,
    current_header_type_equivalence,
    current_type_widths,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_logo_types.h"

EXPECTED_TYPE_WIDTHS = {
    "Vec3": 0x0C,
    "BodNode": 0x10,
    "cRLogoLetter": 0x90,
    "LogoLetterVelocityCursor": 0x90,
    "cRLogo": 0x25218,
}

TYPE_RENAMES = (
    ("AnimManager", "cRAnimManager"),
    ("LogoLetter", "cRLogoLetter"),
    ("Logo", "cRLogo"),
)

# The two buffers are exact 128-byte stack objects. The allocated script owner
# survives from load_file_bytes through free_tracked_memory. Image and glyph
# insertion each reload the borrowed active-list head and new first node in
# separate register lifetimes. The final velocity pass uses an analysis-only
# cursor beginning at cRLogoLetter::velocity and advancing by a whole 0x90-byte
# cRLogoLetter record.
INTRO_LOGO_DIRECT_USER_VAR_UPDATES = (
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        128,
        66,
        "loaded_script_bytes",
        "char*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        261,
        72,
        "script_bytes",
        "char*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        369,
        66,
        "image_name_write",
        "char*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        560,
        68,
        "active_first_link_image",
        "BodNode*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        570,
        68,
        "active_new_first_image",
        "BodNode*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        1311,
        68,
        "active_first_link_glyph",
        "BodNode*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        1321,
        68,
        "active_new_first_glyph",
        "BodNode*",
    ),
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        1792,
        66,
        "velocity_cursor",
        "LogoLetterVelocityCursor*",
    ),
    (
        "initialize_intro_screen",
        "StackVariableSourceType",
        0,
        -256,
        "image_name",
        "char[0x80]",
    ),
    (
        "initialize_intro_screen",
        "StackVariableSourceType",
        0,
        -128,
        "texture_path",
        "char[0x80]",
    ),
)

# This element pointer is materialized by reanalysis only after the strided
# cursor above has its 0x90-byte projection, so it must be replayed separately.
INTRO_LOGO_DERIVED_USER_VAR_UPDATES = (
    (
        "initialize_intro_screen",
        "RegisterVariableSourceType",
        1802,
        68,
        "current_velocity",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay initialize_intro_screen's script, buffer, active-list, "
            "and final cRLogoLetter velocity lifetimes."
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
        help="Header documenting the canonical cRLogo owners.",
    )
    return parser.parse_args()


def ensure_owner_types(target: str, header_path: Path) -> dict[str, object]:
    widths = current_type_widths(
        REPO_ROOT,
        target=target,
        type_names=EXPECTED_TYPE_WIDTHS,
    )
    equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=target,
        header_path=header_path,
    )
    mismatched_types = tuple(
        name
        for name, expected_width in EXPECTED_TYPE_WIDTHS.items()
        if widths[name] != expected_width or not equivalence.get(name, False)
    )
    if not mismatched_types:
        return {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "intro cRLogo owner sizes already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_TYPE_WIDTHS,
            "type_equivalence": equivalence,
        }

    operation = types_declare_missing_only(
        REPO_ROOT,
        target=target,
        header_path=header_path,
        replace_types=mismatched_types,
        include_types=EXPECTED_TYPE_WIDTHS,
    )
    operation["repaired_types"] = mismatched_types
    operation["expected_sizes"] = {
        name: EXPECTED_TYPE_WIDTHS[name] for name in mismatched_types
    }
    return operation


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"cRLogo ownership header not found: {header_path}")

    operations: list[dict[str, object]] = [
        *apply_type_renames(
            REPO_ROOT,
            target=args.target,
            renames=TYPE_RENAMES,
        ),
        ensure_owner_types(args.target, header_path),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=INTRO_LOGO_DIRECT_USER_VAR_UPDATES,
        ),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=INTRO_LOGO_DERIVED_USER_VAR_UPDATES,
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
