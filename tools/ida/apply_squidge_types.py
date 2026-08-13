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
from type_alias_migration import migrate_equivalent_struct_aliases

TRUSTED_NAMES = (
    (0x444960, "initialize_squidge"),
    (0x444980, "start_squidge_y"),
    (0x4449A0, "start_squidge_z"),
    (0x4449C0, "update_squidge"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_squidge",
        "void __thiscall initialize_squidge(cRSquidge* squidge);",
    ),
    (
        "start_squidge_y",
        "void __thiscall start_squidge_y(cRSquidge* squidge, float value);",
    ),
    (
        "start_squidge_z",
        "void __thiscall start_squidge_z(cRSquidge* squidge, float value);",
    ),
    (
        "update_squidge",
        "void __thiscall update_squidge(cRSquidge* squidge);",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct cRSquidge {",
    "} cRSquidge;",
    "float y_output;",
    "float z_phase;",
    "cRSquidge_must_be_0x18",
)

EXPECTED_OWNER_SIZES = {
    "cRSquidge": 0x18,
}

OWNER_TYPE_ALIASES = (("Squidge", "cRSquidge", 0x18),)

EXPECTED_OWNER_LAYOUT = {
    "size": 0x18,
    "members": {
        0x00: (0x04, "y_output", "float"),
        0x04: (0x04, "y_velocity", "float"),
        0x08: (0x04, "y_phase", "float"),
        0x0C: (0x04, "z_output", "float"),
        0x10: (0x04, "z_velocity", "float"),
        0x14: (0x04, "z_phase", "float"),
    },
}

EXPECTED_PLAYER_EMBED = {
    "offset": "0x4344",
    "size": 0x18,
    "name": "squidge",
    "type": "cRSquidge",
}

DIRTY_FUNCTIONS = (
    0x42C770,  # try_enter_track_attachment_from_swept_motion
    0x43A9C0,  # initialize_subgoldy
    0x43B120,  # update_subgoldy
    0x444960,  # initialize_squidge
    0x444980,  # start_squidge_y
    0x4449A0,  # start_squidge_z
    0x4449C0,  # update_squidge
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
    return re.sub(r"\b(?:struct|class|union)\s+", "", normalized)


def _named_struct_member_readback(
    struct_name: str, offset: int
) -> dict[str, object] | None:
    owner = ida_typeinf.tinfo_t()
    if not owner.get_named_type(None, struct_name, ida_typeinf.BTF_STRUCT):
        return None
    members = ida_typeinf.udt_type_data_t()
    if not owner.get_udt_details(members):
        return None
    for member in members:
        member_offset = int(member.offset) // 8
        if member_offset == offset:
            return {
                "offset": hex(member_offset),
                "size": int(member.size) // 8,
                "name": member.name,
                "type": _normalize_udt_type(member.type.dstr()),
            }
    return None


def _owner_layout_readback() -> dict[str, object]:
    type_name = "cRSquidge"
    observed_size = _named_struct_size(type_name)
    observed_members = {
        hex(offset): _named_struct_member_readback(type_name, offset)
        for offset in EXPECTED_OWNER_LAYOUT["members"]
    }
    failures: list[dict[str, object]] = []
    if observed_size != EXPECTED_OWNER_LAYOUT["size"]:
        failures.append(
            {
                "selector": type_name,
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
                    "selector": f"{type_name}.{name}",
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_member,
                }
            )
    player_embed = _named_struct_member_readback("Player", 0x4344)
    if player_embed != EXPECTED_PLAYER_EMBED:
        failures.append(
            {
                "selector": "Player.squidge",
                "reason": "embedded_owner_mismatch",
                "expected": EXPECTED_PLAYER_EMBED,
                "observed": player_embed,
            }
        )
    return {
        "type": type_name,
        "size": observed_size,
        "members": observed_members,
        "player_embed": player_embed,
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
                    "failed": [{"reason": "noncanonical_squidge_header"}],
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
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    owner_size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": owner_sizes[name],
        }
        for name, expected_size in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected_size
    ]
    owner_layout_readback = (
        {
            "type": "cRSquidge",
            "size": None,
            "members": {},
            "player_embed": None,
            "failures": [],
        }
        if parse_errors or owner_type_alias_failures
        else _owner_layout_readback()
    )
    failed = (
        owner_type_alias_failures
        + owner_size_failures
        + owner_layout_readback["failures"]
    )
    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_type_alias_migrations": owner_type_alias_migrations,
                    "owner_sizes": owner_sizes,
                    "owner_layout_readback": owner_layout_readback,
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
                "owner_sizes": owner_sizes,
                "owner_layout_readback": owner_layout_readback,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
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
        print("usage: apply_squidge_types.py <header-path>", file=sys.stderr)
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
