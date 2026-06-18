// update_track_render_cache_rows @ 0x433b30 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_render_cache.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

#define ACTIVATE_CACHE_SLOT(slot, active_list)                                      \
    if (((slot)->bod.list_flags & live_mask) != 0) {                               \
        report_errorf("List ADDafter");                                            \
    } else {                                                                       \
        (slot)->bod.list_prev = (active_list);                                     \
        (slot)->bod.list_next = (active_list)->list_next;                          \
        (active_list)->list_next = &(slot)->bod;                                   \
        if ((slot)->bod.list_next != 0)                                            \
            (slot)->bod.list_next->list_prev = &(slot)->bod;                       \
        (slot)->bod.list_flags |= live_mask;                                       \
    }

void TrackRenderCacheManager::update_track_render_cache_rows()
{
    int live_mask = 0x200;
    int zero = 0;
    if (*(float*)(g_game_base + 0x42fdec) + 46.0f <= next_cache_row_z)
        return;

    do {
        BodNode* active_list = (BodNode*)(g_game_base + 0x3ca17c);
        TrackRenderCacheSlot* slot = &slots[next_cache_row_index][4];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        Vector3* position = &slots[next_cache_row_index][4].bod.position;
        *(int*)&position->z = zero;
        *(int*)&position->y = zero;
        *(int*)&position->x = zero;
        Color4f skirt_color;
        slots[next_cache_row_index][4].bod.color =
            *((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&skirt_color);

        active_list = (BodNode*)(g_game_base + 0x3ca1b4);
        slot = &slots[next_cache_row_index][0];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][0].bod.position;
        *(int*)&position->z = zero;
        *(int*)&position->y = zero;
        *(int*)&position->x = zero;
        slots[next_cache_row_index][0].bod.color.set_color_white();

        active_list = (BodNode*)(g_game_base + 0x3ca1b4);
        slot = &slots[next_cache_row_index][1];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][1].bod.position;
        *(int*)&position->z = zero;
        *(int*)&position->y = zero;
        *(int*)&position->x = zero;
        slots[next_cache_row_index][1].bod.color.set_color_white();

        active_list = (BodNode*)(g_game_base + 0x3ca1b4);
        slot = &slots[next_cache_row_index][3];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][3].bod.position;
        *(int*)&position->z = zero;
        *(int*)&position->y = zero;
        *(int*)&position->x = zero;
        slots[next_cache_row_index][3].bod.color.set_color_white();

        active_list = (BodNode*)(g_game_base + 0x3ca1b4);
        slot = &slots[next_cache_row_index][2];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][2].bod.position;
        *(int*)&position->z = zero;
        *(int*)&position->y = zero;
        *(int*)&position->x = zero;
        slots[next_cache_row_index][2].bod.color.set_color_white();

        next_cache_row_z += 24.0f;
        next_cache_row_index++;
    } while (*(float*)(g_game_base + 0x42fdec) + 46.0f > next_cache_row_z);
}
