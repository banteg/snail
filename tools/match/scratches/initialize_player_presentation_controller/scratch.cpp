// initialize_player_presentation_controller @ 0x4086d0 (thiscall, ret)

#include "player.h"

extern void* g_player_presentation_noop_vtable;             // data_497354
extern void* g_invincible_shell_update_vtable;              // data_497358
extern void* g_presentation_animation_channel_noop_vtable; // data_49735c

typedef RenderableBod* (RenderableBod::*RenderableBodConstructor)();

void __stdcall initialize_array_with_constructor(
    void* base, int stride, int count, RenderableBodConstructor constructor);

struct RenderableSlot {
    RenderableBod body; // +0x00
    char unknown_78[0x80 - 0x78];
};

class IostreamInit {
public:
    IostreamInit* initialize_iostream();
};

PlayerPresentationController*
PlayerPresentationController::initialize_player_presentation_controller()
{
    char* self = (char*)this;
    ((RenderableBod*)self)->initialize_renderable_bod();

    RenderableBod* visible_bods = (RenderableBod*)(self + 0x14c);
    for (int i = 0; i < 10; ++i) {
        ((RenderableBod*)((char*)visible_bods + 0x80 * i))->initialize_renderable_bod();
    }

    RenderableBod* group_a = (RenderableBod*)(self + 0x64c);
    group_a->initialize_renderable_bod();
    ((IostreamInit*)((char*)group_a + 0xc0))->initialize_iostream();
    initialize_array_with_constructor(
        (char*)group_a + 0x150, 0x80, 5, &RenderableBod::initialize_renderable_bod);
    group_a->vtable = &g_presentation_animation_channel_noop_vtable;

    RenderableBod* group_b = (RenderableBod*)(self + 0xa28);
    group_b->initialize_renderable_bod();
    ((IostreamInit*)((char*)group_b + 0xc0))->initialize_iostream();
    initialize_array_with_constructor(
        (char*)group_b + 0x150, 0x80, 5, &RenderableBod::initialize_renderable_bod);
    group_b->vtable = &g_presentation_animation_channel_noop_vtable;

    RenderableBod* group_c = (RenderableBod*)(self + 0xe04);
    group_c->initialize_renderable_bod();
    ((IostreamInit*)((char*)group_c + 0xc0))->initialize_iostream();
    initialize_array_with_constructor(
        (char*)group_c + 0x150, 0x80, 5, &RenderableBod::initialize_renderable_bod);
    group_c->vtable = &g_presentation_animation_channel_noop_vtable;

    RenderableBod* group_d = (RenderableBod*)(self + 0x11e0);
    group_d->initialize_renderable_bod();
    ((IostreamInit*)((char*)group_d + 0x80))->initialize_iostream();
    ((IostreamInit*)((char*)group_d + 0xc0))->initialize_iostream();
    RenderableBod* group_d_children = (RenderableBod*)((char*)group_d + 0x150);
    for (int j = 0; j < 5; ++j) {
        ((RenderableBod*)((char*)group_d_children + 0x80 * j))->initialize_renderable_bod();
    }
    group_d->vtable = &g_presentation_animation_channel_noop_vtable;

    ((RenderableBod*)(self + 0x15cc))->initialize_renderable_bod();
    ((RenderableBod*)(self + 0x164c))->initialize_renderable_bod();
    RenderableBod* child = (RenderableBod*)(self + 0x1894);
    child->initialize_renderable_bod();
    child->vtable = &g_invincible_shell_update_vtable;
    vtable = &g_player_presentation_noop_vtable;
    return this;
}
