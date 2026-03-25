/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_voice_ai @ 0x43f520 */

0043f520        int16_t result
0043f520        result.b = *(arg1 + 0xd8)
0043f52a        if (result.b != 0)
0043f532        long double x87_r7_2 = fconvert.t(*(arg1 + 0xe0)) + fconvert.t(*(arg1 + 0xdc))
0043f538        *(arg1 + 0xdc) = fconvert.s(x87_r7_2)
0043f53e        long double temp0_1 = fconvert.t(1f)
0043f53e        x87_r7_2 - temp0_1
0043f544        result = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
0043f549        if ((result:1.b & 0x41) == 0)
0043f54b        *(arg1 + 0xdc) = 0
0043f551        *(arg1 + 0xd8) = 0
0043f557        return result
