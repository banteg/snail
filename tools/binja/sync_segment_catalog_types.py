#!/usr/bin/env python3

from __future__ import annotations

from pathlib import Path
import sys

from _target import DEFAULT_TARGET
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


REPO_ROOT = Path(__file__).resolve().parents[2]
HEADER_PATH = REPO_ROOT / "analysis/headers/segment_catalog_types.h"
TARGET = DEFAULT_TARGET

EXPECTED_OWNER_SIZES = {
    "AuthoredSegmentRow": 0x38,
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
            *apply_user_var_updates(
                REPO_ROOT,
                target=TARGET,
                updates=SEGMENT_USER_VAR_UPDATES,
            ),
        ]
    )

    return emit_summary(repo_root=REPO_ROOT, target=TARGET, header_path=HEADER_PATH, operations=operations)


if __name__ == "__main__":
    sys.exit(main())
