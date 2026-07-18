/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_sprite_texture @ 0x44e0f0 */

0044e0f9        char* texture_path_1 = texture_path
0044e0fe        if (*texture_path != 0x2e)
0044e107        char i
0044e100        i = texture_path_1[1]
0044e103        texture_path_1 = &texture_path_1[1]
0044e107        do while (i != 0x2e)
0044e113        if (texture_id s>= 0x3e8)
0044e11f        report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h", 0x3e8)
0044e134        struct TextureRef* eax = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, flags)
0044e139        g_sprite_texture_table[texture_id] = eax
0044e145        eax->flags |= flags
0044e147        void* result = g_sprite_texture_table[texture_id]
0044e150        *(result + 0x90) = 0
0044e15a        return result
