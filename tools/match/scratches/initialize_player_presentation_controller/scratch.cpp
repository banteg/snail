// initialize_player_presentation_controller @ 0x4086d0 (thiscall, ret)

#include "player.h"
#include "runtime_slot.h"

extern void* g_player_presentation_noop_vtable;             // data_497354
extern void* g_invincible_shell_update_vtable;              // data_497358
extern void* g_presentation_animation_channel_noop_vtable; // data_49735c

typedef RenderableBod* (RenderableBod::*RenderableBodConstructor)();

void __stdcall initialize_array_with_constructor(
    void* base, int stride, int count, RenderableBodConstructor constructor);

Snail* Snail::initialize_player_presentation_controller()
{
    initialize_renderable_bod();

    PresentationAnimationSlot* visible_bods = cutscene_animation_slots;
    for (int i = 0; i < 10; ++i) {
        visible_bods[i].body.initialize_renderable_bod();
    }

    PresentationAnimationChannel* group_a = &weapon_channels[0];
    group_a->initialize_renderable_bod();
    ((RuntimeSlot*)((char*)group_a + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_a->animation_slots,
        sizeof(PresentationAnimationSlot),
        5,
        &RenderableBod::initialize_renderable_bod);
    group_a->vtable = &g_presentation_animation_channel_noop_vtable;

    PresentationAnimationChannel* group_b = &weapon_channels[1];
    group_b->initialize_renderable_bod();
    ((RuntimeSlot*)((char*)group_b + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_b->animation_slots,
        sizeof(PresentationAnimationSlot),
        5,
        &RenderableBod::initialize_renderable_bod);
    group_b->vtable = &g_presentation_animation_channel_noop_vtable;

    PresentationAnimationChannel* group_c = &weapon_channels[2];
    group_c->initialize_renderable_bod();
    ((RuntimeSlot*)((char*)group_c + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_c->animation_slots,
        sizeof(PresentationAnimationSlot),
        5,
        &RenderableBod::initialize_renderable_bod);
    group_c->vtable = &g_presentation_animation_channel_noop_vtable;

    PresentationAnimationChannel* group_d = &jetpack_channel;
    group_d->initialize_renderable_bod();
    ((RuntimeSlot*)((char*)group_d + 0x80))->noop_runtime_slot_constructor();
    ((RuntimeSlot*)((char*)group_d + 0xc0))->noop_runtime_slot_constructor();
    PresentationAnimationSlot* group_d_children = group_d->animation_slots;
    for (int j = 0; j < 5; ++j) {
        group_d_children[j].body.initialize_renderable_bod();
    }
    group_d->vtable = &g_presentation_animation_channel_noop_vtable;

    snail_hotspot_source_body.initialize_renderable_bod();
    snail_hotspot_body.initialize_renderable_bod();
    invincible_shell.initialize_renderable_bod();
    invincible_shell.vtable = &g_invincible_shell_update_vtable;
    vtable = &g_player_presentation_noop_vtable;
    return this;
}
