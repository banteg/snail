import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402
from type_alias_migration import migrate_equivalent_struct_aliases  # noqa: E402


TRUSTED_NAMES = [
    (0x497310, "g_logo_letter_vtable"),
]

LOGO_OWNER_TYPE_ALIASES = (
    ("LogoLetter", "cRLogoLetter", 0x90),
    ("Logo", "cRLogo", 0x25218),
)

EXPECTED_OWNER_LAYOUTS = {
    "BodBase": {
        "size": 0x38,
        "members": {
            0x24: ("object", "Object *"),
        },
    },
    "TransformMatrix": {
        "size": 0x40,
        "members": {
            0x30: ("position", "Vec3"),
            0x3C: ("position_w", "float"),
        },
    },
    "RenderableBod": {
        "size": 0x80,
        "members": {
            0x00: ("bod", "BodBase"),
            0x38: ("transform", "TransformMatrix"),
            0x78: ("render_animation_manager", "AnimManager *"),
            0x7C: ("frame_number", "int32_t"),
        },
    },
    "cRLogoLetter": {
        "size": 0x90,
        "members": {
            0x00: ("renderable", "RenderableBod"),
            0x80: ("velocity", "Vec3"),
            0x8C: ("glyph", "uint8_t"),
        },
    },
    "cRLogo": {
        "size": 0x25218,
        "members": {
            0x18: ("letters", "cRLogoLetter[1024]"),
            0x24018: ("image_donors", "cRLogoLetter[32]"),
        },
    },
}

TRUSTED_DECLARATIONS = [
    (
        "initialize_intro_logo_renderable",
        "cRLogoLetter* __thiscall initialize_intro_logo_renderable(cRLogoLetter* letter);",
    ),
    ("open_logo", "void __thiscall open_logo(cRLogo* logo);"),
    (
        "initialize_intro_screen",
        "void __thiscall initialize_intro_screen(cRLogo* logo, char* file_name);",
    ),
    (
        "destroy_intro_screen",
        "void __thiscall destroy_intro_screen(cRLogo* logo);",
    ),
    ("update_intro_screen", "void __thiscall update_intro_screen(cRLogo* logo);"),
    (
        "update_intro_logo_renderable",
        "void __thiscall update_intro_logo_renderable(cRLogoLetter* letter);",
    ),
]


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _owner_layout_readback() -> dict[str, object]:
    readback: dict[str, object] = {}
    failures: list[dict[str, object]] = []
    for type_name, expected in EXPECTED_OWNER_LAYOUTS.items():
        type_info = ida_typeinf.tinfo_t()
        if not type_info.get_named_type(None, type_name, ida_typeinf.BTF_STRUCT):
            failures.append(
                {"type": type_name, "reason": "missing_named_struct"}
            )
            continue
        members = ida_typeinf.udt_type_data_t()
        if not type_info.get_udt_details(members):
            failures.append(
                {"type": type_name, "reason": "missing_struct_details"}
            )
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
        else migrate_equivalent_struct_aliases(LOGO_OWNER_TYPE_ALIASES)
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
    owner_layout_readback = _owner_layout_readback()
    renamed = 0
    names_unchanged = 0
    applied = 0
    unchanged = 0
    missing = []
    failed = [*type_alias_failures, *owner_layout_readback["failures"]]

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "name": name, "reason": "rename_failed"})
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
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue
        applied += 1

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "type_alias_migrations": type_alias_migrations,
                "owner_layout_readback": owner_layout_readback,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "applied": applied,
                "unchanged": unchanged,
                "game_root_owner_graph": game_root_owner_graph,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or failed or missing else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_logo_types.py <header-path>", file=sys.stderr)
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
