#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_parse_helper_prototypes.h"

PROTO_UPDATES = (
    ("parse_next_int32", "int32_t __cdecl parse_next_int32(char** cursor)"),
    (
        "parse_next_space_delimited_token",
        "char** __cdecl parse_next_space_delimited_token(char** cursor, char* out)",
    ),
    ("parse_next_float32", "double __cdecl parse_next_float32(char** cursor)"),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow parser-helper prototype slice to the active Binary Ninja target."
    )
    parser.add_argument(
        "--target",
        default="active",
        help="Binary Ninja target selector. Defaults to the active target.",
    )
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Path to the narrow Binary Ninja type-import header.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    operations: list[dict[str, object]] = []
    operations.append(types_declare(REPO_ROOT, target=args.target, header_path=header_path))
    operations.extend(apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES))
    return emit_summary(repo_root=REPO_ROOT, target=args.target, header_path=header_path, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
