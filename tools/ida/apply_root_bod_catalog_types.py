from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


EXPECTED_OWNER_SIZES = {
    "Object": 0xDC,
    "RootBodCatalogEntry": 0x38,
    "RootTrackCornerBodBank": 0xE0,
    "RootTrackSliceBodBank": 0x1C0,
    "RootTrackFringeBodCatalog": 0x3F00,
    "RootBodCatalog": 0x4D00,
    "RootTrackSliceTripletStrideView": 0x44B48,
    "RootFringeCatalogObjectStrideCursor": 0x38,
}

TRUSTED_DECLARATIONS = (
    (
        "initialize_game_assets_and_world",
        "uint8_t __thiscall initialize_game_assets_and_world(GameRoot* game);",
    ),
)

TRACK_SLICE_TRIPLET_LVAR = {
    "selector": "initialize_game_assets_and_world",
    "definition_address": 0x40B76A,
    "accepted_names": {"v18", "track_slice_triplet_stride_view"},
    "accepted_types": {"char *", "RootTrackSliceTripletStrideView *"},
    "target_name": "track_slice_triplet_stride_view",
    "target_struct_name": "RootTrackSliceTripletStrideView",
    "is_stack": False,
}

FRINGE_CATALOG_CURSOR_LVARS = (
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40FFE0,
        "accepted_names": {
            "p_object",
            "fringe_orientation_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "RootFringeCatalogObjectStrideCursor *",
        },
        "target_name": "fringe_orientation_object_cursor",
        "target_struct_name": "RootFringeCatalogObjectStrideCursor",
        "is_stack": False,
    },
    {
        "selector": "initialize_game_assets_and_world",
        "definition_address": 0x40FFEE,
        "accepted_names": {
            "v296",
            "fringe_entry_object_cursor",
        },
        "accepted_types": {
            "Object **",
            "RootFringeCatalogObjectStrideCursor *",
        },
        "target_name": "fringe_entry_object_cursor",
        "target_struct_name": "RootFringeCatalogObjectStrideCursor",
        "is_stack": False,
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


def _sync_exact_struct_pointer_lvar(
    spec: dict[str, object],
) -> dict[str, object]:
    """Persist one exact Hex-Rays local without broad candidate matching."""
    selector = str(spec["selector"])
    definition_address = int(spec["definition_address"])
    accepted_names = set(spec["accepted_names"])
    accepted_types = {
        _normalize_struct_pointer_type(value)
        for value in spec["accepted_types"]
    }
    target_name = str(spec["target_name"])
    target_struct_name = str(spec["target_struct_name"])
    is_stack = bool(spec["is_stack"])

    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR or ida_funcs.get_func(address) is None:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    ida_hexrays.mark_cfunc_dirty(address, True)
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and bool(lvar.is_stk_var()) == is_stack
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
            "is_stack": is_stack,
        }

    lvar = candidates[0]
    target_pointer_type = _normalize_struct_pointer_type(
        f"{target_struct_name} *"
    )
    observed_type = _normalize_struct_pointer_type(str(lvar.type()))
    if lvar.name == target_name and observed_type == target_pointer_type:
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
            "is_stack": bool(lvar.is_stk_var()),
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_struct_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": f"missing_{target_name}_target_type",
            "selector": selector,
            "target_struct_name": target_struct_name,
        }
    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(target_type):
        return {
            "status": "failed",
            "reason": f"create_{target_name}_pointer_type_failed",
            "selector": selector,
            "target_struct_name": target_struct_name,
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
            "target_name": target_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and bool(candidate.is_stk_var()) == is_stack
        and candidate.defea == definition_address
        and candidate.name == target_name
    ]
    verified_type = (
        _normalize_struct_pointer_type(str(verified[0].type()))
        if len(verified) == 1
        else None
    )
    if len(verified) != 1 or verified_type != target_pointer_type:
        return {
            "status": "failed",
            "reason": f"{target_name}_readback_failed",
            "selector": selector,
            "candidate_count": len(verified),
            "observed_type": verified_type,
            "target_type": target_pointer_type,
            "target_name": target_name,
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": before_name,
        "before_type": before_type,
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
        "is_stack": bool(verified[0].is_stk_var()),
    }


def _sync_track_slice_triplet_lvar() -> dict[str, object]:
    """Persist the exact register-backed root-relative catalog lifetime."""
    return _sync_exact_struct_pointer_lvar(TRACK_SLICE_TRIPLET_LVAR)


def _sync_fringe_catalog_cursor_lvars() -> list[dict[str, object]]:
    """Persist the exact outer and inner field-stride cursor identities."""
    return [
        _sync_exact_struct_pointer_lvar(spec)
        for spec in FRINGE_CATALOG_CURSOR_LVARS
    ]


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    owner_sizes = {name: _named_struct_size(name) for name in EXPECTED_OWNER_SIZES}
    failed = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected,
            "observed": owner_sizes[name],
        }
        for name, expected in EXPECTED_OWNER_SIZES.items()
        if owner_sizes[name] != expected
    ]
    missing = []
    applied = 0
    unchanged = 0

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

    track_slice_triplet_lvar = {
        "status": "skipped",
        "reason": "owner_or_prototype_preflight_failed",
    }
    if not parse_errors and not failed:
        track_slice_triplet_lvar = _sync_track_slice_triplet_lvar()
        if track_slice_triplet_lvar.get("status") == "failed":
            failed.append(
                {
                    "selector": "track_slice_triplet_stride_view",
                    "lvar_replay": track_slice_triplet_lvar,
                }
            )

    fringe_catalog_cursor_lvars = [
        {
            "status": "skipped",
            "reason": "owner_or_prototype_preflight_failed",
            "target_name": str(spec["target_name"]),
        }
        for spec in FRINGE_CATALOG_CURSOR_LVARS
    ]
    if not parse_errors and not failed:
        fringe_catalog_cursor_lvars = _sync_fringe_catalog_cursor_lvars()
        for spec, lvar_replay in zip(
            FRINGE_CATALOG_CURSOR_LVARS,
            fringe_catalog_cursor_lvars,
            strict=True,
        ):
            if lvar_replay.get("status") == "failed":
                failed.append(
                    {
                        "selector": str(spec["target_name"]),
                        "lvar_replay": lvar_replay,
                    }
                )

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "applied": applied,
                "unchanged": unchanged,
                "track_slice_triplet_lvar": track_slice_triplet_lvar,
                "fringe_catalog_cursor_lvars": fringe_catalog_cursor_lvars,
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
        print("usage: apply_root_bod_catalog_types.py <header-path>", file=sys.stderr)
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
