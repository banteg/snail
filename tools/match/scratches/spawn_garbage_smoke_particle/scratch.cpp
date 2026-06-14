// spawn_garbage_smoke_particle @ 0x43d5a0 (thiscall, ret 0xc)

struct Vec3 {
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
    char unknown_00[0x380];
    int player_slot; // +0x380
};

struct Sprite;

struct SpriteManager {
    Sprite* allocate_sprite(int player_slot, int sprite_id, int texture_a, int texture_b);
};

struct Sprite {
    char unknown_00[0x04];
    unsigned int flags; // +0x04
    char unknown_08[0x2c - 0x08];
    Color4f color; // +0x2c
    char unknown_3c[0x48 - 0x3c];
    Vec3 position; // +0x48
    Vec3 velocity; // +0x54
    float scale_x; // +0x60
    float scale_y; // +0x64
    float progress; // +0x68
    float progress_step; // +0x6c
    float unknown_70; // +0x70
    float lifetime_step; // +0x74
    float unknown_78; // +0x78
};

class GarbageHazardSlot {
public:
    char spawn_garbage_smoke_particle(Vec3* position, Vec3* velocity, Player* player);

    char unknown_00[0x8c];
    Game* game; // +0x8c
};

extern unsigned char g_render_flags; // byte_4df934
extern SpriteManager g_sprite_manager; // data_790f30

char GarbageHazardSlot::spawn_garbage_smoke_particle(
    Vec3* position,
    Vec3* velocity,
    Player* player)
{
    char result = g_render_flags;
    if ((result & 0x10) != 0) {
        Sprite* sprite = g_sprite_manager.allocate_sprite(
            player->player_slot,
            33,
            -1,
            -1);
        sprite->progress = 0.0f;
        sprite->flags |= 0x800;
        sprite->progress_step = game->subgame_rate * 0.033333335f;
        sprite->unknown_70 = 0.0f;
        sprite->lifetime_step = game->subgame_rate * 0.41666669f;

        Color4f color;
        sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        sprite->scale_x = 0.30000001f;
        sprite->scale_y = 1.3f;

        color.r = velocity->x * 0.2f;
        color.g = velocity->y * 0.2f;
        color.b = velocity->z * 0.2f;
        sprite->velocity.x = color.r;
        sprite->unknown_78 = 0.0f;
        sprite->velocity.y = color.g;
        sprite->velocity.z = color.b;

        sprite->position = *position;
        result = *(char*)&position->z;
    }
    return result;
}
