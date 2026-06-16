// deactivate_sub_lazer_projectile @ 0x441740 (thiscall, ret)
// Unlinks the slot from the live list and pushes it onto the free stack
// anchored at game+0x5a8; clears the live state either way.

#include "sub_lazer_types.h"

class Game {
public:
    char unknown_00[0x5a8];
    SubLazerListAnchor sub_lazer_free_anchor; // +0x5a8
};

extern Game* volatile g_game; // data_4df904
int report_errorf(char* format, ...);

int SubLazerSlot::deactivate_sub_lazer_projectile()
{
    SubLazerListAnchor* anchor = &g_game->sub_lazer_free_anchor;
    int flags = list_flags;
    int result;
    if ((flags & 0x200) == 0) {
        result = report_errorf("List remove");
        state = 0;
    } else {
        if ((flags & 0x40) != 0) {
            result = report_errorf("List remove NEXTBOD");
            state = 0;
        } else {
            if (list_next)
                list_next->list_prev = list_prev;
            if (list_prev)
                list_prev->list_next = list_next;
            else
                anchor->first = list_next;
            list_next = anchor->free_top;
            anchor->free_top = this;
            int updated = list_flags;
            state = 0;
            updated &= ~0x200;
            list_flags = updated;
            result = updated;
        }
    }
    return result;
}
