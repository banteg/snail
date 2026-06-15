// set_sprite_manager_paused @ 0x44e540 (thiscall, ret byte)

#include "sprite.h"

char SpriteManager::set_sprite_manager_paused(char paused_)
{
    paused = paused_;
    return paused_;
}
