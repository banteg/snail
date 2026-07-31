// remove_track_render_cache_bods @ 0x433f20 (thiscall)

#include "segment_cache.h"
#include "game_root.h"

int report_errorf(char* format, ...);

void SegmentCache::remove_track_render_cache_bods()
{
    BodNode** next_ref =
        &slots[0][TRACK_RENDER_CACHE_FLOOR].list_next;
    int rows = sizeof(slots) / sizeof(slots[0]);

    do {
        int count = sizeof(slots[0]) / sizeof(slots[0][0]);
        do {
            BodNode* node = BOD_NODE_FROM_NEXT_LINK(next_ref);
            if ((node->list_flags & BOD_FLAG_LINKED) != 0) {
                BodList* list = &g_game->active_bod_list;
                list->remove_bod(node);
            }
            next_ref += sizeof(TrackRenderCacheSlot) / sizeof(*next_ref);
            count--;
        } while (count);
        rows--;
    } while (rows);
}
