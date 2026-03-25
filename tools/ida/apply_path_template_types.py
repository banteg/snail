import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_pro
import idc


TRUSTED_DECLARATIONS = [
    (
        "allocate_path_nodes",
        "void* __fastcall allocate_path_nodes(PathTemplate* self);",
    ),
    (
        "finalize_path_template_record",
        "int32_t __fastcall finalize_path_template_record(PathTemplate* self);",
    ),
    (
        "mirror_path_template_pair_x",
        "int32_t __thiscall mirror_path_template_pair_x(PathTemplate* self, PathTemplate* source);",
    ),
    (
        "request_object_vertices",
        "int32_t* __thiscall request_object_vertices(PathTemplateStripMesh* mesh, int32_t vertex_count);",
    ),
    (
        "request_object_vertex_colours",
        "int32_t* __fastcall request_object_vertex_colours(PathTemplateStripMesh* mesh);",
    ),
    (
        "request_object_facequads",
        "void __thiscall request_object_facequads(PathTemplateStripMesh* mesh, int32_t facequad_count);",
    ),
    (
        "initialize_looptheloop_path_template_pair",
        "int32_t __thiscall initialize_looptheloop_path_template_pair(PathTemplate* self, float arg2, int32_t arg3, char* arg4, char* arg5);",
    ),
    (
        "initialize_loopout_path_template_pair",
        "int32_t __thiscall initialize_loopout_path_template_pair(PathTemplate* self, float arg2, int32_t arg3, char* arg4, char* arg5);",
    ),
    (
        "initialize_detour_path_template_pair",
        "int32_t __thiscall initialize_detour_path_template_pair(PathTemplate* self, int32_t arg2, char* arg3, char* arg4);",
    ),
    (
        "initialize_supertramp_path_template_pair",
        "int32_t __thiscall initialize_supertramp_path_template_pair(PathTemplate* self, float arg2, int32_t arg3, char* arg4, char* arg5, char* arg6);",
    ),
    (
        "initialize_kind42_path_template_pair",
        "int32_t __thiscall initialize_kind42_path_template_pair(PathTemplate* self, int32_t arg2, char* arg3, char* arg4);",
    ),
    (
        "initialize_halfpipe_path_template_pair",
        "int32_t __thiscall initialize_halfpipe_path_template_pair(PathTemplate* self, float arg2, float arg3, int32_t arg4, char* arg5, char* arg6);",
    ),
]


def _resolve_function(selector: str) -> tuple[int | None, str]:
    if selector.startswith("0x"):
        address = int(selector, 16)
        name = idc.get_func_name(address) or selector
        return address, name

    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    missing = []
    failed = []

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        current_type = idc.get_type(address)
        normalized_current = _normalize_type_text(current_type)

        if normalized_current == expected_observed:
            unchanged += 1
            continue

        if not idc.SetType(address, declaration):
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "reason": "set_type_failed",
                }
            )
            continue

        observed = idc.get_type(address)
        normalized_observed = _normalize_type_text(observed)
        if normalized_observed != expected_observed:
            failed.append(
                {
                    "selector": selector,
                    "address": hex(address),
                    "declaration": declaration,
                    "observed": observed,
                    "reason": "verification_failed",
                }
            )
            continue

        applied += 1

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "applied": applied,
                "unchanged": unchanged,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )

    if parse_errors or failed or missing:
        return 1
    return 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_path_template_types.py <header-path>", file=sys.stderr)
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
