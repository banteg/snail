/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_slider_to_rate @ 0x437e80 */

00437e80        long double x87_r7 = fconvert.t(arg1)
00437e84        long double temp1 = fconvert.t(1f)
00437e84        x87_r7 - temp1
00437e8f        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00437eaa        return fconvert.t(arg1) * fconvert.t(0.900000036f) + fconvert.t(0.200000003f)
00437e97        return fconvert.t(1.10000002f)
