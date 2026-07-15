from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_pro
import ida_typeinf
import idc


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
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    missing = []
    failed = []

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

    grid_offset_lvar = _sync_builtin_grid_offset_lvar()
    if grid_offset_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "load_builtin_segment_definitions",
                "grid_offset_lvar": grid_offset_lvar,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "grid_offset_lvar": grid_offset_lvar,
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
