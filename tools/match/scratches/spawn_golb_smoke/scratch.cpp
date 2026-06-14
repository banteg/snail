// spawn_golb_smoke @ 0x415c60 (thiscall, ret 0x4)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Color4f {
    Color4f* set_color_rgba(float r, float g, float b, float a);

    float r;
    float g;
    float b;
    float a;
};

struct Game {
    char unknown_00[0x38];
    float subgame_rate; // +0x38
};

struct Player {
    char unknown_000[0x380];
    int player_slot; // +0x380
};

struct Sprite {
    void* object_ref;       // +0x00
    unsigned int flags;     // +0x04
    char unknown_08[0x2c - 0x08];
    Color4f color;          // +0x2c
    char unknown_3c[0x48 - 0x3c];
    Vector3 position;       // +0x48
    Vector3 velocity;       // +0x54
    float scale_x;          // +0x60
    float scale_y;          // +0x64
    float progress;         // +0x68
    float progress_step;    // +0x6c
    float unknown_70;       // +0x70
    float lifetime_step;    // +0x74
    float gravity_step;     // +0x78
};

struct SpriteManager {
    Sprite* allocate_sprite(int player_slot, int sprite_id, int texture_a, int texture_b);
};

extern SpriteManager g_sprite_manager; // data_790f30

class GolbProjectile {
public:
    void spawn_golb_smoke(Vector3* position);

    char unknown_000[0x24c];
    Vector3 velocity;       // +0x24c
    char unknown_258[0x270 - 0x258];
    Game* game;             // +0x270
    void* object_ref;       // +0x274
    Player* owner_player;   // +0x278
};

void GolbProjectile::spawn_golb_smoke(Vector3* position)
{
    Sprite* sprite = g_sprite_manager.allocate_sprite(
        owner_player->player_slot,
        128,
        -1,
        -1);

    unsigned int flags = sprite->flags;
    sprite->progress = 0.0f;
    flags |= 0x800;
    sprite->flags = flags;

    float rate = game->subgame_rate;
    sprite->unknown_70 = 0.0f;
    sprite->progress_step = rate * 0.16666667f;
    sprite->lifetime_step = game->subgame_rate * 0.41666669f;

    Color4f color;
    sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    sprite->scale_x = 0.1f;
    sprite->scale_y = 0.5f;

    color.r = velocity.x * 0.40000001f;
    color.g = velocity.y * 0.40000001f;
    color.b = velocity.z * 0.40000001f;
    Vector3* out_velocity = &sprite->velocity;
    Vector3* out_position = &sprite->position;
    out_velocity->x = color.r;
    sprite->gravity_step = 0.0f;
    out_velocity->y = color.g;
    out_velocity->z = color.b;
    *out_position = *position;
}
