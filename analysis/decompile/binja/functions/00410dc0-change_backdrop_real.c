/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_backdrop_real @ 0x410dc0 */

00410dc5        int32_t eax = *(arg1 + 0x40)
00410dca        if (eax == 0)
00410e03        char edx = *(arg1 + 0x54)
00410e06        eax.b = *(arg1 + 0x39)
00410e09        *(arg1 + 0x658) = 0
00410e0f        *(arg1 + 0x55) = edx
00410e12        *(arg1 + 0x38) = eax.b
00410e16        return eax
00410dcf        if (eax != *(arg1 + 0x3c))
00410dd1        *(arg1 + 0x3c) = eax
00410dd7        *(arg1 + 0x44) = *(arg1 + 0x48)
00410dda        *(arg1 + 0x6c8) = 0
00410de6        set_backdrop_distort(arg1, *(arg1 + 0x50))
00410deb        char edx_1 = *(arg1 + 0x54)
00410dee        char eax_2 = *(arg1 + 0x39)
00410df1        *(arg1 + 0x658) = 1
00410dfb        *(arg1 + 0x55) = edx_1
00410dfe        *(arg1 + 0x38) = eax_2
00410e02        return eax_2
