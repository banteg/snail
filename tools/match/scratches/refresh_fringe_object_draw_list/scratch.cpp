// refresh_fringe_object_draw_list @ 0x439b00 (thiscall, ret)

#include "fringe_object.h"
#include "bod_list.h"

class SubgameRuntime {
public:
    Color4f* get_track_skirt_color(Color4f* out);
};

int report_errorf(char* format, ...);

extern char* g_game_base; // data_4df904

void FringeObject::refresh_fringe_object_draw_list()
{
    Color4f color;
    Color4f* resolved =
        ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&color);

    float current_z = position.z;
    this->color = *resolved;

    if (current_z < *(float*)(g_game_base + 0x4326fc)) {
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
