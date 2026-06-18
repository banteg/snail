/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_sprite_texture_ref @ 0x44e550 */

0044e565        int32_t result = *((arg2 << 2) + &g_sprite_texture_table) + arg3 * 0xa4
0044e568        *(arg1 + 0x1c) = result
0044e56b        return result
