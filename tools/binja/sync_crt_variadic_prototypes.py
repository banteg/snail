#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    emit_summary,
    reanalyze_functions,
    types_declare,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_crt_variadic_prototypes.h"

PROTO_UPDATES = (
    (
        "sprintf",
        "int32_t __cdecl sprintf(char* buffer, const char* format, ...)",
    ),
)

# Complete native xref set for sprintf at 0x48b32c. Reanalyzing every caller is
# intentional: Binary Ninja does not reliably invalidate already-materialized
# caller HLIL when a fixed prototype becomes variadic.
SPRINTF_CALLERS = (
    "update_frontend_widget_interaction",
    "load_x_mesh",
    "load_x_animation_clip",
    "load_galaxy_layout",
    "load_landscape_script_by_name",
    "open_logo",
    "initialize_intro_screen",
    "build_subgame_level",
    "load_frontend_level_by_mode_and_index",
    "handle_subgoldy_collisions",
    "load_level_definition_file",
    "load_segment_definitions",
    "format_time_trial_string",
    "load_object_definition",
    "sub_46120b",
    "sub_47d91e",
    "sub_47f8dc",
    "sub_485cf8",
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the recovered variadic MSVC CRT ABIs to Binary Ninja."
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
        help="Path to the narrow Binary Ninja CRT prototype header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = [
        types_declare(REPO_ROOT, target=args.target, header_path=header_path),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=PROTO_UPDATES,
        ),
        *reanalyze_functions(
            REPO_ROOT,
            target=args.target,
            identifiers=SPRINTF_CALLERS,
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
