/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_timer_counters @ 0x441b90 */

00441b94        long double x87_r7 = fconvert.t(arg2) * fconvert.t(0.0166666675f)
00441ba1        *arg1 = fconvert.s(x87_r7 + fconvert.t(*arg1))
00441ba3        long double x87_r7_1 = x87_r7 + fconvert.t(arg1[5])
00441ba6        long double temp1 = fconvert.t(1f)
00441ba6        x87_r7_1 - temp1
00441bac        arg1[5] = fconvert.s(x87_r7_1)
00441bac        bool c1 = unimplemented  {fst dword [esi+0x14], st0}
00441bb4        if ((((x87_r7_1 < temp1 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_1, temp1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00441bbf        int32_t edx_2 = arg1[2] i+ 1
00441bc2        arg1[2] = edx_2
00441bc8        arg1[5] = fconvert.s(x87_r7_1 - fconvert.t(1f))
00441bcb        if (edx_2 s>= 0x3c)
00441bd0        arg1[2] = edx_2 - 0x3c
00441bd7        arg1[1] += 1
00441be7        int32_t eax_5
00441be7        int16_t x87control
00441be7        int16_t x87control_1
00441be7        eax_5, x87control_1 = __ftol(x87control, fconvert.t(arg1[5]) * fconvert.t(100f))
00441bef        long double x87_r7_7 = fconvert.t(arg1[5]) * fconvert.t(1000f)
00441bf5        arg1[3] = eax_5
00441bf8        int32_t result = __ftol(x87control_1, x87_r7_7)
00441bfd        arg1[4] = result
00441c01        return result
