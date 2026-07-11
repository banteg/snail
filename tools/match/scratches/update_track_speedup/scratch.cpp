// update_track_speedup @ 0x43ee50 (thiscall, ret)

#include "bod_list.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_speedup.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

void SubSpeedUp::update_track_speedup()
{
    int zero = 0;
    unsigned int flags;
    BodList* head;
    SubSpeedUp* next;
    SubSpeedUp* prev;

    if (owner_game->subgame_pause_gate != zero) {
        return;
    }

    int current_state = state - zero;
    switch (current_state) {
    case 0:
        break;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        return;
    }
    return;

state_two:
    flags = list_flags;
    state = zero;
    head = (BodList*)(g_game_base + 0x5a8);
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

    next = (SubSpeedUp*)list_next;
    if (next != (SubSpeedUp*)zero) {
        next->list_prev = list_prev;
    }

    prev = (SubSpeedUp*)list_prev;
    if (prev != (SubSpeedUp*)zero) {
        prev->list_next = list_next;
    } else {
        head->first = (BodNode*)list_next;
    }

    list_next = head->free_top;
    head->free_top = (BodNode*)this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (world_position.z >= owner->interaction_max_z) {
        return;
    }

    flags = list_flags;
    state = zero;
    head = (BodList*)(g_game_base + 0x5a8);
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

    next = (SubSpeedUp*)list_next;
    if (next != (SubSpeedUp*)zero) {
        next->list_prev = list_prev;
    }

    prev = (SubSpeedUp*)list_prev;
    if (prev != (SubSpeedUp*)zero) {
        prev->list_next = list_next;
    } else {
        head->first = (BodNode*)list_next;
    }

    list_next = head->free_top;
    head->free_top = (BodNode*)this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
}
