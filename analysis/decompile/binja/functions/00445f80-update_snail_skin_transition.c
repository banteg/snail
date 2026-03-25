/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_snail_skin_transition @ 0x445f80 */

00445f83        void* eax = *(arg1[4] + 0x24)
00445f8c        *(eax + 0x10) |= 8
00445f9b        *(*(arg1[4] + 0x24) + 0x18) = arg1[*arg1 + 1]
00445f9e        int32_t eax_3 = arg1[5]
00445fa1        int16_t result = eax_3.w - 1
00445fa2        if (eax_3 == 1)
00445fa7        long double x87_r7_2 = fconvert.t(arg1[7]) + fconvert.t(arg1[6])
00445faa        arg1[6] = fconvert.s(x87_r7_2)
00445fad        long double temp1_1 = fconvert.t(1f)
00445fad        x87_r7_2 - temp1_1
00445fb3        result = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
00445fb8        if ((result:1.b & 0x41) == 0)
00445fba        result = 0
00445fbc        arg1[6] = 0
00445fbf        arg1[5] = 0
00445fc2        *arg1 = 0
00445fc4        return result
