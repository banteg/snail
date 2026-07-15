import json
import pathlib
import re
import sys

import ida_funcs
import ida_name
import ida_pro
import idc


TRUSTED_DECLARATIONS = [
    (
        "initialize_high_score_tables",
        "void __thiscall initialize_high_score_tables(SubHighScore* bank);",
    ),
    (
        "load_high_scores_from_file",
        "void __thiscall load_high_scores_from_file(SubHighScore* bank, char* file_name);",
    ),
    (
        "initialize_high_score_entry",
        "void __thiscall initialize_high_score_entry(SubSolution* record, int runtime_build_seed, int replay_level_index, int replay_speed_scalar_bits, unsigned int runtime_build_flags, int high_score_mode_tag, int route_or_rank_index);",
    ),
    (
        "add_arcade_high_score",
        "void __thiscall add_arcade_high_score(SubHighScore* bank, SubSolution* record, int level_arg);",
    ),
    (
        "add_survival_high_score",
        "void __thiscall add_survival_high_score(SubHighScore* bank, SubSolution* record);",
    ),
    (
        "add_time_trial_high_score",
        "void __thiscall add_time_trial_high_score(SubHighScore* bank, SubSolution* record, int route_index, unsigned char route_active);",
    ),
    (
        "mini_delete_high_score_entry",
        "void __thiscall mini_delete_high_score_entry(SubHighScore* bank, int rank);",
    ),
    (
        "save_high_scores_and_config",
        "char* __thiscall save_high_scores_and_config(SubHighScore* bank, unsigned char save_mask);",
    ),
]

TRUSTED_NAMES = [
    (0x417AF0, "mini_delete_high_score_entry"),
    (0x4DF904, "g_game_base"),
]

# 0x4DF9C0 is the selected-bank lane at g_runtime_config + 0xA8, inside
# IDA's existing aggregate data item. The reference manifest carries its
# field alias; idc.set_name cannot create a standalone name at that interior
# address.


def _resolve_function(selector: str) -> tuple[int | None, str]:
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return None, selector
    return address, selector


def _normalize_type_text(value: str | None) -> str | None:
    if value is None:
        return None
    normalized = value.strip().removesuffix(";")
    normalized = re.sub(r"\s+", " ", normalized)
    normalized = normalized.replace("unsigned __int8", "unsigned char")
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
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = []

    for address, name in TRUSTED_NAMES:
        current_name = idc.get_name(address)
        if current_name == name:
            names_unchanged += 1
            continue
        if not idc.set_name(address, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            existing_name_address = idc.get_name_ea_simple(name)
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "current_name": current_name,
                    "existing_name_address": (
                        None
                        if existing_name_address == idc.BADADDR
                        else hex(existing_name_address)
                    ),
                    "reason": "rename_failed",
                }
            )
            continue
        renamed += 1

    for selector, declaration in TRUSTED_DECLARATIONS:
        address, _name = _resolve_function(selector)
        if address is None:
            missing.append({"selector": selector, "reason": "missing_symbol"})
            continue

        if ida_funcs.get_func(address) is None:
            missing.append({"selector": selector, "address": hex(address), "reason": "missing_function"})
            continue

        expected_observed = _declaration_to_observed_type(selector, declaration)
        normalized_current = _normalize_type_text(idc.get_type(address))

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
                "renamed": renamed,
                "names_unchanged": names_unchanged,
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
        print("usage: apply_high_score_bank_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
