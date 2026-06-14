// spawn_golb_impact_sprite @ 0x415d80 (thiscall, ret 0x4)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Sprite {
    void* object_ref;      // +0x00
    unsigned int flags;    // +0x04
    char unknown_08[0x48 - 0x08];
    Vector3 position;      // +0x48
    Vector3 velocity;      // +0x54
    float scale_x;         // +0x60
    float scale_y;         // +0x64
    int age;               // +0x68
    float progress_step;   // +0x6c
    int unknown_70;        // +0x70
    float lifetime_step;   // +0x74
    int gravity_step;      // +0x78
};

struct Player {
    char unknown_000[0x380];
    int player_slot;       // +0x380
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

extern unsigned char g_render_effect_flags; // data_4df934
extern SpriteManager g_sprite_manager;      // data_790f30

class GolbProjectile {
public:
    void spawn_golb_impact_sprite(Vector3* position);

    char unknown_000[0x278];
    Player* owner_player; // +0x278
};

void GolbProjectile::spawn_golb_impact_sprite(Vector3* position)
{
    unsigned char render_flags = g_render_effect_flags;

    if ((render_flags & 0x10) != 0) {
        Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x21, -1, -1);
        int zero = 0;
        int flags = sprite->flags;
        flags |= 0x800;
        Vector3 velocity = { 0.0f, 0.05f, 0.0f };
        Vector3* out_velocity = &sprite->velocity;
        sprite->flags = flags;
        sprite->age = zero;
        sprite->unknown_70 = zero;
        sprite->gravity_step = zero;
        sprite->progress_step = 0.055555552f;
        sprite->lifetime_step = 0.83333337f;
        sprite->scale_x = 0.5f;
        sprite->scale_y = 1.0f;
        *out_velocity = velocity;
        sprite->position = *position;
    }
}
