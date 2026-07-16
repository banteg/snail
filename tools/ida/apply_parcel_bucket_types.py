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


TRUSTED_NAMES = (
    (0x53D190, "g_zero_parcel_buckets"),
    (0x643390, "g_zero_parcel_bucket_count_lane_end"),
    (0x6447E8, "g_parcel_group_survival_0"),
    (0x6487E8, "g_parcel_set_buckets"),
)

TRUSTED_DATA_DECLARATIONS = (
    (
        0x53D190,
        "g_zero_parcel_buckets",
        "ParcelBucket g_zero_parcel_buckets[0x800];",
    ),
    (
        0x6447E8,
        "g_parcel_group_survival_0",
        "int32_t g_parcel_group_survival_0[0x1000];",
    ),
    (
        0x6487E8,
        "g_parcel_set_buckets",
        "ParcelBucket g_parcel_set_buckets[0x800];",
    ),
)

TRUSTED_FUNCTION_DECLARATIONS = (
    (
        "initialize_array_with_constructor",
        "void __stdcall initialize_array_with_constructor(void *base, int32_t stride, int32_t count, void *(__thiscall *constructor)(void *slot));",
    ),
    (
        "noop_runtime_slot_constructor",
        "void *__thiscall noop_runtime_slot_constructor(void *slot);",
    ),
    (
        "initialize_parcel_set_bucket_pool",
        "void __cdecl initialize_parcel_set_bucket_pool(void);",
    ),
    (
        "initialize_zero_parcel_bucket_pool",
        "void __cdecl initialize_zero_parcel_bucket_pool(void);",
    ),
    (
        "place_parcels_on_track",
        "void __thiscall place_parcels_on_track(SubgameRuntime *game);",
    ),
    (
        "place_challenge_parcels_on_track",
        "void __thiscall place_challenge_parcels_on_track(SubgameRuntime *game);",
    ),
)

DIRTY_FUNCTIONS = (
    0x401000,
    0x408600,
    0x443870,
    0x4438B0,
    0x4438E0,
    0x444240,
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\bint32_t\b", "int", normalized)
    normalized = re.sub(r"\s+__cdecl\b", "", normalized)
    normalized = normalized.replace("(void)", "()")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = re.sub(r"\s*\(\s*", "(", normalized)
    normalized = re.sub(r"\s*\)\s*", ")", normalized)
    normalized = re.sub(r"\s*,\s*", ", ", normalized)
    normalized = re.sub(r"\s*\*\s*", " *", normalized)
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
    normalized = re.sub(
        r"\[(0x[0-9a-fA-F]+|\d+)\]",
        lambda match: f"[{int(match.group(1), 0)}]",
        normalized,
    )
    return normalized.strip()


def _function_declaration_to_observed_type(
    selector: str, declaration: str
) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1)
    return _normalize_type_text(unnamed) or ""


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\[|;)", "", declaration, count=1
    )
    return _normalize_type_text(unnamed) or ""


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    renamed = 0
    names_unchanged = 0
    data_applied = 0
    data_unchanged = 0
    functions_applied = 0
    functions_unchanged = 0
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

    for selector, declaration in TRUSTED_FUNCTION_DECLARATIONS:
        address = idc.get_name_ea_simple(selector)
        if address == idc.BADADDR or ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "reason": "missing_function"})
            continue
        expected = _function_declaration_to_observed_type(selector, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            functions_unchanged += 1
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
                    "expected": expected,
                }
            )
            continue
        functions_applied += 1

    ida_auto.auto_wait()
    for address in DIRTY_FUNCTIONS:
        ida_hexrays.mark_cfunc_dirty(address, True)

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "data_applied": data_applied,
                "data_unchanged": data_unchanged,
                "functions_applied": functions_applied,
                "functions_unchanged": functions_unchanged,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or failed or missing else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) != 2:
        print("usage: apply_parcel_bucket_types.py <header-path>", file=sys.stderr)
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
