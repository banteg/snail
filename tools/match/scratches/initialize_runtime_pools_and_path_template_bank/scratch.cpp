// initialize_runtime_pools_and_path_template_bank @ 0x408060 (thiscall, ret)

#include "player.h"
#include "runtime_slot.h"
#include "sprite.h"
#include "subgame_runtime.h"

extern void* g_banner_callback_table;        // data_497304
extern void* g_subgoldy_callback_table;      // data_497300
extern void* g_barrier_actor_callback_table; // data_4972fc
extern void* g_smtracks_callback_table;      // data_4972f8

#define SLOT(offset) ((RuntimeSlot*)(self + (offset)))
#define COLOR(offset) ((Color4f*)(self + (offset)))

SubgameRuntime* SubgameRuntime::initialize_runtime_pools_and_path_template_bank()
{
    char* self = (char*)this;

    Color4f* first_buffer_color = COLOR(0x5c);
    first_buffer_color->noop_this_constructor();
    RuntimeSlot* active_bods = (RuntimeSlot*)((char*)first_buffer_color + 0x58);
    initialize_array_with_constructor(
        active_bods, 0x3c, 0x2cb, &RuntimeSlot::initialize_active_bod);

    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.segment_slots,
        sizeof(SubSegment),
        0x64,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.first_segment.rows,
        sizeof(AuthoredSegmentRow),
        0x100,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition.last_segment.rows,
        sizeof(AuthoredSegmentRow),
        0x100,
        &RuntimeSlot::noop_runtime_slot_constructor);

    level_definition.fringe_color.noop_this_constructor();
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.segment_slots,
        sizeof(SubSegment),
        0x64,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.first_segment.rows,
        sizeof(AuthoredSegmentRow),
        0x100,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)level_definition_scratch.last_segment.rows,
        sizeof(AuthoredSegmentRow),
        0x100,
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
    int health_count = 8;
    do {
        health_pickup->initialize_track_health_pickup_runtime();
        ++health_pickup;
        --health_count;
    } while (health_count);

    Slug* slug = slug_hazards.slots;
    int slug_count = 8;
    do {
        slug->initialize_slug_hazard_runtime();
        ++slug;
        --slug_count;
    } while (slug_count);

    initialize_array_with_constructor(
        (RuntimeSlot*)sub_lazers.slots,
        sizeof(SubLazer),
        20,
        &RuntimeSlot::initialize_sub_lazer_runtime);
    initialize_array_with_constructor(
        (RuntimeSlot*)salt_hazards.slots,
        sizeof(Salt),
        40,
        &RuntimeSlot::initialize_salt_hazard_runtime);

    Banner* banner = banners.slots;
    int banner_count = 2;
    do {
        banner->initialize_bod_base();
        banner->vtable = &g_banner_callback_table;
        ++banner;
        --banner_count;
    } while (banner_count);

    SubGarbage* garbage = garbage_hazards.slots;
    int garbage_count = 0x32;
    do {
        garbage->initialize_garbage_hazard();
        ++garbage;
        --garbage_count;
    } while (garbage_count);

    SubRing* ring = ring_effects.slots;
    int ring_count = 2;
    do {
        ring->initialize_track_ring_or_special_effect_runtime();
        ++ring;
        --ring_count;
    } while (ring_count);

    initialize_array_with_constructor(
        (RuntimeSlot*)fringe_manager.objects,
        sizeof(Fringe),
        7000,
        &RuntimeSlot::initialize_fringe_object);

    Player* subgoldy = &player;
    subgoldy->initialize_renderable_bod();
    subgoldy->click_start.initialize_click_start_controller_runtime();
    ((RuntimeSlot*)&subgoldy->cameraman)->noop_runtime_slot_constructor();
    ((RuntimeSlot*)&subgoldy->follow_state)->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        (RuntimeSlot*)subgoldy->golb_shots,
        sizeof(GolbShot),
        0xc,
        &RuntimeSlot::initialize_golb_shot);
    subgoldy->presentation.initialize_player_presentation_controller();
    subgoldy->vtable = &g_subgoldy_callback_table;

    SubLoc* loc = &runtime_cells[0][0];
    int loc_count = 0x6400;
    do {
        loc->initialize_sub_loc();
        ++loc;
        --loc_count;
    } while (loc_count);

    SubRow* row = runtime_rows;
    int row_count = 0xc80;
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

    RuntimeSlot* barrier = SLOT(0xff7bc4);
    barrier->initialize_bod_base();
    barrier->vtable = &g_barrier_actor_callback_table;

    RuntimeSlot* landscape = (RuntimeSlot*)landscape_manager.active_entries;
    initialize_array_with_constructor(
        landscape,
        sizeof(ActiveLandscapeEntry),
        0xa,
        &RuntimeSlot::initialize_active_landscape_entry);
    landscape = (RuntimeSlot*)((char*)landscape +
        sizeof(landscape_manager.active_entries) + sizeof(landscape_manager.script_count));
    initialize_array_with_constructor(
        landscape,
        sizeof(LandscapeScriptRecord),
        0x80,
        &RuntimeSlot::initialize_landscape_script_record);

    SmtrackHeightfieldAnimator* smtracks_owner = &smtrack_heightfield;
    smtracks_owner->initialize_bod_base();
    smtracks_owner->frame_sequence.initialize_object_constructor_thunk();
    smtracks_owner->vtable = &g_smtracks_callback_table;

    initialize_array_with_constructor(
        (RuntimeSlot*)sm_tracks.entries,
        sizeof(SegmentCatalogEntry),
        0x96,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)parcel_manager.slots,
        sizeof(Parcel),
        0x32,
        &RuntimeSlot::initialize_track_parcel_runtime);
    initialize_array_with_constructor(
        (RuntimeSlot*)galaxy.route_slots,
        sizeof(GalaxyRouteSlot),
        0x65,
        &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        (RuntimeSlot*)galaxy.route_names,
        sizeof(GalaxyRouteNameRecord),
        0xa,
        &RuntimeSlot::initialize_galaxy_route_name_record);
    initialize_array_with_constructor(
        (RuntimeSlot*)enemy_manager.entries,
        sizeof(ContactTargetEntry),
        CONTACT_TARGET_CAPACITY,
        &RuntimeSlot::noop_runtime_slot_constructor);

    return this;
}

#undef SLOT
#undef COLOR
