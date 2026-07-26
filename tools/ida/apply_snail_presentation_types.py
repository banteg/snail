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
    (0x43A390, "update_jetpack_gauge"),
    (0x43A580, "uninit_jet_particles"),
    (0x43A5B0, "initialize_jet_particles"),
    (0x43A690, "update_jet_particles"),
    (0x43A930, "initialize_jetpack_gauge"),
    (0x43A980, "arm_jetpack_gauge"),
    (0x4428D0, "update_snail_presentation"),
    (0x442E40, "release_snail_weapons"),
    (0x444600, "dispatch_cutscene_animation"),
    (0x4446E0, "set_weapon_animation"),
    (0x444AC0, "initialize_invincible_shell"),
    (0x444AE0, "start_invincible_shell"),
    (0x444B50, "update_invincible_shell"),
    (0x445860, "set_snail_jetpack"),
    (0x445CD0, "build_snail_world_hotspots"),
    (0x445D50, "extract_snail_local_hotspots"),
    (0x445F60, "initialize_snail_skin"),
    (0x445F80, "update_snail_skin_transition"),
    (0x445FD0, "change_snail_skin"),
)

TRUSTED_DECLARATIONS = (
    (
        "update_jetpack_gauge",
        "void __thiscall update_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "uninit_jet_particles",
        "void __thiscall uninit_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jet_particles",
        "void __thiscall initialize_jet_particles(SubHover* sub_hover);",
    ),
    (
        "update_jet_particles",
        "void __thiscall update_jet_particles(SubHover* sub_hover);",
    ),
    (
        "initialize_jetpack_gauge",
        "void __thiscall initialize_jetpack_gauge(SubHover* sub_hover, int32_t player_slot);",
    ),
    (
        "arm_jetpack_gauge",
        "void __thiscall arm_jetpack_gauge(SubHover* sub_hover);",
    ),
    (
        "update_snail_presentation",
        "void __thiscall update_snail_presentation(Snail* snail);",
    ),
    (
        "release_snail_weapons",
        "void __thiscall release_snail_weapons(Snail* snail);",
    ),
    (
        "dispatch_cutscene_animation",
        "void __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "initialize_invincible_shell",
        "void __thiscall initialize_invincible_shell(Invincible* invincible);",
    ),
    (
        "start_invincible_shell",
        "void __thiscall start_invincible_shell(Invincible* invincible);",
    ),
    (
        "update_invincible_shell",
        "void __thiscall update_invincible_shell(Invincible* invincible);",
    ),
    (
        "set_snail_jetpack",
        "void __thiscall set_snail_jetpack(Snail* snail, int32_t state);",
    ),
    (
        "build_snail_world_hotspots",
        "void __thiscall build_snail_world_hotspots(Snail* snail);",
    ),
    (
        "extract_snail_local_hotspots",
        "void __thiscall extract_snail_local_hotspots(Snail* snail);",
    ),
    (
        "initialize_snail_skin",
        "void __thiscall initialize_snail_skin(SnailSkin* snail_skin);",
    ),
    (
        "update_snail_skin_transition",
        "void __thiscall update_snail_skin_transition(SnailSkin* snail_skin);",
    ),
    (
        "change_snail_skin",
        "void __thiscall change_snail_skin(SnailSkin* snail_skin, int32_t slot_id, float duration_seconds);",
    ),
)

DEPENDENCY_HEADER_NAMES = (
    "object_render_types.h",
    "star_manager_types.h",
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
}

REQUIRED_OWNER_MARKERS = (
    "typedef struct ObjectAnimation {",
    "struct AnimManager {",
    "typedef struct SubHover {",
    "typedef struct Weapon {",
    "Vec3 release_step;",
    "typedef struct Invincible {",
    "typedef struct SnailSkin {",
    "TextureRef* material_overrides[3];",
    "uint8_t channel_release_steps_active;",
    "typedef struct Snail {",
    "Weapon weapon_channels[3];",
    "Vec3 snail_hotspots_local[19];",
    "typedef struct Player {",
    "SubHover sub_hover;",
    "Snail presentation;",
)

EXPECTED_OWNER_SIZES = {
    "ObjectAnimation": 0x14,
    "Object": 0xDC,
    "ObjectFaceQuadTextureCursorView": 0x30,
    "Sprite": 0xB4,
    "RenderableBod": 0x80,
    "SnailHotspotLocalZCursorView": 0x0C,
    "PresentationAnimationSlot": 0x80,
    "AnimManager": 0x48,
    "SubHover": 0x214,
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "SnailSkin": 0x20,
    "Snail": 0x19B4,
    "Player": 0x4364,
}

# The authored Player root displacement numerically lands on the tracked
# g_player_block offset symbol. Keep that evidence symbol, but render this one
# ADD operand as a number so Hex-Rays can fold GameRoot::subgame.player.
SUBHOVER_PLAYER_ROOT_OFFSET_OPERAND = (0x43A953, 1, 0x42FD7C)

# These relocatable reference symbols remain useful in the reference manifest,
# but rendering them symbolically at these instructions prevents Hex-Rays from
# folding the accesses through GameRoot::subgame.player and Snail. Normalize
# only the proved consumer operands; the underlying reference names stay intact.
INVINCIBLE_ROOT_OFFSET_OPERANDS = (
    (0x444B72, 0, 0x4300B4),
    (0x444BCD, 0, 0x4300B4),
    (0x444BE4, 0, 0x4300B4),
    (0x444C3C, 0, 0x4300B4),
    (0x444CBD, 1, 0x432738),
)

HOTSPOT_LVAR_SPECS = (
    (
        "build_snail_world_hotspots",
        "hotspot_index",
        "int32_t hotspot_index;",
        0x445CDC,
    ),
    (
        "build_snail_world_hotspots",
        "hotspot_world_cursor",
        "Vec3 *hotspot_world_cursor;",
        0x445CDE,
    ),
    (
        "build_snail_world_hotspots",
        "hotspot_transform",
        "TransformMatrix *hotspot_transform;",
        0x445CF3,
    ),
    (
        "build_snail_world_hotspots",
        "hotspot_world_slot",
        "Vec3 *hotspot_world_slot;",
        0x445D32,
    ),
    (
        "extract_snail_local_hotspots",
        "hotspot_model",
        "Object *hotspot_model;",
        0x445D54,
    ),
    (
        "extract_snail_local_hotspots",
        "hotspot_name_cursor",
        "char **hotspot_name_cursor;",
        0x445D60,
    ),
    (
        "extract_snail_local_hotspots",
        "hotspot_local_z_cursor",
        (
            "float *__shifted(SnailHotspotLocalZCursorView, 0x08) "
            "hotspot_local_z_cursor;"
        ),
        0x445D65,
    ),
    (
        "extract_snail_local_hotspots",
        "hotspot_face_texture_cursor",
        (
            "TextureRef **__shifted(ObjectFaceQuadTextureCursorView, 0x0C) "
            "hotspot_face_texture_cursor;"
        ),
        0x445D90,
    ),
    (
        "extract_snail_local_hotspots",
        "hotspot_source_vertex",
        "Vec3 *hotspot_source_vertex;",
        0x445DCD,
    ),
)

JETPACK_LVAR_SPECS = (
    (
        "set_snail_jetpack",
        "target_state",
        "int32_t target_state;",
        0x445871,
        False,
    ),
    (
        "set_snail_jetpack",
        "selected_state",
        "int32_t selected_state;",
        0x445880,
        False,
    ),
    (
        "set_snail_jetpack",
        "transition_immediate",
        "uint8_t transition_immediate;",
        0x445886,
        True,
    ),
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


def _sync_named_lvar(
    selector: str,
    expected_name: str,
    declaration: str,
    definition_address: int,
    expected_stack: bool = False,
) -> dict[str, object]:
    address = idc.get_name_ea_simple(selector)
    if (
        address == idc.BADADDR
        or ida_funcs.get_func_start(address) == idc.BADADDR
    ):
        return {"status": "failed", "selector": selector, "reason": "missing_function"}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and lvar.is_stk_var() == expected_stack
        and lvar.defea == definition_address
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "unexpected_named_lvar_candidates",
            "definition_address": hex(definition_address),
            "expected_stack": expected_stack,
            "candidate_count": len(candidates),
        }

    expected_type = ida_typeinf.tinfo_t()
    if not ida_typeinf.parse_decl(
        expected_type,
        None,
        declaration,
        ida_typeinf.PT_SIL,
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "parse_named_lvar_type_failed",
            "declaration": declaration,
        }

    lvar = candidates[0]
    normalized_expected_type = _normalize_type_text(str(expected_type))
    observed_type = _normalize_type_text(str(lvar.type()))
    if lvar.name == expected_name and observed_type == normalized_expected_type:
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
    info.type = expected_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "selector": selector,
            "reason": "modify_named_lvar_failed",
            "definition_address": hex(definition_address),
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and candidate.is_stk_var() == expected_stack
        and candidate.defea == definition_address
        and candidate.name == expected_name
        and _normalize_type_text(str(candidate.type())) == normalized_expected_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "selector": selector,
            "reason": "named_lvar_readback_failed",
            "definition_address": hex(definition_address),
            "expected_stack": expected_stack,
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


def _normalize_subhover_player_root_offset() -> dict[str, object]:
    address, operand_index, expected_offset = SUBHOVER_PLAYER_ROOT_OFFSET_OPERAND
    before = idc.print_operand(address, operand_index)
    idc.op_num(address, operand_index)
    after = idc.print_operand(address, operand_index)
    observed_offset = idc.get_operand_value(address, operand_index)
    normalized = (
        observed_offset == expected_offset
        and f"{expected_offset:X}H" in after.upper()
    )
    return {
        "status": (
            "applied"
            if normalized and before != after
            else "unchanged"
            if normalized
            else "failed"
        ),
        "address": hex(address),
        "operand_index": operand_index,
        "expected_offset": hex(expected_offset),
        "observed_offset": hex(observed_offset),
        "before": before,
        "after": after,
    }


def _normalize_invincible_root_offsets() -> list[dict[str, object]]:
    results = []
    for address, operand_index, expected_offset in INVINCIBLE_ROOT_OFFSET_OPERANDS:
        before = idc.print_operand(address, operand_index)
        idc.op_num(address, operand_index)
        after = idc.print_operand(address, operand_index)
        observed_offset = idc.get_operand_value(address, operand_index)
        normalized = (
            observed_offset == expected_offset
            and f"{expected_offset:X}H" in after.upper()
        )
        results.append(
            {
                "status": (
                    "applied"
                    if normalized and before != after
                    else "unchanged"
                    if normalized
                    else "failed"
                ),
                "address": hex(address),
                "operand_index": operand_index,
                "expected_offset": hex(expected_offset),
                "observed_offset": hex(observed_offset),
                "before": before,
                "after": after,
            }
        )
    return results


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    dependency_headers = [
        header_path.with_name(name) for name in DEPENDENCY_HEADER_NAMES
    ]
    dependency_marker_failures = []
    for dependency_header in dependency_headers:
        if not dependency_header.is_file():
            dependency_marker_failures.append(
                {
                    "header": str(dependency_header),
                    "reason": "missing_dependency_header",
                }
            )
            continue
        dependency_text = dependency_header.read_text(encoding="utf-8")
        markers = DEPENDENCY_OWNER_MARKERS[dependency_header.name]
        missing = [marker for marker in markers if marker not in dependency_text]
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
                    "failed": [{"reason": "noncanonical_snail_owner_header"}],
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
        if (
            address == idc.BADADDR
            or ida_funcs.get_func_start(address) == idc.BADADDR
        ):
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

    subhover_player_root_offset = _normalize_subhover_player_root_offset()
    if subhover_player_root_offset["status"] == "failed":
        failed.append(
            {
                "selector": "initialize_jetpack_gauge",
                "root_offset_operand": subhover_player_root_offset,
            }
        )
    ida_hexrays.mark_cfunc_dirty(0x43A930, True)

    invincible_root_offsets = _normalize_invincible_root_offsets()
    failed_invincible_root_offsets = [
        result for result in invincible_root_offsets if result["status"] == "failed"
    ]
    if failed_invincible_root_offsets:
        failed.append(
            {
                "selector": "update_invincible_shell",
                "root_offset_operands": failed_invincible_root_offsets,
            }
        )
    ida_hexrays.mark_cfunc_dirty(0x444B50, True)

    hotspot_lvars = [
        _sync_named_lvar(
            selector,
            expected_name,
            declaration,
            definition_address,
        )
        for selector, expected_name, declaration, definition_address in (
            HOTSPOT_LVAR_SPECS
        )
    ]
    failed.extend(
        {"hotspot_lvar": hotspot_lvar}
        for hotspot_lvar in hotspot_lvars
        if hotspot_lvar.get("status") == "failed"
    )
    jetpack_lvars = [
        _sync_named_lvar(
            selector,
            expected_name,
            declaration,
            definition_address,
            expected_stack,
        )
        for (
            selector,
            expected_name,
            declaration,
            definition_address,
            expected_stack,
        ) in JETPACK_LVAR_SPECS
    ]
    failed.extend(
        {"jetpack_lvar": jetpack_lvar}
        for jetpack_lvar in jetpack_lvars
        if jetpack_lvar.get("status") == "failed"
    )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "dependency_parse_results": dependency_parse_results,
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "subhover_player_root_offset": subhover_player_root_offset,
                "invincible_root_offsets": invincible_root_offsets,
                "hotspot_lvars": hotspot_lvars,
                "jetpack_lvars": jetpack_lvars,
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
        print("usage: apply_snail_presentation_types.py <header-path>", file=sys.stderr)
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
