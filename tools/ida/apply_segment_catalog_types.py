from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc


TRUSTED_NAMES = (
    (0x443650, "load_frontend_level_by_mode_and_index"),
    (0x447300, "copy_segment_definition_to_level_slot"),
    (0x447480, "load_level_definition_file"),
    (0x448060, "load_builtin_segment_definitions"),
    (0x448160, "load_segment_definitions"),
    (0x448900, "load_level_definitions"),
    (0x74EC74, "g_current_level_definition_name"),
    (0x74EC78, "g_level_file_text_buffer"),
)

TRUSTED_DATA_DECLARATIONS = (
    (
        0x74EC74,
        "g_current_level_definition_name",
        "char *g_current_level_definition_name;",
    ),
    (
        0x74EC78,
        "g_level_file_text_buffer",
        "char g_level_file_text_buffer[10240];",
    ),
)

DIRTY_FUNCTIONS = (
    0x443650,
    0x447300,
    0x447480,
    0x448060,
    0x448160,
    0x448900,
)

SEGMENT_COPY_ENTRY_ANCHOR_DEFEA = 0x447372

SEGMENT_COPY_LVAR_SPECS = (
    (
        "copy_segment_definition_to_level_slot",
        0x44730E,
        None,
        "catalog",
        "SMTracks *catalog;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447314,
        None,
        "catalog_index",
        "int32_t catalog_index;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x44731B,
        None,
        "catalog_filename_cursor",
        "char *catalog_filename_cursor;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x44735C,
        None,
        "destination_segment",
        "SubSegment *destination_segment;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447365,
        32,
        "glyph_lane_remaining",
        "int32_t glyph_lane_remaining;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447375,
        None,
        "destination_glyph_row_cursor",
        "char *destination_glyph_row_cursor;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447378,
        None,
        "source_glyph_lane_cursor",
        "char *source_glyph_lane_cursor;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447384,
        None,
        "glyph_column_index",
        "int32_t glyph_column_index;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x44738A,
        None,
        "source_glyph_column_cursor",
        "char *source_glyph_column_cursor;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x44738C,
        None,
        "glyph",
        "char glyph;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x4473BA,
        None,
        "metadata_row_index",
        "int32_t metadata_row_index;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x4473DB,
        None,
        "destination_metadata_cursor",
        (
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView, 0x14) "
            "destination_metadata_cursor;"
        ),
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x4473E1,
        None,
        "source_metadata_cursor",
        (
            "int32_t *__shifted(AuthoredSegmentRowObjectIdCursorView, 0x14) "
            "source_metadata_cursor;"
        ),
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447424,
        None,
        "source_local_position",
        "Vec3 *source_local_position;",
    ),
    (
        "copy_segment_definition_to_level_slot",
        0x447427,
        None,
        "destination_local_position",
        "Vec3 *destination_local_position;",
    ),
)

SEGMENT_IMPORT_LVAR_SPECS = (
    (
        "load_segment_definitions",
        0x448186,
        64,
        "tracks_after_stack_probe",
        "SMTracks *tracks_after_stack_probe;",
    ),
    (
        "load_segment_definitions",
        0x4481D8,
        60,
        "segment_file_name_cursor",
        "char *segment_file_name_cursor;",
    ),
    (
        "load_segment_definitions",
        0x448301,
        80,
        "row_index",
        "int32_t row_index;",
    ),
    (
        "load_segment_definitions",
        0x448387,
        148,
        "option_text",
        "char option_text[512];",
    ),
    (
        "load_segment_definitions",
        0x4481FB,
        788,
        "file_path",
        "char file_path[512];",
    ),
    (
        "load_segment_definitions",
        0x448223,
        1300,
        "file_buffer",
        "char file_buffer[4096];",
    ),
    (
        "load_segment_definitions",
        0x44818B,
        5396,
        "segment_files",
        "char segment_files[512][128];",
    ),
    (
        "load_segment_definitions",
        0x448336,
        None,
        "row_stride_anchor",
        "SegmentCatalogRowStrideAnchor *row_stride_anchor;",
    ),
)

LEVEL_PARSER_LVAR_SPECS = (
    (
        "load_level_definition_file",
        0x44753F,
        None,
        "level_display_name_cursor",
        "char *level_display_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x4477EE,
        None,
        "script_name_cursor",
        "char *script_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x447BCC,
        None,
        "segment_name_cursor",
        "char *segment_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x447C26,
        None,
        "line_options_cursor",
        "char *line_options_cursor;",
    ),
    (
        "load_level_definition_file",
        0x447E1E,
        None,
        "sample_name_cursor",
        "char *sample_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x447F60,
        None,
        "first_segment_name_cursor",
        "char *first_segment_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x44800F,
        None,
        "last_segment_name_cursor",
        "char *last_segment_name_cursor;",
    ),
    (
        "load_level_definition_file",
        0x447C2D,
        52,
        "line_cursor",
        "char *line_cursor;",
    ),
    (
        "load_level_definition_file",
        0x4478A4,
        56,
        "parsed_int",
        "int32_t parsed_int;",
    ),
    (
        "load_level_definition_file",
        0x447B7F,
        60,
        "segments_end",
        "char *segments_end;",
    ),
    (
        "load_level_definition_file",
        0x4474A4,
        64,
        "level_path",
        "char level_path[512];",
    ),
    (
        "load_level_definition_file",
        0x447C25,
        576,
        "line_options",
        "char line_options[128];",
    ),
    (
        "load_level_definition_file",
        0x447E1D,
        704,
        "sample_name",
        "char sample_name[128];",
    ),
    (
        "load_level_definition_file",
        0x447BCB,
        832,
        "segment_name",
        "char segment_name[512];",
    ),
    (
        "load_level_definition_file",
        0x4477ED,
        1344,
        "script_name",
        "char script_name[512];",
    ),
)

SEGMENT_OWNER_MARKERS = (
    "typedef struct AuthoredSegmentRow {",
    "typedef struct __ptr_offset(0x14) AuthoredSegmentRowObjectIdCursorView {",
    "typedef struct SegmentCatalogEntry {",
    "typedef struct SegmentCatalogEntryAnchor {",
    "typedef struct SegmentCatalogRowStrideAnchor {",
    "typedef struct SMTracks {",
    "SegmentCatalogEntry entries[150];",
    "typedef struct SubSegment {",
    "AuthoredSegmentRow rows[256];",
    "typedef struct SubTracks {",
    "SubSegment segment_slots[100];",
    "typedef struct SubSegmentRaw {",
)

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


TRUSTED_DECLARATIONS = [
    (
        "load_frontend_level_by_mode_and_index",
        "void __thiscall load_frontend_level_by_mode_and_index(SubTracks *tracks, int mode, int level_index);",
    ),
    (
        "copy_segment_definition_to_level_slot",
        "void __thiscall copy_segment_definition_to_level_slot(SubTracks *tracks, char *segment_name, SubSegment *segment);",
    ),
    (
        "load_level_definition_file",
        "void __thiscall load_level_definition_file(SubTracks *tracks, char *filename);",
    ),
    (
        "load_builtin_segment_definitions",
        "void __thiscall load_builtin_segment_definitions(SubTracks *tracks, SubSegmentRaw **raw_segments);",
    ),
    (
        "load_segment_definitions",
        "void __thiscall load_segment_definitions(SMTracks *tracks);",
    ),
    (
        "load_level_definitions",
        "void __thiscall load_level_definitions(SMTracks *tracks);",
    ),
]


def _resolve_function(selector: str) -> tuple[int | None, str]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]", "]", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _sync_owned_lvar(
    selector: str,
    definition_address: int,
    stack_offset: int | None,
    expected_name: str,
    declaration: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {
            "status": "failed",
            "reason": "missing_function",
            "selector": selector,
        }

    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_owned_lvar_type_failed",
            "selector": selector,
            "declaration": declaration,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.defea == definition_address
        and (
            (stack_offset is None and not lvar.is_stk_var())
            or (
                stack_offset is not None
                and lvar.is_stk_var()
                and lvar.get_stkoff() == stack_offset
            )
        )
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_owned_lvar_candidates",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    expected_type = _normalize_type_text(str(local_type))
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == expected_name and observed_type == expected_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": expected_name,
            "type": str(local_type),
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = expected_name
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_owned_lvar_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.defea == definition_address
        and candidate.name == expected_name
        and _normalize_type_text(str(candidate.type())) == expected_type
        and (
            (stack_offset is None and not candidate.is_stk_var())
            or (
                stack_offset is not None
                and candidate.is_stk_var()
                and candidate.get_stkoff() == stack_offset
            )
        )
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "owned_lvar_readback_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": before_name,
        "before_type": before_type,
        "name": expected_name,
        "type": str(local_type),
        "definition_address": hex(definition_address),
        "stack_offset": stack_offset,
    }


def _sync_builtin_grid_offset_lvar() -> dict[str, object]:
    selector = "load_builtin_segment_definitions"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var()
        and (
            lvar.name in {"builtins", "grid_offset"}
            or "BuiltinSegmentDefinition" in str(lvar.type())
        )
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_local_candidates",
            "candidate_count": len(candidates),
            "selector": selector,
        }

    lvar = candidates[0]
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == "grid_offset" and observed_type in {"int", "int32_t"}:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "selector": selector,
        }

    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        "int32_t grid_offset;",
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_grid_offset_type_failed",
            "selector": selector,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "grid_offset"
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_user_lvar_info_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_candidates = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if candidate.is_stk_var() and candidate.name == "grid_offset"
    ]
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "grid_offset_readback_failed",
            "candidate_count": len(verified_candidates),
            "selector": selector,
        }

    verified = verified_candidates[0]
    verified_type = _normalize_type_text(str(verified.type()))
    if verified_type not in {"int", "int32_t"}:
        return {
            "status": "failed",
            "reason": "grid_offset_type_readback_failed",
            "observed_type": str(verified.type()),
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified.name,
        "type": str(verified.type()),
        "selector": selector,
    }


def _sync_segment_copy_entry_anchor_lvar() -> dict[str, object]:
    selector = "copy_segment_definition_to_level_slot"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_stk_var()
        and lvar.defea == SEGMENT_COPY_ENTRY_ANCHOR_DEFEA
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_entry_anchor_candidates",
            "candidate_count": len(candidates),
            "selector": selector,
        }

    lvar = candidates[0]
    observed_type = _normalize_type_text(str(lvar.type()))
    expected_types = {
        "SegmentCatalogEntryAnchor *",
        "struct SegmentCatalogEntryAnchor *",
    }
    if lvar.name == "selected_entry_anchor" and observed_type in expected_types:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "defea": hex(lvar.defea),
            "location": str(lvar.location),
            "selector": selector,
        }

    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        "SegmentCatalogEntryAnchor *selected_entry_anchor;",
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "reason": "parse_entry_anchor_type_failed",
            "selector": selector,
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = "selected_entry_anchor"
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_entry_anchor_lvar_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_candidates = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_stk_var()
        and candidate.defea == SEGMENT_COPY_ENTRY_ANCHOR_DEFEA
        and candidate.name == "selected_entry_anchor"
    ]
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "entry_anchor_readback_failed",
            "candidate_count": len(verified_candidates),
            "selector": selector,
        }

    verified = verified_candidates[0]
    verified_type = _normalize_type_text(str(verified.type()))
    if verified_type not in expected_types:
        return {
            "status": "failed",
            "reason": "entry_anchor_type_readback_failed",
            "observed_type": str(verified.type()),
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": before_name,
        "before_type": before_type,
        "name": verified.name,
        "type": str(verified.type()),
        "defea": hex(verified.defea),
        "location": str(verified.location),
        "selector": selector,
    }


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in SEGMENT_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [{"reason": "noncanonical_segment_owner_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    owner_size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": owner_sizes[name],
        }
        for name, expected_size in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected_size
    ]
    if parse_errors or owner_size_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_sizes": owner_sizes,
                    "failed": owner_size_failures,
                },
                indent=2,
            )
        )
        return 1

    renamed = 0
    names_unchanged = 0
    applied = 0
    unchanged = 0
    data_applied = 0
    data_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"address": hex(address), "selector": name, "reason": "rename_failed"}
            )
            continue
        renamed += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected = _data_declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            data_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "declaration": declaration,
                    "reason": "set_data_type_failed",
                }
            )
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "declaration": declaration,
                    "observed": observed,
                    "expected": expected,
                    "reason": "data_verification_failed",
                }
            )
            continue
        data_applied += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        current_type = idc.get_type(address)
        normalized_current = _normalize_type_text(current_type)

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue

        applied += 1

    name_failures = [
        {
            "address": hex(address),
            "selector": name,
            "observed": idc.get_name(address),
            "reason": "name_verification_failed",
        }
        for address, name in TRUSTED_NAMES
        if idc.get_name(address) != name
    ]
    failed.extend(name_failures)

    dirty_functions = []
    for address in DIRTY_FUNCTIONS:
        function = ida_funcs.get_func(address)
        if function is None or function.start_ea != address:
            failed.append(
                {
                    "address": hex(address),
                    "reason": "missing_dirty_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        dirty_functions.append(hex(address))

    segment_entry_lvar = _sync_segment_copy_entry_anchor_lvar()
    if segment_entry_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "copy_segment_definition_to_level_slot",
                "segment_entry_lvar": segment_entry_lvar,
            }
        )

    segment_copy_lvars = [
        _sync_owned_lvar(
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        )
        for (
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        ) in SEGMENT_COPY_LVAR_SPECS
    ]
    segment_copy_lvar_failures = [
        result for result in segment_copy_lvars if result.get("status") == "failed"
    ]
    if segment_copy_lvar_failures:
        failed.append(
            {
                "selector": "copy_segment_definition_to_level_slot",
                "segment_copy_lvars": segment_copy_lvars,
            }
        )

    grid_offset_lvar = _sync_builtin_grid_offset_lvar()
    if grid_offset_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "load_builtin_segment_definitions",
                "grid_offset_lvar": grid_offset_lvar,
            }
        )

    segment_import_lvars = [
        _sync_owned_lvar(
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        )
        for (
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        ) in SEGMENT_IMPORT_LVAR_SPECS
    ]
    segment_import_lvar_failures = [
        result
        for result in segment_import_lvars
        if result.get("status") == "failed"
    ]
    if segment_import_lvar_failures:
        failed.append(
            {
                "selector": "load_segment_definitions",
                "segment_import_lvars": segment_import_lvars,
            }
        )

    level_parser_lvars = [
        _sync_owned_lvar(
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        )
        for (
            selector,
            definition_address,
            stack_offset,
            expected_name,
            declaration,
        ) in LEVEL_PARSER_LVAR_SPECS
    ]
    level_parser_lvar_failures = [
        result for result in level_parser_lvars if result.get("status") == "failed"
    ]
    if level_parser_lvar_failures:
        failed.append(
            {
                "selector": "load_level_definition_file",
                "level_parser_lvars": level_parser_lvars,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "applied": applied,
                "unchanged": unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "dirty_functions": dirty_functions,
                "segment_entry_lvar": segment_entry_lvar,
                "segment_copy_lvars": segment_copy_lvars,
                "grid_offset_lvar": grid_offset_lvar,
                "segment_import_lvars": segment_import_lvars,
                "level_parser_lvars": level_parser_lvars,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if parse_errors or failed or missing:
        return 1
    return 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_segment_catalog_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    if not header_path.is_file():
        print(f"missing header: {header_path}", file=sys.stderr)
        ida_pro.qexit(2)
        return

    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
