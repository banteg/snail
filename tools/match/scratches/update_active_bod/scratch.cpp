// update_active_bod @ 0x433e80 (thiscall, ret)

#include "active_bod.h"
#include "bod_list.h"

int report_errorf(char* format, ...);

extern char* g_game_base; // data_4df904

void ActiveBod::update_active_bod()
{
    if (world_z + 24.0f < *(float*)(g_game_base + 0x4326fc)) {
        unsigned int flags = list_flags;
        BodList* list = (BodList*)(g_game_base + 0x5a8);
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            return;
        }

        ActiveBod* next = list_next;
        if (next != 0)
            next->list_prev = list_prev;

        ActiveBod* prev = list_prev;
        if (prev != 0)
            prev->list_next = list_next;
        else
            list->first = (BodNode*)list_next;

        list_next = (ActiveBod*)list->free_top;
        list->free_top = (BodNode*)this;

        unsigned int updated = list_flags;
        updated &= ~0x200;
        list_flags = updated;
    }
}
