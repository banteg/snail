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
        "initialize_help_screen",
        "void __thiscall initialize_help_screen(cRHelp* help);",
    ),
    (
        "destroy_help_screen",
        "void __thiscall destroy_help_screen(cRHelp* help);",
    ),
    (
        "update_help_screen",
        "void __thiscall update_help_screen(cRHelp* help);",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct cRHelp {",
    "FrontendWidget* back_button;",
    "cRHelp_must_be_0x04",
)

OWNER_TYPE_ALIASES = (("Help", "cRHelp", 0x04),)

EXPECTED_OWNER_LAYOUT = {
    "size": 0x04,
    "members": {
        0x00: (0x04, "back_button", "FrontendWidget *"),
    },
}

EXPECTED_OWNER_EDGES = {
    "previous_gui": {
        "struct": "cRSubGame",
        "offset": 0x125FFE0,
        "expected": {
            "offset": "0x125ffe0",
            "size": 0x28,
            "name": "gui",
            "type": "cRGUI",
        },
    },
    "subgame_embed": {
        "struct": "cRSubGame",
        "offset": 0x1260008,
        "expected": {
            "offset": "0x1260008",
            "size": 0x04,
            "name": "help",
            "type": "cRHelp",
        },
    },
    "following_splash": {
        "struct": "cRSubGame",
        "offset": 0x126000C,
        "expected": {
            "offset": "0x126000c",
            "size": 0x14,
            "name": "splash",
            "type": "cRSplash",
        },
    },
}

DIRTY_FUNCTIONS = (
    0x4107D0,  # update_frontend_state_machine
    0x416800,  # initialize_help_screen
    0x4168C0,  # destroy_help_screen
    0x4168D0,  # update_help_screen
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
    observed_size = _named_struct_size("cRHelp")
    observed_members = {
        hex(offset): _named_struct_member_readback("cRHelp", offset)
        for offset in EXPECTED_OWNER_LAYOUT["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != EXPECTED_OWNER_LAYOUT["size"]:
        failures.append(
            {
                "selector": "cRHelp",
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
                    "selector": f"cRHelp.{name}",
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
        "type": "cRHelp",
        "size": observed_size,
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
                    "failed": [{"reason": "noncanonical_help_header"}],
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
        {"type": "cRHelp", "size": None, "members": {}, "edges": {}, "failures": []}
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
        print("usage: apply_help_types.py <header-path>", file=sys.stderr)
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
