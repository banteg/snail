// update_pause_menu @ 0x4407a0 (thiscall, ret)

#include "completion_screen.h"

extern char* g_game_base; // data_4df904

void* PauseMenu::update_pause_menu()
{
    unsigned int flags = options_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        options_widget->widget_flags = flags & ~0x20u;
        *(unsigned char*)(g_game_base + 0x4f38c) = 0;
        char* game = g_game_base;
        *(int*)(game + 0x4f388) = *(int*)(game + 0x1b8);
        *(int*)(g_game_base + 0x1b8) = 6;
        return game;
    }

    FrontendWidget* resume = resume_widget;
    flags = resume->widget_flags;
    if ((flags & 0x20) != 0) {
        resume->widget_flags = flags & ~0x20u;
        uninit_pause_menu();
        char* game = g_game_base;
        *(int*)(game + 0x74654) = 2;
        *(unsigned char*)(g_game_base + 0x74620) = 1;
        return game;
    }

    FrontendWidget* end_game = end_game_widget;
    void* result = (void*)end_game->widget_flags;
    if (((unsigned int)result & 0x20) != 0) {
        end_game->widget_flags = (unsigned int)result & ~0x20u;
        char* game = g_game_base;
        *(int*)(game + 0x4f3b4) = *(int*)(game + 0x1b8);
        game = g_game_base;
        if (*(int*)(game + 0x74658) == 7) {
            *(int*)(game + 0x4f3ac) = 7;
        } else if (*(unsigned char*)(game + 0x1066be9) == 1) {
            *(int*)(game + 0x4f3ac) = 3;
        } else {
            *(int*)(game + 0x4f3ac) = 2;
        }
        result = g_game_base;
        *(int*)((char*)result + 0x12e55e0) = 2;
        *(int*)(g_game_base + 0x1b8) = 8;
    }
    return result;
}
