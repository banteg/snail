import json
import pathlib
import re
import sys

import ida_funcs
import ida_pro
import ida_typeinf
import idc


TRUSTED_DECLARATIONS = [
    (
        "zero_timer_counters",
        "void __thiscall zero_timer_counters(Time* time);",
    ),
    (
        "advance_timer_counters",
        "void __thiscall advance_timer_counters(Time* time, float delta_ticks);",
    ),
    (
        "update_banner",
        "void __thiscall update_banner(Banner* banner);",
    ),
    (
        "initialize_track_jetpack_pickup_runtime",
        "JetPack* __thiscall initialize_track_jetpack_pickup_runtime(JetPack* jetpack);",
    ),
    (
        "update_track_jetpack_pickup",
        "void __thiscall update_track_jetpack_pickup(JetPack* jetpack);",
    ),
    (
        "initialize_vapour",
        "void __thiscall initialize_vapour(Vapour* vapour, Object* unused, float half_width);",
    ),
    (
        "reset_vapour",
        "void __thiscall reset_vapour(Vapour* vapour, float* z_floor);",
    ),
    (
        "add_vapour_point",
        "void __thiscall add_vapour_point(Vapour* vapour, const TransformMatrix* point);",
    ),
    (
        "update_vapour",
        "void __thiscall update_vapour(Vapour* vapour);",
    ),
    (
        "initialize_enemy_manager",
        # Keep this ICF-shared one-store ABI coarse in IDA so the unrelated
        # tracked-allocation callsite is not assigned the registry owner.
        "void __thiscall initialize_enemy_manager(int* count_owner);",
    ),
    (
        "search_path_for_golb",
        "ContactTargetEntry* __thiscall search_path_for_golb(EnemyManager* manager, const Vec3* position);",
    ),
    (
        "append_subgame_contact_target",
        "void __thiscall append_subgame_contact_target(EnemyManager* manager, const Vec3* position, float radius, int kind, ContactTargetObject* object);",
    ),
    (
        "set_subgame_features",
        "int __thiscall set_subgame_features(SubgameRuntime* runtime);",
    ),
    (
        "switch_track_mirror",
        "bool __thiscall switch_track_mirror(SubgameRuntime* runtime);",
    ),
    (
        "rebuild_track_runtime_from_segments",
        "int __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* runtime, int level_index);",
    ),
    (
        "set_subgame_rate",
        "void __thiscall set_subgame_rate(SubgameRuntime* runtime, float rate);",
    ),
    (
        "calc_subgame_rate",
        "void __thiscall calc_subgame_rate(SubgameRuntime* runtime);",
    ),
    (
        "complete_subgame",
        "void __thiscall complete_subgame(SubgameRuntime* runtime, unsigned char completed);",
    ),
    (
        "initialize_track_parcel_runtime",
        "Parcel* __thiscall initialize_track_parcel_runtime(Parcel* parcel);",
    ),
    (
        "update_track_parcels",
        "void __thiscall update_track_parcels(ParcelManager* manager);",
    ),
    (
        "initialize_track_parcel_slots",
        "void __thiscall initialize_track_parcel_slots(ParcelManager* manager);",
    ),
    (
        "allocate_track_parcel_slot",
        "Parcel* __thiscall allocate_track_parcel_slot(ParcelManager* manager);",
    ),
    (
        "update_track_parcel",
        "void __thiscall update_track_parcel(Parcel* parcel);",
    ),
    (
        "spawn_track_parcel",
        "Parcel* __thiscall spawn_track_parcel(SubgameRuntime* runtime, Vec3* world_position, Player* source_player);",
    ),
    (
        "initialize_challenge_setup_screen",
        "int __thiscall initialize_challenge_setup_screen(GUI* gui);",
    ),
    (
        "destroy_challenge_setup_screen",
        "void __thiscall destroy_challenge_setup_screen(GUI* gui);",
    ),
    (
        "update_challenge_setup_screen",
        "int __thiscall update_challenge_setup_screen(GUI* gui);",
    ),
    (
        "format_time_trial_string",
        "char* __thiscall format_time_trial_string(TimeTrial* time_trial, Time* timer);",
    ),
    (
        "bind_subgame_owner",
        "SubgameRuntime* __thiscall bind_subgame_owner(SubgameOwnerLink* owner);",
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


def _named_struct_size(name: str) -> int | None:
    value = ida_typeinf.tinfo_t()
    if not value.get_named_type(None, name, ida_typeinf.BTF_STRUCT):
        return None
    return value.get_size()


def _sync_types(header_path: pathlib.Path) -> int:
    contact_header_path = header_path.with_name("contact_target_types.h")
    contact_parse_errors = idc.parse_decls(str(contact_header_path), idc.PT_FILE)
    parse_errors = contact_parse_errors + idc.parse_decls(str(header_path), idc.PT_FILE)

    applied = 0
    unchanged = 0
    missing = []
    failed = []

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
                "contact_header": str(contact_header_path),
                "type_sizes": {
                    "SubgameRuntime": _named_struct_size("SubgameRuntime"),
                    "EnemyManager": _named_struct_size("EnemyManager"),
                    "GUI": _named_struct_size("GUI"),
                    "Help": _named_struct_size("Help"),
                    "ThanksScreen": _named_struct_size("ThanksScreen"),
                    "Galaxy": _named_struct_size("Galaxy"),
                    "Parcel": _named_struct_size("Parcel"),
                    "ParcelManager": _named_struct_size("ParcelManager"),
                    "Completion": _named_struct_size("Completion"),
                    "TimesUp": _named_struct_size("TimesUp"),
                },
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
        print("usage: apply_subgame_runtime_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
