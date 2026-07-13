// Shared neutral runtime-slot callback view for cRGame/cRSubGame constructor
// passes. The concrete pool layouts stay with their owning scratches.
#ifndef RUNTIME_SLOT_H
#define RUNTIME_SLOT_H

class RuntimeSlot {
public:
    RuntimeSlot* initialize_bod_base();
    RuntimeSlot* initialize_renderable_bod();
    RuntimeSlot* noop_runtime_slot_constructor();
    RuntimeSlot* initialize_border_record();
    RuntimeSlot* initialize_cached_x_mesh_slot();
    RuntimeSlot* initialize_intro_logo_renderable();
    RuntimeSlot* initialize_active_bod();
    RuntimeSlot* initialize_track_speedup_runtime();
    RuntimeSlot* initialize_track_jetpack_pickup_runtime();
    RuntimeSlot* initialize_track_health_pickup_runtime();
    RuntimeSlot* initialize_slug_hazard_runtime();
    RuntimeSlot* initialize_sub_lazer_runtime();
    RuntimeSlot* initialize_salt_hazard_runtime();
    RuntimeSlot* initialize_garbage_hazard();
    RuntimeSlot* initialize_track_ring_or_special_effect_runtime();
    RuntimeSlot* initialize_fringe_object();
    RuntimeSlot* initialize_golb_shot();
    RuntimeSlot* initialize_sub_loc();
    RuntimeSlot* initialize_track_row_runtime();
    RuntimeSlot* initialize_active_landscape_entry();
    RuntimeSlot* initialize_landscape_script_record();
    RuntimeSlot* sub_42F6E0();
    RuntimeSlot* initialize_track_parcel_runtime();
    RuntimeSlot* initialize_galaxy_route_name_record();

    // Shared one-byte 0x407b50 stub. Callsite receiver types distinguish the
    // empty lifecycle hooks that the Windows binary folds to this address.
    void noop_runtime_ai();

    void* vtable; // +0x00 for bod-like runtime slots
};

typedef RuntimeSlot* (RuntimeSlot::*RuntimeSlotConstructor)();

void __stdcall initialize_array_with_constructor(
    RuntimeSlot* base,
    int stride,
    int count,
    RuntimeSlotConstructor constructor);

#endif
