// uninit_warning @ 0x446f10 (thiscall, tailcall)

#include "border_manager.h"
#include "warning.h"

extern char* g_game_base; // data_4df904

void Warning::uninit_warning()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_border(border);
}
