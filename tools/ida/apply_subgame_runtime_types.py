import json
import pathlib
import re
import sys

import ida_funcs
import ida_hexrays
import ida_kernwin
import ida_name
import ida_pro
import ida_typeinf
import idc

SCRIPT_ROOT = pathlib.Path(__file__).resolve().parent
if str(SCRIPT_ROOT) not in sys.path:
    sys.path.insert(0, str(SCRIPT_ROOT))

from game_root_owner import sync_game_root_owner_graph  # noqa: E402


TRUSTED_NAMES = (
    (0x408860, "initialize_track_parcel_runtime"),
    (0x435DF0, "set_subgame_features"),
    (0x440600, "uninit_pause_menu"),
    (0x440660, "initialize_pause_menu"),
    (0x4407A0, "update_pause_menu"),
    (0x443130, "update_track_parcels"),
    (0x443160, "initialize_track_parcel_slots"),
    (0x443190, "allocate_track_parcel_slot"),
    (0x4431D0, "update_track_parcel"),
    (0x443730, "spawn_track_parcel"),
)


TRUSTED_DECLARATIONS = [
    (
        "uninit_pause_menu",
        "void __thiscall uninit_pause_menu(SubPause* pause);",
    ),
    (
        "initialize_pause_menu",
        "void __thiscall initialize_pause_menu(SubPause* pause);",
    ),
    (
        "update_pause_menu",
        "void __thiscall update_pause_menu(SubPause* pause);",
    ),
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
        "spawn_slug_hazard",
        "int32_t __thiscall spawn_slug_hazard(SubgameRuntime* game, TrackRowCell* cell, Player* owner_player);",
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
        "int32_t __thiscall set_subgame_features(SubgameRuntime* runtime);",
    ),
    (
        "switch_track_mirror",
        "bool __thiscall switch_track_mirror(SubgameRuntime* runtime);",
    ),
    (
        "normalize_segment_glyph_for_track_flags",
        "char __thiscall normalize_segment_glyph_for_track_flags(SubgameRuntime* runtime, char glyph, int32_t row, char edge_row);",
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
        "update_times_up",
        "void __thiscall update_times_up(TimesUp* times_up);",
    ),
    (
        "uninit_times_up",
        "void __thiscall uninit_times_up(TimesUp* times_up);",
    ),
    (
        "show_times_up_message",
        "void __thiscall show_times_up_message(TimesUp* times_up);",
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
    "SubSolution* selected_level_record;",
    "Parcel_must_be_0x8c",
    "Parcel slots[50];",
    "ParcelManager_must_be_0x1b58",
)

EXPECTED_PARCEL_OWNER_SIZES = {
    "Parcel": 0x8C,
    "ParcelManager": 0x1B58,
}

REANALYSIS_FUNCTIONS = (
    0x404CF0,  # update_row_event_display
    0x408060,  # initialize_runtime_pools_and_path_template_bank
    0x408860,  # initialize_track_parcel_runtime
    0x435DF0,  # set_subgame_features
    0x437270,  # normalize_segment_glyph_for_track_flags
    0x437EB0,  # build_subgame_level
    0x438B90,  # update_subgame
    0x43B120,  # update_subgoldy
    0x440600,  # uninit_pause_menu
    0x440660,  # initialize_pause_menu
    0x4407A0,  # update_pause_menu
    0x443130,  # update_track_parcels
    0x443160,  # initialize_track_parcel_slots
    0x443190,  # allocate_track_parcel_slot
    0x4431D0,  # update_track_parcel
    0x443730,  # spawn_track_parcel
    0x444CF0,  # handle_subgoldy_collisions
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


def _normalize_pointer_type(value: str | None) -> str:
    return (_normalize_type_text(value) or "").removeprefix("struct ")


def _sync_slug_allocator_lvar(
    *,
    definition_address: int,
    accepted_names: set[str],
    accepted_types: set[str],
    target_name: str,
    target_struct_name: str,
) -> dict[str, object]:
    """Persist one exact borrowed-cursor relationship in AddSlug."""
    selector = "spawn_slug_hazard"
    address = idc.get_name_ea_simple(selector)
    if address == idc.BADADDR:
        return {"status": "failed", "reason": "missing_function", "selector": selector}

    ida_hexrays.mark_cfunc_dirty(address, True)
    normalized_accepted_types = {
        _normalize_pointer_type(value) for value in accepted_types
    }
    cfunc = ida_hexrays.decompile(address)
    candidates = [
        lvar
        for lvar in cfunc.get_lvars()
        if not lvar.is_arg_var
        and not lvar.is_stk_var()
        and lvar.defea == definition_address
        and lvar.name in accepted_names
        and _normalize_pointer_type(str(lvar.type()))
        in normalized_accepted_types
    ]
    if len(candidates) != 1:
        return {
            "status": "failed",
            "reason": "unexpected_slug_allocator_lvar_candidates",
            "selector": selector,
            "definition_address": hex(definition_address),
            "target_name": target_name,
            "candidate_count": len(candidates),
        }

    lvar = candidates[0]
    target_pointer_type = _normalize_pointer_type(f"{target_struct_name} *")
    if (
        lvar.name == target_name
        and _normalize_pointer_type(str(lvar.type())) == target_pointer_type
    ):
        return {
            "status": "unchanged",
            "selector": selector,
            "name": lvar.name,
            "type": str(lvar.type()),
            "definition_address": hex(lvar.defea),
        }

    target_type = ida_typeinf.tinfo_t()
    if not target_type.get_named_type(
        None,
        target_struct_name,
        ida_typeinf.BTF_STRUCT,
    ):
        return {
            "status": "failed",
            "reason": "missing_slug_allocator_lvar_type",
            "selector": selector,
            "target_struct_name": target_struct_name,
        }

    pointer_type = ida_typeinf.tinfo_t()
    if not pointer_type.create_ptr(target_type):
        return {
            "status": "failed",
            "reason": "create_slug_allocator_pointer_type_failed",
            "selector": selector,
            "target_struct_name": target_struct_name,
        }

    info = ida_hexrays.lvar_saved_info_t()
    info.ll = ida_hexrays.lvar_locator_t(lvar.location, lvar.defea)
    info.name = target_name
    info.type = pointer_type
    if not ida_hexrays.modify_user_lvar_info(
        address,
        ida_hexrays.MLI_NAME | ida_hexrays.MLI_TYPE,
        info,
    ):
        return {
            "status": "failed",
            "reason": "modify_slug_allocator_lvar_failed",
            "selector": selector,
            "target_name": target_name,
        }

    ida_hexrays.mark_cfunc_dirty(address, True)
    verified_cfunc = ida_hexrays.decompile(address)
    verified = [
        candidate
        for candidate in verified_cfunc.get_lvars()
        if not candidate.is_arg_var
        and not candidate.is_stk_var()
        and candidate.defea == definition_address
        and candidate.name == target_name
        and _normalize_pointer_type(str(candidate.type())) == target_pointer_type
    ]
    if len(verified) != 1:
        return {
            "status": "failed",
            "reason": "slug_allocator_lvar_readback_failed",
            "selector": selector,
            "definition_address": hex(definition_address),
            "target_name": target_name,
            "candidate_count": len(verified),
        }

    return {
        "status": "applied",
        "selector": selector,
        "before_name": lvar.name,
        "before_type": str(lvar.type()),
        "name": verified[0].name,
        "type": str(verified[0].type()),
        "definition_address": hex(verified[0].defea),
    }


SPAWN_SLUG_HAZARD_LVAR_SPECS = (
    (
        "state_stride_cursor",
        0x43DC89,
        {"i", "slug_state_cursor"},
        {
            "_DWORD *",
            "int *",
            "int32_t *",
            "unsigned int *",
            "SlugStateStrideCursor *",
        },
        "slug_state_cursor",
        "SlugStateStrideCursor",
    ),
    (
        "selected_slot_cursor",
        0x43DCBD,
        {"v6", "slug_slot_cursor"},
        {"int", "char *", "void *", "SlugSlotCursor *"},
        "slug_slot_cursor",
        "SlugSlotCursor",
    ),
    (
        "sprite",
        0x43DDC8,
        {"sprite"},
        {"_DWORD *", "Sprite *"},
        "sprite",
        "Sprite",
    ),
)


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
    parcel_owner_sizes = {
        name: _named_struct_size(name) for name in EXPECTED_PARCEL_OWNER_SIZES
    }
    size_failures = [
        {
            "selector": name,
            "reason": "owner_size_mismatch",
            "expected": expected_size,
            "observed": parcel_owner_sizes[name],
        }
        for name, expected_size in EXPECTED_PARCEL_OWNER_SIZES.items()
        if parcel_owner_sizes[name] != expected_size
    ]
    if parse_errors or size_failures:
        print(
            json.dumps(
                {
                    "database": idc.get_idb_path(),
                    "header": str(header_path),
                    "parse_errors": parse_errors,
                    "parcel_owner_sizes": parcel_owner_sizes,
                    "failed": size_failures,
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
        if idc.get_name(address) != name:
            failed.append(
                {
                    "selector": name,
                    "address": hex(address),
                    "observed": idc.get_name(address),
                    "reason": "rename_readback_failed",
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

    slug_allocator_lvars = {}
    for (
        result_name,
        definition_address,
        accepted_names,
        accepted_types,
        target_name,
        target_struct_name,
    ) in SPAWN_SLUG_HAZARD_LVAR_SPECS:
        result = _sync_slug_allocator_lvar(
            definition_address=definition_address,
            accepted_names=accepted_names,
            accepted_types=accepted_types,
            target_name=target_name,
            target_struct_name=target_struct_name,
        )
        slug_allocator_lvars[result_name] = result
        if result.get("status") == "applied":
            applied += 1
        elif result.get("status") == "unchanged":
            unchanged += 1
        else:
            failed.append(
                {
                    "selector": "spawn_slug_hazard",
                    "lvar": result_name,
                    "result": result,
                }
            )

    game_root_owner_graph = sync_game_root_owner_graph(require=True)
    if game_root_owner_graph.get("status") == "failed":
        failed.append(
            {"selector": "GameRoot", "owner_graph": game_root_owner_graph}
        )

    reanalyzed = []
    for address in REANALYSIS_FUNCTIONS:
        function = ida_funcs.get_func(address)
        if function is None:
            failed.append(
                {
                    "selector": hex(address),
                    "reason": "missing_reanalysis_function",
                }
            )
            continue
        ida_hexrays.mark_cfunc_dirty(function.start_ea, True)
        reanalyzed.append(
            {
                "address": hex(function.start_ea),
                "name": idc.get_func_name(function.start_ea),
            }
        )

    print(
        json.dumps(
            {
                "database": idc.get_idb_path(),
                "header": str(header_path),
                "contact_header": str(contact_header_path),
                "parcel_owner_sizes": parcel_owner_sizes,
                "type_sizes": {
                    "SubgameRuntime": _named_struct_size("SubgameRuntime"),
                    "SubRingStar": _named_struct_size("SubRingStar"),
                    "SubRing": _named_struct_size("SubRing"),
                    "SubRingPool": _named_struct_size("SubRingPool"),
                    "SlugStateStrideCursor": _named_struct_size("SlugStateStrideCursor"),
                    "SlugSlotCursor": _named_struct_size("SlugSlotCursor"),
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
                "renamed": renamed,
                "names_unchanged": names_unchanged,
                "reanalyzed": reanalyzed,
                "game_root_owner_graph": game_root_owner_graph,
                "slug_allocator_lvars": slug_allocator_lvars,
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
    exit_code = _sync_types(header_path)
    try:
        idc.save_database(idc.get_idb_path(), 0)
    except Exception as exc:  # pragma: no cover - IDA runtime dependent
        ida_kernwin.msg(f"warning: failed to save database explicitly: {exc}\n")
    ida_pro.qexit(exit_code)


if __name__ == "__main__":
    main()
