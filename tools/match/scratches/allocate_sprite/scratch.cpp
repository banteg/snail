// allocate_sprite @ 0x44e2a0 (thiscall, ret 0x10)

struct TextureRef {
    unsigned int flags; // +0x00
    char unknown_04[0x90 - 0x04];
    int frame_count; // +0x90
    int frame_progress_step; // +0x94
};

extern TextureRef* g_sprite_texture_table[]; // data_78ff90

class Sprite {
public:
    void initialize_sprite();

    void* object_ref; // +0x00
    unsigned int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    char unknown_14[0x1c - 0x14];
    TextureRef* texture_ref; // +0x1c
    TextureRef* texture_ref_a; // +0x20
    TextureRef* texture_ref_b; // +0x24
    char unknown_28[0x64 - 0x28];
    float scale_y; // +0x64
    char unknown_68[0x9c - 0x68];
    int texture_id; // +0x9c
    int frame_count; // +0xa0
    int frame; // +0xa4
    int frame_step; // +0xa8
    int frame_progress; // +0xac
    int frame_progress_step; // +0xb0
};

extern Sprite g_sprite_sentinel; // data_814cb0

class SpriteManager {
public:
    Sprite* allocate_sprite(int owner, int texture_id, int texture_a, int texture_b);

    char unknown_00000[0x83d64];
    Sprite* active_heads[5]; // +0x83d64
    Sprite* free_head; // +0x83d78
};

Sprite* SpriteManager::allocate_sprite(int owner, int texture_id, int texture_a, int texture_b)
{
    int zero = 0;
    int primary_texture_id = texture_id;
    Sprite* sprite = free_head;
    if (sprite == 0) {
        return &g_sprite_sentinel;
    }

    free_head = sprite->next;
    sprite->owner = owner;

    Sprite* head = active_heads[owner];
    if (head != 0) {
        head->prev = sprite;
    }
    sprite->prev = 0;
    sprite->next = active_heads[owner];
    active_heads[owner] = sprite;

    sprite->initialize_sprite();

    sprite->flags |= 1 << (owner + 0x18);
    sprite->texture_ref = g_sprite_texture_table[primary_texture_id];

    if (texture_b != -1) {
        sprite->flags |= 0x20;
        sprite->texture_ref_a = g_sprite_texture_table[texture_a];
        sprite->texture_ref_b = g_sprite_texture_table[texture_b];
    } else if (texture_a != -1) {
        sprite->flags |= 0x10;
        sprite->texture_ref_a = g_sprite_texture_table[texture_a];
    }

    sprite->scale_y = 0.0f;
    sprite->texture_id = primary_texture_id;
    sprite->frame_progress = zero;
    sprite->frame_progress_step = zero;
    sprite->frame_count = g_sprite_texture_table[primary_texture_id]->frame_count;

    if ((g_sprite_texture_table[primary_texture_id]->flags & 0x2000) != 0) {
        sprite->flags |= 0x2000;
        sprite->frame_progress_step = g_sprite_texture_table[primary_texture_id]->frame_progress_step;
        if ((g_sprite_texture_table[primary_texture_id]->flags & 0x4000) != 0) {
            sprite->flags |= 0x4000;
        }
    }

    return sprite;
}
