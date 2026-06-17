// destroy_main_menu @ 0x419b30 (cdecl)

#include "border_manager.h"
#include "sprite.h"

extern char* g_game_base; // data_4df904

void destroy_main_menu()
{
    ((BorderManager*)(g_game_base + 0xb4c))->kill_all_borders();
    g_sprite_manager.kill_game_sprites();
}
