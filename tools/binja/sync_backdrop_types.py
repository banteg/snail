#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_proto_updates,
    apply_struct_field_updates,
    apply_user_var_updates,
    current_struct_size,
    emit_summary,
    reanalyze_functions,
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_HEADER_PATH = REPO_ROOT / "analysis/headers/bn_backdrop_types.h"

GAME_ROOT_FIELD_UPDATES = (
    ("0x4ec10", "backdrop", "Backdrop"),
)

PROTO_UPDATES = (
    (
        "set_backdrop_progress_fraction",
        "void __thiscall set_backdrop_progress_fraction(Backdrop* backdrop, float zoom)",
    ),
    (
        "set_backdrop_distort",
        "void __thiscall set_backdrop_distort(Backdrop* backdrop, float distort)",
    ),
    (
        "change_backdrop",
        "void __thiscall change_backdrop(Backdrop* backdrop, LandscapeScriptRecord* record, uint8_t flip)",
    ),
    (
        "change_backdrop_real",
        "void __thiscall change_backdrop_real(Backdrop* backdrop)",
    ),
    (
        "initialize_backdrop",
        "void __thiscall initialize_backdrop(Backdrop* backdrop, int32_t last_mode)",
    ),
    (
        "set_backdrop_texture_target",
        "void __thiscall set_backdrop_texture_target(Backdrop* backdrop, int32_t world)",
    ),
    (
        "draw_split_backdrop",
        "int32_t __thiscall draw_split_backdrop(Backdrop* backdrop)",
    ),
    (
        "render_backdrop",
        "void __thiscall render_backdrop(Backdrop* backdrop)",
    ),
    (
        "update_backdrop",
        "int32_t __thiscall update_backdrop(Backdrop* backdrop)",
    ),
)

# update_backdrop walks the row-major 8x8 distortion grid column-first.
# EBX borrows the first cell in the current column and advances by one cell;
# ESI borrows the current cell in that column and advances by eight cells.
# Pin the exact cell-pointer lifetimes so Binary Ninja does not promote either
# borrow to a pointer to the complete array and recover fields through a false
# subtraction from the Backdrop owner.
BACKDROP_DISTORT_USER_VAR_UPDATES = (
    (
        "update_backdrop",
        "RegisterVariableSourceType",
        25,
        69,
        "column_start",
        "BackdropDistortCell*",
    ),
    (
        "update_backdrop",
        "RegisterVariableSourceType",
        43,
        72,
        "cell",
        "BackdropDistortCell*",
    ),
)


def require_bod_base_dependency(*, target: str) -> None:
    size = current_struct_size(
        REPO_ROOT,
        target=target,
        struct_name="BodBase",
    )
    if size != 0x38:
        raise RuntimeError(
            "BodBase must be exactly 0x38 bytes before Backdrop replay; "
            f"observed {size!r}"
        )


def require_distort_cursor_dependencies(*, target: str) -> dict[str, object]:
    expected_sizes = {
        "BackdropDistortCell": 0x18,
        "Backdrop": 0x6CC,
    }
    observed_sizes = {
        name: current_struct_size(REPO_ROOT, target=target, struct_name=name)
        for name in expected_sizes
    }
    mismatches = {
        name: (expected_sizes[name], observed_sizes[name])
        for name in expected_sizes
        if observed_sizes[name] != expected_sizes[name]
    }
    if mismatches:
        detail = ", ".join(
            f"{name}: expected {expected:#x}, observed {observed!r}"
            for name, (expected, observed) in mismatches.items()
        )
        raise RuntimeError(
            "Backdrop distortion cursor dependencies are not current: " + detail
        )
    return {
        "op": "verify_backdrop_distort_cursor_dependencies",
        "status": "verified",
        "sizes": observed_sizes,
    }


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Apply the narrow cRBackdrop ownership slice to Binary Ninja."
    )
    parser.add_argument("--target", default=DEFAULT_TARGET, help="Binary Ninja target selector.")
    parser.add_argument(
        "--header",
        type=Path,
        default=DEFAULT_HEADER_PATH,
        help="Narrow Binary Ninja type header.",
    )
    parser.add_argument(
        "--distort-cursors-only",
        action="store_true",
        help=(
            "Replay only update_backdrop's two distortion-cell cursors after "
            "verifying the existing owner layouts."
        ),
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    header_path = args.header.resolve()
    if not header_path.is_file():
        raise FileNotFoundError(f"Binary Ninja type header not found: {header_path}")

    if args.distort_cursors_only:
        operations = [
            require_distort_cursor_dependencies(target=args.target),
            *apply_user_var_updates(
                REPO_ROOT,
                target=args.target,
                updates=BACKDROP_DISTORT_USER_VAR_UPDATES,
            ),
        ]
        return emit_summary(
            repo_root=REPO_ROOT,
            target=args.target,
            header_path=header_path,
            operations=operations,
        )

    require_bod_base_dependency(target=args.target)
    type_replay = types_declare_if_changed(
        REPO_ROOT, target=args.target, header_path=header_path
    )
    operations: list[dict[str, object]] = [type_replay]
    operations.extend(
        apply_struct_field_updates(
            REPO_ROOT,
            target=args.target,
            struct_name="GameRoot",
            updates=GAME_ROOT_FIELD_UPDATES,
        )
    )
    operations.extend(
        apply_proto_updates(REPO_ROOT, target=args.target, updates=PROTO_UPDATES)
    )
    operations.extend(
        apply_user_var_updates(
            REPO_ROOT,
            target=args.target,
            updates=BACKDROP_DISTORT_USER_VAR_UPDATES,
        )
    )
    if type_replay.get("status") != "skipped":
        operations.extend(
            reanalyze_functions(
                REPO_ROOT,
                target=args.target,
                identifiers=("construct_game_runtime",),
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
