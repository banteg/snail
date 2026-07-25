from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_pro
import ida_typeinf
import idc


DISPLAY_MODE_STATE_ADDRESS = 0x4DF9E0
DISPLAY_MODE_STATE_MINIMUM_SIZE = 0x1C
NEXT_KNOWN_OWNER_ADDRESS = 0x4DFAD0

EXPECTED_STRUCT_SIZES = (
    ("DisplayModeRecord", 0x10),
    ("DisplayModeViewSample", 0x10),
    ("DisplayModeState", DISPLAY_MODE_STATE_MINIMUM_SIZE),
)

TRUSTED_NAMES = (
    (0x406D70, "initialize_main_loop_display_state"),
    (0x407910, "clear_display_mode_state"),
    (0x407920, "reset_display_mode_probe_count"),
    (0x407930, "read_next_display_mode_view_sample"),
    (0x412940, "update_display_mode_view_state"),
    (0x4134C0, "render_game_frame_scene"),
    (0x433030, "get_authored_view_width"),
    (0x433040, "get_authored_view_height"),
    (DISPLAY_MODE_STATE_ADDRESS, "g_display_mode_state"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_main_loop_display_state",
        "void __cdecl initialize_main_loop_display_state();",
    ),
    (
        "clear_display_mode_state",
        "void __thiscall clear_display_mode_state(DisplayModeState *state);",
    ),
    (
        "reset_display_mode_probe_count",
        "void __thiscall reset_display_mode_probe_count(DisplayModeState *state);",
    ),
    (
        "read_next_display_mode_view_sample",
        "uint8_t __thiscall read_next_display_mode_view_sample("
        "DisplayModeState *state, float *x, float *y, "
        "float *width, float *height);",
    ),
    (
        "update_display_mode_view_state",
        "uint8_t __thiscall update_display_mode_view_state("
        "DisplayModeState *state);",
    ),
    (
        "render_game_frame_scene",
        "void __cdecl render_game_frame_scene();",
    ),
    (
        "get_authored_view_width",
        "float __cdecl get_authored_view_width();",
    ),
    (
        "get_authored_view_height",
        "float __cdecl get_authored_view_height();",
    ),
)

TRUSTED_DATA_DECLARATION = (
    DISPLAY_MODE_STATE_ADDRESS,
    "g_display_mode_state",
    "DisplayModeState g_display_mode_state;",
)

DEPENDENT_DECOMPILE_FUNCTIONS = (
    "game_window_proc",
    "render_game_frame_scene",
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct DisplayModeRecord {",
    "uint16_t width;",
    "uint16_t height;",
    "typedef struct DisplayModeViewSample {",
    "typedef struct DisplayModeState {",
    "DisplayModeRecord* current_mode;",
    "DisplayModeViewSample view_samples[1];",
    "DisplayModeState_minimum_prefix_must_be_0x1c",
    "extern DisplayModeState g_display_mode_state;",
)

# The update helper passes four address-taken stack floats to the exact sample
# reader ABI. Hex-Rays initially leaves the x slot as int and compensates with
# a float-pointer cast; exact definition address plus stack offset recovers the
# four borrows without relying on transient vN names.
UPDATE_SAMPLE_LVAR_SPECS = (
    ("y", "float y;", 0x41297C, 24, ("float",)),
    ("height", "float height;", 0x41297C, 28, ("float",)),
    ("width", "float width;", 0x41297C, 32, ("float",)),
    ("x", "float x;", 0x41297C, 36, ("int", "float")),
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    normalized = re.sub(r"\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)", ")", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\()",
        "",
        declaration,
        count=1,
    )
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(
    selector: str,
    declaration: str,
) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\b",
        "",
        declaration,
        count=1,
    )
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _sync_update_sample_lvar(
    expected_name: str,
    declaration: str,
    definition_address: int,
    stack_offset: int,
    accepted_types: tuple[str, ...],
) -> dict[str, object]:
    selector = "update_display_mode_view_state"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "missing_function",
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.get_stkoff() == stack_offset
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_sample_lvar_candidates",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    observed_name = lvar.name
    observed_type = _normalize_type_text(str(lvar.type())) or ""
    accepted_normalized_types = {
        _normalize_type_text(value) or "" for value in accepted_types
    }
    if (
        observed_name != expected_name
        and not re.fullmatch(r"v\d+", observed_name)
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_sample_lvar_name",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "observed_name": observed_name,
            "expected_name": expected_name,
        }
    if observed_type not in accepted_normalized_types:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_sample_lvar_type",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "observed_type": observed_type,
            "accepted_types": sorted(accepted_normalized_types),
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
            "selector": selector,
            "reason": "parse_sample_lvar_type_failed",
            "declaration": declaration,
        }
    expected_type = _normalize_type_text(str(local_type)) or ""
    if observed_name == expected_name and observed_type == expected_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": observed_name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "stack_offset": lvar.get_stkoff(),
        }

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
            "selector": selector,
            "reason": "modify_sample_lvar_failed",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.get_stkoff() == stack_offset
        and candidate.name == expected_name
        and (_normalize_type_text(str(candidate.type())) or "")
        == expected_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "sample_lvar_readback_failed",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(verified),
        }
    return {
        "status": "applied",
        "selector": selector,
        "before_name": observed_name,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
        "stack_offset": verified[0].get_stkoff(),
    }


def _prepare_minimum_owner_extent() -> dict[str, object]:
    if (
        DISPLAY_MODE_STATE_ADDRESS + DISPLAY_MODE_STATE_MINIMUM_SIZE
        > NEXT_KNOWN_OWNER_ADDRESS
    ):
        return {
            "status": "failed",
            "reason": "invalid_checked_in_minimum_owner_boundary",
        }

    item_head = ida_bytes.get_item_head(DISPLAY_MODE_STATE_ADDRESS)
    item_size = ida_bytes.get_item_size(item_head)
    if (
        item_head == DISPLAY_MODE_STATE_ADDRESS
        and item_size == DISPLAY_MODE_STATE_MINIMUM_SIZE
    ):
        observed_name = idc.get_name(DISPLAY_MODE_STATE_ADDRESS)
        observed_type = _normalize_type_text(
            idc.get_type(DISPLAY_MODE_STATE_ADDRESS)
        )
        if (
            observed_name != "g_display_mode_state"
            or observed_type != "DisplayModeState"
        ):
            return {
                "status": "failed",
                "reason": "unexpected_existing_display_mode_state_owner",
                "observed_name": observed_name,
                "observed_type": observed_type,
                "observed_size": item_size,
            }
        return {
            "status": "unchanged",
            "address": hex(DISPLAY_MODE_STATE_ADDRESS),
            "minimum_size": item_size,
            "next_known_owner": hex(NEXT_KNOWN_OWNER_ADDRESS),
        }

    observed_name = idc.get_name(DISPLAY_MODE_STATE_ADDRESS)
    observed_type = _normalize_type_text(
        idc.get_type(DISPLAY_MODE_STATE_ADDRESS)
    )
    accepted_stale_types = (None, "_DWORD[60]", "int[60]")
    if (
        item_head != DISPLAY_MODE_STATE_ADDRESS
        or item_size != 1
        or observed_name != "g_display_mode_state"
        or observed_type not in accepted_stale_types
    ):
        return {
            "status": "failed",
            "reason": "unexpected_display_mode_state_extent_head",
            "observed_head": hex(item_head),
            "observed_size": item_size,
            "observed_name": observed_name,
            "observed_type": observed_type,
            "accepted_stale_types": accepted_stale_types,
        }

    conflicts = []
    for address in range(
        DISPLAY_MODE_STATE_ADDRESS + 1,
        DISPLAY_MODE_STATE_ADDRESS + DISPLAY_MODE_STATE_MINIMUM_SIZE,
    ):
        interior_head = ida_bytes.get_item_head(address)
        interior_size = ida_bytes.get_item_size(interior_head)
        interior_name = idc.get_name(address)
        interior_type = _normalize_type_text(idc.get_type(address))
        if (
            interior_head != address
            or interior_size != 1
            or interior_name
            or interior_type is not None
            or not ida_bytes.is_unknown(ida_bytes.get_flags(address))
        ):
            conflicts.append(
                {
                    "address": hex(address),
                    "head": hex(interior_head),
                    "size": interior_size,
                    "name": interior_name,
                    "type": interior_type,
                    "unknown": ida_bytes.is_unknown(
                        ida_bytes.get_flags(address)
                    ),
                }
            )
    if conflicts:
        return {
            "status": "failed",
            "reason": "display_mode_state_minimum_extent_conflict",
            "conflicts": conflicts,
        }

    if not ida_bytes.del_items(
        DISPLAY_MODE_STATE_ADDRESS,
        ida_bytes.DELIT_SIMPLE,
        DISPLAY_MODE_STATE_MINIMUM_SIZE,
    ):
        return {
            "status": "failed",
            "reason": "delete_stale_display_mode_state_extent_failed",
        }
    if not ida_bytes.create_byte(
        DISPLAY_MODE_STATE_ADDRESS,
        DISPLAY_MODE_STATE_MINIMUM_SIZE,
        True,
    ):
        return {
            "status": "failed",
            "reason": "create_display_mode_state_minimum_extent_failed",
        }

    observed_head = ida_bytes.get_item_head(DISPLAY_MODE_STATE_ADDRESS)
    observed_size = ida_bytes.get_item_size(observed_head)
    if (
        observed_head != DISPLAY_MODE_STATE_ADDRESS
        or observed_size != DISPLAY_MODE_STATE_MINIMUM_SIZE
    ):
        return {
            "status": "failed",
            "reason": "display_mode_state_minimum_extent_readback_failed",
            "observed_head": hex(observed_head),
            "observed_size": observed_size,
        }
    return {
        "status": "applied",
        "address": hex(DISPLAY_MODE_STATE_ADDRESS),
        "minimum_size": observed_size,
        "next_known_owner": hex(NEXT_KNOWN_OWNER_ADDRESS),
        "unclaimed_tail_start": hex(
            DISPLAY_MODE_STATE_ADDRESS + DISPLAY_MODE_STATE_MINIMUM_SIZE
        ),
    }


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [
                        {"reason": "noncanonical_display_mode_header"}
                    ],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(
        str(header_path),
        idc.PT_FILE | idc.PT_REPLACE,
    )
    owner_sizes = {
        name: _named_struct_size(name) for name, _size in EXPECTED_STRUCT_SIZES
    }
    failed: list[dict[str, object]] = []
    for name, expected_size in EXPECTED_STRUCT_SIZES:
        observed_size = owner_sizes[name]
        if observed_size != expected_size:
            failed.append(
                {
                    "selector": name,
                    "reason": "owner_size_mismatch",
                    "expected": expected_size,
                    "observed": observed_size,
                }
            )
    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_sizes": owner_sizes,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

    data_extent = _prepare_minimum_owner_extent()
    if data_extent.get("status") == "failed":
        failed.append({"data_extent": data_extent})

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing: list[dict[str, object]] = []
    invalidated: list[dict[str, object]] = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(
            address,
            name,
            ida_name.SN_NOWARN | ida_name.SN_FORCE,
        ):
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "reason": "rename_failed",
                }
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append(
                {"selector": selector, "reason": "missing_function"}
            )
            continue

        expected = _declaration_to_observed_type(selector, declaration)
        current = _normalize_type_text(idc.get_type(address))
        if current == expected:
            unchanged += 1
        elif not idc.SetType(address, declaration):
            failed.append(
                {"selector": selector, "reason": "set_type_failed"}
            )
            continue
        else:
            observed = _normalize_type_text(idc.get_type(address))
            if observed != expected:
                failed.append(
                    {
                        "selector": selector,
                        "reason": "verification_failed",
                        "observed": observed,
                        "expected": expected,
                    }
                )
                continue
            applied += 1

        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append(
            {"selector": selector, "address": hex(address)}
        )

    data_address, data_name, data_declaration = TRUSTED_DATA_DECLARATION
    expected_data_type = _data_declaration_to_observed_type(
        data_name,
        data_declaration,
    )
    current_data_type = _normalize_type_text(idc.get_type(data_address))
    if current_data_type == expected_data_type:
        unchanged += 1
    elif not idc.SetType(data_address, data_declaration):
        failed.append(
            {"selector": data_name, "reason": "set_data_type_failed"}
        )
    else:
        observed_data_type = _normalize_type_text(idc.get_type(data_address))
        if observed_data_type != expected_data_type:
            failed.append(
                {
                    "selector": data_name,
                    "reason": "data_type_verification_failed",
                    "observed": observed_data_type,
                    "expected": expected_data_type,
                }
            )
        else:
            applied += 1

    observed_head = ida_bytes.get_item_head(DISPLAY_MODE_STATE_ADDRESS)
    observed_size = ida_bytes.get_item_size(observed_head)
    if (
        observed_head != DISPLAY_MODE_STATE_ADDRESS
        or observed_size != DISPLAY_MODE_STATE_MINIMUM_SIZE
    ):
        failed.append(
            {
                "selector": data_name,
                "reason": "minimum_extent_verification_failed",
                "observed_head": hex(observed_head),
                "observed_size": observed_size,
            }
        )

    first_unclaimed_address = (
        DISPLAY_MODE_STATE_ADDRESS + DISPLAY_MODE_STATE_MINIMUM_SIZE
    )
    first_unclaimed_head = ida_bytes.get_item_head(first_unclaimed_address)
    if (
        first_unclaimed_head != first_unclaimed_address
        or ida_bytes.get_item_size(first_unclaimed_head) != 1
        or idc.get_name(first_unclaimed_address)
        or idc.get_type(first_unclaimed_address) is not None
    ):
        failed.append(
            {
                "selector": data_name,
                "reason": "unclaimed_tail_boundary_verification_failed",
                "address": hex(first_unclaimed_address),
                "observed_head": hex(first_unclaimed_head),
                "observed_size": ida_bytes.get_item_size(
                    first_unclaimed_head
                ),
                "observed_name": idc.get_name(first_unclaimed_address),
                "observed_type": idc.get_type(first_unclaimed_address),
            }
        )

    sample_lvars = [
        _sync_update_sample_lvar(*spec)
        for spec in UPDATE_SAMPLE_LVAR_SPECS
    ]
    for result in sample_lvars:
        if result.get("status") == "failed":
            failed.append({"sample_lvar": result})

    for selector in DEPENDENT_DECOMPILE_FUNCTIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append(
                {
                    "selector": selector,
                    "reason": "missing_dependent_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append(
            {"selector": selector, "address": hex(address)}
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "data_extent": data_extent,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "sample_lvars": sample_lvars,
                "invalidated": invalidated,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print(
            "usage: apply_display_mode_types.py <header-path>",
            file=sys.stderr,
        )
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
