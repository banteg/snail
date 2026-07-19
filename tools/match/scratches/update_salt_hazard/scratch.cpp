// update_salt_hazard @ 0x441c10 (thiscall, ret)

#include "game_root.h"
#include "salt_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"

int report_errorf(char* format, ...);

void Salt::update_salt_hazard()
{
    if (owner_game->subgame_pause_gate)
        return;

    switch (state) {
    case SALT_STATE_RECYCLE_PENDING: {
        GameRoot* game = g_game;
        SaltListAnchor* anchor = &game->active_bod_list;
        int flags = list_flags;
        if ((flags & BOD_FLAG_LINKED) == 0) {
            report_errorf("List remove");
            goto first_remove_error;
        } else {
            if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
                report_errorf("List remove NEXTBOD");
                state = SALT_STATE_INACTIVE;
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
                state = SALT_STATE_INACTIVE;
                updated &= ~BOD_FLAG_LINKED;
                list_flags = updated;
            }
        }
        return;
    first_remove_error:
        state = SALT_STATE_INACTIVE;
        return;
    }
    case SALT_STATE_ACTIVE: {
        float alpha =
            1.0f - (transform.position.z - owner_game->player.transform.position.z) * 0.021739131f;
        fade_alpha = alpha;
        if (alpha < 0.0f) {
            alpha = 0.0f;
        } else if (alpha > 1.0f) {
            alpha = 1.0f;
        }
        fade_alpha = alpha;
        color.set_color_alpha(0.899999976f);
        if (transform.position.z < owner_game->player.interaction_max_z)
            state = SALT_STATE_RECYCLE_PENDING;
        return;
    }
    }
}
