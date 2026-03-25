/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_slug_hazard @ 0x43f8b0 */

0043f8b0        int32_t var_4 = arg1
0043f8bb        if (*(arg1 + 0x80) != 1)
0043f8bb        return 
0043f8df        int16_t x87control
0043f8df        play_slug_voice(arg1, 0x1c - __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f)))
0043f8e4        long double x87_r7_3 = fconvert.t(*(arg1 + 0x68))
0043f8e7        long double temp0_1 = fconvert.t(0f)
0043f8e7        x87_r7_3 - temp0_1
0043f8f2        *(arg1 + 0x80) = 2
0043f8fd        if ((((x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043f90b        *(arg1 + 0x84) = 2
0043f8ff        *(arg1 + 0x84) = 1
0043f921        add_subgoldy_score(*(arg1 + 0x88) + 0x3bb764, 1, 0)
0043f928        explode_slug_hazard(arg1)
0043f92f        return
