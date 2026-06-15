// get_sprite_texture @ 0x44e570 (stdcall, ret 0x4)

extern void* g_sprite_texture_table[];

void* __stdcall get_sprite_texture(int texture_id)
{
    return g_sprite_texture_table[texture_id];
}
