/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: activate_all_borders @ 0x403300 */

00403300        int32_t* result = arg1 + 0x824
00403306        int32_t i_1 = 0x96
00403350        int32_t i
0040330b        int32_t ecx = *result
00403313        if ((ecx & 0x80000000) == 0)
00403315        ecx:1.b &= 0x7f
00403318        *result = ecx
0040331a        int32_t ecx_1 = *result
0040331c        result = &result[0x1c9]
00403327        i = i_1
00403327        i_1 -= 1
00403328        result[-0x1c9] = ecx_1 & 0x7fffffff
00403334        result[-0x1aa] = result[-0x1ac]
00403340        result[-0x1a9] = result[-0x1ac]
00403346        result[-0x1ae] = 0
00403350        do while (i != 1)
00403352        return result
