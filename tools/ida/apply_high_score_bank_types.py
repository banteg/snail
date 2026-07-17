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


TRUSTED_DECLARATIONS = [
    (
        "initialize_high_score_tables",
        "void __thiscall initialize_high_score_tables(SubHighScore* bank);",
    ),
    (
        "load_high_scores_from_file",
        "void __thiscall load_high_scores_from_file(SubHighScore* bank, char* file_name);",
    ),
    (
        "initialize_high_score_entry",
        "void __thiscall initialize_high_score_entry(SubSolution* record, int runtime_build_seed, int replay_level_index, int replay_speed_scalar_bits, unsigned int runtime_build_flags, int high_score_mode_tag, int route_or_rank_index);",
    ),
    (
        "add_arcade_high_score",
        "void __thiscall add_arcade_high_score(SubHighScore* bank, SubSolution* record, int level_arg);",
    ),
    (
        "add_survival_high_score",
        "void __thiscall add_survival_high_score(SubHighScore* bank, SubSolution* record);",
    ),
    (
        "add_time_trial_high_score",
        "void __thiscall add_time_trial_high_score(SubHighScore* bank, SubSolution* record, int route_index, unsigned char route_active);",
    ),
    (
        "mini_delete_high_score_entry",
        "void __thiscall mini_delete_high_score_entry(SubHighScore* bank, int rank);",
    ),
    (
        "save_high_scores_and_config",
        "void __thiscall save_high_scores_and_config(SubHighScore* bank, unsigned char save_mask);",
    ),
    (
        "deserialize_compact_high_score_record",
        "unsigned char __thiscall deserialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
    ),
    (
        "serialize_compact_high_score_record",
        "int __thiscall serialize_compact_high_score_record(SubSolution* record, CompactHighScoreRecord* compact);",
    ),
]

TRUSTED_NAMES = [
    (0x417AF0, "mini_delete_high_score_entry"),
    (0x4DF904, "g_game_base"),
]

# 0x4DF9C0 is the selected-bank lane at g_runtime_config + 0xA8, inside
# IDA's existing aggregate data item. The reference manifest carries its
# field alias; idc.set_name cannot create a standalone name at that interior
# address.


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
    normalized = normalized.replace("unsigned __int8", "unsigned char")
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


def _normalize_struct_pointer_type(value: str) -> str:
    return (_normalize_type_text(value) or "").removeprefix("struct ")


def _sync_named_pointer_lvar(
    *,
    selector: str,
    definition_address: int,
    accepted_names: set[str],
    accepted_types: set[str],
    target_name: str,
    target_struct_name: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and _normalize_struct_pointer_type(str(lvar.type())) in accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_pointer_lvar_candidates",
            "candidate_count": len(candidates),
            "definition_address": hex(definition_address),
            "selector": selector,
            "target_name": target_name,
        }

    lvar = candidates[0]
    target_pointer_type = f"{target_struct_name} *"
    observed_type = _normalize_struct_pointer_type(str(lvar.type()))
    if lvar.name == target_name and observed_type == target_pointer_type:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "selector": selector,
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_struct_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_target_struct_type",
            "target_struct_name": target_struct_name,
            "selector": selector,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(target_type):
        return {
            "status": "failed",
            "reason": "create_target_struct_pointer_failed",
            "target_struct_name": target_struct_name,
            "selector": selector,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = pointer_type
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
        if not candidate.is_arg_var
        and candidate.defea == definition_address
        and candidate.name == target_name
    ]
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "pointer_lvar_readback_failed",
            "candidate_count": len(verified_candidates),
            "selector": selector,
            "target_name": target_name,
        }

    verified = verified_candidates[0]
    verified_type = _normalize_struct_pointer_type(str(verified.type()))
    if verified_type != target_pointer_type:
        return {
            "status": "failed",
            "reason": "pointer_lvar_type_readback_failed",
            "observed_type": str(verified.type()),
            "target_type": target_pointer_type,
            "selector": selector,
        }

    return {
        "status": "applied",
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified.name,
        "type": str(verified.type()),
        "definition_address": hex(verified.defea),
        "selector": selector,
    }


def _sync_named_lvar(
    *,
    selector: str,
    definition_address: int,
    accepted_names: set[str],
    accepted_types: set[str],
    target_name: str,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and (_normalize_type_text(str(lvar.type())) or "") in accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_named_lvar_candidates",
            "candidate_count": len(candidates),
            "definition_address": hex(definition_address),
            "selector": selector,
            "target_name": target_name,
        }

    lvar = candidates[0]
    if lvar.name == target_name:
        return {
            "status": "unchanged",
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "selector": selector,
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    if not ida_hexrays.modify_user_lvar_info(address, ida_hexrays.MLI_NAME, info):
        return {
            "status": "failed",
            "reason": "modify_named_lvar_info_failed",
            "selector": selector,
            "target_name": target_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified_candidates = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.defea == definition_address
        and candidate.name == target_name
        and (_normalize_type_text(str(candidate.type())) or "") in accepted_types
    ]
    if len(verified_candidates) != 1:
        return {
            "status": "failed",
            "reason": "named_lvar_readback_failed",
            "candidate_count": len(verified_candidates),
            "definition_address": hex(definition_address),
            "selector": selector,
            "target_name": target_name,
        }

    verified = verified_candidates[0]
    return {
        "status": "applied",
        "before_name": before_name,
        "before_type": before_type,
        "name": verified.name,
        "type": str(verified.type()),
        "definition_address": hex(verified.defea),
        "selector": selector,
    }


def _sync_high_score_screen_active_bank_operands() -> dict[str, object]:
    selector = "initialize_high_score_screen"
    function_address = 0x416910
    operand_specs = (
        (0x416A33, 0, 0x6FFAE0, "89 90 e0 fa 6f 00"),
        (0x416A3E, 0, 0x6FFAE4, "c7 80 e4 fa 6f 00 0a 00 00 00"),
        (0x416A89, 1, 0x6FFAE8, "8d 88 e8 fa 6f 00"),
        (0x416A8F, 0, 0x6FFAE0, "89 88 e0 fa 6f 00"),
        (0x416A9B, 0, 0x6FFAE4, "c7 82 e4 fa 6f 00 0a 00 00 00"),
        (0x416B00, 1, 0x6FFAE0, "8b 91 e0 fa 6f 00"),
        (0x416C3A, 1, 0x6FFAE0, "8b 91 e0 fa 6f 00"),
        (0x416CE2, 1, 0x6FFAE0, "8b 82 e0 fa 6f 00"),
        (0x416E87, 1, 0x6FFAE0, "8b 88 e0 fa 6f 00"),
        (0x416F2C, 1, 0x6FFAE0, "8b 91 e0 fa 6f 00"),
    )

    entries = []
    changed_count = 0
    for operand_address, operand_index, expected_offset, expected_hex in operand_specs:
        expected_bytes = bytes.fromhex(expected_hex)
        observed_bytes = ida_bytes.get_bytes(operand_address, len(expected_bytes))
        if observed_bytes != expected_bytes:
            return {
                "status": "failed",
                "reason": "unexpected_high_score_screen_operand_instruction",
                "address": hex(operand_address),
                "observed_bytes": (
                    None if observed_bytes is None else observed_bytes.hex()
                ),
                "selector": selector,
            }

        before_disassembly = idc.generate_disasm_line(operand_address, 0)
        before_operand = idc.print_operand(operand_address, operand_index)
        idc.op_num(operand_address, operand_index)
        after_operand = idc.print_operand(operand_address, operand_index)
        observed_offset = idc.get_operand_value(operand_address, operand_index)
        if (
            observed_offset != expected_offset
            or f"{expected_offset:X}H" not in after_operand.upper()
        ):
            return {
                "status": "failed",
                "reason": "high_score_screen_operand_readback_failed",
                "address": hex(operand_address),
                "operand_index": operand_index,
                "expected_offset": hex(expected_offset),
                "observed_offset": hex(observed_offset),
                "before_operand": before_operand,
                "after_operand": after_operand,
                "selector": selector,
            }

        changed = before_operand != after_operand
        changed_count += int(changed)
        entries.append(
            {
                "address": hex(operand_address),
                "operand_index": operand_index,
                "expected_offset": hex(expected_offset),
                "before_disassembly": before_disassembly,
                "disassembly": idc.generate_disasm_line(operand_address, 0),
                "before_operand": before_operand,
                "after_operand": after_operand,
                "changed": changed,
            }
        )

    ida_hexrays.mark_cfunc_dirty(function_address, True)
    pseudocode = str(ida_hexrays.decompile(function_address))
    required_owners = (
        "g_game_base->subgame.sub_high_score.active_record_bank",
        "g_game_base->subgame.sub_high_score.active_record_count",
        "g_game_base->subgame.sub_high_score.postal_records",
    )
    missing_owners = [owner for owner in required_owners if owner not in pseudocode]
    forbidden_names = [
        name
        for name in ("byte_6FFAE0", "unk_6FFAE4", "g_parcel_set_buckets")
        if name in pseudocode
    ]
    if missing_owners or forbidden_names:
        return {
            "status": "failed",
            "reason": "high_score_screen_owner_readback_failed",
            "missing_owners": missing_owners,
            "forbidden_names": forbidden_names,
            "selector": selector,
        }

    return {
        "status": "applied" if changed_count else "unchanged",
        "changed_count": changed_count,
        "entries": entries,
        "selector": selector,
    }


def _sync_high_score_screen_loop_lvars() -> dict[str, dict[str, object]]:
    selector = "initialize_high_score_screen"
    scalar_types = {"int", "int32_t"}
    return {
        "row": _sync_named_lvar(
            selector=selector,
            definition_address=0x416AD4,
            accepted_names={"v8", "row"},
            accepted_types=scalar_types,
            target_name="row",
        ),
        "record_offset_bytes": _sync_named_lvar(
            selector=selector,
            definition_address=0x416AD6,
            accepted_names={"v9", "record_offset_bytes"},
            accepted_types=scalar_types,
            target_name="record_offset_bytes",
        ),
        "name_widget_cursor": _sync_named_lvar(
            selector=selector,
            definition_address=0x416AE1,
            accepted_names={"name_row_widgets", "name_widget_cursor"},
            accepted_types={"FrontendWidget * *"},
            target_name="name_widget_cursor",
        ),
        "saved_row": _sync_named_lvar(
            selector=selector,
            definition_address=0x416AD9,
            accepted_names={"v35", "saved_row"},
            accepted_types=scalar_types,
            target_name="saved_row",
        ),
        "record_index": _sync_named_lvar(
            selector=selector,
            definition_address=0x416ADD,
            accepted_names={"v36", "saved_record_offset_bytes", "record_index"},
            accepted_types=scalar_types,
            target_name="record_index",
        ),
    }


def _sync_load_compact_cursor_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="load_high_scores_from_file",
        definition_address=0x417608,
        accepted_names={"file_bytes", "compact"},
        accepted_types={"char *", "CompactHighScoreRecord *"},
        target_name="compact",
        target_struct_name="CompactHighScoreRecord",
    )


def _sync_add_arcade_rank_cursor_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="add_arcade_high_score",
        definition_address=0x417731,
        accepted_names={"v9", "postal_rank_cursor"},
        accepted_types={"char *", "SubHighScorePostalRankCursor *"},
        target_name="postal_rank_cursor",
        target_struct_name="SubHighScorePostalRankCursor",
    )


def _sync_add_survival_rank_cursor_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="add_survival_high_score",
        definition_address=0x417829,
        accepted_names={"v8", "survival_rank_cursor"},
        accepted_types={"SubSolution * *", "SubHighScoreSurvivalRankCursor *"},
        target_name="survival_rank_cursor",
        target_struct_name="SubHighScoreSurvivalRankCursor",
    )


def _sync_survival_active_bank_operand() -> dict[str, object]:
    selector = "add_survival_high_score"
    function_address = 0x417780
    store_address = 0x41787C
    expected_bytes = bytes.fromhex("89 aa e0 fa 6f 00")
    expected_owner = "g_game_base->subgame.sub_high_score.active_record_bank"

    observed_bytes = ida_bytes.get_bytes(store_address, len(expected_bytes))
    if observed_bytes != expected_bytes:
        return {
            "status": "failed",
            "reason": "unexpected_active_bank_store_instruction",
            "address": hex(store_address),
            "observed_bytes": None if observed_bytes is None else observed_bytes.hex(),
            "selector": selector,
        }

    before_disassembly = idc.generate_disasm_line(store_address, 0)
    was_offset = bool(ida_bytes.is_off0(ida_bytes.get_full_flags(store_address)))
    if was_offset and not idc.op_num(store_address, 0):
        return {
            "status": "failed",
            "reason": "clear_false_active_bank_offset_failed",
            "address": hex(store_address),
            "selector": selector,
        }

    if ida_bytes.is_off0(ida_bytes.get_full_flags(store_address)):
        return {
            "status": "failed",
            "reason": "active_bank_operand_readback_failed",
            "address": hex(store_address),
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(function_address, True)
    pseudocode = str(ida_hexrays.decompile(function_address))
    if expected_owner not in pseudocode or "byte_6FFAE0" in pseudocode:
        return {
            "status": "failed",
            "reason": "active_bank_owner_readback_failed",
            "address": hex(store_address),
            "expected_owner": expected_owner,
            "selector": selector,
        }

    return {
        "status": "applied" if was_offset else "unchanged",
        "address": hex(store_address),
        "before_disassembly": before_disassembly,
        "disassembly": idc.generate_disasm_line(store_address, 0),
        "owner": expected_owner,
        "selector": selector,
    }


def _sync_add_time_trial_route_cursor_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="add_time_trial_high_score",
        definition_address=0x417902,
        accepted_names={"v4", "time_trial_route_cursor"},
        accepted_types={"char *", "SubHighScoreTimeTrialRouteCursor *"},
        target_name="time_trial_route_cursor",
        target_struct_name="SubHighScoreTimeTrialRouteCursor",
    )


def _sync_mini_delete_source_cursor_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="mini_delete_high_score_entry",
        definition_address=0x417B16,
        accepted_names={"v4", "source_cursor"},
        accepted_types={"SubSolution *"},
        target_name="source_cursor",
        target_struct_name="SubSolution",
    )


def _sync_mini_delete_destination_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="mini_delete_high_score_entry",
        definition_address=0x417B24,
        accepted_names={"v5", "destination"},
        accepted_types={"SubSolution *"},
        target_name="destination",
        target_struct_name="SubSolution",
    )


def _sync_mini_delete_source_lvar() -> dict[str, object]:
    return _sync_named_pointer_lvar(
        selector="mini_delete_high_score_entry",
        definition_address=0x417B26,
        accepted_names={"v6", "source"},
        accepted_types={"SubSolution *"},
        target_name="source",
        target_struct_name="SubSolution",
    )


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        current_name = idc.get_name(address)
        if current_name == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            existing_name_address = idc.get_name_ea_simple(name)
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "current_name": current_name,
                    "existing_name_address": (
                        None
                        if existing_name_address == idc.BADADDR
                        else hex(existing_name_address)
                    ),
                    "reason": "rename_failed",
                }
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

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

    high_score_screen_active_bank_operands = (
        _sync_high_score_screen_active_bank_operands()
    )
    if high_score_screen_active_bank_operands.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_high_score_screen",
                "active_bank_operands": high_score_screen_active_bank_operands,
            }
        )

    high_score_screen_loop_lvars = _sync_high_score_screen_loop_lvars()
    for lvar_name, lvar_result in high_score_screen_loop_lvars.items():
        if lvar_result.get("status") == "failed":
            failed.append(
                {
                    "selector": "initialize_high_score_screen",
                    lvar_name: lvar_result,
                }
            )

    compact_cursor_lvar = _sync_load_compact_cursor_lvar()
    if compact_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "load_high_scores_from_file",
                "compact_cursor_lvar": compact_cursor_lvar,
            }
        )

    postal_rank_cursor_lvar = _sync_add_arcade_rank_cursor_lvar()
    if postal_rank_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "add_arcade_high_score",
                "postal_rank_cursor_lvar": postal_rank_cursor_lvar,
            }
        )

    survival_rank_cursor_lvar = _sync_add_survival_rank_cursor_lvar()
    if survival_rank_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "add_survival_high_score",
                "survival_rank_cursor_lvar": survival_rank_cursor_lvar,
            }
        )

    survival_active_bank_operand = _sync_survival_active_bank_operand()
    if survival_active_bank_operand.get("status") == "failed":
        failed.append(
            {
                "selector": "add_survival_high_score",
                "survival_active_bank_operand": survival_active_bank_operand,
            }
        )

    time_trial_route_cursor_lvar = _sync_add_time_trial_route_cursor_lvar()
    if time_trial_route_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "add_time_trial_high_score",
                "time_trial_route_cursor_lvar": time_trial_route_cursor_lvar,
            }
        )

    mini_delete_cursor_lvars = {
        "source_cursor": _sync_mini_delete_source_cursor_lvar(),
        "destination": _sync_mini_delete_destination_lvar(),
        "source": _sync_mini_delete_source_lvar(),
    }
    for cursor_name, cursor_lvar in mini_delete_cursor_lvars.items():
        if cursor_lvar.get("status") == "failed":
            failed.append(
                {
                    "selector": "mini_delete_high_score_entry",
                    cursor_name: cursor_lvar,
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
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "high_score_screen_active_bank_operands": (
                    high_score_screen_active_bank_operands
                ),
                "high_score_screen_loop_lvars": high_score_screen_loop_lvars,
                "compact_cursor_lvar": compact_cursor_lvar,
                "postal_rank_cursor_lvar": postal_rank_cursor_lvar,
                "survival_rank_cursor_lvar": survival_rank_cursor_lvar,
                "survival_active_bank_operand": survival_active_bank_operand,
                "time_trial_route_cursor_lvar": time_trial_route_cursor_lvar,
                "mini_delete_cursor_lvars": mini_delete_cursor_lvars,
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
    if len(argv) < 2:
        print("usage: apply_high_score_bank_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
