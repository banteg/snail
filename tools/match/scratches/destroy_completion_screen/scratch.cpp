// destroy_completion_screen @ 0x406060 (thiscall, ret)

#include "border_manager.h"

extern char* g_game_base; // data_4df904

class CompletionScreen {
public:
    int destroy_completion_screen();

    char unknown_00[0x08];
    int previous_frontend_state; // +0x08
    char unknown_0c[0x10 - 0x0c];
    FrontendWidget* heading; // +0x10
    FrontendWidget* body;    // +0x14
    FrontendWidget* button;  // +0x18
};

int CompletionScreen::destroy_completion_screen()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(heading);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(body);
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(button);
    int result = ((BorderManager*)(g_game_base + 0xb4c))->unhide_all_borders();
    *(int*)(g_game_base + 0x1b8) = previous_frontend_state;
    return result;
}
