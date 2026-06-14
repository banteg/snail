// spawn_golb_trail_sprite @ 0x415bb0 (thiscall, ret 0x4)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Sprite {
    void* object_ref; // +0x00
    unsigned int flags; // +0x04
    char unknown_08[0x48 - 0x08];
    Vector3 position; // +0x48
    Vector3 velocity; // +0x54
    float scale_x; // +0x60
    float scale_y; // +0x64
    int age; // +0x68
    float progress_step; // +0x6c
    int unknown_70; // +0x70
    int unknown_74; // +0x74
    int gravity_step; // +0x78
};

struct Player {
    char unknown_000[0x338];
    int movement_flags; // +0x338
    char unknown_33c[0x380 - 0x33c];
    int player_slot; // +0x380
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

extern SpriteManager g_sprite_manager; // data_790f30

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
    int zero = 0;
    int flags = sprite->flags;
    flags |= 0x800;
    sprite->age = zero;
    sprite->flags = flags;

    int movement_flags = owner_player->movement_flags;
    if ((movement_flags & 1) != 0)
        sprite->progress_step = 0.23809524f;
    else if ((movement_flags & 2) != 0)
        sprite->progress_step = 0.33333334f;

    sprite->progress_step = 0.55555558f;
    sprite->unknown_70 = zero;
    sprite->unknown_74 = zero;
    sprite->scale_x = 0.2f;
    sprite->scale_y = 0.03f;
    Vector3* velocity = &sprite->velocity;
    velocity->z = 0.0f;
    velocity->y = 0.0f;
    velocity->x = 0.0f;
    sprite->gravity_step = zero;
    sprite->position = *position;
    sprite->object_ref = object_ref;
    return sprite;
}
