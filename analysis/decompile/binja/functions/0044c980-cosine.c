/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: cosine @ 0x44c980 */

0044c990        int16_t x87control
0044c990        int32_t eax = __ftol(x87control, fconvert.t(arg1) * fconvert.t(0.159154937f) * fconvert.t(8192f))
0044c999        long double st0
0044c999        bool c1
0044c999        bool c2
0044c999        st0, c1, c2 = __fcos(fconvert.t(arg1))
0044c99d        int32_t ecx_1 = eax & 0x1fff
0044c9a3        long double x87_r7_4 = fconvert.t(*((ecx_1 << 2) + &data_777f3c)) - st0
0044c9aa        long double temp0 = fconvert.t(0f)
0044c9aa        x87_r7_4 - temp0
0044c9b0        eax.w = (x87_r7_4 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp0) ? 1 : 0) << 0xa | (x87_r7_4 == temp0 ? 1 : 0) << 0xe | 0x3800
0044c9b5        if ((eax:1.b & 1) != 0)
0044c9b7        x87_r7_4 = fneg(x87_r7_4)
0044c9b9        long double temp1 = fconvert.t(0.0199999996f)
0044c9b9        x87_r7_4 - temp1
0044c9bf        eax.w = (x87_r7_4 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1 ? 1 : 0) << 0xe
0044c9c4        if ((eax:1.b & 0x41) != 0)
0044c9cf        return fconvert.t(*((ecx_1 << 2) + &data_777f3c))
0044c9c6        while (true)
