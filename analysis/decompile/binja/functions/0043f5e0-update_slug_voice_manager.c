/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_slug_voice_manager @ 0x43f5e0 */

0043f5e0        long double x87_r7 = fconvert.t(*(arg1 + 4))
0043f5e3        long double temp0 = fconvert.t(0f)
0043f5e3        x87_r7 - temp0
0043f5e9        int16_t result = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
0043f5ee        if ((result:1.b & 0x41) == 0)
0043f5f3        long double x87_r7_2 = fconvert.t(*(arg1 + 8)) + fconvert.t(*(arg1 + 4))
0043f5f6        *(arg1 + 4) = fconvert.s(x87_r7_2)
0043f5f9        long double temp1_1 = fconvert.t(1f)
0043f5f9        x87_r7_2 - temp1_1
0043f5ff        result = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0043f604        if ((result:1.b & 0x41) == 0)
0043f606        *(arg1 + 4) = 0
0043f60d        *arg1 = 0
0043f610        return result
