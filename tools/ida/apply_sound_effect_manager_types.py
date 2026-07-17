from __future__ import annotations

import json
import pathlib
import re
import sys

import ida_bytes
import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc


TRUSTED_NAMES = (
    (0x44DCB0, "initialize_sound_bank"),
    (0x44DCE0, "play_sound_effect_at_position"),
    (0x44DDE0, "play_sound_effect"),
    (0x44DE00, "play_sound_effect_scaled"),
    (0x44DE20, "play_warning_sample_backend"),
    (0x44DE30, "stop_warning_sample_handle"),
    (0x4A2140, "g_sound_bank_entries"),
    (0x78FF88, "g_sound_effect_manager"),
)

TRUSTED_DECLARATIONS = (
    (
        "initialize_sound_bank",
        "void __thiscall initialize_sound_bank(SoundEffectManager* manager, SoundBankEntry* entries);",
    ),
    (
        "play_sound_effect_at_position",
        "void __thiscall play_sound_effect_at_position(SoundEffectManager* manager, int32_t sound_id, Vec3* position);",
    ),
    (
        "play_sound_effect",
        "void __thiscall play_sound_effect(SoundEffectManager* manager, int32_t sound_id);",
    ),
    (
        "play_sound_effect_scaled",
        "void __thiscall play_sound_effect_scaled(SoundEffectManager* manager, int32_t sound_id, float gain);",
    ),
    (
        "play_warning_sample_backend",
        "int32_t __thiscall play_warning_sample_backend(SoundEffectManager* manager, int32_t sample_id);",
    ),
    (
        "stop_warning_sample_handle",
        "void __thiscall stop_warning_sample_handle(SoundEffectManager* manager, int32_t handle);",
    ),
)

TRUSTED_DATA_DECLARATIONS = (
    (
        0x4A2140,
        "g_sound_bank_entries",
        "SoundBankEntry g_sound_bank_entries[52];",
    ),
    (
        0x78FF88,
        "g_sound_effect_manager",
        "SoundEffectManager g_sound_effect_manager;",
    ),
)

REQUIRED_OWNER_MARKERS = (
    "typedef struct SoundEffectManager {",
    "typedef struct SoundBankEntry {",
    "extern SoundEffectManager g_sound_effect_manager;",
    "extern SoundBankEntry g_sound_bank_entries[52];",
)

EXPECTED_OWNER_SIZES = {
    "SoundEffectManager": 0x01,
    "SoundBankEntry": 0x0C,
}

TRUSTED_DATA_EXTENTS = (
    (0x4A2140, 0x270, "g_sound_bank_entries", "SoundBankEntry[52]"),
    (0x78FF88, 0x01, "g_sound_effect_manager", "SoundEffectManager"),
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
    normalized = re.sub(r"\s*\[\s*", "[", normalized)
    normalized = re.sub(r"\s*\]\s*", "]", normalized)
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


def _ensure_data_extent(
    address: int,
    size: int,
    expected_name: str,
    expected_type: str,
) -> dict[str, object]:
    item_head = ida_bytes.get_item_head(address)
    item_size = ida_bytes.get_item_size(item_head)
    if item_head == address and item_size == size:
        return {
            "status": "unchanged",
            "address": hex(address),
            "item_size": item_size,
        }

    observed_name = idc.get_name(item_head)
    observed_type = _normalize_type_text(idc.get_type(item_head))
    normalized_expected_type = _normalize_type_text(expected_type)
    if (
        item_head != address
        or item_size not in (1, 4)
        or observed_name != expected_name
        or observed_type != normalized_expected_type
    ):
        return {
            "status": "failed",
            "reason": "unexpected_data_extent_head",
            "address": hex(address),
            "expected_size": size,
            "expected_name": expected_name,
            "expected_type": normalized_expected_type,
            "observed_head": hex(item_head),
            "observed_size": item_size,
            "observed_name": observed_name,
            "observed_type": observed_type,
        }

    if not ida_bytes.create_byte(address, size, True):
        return {
            "status": "failed",
            "reason": "create_data_extent_failed",
            "address": hex(address),
            "expected_size": size,
        }

    verified_head = ida_bytes.get_item_head(address)
    verified_size = ida_bytes.get_item_size(verified_head)
    if verified_head != address or verified_size != size:
        return {
            "status": "failed",
            "reason": "data_extent_readback_failed",
            "address": hex(address),
            "expected_size": size,
            "observed_head": hex(verified_head),
            "observed_size": verified_size,
        }
    return {
        "status": "applied",
        "address": hex(address),
        "item_size": verified_size,
    }


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
                    "failed": [{"reason": "noncanonical_sound_manager_header"}],
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

    data_extents = [
        _ensure_data_extent(address, size, name, data_type)
        for address, size, name, data_type in TRUSTED_DATA_EXTENTS
    ]
    failed.extend(
        {"data_extent": result}
        for result in data_extents
        if result.get("status") == "failed"
    )
    if failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "owner_sizes": owner_sizes,
                    "data_extents": data_extents,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

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
                "data_extents": data_extents,
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
        print(
            "usage: apply_sound_effect_manager_types.py <header-path>",
            file=sys.stderr,
        )
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
