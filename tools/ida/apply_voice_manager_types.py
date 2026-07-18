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
    (0x448DF0, "initialize_voice_set"),
    (0x448E60, "shuffle_voice_set"),
    (0x448EC0, "reset_voice_manager"),
    (0x448EE0, "initialize_voice_manager"),
    (0x4492A0, "update_voice_manager"),
    (0x4492D0, "play_voice_manager"),
    (0x449360, "update_voice_set"),
    (0x449390, "play_voice_set"),
    (0x449410, "is_voice_playing"),
    (0x751498, "g_voice_manager"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_voice_set",
        "void __thiscall initialize_voice_set(VoiceSet* set, int32_t count);",
    ),
    ("shuffle_voice_set", "void __thiscall shuffle_voice_set(VoiceSet* set);"),
    (
        "reset_voice_manager",
        "void __thiscall reset_voice_manager(VoiceManager* manager);",
    ),
    (
        "initialize_voice_manager",
        "void __thiscall initialize_voice_manager(VoiceManager* manager);",
    ),
    (
        "update_voice_manager",
        "void __thiscall update_voice_manager(VoiceManager* manager);",
    ),
    (
        "play_voice_manager",
        "bool __thiscall play_voice_manager(VoiceManager* manager, int32_t set_id, uint32_t mode, int32_t sample_override);",
    ),
    ("update_voice_set", "void __thiscall update_voice_set(VoiceSet* set);"),
    (
        "play_voice_set",
        "bool __thiscall play_voice_set(VoiceSet* set, int32_t sample_override);",
    ),
    (
        "is_voice_playing",
        "int32_t __thiscall is_voice_playing(VoiceManager* manager);",
    ),
)

TRUSTED_DATA_DECLARATIONS = (
    (0x751498, "g_voice_manager", "VoiceManager g_voice_manager;"),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct VoiceSet {",
    "typedef struct VoiceManager {",
    "VoiceSet sets[16];",
    "extern VoiceManager g_voice_manager;",
)

EXPECTED_OWNER_SIZES = {
    "VoiceSet": 0x18,
    "VoiceManager": 0x188,
}

# Stable native definitions for the inline-bank borrows and the initializer's
# real source variables. Hex-Rays otherwise widens VoiceSet cursors back to the
# enclosing VoiceManager and merges the reused parser stack slots into floats.
VOICE_MANAGER_LVAR_SPECS = (
    (
        "reset_voice_manager",
        0x448ECB,
        None,
        "cooldown_cursor",
        "float *cooldown_cursor;",
    ),
    (
        "initialize_voice_manager",
        0x448EED,
        88,
        "owner",
        "VoiceManager *owner;",
    ),
    (
        "initialize_voice_manager",
        0x448F04,
        80,
        "buffer",
        "char *buffer;",
    ),
    (
        "initialize_voice_manager",
        0x448F0D,
        None,
        "set_index",
        "int32_t set_index;",
    ),
    (
        "initialize_voice_manager",
        0x448F0F,
        84,
        "next_set_index",
        "int32_t next_set_index;",
    ),
    (
        "initialize_voice_manager",
        0x449082,
        None,
        "set",
        "VoiceSet *set;",
    ),
    (
        "update_voice_manager",
        0x4492A6,
        None,
        "set_cursor",
        "VoiceSet *set_cursor;",
    ),
    (
        "is_voice_playing",
        0x449419,
        None,
        "set_cursor",
        "VoiceSet *set_cursor;",
    ),
)

# The compiler intentionally reuses two initializer stack slots after the
# 16-set sweep. Split those later definitions so the archive buffer and loop
# index remain distinct from the three normalization scales.
VOICE_MANAGER_SPLIT_LVAR_SPECS = (
    (
        "initialize_voice_manager",
        80,
        0x448F04,
        0x44915A,
        "music_percent",
        "int32_t music_percent;",
    ),
    (
        "initialize_voice_manager",
        80,
        0x448F04,
        0x449194,
        "sfx_percent",
        "int32_t sfx_percent;",
    ),
    (
        "initialize_voice_manager",
        80,
        0x448F04,
        0x4491E7,
        "voice_scale",
        "float voice_scale;",
    ),
    (
        "initialize_voice_manager",
        84,
        0x448F0F,
        0x4491A8,
        "sfx_scale",
        "float sfx_scale;",
    ),
)

VOICE_MANAGER_DIRTY_FUNCTIONS = tuple(name for _, name in TRUSTED_NAMES[:9])


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


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _parse_local_type(declaration: str) -> ida_typeinf.tinfo_t | None:
    local_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        local_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return None
    return local_type


def _sync_owned_lvar(
    selector: str,
    definition_address: int,
    stack_offset: int | None,
    expected_name: str,
    declaration: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    local_type = _parse_local_type(declaration)
    if local_type is None:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "parse_lvar_type_failed",
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
            "selector": selector,
            "reason": "unexpected_lvar_candidates",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    expected_type = _normalize_type_text(str(local_type))
    if (
        lvar.name == expected_name
        and _normalize_type_text(str(lvar.type())) == expected_type
    ):
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
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "modify_lvar_info_failed",
            "definition_address": hex(definition_address),
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
            "selector": selector,
            "reason": "lvar_readback_failed",
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


def _sync_split_stack_lvar(
    selector: str,
    stack_offset: int,
    source_definition_address: int,
    split_definition_address: int,
    expected_name: str,
    declaration: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    local_type = _parse_local_type(declaration)
    if local_type is None:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "parse_split_lvar_type_failed",
            "declaration": declaration,
        }

    expected_type = _normalize_type_text(str(local_type))
    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    existing = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == stack_offset
        and lvar.defea == split_definition_address
        and lvar.name == expected_name
        and _normalize_type_text(str(lvar.type())) == expected_type
    ]
    if len(existing) == 1:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": existing[0].name,
            "type": str(existing[0].type()),
            "definition_address": hex(existing[0].defea),
        }
    if existing:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_existing_split_lvars",
            "definition_address": hex(split_definition_address),
            "candidate_count": len(existing),
        }

    sources = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == stack_offset
        and lvar.defea == source_definition_address
    ]
    if len(sources) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_split_source_lvars",
            "source_definition_address": hex(source_definition_address),
            "split_definition_address": hex(split_definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(sources),
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(
        sources[0].location,
        split_definition_address,
    )
    info.name = expected_name
    info.type = local_type
    info.set_split_lvar()
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE | ida_hexrays.MLI_SET_FLAGS,
        info,
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "modify_split_lvar_info_failed",
            "definition_address": hex(split_definition_address),
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        lvar
        for lvar in verified_cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.get_stkoff() == stack_offset
        and lvar.defea == split_definition_address
        and lvar.name == expected_name
        and _normalize_type_text(str(lvar.type())) == expected_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "split_lvar_readback_failed",
            "definition_address": hex(split_definition_address),
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
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
                    "failed": [{"reason": "noncanonical_voice_manager_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    failed = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": owner_sizes[name],
        }
        for name, expected_size in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected_size
    ]
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

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []

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
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue

        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "verification_failed",
                    "observed": observed,
                }
            )
            continue
        applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected = _data_declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_data_type_failed"})
            continue

        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "data_verification_failed",
                    "observed": observed,
                }
            )
            continue
        applied += 1

    lvar_updates = [
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
        ) in VOICE_MANAGER_LVAR_SPECS
    ]
    split_lvar_updates = [
        _sync_split_stack_lvar(
            selector,
            stack_offset,
            source_definition_address,
            split_definition_address,
            expected_name,
            declaration,
        )
        for (
            selector,
            stack_offset,
            source_definition_address,
            split_definition_address,
            expected_name,
            declaration,
        ) in VOICE_MANAGER_SPLIT_LVAR_SPECS
    ]
    for lvar_update in (*lvar_updates, *split_lvar_updates):
        if lvar_update.get("status") == "failed":
            failed.append({"lvar_update": lvar_update})

    invalidated = []
    for selector in VOICE_MANAGER_DIRTY_FUNCTIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_dirty_function"})
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        invalidated.append({"selector": selector, "address": hex(address)})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "lvar_updates": lvar_updates,
                "split_lvar_updates": split_lvar_updates,
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
    if len(argv) != 2:
        print("usage: apply_voice_manager_types.py <header-path>", file=sys.stderr)
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
