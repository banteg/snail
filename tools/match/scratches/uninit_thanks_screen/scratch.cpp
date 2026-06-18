// uninit_thanks_screen @ 0x4340c0 (thiscall, ret)

#include "thanks_screen.h"

extern char* g_game_base; // data_4df904

class BorderManager {
public:
    int kill_border(void* border);
};

void ThanksScreen::uninit_thanks_screen()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(message_widget);
    *(int*)(g_game_base + 0x1b8) = 14;
}
