// initialize_subgoldy_ghost @ 0x43d230 (thiscall, ret 0x4)

struct Color4f {
    float r;
    float g;
    float b;
    float a;

    Color4f* set_color_rgba(float r, float g, float b, float a);
};

struct Sprite {
    int unknown_00;
    int flags;
    char unknown_08[0x2c - 0x08];
    Color4f color;
    char unknown_3c[0x48 - 0x3c];
    float x;
    float y;
    float z;
    char unknown_54[0x60 - 0x54];
    float scale_x;
    float scale_y;
    int unknown_68;
    int unknown_6c;
    char unknown_70[0x78 - 0x70];
    int unknown_78;
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

extern SpriteManager g_sprite_manager; // 0x790f30

class Player {
public:
    int initialize_subgoldy_ghost(int owner);

    char unknown_00[0x98];
    Sprite* ghost_sprite_a;
    Sprite* ghost_sprite_b;
};

int Player::initialize_subgoldy_ghost(int owner)
{
    Color4f color;

    ghost_sprite_a = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_a->flags |= 0x800;
    ghost_sprite_a->unknown_68 = 0;
    ghost_sprite_a->unknown_6c = 0;
    ghost_sprite_a->unknown_78 = 0;
    ghost_sprite_a->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_a->scale_x = 0.5f;
    ghost_sprite_a->scale_y = 0.5f;
    ghost_sprite_a->x = 4.5f;
    ghost_sprite_a->y = 1.0f;
    ghost_sprite_a->z = 0.0f;

    ghost_sprite_b = g_sprite_manager.allocate_sprite(owner, 159, -1, -1);
    ghost_sprite_b->flags |= 0x800;
    ghost_sprite_b->unknown_68 = 0;
    ghost_sprite_b->unknown_6c = 0;
    ghost_sprite_b->unknown_78 = 0;
    ghost_sprite_b->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    ghost_sprite_b->scale_x = 0.5f;
    ghost_sprite_b->scale_y = 0.5f;
    ghost_sprite_b->x = -4.5f;
    ghost_sprite_b->y = 1.0f;
    ghost_sprite_b->z = 0.0f;

    int clear_visible_mask = ~0x40;
    Sprite* first_ghost = ghost_sprite_a;
    first_ghost->flags &= clear_visible_mask;

    Sprite* second_ghost = ghost_sprite_b;
    return second_ghost->flags &= clear_visible_mask;
}
