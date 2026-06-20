// initialize_runtime_pools_and_path_template_bank @ 0x408060 (thiscall, ret)

#include "runtime_slot.h"
#include "sprite.h"

extern void* g_banner_callback_table;        // data_497304
extern void* g_subgoldy_callback_table;      // data_497300
extern void* g_barrier_actor_callback_table; // data_4972fc
extern void* g_smtracks_callback_table;      // data_4972f8

class RuntimePools {
public:
    RuntimePools* initialize_runtime_pools_and_path_template_bank();
};

#define SLOT(offset) ((RuntimeSlot*)(self + (offset)))
#define COLOR(offset) ((Color4f*)(self + (offset)))

RuntimePools* RuntimePools::initialize_runtime_pools_and_path_template_bank()
{
    char* self = (char*)this;

    Color4f* first_buffer_color = COLOR(0x5c);
    first_buffer_color->noop_this_constructor();
    RuntimeSlot* active_bods = (RuntimeSlot*)((char*)first_buffer_color + 0x58);
    initialize_array_with_constructor(
        active_bods, 0x3c, 0x2cb, &RuntimeSlot::initialize_active_bod);

    initialize_array_with_constructor(
        SLOT(0xa878), 0x4220, 0x64, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x1a850c), 0x38, 0x100, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x1ac72c), 0x38, 0x100, &RuntimeSlot::noop_runtime_slot_constructor);

    COLOR(0x1b0140)->noop_this_constructor();
    initialize_array_with_constructor(
        SLOT(0x1b01f0), 0x4220, 0x64, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x34de84), 0x38, 0x100, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x3520a4), 0x38, 0x100, &RuntimeSlot::noop_runtime_slot_constructor);

    COLOR(0x355ab8)->noop_this_constructor();
    SLOT(0x355b64)->initialize_bod_base();
    SLOT(0x355b9c)->initialize_bod_base();
    SLOT(0x355bd4)->initialize_bod_base();
    SLOT(0x355c0c)->initialize_bod_base();
    SLOT(0x355c44)->initialize_bod_base();
    SLOT(0x355c7c)->initialize_bod_base();
    SLOT(0x355cb4)->initialize_bod_base();
    SLOT(0x355cec)->initialize_bod_base();
    SLOT(0x355d24)->initialize_bod_base();
    SLOT(0x355d5c)->initialize_bod_base();
    SLOT(0x355db0)->initialize_track_speedup_runtime();
    SLOT(0x355e64)->initialize_track_jetpack_pickup_runtime();

    RuntimeSlot* health_pickup = SLOT(0x356000);
    int health_count = 8;
    do {
        health_pickup->initialize_track_health_pickup_runtime();
        health_pickup = (RuntimeSlot*)((char*)health_pickup + 0x74);
        --health_count;
    } while (health_count);

    RuntimeSlot* slug = SLOT(0x3563a0);
    int slug_count = 8;
    do {
        slug->initialize_slug_hazard_runtime();
        slug = (RuntimeSlot*)((char*)slug + 0xec);
        --slug_count;
    } while (slug_count);

    initialize_array_with_constructor(
        SLOT(0x356b00), 0xb0, 0x14, &RuntimeSlot::initialize_sub_lazer_runtime);
    initialize_array_with_constructor(
        SLOT(0x3578c0), 0x98, 0x28, &RuntimeSlot::initialize_salt_hazard_runtime);

    RuntimeSlot* banner = SLOT(0x359080);
    int banner_count = 2;
    do {
        banner->initialize_bod_base();
        banner->vtable = &g_banner_callback_table;
        banner = (RuntimeSlot*)((char*)banner + 0x60);
        --banner_count;
    } while (banner_count);

    RuntimeSlot* garbage = SLOT(0x359144);
    int garbage_count = 0x32;
    do {
        garbage->initialize_garbage_hazard();
        garbage = (RuntimeSlot*)((char*)garbage + 0xc4);
        --garbage_count;
    } while (garbage_count);

    RuntimeSlot* ring = SLOT(0x35b78c);
    int ring_count = 2;
    do {
        ring->initialize_track_ring_or_special_effect_runtime();
        ring = (RuntimeSlot*)((char*)ring + 0x1f8);
        --ring_count;
    } while (ring_count);

    initialize_array_with_constructor(
        SLOT(0x35bbbc), 0x38, 0x1b58, &RuntimeSlot::initialize_fringe_object);

    RuntimeSlot* subgoldy = SLOT(0x3bb764);
    subgoldy->initialize_renderable_bod();
    ((RuntimeSlot*)((char*)subgoldy + 0xa0))->initialize_click_start_controller_runtime();
    ((RuntimeSlot*)((char*)subgoldy + 0x200))->noop_runtime_slot_constructor();
    ((RuntimeSlot*)((char*)subgoldy + 0x384))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        (RuntimeSlot*)((char*)subgoldy + 0x450),
        0x2e8,
        0xc,
        &RuntimeSlot::initialize_golb_shot);
    ((RuntimeSlot*)((char*)subgoldy + 0x2984))->initialize_enemy_manager_runtime();
    subgoldy->vtable = &g_subgoldy_callback_table;

    RuntimeSlot* bod = SLOT(0x3bfac8);
    int bod_count = 0x6400;
    do {
        bod->initialize_bod();
        bod = (RuntimeSlot*)((char*)bod + 0x54);
        --bod_count;
    } while (bod_count);

    RuntimeSlot* row = SLOT(0x5ccac8);
    int row_count = 0xc80;
    do {
        row->initialize_track_row_runtime();
        row = (RuntimeSlot*)((char*)row + 0xf4);
        --row_count;
    } while (row_count);

    RuntimeSlot* path_template = SLOT(0xff2914);
    int path_template_count = 0x7e;
    do {
        path_template->initialize_path_template_record_pair();
        path_template = (RuntimeSlot*)((char*)path_template + 0xa8);
        --path_template_count;
    } while (path_template_count);

    RuntimeSlot* barrier = SLOT(0xff7bc4);
    barrier->initialize_bod_base();
    barrier->vtable = &g_barrier_actor_callback_table;

    RuntimeSlot* landscape = SLOT(0xff7c00);
    initialize_array_with_constructor(
        landscape, 0x90, 0xa, &RuntimeSlot::initialize_active_landscape_entry);
    landscape = (RuntimeSlot*)((char*)landscape + 0x5a4);
    initialize_array_with_constructor(
        landscape, 0x124, 0x80, &RuntimeSlot::initialize_landscape_script_record);

    RuntimeSlot* smtracks = SLOT(0x10013a4);
    smtracks->initialize_bod_base();
    ((RuntimeSlot*)((char*)smtracks + 0x38))->sub_42F6E0();
    smtracks->vtable = &g_smtracks_callback_table;

    initialize_array_with_constructor(
        SLOT(0x10014d0), 0x4088, 0x96, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x125e480), 0x8c, 0x32, &RuntimeSlot::initialize_track_parcel_runtime);
    initialize_array_with_constructor(
        SLOT(0x1260030), 0x2a0, 0x65, &RuntimeSlot::noop_runtime_slot_constructor);
    initialize_array_with_constructor(
        SLOT(0x1270950), 0xa0, 0xa, &RuntimeSlot::sub_408880);
    initialize_array_with_constructor(
        SLOT(0x1270fd8), 0x18, 0x100, &RuntimeSlot::noop_runtime_slot_constructor);

    return this;
}

#undef SLOT
#undef COLOR
