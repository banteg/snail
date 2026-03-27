/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: parse_next_float32 @ 0x431f20 */

00431f29        if (**cursor != 0x2d)
00431f47        char* edx_1
00431f2b        edx_1 = *cursor
00431f2d        char* eax
00431f2d        eax.b = *edx_1
00431f31        if (eax.b == 0x2b)
00431f31        break
00431f35        if (eax.b == 0x2e)
00431f35        break
00431f3d        if (eax.b s>= 0x30 && eax.b s<= 0x39)
00431f3d        break
00431f42        *cursor = &edx_1[1]
00431f47        do while (edx_1[1] != 0x2d)
00431f49        char* eax_1 = *cursor
00431f4e        long double x87_r7
00431f4e        if (*eax_1 != 0x2d)
00431f5b        x87_r7 = fconvert.t(1f)
00431f50        x87_r7 = fconvert.t(-1f)
00431f57        *cursor = &eax_1[1]
00431f61        long double x87_r6 = fconvert.t(0f)
00431f67        long double x87_r5 = fconvert.t(0f)
00431f6d        while (true)
00431f6d        char* edx_2 = *cursor
00431f6f        eax_1.b = *edx_2
00431f7b        if ((eax_1.b s< 0x30 || eax_1.b s> 0x39) && eax_1.b != 0x2e)
00431fb1        long double temp1 = fconvert.t(0f)
00431fb1        x87_r5 - temp1
00431fb7        eax_1.w = (x87_r5 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r5, temp1) ? 1 : 0) << 0xa | (x87_r5 == temp1 ? 1 : 0) << 0xe | 0x2800
00431fbc        if ((eax_1:1.b & 0x40) != 0)
00431fc0        x87_r5 = fconvert.t(1f)
00431fcc        return (x87_r7 * x87_r5 * x87_r6).q
00431f7f        if (eax_1.b != 0x2e)
00431f99        *cursor = &edx_2[1]
00431fa7        x87_r6 = float.t(sx.d(eax_1.b) - 0x30) + x87_r6 * fconvert.t(10f)
00431fa9        x87_r5 = x87_r5 * fconvert.t(0.100000001f)
00431f83        x87_r5 = fconvert.t(1f)
00431f8a        *cursor = &edx_2[1]
