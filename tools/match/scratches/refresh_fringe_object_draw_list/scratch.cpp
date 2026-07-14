// refresh_fringe_object_draw_list @ 0x439b00 (thiscall, ret)

#include "fringe_object.h"
#include "bod_list.h"
#include "game_root.h"
#include "subgame_runtime.h"

int report_errorf(char* format, ...);

extern GameRoot* g_game; // data_4df904

void Fringe::refresh_fringe_object_draw_list()
{
    Color4f color;
    Color4f* resolved =
        g_game->subgame.get_track_skirt_color(&color);

    float current_z = position.z;
    this->color = *resolved;

    if (current_z < g_game->subgame.embedded_player()->interaction_max_z) {
        unsigned int flags = list_flags;
        BodList* list = &g_game->active_bod_list;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            return;
        }
        if ((flags & 0x40) != 0) {
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
        updated &= ~0x200;
        list_flags = updated;
    }
}
