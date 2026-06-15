// get_sprite_texture_ref @ 0x44e580 (stdcall, ret 0x4)

extern char* g_sprite_texture_table[];

void* __stdcall get_sprite_texture_ref(int texture_id)
{
    return *(void**)(g_sprite_texture_table[texture_id] + 0x98);
}
