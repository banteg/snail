#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_symbol_updates,
    emit_summary,
)
from _target import DEFAULT_TARGET
from sync_input_state_types import (
    HEADER_PATH,
    INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES,
    INPUT_POINTER_REGION_DATA_VAR_UPDATES,
    INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES,
    INPUT_POINTER_REGION_PROTO_UPDATES,
)


REPO_ROOT = Path(__file__).resolve().parents[2]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Apply only the input-pointer region sidecars and helper ABIs to a "
            "Binary Ninja target."
        )
    )
    parser.add_argument(
        "--target",
        default=DEFAULT_TARGET,
        help="Binary Ninja target selector.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    operations = [
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=INPUT_POINTER_REGION_FUNCTION_SYMBOL_UPDATES,
            kind="function",
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=args.target,
            updates=INPUT_POINTER_REGION_DATA_SYMBOL_UPDATES,
            kind="data",
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=INPUT_POINTER_REGION_DATA_VAR_UPDATES,
        ),
        *apply_proto_updates(
            REPO_ROOT,
            target=args.target,
            updates=INPUT_POINTER_REGION_PROTO_UPDATES,
        ),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=args.target,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
