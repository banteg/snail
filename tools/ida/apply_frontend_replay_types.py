import json
import pathlib
import re
import sys

import ida_funcs
import ida_name
import ida_pro
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_NAMES = [
    (0x401130, "draw_frontend_widget"),
    (0x4034D0, "update_input_ok"),
    (0x403560, "initialize_input_ok"),
    (0x404030, "update_twinkle_manager"),
    (0x404070, "draw_twinkle"),
    (0x404080, "update_twinkle"),
]

TRUSTED_DECLARATIONS = [
    (
        "draw_frontend_widget",
        "void __thiscall draw_frontend_widget(FrontendWidget* widget);",
    ),
    (
        "initialize_frontend_sprite_button",
        "void __thiscall initialize_frontend_sprite_button(FrontendWidget* widget, uint32_t widget_flags, int32_t sprite, float x, float y, tColour* color, float anchor_x, int32_t layer);",
    ),
    (
        "update_input_ok",
        "void __thiscall update_input_ok(InputOkState* input_ok);",
    ),
    (
        "initialize_input_ok",
        "void __thiscall initialize_input_ok(InputOkState* input_ok);",
    ),
    (
        "update_twinkle_manager",
        "void __thiscall update_twinkle_manager(TwinkleManager* manager);",
    ),
    (
        "draw_twinkle",
        "void __thiscall draw_twinkle(Twinkle* twinkle);",
    ),
    (
        "update_twinkle",
        "void __thiscall update_twinkle(Twinkle* twinkle);",
    ),
    (
        "initialize_high_score_screen",
        "void __thiscall initialize_high_score_screen(HighScore* high_score, int selected_bank, int selected_rank);",
    ),
    (
        "destroy_high_score_screen",
        "void __thiscall destroy_high_score_screen(HighScore* high_score);",
    ),
    (
        "update_high_score_screen",
        "void __thiscall update_high_score_screen(HighScore* high_score);",
    ),
    (
        "exit_high_score_screen",
        "void __thiscall exit_high_score_screen(HighScore* high_score);",
    ),
    (
        "initialize_new_game_menu",
        "void __thiscall initialize_new_game_menu(Intro* intro);",
    ),
    (
        "update_new_game_menu",
        "void __thiscall update_new_game_menu(Intro* intro);",
    ),
]


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
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
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

    game_root_owner_graph = sync_game_root_owner_graph(require=False)
    if game_root_owner_graph.get("status") == "failed":
        failed.append({"selector": "GameRoot", "owner_graph": game_root_owner_graph})

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
                "game_root_owner_graph": game_root_owner_graph,
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
        print("usage: apply_frontend_replay_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
