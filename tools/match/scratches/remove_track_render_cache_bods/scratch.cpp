// remove_track_render_cache_bods @ 0x433f20 (thiscall)

#include "segment_cache.h"
#include "game_root.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

void SegmentCache::remove_track_render_cache_bods()
{
    BodNode** next_ref = &slots[0][0].bod.list_next;
    int rows = 0x8f;

    do {
        int count = 5;
        do {
            unsigned int* flags_ref = (unsigned int*)((char*)next_ref - 8);
            if ((*flags_ref & 0x200) != 0) {
                BodList* list = &((GameRoot*)g_game_base)->active_bod_list;
                list->remove_bod((BodNode*)((char*)next_ref - 0xc));
            }
            next_ref = (BodNode**)((char*)next_ref + 0x3c);
            count--;
        } while (count);
        rows--;
    } while (rows);
}
