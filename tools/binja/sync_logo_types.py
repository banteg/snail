#!/usr/bin/env python3

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from _narrow_sync import (
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    apply_type_renames,
    current_header_type_equivalence,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_logo_types.h"

EXPECTED_STRUCT_SIZES = {
    "cRLogoLetter": 0x90,
    "cRLogo": 0x25218,
}

TYPE_RENAMES = (
    ("AnimManager", "cRAnimManager"),
    ("LogoLetter", "cRLogoLetter"),
    ("Logo", "cRLogo"),
)

LOGO_LETTER_FIELD_UPDATES = (
    ("0x00", "renderable", "RenderableBod"),
    ("0x80", "velocity", "Vec3"),
    ("0x8c", "glyph", "uint8_t"),
    ("0x8d", "_pad_8d", "uint8_t[3]"),
)

LOGO_FIELD_UPDATES = (
    ("0x00", "progress", "float"),
    ("0x04", "progress_step", "float"),
    ("0x08", "state", "int32_t"),
    ("0x0c", "saved_render_flags", "int32_t"),
    ("0x10", "duration_seconds", "float"),
    ("0x14", "renderable_count", "int32_t"),
    ("0x18", "letters", "cRLogoLetter[1024]"),
    ("0x24018", "image_donors", "cRLogoLetter[32]"),
)

GAME_ROOT_FIELD_UPDATES = (
    ("0x4f400", "logo", "cRLogo"),
)

DATA_SYMBOL_UPDATES = (
    ("0x497310", "g_logo_letter_vtable"),
)

PROTO_UPDATES = (
    (
        "initialize_intro_logo_renderable",
        "cRLogoLetter* __thiscall initialize_intro_logo_renderable(cRLogoLetter* letter)",
    ),
    ("open_logo", "void __thiscall open_logo(cRLogo* logo)"),
    (
        "initialize_intro_screen",
        "void __thiscall initialize_intro_screen(cRLogo* logo, char* file_name)",
    ),
    ("destroy_intro_screen", "void __thiscall destroy_intro_screen(cRLogo* logo)"),
    ("update_intro_screen", "void __thiscall update_intro_screen(cRLogo* logo)"),
    (
        "update_intro_logo_renderable",
        "void __thiscall update_intro_logo_renderable(cRLogoLetter* letter)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRLogo ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    type_rename_operations = apply_type_renames(
        REPO_ROOT,
        target=args.target,
        renames=TYPE_RENAMES,
    )
    type_equivalence = current_header_type_equivalence(
        REPO_ROOT,
        target=args.target,
        header_path=header_path,
    )
    mismatched_types = tuple(
        name
        for name, expected_size in EXPECTED_STRUCT_SIZES.items()
        if (
            current_struct_size(REPO_ROOT, target=args.target, struct_name=name)
            != expected_size
            or not type_equivalence.get(name, False)
        )
    )
    if mismatched_types:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=mismatched_types,
            include_types=EXPECTED_STRUCT_SIZES,
        )
        type_operation["repaired_types"] = mismatched_types
        type_operation["expected_sizes"] = {
            name: EXPECTED_STRUCT_SIZES[name] for name in mismatched_types
        }
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "logo owner layouts already current",
            "header": str(header_path),
            "expected_sizes": EXPECTED_STRUCT_SIZES,
            "type_equivalence": type_equivalence,
        }

    operations: list[dict[str, object]] = [
        *type_rename_operations,
        type_operation,
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(
                ("cRLogoLetter", LOGO_LETTER_FIELD_UPDATES),
                ("cRLogo", LOGO_FIELD_UPDATES),
                ("GameRoot", GAME_ROOT_FIELD_UPDATES),
            ),
            proto_updates=PROTO_UPDATES,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
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
