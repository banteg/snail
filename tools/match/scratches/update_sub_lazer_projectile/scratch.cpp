// update_sub_lazer_projectile @ 0x43efb0 (thiscall, ret)
// State 2 -> list remove + kill_sprite; state 1 -> cull behind the owner
// kill plane or advance the wrapped sine bob on the nested sprite. The
// projectile BODY motion lives with the renderable-body owner; this
// update never integrates position. Update-state (+0x38) is distinct
// from the pool free flag (+0x80) used by the shoot scan.

#include "sprite.h"

struct SubLazerRuntime;

struct FreeAnchor {
    char unknown_00[4];
    SubLazerRuntime* first;    // +0x04
    SubLazerRuntime* free_top; // +0x08
};

struct GameView {
    char unknown_00[0x9];
    unsigned char paused; // +0x09
};

struct OwnerRecord {
    char unknown_00[0x2980];
    float kill_plane_z; // +0x2980
};

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);
float sine(float radians);

struct SubLazerRuntime {
    void update_sub_lazer_projectile();

    int unknown_00;
    unsigned int list_flags;  // +0x04
    SubLazerRuntime* list_prev;  // +0x08
    SubLazerRuntime* list_next;  // +0x0c
    char unknown_10[0x14 - 0x10];
    float bob_base_y;         // +0x14
    float position_z;         // +0x18
    char unknown_1c[0x38 - 0x1c];
    int state;                // +0x38: 1 live, 2 remove
    OwnerRecord* owner;       // +0x3c
    char unknown_40[0x44 - 0x40];
    GameView* owner_game;     // +0x44
    char unknown_48[0x64 - 0x48];
    Sprite* sprite;           // +0x64
    char unknown_68[0x6c - 0x68];
    float bob_phase;          // +0x6c
    float bob_phase_step;     // +0x70
};

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
    if (position_z >= owner->kill_plane_z) {
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
