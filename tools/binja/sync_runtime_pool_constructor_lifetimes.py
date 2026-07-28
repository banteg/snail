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
    "SubgameRuntime": 0x1272838,
    "SubHealth": 0x74,
    "Slug": 0xEC,
    "SlugPool": 0x760,
    "Banner": 0x60,
    "BannerPool": 0xC0,
    "SubGarbage": 0xC4,
    "SubGarbagePool": 0x264C,
    "SubRing": 0x1F8,
    "SubRingPool": 0x3F0,
    "cRSubLoc": 0x54,
    "cRPath": 0xA8,
    "PathPair": 0x150,
}

EXPECTED_STRUCT_FIELDS = {
    "SubgameRuntime": {
        0x356000: ("health_pickups", "SubHealth[8]"),
        0x3563A0: ("slug_hazards", "SlugPool"),
        0x359080: ("banners", "BannerPool"),
        0x359140: ("garbage_hazards", "SubGarbagePool"),
        0x35B78C: ("ring_effects", "SubRingPool"),
        0x3BFAC8: ("runtime_cells", "cRSubLoc[3200][8]"),
        0xFF2914: ("path_pairs", "PathPair[63]"),
    },
    "SlugPool": {
        0x00: ("slots", "Slug[8]"),
    },
    "BannerPool": {
        0x00: ("slots", "Banner[2]"),
    },
    "SubGarbagePool": {
        0x00: ("active_head", "SubGarbage*"),
        0x04: ("slots", "SubGarbage[50]"),
    },
    "SubRingPool": {
        0x00: ("slots", "SubRing[2]"),
    },
    "PathPair": {
        0x00: ("primary", "cRPath"),
        0xA8: ("secondary", "cRPath"),
    },
}

# The constructor reuses EDI for seven independent walks. Each lifetime borrows
# one inline element from its enclosing SubgameRuntime pool and advances by the
# exact element width; none owns the complete array it traverses.
RUNTIME_POOL_CONSTRUCTOR_CURSOR_USER_VAR_UPDATES = (
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        334,
        73,
        "health_pickup_cursor",
        "SubHealth*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        358,
        73,
        "slug_cursor",
        "Slug*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        433,
        73,
        "banner_cursor",
        "Banner*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        463,
        73,
        "garbage_hazard_cursor",
        "SubGarbage*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        490,
        73,
        "ring_effect_cursor",
        "SubRing*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        628,
        73,
        "runtime_cell_cursor",
        "cRSubLoc*",
    ),
    (
        "initialize_runtime_pools_and_path_template_bank",
        "RegisterVariableSourceType",
        679,
        73,
        "path_template_cursor",
        "cRPath*",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Replay the inline element cursors used by the runtime-pool "
            "constructor."
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
        help="Header documenting the canonical SubgameRuntime pool owners.",
    )
    return parser.parse_args()


def verify_runtime_pool_constructor_owner_layouts(
    target: str,
) -> dict[str, object]:
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
            "canonical runtime-pool constructor ownership is not current:\n"
            + "\n".join(mismatches)
        )
    return {
        "op": "verify_runtime_pool_constructor_owner_layouts",
        "status": "verified",
        "types": tuple(EXPECTED_TYPE_WIDTHS),
    }


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations = [
        verify_runtime_pool_constructor_owner_layouts(args.target),
        *apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=RUNTIME_POOL_CONSTRUCTOR_CURSOR_USER_VAR_UPDATES,
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
