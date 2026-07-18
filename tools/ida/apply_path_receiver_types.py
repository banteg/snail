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
import ida_typeinf
import idc


TRUSTED_NAMES = (
    (0x42B9C0, "get_path_position_at_node"),
    (0x42CA90, "is_point_inside_track_attachment"),
)

TRUSTED_DECLARATIONS = (
    (
        "get_path_position_at_node",
        "void __thiscall get_path_position_at_node(Path* self, Vec3* out, int32_t node, int32_t row_index, Vec3* local);",
    ),
    (
        "is_point_inside_track_attachment",
        "bool __thiscall is_point_inside_track_attachment(Path* self, Vec3 probe, Vec3 swept_motion, TrackRowCell* cell);",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct Vec3 {",
    "typedef struct TrackRowCell {",
    "typedef struct PathTemplateSample {",
    "typedef struct Path {",
    "void __thiscall get_path_position_at_node(",
    "bool __thiscall is_point_inside_track_attachment(",
)

EXPECTED_OWNER_SIZES = {
    "Vec3": 0xC,
    "TrackRowCell": 0x54,
    "PathTemplateSample": 0xA8,
    "Path": 0xA8,
}

REANALYSIS_FUNCTIONS = (
    0x42B9C0,  # get_path_position_at_node
    0x42CA90,  # is_point_inside_track_attachment
    0x4417D0,  # update_sub_lazer_projectile
    0x4438E0,  # place_parcels_on_track
    0x444240,  # place_challenge_parcels_on_track
)


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\bint32_t\b", "int", normalized)
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


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [{"reason": "noncanonical_path_owner_header"}],
                },
                indent=2,
            )
        )
        return 1

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
    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
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
    missing = []

    for address, name in TRUSTED_NAMES:
        if ida_funcs.get_func(address) is None:
            missing.append(
                {"selector": name, "address": hex(address), "reason": "missing_function"}
            )
            continue
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append(
                {"selector": name, "address": hex(address), "reason": "rename_failed"}
            )
            continue
        if idc.get_name(address) != name:
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "reason": "rename_readback_failed",
                    "observed": idc.get_name(address),
                }
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
                    "expected": expected,
                }
            )
            continue
        applied += 1

    ida_auto.auto_wait()
    dirty = []
    for address in REANALYSIS_FUNCTIONS:
        if ida_funcs.get_func(address) is None:
            missing.append(
                {"address": hex(address), "reason": "missing_reanalysis_function"}
            )
            continue
        ida_hexrays.mark_cfunc_dirty(address, True)
        dirty.append(hex(address))

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "owner_sizes": owner_sizes,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "dirty": dirty,
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
        print("usage: apply_path_receiver_types.py <header-path>", file=sys.stderr)
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
