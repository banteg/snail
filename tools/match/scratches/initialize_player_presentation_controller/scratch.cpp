// initialize_player_presentation_controller @ 0x4086d0 (thiscall, ret)

#include "player.h"
#include "runtime_slot.h"

extern void* g_player_presentation_noop_vtable;             // data_497354
extern void* g_invincible_shell_update_vtable;              // data_497358
extern void* g_weapon_noop_vtable;                         // data_49735c

typedef RuntimeSlot* (RuntimeSlot::*RuntimeSlotConstructor)();

void __stdcall initialize_array_with_constructor(
    void* base, int stride, int count, RuntimeSlotConstructor constructor);

cRSnail* cRSnail::initialize_player_presentation_controller()
{
    this->cRBodPos::cRBodPos();

    PresentationAnimationSlot* visible_bods = cutscene_animation_slots;
    for (int i = 0;
         i < sizeof(cutscene_animation_slots) / sizeof(cutscene_animation_slots[0]);
         ++i) {
        visible_bods[i].body.cRBodPos::cRBodPos();
    }

    Weapon* group_a = &weapon_channels[0];
    group_a->cRBodPos::cRBodPos();
    ((RuntimeSlot*)((char*)group_a + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_a->animation_slots,
        sizeof(PresentationAnimationSlot),
        sizeof(group_a->animation_slots) / sizeof(group_a->animation_slots[0]),
        &RuntimeSlot::initialize_renderable_bod);
    group_a->vtable = &g_weapon_noop_vtable;

    Weapon* group_b = &weapon_channels[1];
    group_b->cRBodPos::cRBodPos();
    ((RuntimeSlot*)((char*)group_b + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_b->animation_slots,
        sizeof(PresentationAnimationSlot),
        sizeof(group_b->animation_slots) / sizeof(group_b->animation_slots[0]),
        &RuntimeSlot::initialize_renderable_bod);
    group_b->vtable = &g_weapon_noop_vtable;

    Weapon* group_c = &weapon_channels[2];
    group_c->cRBodPos::cRBodPos();
    ((RuntimeSlot*)((char*)group_c + 0xc0))->noop_runtime_slot_constructor();
    initialize_array_with_constructor(
        group_c->animation_slots,
        sizeof(PresentationAnimationSlot),
        sizeof(group_c->animation_slots) / sizeof(group_c->animation_slots[0]),
        &RuntimeSlot::initialize_renderable_bod);
    group_c->vtable = &g_weapon_noop_vtable;

    Weapon* group_d = &jetpack_channel;
    group_d->cRBodPos::cRBodPos();
    ((RuntimeSlot*)((char*)group_d + 0x80))->noop_runtime_slot_constructor();
    ((RuntimeSlot*)((char*)group_d + 0xc0))->noop_runtime_slot_constructor();
    PresentationAnimationSlot* group_d_children = group_d->animation_slots;
    for (int j = 0;
         j < sizeof(group_d->animation_slots) / sizeof(group_d->animation_slots[0]);
         ++j) {
        group_d_children[j].body.cRBodPos::cRBodPos();
    }
    group_d->vtable = &g_weapon_noop_vtable;

    snail_hotspot_source_body.cRBodPos::cRBodPos();
    snail_hotspot_body.cRBodPos::cRBodPos();
    invincible_shell.cRBodPos::cRBodPos();
    invincible_shell.vtable = &g_invincible_shell_update_vtable;
    vtable = &g_player_presentation_noop_vtable;
    return this;
}
