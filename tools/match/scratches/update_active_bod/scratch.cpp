// update_active_bod @ 0x433e80 (thiscall, ret)

#include "active_bod.h"
#include "bod_list.h"
#include "game_root.h"

int report_errorf(char* format, ...);

extern GameRoot* g_game; // data_4df904

void ActiveBod::update_active_bod()
{
    if (world_z + 24.0f
        < g_game->subgame.embedded_player()->interaction_max_z) {
        unsigned int flags = list_flags;
        BodList* list = &g_game->active_bod_list;
        if ((flags & BOD_FLAG_LINKED) == 0) {
            report_errorf("List remove");
            return;
        }
        if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
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
        updated &= ~BOD_FLAG_LINKED;
        list_flags = updated;
    }
}
