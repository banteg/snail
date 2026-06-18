// remove_track_render_cache_bods @ 0x433f20 (thiscall)

#include "track_render_cache.h"

extern char* volatile g_game_base; // data_4df904
int report_errorf(char* format, ...);

void TrackRenderCacheManager::remove_track_render_cache_bods()
{
    BodNode** next_ref = &slots[0][0].bod.list_next;
    int rows = 0x8f;
    int live_mask = 0x200;
    int clear_live_mask = ~0x200;

    do {
        int count = 5;
        do {
            unsigned int* flags_ref = (unsigned int*)((char*)next_ref - 8);
            if ((*flags_ref & live_mask) != 0) {
                BodList* list = (BodList*)(g_game_base + 0x5a8);
                unsigned int flags = *flags_ref;
                if ((live_mask & flags) == 0) {
                    report_errorf("List remove");
                }
                if ((flags & 0x40) != 0) {
                    report_errorf("List remove NEXTBOD");
                } else {
                    BodNode* next = *next_ref;
                    if (next != 0)
                        next->list_prev = *(BodNode**)((char*)next_ref - 4);

                    BodNode* prev = *(BodNode**)((char*)next_ref - 4);
                    if (prev != 0)
                        prev->list_next = *next_ref;
                    else
                        list->first = *next_ref;

                    *next_ref = list->free_top;
                    list->free_top = (BodNode*)((char*)next_ref - 0xc);
                    *flags_ref &= clear_live_mask;
                }
            }
            next_ref = (BodNode**)((char*)next_ref + 0x3c);
            count--;
        } while (count);
        rows--;
    } while (rows);
}
