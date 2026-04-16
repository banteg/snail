/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_track_warning_zones @ 0x4354f0 */

004354f7        int32_t i = 0
004354f9        char* result = *(arg1 + 0x54) - 1
004354fc        int32_t i_1 = 0
00435500        if (result s> 0)
00435509        result = arg1 + 0x3bfb04
0043550f        char* result_1 = result
00435511        int32_t j = 0
00435513        char* result_2 = result_1
00435517        result.b = *result_1
00435557        if (result.b == 2 || result.b == 3 || result.b == 4 || result.b == 5 || result.b == 6 || result.b == 7 || result.b == 8 || result.b == 9 || result.b == 0xa || result.b == 0xb || result.b == 0xc || result.b == 0xd || result.b == 0xe || result.b == 0x17 || result.b == 0x19 || result.b == 0x21)
00435559        int32_t edi_1 = j + (i << 3)
0043555d        char* var_c_1 = 6
004355b5        bool cond:1_1
00435565        int32_t k = 0xffffffff
004355a6        while (k s< 1)
00435572        if (i s>= 0 && i s< *(arg1 + 0x54) - 1)
00435574        int32_t eax_1 = k + j
0043557e        if (eax_1 s>= 0 && eax_1 s< 8)
0043558c        int32_t eax_4 = (edi_1 + k) * 0x15
004355a0        *(arg1 + (eax_4 << 2) + 0x3bfb08) |= 0x18
004355a2        k += 1
004355ac        i -= 1
004355ad        edi_1 -= 8
004355b0        cond:1_1 = var_c_1 != 1
004355b1        var_c_1 -= 1
004355b5        do while (cond:1_1)
004355b7        result_1 = result_2
004355bb        i = i_1
004355bf        j += 1
004355c0        result_1 = &result_1[0x54]
004355c6        result_2 = result_1
004355ca        do while (j s< 8)
004355d0        result = result_1
004355d5        i += 1
004355d9        i_1 = i
004355dd        do while (i s< *(arg1 + 0x54) - 1)
004355ea        return result
