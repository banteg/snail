// destroy_intro_screen @ 0x419920 (thiscall, ret)

#include "intro_screen_runtime.h"
#include "runtime_config.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

int IntroScreenRuntime::destroy_intro_screen()
{
    g_runtime_config.render_flags = saved_render_flags;

    char* game = g_game_base;
    if (*(unsigned char*)(game + 0x30d) == 1)
        *(int*)(game + 0x1b8) = 20;
    else
        *(int*)(game + 0x1b8) = 3;

    int result = renderable_count;
    int index = 0;
    if (result > 0) {
        BodNode** next_ref = &renderables[0].list_next;
        do {
            unsigned int* flags_ref = (unsigned int*)((char*)next_ref - 8);
            unsigned int flags = *flags_ref;
            BodList* list = (BodList*)(g_game_base + 0x5a8);
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
            next_ref = (BodNode**)((char*)next_ref + sizeof(IntroLogoRenderable));
        } while (index < result);
    }
    return result;
}
