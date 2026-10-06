// remove_track_render_cache_bods @ 0x433f20 (thiscall)

#include "segment_cache.h"
#include "game_root.h"

int report_errorf(char* format, ...);

void SegmentCache::remove_track_render_cache_bods()
{
    for (int row = 0; row < TRACK_RENDER_CACHE_ROW_COUNT; ++row) {
        for (int family = 0; family < TRACK_RENDER_CACHE_FAMILY_COUNT; ++family) {
            if ((slots[row][family].list_flags & BOD_FLAG_LINKED) != 0) {
                g_game->active_bod_list.remove_bod(&slots[row][family]);
            }
        }
    }
}
