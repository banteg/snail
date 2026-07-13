#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, emit_summary, types_declare


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/segment_catalog_types.h"
TARGET = "active"

PROTO_UPDATES = (
    (
        "load_frontend_level_by_mode_and_index",
        "void __thiscall load_frontend_level_by_mode_and_index(SubTracks* tracks, int32_t mode, int32_t level_index)",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "void __thiscall copy_segment_definition_to_level_slot(SubTracks* tracks, char* segment_name, SubSegment* segment)",
    ),
    (
        "load_level_definition_file",
        "void __thiscall load_level_definition_file(SubTracks* tracks, char* filename)",
    ),
    (
        "load_builtin_segment_definitions",
        "void __thiscall load_builtin_segment_definitions(SubTracks* tracks, SubSegmentRaw** raw_segments)",
    ),
    (
        "load_segment_definitions",
        "void __thiscall load_segment_definitions(SMTracks* tracks)",
    ),
    (
        "load_level_definitions",
        "void __thiscall load_level_definitions(SMTracks* tracks)",
    ),
)


def main() -> int:
    operations: list[dict[str, object]] = [
        types_declare(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
