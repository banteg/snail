import json
import pathlib
import re
import sys

import ida_funcs
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_DECLARATIONS = [
    (
        "initialize_galaxy_route_name_record",
        "GalaxyRouteNameRecord* __thiscall initialize_galaxy_route_name_record(GalaxyRouteNameRecord* record);",
    ),
    (
        "load_galaxy_layout",
        "void __thiscall load_galaxy_layout(Galaxy* galaxy);",
    ),
    (
        "destroy_galaxy",
        "void __thiscall destroy_galaxy(Galaxy* galaxy);",
    ),
    (
        "initialize_galaxy",
        "void __thiscall initialize_galaxy(Galaxy* galaxy);",
    ),
    (
        "update_galaxy",
        "int32_t __thiscall update_galaxy(Galaxy* galaxy);",
    ),
    (
        "draw_galaxy_line",
        "int32_t __thiscall draw_galaxy_line(Galaxy* galaxy, int32_t texture_id, float x0, float y0, float x1, float y1, float width, tColour* color);",
    ),
    (
        "update_galaxy_route_record",
        "void __thiscall update_galaxy_route_record(GalaxyRouteSlot* slot);",
    ),
    (
        "close_galaxy_route",
        "void __thiscall close_galaxy_route(Galaxy* galaxy);",
    ),
    (
        "open_galaxy_route",
        "void __thiscall open_galaxy_route(Galaxy* galaxy, int32_t selected_level_index);",
    ),
    (
        "galaxy_border_bound",
        "void __thiscall galaxy_border_bound(Galaxy* galaxy, float* min_x, float* max_x, float* min_y, float* max_y, FrontendWidget* widget);",
    ),
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
        "clear_active_landscape_entries",
        "void __thiscall clear_active_landscape_entries(LandscapeManager* manager);",
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
        "initialize_slug_hazard_runtime",
        "Slug* __thiscall initialize_slug_hazard_runtime(Slug* slug);",
    ),
    (
        "update_slug_voice_ai",
        "void __thiscall update_slug_voice_ai(Slug* slug);",
    ),
    (
        "play_slug_voice",
        "void __thiscall play_slug_voice(Slug* slug, int32_t sample_index);",
    ),
    (
        "hit_slug_hazard",
        "void __thiscall hit_slug_hazard(Slug* slug, int32_t damage);",
    ),
    (
        "explode_slug_hazard",
        "void __thiscall explode_slug_hazard(Slug* slug);",
    ),
    (
        "kill_slug_hazard",
        "void __thiscall kill_slug_hazard(Slug* slug);",
    ),
    (
        "update_slug_hazard_ai",
        "void __thiscall update_slug_hazard_ai(Slug* slug);",
    ),
    (
        "initialize_sub_lazer_runtime",
        "SubLazer* __thiscall initialize_sub_lazer_runtime(SubLazer* sub_lazer);",
    ),
    (
        "initialize_sub_lazer_pool",
        "void __thiscall initialize_sub_lazer_pool(SubLazerManager* manager);",
    ),
    (
        "spawn_sub_lazer_projectile",
        "void __thiscall spawn_sub_lazer_projectile(SubLazer* sub_lazer, const Vec3* origin, const Vec3* direction);",
    ),
    (
        "deactivate_sub_lazer_projectile",
        "void __thiscall deactivate_sub_lazer_projectile(SubLazer* sub_lazer);",
    ),
    (
        "update_sub_lazer_projectile",
        "void __thiscall update_sub_lazer_projectile(SubLazer* sub_lazer);",
    ),
    (
        "shoot_subgoldy",
        "void __thiscall shoot_subgoldy(SubLazerManager* manager, Vec3* origin, const Vec3* direction);",
    ),
    (
        "initialize_salt_hazard_runtime",
        "Salt* __thiscall initialize_salt_hazard_runtime(Salt* salt);",
    ),
    (
        "initialize_salt_hazard_pool",
        "int32_t* __thiscall initialize_salt_hazard_pool(SaltManager* manager);",
    ),
    (
        "spawn_salt_hazard",
        "int32_t __thiscall spawn_salt_hazard(SaltManager* manager, const Vec3* position);",
    ),
    (
        "update_salt_hazard",
        "void __thiscall update_salt_hazard(Salt* salt);",
    ),
    (
        "initialize_garbage_hazard",
        "SubGarbage* __thiscall initialize_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "update_garbage_hazard",
        "void __thiscall update_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "destroy_garbage_hazard",
        "SubGarbage* __thiscall destroy_garbage_hazard(SubGarbage* sub_garbage);",
    ),
    (
        "spawn_garbage_smoke_particle",
        "void __thiscall spawn_garbage_smoke_particle(SubGarbage* sub_garbage, Vec3* position, Vec3* velocity, Player* owner_player);",
    ),
    (
        "spawn_track_garbage_hazard",
        "void __thiscall spawn_track_garbage_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* player);",
    ),
    (
        "initialize_track_ring_or_special_effect_runtime",
        "SubRing* __thiscall initialize_track_ring_or_special_effect_runtime(SubRing* ring);",
    ),
    (
        "spawn_track_ring_or_special_effect",
        "void __thiscall spawn_track_ring_or_special_effect(SubgameRuntime* game, TrackRowCell* cell, int32_t requested_kind, Player* player, float ring_speed);",
    ),
    (
        "initialize_ring_or_special_effect_particles",
        "int32_t __thiscall initialize_ring_or_special_effect_particles(SubRing* ring, int32_t unused_lives_snapshot);",
    ),
    (
        "emit_ring_star_shower",
        "void __thiscall emit_ring_star_shower(SubRingStar* particle, Player* owner);",
    ),
    (
        "update_ring_or_special_effect_particle",
        "void __thiscall update_ring_or_special_effect_particle(SubRingStar* particle);",
    ),
    (
        "update_ring_or_special_effect_parent",
        "void __thiscall update_ring_or_special_effect_parent(SubRing* ring);",
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
        "void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime* game, int32_t level_index);",
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
        "void __thiscall initialize_challenge_setup_screen(GUI* gui);",
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


TRUSTED_DATA_DECLARATIONS = [
    (
        0x4A1C4C,
        "g_galaxy_group_points",
        "GalaxyPoint g_galaxy_group_points[10];",
    ),
    (
        0x4A1D14,
        "g_galaxy_route_points",
        "GalaxyPoint g_galaxy_route_points[101];",
    ),
]


REQUIRED_CANONICAL_OWNER_MARKERS = (
    "SegmentCache segment_cache;",
    "SubRingStar particles[10];",
    "SubRingPool ring_effects;",
    "TrackRowCell runtime_cells[3200][8];",
    "SubRow runtime_rows[3200];",
)


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


def _sync_types(header_path: pathlib.Path) -> int:
    header_text = header_path.read_text(encoding="utf-8")
    missing_owner_markers = [
        marker for marker in REQUIRED_CANONICAL_OWNER_MARKERS if marker not in header_text
    ]
    if missing_owner_markers:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "applied": 0,
                    "missing_owner_markers": missing_owner_markers,
                    "failed": [
                        {
                            "reason": "noncanonical_subgame_runtime_header",
                            "detail": (
                                "refusing to replace the recovered SubgameRuntime owner "
                                "with a sparse compatibility header"
                            ),
                        }
                    ],
                },
                indent=2,
            )
        )
        return 1

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

    for address, selector, declaration in TRUSTED_DATA_DECLARATIONS:
        expected_observed = _data_declaration_to_observed_type(selector, declaration)
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
                    "reason": "set_data_type_failed",
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
                    "reason": "data_verification_failed",
                }
            )
            continue

        applied += 1

    game_root_owner_graph = sync_game_root_owner_graph(require=True)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "contact_header": str(contact_header_path),
                "type_sizes": {
                    "SubgameRuntime": _named_struct_size("SubgameRuntime"),
                    "SubRingStar": _named_struct_size("SubRingStar"),
                    "SubRing": _named_struct_size("SubRing"),
                    "SubRingPool": _named_struct_size("SubRingPool"),
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
        print("usage: apply_subgame_runtime_types.py <header-path>", file=sys.stderr)
        ida_pro.qexit(2)
        return

    header_path = pathlib.Path(argv[1]).resolve()
    ida_pro.qexit(_sync_types(header_path))


if __name__ == "__main__":
    main()
