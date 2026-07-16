// update_row_model @ 0x443070 (thiscall, ret)

#include "game_root.h"
#include "object_render_types.h"
#include "track_attachment_types.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);

void RowModel::update_row_model()
{
    Vector3* position = &transform.position;
    position->x = velocity.x + position->x;
    position->y = velocity.y + position->y;
    position->z = velocity.z + position->z;

    if (((Object*)object)->bounds_max.z
            + g_game->subgame.embedded_player()->interaction_max_z
        > transform.position.z) {
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

        BodNode* next = list_next;
        if (next != 0)
            next->list_prev = list_prev;

        BodNode* prev = list_prev;
        if (prev != 0)
            prev->list_next = list_next;
        else
            list->first = list_next;

        list_next = list->free_top;
        list->free_top = this;

        unsigned int updated = list_flags;
        updated &= ~BOD_FLAG_LINKED;
        list_flags = updated;
    }
}
