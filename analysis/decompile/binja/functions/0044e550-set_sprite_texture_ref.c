/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_sprite_texture_ref @ 0x44e550 */

0044e565        int32_t result = *((arg2 << 2) + &data_78ff90) + arg3 * 0xa4
0044e568        *(arg1 + 0x1c) = result
0044e56b        return result
