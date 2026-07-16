#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_symbol_updates,
    apply_user_var_updates,
    emit_summary,
    types_declare_if_changed,
)


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/segment_catalog_types.h"
TARGET = DEFAULT_TARGET

DATA_SYMBOL_UPDATES = (
    ("0x74ec74", "g_current_level_definition_name"),
    ("0x74ec78", "g_level_file_text_buffer"),
)

DATA_VAR_UPDATES = (
    ("0x74ec74", "char*"),
    ("0x74ec78", "LevelFileTextBuffer"),
)

# The selected entry is materialized as an EDX SSA owner after a native
# 0x4088-stride calculation from the SMTracks base. That leaves the register
# four bytes before the entry, so the exact anchor view preserves the count /
# previous-tail prefix without shifting any entry field.
SEGMENT_COPY_USER_VAR_UPDATES = (
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        113,
        68,
        "selected_entry_anchor",
        "SegmentCatalogEntryAnchor*",
    ),
)

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
        types_declare_if_changed(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
        ),
        *apply_symbol_updates(
            REPO_ROOT,
            target=TARGET,
            updates=DATA_SYMBOL_UPDATES,
        ),
        *apply_data_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=DATA_VAR_UPDATES,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
        *apply_user_var_updates(
            REPO_ROOT,
            target=TARGET,
            updates=SEGMENT_COPY_USER_VAR_UPDATES,
        ),
    ]

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
