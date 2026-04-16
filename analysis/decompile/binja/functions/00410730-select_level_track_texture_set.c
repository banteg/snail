/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: select_level_track_texture_set @ 0x410730 */

0041073d        int32_t edi
0041073d        switch (arg2)
00410744        case 0
00410744        edi = 0
00410748        case 1
00410748        edi = 1
0041074f        case 2
0041074f        edi = 2
00410756        case 3
00410756        edi = 3
0041075d        case 5
0041075d        int32_t var_c_1 = 0
00410771        int16_t x87control
00410771        edi = __ftol(x87control, random_float_below(4f))
00410775        edi = arg2
00410779        int32_t result = *(arg1 + 0x20)
0041077e        if (edi != result)
0041078d        sub_430d90(0x4b7648, *(arg1 + (edi << 2)), *(arg1 + (result << 2)))
004107a4        result = sub_430d90(0x4b7648, *(arg1 + (edi << 2) + 0x10), *(arg1 + (*(arg1 + 0x20) << 2) + 0x10))
004107a9        *(arg1 + 0x20) = edi
004107ae        return result
