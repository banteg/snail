from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


EXPECTED_BACKDROP_SIZE = 0x6CC

TRUSTED_DECLARATIONS = (
    (
        "set_backdrop_progress_fraction",
        "void __thiscall set_backdrop_progress_fraction(Backdrop* backdrop, float zoom);",
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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    backdrop_size = _named_struct_size("Backdrop")
    failed = []
    missing = []
    applied = 0
    unchanged = 0

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

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "backdrop_size": backdrop_size,
                "applied": applied,
                "unchanged": unchanged,
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
