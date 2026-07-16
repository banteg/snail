from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_auto
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import idc


REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
FUNCTION_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"

TRUSTED_FUNCTION_NAMES = (
    (0x434980, "initialize_track_colour_bank_a_thunk"),
    (0x434990, "initialize_track_colour_bank_a"),
    (0x4349B0, "initialize_track_colour_banks_b_c_thunk"),
    (0x4349C0, "initialize_track_colour_banks_b_c"),
    (0x4349E0, "initialize_track_colour_bank_d_thunk"),
    (0x4349F0, "initialize_track_colour_bank_d"),
    (0x434A10, "initialize_track_colour_bank_e_thunk"),
    (0x434A20, "initialize_track_colour_bank_e"),
    (0x434A40, "initialize_track_colour_bank_f_thunk"),
    (0x434A50, "initialize_track_colour_bank_f"),
    (0x434A70, "initialize_track_colour_bank_g_thunk"),
    (0x434A80, "initialize_track_colour_bank_g"),
    (0x434AA0, "initialize_track_colour_bank_h_thunk"),
    (0x434AB0, "initialize_track_colour_bank_h"),
    (0x434AD0, "initialize_track_colour_bank_i_thunk"),
    (0x434AE0, "initialize_track_colour_bank_i"),
    (0x434B00, "initialize_track_colour_bank_j_thunk"),
    (0x434B10, "initialize_track_colour_bank_j"),
    (0x434B30, "initialize_track_colour_bank_k_thunk"),
    (0x434B40, "initialize_track_colour_bank_k"),
    (0x435D40, "build_track_colours"),
)

TRUSTED_FUNCTION_DECLARATIONS = tuple(
    (name, f"void __cdecl {name}(void);")
    for _address, name in TRUSTED_FUNCTION_NAMES
    if name != "build_track_colours"
) + (
    (
        "build_track_colours",
        "void __thiscall build_track_colours(SubgameRuntime *game);",
    ),
)

TRUSTED_NAMES = (
    (0x53C800, "g_loc_colour_lookup_path_worm"),
    (0x53CB30, "g_loc_colour_lookup_slide_1"),
    (0x53CE60, "g_loc_colour_lookup_wall"),
    (0x643198, "g_loc_colour_lookup_path_warp"),
    (0x6434C8, "g_loc_colour_lookup_trampoline"),
    (0x6437F8, "g_loc_colour_lookup_floor_slide_0"),
    (0x643E58, "g_loc_colour_lookup_path"),
    (0x644188, "g_loc_colour_lookup_empty"),
    (0x6444B8, "g_loc_colour_lookup_ramp"),
    (0x74E7E8, "g_loc_colour_lookup_check_black"),
)

# IDA represents 0x643b28 as the `slide_0` member inside the complete owner at
# 0x6437f8. A competing top-level label is deleted when that struct type is
# applied, so the replay verifies the interior remains label-free instead of
# continually recreating an alias that IDA cannot retain.
INTERIOR_FIELD = (0x643B28, "g_loc_colour_lookup_slide_0")

# Isolated banks deliberately receive only a narrow base tColour type. The
# complete PathWarp extent overlaps an independent parcel-loop sentinel. The
# combined Floor/Slide-0 allocation is non-overlapping and receives its proved
# complete owner type.
TRUSTED_DATA_DECLARATIONS = (
    (0x53C800, "g_loc_colour_lookup_path_worm", "tColour g_loc_colour_lookup_path_worm;"),
    (0x53CB30, "g_loc_colour_lookup_slide_1", "tColour g_loc_colour_lookup_slide_1;"),
    (0x53CE60, "g_loc_colour_lookup_wall", "tColour g_loc_colour_lookup_wall;"),
    (0x643198, "g_loc_colour_lookup_path_warp", "tColour g_loc_colour_lookup_path_warp;"),
    (0x6434C8, "g_loc_colour_lookup_trampoline", "tColour g_loc_colour_lookup_trampoline;"),
    (
        0x6437F8,
        "g_loc_colour_lookup_floor_slide_0",
        "TrackFloorSlideColourBanks g_loc_colour_lookup_floor_slide_0;",
    ),
    (0x643E58, "g_loc_colour_lookup_path", "tColour g_loc_colour_lookup_path;"),
    (0x644188, "g_loc_colour_lookup_empty", "tColour g_loc_colour_lookup_empty;"),
    (0x6444B8, "g_loc_colour_lookup_ramp", "tColour g_loc_colour_lookup_ramp;"),
    (
        0x74E7E8,
        "g_loc_colour_lookup_check_black",
        "tColour g_loc_colour_lookup_check_black;",
    ),
)

DIRTY_FUNCTIONS = (
    0x434990,
    0x4349C0,
    0x4349F0,
    0x434A20,
    0x434A50,
    0x434A80,
    0x434AB0,
    0x434AE0,
    0x434B10,
    0x434B40,
    0x435D40,
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+__cdecl\b", "", normalized)
    normalized = normalized.replace("(void)", "()")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    return normalized.strip()


def _function_declaration_to_observed_type(
    selector: str, declaration: str
) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _load_trusted_function_comments() -> tuple[tuple[int, str, str], ...]:
    raw = json.loads(FUNCTION_MANIFEST_PATH.read_text(encoding="utf-8"))
    by_address = {
        int(entry["address"], 0): entry
        for entry in raw["functions"]
        if isinstance(entry, dict) and isinstance(entry.get("address"), str)
    }
    comments = []
    for address, expected_name in TRUSTED_FUNCTION_NAMES:
        entry = by_address.get(address)
        if entry is None or entry.get("name") != expected_name:
            raise RuntimeError(
                f"function manifest mismatch at {address:#x}: {entry!r}"
            )
        description = entry.get("description")
        if isinstance(description, str) and description:
            comments.append((address, expected_name, description))
    return tuple(comments)


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    functions_applied = 0
    functions_unchanged = 0
    comments_updated = 0
    comments_unchanged = 0
    interior_name_removed = False
    failed = []

    for address, name in (*TRUSTED_FUNCTION_NAMES, *TRUSTED_NAMES):
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"address": hex(address), "selector": name, "reason": "rename_failed"}
            )
            continue
        renamed += 1

    for address, selector, description in _load_trusted_function_comments():
        function = ida_funcs.get_func(address)
        if function is None or function.start_ea != address:
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "reason": "missing_function_for_comment",
                }
            )
            continue
        if (ida_funcs.get_func_cmt(function, True) or "") == description:
            comments_unchanged += 1
            continue
        if not ida_funcs.set_func_cmt(function, description, True):
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "reason": "set_function_comment_failed",
                }
            )
            continue
        if (ida_funcs.get_func_cmt(function, True) or "") != description:
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
                    "reason": "function_comment_verification_failed",
                }
            )
            continue
        comments_updated += 1

    for selector, declaration in TRUSTED_FUNCTION_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            failed.append(
                {"selector": selector, "reason": "missing_function_for_type"}
            )
            continue
        expected = _function_declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            functions_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append({"selector": selector, "reason": "set_function_type_failed"})
            continue
        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "function_type_verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        functions_applied += 1

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected = _data_declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            data_unchanged += 1
            continue
        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "selector": selector,
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
                    "reason": "data_verification_failed",
                    "observed": observed,
                    "expected": expected,
                }
            )
            continue
        data_applied += 1

    ida_auto.auto_wait()
    for address in DIRTY_FUNCTIONS:
        ida_hexrays.mark_cfunc_dirty(address, True)

    interior_address, interior_field_name = INTERIOR_FIELD
    interior_name = idc.get_name(interior_address)
    if interior_name:
        if not idc.set_name(
            interior_address, "", ida_name.SN_NOWARN | ida_name.SN_FORCE
        ):
            failed.append(
                {
                    "address": hex(interior_address),
                    "selector": interior_field_name,
                    "observed": interior_name,
                    "reason": "interior_name_delete_failed",
                }
            )
        else:
            interior_name_removed = True
    if idc.get_name(interior_address):
        failed.append(
            {
                "address": hex(interior_address),
                "selector": interior_field_name,
                "observed": idc.get_name(interior_address),
                "reason": "interior_name_verification_failed",
            }
        )

    name_failures = [
        {
            "address": hex(address),
            "selector": name,
            "observed": idc.get_name(address),
            "reason": "name_verification_failed",
        }
        for address, name in (*TRUSTED_FUNCTION_NAMES, *TRUSTED_NAMES)
        if idc.get_name(address) != name
    ]
    failed.extend(name_failures)

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "comments_updated": comments_updated,
                "comments_unchanged": comments_unchanged,
                "functions_applied": functions_applied,
                "functions_unchanged": functions_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "interior_field": {
                    "address": hex(interior_address),
                    "name": interior_field_name,
                    "top_level_name": idc.get_name(interior_address),
                    "name_removed": interior_name_removed,
                },
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or failed else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_track_colour_bank_types.py <header-path>", file=sys.stderr)
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
