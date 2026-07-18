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
    (0x43A010, "health_collect_particles"),
    (0x43A300, "update_movement_flag_emitters"),
    (0x43A370, "end_jetpack_hover"),
    (0x43A9C0, "initialize_subgoldy"),
    (0x43AF10, "show_subgoldy_lives"),
    (0x43AFD0, "play_movement_state_sound"),
    (0x43D230, "initialize_subgoldy_ghost"),
    (0x43D3D0, "set_subgoldy_ghost_z"),
)

TRUSTED_DECLARATIONS = (
    (
        "health_collect_particles",
        "void __thiscall health_collect_particles(Player* player, SubHealth* pickup);",
    ),
    (
        "update_movement_flag_emitters",
        "void __thiscall update_movement_flag_emitters(Player* owner, Player* movement_source);",
    ),
    (
        "end_jetpack_hover",
        "void __thiscall end_jetpack_hover(SubHover* sub_hover);",
    ),
    (
        "initialize_subgoldy",
        "void __thiscall initialize_subgoldy(Player* player, int32_t player_slot);",
    ),
    (
        "show_subgoldy_lives",
        "void __thiscall show_subgoldy_lives(Player* player);",
    ),
    (
        "play_movement_state_sound",
        "void __thiscall play_movement_state_sound(Player* player);",
    ),
    (
        "initialize_subgoldy_ghost",
        "void __thiscall initialize_subgoldy_ghost(Player* player, int32_t owner);",
    ),
    (
        "set_subgoldy_ghost_z",
        "void __thiscall set_subgoldy_ghost_z(Player* player, float ghost_z);",
    ),
)

DEPENDENCY_HEADER_NAMES = (
    "object_render_types.h",
    "star_manager_types.h",
    "runtime_config_types.h",
)

DEPENDENCY_OWNER_MARKERS = {
    "object_render_types.h": (
        "typedef struct Object {",
        "ObjectAnimation* animation;",
    ),
    "star_manager_types.h": (
        "struct Sprite {",
        "Vec3 position;",
        "float gravity_step;",
    ),
    "runtime_config_types.h": (
        "typedef struct RuntimeConfig {",
        "RuntimeRenderFlag render_flags;",
        "extern RuntimeConfig g_runtime_config;",
    ),
}

REQUIRED_OWNER_MARKERS = (
    "typedef struct SubHealth {",
    "typedef struct SubHover {",
    "typedef struct GolbShot {",
    "typedef struct GolbShotFlightStrideCursor {",
    "TransformMatrix flight_transform;",
    "uint8_t _stride_tail[0x238];",
    "typedef struct Player {",
    "GolbShot golb_shots[0xc];",
    "SubHover sub_hover;",
    "Snail presentation;",
    "typedef struct SubgameRuntime {",
    "void __thiscall health_collect_particles(Player* player, SubHealth* pickup);",
)

EXPECTED_OWNER_SIZES = {
    "ObjectAnimation": 0x14,
    "Object": 0xDC,
    "Sprite": 0xB4,
    "RuntimeConfig": 0xC4,
    "RenderableBod": 0x80,
    "AnimManager": 0x48,
    "SubHealth": 0x74,
    "SubHover": 0x214,
    "GolbShot": 0x2E8,
    "GolbShotFlightStrideCursor": 0x2E8,
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "Snail": 0x19B4,
    "Player": 0x4364,
    "SubgameRuntime": 0x1272838,
}

GOLB_SHOT_CURSOR_LVAR = (
    "golb_shot_flight_cursor",
    "GolbShotFlightStrideCursor *golb_shot_flight_cursor;",
    0x43AE54,
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


def _sync_golb_shot_cursor_lvar() -> dict[str, object]:
    selector = "initialize_subgoldy"
    expected_name, declaration, definition_address = GOLB_SHOT_CURSOR_LVAR
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
        nearby_lvars = [
            {
                "name": lvar.name,
                "type": str(lvar.type()),
                "definition_address": hex(lvar.defea),
                "is_stack": lvar.is_stk_var(),
            }
            for lvar in cfunc.get_lvars()
            if not lvar.is_arg_var and 0x43AE00 <= lvar.defea <= 0x43AE80
        ]
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_cursor_lvar_candidates",
            "definition_address": hex(definition_address),
            "candidate_count": len(candidates),
            "nearby_lvars": nearby_lvars,
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


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    dependency_headers = [header_path.with_name(name) for name in DEPENDENCY_HEADER_NAMES]
    dependency_marker_failures = []
    for dependency_header in dependency_headers:
        if not dependency_header.is_file():
            dependency_marker_failures.append(
                {"header": str(dependency_header), "reason": "missing_dependency_header"}
            )
            continue
        dependency_text = dependency_header.read_text(encoding="utf-8")
        missing = [
            marker
            for marker in DEPENDENCY_OWNER_MARKERS[dependency_header.name]
            if marker not in dependency_text
        ]
        if missing:
            dependency_marker_failures.append(
                {
                    "header": str(dependency_header),
                    "reason": "noncanonical_dependency_header",
                    "missing_owner_markers": missing,
                }
            )

    if missing_owner_markers or dependency_marker_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_owner_markers": missing_owner_markers,
                    "dependency_marker_failures": dependency_marker_failures,
                    "failed": [{"reason": "noncanonical_player_owner_header"}],
                },
                indent=2,
            )
        )
        return 1

    dependency_parse_results = [
        {
            "header": str(dependency_header),
            "parse_errors": idc.parse_decls(str(dependency_header), idc.PT_FILE),
        }
        for dependency_header in dependency_headers
    ]
    dependency_parse_failed = any(
        result["parse_errors"] for result in dependency_parse_results
    )
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
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
    if dependency_parse_failed or parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "dependency_parse_results": dependency_parse_results,
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
    dirty_functions = []
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
        elif not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_type_failed"})
            continue
        elif _normalize_type_text(idc.get_type(address)) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "verification_failed",
                    "observed": idc.get_type(address),
                }
            )
            continue
        else:
            applied += 1

        ida_hexrays.mark_cfunc_dirty(address, True)
        dirty_functions.append(hex(address))

    golb_shot_cursor_lvar = _sync_golb_shot_cursor_lvar()
    if golb_shot_cursor_lvar.get("status") == "failed":
        failed.append(
            {
                "selector": "initialize_subgoldy",
                "cursor_lvar": golb_shot_cursor_lvar,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "dependency_parse_results": dependency_parse_results,
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "golb_shot_cursor_lvar": golb_shot_cursor_lvar,
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
    return 1 if dependency_parse_failed or parse_errors or missing or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_player_lifecycle_types.py <header-path>", file=sys.stderr)
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
