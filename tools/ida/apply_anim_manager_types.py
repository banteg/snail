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
    (0x4447C0, "initialize_anim_manager"),
    (0x4447D0, "update_anim_manager"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_anim_manager",
        "void __thiscall initialize_anim_manager(cRAnimManager* manager);",
    ),
    (
        "update_anim_manager",
        "void __thiscall update_anim_manager(cRAnimManager* manager);",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct cRAnimManager {",
    "} cRAnimManager;",
    "ObjectAnimation* active_animation;",
    "int32_t queued_animations[10];",
    "PresentationAnimationSlot* animation_slots;",
    "cRAnimManager_must_be_0x48",
)

EXPECTED_OWNER_SIZES = {
    "cRAnimManager": 0x48,
}

OWNER_TYPE_ALIASES = (("AnimManager", "cRAnimManager", 0x48),)

EXPECTED_OWNER_LAYOUT = {
    "size": 0x48,
    "members": {
        0x00: (0x04, "state", "int32_t"),
        0x04: (0x04, "progress", "float"),
        0x08: (0x04, "progress_step", "float"),
        0x0C: (0x04, "active_animation", "ObjectAnimation *"),
        0x10: (0x01, "completed", "uint8_t"),
        0x11: (0x03, "_pad_11", "uint8_t[3]"),
        0x14: (0x28, "queued_animations", "int32_t[10]"),
        0x3C: (0x04, "queue_count", "int32_t"),
        0x40: (0x04, "target_model", "RenderableBod *"),
        0x44: (0x04, "animation_slots", "PresentationAnimationSlot *"),
    },
}

EXPECTED_OWNER_EDGES = {
    "renderable_backlink": {
        "struct": "RenderableBod",
        "offset": 0x78,
        "expected": {
            "offset": "0x78",
            "size": 0x04,
            "name": "render_animation_manager",
            "type": "cRAnimManager *",
        },
    },
    "snail_embed": {
        "struct": "Snail",
        "offset": 0x104,
        "expected": {
            "offset": "0x104",
            "size": 0x48,
            "name": "anim_manager",
            "type": "cRAnimManager",
        },
    },
    "weapon_embed": {
        "struct": "Weapon",
        "offset": 0x108,
        "expected": {
            "offset": "0x108",
            "size": 0x48,
            "name": "anim_manager",
            "type": "cRAnimManager",
        },
    },
}

DIRTY_FUNCTIONS = (
    0x40A490,  # render_game_frame
    0x43A9C0,  # initialize_subgoldy
    0x43B120,  # update_subgoldy
    0x444600,  # dispatch_cutscene_animation
    0x4446E0,  # set_weapon_animation
    0x4447C0,  # initialize_anim_manager
    0x4447D0,  # update_anim_manager
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
    type_name = "cRAnimManager"
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
        "type": type_name,
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
                    "failed": [{"reason": "noncanonical_anim_manager_header"}],
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
            "type": "cRAnimManager",
            "size": None,
            "members": {},
            "edges": {},
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
        print("usage: apply_anim_manager_types.py <header-path>", file=sys.stderr)
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
