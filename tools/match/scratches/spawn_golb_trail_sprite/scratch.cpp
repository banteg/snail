// spawn_golb_trail_sprite @ 0x415bb0 (thiscall, ret 0x4)

#include "sprite.h"
#include "player.h"

class GolbProjectile {
public:
    Sprite* spawn_golb_trail_sprite(Vector3* position);

    char unknown_000[0x274];
    void* object_ref; // +0x274
    Player* owner_player; // +0x278
};

Sprite* GolbProjectile::spawn_golb_trail_sprite(Vector3* position)
{
    Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x21, -1, -1);
    int flags = sprite->flags;
    flags |= 0x800;
    sprite->progress = 0.0f;
    sprite->flags = flags;

    int movement_flags = owner_player->movement_flags;
    if ((movement_flags & 1) != 0)
        sprite->progress_step = 0.23809524f;
    else if ((movement_flags & 2) != 0)
        sprite->progress_step = 0.33333334f;

    sprite->progress_step = 0.55555558f;
    sprite->lifetime = 0.0f;
    sprite->lifetime_step = 0.0f;
    sprite->size_start = 0.2f;
    sprite->size_end = 0.03f;
    Vector3* velocity = &sprite->velocity;
    velocity->z = 0.0f;
    velocity->y = 0.0f;
    velocity->x = 0.0f;
    sprite->gravity_step = 0.0f;
    sprite->position = *position;
    sprite->object_ref = object_ref;
    return sprite;
}
