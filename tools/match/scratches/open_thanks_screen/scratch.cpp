// open_thanks_screen @ 0x433fc0 (thiscall, ret)

#include "thanks_screen.h"

extern char* g_game_base; // data_4df904

ThanksScreen* ThanksScreenOwner::open_thanks_screen()
{
    ThanksScreen* result = (ThanksScreen*)(g_game_base + 0x74618);
    thanks_screen = result;
    return result;
}
