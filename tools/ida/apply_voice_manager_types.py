from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc


TRUSTED_NAMES = (
    (0x448DF0, "initialize_voice_set"),
    (0x448E60, "shuffle_voice_set"),
    (0x448EC0, "reset_voice_manager"),
    (0x448EE0, "initialize_voice_manager"),
    (0x4492A0, "update_voice_manager"),
    (0x4492D0, "play_voice_manager"),
    (0x449360, "update_voice_set"),
    (0x449390, "play_voice_set"),
    (0x449410, "is_voice_playing"),
    (0x751498, "g_voice_manager"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_voice_set",
        "void __thiscall initialize_voice_set(VoiceSet* set, int32_t count);",
    ),
    ("shuffle_voice_set", "void __thiscall shuffle_voice_set(VoiceSet* set);"),
    (
        "reset_voice_manager",
        "void __thiscall reset_voice_manager(VoiceManager* manager);",
    ),
    (
        "initialize_voice_manager",
        "void __thiscall initialize_voice_manager(VoiceManager* manager);",
    ),
    (
        "update_voice_manager",
        "void __thiscall update_voice_manager(VoiceManager* manager);",
    ),
    (
        "play_voice_manager",
        "bool __thiscall play_voice_manager(VoiceManager* manager, int32_t set_id, uint32_t mode, int32_t sample_override);",
    ),
    ("update_voice_set", "void __thiscall update_voice_set(VoiceSet* set);"),
    (
        "play_voice_set",
        "bool __thiscall play_voice_set(VoiceSet* set, int32_t sample_override);",
    ),
    (
        "is_voice_playing",
        "int32_t __thiscall is_voice_playing(VoiceManager* manager);",
    ),
)

TRUSTED_DATA_DECLARATIONS = (
    (0x751498, "g_voice_manager", "VoiceManager g_voice_manager;"),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct VoiceSet {",
    "typedef struct VoiceManager {",
    "VoiceSet sets[16];",
    "extern VoiceManager g_voice_manager;",
)

EXPECTED_OWNER_SIZES = {
    "VoiceSet": 0x18,
    "VoiceManager": 0x188,
}


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


def _data_declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(rf"\b{re.escape(selector)}\b", "", declaration, count=1)
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
                    "failed": [{"reason": "noncanonical_voice_manager_header"}],
                },
                indent=2,
            )
        )
        return 1

    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE | idc.PT_REPLACE)
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
            failed.append({"selector": selector, "reason": "set_data_type_failed"})
            continue

        observed = idc.get_type(address)
        if _normalize_type_text(observed) != expected:
            failed.append(
                {
                    "selector": selector,
                    "reason": "data_verification_failed",
                    "observed": observed,
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
                "owner_sizes": owner_sizes,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
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
        print("usage: apply_voice_manager_types.py <header-path>", file=sys.stderr)
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
