/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_star_field @ 0x4346f0 */

004346f3        void* eax = arg1[0xe]
004346ff        switch (eax)
0043470d        case nullptr
0043470d        if ((data_4df934 & 4) != 0)
00434715        arg1[0xe] = 2
0043471c        initialize_star_field(arg1)
00434725        arg1[0xe] = 2
0043472c        arg1[0x11] = 0
00434733        arg1[0x12] = 0x3caaaaab
00434740        return update_star_positions(arg1, 0f)
004347c2        case 1
004347c2        eax = update_star_positions(arg1, 1f)
004347ce        if ((data_4df934 & 4) == 0)
004347d0        arg1[0x11] = 0x3f800000
004347d7        arg1[0x12] = 0x3caaaaab
004347de        arg1[0xe] = 3
00434747        case 2
00434747        eax = update_star_positions(arg1, arg1[0x11])
00434753        if ((data_4df934 & 4) == 0)
004347de        arg1[0xe] = 3
0043475c        long double x87_r7_2 = fconvert.t(arg1[0x12]) + fconvert.t(arg1[0x11])
0043475f        arg1[0x11] = fconvert.s(x87_r7_2)
00434762        long double temp0_1 = fconvert.t(1f)
00434762        x87_r7_2 - temp0_1
00434768        eax.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
0043476d        if ((eax:1.b & 0x41) == 0)
0043476f        arg1[0xe] = 1
0043477e        case 3
0043477e        eax = update_star_positions(arg1, arg1[0x11])
0043478a        if ((data_4df934 & 4) != 0)
0043478c        arg1[0xe] = 2
00434794        return eax
00434798        long double x87_r7_4 = fconvert.t(arg1[0x11]) - fconvert.t(arg1[0x12])
0043479b        arg1[0x11] = fconvert.s(x87_r7_4)
0043479e        long double temp1_1 = fconvert.t(0f)
0043479e        x87_r7_4 - temp1_1
004347a4        eax.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe
004347a9        if ((eax:1.b & 1) != 0)
004347ad        int32_t eax_3 = destroy_star_field(arg1)
004347b2        arg1[0xe] = 0
004347ba        return eax_3
004347e6        return eax
