/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_sprite_extend @ 0x404540 */

00404548        *(arg1 + 0x60) = arg2
0040454f        *(arg1 + 0x64) = arg4
00404552        int32_t edx
00404552        edx.b = arg5
00404556        *(arg1 + 0x68) = arg3
0040455b        *(arg1 + 0x5c) = 1
0040455f        *(arg1 + 0x5d) = edx.b
00404562        *(arg1 + 0x21c) = 0
00404568        *(arg1 + 0x214) = 0
0040456e        *(arg1 + 0x218) = 0
00404574        return 0
