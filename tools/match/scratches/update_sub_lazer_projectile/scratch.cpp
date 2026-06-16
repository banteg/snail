// update_sub_lazer_projectile @ 0x43efb0 (thiscall, ret)
// State 2 -> list remove + kill_sprite; state 1 -> cull behind the owner
// kill plane or advance the wrapped sine bob on the nested sprite. The
// projectile BODY motion lives with the renderable-body owner; this
// update never integrates position. Update-state (+0x38) is distinct
// from the pool free flag (+0x80) used by the shoot scan.

#include "sub_lazer_types.h"

struct FreeAnchor {
    char unknown_00[4];
    SubLazerRuntime* first;    // +0x04
    SubLazerRuntime* free_top; // +0x08
};

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);
float sine(float radians);

void SubLazerRuntime::update_sub_lazer_projectile()
{
    int zero = 0;
    unsigned int flags;
    FreeAnchor* anchor;
    SubLazerRuntime* next;
    SubLazerRuntime* prev;

    if (owner_game->paused != zero)
        return;

    int current_state = state - zero;
    switch (current_state) {
    case 0:
        break;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        goto update_bob;
    }
    return;

state_two:
    flags = list_flags;
    state = zero;
    anchor = (FreeAnchor*)(g_game_base + 0x5a8);
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
        sprite->kill_sprite();
        return;
    }
    if ((flags & 0x40) != 0) {
        report_errorf("List remove NEXTBOD");
        sprite->kill_sprite();
        return;
    }

    next = list_next;
    if (next != (SubLazerRuntime*)zero)
        next->list_prev = list_prev;

    prev = list_prev;
    if (prev != (SubLazerRuntime*)zero) {
        prev->list_next = list_next;
    } else {
        anchor->first = list_next;
    }

    list_next = anchor->free_top;
    anchor->free_top = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (position_z >= owner->interaction_max_z) {
        goto update_bob;
    }

    flags = list_flags;
    state = zero;
    anchor = (FreeAnchor*)(g_game_base + 0x5a8);
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
        sprite->kill_sprite();
        return;
    }
    if ((flags & 0x40) != 0) {
        report_errorf("List remove NEXTBOD");
        sprite->kill_sprite();
        return;
    }

    next = list_next;
    if (next != (SubLazerRuntime*)zero)
        next->list_prev = list_prev;

    prev = list_prev;
    if (prev != (SubLazerRuntime*)zero) {
        prev->list_next = list_next;
    } else {
        anchor->first = list_next;
    }

    list_next = anchor->free_top;
    anchor->free_top = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

update_bob:
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced > 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->position.y = sine(bob_phase * 6.2831855f) * 0.30000001f + bob_base_y;
}
