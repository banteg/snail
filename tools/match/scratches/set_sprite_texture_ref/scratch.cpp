// set_sprite_texture_ref @ 0x44e550 (thiscall, ret 0x8)

extern char* g_sprite_texture_table[];

class Sprite {
public:
    char* set_sprite_texture_ref(int texture_id, int frame);

    char pad_00[0x1c];
    char* texture_ref; // +0x1c
};

char* Sprite::set_sprite_texture_ref(int texture_id, int frame)
{
    char* ref = g_sprite_texture_table[texture_id] + frame * 0xa4;
    texture_ref = ref;
    return ref;
}
