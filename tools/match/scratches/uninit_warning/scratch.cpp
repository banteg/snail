// uninit_warning @ 0x446f10 (thiscall, tailcall)

#include "warning_actor.h"

extern char* g_game_base; // data_4df904

struct BorderManager {
    void kill_border(FrontendWidget* border);
};

void WarningActor::uninit_warning()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
}
