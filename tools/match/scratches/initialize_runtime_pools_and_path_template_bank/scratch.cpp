// initialize_runtime_pools_and_path_template_bank @ 0x408060 (thiscall, ret)

#include <stddef.h>

#include "player.h"
#include "runtime_slot.h"
#include "sprite.h"
#include "subgame_runtime.h"

extern void* g_banner_callback_table;        // data_497304
extern void* g_subgoldy_callback_table;      // data_497300
extern void* g_barrier_actor_callback_table; // data_4972fc
extern void* g_smtracks_callback_table;      // data_4972f8

SubgameRuntime* SubgameRuntime::initialize_runtime_pools_and_path_template_bank()
{
    char* self = (char*)this;

    tColour* segment_cache_constructor_receiver =
        (tColour*)(self + offsetof(SubgameRuntime, segment_cache));
    segment_cache_constructor_receiver->noop_this_constructor();
    RuntimeSlot* active_bods = (RuntimeSlot*)((char*)segment_cache_constructor_receiver
        + offsetof(SegmentCache, slots));
    initialize_array_with_constructor(
        active_bods,
        sizeof(TrackRenderCacheSlot),
        sizeof(segment_cache.slots) / sizeof(segment_cache.slots[0][0]),
        &RuntimeSlot::initialize_active_bod);

    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.segment_slots,
        sizeof(SubSegment),
        sizeof(level_definition.segment_slots)
            / sizeof(level_definition.segment_slots[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.first_segment.rows,
        sizeof(AuthoredSegmentRow),
        sizeof(level_definition.first_segment.rows)
            / sizeof(level_definition.first_segment.rows[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.last_segment.rows,
        sizeof(AuthoredSegmentRow),
        sizeof(level_definition.last_segment.rows)
            / sizeof(level_definition.last_segment.rows[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);

    level_definition.fringe_color.noop_this_constructor();
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.segment_slots,
        sizeof(SubSegment),
        sizeof(level_definition_scratch.segment_slots)
            / sizeof(level_definition_scratch.segment_slots[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.first_segment.rows,
        sizeof(AuthoredSegmentRow),
        sizeof(level_definition_scratch.first_segment.rows)
            / sizeof(level_definition_scratch.first_segment.rows[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.last_segment.rows,
        sizeof(AuthoredSegmentRow),
        sizeof(level_definition_scratch.last_segment.rows)
            / sizeof(level_definition_scratch.last_segment.rows[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);

    level_definition_scratch.fringe_color.noop_this_constructor();
    fringe_attachment_list_head.initialize_bod_base();
    track_body_list_head.initialize_bod_base();
    barrier_sub_lazer_list_head.initialize_bod_base();
    salt_hazard_list_head.initialize_bod_base();
    landscape_slice_list_head.initialize_bod_base();
    unknown_bod_355c7c.initialize_bod_base();
    special_track_cell_list_head.initialize_bod_base();
    unknown_bod_355cec.initialize_bod_base();
    golb_vapour_list_head.initialize_bod_base();
    unknown_bod_355d5c.initialize_bod_base();
    speedup_pickup.initialize_track_speedup_runtime();
    jetpack_pickup.initialize_track_jetpack_pickup_runtime();

    SubHealth* health_pickup = health_pickups;
    int health_count = sizeof(health_pickups) / sizeof(health_pickups[0]);
    do {
        health_pickup->initialize_track_health_pickup_runtime();
        ++health_pickup;
        --health_count;
    } while (health_count);

    Slug* slug = slug_hazards.slots;
    int slug_count =
        sizeof(slug_hazards.slots) / sizeof(slug_hazards.slots[0]);
    do {
        slug->initialize_slug_hazard_runtime();
        ++slug;
        --slug_count;
    } while (slug_count);

    initialize_array_with_constructor(
        (RuntimeSlot*)sub_lazers.slots,
        sizeof(SubLazer),
        sizeof(sub_lazers.slots) / sizeof(sub_lazers.slots[0]),
        &RuntimeSlot::initialize_sub_lazer_runtime);
    initialize_array_with_constructor(
        (RuntimeSlot*)salt_hazards.slots,
        sizeof(Salt),
        sizeof(salt_hazards.slots) / sizeof(salt_hazards.slots[0]),
        &RuntimeSlot::initialize_salt_hazard_runtime);

    Banner* banner = banners.slots;
    int banner_count = sizeof(banners.slots) / sizeof(banners.slots[0]);
    do {
        banner->initialize_bod_base();
        banner->vtable = &g_banner_callback_table;
        ++banner;
        --banner_count;
    } while (banner_count);

    SubGarbage* garbage = garbage_hazards.slots;
    int garbage_count =
        sizeof(garbage_hazards.slots) / sizeof(garbage_hazards.slots[0]);
    do {
        garbage->initialize_garbage_hazard();
        ++garbage;
        --garbage_count;
    } while (garbage_count);

    SubRing* ring = ring_effects.slots;
    int ring_count =
        sizeof(ring_effects.slots) / sizeof(ring_effects.slots[0]);
    do {
        ring->initialize_track_ring_or_special_effect_runtime();
        ++ring;
        --ring_count;
    } while (ring_count);

    initialize_array_with_constructor(
        (RuntimeSlot*)fringe_manager.objects,
        sizeof(Fringe),
        sizeof(fringe_manager.objects) / sizeof(fringe_manager.objects[0]),
        &RuntimeSlot::initialize_fringe_object);

    Player* subgoldy = &player;
    subgoldy->initialize_renderable_bod();
    subgoldy->click_start.initialize_click_start_controller_runtime();
    ((RuntimeSlot*)&subgoldy->cameraman)->noop_runtime_slot_constructor();
    ((RuntimeSlot*)&subgoldy->follow_state)->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        (RuntimeSlot*)subgoldy->golb_shots,
        sizeof(GolbShot),
        sizeof(subgoldy->golb_shots) / sizeof(subgoldy->golb_shots[0]),
        &RuntimeSlot::initialize_golb_shot);
    subgoldy->presentation.initialize_player_presentation_controller();
    subgoldy->vtable = &g_subgoldy_callback_table;

    SubLoc* loc = &runtime_cells[0][0];
    int loc_count = sizeof(runtime_cells) / sizeof(runtime_cells[0][0]);
    do {
        loc->initialize_sub_loc();
        ++loc;
        --loc_count;
    } while (loc_count);

    SubRow* row = runtime_rows;
    int row_count = sizeof(runtime_rows) / sizeof(runtime_rows[0]);
    do {
        row->initialize_track_row_runtime();
        ++row;
        --row_count;
    } while (row_count);

    Path* path_template = &path_pairs[0].primary;
    int path_template_count = PATH_COUNT;
    do {
        path_template->initialize_path_template_record_pair();
        ++path_template;
        --path_template_count;
    } while (path_template_count);

    barrier.initialize_bod_base();
    barrier.vtable = &g_barrier_actor_callback_table;

    RuntimeSlot* landscape = (RuntimeSlot*)landscape_manager.active_entries;
    initialize_array_with_constructor(
        landscape,
        sizeof(ActiveLandscapeEntry),
        sizeof(landscape_manager.active_entries)
            / sizeof(landscape_manager.active_entries[0]),
        &RuntimeSlot::initialize_active_landscape_entry);
    landscape = (RuntimeSlot*)((char*)landscape +
        sizeof(landscape_manager.active_entries) + sizeof(landscape_manager.script_count));
    initialize_array_with_constructor(
        landscape,
        sizeof(LandscapeScriptRecord),
        sizeof(landscape_manager.scripts) / sizeof(landscape_manager.scripts[0]),
        &RuntimeSlot::initialize_landscape_script_record);

    SmtrackHeightfieldAnimator* smtracks_owner = &smtrack_heightfield;
    smtracks_owner->initialize_bod_base();
    smtracks_owner->frame_sequence.initialize_object_constructor_thunk();
    smtracks_owner->vtable = &g_smtracks_callback_table;

    initialize_array_with_constructor(
        (RuntimeSlot*)sm_tracks.entries,
        sizeof(SegmentCatalogEntry),
        sizeof(sm_tracks.entries) / sizeof(sm_tracks.entries[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)parcel_manager.slots,
        sizeof(Parcel),
        sizeof(parcel_manager.slots) / sizeof(parcel_manager.slots[0]),
        &RuntimeSlot::initialize_track_parcel_runtime);
    initialize_array_with_constructor(
        (RuntimeSlot*)galaxy.route_slots,
        sizeof(GalaxyRouteSlot),
        sizeof(galaxy.route_slots) / sizeof(galaxy.route_slots[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)galaxy.route_names,
        sizeof(GalaxyRouteNameRecord),
        sizeof(galaxy.route_names) / sizeof(galaxy.route_names[0]),
        &RuntimeSlot::initialize_galaxy_route_name_record);
    initialize_array_with_constructor(
        (RuntimeSlot*)enemy_manager.entries,
        sizeof(ContactTargetEntry),
        sizeof(enemy_manager.entries) / sizeof(enemy_manager.entries[0]),
        &RuntimeSlot::noop_runtime_slot_constructor);

    return this;
}
