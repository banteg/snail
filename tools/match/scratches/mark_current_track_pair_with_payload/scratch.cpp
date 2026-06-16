// mark_current_track_pair_with_payload @ 0x43d3d0 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"

Sprite* Player::mark_current_track_pair_with_payload(float payload)
{
    int payload_bits = *(int*)&payload;
    ghost_sprite_a->flags |= 0x40;
    ghost_sprite_b->flags |= 0x40;
    *(int*)&ghost_sprite_a->position.z = payload_bits;
    Sprite* second = ghost_sprite_b;
    *(int*)&second->position.z = payload_bits;
    return second;
}
