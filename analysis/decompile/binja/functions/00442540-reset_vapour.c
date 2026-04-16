/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_vapour @ 0x442540 */

00442544        *(arg1 + 0x80) = 0
0044254e        *(arg1 + 0x8c) = arg2
00442557        int32_t result
00442557        result.b = (*(arg1 + 4)).b & 0xdf
00442559        *(arg1 + 4) = result
0044255c        return result
