#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _narrow_sync import apply_proto_updates, emit_summary, types_declare_if_missing


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/segment_catalog_types.h"
TARGET = "active"

REQUIRED_HEADER_STRUCTS = (
    "AuthoredFloatBits",
    "AuthoredSegmentRow",
    "SegmentCatalogEntry",
    "SegmentCatalog",
    "LevelSegmentSlot",
    "LevelDefinitionLoader",
    "BuiltinSegmentDefinition",
    "LevelSegmentSlotStore",
)

PROTO_UPDATES = (
    (
        "copy_segment_definition_to_level_slot",
        "int32_t* __stdcall copy_segment_definition_to_level_slot(char* segment_name, LevelSegmentSlot* slot)",
    ),
    (
        "load_level_definition_file",
        "int32_t* __thiscall load_level_definition_file(LevelDefinitionLoader* loader, char* filename)",
    ),
    (
        "load_builtin_segment_definitions",
        "char* __thiscall load_builtin_segment_definitions(LevelSegmentSlotStore* store, BuiltinSegmentDefinition** builtins)",
    ),
    (
        "load_segment_definitions",
        "int32_t __thiscall load_segment_definitions(SegmentCatalog* catalog)",
    ),
    (
        "load_level_definitions",
        "int32_t __thiscall load_level_definitions(SegmentCatalog* catalog)",
    ),
)


def main() -> int:
    operations: list[dict[str, object]] = [
        types_declare_if_missing(
            REPO_ROOT,
            target=TARGET,
            header_path=HEADER_PATH,
            required_structs=REQUIRED_HEADER_STRUCTS,
        ),
        *apply_proto_updates(REPO_ROOT, target=TARGET, updates=PROTO_UPDATES),
    ]

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
