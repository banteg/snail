// destroy_garbage_hazard @ 0x43f130 (thiscall, ret)
// cRSubGarbage::Kill(): remove the live bod from the shared active list,
// kill its sprite, then unlink the slot from the active garbage chain at
// game+0x359140.

#include "sprite.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

class GarbageHazardSlot;

struct SharedBodListAnchor {
    int unknown_00;
    GarbageHazardSlot* first;    // +0x04
    GarbageHazardSlot* free_top; // +0x08
};

struct Game {
    char unknown_00[0x359140];
    GarbageHazardSlot* active_garbage_head; // +0x359140
};

class GarbageHazardSlot {
public:
    GarbageHazardSlot* destroy_garbage_hazard();

    int unknown_00;
    unsigned int list_flags;         // +0x04
    GarbageHazardSlot* list_prev;    // +0x08
    GarbageHazardSlot* list_next;    // +0x0c
    char unknown_10[0x80 - 0x10];
    GarbageHazardSlot* next_active;  // +0x80
    int state;                       // +0x84
    char unknown_88[0x8c - 0x88];
    Game* game;                      // +0x8c
    char unknown_90[0xb4 - 0x90];
    Sprite* sprite;                  // +0xb4
};

GarbageHazardSlot* GarbageHazardSlot::destroy_garbage_hazard()
{
    state = 0;

    SharedBodListAnchor* anchor = (SharedBodListAnchor*)(g_game_base + 0x5a8);
    int flags = list_flags;
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
    } else {
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
        } else {
            GarbageHazardSlot* next = list_next;
            if (next)
                next->list_prev = list_prev;

            GarbageHazardSlot* prev = list_prev;
            if (prev)
                prev->list_next = list_next;
            else
                anchor->first = list_next;

            list_next = anchor->free_top;
            anchor->free_top = this;

            int updated = list_flags;
            updated &= ~0x200;
            list_flags = updated;
        }
    }

    sprite->kill_sprite();

    Game* owner = game;
    GarbageHazardSlot* result = owner->active_garbage_head;
    if (result == this) {
        result = next_active;
        owner->active_garbage_head = result;
        return result;
    } else if (result) {
        while (1) {
            if (result->next_active == this)
                break;
            result = result->next_active;
            if (!result)
                return result;
        }
        result->next_active = next_active;
        next_active = 0;
    }
    return result;
}
