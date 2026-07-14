// uninit_pause_menu @ 0x440600 (thiscall, ret)

#include "game_root.h"

extern GameRoot* g_game; // data_4df904

class PauseMenuMouseCursorReleaseView {
public:
    int release_mouse_cursor();
};

class PauseMenuTeardownView {
public:
    int uninit_pause_menu();

    FrontendWidget* options_widget;  // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget;   // +0x08
};

int PauseMenuTeardownView::uninit_pause_menu()
{
    g_game->border_manager.kill_border(options_widget);
    g_game->border_manager.kill_border(end_game_widget);
    g_game->border_manager.kill_border(resume_widget);
    return ((PauseMenuMouseCursorReleaseView*)&g_game->players[0].mouse_cursor)
        ->release_mouse_cursor();
}
