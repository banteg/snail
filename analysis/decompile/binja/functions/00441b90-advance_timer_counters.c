/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_timer_counters @ 0x441b90 */

00441b94        long double x87_r7 = fconvert.t(delta_ticks) * fconvert.t(0.0166666675f)
00441ba1        stopwatch->total_seconds = fconvert.s(x87_r7 + fconvert.t(stopwatch->total_seconds))
00441ba3        long double x87_r7_1 = x87_r7 + fconvert.t(stopwatch->second_fraction)
00441ba6        long double temp1 = fconvert.t(1f)
00441ba6        x87_r7_1 - temp1
00441bac        stopwatch->second_fraction = fconvert.s(x87_r7_1)
00441bac        bool c1 = unimplemented  {fst dword [esi+0x14], st0}
00441bb4        if ((((x87_r7_1 < temp1 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_1, temp1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00441bbf        int32_t edx_2 = stopwatch->frames_into_second + 1
00441bc2        stopwatch->frames_into_second = edx_2
00441bc8        stopwatch->second_fraction = fconvert.s(x87_r7_1 - fconvert.t(1f))
00441bcb        if (edx_2 s>= 0x3c)
00441bd0        stopwatch->frames_into_second = edx_2 - 0x3c
00441bd7        stopwatch->minutes += 1
00441be7        int32_t eax_5
00441be7        int16_t x87control
00441be7        int16_t x87control_1
00441be7        eax_5, x87control_1 = __ftol(x87control, fconvert.t(stopwatch->second_fraction) * fconvert.t(100f))
00441bef        long double x87_r7_7 = fconvert.t(stopwatch->second_fraction) * fconvert.t(1000f)
00441bf5        stopwatch->display_hundredths = eax_5
00441bfd        stopwatch->display_thousandths = __ftol(x87control_1, x87_r7_7)
00441c01        return
