// initialize_game_player @ 0x408000 (thiscall)

#include "game_root.h"

extern void* g_game_player_callback_table;  // data_4972f4

GamePlayer* GamePlayer::initialize_game_player()
{
    initialize_renderable_bod();
    camera.initialize_renderable_bod();
    camera.vtable = &g_noop_runtime_callback_table;
    frontend_overlay.target.noop_this_constructor();
    frontend_overlay.current.noop_this_constructor();
    vtable = &g_game_player_callback_table;
    return this;
}
