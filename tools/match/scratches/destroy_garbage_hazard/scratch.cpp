// destroy_garbage_hazard @ 0x43f130 (thiscall, ret)
// cRSubGarbage::Kill(): remove the live bod from the shared active list,
// kill its sprite, then unlink the slot from the runtime-owned active garbage
// chain.

#include "garbage_hazard_slot.h"
#include "game_root.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

SubGarbage* SubGarbage::destroy_garbage_hazard()
{
    state = SUB_GARBAGE_STATE_INACTIVE;

    BodList* anchor = &((GameRoot*)g_game_base)->active_bod_list;
    int flags = list_flags;
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
    } else {
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
        } else {
            SubGarbage* next = (SubGarbage*)list_next;
            if (next)
                next->list_prev = (BodNode*)list_prev;

            SubGarbage* prev = (SubGarbage*)list_prev;
            if (prev)
                prev->list_next = (BodNode*)list_next;
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

    SubGarbage* cursor = owner_game->garbage_hazards.active_head;
    if (cursor == this) {
        cursor = next_active;
        owner_game->garbage_hazards.active_head = cursor;
        return cursor;
    } else if (cursor) {
        while (1) {
            if (cursor->next_active == this)
                break;
            cursor = cursor->next_active;
            if (cursor)
                continue;
            return cursor;
        }
        cursor->next_active = next_active;
        next_active = 0;
    }
    return cursor;
}
