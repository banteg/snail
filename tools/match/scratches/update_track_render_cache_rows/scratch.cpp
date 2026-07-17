// update_track_render_cache_rows @ 0x433b30 (thiscall, ret)

#include "game_root.h"
#include "subgame_runtime.h"
#include "segment_cache.h"

int report_errorf(char* format, ...);

#define ACTIVATE_CACHE_SLOT(slot, active_list)                                      \
    if (((slot)->list_flags & live_mask) != 0) {                                   \
        report_errorf("List ADDafter");                                            \
    } else {                                                                       \
        (slot)->list_prev = (active_list);                                         \
        (slot)->list_next = (active_list)->list_next;                              \
        (active_list)->list_next = (slot);                                         \
        if ((slot)->list_next != 0)                                                \
            (slot)->list_next->list_prev = (slot);                                 \
        (slot)->list_flags |= live_mask;                                           \
    }

void SegmentCache::update_track_render_cache_rows()
{
    int live_mask = 0x200;
    if (g_game->subgame.embedded_player()->transform.position.z + 46.0f <= next_cache_row_z)
        return;

    do {
        BodNode* active_list = &g_game->subgame.fringe_attachment_list_head;
        TrackRenderCacheSlot* slot =
            &slots[next_cache_row_index][TRACK_RENDER_CACHE_FRINGE];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        Vector3* position =
            &slots[next_cache_row_index][TRACK_RENDER_CACHE_FRINGE].position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        tColour skirt_color;
        slots[next_cache_row_index][TRACK_RENDER_CACHE_FRINGE].color =
            *g_game->subgame.get_track_skirt_color(&skirt_color);

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][TRACK_RENDER_CACHE_FLOOR];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][TRACK_RENDER_CACHE_FLOOR].position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][TRACK_RENDER_CACHE_FLOOR]
            .color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][TRACK_RENDER_CACHE_SLIDE];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][TRACK_RENDER_CACHE_SLIDE].position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][TRACK_RENDER_CACHE_SLIDE]
            .color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][TRACK_RENDER_CACHE_RAMP];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][TRACK_RENDER_CACHE_RAMP].position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][TRACK_RENDER_CACHE_RAMP]
            .color.set_color_white();

        active_list = &g_game->subgame.track_body_list_head;
        slot = &slots[next_cache_row_index][TRACK_RENDER_CACHE_WARNING];
        ACTIVATE_CACHE_SLOT(slot, active_list);
        position = &slots[next_cache_row_index][TRACK_RENDER_CACHE_WARNING].position;
        position->z = 0.0f;
        position->y = 0.0f;
        position->x = 0.0f;
        slots[next_cache_row_index][TRACK_RENDER_CACHE_WARNING]
            .color.set_color_white();

        next_cache_row_z += 24.0f;
        next_cache_row_index++;
    } while (g_game->subgame.embedded_player()->transform.position.z + 46.0f > next_cache_row_z);
}
