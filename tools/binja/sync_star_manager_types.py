#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/star_manager_types.h"
TARGET = "active"

PROTO_UPDATES = (
    ("destroy_star_field", "int32_t __thiscall destroy_star_field(StarManager* manager)"),
    (
        "open_star_field",
        "void __thiscall open_star_field(StarManager* manager, int32_t star_count)",
    ),
    (
        "initialize_star_field",
        "int32_t __thiscall initialize_star_field(StarManager* manager)",
    ),
    ("hide_star_field", "int32_t __thiscall hide_star_field(StarManager* manager)"),
    ("unhide_star_field", "int32_t __thiscall unhide_star_field(StarManager* manager)"),
    ("update_star_field", "void __thiscall update_star_field(StarManager* manager)"),
    (
        "update_star_positions",
        "void __thiscall update_star_positions(StarManager* manager, float fade_alpha)",
    ),
)


def main() -> int:
    operations: list[dict[str, object]] = [
        types_declare(REPO_ROOT, target=TARGET, header_path=HEADER_PATH),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]
    return emit_summary(
        repo_root=REPO_ROOT,
        target=TARGET,
        header_path=HEADER_PATH,
        operations=operations,
    )


if __name__ == "__main__":
    sys.exit(main())
