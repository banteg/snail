// get_sprite_texture_ref @ 0x44e580 (stdcall, ret 0x4)

#include "sprite.h"

void* __stdcall get_sprite_texture_ref(int texture_id)
{
    return g_sprite_texture_table[texture_id]->texture_ref;
}
