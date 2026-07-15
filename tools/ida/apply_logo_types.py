import json
import pathlib
import re
import sys

import ida_funcs
import ida_kernwin
import ida_name
import ida_pro
import idc


TRUSTED_NAMES = [
    (0x497310, "g_logo_letter_vtable"),
]

TRUSTED_DECLARATIONS = [
    (
        "initialize_intro_logo_renderable",
        "LogoLetter* __thiscall initialize_intro_logo_renderable(LogoLetter* letter);",
    ),
    ("open_logo", "int32_t __thiscall open_logo(Logo* logo);"),
    (
        "initialize_intro_screen",
        "void __thiscall initialize_intro_screen(Logo* logo, char* file_name);",
    ),
    (
        "destroy_intro_screen",
        "void __thiscall destroy_intro_screen(Logo* logo);",
    ),
    ("update_intro_screen", "void __thiscall update_intro_screen(Logo* logo);"),
    (
        "update_intro_logo_renderable",
        "void __thiscall update_intro_logo_renderable(LogoLetter* letter);",
    ),
]


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


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)
    renamed = 0
    names_unchanged = 0
    applied = 0
    unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        if idc.get_name(address) == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            failed.append({"address": hex(address), "name": name, "reason": "rename_failed"})
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
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "applied": applied,
                "unchanged": unchanged,
                "missing": missing,
                "failed": failed,
            },
            indent=2,
        )
    )
    return 1 if parse_errors or failed or missing else 0


def main() -> None:
    argv = list(idc.ARGV)
    if len(argv) < 2:
        print("usage: apply_logo_types.py <header-path>", file=sys.stderr)
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
