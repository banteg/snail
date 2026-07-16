// destroy_intro_screen @ 0x419920 (thiscall)

#include "game_root.h"
#include "intro_screen_runtime.h"
#include "runtime_config.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

void Logo::destroy_intro_screen()
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
            unsigned int* flags_ref = &BOD_NEXT_LINK_FLAGS(next_ref);
            unsigned int flags = *flags_ref;
            BodList* list = &g_game->active_bod_list;
            BodNode* next;
            BodNode* prev;
            int updated;
            if ((flags & BOD_FLAG_LINKED) == 0) {
                report_errorf("List remove");
                goto next_renderable;
            }
            if ((flags & BOD_FLAG_NEXT_UPDATE_GUARD) != 0) {
                report_errorf("List remove NEXTBOD");
                goto next_renderable;
            }

            next = *next_ref;
            if (next != 0)
                next->list_prev = BOD_NEXT_LINK_PREV(next_ref);

            prev = BOD_NEXT_LINK_PREV(next_ref);
            if (prev != 0)
                prev->list_next = *next_ref;
            else
                list->first = *next_ref;

            *next_ref = list->free_top;
            list->free_top = BOD_NODE_FROM_NEXT_LINK(next_ref);

            updated = *flags_ref;
            updated &= ~BOD_FLAG_LINKED;
            *flags_ref = updated;

next_renderable:
            result = renderable_count;
            ++index;
            next_ref = (BodNode**)((char*)next_ref + sizeof(LogoLetter));
        } while (index < result);
    }
}
