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


EXPECTED_BOD_BASE_SIZE = 0x38
EXPECTED_BACKDROP_DISTORT_CELL_SIZE = 0x18
EXPECTED_BACKDROP_SIZE = 0x6CC

TRUSTED_NAMES = (
    (0x410720, "initialize_game_last"),
    (0x410C30, "set_backdrop_zoom"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_game_last",
        "void __thiscall initialize_game_last(GameRoot* game);",
    ),
    (
        "set_backdrop_zoom",
        "void __thiscall set_backdrop_zoom(Backdrop* backdrop, float zoom);",
    ),
    (
        "set_backdrop_distort",
        "void __thiscall set_backdrop_distort(Backdrop* backdrop, float distort);",
    ),
    (
        "change_backdrop",
        "void __thiscall change_backdrop(Backdrop* backdrop, LandscapeScriptRecord* record, uint8_t flip);",
    ),
    (
        "change_backdrop_real",
        "void __thiscall change_backdrop_real(Backdrop* backdrop);",
    ),
    (
        "initialize_backdrop",
        "void __thiscall initialize_backdrop(Backdrop* backdrop, int32_t last_mode);",
    ),
    (
        "set_backdrop_texture_target",
        "void __thiscall set_backdrop_texture_target(Backdrop* backdrop, int32_t world);",
    ),
    (
        "render_backdrop",
        "void __thiscall render_backdrop(Backdrop* backdrop);",
    ),
    (
        "update_backdrop",
        "int32_t __thiscall update_backdrop(Backdrop* backdrop);",
    ),
)

ROOT_INITIALIZER_DIRTY_FUNCTIONS = (
    0x406DC0,  # game_startup_and_main_loop
    0x410720,  # initialize_game_last
)

DISTORT_CELL_LVARS = (
    {
        "definition_address": 0x41130A,
        "accepted_names": {"v2", "column_start"},
        "accepted_types": {"BackdropDistortCell *"},
        "target_name": "column_start",
    },
    {
        "definition_address": 0x411315,
        "accepted_names": {"p_phase", "v3", "cell"},
        "accepted_types": {"float *", "BackdropDistortCell *"},
        "target_name": "cell",
    },
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
    return normalized.strip()


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _normalize_struct_pointer_type(value: str | None) -> str:
    normalized = (_normalize_type_text(value) or "").removeprefix("struct ")
    return re.sub(r"\s+", "", normalized)


def _sync_distort_cell_lvar(spec: dict[str, object]) -> dict[str, object]:
    """Persist one exact borrowed BackdropDistortCell register lifetime."""
    selector = "update_backdrop"
    definition_address = int(spec["definition_address"])
    accepted_names = set(spec["accepted_names"])
    accepted_types = {
        _normalize_struct_pointer_type(value)
        for value in spec["accepted_types"]
    }
    target_name = str(spec["target_name"])
    target_type_text = _normalize_struct_pointer_type("BackdropDistortCell *")

    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and _normalize_struct_pointer_type(str(lvar.type())) in accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": f"unexpected_{target_name}_candidates",
            "selector": selector,
            "candidate_count": len(candidates),
            "definition_address": hex(definition_address),
        }

    lvar = candidates[0]
    observed_type = _normalize_struct_pointer_type(str(lvar.type()))
    if lvar.name == target_name and observed_type == target_type_text:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
        }

    cell_type = ida_typeinf.tinfo_t()
    if not cell_type.get_named_type(
        None,
        "BackdropDistortCell",
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_backdrop_distort_cell_type",
            "selector": selector,
        }
    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(cell_type):
        return {
            "status": "failed",
            "reason": "create_backdrop_distort_cell_pointer_failed",
            "selector": selector,
        }

    before_name = lvar.name
    before_type = str(lvar.type())
    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": f"modify_{target_name}_failed",
            "selector": selector,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and not candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.name == target_name
        and _normalize_struct_pointer_type(str(candidate.type()))
        == target_type_text
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": f"{target_name}_readback_failed",
            "selector": selector,
            "candidate_count": len(verified),
            "definition_address": hex(definition_address),
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
    failed = []
    missing = []
    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    bod_base_size = _named_struct_size("BodBase")

    if bod_base_size != EXPECTED_BOD_BASE_SIZE:
        failed.append(
            {
                "selector": "BodBase",
                "reason": "dependency_size_mismatch",
                "expected": EXPECTED_BOD_BASE_SIZE,
                "observed": bod_base_size,
            }
        )

    parse_errors = (
        0 if failed else idc.parse_decls(str(header_path), idc.PT_FILE)
    )
    distort_cell_size = _named_struct_size("BackdropDistortCell")
    backdrop_size = _named_struct_size("Backdrop")

    if distort_cell_size != EXPECTED_BACKDROP_DISTORT_CELL_SIZE:
        failed.append(
            {
                "selector": "BackdropDistortCell",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_BACKDROP_DISTORT_CELL_SIZE,
                "observed": distort_cell_size,
            }
        )
    if backdrop_size != EXPECTED_BACKDROP_SIZE:
        failed.append(
            {
                "selector": "Backdrop",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_BACKDROP_SIZE,
                "observed": backdrop_size,
            }
        )

    if not parse_errors and not failed:
        for address, name in TRUSTED_NAMES:
            if idc.get_name(address) == name:
                names_unchanged += 1
                continue
            if not idc.set_name(
                address,
                name,
                ida_name.SN_NOWARN | ida_name.SN_FORCE,
            ):
                failed.append(
                    {
                        "selector": name,
                        "address": hex(address),
                        "reason": "rename_failed",
                    }
                )
                continue
            renamed += 1

    if not parse_errors and not failed:
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

    distort_cell_lvars = []
    if not parse_errors and not failed:
        distort_cell_lvars = [
            _sync_distort_cell_lvar(spec)
            for spec in DISTORT_CELL_LVARS
        ]
        for spec, lvar_replay in zip(DISTORT_CELL_LVARS, distort_cell_lvars):
            if lvar_replay.get("status") == "failed":
                failed.append(
                    {
                        "selector": "update_backdrop",
                        "lvar": spec["target_name"],
                        "lvar_replay": lvar_replay,
                    }
                )

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    dirty_functions = []
    if not parse_errors and not failed:
        for address in ROOT_INITIALIZER_DIRTY_FUNCTIONS:
            if ida_funcs.get_func(address) is None:
                failed.append(
                    {
                        "selector": hex(address),
                        "reason": "missing_dirty_function",
                    }
                )
                continue
            ida_hexrays.mark_cfunc_dirty(address, True)
            dirty_functions.append(hex(address))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "bod_base_size": bod_base_size,
                "distort_cell_size": distort_cell_size,
                "backdrop_size": backdrop_size,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "distort_cell_lvars": distort_cell_lvars,
                "game_root_owner_graph": game_root_owner_graph,
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
        print("usage: apply_backdrop_types.py <header-path>", file=sys.stderr)
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
