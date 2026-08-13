import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_name
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402
from type_alias_migration import migrate_equivalent_struct_aliases  # noqa: E402


INTRO_OWNER_TYPE_ALIASES = (("Intro", "cRIntro", 0x48),)

EXPECTED_INTRO_OWNER_LAYOUT = {
    "size": 0x48,
    "members": {
        0x00: ("replay_attract_bank_cursor", "int32_t"),
        0x04: ("hide_for_replay_latch", "uint8_t"),
        0x08: ("attract_reset_progress", "float"),
        0x0C: ("attract_reset_step", "float"),
        0x10: ("replay_probe_progress", "float"),
        0x14: ("replay_probe_step", "float"),
        0x30: ("postal_button", "FrontendWidget *"),
        0x34: ("time_trial_button", "FrontendWidget *"),
        0x38: ("challenge_button", "FrontendWidget *"),
        0x3C: ("tutorial_button", "FrontendWidget *"),
        0x40: ("help_button", "FrontendWidget *"),
        0x44: ("back_button", "FrontendWidget *"),
    },
}


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
        "void __thiscall initialize_new_game_menu(cRIntro* intro);",
    ),
    (
        "update_new_game_menu",
        "void __thiscall update_new_game_menu(cRIntro* intro);",
    ),
]

# cRHighScore::AI borrows the active SubHighScore bank six times. Those
# GameRoot displacements also land inside the unrelated parcel-bucket data
# symbol, so IDA promotes the instructions to false global expressions and
# hides the already recovered GameRoot -> cRSubGame -> SubHighScore graph.
# Normalize only these exact operands; the parcel-bank symbol remains intact.
HIGH_SCORE_UPDATE_BANK_OFFSET_OPERANDS = (
    (0x4172C5, 1, 0x6FFAE0),
    (0x417377, 1, 0x6FFAE0),
    (0x41744F, 1, 0x6FFAE4),
    (0x41746F, 1, 0x6FFAE0),
    (0x4174C6, 1, 0x6FFAE0),
    (0x417527, 1, 0x6FFAE4),
)

HIGH_SCORE_LIFECYCLE_DIRTY_FUNCTIONS = {
    "destroy_high_score_screen": 0x417220,
    "update_high_score_screen": 0x417260,
    "exit_high_score_screen": 0x417B50,
}


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


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _intro_owner_layout_readback() -> dict[str, object]:
    type_name = "cRIntro"
    type_info = ida_typeinf.tinfo_t()
    if not type_info.get_named_type(None, type_name, ida_typeinf.BTF_STRUCT):
        return {
            "type": type_name,
            "observed": None,
            "failures": [{"type": type_name, "reason": "missing_named_struct"}],
        }

    members = ida_typeinf.udt_type_data_t()
    if not type_info.get_udt_details(members):
        return {
            "type": type_name,
            "observed": None,
            "failures": [{"type": type_name, "reason": "missing_struct_details"}],
        }

    observed_members = {
        int(member.offset) // 8: {
            "name": str(member.name),
            "type": _normalize_type_text(member.type.dstr()),
        }
        for member in members
    }
    observed = {
        "size": type_info.get_size(),
        "members": {
            hex(offset): observed_members.get(offset)
            for offset in EXPECTED_INTRO_OWNER_LAYOUT["members"]
        },
    }
    failures: list[dict[str, object]] = []
    if observed["size"] != EXPECTED_INTRO_OWNER_LAYOUT["size"]:
        failures.append(
            {
                "type": type_name,
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_INTRO_OWNER_LAYOUT["size"],
                "observed": observed["size"],
            }
        )
    for offset, (expected_name, expected_type) in EXPECTED_INTRO_OWNER_LAYOUT[
        "members"
    ].items():
        expected_member = {
            "name": expected_name,
            "type": _normalize_type_text(expected_type),
        }
        if observed_members.get(offset) != expected_member:
            failures.append(
                {
                    "type": type_name,
                    "offset": hex(offset),
                    "reason": "owner_member_mismatch",
                    "expected": expected_member,
                    "observed": observed_members.get(offset),
                }
            )
    return {"type": type_name, "observed": observed, "failures": failures}


def _normalize_root_offset_operands(
    operand_specs: tuple[tuple[int, int, int], ...],
) -> list[dict[str, object]]:
    results = []
    for address, operand_index, expected_offset in operand_specs:
        before = idc.print_operand(address, operand_index)
        idc.op_num(address, operand_index)
        after = idc.print_operand(address, operand_index)
        observed_offset = idc.get_operand_value(address, operand_index)
        normalized = (
            observed_offset == expected_offset
            and f"{expected_offset:X}H" in after.upper()
        )
        results.append(
            {
                "status": (
                    "applied"
                    if normalized and before != after
                    else "unchanged"
                    if normalized
                    else "failed"
                ),
                "address": hex(address),
                "operand_index": operand_index,
                "expected_offset": hex(expected_offset),
                "observed_offset": hex(observed_offset),
                "before": before,
                "after": after,
            }
        )
    return results


def _sync_high_score_lifecycle_owner_graph() -> dict[str, object]:
    operand_results = _normalize_root_offset_operands(
        HIGH_SCORE_UPDATE_BANK_OFFSET_OPERANDS
    )
    failed_operands = [
        result for result in operand_results if result["status"] == "failed"
    ]
    if failed_operands:
        return {
            "status": "failed",
            "reason": "high_score_bank_operand_normalization_failed",
            "operands": operand_results,
        }

    pseudocode = {}
    for selector, address in HIGH_SCORE_LIFECYCLE_DIRTY_FUNCTIONS.items():
        if ida_funcs.get_func(address) is None:
            return {
                "status": "failed",
                "reason": "high_score_lifecycle_function_missing",
                "selector": selector,
                "address": hex(address),
                "operands": operand_results,
            }
        ida_hexrays.mark_cfunc_dirty(address, True)
        try:
            pseudocode[selector] = str(ida_hexrays.decompile(address))
        except Exception as exc:
            return {
                "status": "failed",
                "reason": "high_score_lifecycle_decompile_failed",
                "selector": selector,
                "address": hex(address),
                "error": str(exc),
                "operands": operand_results,
            }

    required_owners = {
        "destroy_high_score_screen": (
            "&g_game_base->border_manager",
            "g_game_base->players[0].high_score_entry_pending",
            "g_game_base->players[0].selected_high_score_rank",
        ),
        "update_high_score_screen": (
            "g_game_base->subgame.sub_high_score.active_record_bank",
            "g_game_base->subgame.sub_high_score.active_record_count",
            "g_game_base->players[0].player_name",
            "g_game_base->players[0].frontend_state",
            "g_game_base->players[0].redispatch_requested",
            "g_game_base->subgame.selected_level_record",
            "g_game_base->subgame.selected_level_record_active",
            "g_game_base->subgame.selected_level_record_persistent",
            "g_game_base->subgame.selected_level_record_cursor",
            "g_game_base->subgame.level_mode",
        ),
        "exit_high_score_screen": (
            "g_game_base->subgame.level_mode",
            "g_game_base->players[0].frontend_state",
            "g_game_base->subgame.subgame_rebuild_selector",
            "g_game_base->players[0].redispatch_requested",
        ),
    }
    forbidden_renderings = {
        "destroy_high_score_screen": (
            "*((_BYTE *)g_game_base",
            "*((_DWORD *)g_game_base",
        ),
        "update_high_score_screen": (
            "g_parcel_set_buckets",
            "byte_6FFAE0",
            "unk_6FFAE4",
            "*((_BYTE *)g_game_base",
            "*((_DWORD *)g_game_base",
            "(char *)g_game_base +",
        ),
        "exit_high_score_screen": (
            "*((_BYTE *)g_game_base",
            "*((_DWORD *)g_game_base",
        ),
    }
    missing_owners = {
        selector: [
            owner for owner in owners if owner not in pseudocode[selector]
        ]
        for selector, owners in required_owners.items()
    }
    stale_renderings = {
        selector: [
            rendering
            for rendering in renderings
            if rendering in pseudocode[selector]
        ]
        for selector, renderings in forbidden_renderings.items()
    }
    missing_owners = {
        selector: missing
        for selector, missing in missing_owners.items()
        if missing
    }
    stale_renderings = {
        selector: stale
        for selector, stale in stale_renderings.items()
        if stale
    }
    if missing_owners or stale_renderings:
        return {
            "status": "failed",
            "reason": "high_score_lifecycle_owner_readback_failed",
            "missing_owners": missing_owners,
            "stale_renderings": stale_renderings,
            "operands": operand_results,
        }

    return {
        "status": (
            "applied"
            if any(result["status"] == "applied" for result in operand_results)
            else "unchanged"
        ),
        "operands": operand_results,
        "functions": {
            selector: hex(address)
            for selector, address in HIGH_SCORE_LIFECYCLE_DIRTY_FUNCTIONS.items()
        },
    }


def _sync_types(header_path: pathlib.Path) -> int:
    parse_errors = idc.parse_decls(str(header_path), idc.PT_FILE)

    type_alias_migrations = (
        []
        if parse_errors
        else migrate_equivalent_struct_aliases(INTRO_OWNER_TYPE_ALIASES)
    )
    type_alias_failures = [
        {
            "selector": result.get("old_name"),
            "reason": "type_alias_migration_failed",
            "result": result,
        }
        for result in type_alias_migrations
        if result.get("status") == "failed"
    ]
    intro_owner_layout_readback = (
        {"type": "cRIntro", "observed": None, "failures": []}
        if parse_errors or type_alias_failures
        else _intro_owner_layout_readback()
    )
    intro_owner_size = _named_struct_size("cRIntro")

    applied = 0
    unchanged = 0
    renamed = 0
    names_unchanged = 0
    missing = []
    failed = [
        *type_alias_failures,
        *intro_owner_layout_readback["failures"],
    ]
    if intro_owner_size != EXPECTED_INTRO_OWNER_LAYOUT["size"]:
        failed.append(
            {
                "selector": "cRIntro",
                "reason": "owner_size_mismatch",
                "expected": EXPECTED_INTRO_OWNER_LAYOUT["size"],
                "observed": intro_owner_size,
            }
        )

    if parse_errors or failed:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "type_alias_migrations": type_alias_migrations,
                    "intro_owner_size": intro_owner_size,
                    "intro_owner_layout_readback": intro_owner_layout_readback,
                    "applied": applied,
                    "unchanged": unchanged,
                    "renamed": renamed,
                    "names_unchanged": names_unchanged,
                    "game_root_owner_graph": {
                        "status": "skipped",
                        "reason": "owner_preflight_failed",
                    },
                    "high_score_lifecycle_owner_graph": {
                        "status": "skipped",
                        "reason": "owner_preflight_failed",
                    },
                    "missing": missing,
                    "failed": failed,
                },
                indent=2,
            )
        )
        return 1

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

    high_score_lifecycle_owner_graph = _sync_high_score_lifecycle_owner_graph()
    if high_score_lifecycle_owner_graph.get("status") == "failed":
        failed.append(
            {
                "selector": "cRHighScore lifecycle",
                "owner_graph": high_score_lifecycle_owner_graph,
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "parse_errors": parse_errors,
                "type_alias_migrations": type_alias_migrations,
                "intro_owner_size": intro_owner_size,
                "intro_owner_layout_readback": intro_owner_layout_readback,
                "applied": applied,
                "unchanged": unchanged,
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "game_root_owner_graph": game_root_owner_graph,
                "high_score_lifecycle_owner_graph": (
                    high_score_lifecycle_owner_graph
                ),
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
