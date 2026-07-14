// MainMenu::destroy_main_menu @ 0x419b30

#include "game_root.h"
#include "sprite.h"

extern GameRoot* g_game; // data_4df904

void MainMenu::destroy_main_menu()
{
    g_game->border_manager.kill_all_borders();
    g_sprite_manager.kill_game_sprites();
}
