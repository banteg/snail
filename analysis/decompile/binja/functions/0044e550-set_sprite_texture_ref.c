/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_sprite_texture_ref @ 0x44e550 */

0044e565        struct TextureRef* result = &g_sprite_texture_table[texture_id][frame]
0044e568        sprite->texture_ref = result
0044e56b        return result
