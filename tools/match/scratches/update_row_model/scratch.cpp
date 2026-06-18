// update_row_model @ 0x443070 (thiscall, ret)

#include "bod_types.h"
#include "object_render_types.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

class RowModel : public RenderableBod {
public:
    void update_row_model();

    char unknown_078[0x80 - 0x78];
    Vector3 velocity; // +0x80
};

void RowModel::update_row_model()
{
    Vector3* position = &transform.position;
    position->x = velocity.x + position->x;
    position->y = velocity.y + position->y;
    position->z = velocity.z + position->z;

    if (((Object*)object)->bounds_max.z
            + *(float*)(g_game_base + 0x4326fc) > transform.position.z) {
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
