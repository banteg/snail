/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: normalize_segment_glyph_for_track_flags @ 0x437270 */

00437279        int32_t result
00437279        result.b = arg2
0043728d        if (arg3 s<= *(arg1 + 0x58) && sx.d(result.b) - 0x20 u<= 0x5d)
00437295        int32_t ebx_1
00437295        ebx_1.b = *(sx.d(result.b) + &jump_table_437418[5])
0043729b        int16_t edx_4
0043729b        switch (ebx_1)
004372a2        case 0
004372a2        int16_t ecx = (*(arg1 + 0x4c)).w
004372a8        if ((ecx:1.b & 4) == 0)
004372aa        result.b = 0x2c
004372ad        return result
004372b3        if ((ecx.b & 1) == 0)
004372b9        result.b = 0x2e
00437400        case 1
00437400        int32_t ecx_8 = *(arg1 + 0x4c)
00437406        if ((ecx_8:1.b & 8) == 0)
0043740a        result.b = ecx_8.b & 0x40
0043740c        char temp2_1 = result.b
0043740c        result.b = neg.b(result.b)
0043740e        result.b = sbb.b(result.b, result.b, temp2_1 != 0)
00437410        result.b &= 0x31
00437412        result.b += 0x2e
004373f8        case 2
004373f8        if (((*(arg1 + 0x4c)).w:1.b & 0x40) == 0)
004373fa        result.b = 0x2e
004372c5        case 3
004372c5        if (((*(arg1 + 0x4c)).w:1.b & 2) == 0)
004372cb        result.b = 0x2e
00437384        case 4
00437384        int32_t ecx_1 = *(arg1 + 0x4c)
0043738a        if ((ecx_1:1.b & 1) == 0)
00437393        if ((ecx_1.b & 1) == 0)
00437395        result.b = 0x2e
00437398        return result
0043739b        int32_t ecx_2 = ecx_1 & 0x400
004373a2        char ecx_3 = (neg.d(ecx_2)).b
004373ac        result.b = (sbb.b(ecx_3, ecx_3, ecx_2 != 0) & 0xf4) + 0x2c
0043733e        case 5
0043733e        int16_t edx_6 = (*(arg1 + 0x4c)).w
00437344        if ((edx_6:1.b & 2) == 0)
00437346        result.b = 0x2e
00437349        return result
0043734f        if ((edx_6.b & 0x20) == 0)
00437351        result.b = 0x3c
00437354        return result
00437357        edx_6.b = *(arg1 + 2)
0043735c        if (edx_6.b != 0)
00437362        result.b = 0x5b
00437314        case 6
00437314        edx_4 = (*(arg1 + 0x4c)).w
0043731a        if ((edx_4:1.b & 2) == 0)
0043731c        result.b = 0x2e
0043731f        return result
00437325        if ((edx_4.b & 0x20) != 0)
0043731a        goto label_43732d
00437327        result.b = 0x3c
0043736c        case 7
0043736c        if ((*(arg1 + 0x4c) & 0x40) == 0)
00437372        arg1.b = arg4
00437378        if (arg1.b == 0)
0043737e        result.b = 0x2e
004373da        case 8
004373da        char ecx_7 = (*(arg1 + 0x4c)).b
004373e0        if ((ecx_7 & 4) == 0)
004373e5        char eax = ecx_7 & 0x40
004373e7        char temp1 = eax
004373e7        eax = neg.b(eax)
004373ef        return (sbb.b(eax, eax, temp1 != 0) & 0x31) + 0x2e
004372ea        case 9
004372ea        int16_t edx_5 = (*(arg1 + 0x4c)).w
004372f0        if ((edx_5:1.b & 2) == 0)
004372f2        result.b = 0x2e
004372f5        return result
004372fb        if ((edx_5.b & 0x20) == 0)
004372fd        result.b = 0x3e
00437300        return result
00437303        edx_5.b = *(arg1 + 2)
00437308        if (edx_5.b != 0)
0043730e        result.b = 0x7d
004373b1        case 0xa
004373b1        int32_t ecx_4 = *(arg1 + 0x4c)
004373b7        if ((ecx_4:1.b & 1) == 0)
004373bc        if ((ecx_4.b & 1) == 0)
004373be        result.b = 0x20
004373c1        return result
004373c4        int32_t ecx_5 = ecx_4 & 0x400
004373cb        char ecx_6 = (neg.d(ecx_5)).b
004373d5        result.b = (sbb.b(ecx_6, ecx_6, ecx_5 != 0) & 0x11) + 0x2c
004372d1        case 0xb
004372d1        edx_4 = (*(arg1 + 0x4c)).w
004372d7        if ((edx_4:1.b & 2) == 0)
004372d9        result.b = 0x2e
004372dc        return result
004372e2        if ((edx_4.b & 0x20) == 0)
004372e4        result.b = 0x3e
004372e7        return result
0043732d        label_43732d:
0043732d        edx_4.b = *(arg1 + 2)
00437332        if (edx_4.b != 0)
00437338        result.b = 0x7b
00437415        return result
