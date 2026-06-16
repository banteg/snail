// mark_current_track_pair_with_payload @ 0x43d3d0 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"

Sprite* Player::mark_current_track_pair_with_payload(int payload)
{
    ghost_sprite_a->flags |= 0x40;
    ghost_sprite_b->flags |= 0x40;
    *(int*)&ghost_sprite_a->position.z = payload;
    Sprite* second = ghost_sprite_b;
    *(int*)&second->position.z = payload;
    return second;
}
