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

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_NAMES = [
    (0x4B7790, "g_texture_refs"),
    (0x44DE90, "initialize_sprite"),
    (0x44DF30, "update_sprite"),
    (0x44E0F0, "register_sprite_texture"),
    (0x44E160, "initialize_sprite_manager"),
    (0x44E200, "kill_sprite"),
    (0x44E2A0, "allocate_sprite"),
    (0x44E3D0, "kill_game_sprites"),
    (0x44E410, "update_sprite_facing_angle"),
    (0x44E540, "set_sprite_manager_paused"),
    (0x44E550, "set_sprite_texture_ref"),
    (0x44E570, "get_sprite_texture"),
    (0x44E580, "get_sprite_texture_ref"),
    (0x44E800, "initialize_texture_list"),
    (0x44E810, "get_or_create_texture_ref"),
]

TRUSTED_DECLARATIONS = [
    (
        "initialize_texture_list",
        "void __thiscall initialize_texture_list(TextureRefList *texture_list, int32_t capacity);",
    ),
    (
        "get_or_create_texture_ref",
        "TextureRef *__thiscall get_or_create_texture_ref(TextureRefList *texture_list, char *texture_path, void *payload, int32_t flags);",
    ),
    (
        "initialize_sprite",
        "void __thiscall initialize_sprite(Sprite *sprite);",
    ),
    (
        "update_sprite",
        "void __thiscall update_sprite(Sprite *sprite);",
    ),
    (
        "register_sprite_texture",
        "TextureRef *__thiscall register_sprite_texture(SpriteManager *manager, char *texture_path, int32_t texture_id, int32_t flags);",
    ),
    (
        "initialize_sprite_manager",
        "void __thiscall initialize_sprite_manager(SpriteManager *manager);",
    ),
    (
        "kill_sprite",
        "void __thiscall kill_sprite(Sprite *sprite);",
    ),
    (
        "allocate_sprite",
        "Sprite *__thiscall allocate_sprite(SpriteManager *manager, int32_t owner, int32_t texture_id, int32_t texture_a, int32_t texture_b);",
    ),
    (
        "kill_game_sprites",
        "void __thiscall kill_game_sprites(SpriteManager *manager);",
    ),
    (
        "update_sprite_facing_angle",
        "void __thiscall update_sprite_facing_angle(Sprite *sprite, const struct TransformMatrix *matrix);",
    ),
    (
        "set_sprite_manager_paused",
        "uint8_t __thiscall set_sprite_manager_paused(SpriteManager *manager, uint8_t paused);",
    ),
    (
        "set_sprite_texture_ref",
        "TextureRef *__thiscall set_sprite_texture_ref(Sprite *sprite, int32_t texture_id, int32_t frame);",
    ),
    (
        "get_sprite_texture",
        "TextureRef *__thiscall get_sprite_texture(SpriteManager *manager, int32_t texture_id);",
    ),
    (
        "get_sprite_texture_ref",
        "void *__thiscall get_sprite_texture_ref(SpriteManager *manager, int32_t texture_id);",
    ),
    (
        "destroy_star_field",
        "void __thiscall destroy_star_field(StarManager *manager);",
    ),
    (
        "open_star_field",
        "void __thiscall open_star_field(StarManager *manager, int32_t star_count);",
    ),
    (
        "initialize_star_field",
        "void __thiscall initialize_star_field(StarManager *manager);",
    ),
    (
        "hide_star_field",
        "void __thiscall hide_star_field(StarManager *manager);",
    ),
    (
        "unhide_star_field",
        "void __thiscall unhide_star_field(StarManager *manager);",
    ),
    (
        "update_star_field",
        "void __thiscall update_star_field(StarManager *manager);",
    ),
    (
        "update_star_positions",
        "void __thiscall update_star_positions(StarManager *manager, float fade_alpha);",
    ),
]

TRUSTED_DATA_DECLARATIONS = [
    (0x4B7790, "g_texture_refs", "TextureRefList g_texture_refs;"),
]

REQUIRED_OWNER_MARKERS = (
    "#define TEXTURE_REF_LIST_CAPACITY 500",
    "typedef struct TextureRefList {",
    "TextureRef entries[TEXTURE_REF_LIST_CAPACITY];",
    "void __thiscall initialize_texture_list(",
    "TextureRef* __thiscall get_or_create_texture_ref(",
    "extern TextureRefList g_texture_refs;",
    "struct Sprite {",
    "float facing_refresh_progress;",
    "typedef struct StarManagerEntry {",
    "typedef struct StarManager {",
)

FORBIDDEN_DESTRUCTIVE_DECLARATIONS = (
    "typedef struct TransformMatrix TransformMatrix;",
)

EXPECTED_OWNER_SIZES = {
    "Object": 0xDC,
    "BodBase": 0x38,
    "TransformMatrix": 0x40,
    "TextureRef": 0xA4,
    "TextureRefList": 0x14058,
    "Sprite": 0xB4,
    "StarManagerEntry": 0x2C,
    "StarManager": 0x4C,
}

DEPENDENCY_HEADER_NAMES = (
    "object_render_types.h",
    "path_template_types.h",
)

REANALYSIS_FUNCTIONS = (
    0x40ACF0,
    0x40A490,
    0x44E0F0,
    0x44E410,
    0x44E800,
    0x44E810,
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


def _sync_initialize_color_lvar() -> dict[str, object]:
    selector = "initialize_star_field"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if lvar.is_stk_var() and "Color4f" in str(lvar.type())
    ]
    if not candidates:
        return {"status": "unchanged", "updated_count": 0, "selector": selector}

    local_type = ida_typeinf.tinfo_t()
    if not local_type.get_named_type(None, "tColour", ida_typeinf.BTF_STRUCT):
        return {
            "status": "failed",
            "reason": "missing_tColour_type",
            "selector": selector,
        }

    updated = []
    for lvar in candidates:
        info = ida_hexrays.lvar_saved_info_t()
        info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
        info.type = local_type
        if not ida_hexrays.modify_user_lvar_info(address, ida_hexrays.MLI_TYPE, info):
            return {
                "status": "failed",
                "reason": "modify_user_lvar_info_failed",
                "local": lvar.name,
                "selector": selector,
            }
        updated.append(lvar.name)

    return {
        "status": "applied",
        "updated_count": len(updated),
        "locals": updated,
        "type": "tColour",
        "selector": selector,
    }


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    destructive_declarations = [
        declaration
        for declaration in FORBIDDEN_DESTRUCTIVE_DECLARATIONS
        if declaration in header_text
    ]
    if missing_owner_markers or destructive_declarations:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "applied": 0,
                    "missing_owner_markers": missing_owner_markers,
                    "destructive_declarations": destructive_declarations,
                    "failed": [
                        {
                            "reason": "noncanonical_star_manager_header",
                            "detail": (
                                "refusing to replace shared IDA types with a sparse "
                                "or forward-only StarManager compatibility header"
                            ),
                        }
                    ],
                },
                indent=2,
            )
        )
        return 1

    dependency_parse_results = []
    for dependency_name in DEPENDENCY_HEADER_NAMES:
        dependency_header = header_path.with_name(dependency_name)
        if dependency_header.is_file():
            dependency_parse_results.append(
                {
                    "header": str(dependency_header),
                    "parse_errors": idc.parse_decls(
                        str(dependency_header), idc.PT_FILE
                    ),
                }
            )
        else:
            dependency_parse_results.append(
                {
                    "header": str(dependency_header),
                    "parse_errors": None,
                    "reason": "missing_dependency_header",
                }
            )

    # Sprite is shared by several narrow ownership lanes. Replace any earlier
    # partial declaration so this full 0xb4-byte owner remains authoritative.
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
    owner_sizes = {
        name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES
    }
    size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": owner_sizes[name],
        }
        for name, expected_size in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected_size
    ]
    dependency_failures = [
        {
            "selector": result["header"],
            "reason": result.get("reason", "dependency_parse_failed"),
            "parse_errors": result["parse_errors"],
        }
        for result in dependency_parse_results
        if result["parse_errors"] != 0
    ]
    if parse_errors or size_failures or dependency_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "dependency_headers": dependency_parse_results,
                    "parse_errors": parse_errors,
                    "applied": 0,
                    "owner_sizes": owner_sizes,
                    "failed": [*dependency_failures, *size_failures],
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
    failed = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"address": hex(address), "selector": name, "reason": "rename_failed"}
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
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "declaration": declaration,
                    "reason": "set_data_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "data_verification_failed",
                }
            )
            continue
        applied += 1

    color_lvar = _sync_initialize_color_lvar()
    if color_lvar.get("status") == "failed":
        failed.append({"selector": "initialize_star_field", "color_lvar": color_lvar})

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    reanalysis_functions = []
    for address in REANALYSIS_FUNCTIONS:
        function = ida_funcs.get_func(address)
        if function is None:
            failed.append(
                {
                    "address": hex(address),
                    "reason": "missing_reanalysis_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(function.start_ea, True)
        reanalysis_functions.append(hex(function.start_ea))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "dependency_headers": dependency_parse_results,
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "owner_sizes": owner_sizes,
                "color_lvar": color_lvar,
                "game_root_owner_graph": game_root_owner_graph,
                "reanalysis_functions": reanalysis_functions,
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
        print("usage: apply_star_manager_types.py <header-path>", file=sys.stderr)
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
