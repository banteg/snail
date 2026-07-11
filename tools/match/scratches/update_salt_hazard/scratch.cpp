// update_salt_hazard @ 0x441c10 (thiscall, ret)

#include "game_root.h"
#include "salt_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);

void SaltHazardSlot::update_salt_hazard()
{
    if (owner_game->subgame_pause_gate)
        return;

    switch (state) {
    case 2: {
        GameRoot* game = g_game;
        SaltListAnchor* anchor = &game->active_bod_list;
        int flags = list_flags;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            goto first_remove_error;
        } else {
            if ((flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
                state = 0;
                return;
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
            }
        }
        return;
    first_remove_error:
        state = 0;
        return;
    }
    case 1: {
        float alpha =
            1.0f - (position.z - owner_game->player.position.z) * 0.021739131f;
        fade_alpha() = alpha;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        } else if (alpha > 1.0f) {
            alpha = 1.0f;
        }
        fade_alpha() = alpha;
        color.set_color_alpha(0x3f666666);
        if (position.z < owner_game->player.interaction_max_z)
            state = 2;
        return;
    }
    }
}
