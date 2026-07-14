// destroy_intro_screen @ 0x419920 (thiscall, ret)

#include "game_root.h"
#include "intro_screen_runtime.h"
#include "runtime_config.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

int Logo::destroy_intro_screen()
{
    g_runtime_config.render_flags = saved_render_flags;

    GameRoot* game = g_game;
    if (game->players[0].high_score_entry_pending == 1)
        game->players[0].frontend_state = 20;
    else
        game->players[0].frontend_state = 3;

    int result = renderable_count;
    int index = 0;
    if (result > 0) {
        BodNode** next_ref = &letters[0].list_next;
        do {
            unsigned int* flags_ref = (unsigned int*)((char*)next_ref - 8);
            unsigned int flags = *flags_ref;
            BodList* list = &g_game->active_bod_list;
            BodNode* next;
            BodNode* prev;
            int updated;
            if ((flags & 0x200) == 0) {
                report_errorf("List remove");
                goto next_renderable;
            }
            if ((flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
                goto next_renderable;
            }

            next = *next_ref;
            if (next != 0)
                next->list_prev = *(BodNode**)((char*)next_ref - 4);

            prev = *(BodNode**)((char*)next_ref - 4);
            if (prev != 0)
                prev->list_next = *next_ref;
            else
                list->first = *next_ref;

            *next_ref = list->free_top;
            list->free_top = (BodNode*)((char*)next_ref - 0xc);

            updated = *flags_ref;
            updated &= ~0x200;
            *flags_ref = updated;

next_renderable:
            result = renderable_count;
            ++index;
            next_ref = (BodNode**)((char*)next_ref + sizeof(LogoLetter));
        } while (index < result);
    }
    return result;
}
