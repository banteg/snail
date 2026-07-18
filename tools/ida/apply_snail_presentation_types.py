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
    (0x442E40, "release_snail_weapons"),
    (0x444600, "dispatch_cutscene_animation"),
    (0x4446E0, "set_weapon_animation"),
    (0x445CD0, "update_snail_skin"),
    (0x445D50, "build_snail_hotspots"),
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
        "release_snail_weapons",
        "void __thiscall release_snail_weapons(Snail* snail);",
    ),
    (
        "dispatch_cutscene_animation",
        "int32_t __thiscall dispatch_cutscene_animation(Snail* snail, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "set_weapon_animation",
        "void __thiscall set_weapon_animation(Weapon* weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags);",
    ),
    (
        "update_snail_skin",
        "void __thiscall update_snail_skin(Snail* snail);",
    ),
    (
        "build_snail_hotspots",
        "void __thiscall build_snail_hotspots(Snail* snail);",
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
    "Sprite": 0xB4,
    "RenderableBod": 0x80,
    "AnimManager": 0x48,
    "SubHover": 0x214,
    "Weapon": 0x3DC,
    "Invincible": 0xA4,
    "Snail": 0x19B4,
    "Player": 0x4364,
}

# The authored Player root displacement numerically lands on the tracked
# g_player_block offset symbol. Keep that evidence symbol, but render this one
# ADD operand as a number so Hex-Rays can fold GameRoot::subgame.player.
SUBHOVER_PLAYER_ROOT_OFFSET_OPERAND = (0x43A953, 1, 0x42FD7C)


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

    subhover_player_root_offset = _normalize_subhover_player_root_offset()
    if subhover_player_root_offset["status"] == "failed":
        failed.append(
            {
                "selector": "initialize_jetpack_gauge",
                "root_offset_operand": subhover_player_root_offset,
            }
        )
    ida_hexrays.mark_cfunc_dirty(0x43A930, True)

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "dependency_parse_results": dependency_parse_results,
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "subhover_player_root_offset": subhover_player_root_offset,
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
