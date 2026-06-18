// uninit_pause_menu @ 0x440600 (thiscall, ret)

#include "border_manager.h"

extern char* g_game_base; // data_4df904

class MouseCursorState {
public:
    int release_mouse_cursor();
};

class PauseMenu {
public:
    int uninit_pause_menu();

    FrontendWidget* options_widget;  // +0x00
    FrontendWidget* end_game_widget; // +0x04
    FrontendWidget* resume_widget;   // +0x08
};

int PauseMenu::uninit_pause_menu()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(options_widget);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(end_game_widget);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(resume_widget);
    return ((MouseCursorState*)(g_game_base + 0x290))->release_mouse_cursor();
}
