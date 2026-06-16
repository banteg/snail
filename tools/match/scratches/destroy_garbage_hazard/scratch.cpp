// destroy_garbage_hazard @ 0x43f130 (thiscall, ret)
// cRSubGarbage::Kill(): remove the live bod from the shared active list,
// kill its sprite, then unlink the slot from the active garbage chain at
// game+0x359140.

#include "garbage_hazard_slot.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

struct SharedBodListAnchor {
    int unknown_00;
    GarbageHazardSlot* first;    // +0x04
    GarbageHazardSlot* free_top; // +0x08
};

class Game {
public:
    char unknown_00[0x359140];
    GarbageHazardSlot* active_garbage_head; // +0x359140
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
            GarbageHazardSlot* next = (GarbageHazardSlot*)list_next;
            if (next)
                next->list_prev = (BodNode*)list_prev;

            GarbageHazardSlot* prev = (GarbageHazardSlot*)list_prev;
            if (prev)
                prev->list_next = (BodNode*)list_next;
            else
                anchor->first = (GarbageHazardSlot*)list_next;

            list_next = (BodNode*)anchor->free_top;
            anchor->free_top = (GarbageHazardSlot*)this;

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
