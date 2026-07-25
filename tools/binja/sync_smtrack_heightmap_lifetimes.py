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
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/font_system_types.h"

EXPECTED_TYPE_WIDTHS = {
    "TgaImageView": 0x14,
    "TextureRef": 0xA4,
    "Vec3": 0x0C,
    "Object": 0xDC,
}

EXPECTED_STRUCT_FIELDS = {
    "TgaImageView": {
        0x0C: ("width", "uint16_t"),
        0x0E: ("height", "uint16_t"),
        0x10: ("bits_per_pixel", "uint8_t"),
        0x12: ("pixels", "uint8_t[1]"),
    },
    "TextureRef": {
        0x98: ("texture_ref", "void*"),
    },
    "Vec3": {
        0x00: ("x", "float"),
        0x04: ("y", "float"),
        0x08: ("z", "float"),
    },
    "Object": {
        0x1C: ("heightmap_sample_count", "int32_t"),
        0x24: ("heightmap_sample_divisor", "float"),
        0x28: ("heightmap_sample_scale", "float"),
        0x38: ("vertices", "Vec3*"),
    },
}

# ESI is a borrowed TGA view over TextureRef::texture_ref, not a generic
# retained allocation. EBP walks the Object-owned Vec3 bank one sample at a
# time; naming that physical cursor does not transfer ownership away from the
# Object.
SMTRACK_HEIGHTMAP_USER_VAR_UPDATES = (
    (
        "sample_smtrack_heightmap",
        "RegisterVariableSourceType",
        14,
        72,
        "image",
        "TgaImageView*",
    ),
    (
        "sample_smtrack_heightmap",
        "RegisterVariableSourceType",
        84,
        71,
        "sample_cursor",
        "Vec3*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay sample_smtrack_heightmap's borrowed TGA view and Vec3 "
            "sample cursor."
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
        help="Header documenting the canonical TgaImageView layout.",
    )
    return parser.parse_args()


def verify_smtrack_heightmap_owner_layouts(target: str) -> dict[str, object]:
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
            "canonical SMTrack heightmap ownership layout is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_smtrack_heightmap_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"TGA ownership header not found: {header_path}")

    operations = [
        verify_smtrack_heightmap_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=SMTRACK_HEIGHTMAP_USER_VAR_UPDATES,
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
