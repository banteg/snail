/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_bod_after_sprites @ 0x42f5c0 */

0042f5c4        int32_t result
0042f5c4        result.b = (*(arg1 + 4) & 0x80) != 0
0042f5c7        return result
