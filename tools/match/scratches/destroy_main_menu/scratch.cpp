// cRMainMenu::UnInit @ 0x419b30

#include "game_root.h"
#include "sprite.h"


void cRMainMenu::UnInit()
{
    g_game->border_manager.kill_all_borders();
    g_sprite_manager.KillGame();
}
