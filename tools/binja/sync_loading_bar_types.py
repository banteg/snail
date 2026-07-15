#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_struct_and_proto_updates,
    apply_symbol_updates,
    current_struct_size,
    emit_summary,
    types_declare_missing_only,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_loading_bar_types.h"

EXPECTED_STRUCT_SIZE = 0x0C

DATA_SYMBOL_UPDATES = (
    ("0x503290", "g_loading_bar"),
)

DATA_VAR_UPDATES = (
    ("0x503290", "LoadingBar"),
)

PROTO_UPDATES = (
    (
        "initialize_loading_screen",
        "void __thiscall initialize_loading_screen(LoadingBar* loading_bar)",
    ),
    (
        "destroy_loading_screen",
        "void __thiscall destroy_loading_screen(LoadingBar* loading_bar)",
    ),
    (
        "update_loading_screen",
        "void __thiscall update_loading_screen(LoadingBar* loading_bar)",
    ),
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the exact cRLoadingBar owner and void lifecycle ABI."
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

    observed_size = current_struct_size(
        REPO_ROOT,
        target=args.target,
        struct_name="LoadingBar",
    )
    if observed_size != EXPECTED_STRUCT_SIZE:
        type_operation = types_declare_missing_only(
            REPO_ROOT,
            target=args.target,
            header_path=header_path,
            replace_types=("LoadingBar",),
        )
        type_operation["observed_size"] = observed_size
        type_operation["expected_size"] = EXPECTED_STRUCT_SIZE
    else:
        type_operation = {
            "op": "types_declare_missing_only",
            "status": "skipped",
            "reason": "LoadingBar owner size already current",
            "header": str(header_path),
            "expected_size": EXPECTED_STRUCT_SIZE,
        }

    operations: list[dict[str, object]] = [
        type_operation,
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=DATA_VAR_UPDATES,
        ),
        *apply_struct_and_proto_updates(
            REPO_ROOT,
            target=args.target,
            struct_updates=(),
            proto_updates=PROTO_UPDATES,
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
