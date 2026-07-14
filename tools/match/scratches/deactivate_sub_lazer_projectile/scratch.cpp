// deactivate_sub_lazer_projectile @ 0x441740 (thiscall, ret)
// Unlinks the slot from the live list and pushes it onto the free stack
// anchored at game+0x5a8; clears the live state either way.

#include "sub_lazer_types.h"
#include "game_root.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

void SubLazer::deactivate_sub_lazer_projectile()
{
    BodList* anchor = &((GameRoot*)g_game_base)->active_bod_list;
    int flags = list_flags;
    BodNode* next;
    BodNode* prev;
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
        state = SUB_LAZER_STATE_INACTIVE;
    } else {
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            state = SUB_LAZER_STATE_INACTIVE;
        } else {
            next = list_next;
            if (next)
                next->list_prev = list_prev;
            prev = list_prev;
            if (prev)
                prev->list_next = list_next;
            else
                anchor->first = list_next;
            list_next = anchor->free_top;
            anchor->free_top = this;
            int updated = list_flags;
            state = SUB_LAZER_STATE_INACTIVE;
            updated &= ~0x200;
            list_flags = updated;
        }
    }
}
