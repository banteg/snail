from __future__ import annotations

import json
import pathlib
import re

import ida_auto
import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import idc

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
FUNCTION_MANIFEST_PATH = REPO_ROOT / "analysis/symbols/gameplay-functions.json"

TRUSTED_FUNCTIONS = (
    (
        0x44C8D0,
        "initialize_math_random_table",
        "void __cdecl initialize_math_random_table();",
    ),
    (
        0x44C930,
        "initialize_trigonometry_tables",
        "void __cdecl initialize_trigonometry_tables();",
    ),
    (
        0x44DC70,
        "random_signed_float_below",
        (
            "float __cdecl random_signed_float_below("
            "float upper_bound, char *tag);"
        ),
    ),
    (
        0x44DC90,
        "random_float_below",
        "float __cdecl random_float_below(float upper_bound, char *tag);",
    ),
)

# Keep this IDA-only: the matcher must continue keying the relocation as the
# literal `str:Mirror`, not as a curated data reference.
TRUSTED_STRING_NAMES = (
    (0x4A4C90, "g_rng_tag_mirror"),
)

DIRTY_FUNCTIONS = (
    *(address for address, _name, _declaration in TRUSTED_FUNCTIONS),
    0x406DC0,
    0x410730,
    0x435E60,
    0x435EB0,
    0x437EB0,
    0x438B90,
    0x439D50,
    0x43DA80,
    0x43DF10,
    0x43F200,
    0x43F930,
    0x441DD0,
    0x442E40,
    0x4438E0,
    0x444240,
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


def _declaration_to_observed_type(selector: str, declaration: str) -> str:
    unnamed = re.sub(
        rf"\b{re.escape(selector)}\s*(?=\()", "", declaration, count=1
    )
    return _normalize_type_text(unnamed) or ""


def _load_trusted_comments() -> dict[int, str]:
    raw = json.loads(FUNCTION_MANIFEST_PATH.read_text(encoding="utf-8"))
    comments: dict[int, str] = {}
    by_address = {
        int(entry["address"], 0): entry
        for entry in raw["functions"]
        if isinstance(entry, dict) and isinstance(entry.get("address"), str)
    }
    for address, expected_name, _declaration in TRUSTED_FUNCTIONS:
        entry = by_address.get(address)
        if entry is None or entry.get("name") != expected_name:
            raise RuntimeError(
                f"function manifest mismatch at {address:#x}: {entry!r}"
            )
        description = entry.get("description")
        if isinstance(description, str) and description:
            comments[address] = description
    return comments


def _sync_types() -> int:
    trusted_comments = _load_trusted_comments()
    renamed = 0
    names_unchanged = 0
    types_applied = 0
    types_unchanged = 0
    comments_updated = 0
    comments_unchanged = 0
    strings_renamed = 0
    string_names_unchanged = 0
    failed = []

    for address, name, declaration in TRUSTED_FUNCTIONS:
        if ida_funcs.get_func_start(address) != address:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "missing_function",
                }
            )
            continue

        if idc.get_name(address) == name:
            names_unchanged += 1
        elif idc.set_name(
            address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE
        ):
            renamed += 1
        else:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "rename_failed",
                }
            )
            continue

        expected = _declaration_to_observed_type(name, declaration)
        if _normalize_type_text(idc.get_type(address)) == expected:
            types_unchanged += 1
        elif not idc.SetType(address, declaration):
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "set_type_failed",
                }
            )
        else:
            observed = idc.get_type(address)
            if _normalize_type_text(observed) != expected:
                failed.append(
                    {
                        "address": hex(address),
                        "selector": name,
                        "reason": "type_verification_failed",
                        "observed": observed,
                        "expected": expected,
                    }
                )
            else:
                types_applied += 1

        description = trusted_comments.get(address)
        if description is None:
            continue
        if (ida_funcs.get_func_cmt_ea(address, True) or "") == description:
            comments_unchanged += 1
        elif ida_funcs.set_func_cmt_ea(address, description, True):
            comments_updated += 1
        else:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "set_function_comment_failed",
                }
            )

    for address, name in TRUSTED_STRING_NAMES:
        if idc.get_name(address) == name:
            string_names_unchanged += 1
        elif idc.set_name(
            address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE
        ):
            strings_renamed += 1
        else:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "string_rename_failed",
                }
            )

    ida_auto.auto_wait()
    for address in DIRTY_FUNCTIONS:
        ida_hexrays.mark_cfunc_dirty(address, True)

    for address, name, declaration in TRUSTED_FUNCTIONS:
        expected = _declaration_to_observed_type(name, declaration)
        if idc.get_name(address) != name:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "name_verification_failed",
                    "observed": idc.get_name(address),
                }
            )
        if _normalize_type_text(idc.get_type(address)) != expected:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "final_type_verification_failed",
                    "observed": idc.get_type(address),
                    "expected": expected,
                }
            )
    for address, name in TRUSTED_STRING_NAMES:
        if idc.get_name(address) != name:
            failed.append(
                {
                    "address": hex(address),
                    "selector": name,
                    "reason": "string_name_verification_failed",
                    "observed": idc.get_name(address),
                }
            )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "types_applied": types_applied,
                "types_unchanged": types_unchanged,
                "comments_updated": comments_updated,
                "comments_unchanged": comments_unchanged,
                "strings_renamed": strings_renamed,
                "string_names_unchanged": string_names_unchanged,
                "dirty_function_count": len(DIRTY_FUNCTIONS),
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if failed else 0


def main() -> None:
    exit_code = _sync_types()
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # noqa: BLE001  # pragma: no cover - IDA runtime
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
