/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: toggle_archive_high_bit_in_place @ 0x405350 */

00405350        int32_t i_1 = arg2
00405354        char* result = arg1
0040535a        if (i_1 s> 0)
00405365        int32_t i
00405361        *result ^= 0x80
00405363        result = &result[1]
00405364        i = i_1
00405364        i_1 -= 1
00405365        do while (i != 1)
00405367        return result
