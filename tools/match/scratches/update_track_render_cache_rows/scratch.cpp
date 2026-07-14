// update_track_render_cache_rows @ 0x433b30 (thiscall, ret)

#include "game_root.h"
#include "subgame_runtime.h"
#include "segment_cache.h"

extern GameRoot* g_game; // data_4df904
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

void SegmentCache::update_track_render_cache_rows()
{
    int live_mask = 0x200;
    if (g_game->subgame.embedded_player()->live_matrix.position.z + 46.0f <= next_cache_row_z)
        return;

    do {
        BodNode* active_list = &g_game->subgame.fringe_attachment_list_head;
        TrackRenderCacheSlot* slot = &slots[next_cache_row_index][4];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        Vector3* position = &slots[next_cache_row_index][4].bod.position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        Color4f skirt_color;
        slots[next_cache_row_index][4].bod.color =
            *g_game->subgame.get_track_skirt_color(&skirt_color);

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][0];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][0].bod.position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][0].bod.color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][1];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][1].bod.position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][1].bod.color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][3];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][3].bod.position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][3].bod.color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][2];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][2].bod.position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][2].bod.color.set_color_white();

        next_cache_row_z += 24.0f;
        next_cache_row_index++;
    } while (g_game->subgame.embedded_player()->live_matrix.position.z + 46.0f > next_cache_row_z);
}
