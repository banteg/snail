// set_subgoldy_ghost_z @ 0x43d3d0 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"

void Player::set_subgoldy_ghost_z(float ghost_z)
{
    ghost_sprite_a->flags |= 0x40;
    ghost_sprite_b->flags |= 0x40;
    ghost_sprite_a->position.z = ghost_z;
    Sprite* second = ghost_sprite_b;
    second->position.z = ghost_z;
}
