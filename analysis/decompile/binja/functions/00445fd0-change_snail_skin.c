/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: change_snail_skin @ 0x445fd0 */

00445fd0        long double x87_r7 = fconvert.t(arg3)
00445fd4        long double temp1 = fconvert.t(0f)
00445fd4        x87_r7 - temp1
00445fdc        arg1[5] = 1
00445fe3        arg1[6] = 0
00445fe6        int16_t eax = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
00445feb        if ((eax:1.b & 0x40) == 0)
00446007        *arg1 = arg2
0044600f        arg1[7] = fconvert.s(fconvert.t(1f) / (fconvert.t(arg3) * fconvert.t(60f)))
00446012        return eax
00445ff1        arg1[7] = 0
00445ff4        *arg1 = arg2
00445ff6        return arg2
