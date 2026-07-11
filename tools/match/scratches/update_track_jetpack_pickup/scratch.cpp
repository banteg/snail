// update_track_jetpack_pickup @ 0x43efb0 (thiscall, ret)
// State 2 -> list remove + kill_sprite; state 1 -> cull behind the owner
// kill plane or advance the wrapped sine bob on the nested sprite. The
// embedded renderable bodies live below the pickup parent; this update only
// manages the parent state and sprite bob.

#include "player.h"
#include "subgame_runtime.h"
#include "track_jetpack_pickup.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);
float sine(float radians);

void TrackJetpackPickup::update_track_jetpack_pickup()
{
    int zero = 0;
    unsigned int flags;
    BodList* anchor;
    TrackJetpackPickup* next;
    TrackJetpackPickup* prev;

    if (owner_game->subgame_pause_gate != zero)
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
    anchor = (BodList*)(g_game_base + 0x5a8);
    if ((flags & 0x200) == 0) goto state_two_not_linked;
    if ((flags & 0x40) != 0) goto state_two_nextbod;

    next = (TrackJetpackPickup*)list_next;
    if (next != (TrackJetpackPickup*)zero)
        next->list_prev = list_prev;

    prev = (TrackJetpackPickup*)list_prev;
    if (prev != (TrackJetpackPickup*)zero) {
        prev->list_next = list_next;
    } else {
        anchor->first = list_next;
    }

    list_next = (TrackJetpackPickup*)anchor->free_top;
    anchor->free_top = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_two_nextbod:
    report_errorf("List remove NEXTBOD");
    sprite->kill_sprite();
    return;

state_two_not_linked:
    report_errorf("List remove");
    sprite->kill_sprite();
    return;

state_one:
    if (world_position.z < owner->interaction_max_z) {
        flags = list_flags;
        state = zero;
        anchor = (BodList*)(g_game_base + 0x5a8);
        Sprite* pickup_sprite = sprite;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            pickup_sprite->kill_sprite();
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            pickup_sprite->kill_sprite();
            return;
        }

        next = (TrackJetpackPickup*)list_next;
        if (next != (TrackJetpackPickup*)zero)
            next->list_prev = list_prev;

        prev = (TrackJetpackPickup*)list_prev;
        if (prev != (TrackJetpackPickup*)zero) {
            prev->list_next = list_next;
        } else {
            anchor->first = list_next;
        }

        list_next = (TrackJetpackPickup*)anchor->free_top;
        anchor->free_top = this;
        list_flags &= ~0x200;
        sprite->kill_sprite();
        return;
    }

update_bob:
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced > 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->position.y = sine(bob_phase * 6.2831855f) * 0.30000001f + world_position.y;
}
