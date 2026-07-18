from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc


CHEAT_STATE_ADDRESS = 0x4B2F40
CHEAT_STATE_SIZE = 0x10
NEXT_OWNER_ADDRESS = 0x4B2F50

TRUSTED_NAMES = (
    (0x404740, "initialize_cheat"),
    (0x404750, "update_cheat"),
    (0x4047D0, "match_cheat_text"),
    (CHEAT_STATE_ADDRESS, "g_cheat_state"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_cheat",
        "void __thiscall initialize_cheat(CheatState* cheat);",
    ),
    (
        "update_cheat",
        "void __thiscall update_cheat(CheatState* cheat);",
    ),
    (
        "match_cheat_text",
        "bool __thiscall match_cheat_text(CheatState* cheat, char* text);",
    ),
)

TRUSTED_DATA_DECLARATION = (
    CHEAT_STATE_ADDRESS,
    "g_cheat_state",
    "CheatState g_cheat_state;",
)

DEPENDENT_DECOMPILE_FUNCTIONS = (
    "run_frame_update",
    "initialize_game_assets_and_world",
    "complete_subgame",
    "update_subgoldy",
)

REQUIRED_OWNER_MARKERS = (
    "typedef union CheatTextBuffer {",
    "char bytes[8];",
    "typedef struct CheatState {",
    "CheatTextBuffer recent_text;",
    "extern CheatState g_cheat_state;",
)

# Exact non-stack Hex-Rays locals for the two descending borrows into
# CheatState.recent_text.bytes. The definition addresses are stable native
# instruction identities; candidate-count and readback checks prevent a stale
# decompiler layout from being silently applied to a different local.
CURSOR_LVAR_SPECS = (
    ("update_cheat", "recent_text_cursor", "char *recent_text_cursor;", 0x404772),
    (
        "match_cheat_text",
        "recent_text_cursor",
        "char *recent_text_cursor;",
        0x40480A,
    ),
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


def _sync_cursor_lvar(
    selector: str,
    expected_name: str,
    declaration: str,
    definition_address: int,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == definition_address
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_cursor_lvar_candidates",
            "definition_address": hex(definition_address),
            "candidate_count": len(candidates),
        }

    cursor_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(cursor_type, None, declaration, ida_typeinf.PT_SIL):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "parse_cursor_lvar_type_failed",
            "declaration": declaration,
        }

    lvar = candidates[0]
    expected_type = _normalize_type_text(str(cursor_type))
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == expected_name and observed_type == expected_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = expected_name
    info.type = cursor_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "modify_cursor_lvar_failed",
            "definition_address": hex(definition_address),
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and not candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.name == expected_name
        and _normalize_type_text(str(candidate.type())) == expected_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "cursor_lvar_readback_failed",
            "definition_address": hex(definition_address),
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": before_name,
        "before_type": before_type,
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
    }


def _prepare_cheat_state_extent() -> dict[str, object]:
    if NEXT_OWNER_ADDRESS - CHEAT_STATE_ADDRESS != CHEAT_STATE_SIZE:
        return {
            "status": "failed",
            "reason": "invalid_checked_in_owner_boundary",
        }

    item_head = ida_bytes.get_item_head(CHEAT_STATE_ADDRESS)
    item_size = ida_bytes.get_item_size(item_head)
    if item_head == CHEAT_STATE_ADDRESS and item_size == CHEAT_STATE_SIZE:
        return {
            "status": "unchanged",
            "address": hex(CHEAT_STATE_ADDRESS),
            "item_size": item_size,
            "next_owner": hex(NEXT_OWNER_ADDRESS),
        }

    if item_head != CHEAT_STATE_ADDRESS or item_size not in (1, 4):
        return {
            "status": "failed",
            "reason": "unexpected_cheat_state_extent_head",
            "observed_head": hex(item_head),
            "observed_size": item_size,
        }

    interior_names = {
        hex(address): idc.get_name(address)
        for address in range(CHEAT_STATE_ADDRESS + 1, NEXT_OWNER_ADDRESS)
        if idc.get_name(address)
    }
    non_auto_names = {
        address: name
        for address, name in interior_names.items()
        if not re.fullmatch(r"(?:byte|word|dword|qword|unk)_[0-9A-Fa-f]+", name)
    }
    if non_auto_names:
        return {
            "status": "failed",
            "reason": "named_interior_owner_conflict",
            "interior_names": non_auto_names,
        }

    if not ida_bytes.del_items(
        CHEAT_STATE_ADDRESS,
        ida_bytes.DELIT_SIMPLE,
        CHEAT_STATE_SIZE,
    ):
        return {
            "status": "failed",
            "reason": "delete_stale_cheat_state_extent_failed",
        }
    if not ida_bytes.create_byte(CHEAT_STATE_ADDRESS, CHEAT_STATE_SIZE, True):
        return {
            "status": "failed",
            "reason": "create_cheat_state_extent_failed",
        }

    observed_head = ida_bytes.get_item_head(CHEAT_STATE_ADDRESS)
    observed_size = ida_bytes.get_item_size(observed_head)
    if observed_head != CHEAT_STATE_ADDRESS or observed_size != CHEAT_STATE_SIZE:
        return {
            "status": "failed",
            "reason": "cheat_state_extent_readback_failed",
            "observed_head": hex(observed_head),
            "observed_size": observed_size,
        }
    return {
        "status": "applied",
        "address": hex(CHEAT_STATE_ADDRESS),
        "item_size": observed_size,
        "next_owner": hex(NEXT_OWNER_ADDRESS),
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
                    "failed": [{"reason": "noncanonical_cheat_state_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
    observed_owner_size = _named_struct_size("CheatState")
    failed: list[dict[str, object]] = []
    if observed_owner_size != CHEAT_STATE_SIZE:
        failed.append(
            {
                "selector": "CheatState",
                "reason": "owner_size_mismatch",
                "expected": CHEAT_STATE_SIZE,
                "observed": observed_owner_size,
            }
        )
    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_size": observed_owner_size,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

    data_extent = _prepare_cheat_state_extent()
    if data_extent.get("status") == "failed":
        failed.append({"data_extent": data_extent})

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing: list[dict[str, object]] = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"selector": name, "address": hex(address), "reason": "rename_failed"}
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_function"})
            continue

        expected = _declaration_to_observed_type(selector, declaration)
        current = _normalize_type_text(idc.get_type(address))
        if current == expected:
            unchanged += 1
        elif not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue
        elif _normalize_type_text(idc.get_type(address)) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "verification_failed",
                    "expected": expected,
                    "observed": idc.get_type(address),
                }
            )
            continue
        else:
            applied += 1

        ida_hexrays.mark_cfunc_dirty(address, True)

    data_address, data_selector, data_declaration = TRUSTED_DATA_DECLARATION
    expected_data_type = _data_declaration_to_observed_type(
        data_selector,
        data_declaration,
    )
    current_data_type = _normalize_type_text(idc.get_type(data_address))
    if current_data_type == expected_data_type:
        unchanged += 1
    elif not idc.SetType(data_address, data_declaration):
        failed.append({"selector": data_selector, "reason": "set_data_type_failed"})
    elif _normalize_type_text(idc.get_type(data_address)) != expected_data_type:
        failed.append(
            {
                "selector": data_selector,
                "reason": "data_verification_failed",
                "expected": expected_data_type,
                "observed": idc.get_type(data_address),
            }
        )
    else:
        applied += 1

    cursor_lvars = [
        _sync_cursor_lvar(selector, expected_name, declaration, definition_address)
        for selector, expected_name, declaration, definition_address in CURSOR_LVAR_SPECS
    ]
    for cursor_lvar in cursor_lvars:
        if cursor_lvar.get("status") == "failed":
            failed.append({"cursor_lvar": cursor_lvar})

    invalidated = []
    for selector in DEPENDENT_DECOMPILE_FUNCTIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_dependent_function"})
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append({"selector": selector, "address": hex(address)})

    verified_head = ida_bytes.get_item_head(CHEAT_STATE_ADDRESS)
    verified_size = ida_bytes.get_item_size(verified_head)
    if verified_head != CHEAT_STATE_ADDRESS or verified_size != CHEAT_STATE_SIZE:
        failed.append(
            {
                "selector": "g_cheat_state",
                "reason": "final_data_extent_verification_failed",
                "observed_head": hex(verified_head),
                "observed_size": verified_size,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_size": observed_owner_size,
                "data_extent": data_extent,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "invalidated": invalidated,
                "cursor_lvars": cursor_lvars,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_cheat_state_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
