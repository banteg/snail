/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhide_border_init @ 0x401110 */

00401110        int32_t result = *(arg1 + 0x1a0)
00401116        *(arg1 + 0x44) = 0x3f800000
0040111d        result:1.b &= 0xef
00401120        *(arg1 + 0x1a0) = result
00401126        return result
