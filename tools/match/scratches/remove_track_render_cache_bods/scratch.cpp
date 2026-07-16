// remove_track_render_cache_bods @ 0x433f20 (thiscall)

#include <stddef.h>

#include "segment_cache.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);

void SegmentCache::remove_track_render_cache_bods()
{
    BodNode** next_ref =
        &slots[0][TRACK_RENDER_CACHE_FLOOR].bod.list_next;
    int rows = sizeof(slots) / sizeof(slots[0]);

    do {
        int count = sizeof(slots[0]) / sizeof(slots[0][0]);
        do {
            unsigned int* flags_ref = (unsigned int*)((char*)next_ref
                + (int)offsetof(BodNode, list_flags)
                - (int)offsetof(BodNode, list_next));
            if ((*flags_ref & BOD_FLAG_LINKED) != 0) {
                BodList* list = &g_game->active_bod_list;
                list->remove_bod((BodNode*)((char*)next_ref
                    - (int)offsetof(BodNode, list_next)));
            }
            next_ref =
                (BodNode**)((char*)next_ref + sizeof(TrackRenderCacheSlot));
            count--;
        } while (count);
        rows--;
    } while (rows);
}
