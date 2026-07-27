#!/usr/bin/env python3

from __future__ import annotations

import sys
from pathlib import Path

from _narrow_sync import (
    apply_data_var_updates,
    apply_proto_updates,
    apply_split_user_var_update,
    apply_symbol_updates,
    apply_user_var_updates,
    current_type_widths,
    emit_summary,
    types_declare_if_changed,
)
from _target import DEFAULT_TARGET

REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/segment_catalog_types.h"
TARGET = DEFAULT_TARGET

EXPECTED_OWNER_SIZES = {
    "AuthoredSegmentRow": 0x38,
    "AuthoredSegmentRowObjectIdCursorView": 0x38,
    "SegmentCatalogEntry": 0x4088,
    "SegmentCatalogEntryAnchor": 0x408C,
    "SegmentCatalogRowStrideAnchor": 0x8C4,
    "SMTracks": 0x25CFB4,
    "SubSegment": 0x4220,
    "SubTracks": 0x1A5978,
    "SubSegmentRaw": 0x48,
}

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
SEGMENT_USER_VAR_UPDATES = (
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        113,
        68,
        "selected_entry_anchor",
        "SegmentCatalogEntryAnchor*",
    ),
    # chkstk preserves ECX, but Binary Ninja conservatively starts a new SSA
    # variable for the register after the call. Recover that exact split as
    # the same SMTracks owner without changing chkstk's global call model,
    # whose stack-adjust semantics are needed by other large-frame callers.
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        5,
        67,
        "tracks_after_stack_probe",
        "SMTracks*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        469,
        72,
        "row_stride_anchor",
        "SegmentCatalogRowStrideAnchor*",
    ),
)

# The 0x114e0-byte importer frame is allocated through chkstk, which leaves
# Binary Ninja's otherwise-correct stack accesses named as incoming arguments
# and the return address. Pin the physical frame slots and the register
# lifetimes that borrow from them. The two base indices are measured in
# complete 0x38-byte authored rows and 8-byte glyph rows respectively; neither
# owns storage independently of SMTracks.
SEGMENT_IMPORT_CURSOR_USER_VAR_UPDATES = (
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        0,
        "parse_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        4,
        "row_count_cursor",
        "int32_t*",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        8,
        "segment_file_name_saved",
        "EnumeratedEntryName*",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        12,
        "ring_speed_catalog_owner",
        "SMTracks*",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        16,
        "segment_index_spill",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        20,
        "glyph_row_base",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        24,
        "segment_row_base",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        28,
        "row_index",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        32,
        "path_name",
        "char[64]",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        96,
        "option_text",
        "char[512]",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        608,
        "mesh_name",
        "char[128]",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        736,
        "file_path",
        "char[512]",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        1248,
        "file_buffer",
        "char[4096]",
    ),
    (
        "load_segment_definitions",
        "StackVariableSourceType",
        0,
        5344,
        "segment_files",
        "EnumeratedEntryName[512]",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        84,
        71,
        "segment_index",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        98,
        73,
        "segment_file_name_cursor",
        "EnumeratedEntryName*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        105,
        72,
        "row_count_cursor_register",
        "int32_t*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        257,
        72,
        "entry_filename_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        390,
        73,
        "data_line_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        452,
        71,
        "flattened_row_index",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        455,
        67,
        "glyph_catalog",
        "SMTracks*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        468,
        73,
        "glyph_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        472,
        66,
        "lane_index",
        "int32_t",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        492,
        69,
        "glyph",
        "char",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        527,
        73,
        "option_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        551,
        67,
        "option_out_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        559,
        66,
        "option_char",
        "char",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        623,
        67,
        "mesh_name_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        630,
        68,
        "mesh_char",
        "char",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        1089,
        68,
        "path_name_cursor",
        "char*",
    ),
    (
        "load_segment_definitions",
        "RegisterVariableSourceType",
        1093,
        67,
        "path_char",
        "char",
    ),
)

# The catalog-to-runtime copy walks three independent borrowed regions:
# catalog filenames, the eight glyph lanes, and each row's object_id-relative
# metadata cursor. Keep those register lifetimes explicit so neither glyph
# arrays nor the +0x14 metadata cursors become false owners in HLIL.
SEGMENT_COPY_USER_VAR_UPDATES = (
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        13,
        73,
        "catalog",
        "SMTracks*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        19,
        72,
        "catalog_index",
        "int32_t",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        26,
        71,
        "catalog_filename_cursor",
        "char*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        91,
        71,
        "destination_segment",
        "SubSegment*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        116,
        73,
        "destination_glyph_row_cursor",
        "char*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        119,
        67,
        "source_glyph_lane_cursor",
        "char*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        131,
        66,
        "glyph_column_index",
        "int32_t",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        137,
        72,
        "source_glyph_column_cursor",
        "char*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        139,
        69,
        "glyph",
        "char",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        185,
        72,
        "metadata_row_index",
        "int32_t",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        218,
        67,
        "destination_metadata_cursor",
        "AuthoredSegmentRowObjectIdCursorView*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        224,
        66,
        "source_metadata_cursor",
        "AuthoredSegmentRowObjectIdCursorView*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        291,
        73,
        "source_local_position",
        "Vec3*",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "RegisterVariableSourceType",
        294,
        69,
        "destination_local_position",
        "Vec3*",
    ),
)

# The original segment-name argument is dead once lookup succeeds. VC6 reuses
# its stack slot for the eight-lane countdown, whose initialization, loop phi,
# and decrement definitions must be split and merged as one integer lifetime.
SEGMENT_COPY_GLYPH_LANE_SPLIT_DEFINITIONS = (
    ("0x447364", "mlil", "StackVariableSourceType", 100, 4),
    ("0x44737d", "mlil_ssa", "StackVariableSourceType", 125, 4),
    ("0x4473aa", "mlil", "StackVariableSourceType", 170, 4),
)

SEGMENT_COPY_GLYPH_LANE_TARGET_VAR = (
    "StackVariableSourceType",
    100,
    4,
)

# VC6 first materializes SubTracks::level_display_name in EBP, then hands the
# borrowed byte cursor to EDX for the write loop. Those simultaneously live
# registers remain distinct. The parser's native 0x710-byte frame then keeps
# four scalar/cursor slots followed by five independently owned buffers. Pin
# the complete storage extents instead of allowing HLIL to collapse the
# 128-byte line-options bank to `void` or carry anonymous frame offsets through
# every diagnostic path.
LEVEL_PARSER_USER_VAR_UPDATES = (
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        182,
        71,
        "level_display_name_begin",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        190,
        68,
        "level_display_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        877,
        67,
        "script_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        1867,
        67,
        "segment_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        1957,
        68,
        "line_options_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        2461,
        68,
        "sample_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        2783,
        67,
        "first_segment_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "RegisterVariableSourceType",
        2958,
        67,
        "last_segment_name_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1804,
        "line_cursor",
        "char*",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1800,
        "parsed_int",
        "int32_t",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        1790,
        -1796,
        "segments_end",
        "char*",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1792,
        "level_path",
        "char[512]",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1280,
        "line_options",
        "char[128]",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1152,
        "sample_name",
        "char[128]",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -1024,
        "segment_name",
        "char[512]",
    ),
    (
        "load_level_definition_file",
        "StackVariableSourceType",
        0,
        -512,
        "script_name",
        "char[512]",
    ),
)

# VC6 copies raw_segments to EBX, then reuses the dead stack argument slot as
# the 0x100-byte glyph-lane offset. Binary Ninja needs all three definition
# sites split and merged before the slot can own its real integer lifetime.
BUILTIN_GRID_OFFSET_SPLIT_DEFINITIONS = (
    ("0x44809d", "mlil", "StackVariableSourceType", 61, 4),
    ("0x4480c2", "mlil_ssa", "StackVariableSourceType", 98, 4),
    ("0x448109", "mlil", "StackVariableSourceType", 169, 4),
)

BUILTIN_GRID_OFFSET_TARGET_VAR = (
    "StackVariableSourceType",
    61,
    4,
)

# Correcting RTextExtractFloat to float32 exposes the EAX/EDI copies that feed
# this persistent stack owner. Merge the complete definition chain so HLIL
# keeps the segment-loop bound as `segments_end` instead of an auto register.
LEVEL_SEGMENTS_END_SPLIT_DEFINITIONS = (
    ("0x447b72", "mlil", "RegisterVariableSourceType", 1778, 66),
    ("0x447b77", "mlil", "RegisterVariableSourceType", 1783, 73),
    ("0x447b7e", "mlil", "StackVariableSourceType", 1790, -1796),
)
LEVEL_SEGMENTS_END_TARGET_VAR = (
    "StackVariableSourceType",
    1790,
    -1796,
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
        )
    ]

    observed_sizes = current_type_widths(
        REPO_ROOT,
        target=TARGET,
        type_names=EXPECTED_OWNER_SIZES,
    )
    mismatches = []
    for name, expected_size in EXPECTED_OWNER_SIZES.items():
        observed_size = observed_sizes.get(name)
        status = "verified" if observed_size == expected_size else "verification_failed"
        operations.append(
            {
                "op": "owner_size_verify",
                "name": name,
                "expected_size": expected_size,
                "observed_size": observed_size,
                "status": status,
            }
        )
        if status == "verification_failed":
            mismatches.append(
                f"{name}: expected {expected_size:#x}, observed {observed_size!r}"
            )

    if mismatches:
        raise RuntimeError("Segment catalog owner size mismatch: " + "; ".join(mismatches))

    operations.extend(
        [
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
            *apply_split_user_var_update(
                REPO_ROOT,
                target=TARGET,
                identifier="load_builtin_segment_definitions",
                definitions=BUILTIN_GRID_OFFSET_SPLIT_DEFINITIONS,
                target_var=BUILTIN_GRID_OFFSET_TARGET_VAR,
                variable_name="grid_offset",
                variable_type="int32_t",
            ),
            *apply_split_user_var_update(
                REPO_ROOT,
                target=TARGET,
                identifier="load_level_definition_file",
                definitions=LEVEL_SEGMENTS_END_SPLIT_DEFINITIONS,
                target_var=LEVEL_SEGMENTS_END_TARGET_VAR,
                variable_name="segments_end",
                variable_type="char*",
            ),
            *apply_split_user_var_update(
                REPO_ROOT,
                target=TARGET,
                identifier="copy_segment_definition_to_level_slot",
                definitions=SEGMENT_COPY_GLYPH_LANE_SPLIT_DEFINITIONS,
                target_var=SEGMENT_COPY_GLYPH_LANE_TARGET_VAR,
                variable_name="glyph_lane_remaining",
                variable_type="int32_t",
            ),
            *apply_user_var_updates(
                REPO_ROOT,
                target=TARGET,
                updates=(
                    *SEGMENT_USER_VAR_UPDATES,
                    *SEGMENT_IMPORT_CURSOR_USER_VAR_UPDATES,
                    *SEGMENT_COPY_USER_VAR_UPDATES,
                    *LEVEL_PARSER_USER_VAR_UPDATES,
                ),
            ),
        ]
    )

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
