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

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402
from type_alias_migration import migrate_equivalent_struct_aliases  # noqa: E402

TRUSTED_FUNCTIONS = (
    (
        0x404830,
        "flush_row_event_display",
        "void __thiscall flush_row_event_display(cRCompletion* completion);",
    ),
    (
        0x404920,
        "initialize_completion_screen",
        "void __thiscall initialize_completion_screen(cRCompletion* completion, int32_t delivered_count, uint8_t perfect_delivery);",
    ),
    (
        0x404CF0,
        "update_row_event_display",
        "void __thiscall update_row_event_display(cRCompletion* completion);",
    ),
    (
        0x405040,
        "register_parcel_delivery",
        "void __thiscall register_parcel_delivery(cRCompletion* completion);",
    ),
)

EXPECTED_OWNER_SIZES = {
    "cRCompletion": 0x50,
    "SubSolution": 0x1FAC0,
    "cRSubGame": 0x1272838,
}

REQUIRED_OWNER_MARKERS = (
    "typedef struct cRCompletion {",
    "CompletionState state;",
    "Vec3 widget_world;",
    "cRCompletion_must_be_0x50",
)

OWNER_TYPE_ALIASES = (("Completion", "cRCompletion", 0x50),)

EXPECTED_OWNER_LAYOUT = {
    "size": 0x50,
    "members": {
        0x00: (0x04, "title_widget", "FrontendWidget *"),
        0x04: (0x04, "delivered_count_widget", "FrontendWidget *"),
        0x08: (0x04, "bonus_summary_widget", "FrontendWidget *"),
        0x0C: (0x04, "bonus_icon_widget", "FrontendWidget *"),
        0x10: (0x04, "continue_widget", "FrontendWidget *"),
        0x14: (0x04, "state", "CompletionState"),
        0x18: (0x01, "fast_forward_enabled", "uint8_t"),
        0x19: (0x03, "_pad_19", "uint8_t[3]"),
        0x1C: (0x04, "parcel_target_count", "int32_t"),
        0x20: (0x04, "bonus_enabled", "int32_t"),
        0x24: (0x04, "staged_parcel_count", "int32_t"),
        0x28: (0x04, "delivered_parcel_count", "int32_t"),
        0x2C: (0x04, "progress", "float"),
        0x30: (0x04, "progress_step", "float"),
        0x34: (0x0C, "widget_world", "Vec3"),
        0x40: (0x04, "bonus_blink_progress", "float"),
        0x44: (0x04, "bonus_blink_step", "float"),
        0x48: (0x04, "bonus_score", "int32_t"),
        0x4C: (0x04, "display_token", "int32_t"),
    },
}

EXPECTED_OWNER_EDGES = {
    "previous_enemy_manager": {
        "struct": "cRSubGame",
        "offset": 0x1270FD4,
        "expected": {
            "offset": "0x1270fd4",
            "size": 0x1804,
            "name": "enemy_manager",
            "type": "EnemyManager",
        },
    },
    "subgame_embed": {
        "struct": "cRSubGame",
        "offset": 0x12727D8,
        "expected": {
            "offset": "0x12727d8",
            "size": 0x50,
            "name": "completion",
            "type": "cRCompletion",
        },
    },
    "following_times_up": {
        "struct": "cRSubGame",
        "offset": 0x1272828,
        "expected": {
            "offset": "0x1272828",
            "size": 0x10,
            "name": "times_up",
            "type": "cRTimesUp",
        },
    },
}

INITIALIZER_COLOR_SELECTOR = "initialize_completion_screen"
INITIALIZER_COLOR_DEFINITION_ADDRESS = 0x404A5F
INITIALIZER_COLOR_STACK_OFFSET = 48
INITIALIZER_COLOR_NAME = "color"
INITIALIZER_COLOR_ACCEPTED_TYPES = ("Color4f", "tColour")


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\b(?:struct|union|enum)\s+", "", normalized)
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


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _normalize_udt_type(value: str) -> str:
    normalized = _normalize_type_text(value) or ""
    return re.sub(r"\b(?:struct|class|union|enum)\s+", "", normalized)


def _named_struct_members(name: str) -> list[dict[str, object]] | None:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None
    return [
        {
            "offset": hex(int(member.offset) // 8),
            "size": int(member.size) // 8,
            "name": member.name,
            "type": _normalize_udt_type(member.type.dstr()),
        }
        for member in members
    ]


def _named_struct_member_readback(
    struct_name: str, offset: int
) -> dict[str, object] | None:
    members = _named_struct_members(struct_name)
    if members is None:
        return None
    expected_offset = hex(offset)
    return next(
        (member for member in members if member["offset"] == expected_offset),
        None,
    )


def _owner_layout_readback() -> dict[str, object]:
    observed_size = _named_struct_size("cRCompletion")
    observed_members = {
        hex(offset): _named_struct_member_readback("cRCompletion", offset)
        for offset in EXPECTED_OWNER_LAYOUT["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != EXPECTED_OWNER_LAYOUT["size"]:
        failures.append(
            {
                "selector": "cRCompletion",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_OWNER_LAYOUT["size"],
                "observed": observed_size,
            }
        )
    for offset, (size, name, type_text) in EXPECTED_OWNER_LAYOUT["members"].items():
        expected_member = {
            "offset": hex(offset),
            "size": size,
            "name": name,
            "type": _normalize_udt_type(type_text),
        }
        observed_member = observed_members[hex(offset)]
        if observed_member != expected_member:
            failures.append(
                {
                    "selector": f"cRCompletion.{name}",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )

    edges = {}
    for edge_name, edge in EXPECTED_OWNER_EDGES.items():
        observed = _named_struct_member_readback(edge["struct"], edge["offset"])
        edges[edge_name] = observed
        if observed != edge["expected"]:
            failures.append(
                {
                    "selector": f"{edge['struct']}.{edge_name}",
                    "reason": "owner_edge_mismatch",
                    "expected": edge["expected"],
                    "observed": observed,
                }
            )

    return {
        "type": "cRCompletion",
        "size": observed_size,
        "members": observed_members,
        "edges": edges,
        "failures": failures,
    }


def _sync_initializer_color_lvar() -> dict[str, object]:
    selector = INITIALIZER_COLOR_SELECTOR
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func_start(address) == idc.BADADDR:
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    definition_address = INITIALIZER_COLOR_DEFINITION_ADDRESS
    stack_offset = INITIALIZER_COLOR_STACK_OFFSET
    expected_name = INITIALIZER_COLOR_NAME
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.get_stkoff() == stack_offset
        and lvar.name == expected_name
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_color_lvar_candidates",
            "definition_address": hex(definition_address),
            "stack_offset": stack_offset,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    before_type = _normalize_type_text(str(lvar.type())) or ""
    accepted_types = {
        _normalize_type_text(str(value)) or ""
        for value in INITIALIZER_COLOR_ACCEPTED_TYPES
    }
    if before_type not in accepted_types:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_color_lvar_type",
            "observed": str(lvar.type()),
            "accepted": sorted(accepted_types),
        }
    if before_type == "tColour":
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "stack_offset": lvar.get_stkoff(),
        }

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(None, "tColour", ida_typeinf.BTF_STRUCT):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "missing_tColour_type",
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.type = local_type
    if not ida_hexrays.modify_user_lvar_info(address, ida_hexrays.MLI_TYPE, info):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "modify_color_lvar_failed",
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
        and _normalize_type_text(str(candidate.type())) == "tColour"
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "color_lvar_readback_failed",
            "candidate_count": len(verified),
        }
    return {
        "status": "applied",
        "selector": selector,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
        "stack_offset": verified[0].get_stkoff(),
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
                    "failed": [{"reason": "noncanonical_completion_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
    owner_type_alias_migrations = (
        [] if parse_errors else migrate_equivalent_struct_aliases(OWNER_TYPE_ALIASES)
    )
    owner_type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in owner_type_alias_migrations
        if result.get("status") == "failed"
    ]
    owner_sizes = {
        name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES
    }
    size_mismatches = {
        name: {"expected": expected, "observed": owner_sizes[name]}
        for name, expected in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected
    }
    owner_layout_readback = (
        {
            "type": "cRCompletion",
            "size": None,
            "members": {},
            "edges": {},
            "failures": [],
        }
        if parse_errors or owner_type_alias_failures
        else _owner_layout_readback()
    )

    applied = 0
    unchanged = 0
    missing = []
    failed = [*owner_type_alias_failures, *owner_layout_readback["failures"]]
    resolved_functions = []

    if size_mismatches:
        failed.append(
            {
                "selector": "cRCompletion",
                "reason": "owner_size_mismatch",
                "types": size_mismatches,
            }
        )

    if not parse_errors and not size_mismatches and not failed:
        for address, selector, declaration in TRUSTED_FUNCTIONS:
            function_start = ida_funcs.get_func_start(address)
            if function_start == idc.BADADDR:
                missing.append(
                    {
                        "selector": selector,
                        "address": hex(address),
                        "reason": "missing_function",
                    }
                )
                continue

            observed_name = idc.get_func_name(function_start)
            if observed_name != selector:
                failed.append(
                    {
                        "selector": selector,
                        "address": hex(address),
                        "observed_name": observed_name,
                        "reason": "unexpected_function_name",
                    }
                )
                continue

            resolved_functions.append((function_start, selector))
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

    if parse_errors or size_mismatches or failed or missing:
        game_root_owner_graph = {
            "status": "skipped",
            "reason": "completion_owner_validation_failed",
        }
        initializer_color_lvar = {
            "status": "skipped",
            "reason": "completion_owner_validation_failed",
        }
    else:
        game_root_owner_graph = sync_game_root_owner_graph(require=True)
        if game_root_owner_graph.get("status") == "failed":
            failed.append(
                {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
            )

        initializer_color_lvar = _sync_initializer_color_lvar()
        if initializer_color_lvar.get("status") == "applied":
            applied += 1
        elif initializer_color_lvar.get("status") == "unchanged":
            unchanged += 1
        else:
            failed.append(
                {
                    "selector": "initialize_completion_screen",
                    "lvar": "color",
                    "result": initializer_color_lvar,
                }
            )

    reanalyzed = []
    for address, selector in resolved_functions:
        ida_hexrays.mark_cfunc_dirty(address, True)
        reanalyzed.append({"address": hex(address), "name": selector})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_type_alias_migrations": owner_type_alias_migrations,
                "owner_sizes": owner_sizes,
                "owner_layout_readback": owner_layout_readback,
                "applied": applied,
                "unchanged": unchanged,
                "reanalyzed": reanalyzed,
                "game_root_owner_graph": game_root_owner_graph,
                "initializer_color_lvar": initializer_color_lvar,
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
        print("usage: apply_completion_screen_types.py <header-path>", file=sys.stderr)
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
