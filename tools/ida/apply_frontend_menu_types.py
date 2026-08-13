from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph
from type_alias_migration import migrate_equivalent_struct_aliases

FRONTEND_MENU_OWNER_TYPE_ALIASES = (
    ("MainMenu", "cRMainMenu", 0x18),
    ("Options", "cROptions", 0x24),
    ("Exit", "cRExit", 0x1C),
)


EXPECTED_OWNER_SIZES = {
    "cRMainMenu": 0x18,
    "cROptions": 0x24,
    "cRExit": 0x1C,
}

EXPECTED_OWNER_LAYOUTS = {
    "cRMainMenu": {
        "size": 0x18,
        "members": {
            0x00: ("new_game_widget", "FrontendWidget *"),
            0x04: ("high_scores_widget", "FrontendWidget *"),
            0x08: ("options_widget", "FrontendWidget *"),
            0x0C: ("credits_widget", "FrontendWidget *"),
            0x14: ("exit_widget", "FrontendWidget *"),
        },
    },
    "cROptions": {
        "size": 0x24,
        "members": {
            0x00: ("previous_frontend_state", "int32_t"),
            0x04: ("active", "uint8_t"),
            0x10: ("back_widget", "FrontendWidget *"),
            0x14: ("fullscreen_widget", "FrontendWidget *"),
            0x18: ("sound_volume_widget", "FrontendWidget *"),
            0x1C: ("music_volume_widget", "FrontendWidget *"),
            0x20: ("previous_sample_volume", "float"),
        },
    },
    "cRExit": {
        "size": 0x1C,
        "members": {
            0x00: ("state", "int32_t"),
            0x08: ("previous_frontend_state", "int32_t"),
            0x0C: ("prompt_y", "float"),
            0x10: ("prompt_title", "FrontendWidget *"),
            0x14: ("yes_button", "FrontendWidget *"),
            0x18: ("no_button", "FrontendWidget *"),
        },
    },
}

TRUSTED_DECLARATIONS = (
    ("destroy_main_menu", "void __thiscall destroy_main_menu(cRMainMenu* menu);"),
    ("initialize_main_menu", "void __thiscall initialize_main_menu(cRMainMenu* menu);"),
    ("update_main_menu", "void __thiscall update_main_menu(cRMainMenu* menu);"),
    (
        "initialize_options_menu",
        "void __thiscall initialize_options_menu(cROptions* options);",
    ),
    (
        "destroy_options_menu",
        "void __thiscall destroy_options_menu(cROptions* options);",
    ),
    (
        "update_options_menu",
        "void __thiscall update_options_menu(cROptions* options);",
    ),
    (
        "apply_audio_config_volumes",
        "void __thiscall apply_audio_config_volumes(cROptions* options);",
    ),
    (
        "destroy_completion_screen",
        "void __thiscall destroy_completion_screen(cRExit* exit_controller);",
    ),
    (
        "initialize_exit_prompt",
        "void __thiscall initialize_exit_prompt(cRExit* exit_controller);",
    ),
    (
        "update_completion_screen",
        "void __thiscall update_completion_screen(cRExit* exit_controller);",
    ),
    ("launch_alpha72_url", "void __cdecl launch_alpha72_url(char* url);"),
)


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
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _owner_layout_readback() -> dict[str, object]:
    readback: dict[str, object] = {}
    failures: list[dict[str, object]] = []
    for type_name, expected in EXPECTED_OWNER_LAYOUTS.items():
        type_info = ida_typeinf.tinfo_t()
        if not type_info.get_named_type(None, type_name, ida_typeinf.BTF_STRUCT):
            failures.append({"type": type_name, "reason": "missing_named_struct"})
            continue
        members = ida_typeinf.udt_type_data_t()
        if not type_info.get_udt_details(members):
            failures.append({"type": type_name, "reason": "missing_struct_details"})
            continue
        observed_members = {
            int(member.offset) // 8: {
                "name": str(member.name),
                "type": _normalize_type_text(member.type.dstr()),
            }
            for member in members
        }
        observed = {
            "size": type_info.get_size(),
            "members": {
                hex(offset): observed_members.get(offset)
                for offset in expected["members"]
            },
        }
        readback[type_name] = observed
        if observed["size"] != expected["size"]:
            failures.append(
                {
                    "type": type_name,
                    "reason": "owner_size_mismatch",
                    "expected": expected["size"],
                    "observed": observed["size"],
                }
            )
        for offset, (expected_name, expected_type) in expected["members"].items():
            expected_member = {
                "name": expected_name,
                "type": _normalize_type_text(expected_type),
            }
            if observed_members.get(offset) != expected_member:
                failures.append(
                    {
                        "type": type_name,
                        "offset": hex(offset),
                        "reason": "owner_member_mismatch",
                        "expected": expected_member,
                        "observed": observed_members.get(offset),
                    }
                )
    return {"types": readback, "failures": failures}


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(FRONTEND_MENU_OWNER_TYPE_ALIASES)
    )
    type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in type_alias_migrations
        if result.get("status") == "failed"
    ]
    owner_layout_readback = (
        {"types": {}, "failures": []}
        if parse_errors or type_alias_failures
        else _owner_layout_readback()
    )
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    failed = [
        *type_alias_failures,
        *[
            {
                "selector": name,
                "reason": "owner_size_mismatch",
                "expected": expected,
                "observed": owner_sizes[name],
            }
            for name, expected in EXPECTED_OWNER_SIZES.items()
            if owner_sizes[name] != expected
        ],
        *owner_layout_readback["failures"],
    ]
    missing = []
    applied = 0
    unchanged = 0

    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "type_alias_migrations": type_alias_migrations,
                    "owner_sizes": owner_sizes,
                    "owner_layout_readback": owner_layout_readback,
                    "applied": applied,
                    "unchanged": unchanged,
                    "game_root_owner_graph": {
                        "status": "skipped",
                        "reason": "owner_preflight_failed",
                    },
                    "missing": missing,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

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

    game_root_owner_graph = (
        sync_game_root_owner_graph(require=False)
        if not missing and not failed
        else {"status": "skipped", "reason": "prototype_replay_failed"}
    )
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "type_alias_migrations": type_alias_migrations,
                "owner_sizes": owner_sizes,
                "owner_layout_readback": owner_layout_readback,
                "applied": applied,
                "unchanged": unchanged,
                "game_root_owner_graph": game_root_owner_graph,
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
        print("usage: apply_frontend_menu_types.py <header-path>", file=sys.stderr)
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
