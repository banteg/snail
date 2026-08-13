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
from type_alias_migration import migrate_equivalent_struct_aliases

TRUSTED_DECLARATIONS = (
    (
        "initialize_click_start_controller_runtime",
        "cRClickStart* __thiscall initialize_click_start_controller_runtime(cRClickStart* click_start);",
    ),
    (
        "initialize_click_start",
        "void __thiscall initialize_click_start(cRClickStart* click_start, Player* player);",
    ),
    (
        "update_click_start",
        "void __thiscall update_click_start(cRClickStart* click_start);",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct cRClickStart {",
    "RenderableBod bod;",
    "ClickStartState state;",
    "cRClickStart_must_be_0xac",
)

OWNER_TYPE_ALIASES = (("ClickStart", "cRClickStart", 0xAC),)

EXPECTED_PLAYER_SIZE = 0x4364

EXPECTED_OWNER_LAYOUT = {
    "size": 0xAC,
    "members": {
        0x00: (0x80, "bod", "RenderableBod"),
        0x80: (0x04, "state", "ClickStartState"),
        0x84: (0x04, "prompt", "FrontendWidget *"),
        0x88: (0x04, "teardown_progress", "float"),
        0x8C: (0x04, "teardown_progress_step", "float"),
        0x90: (0x08, "_pad_90", "uint8_t[8]"),
        0x98: (0x04, "owner_player", "Player *"),
        0x9C: (0x0C, "_pad_9c", "uint8_t[12]"),
        0xA8: (0x01, "hide_prompt", "uint8_t"),
        0xA9: (0x03, "_pad_a9", "uint8_t[3]"),
    },
}

EXPECTED_OWNER_EDGES = {
    "previous_ghost_sprite": {
        "struct": "Player",
        "offset": 0x9C,
        "expected": {
            "offset": "0x9c",
            "size": 0x04,
            "name": "ghost_sprite_b",
            "type": "Sprite *",
        },
    },
    "player_embed": {
        "struct": "Player",
        "offset": 0xA0,
        "expected": {
            "offset": "0xa0",
            "size": 0xAC,
            "name": "click_start",
            "type": "cRClickStart",
        },
    },
    "following_cutscene_flag": {
        "struct": "Player",
        "offset": 0x14C,
        "expected": {
            "offset": "0x14c",
            "size": 0x01,
            "name": "row_event_cutscene_started",
            "type": "uint8_t",
        },
    },
    "following_nuke": {
        "struct": "Player",
        "offset": 0x150,
        "expected": {
            "offset": "0x150",
            "size": 0x7C,
            "name": "nuke",
            "type": "cRNuke",
        },
    },
}

DIRTY_FUNCTIONS = (
    0x408060,  # initialize_runtime_pools_and_path_template_bank
    0x408670,  # initialize_click_start_controller_runtime
    0x438B90,  # update_subgame
    0x43A9C0,  # initialize_subgoldy
    0x43B120,  # update_subgoldy
    0x440910,  # remove_subgame_bods
    0x442170,  # initialize_click_start
    0x442290,  # update_click_start
    0x4466D0,  # update_cutscene
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
    observed_size = _named_struct_size("cRClickStart")
    observed_player_size = _named_struct_size("Player")
    observed_members = {
        hex(offset): _named_struct_member_readback("cRClickStart", offset)
        for offset in EXPECTED_OWNER_LAYOUT["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != EXPECTED_OWNER_LAYOUT["size"]:
        failures.append(
            {
                "selector": "cRClickStart",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_OWNER_LAYOUT["size"],
                "observed": observed_size,
            }
        )
    if observed_player_size != EXPECTED_PLAYER_SIZE:
        failures.append(
            {
                "selector": "Player",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_PLAYER_SIZE,
                "observed": observed_player_size,
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
                    "selector": f"cRClickStart.{name}",
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
        "type": "cRClickStart",
        "size": observed_size,
        "player_size": observed_player_size,
        "members": observed_members,
        "edges": edges,
        "failures": failures,
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
                    "failed": [{"reason": "noncanonical_click_start_header"}],
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
    owner_layout_readback = (
        {
            "type": "cRClickStart",
            "size": None,
            "player_size": None,
            "members": {},
            "edges": {},
            "failures": [],
        }
        if parse_errors or owner_type_alias_failures
        else _owner_layout_readback()
    )
    failed = owner_type_alias_failures + owner_layout_readback["failures"]
    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_type_alias_migrations": owner_type_alias_migrations,
                    "owner_layout_readback": owner_layout_readback,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

    applied = 0
    unchanged = 0
    missing = []
    for selector, declaration in TRUSTED_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func_start(address) == idc.BADADDR:
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

    dirty_functions = []
    for address in DIRTY_FUNCTIONS:
        if ida_funcs.get_func_start(address) != idc.BADADDR:
            ida_hexrays.mark_cfunc_dirty(address, True)
            dirty_functions.append(hex(address))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_type_alias_migrations": owner_type_alias_migrations,
                "owner_layout_readback": owner_layout_readback,
                "applied": applied,
                "unchanged": unchanged,
                "dirty_functions": dirty_functions,
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
        print("usage: apply_click_start_types.py <header-path>", file=sys.stderr)
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
