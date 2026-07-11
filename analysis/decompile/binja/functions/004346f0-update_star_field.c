/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_star_field @ 0x4346f0 */

004346ff        switch (manager->state)
0043470d        case 0
0043470d        if ((data_4df934 & 4) != 0)
00434715        manager->state = 2
0043471c        initialize_star_field(manager)
00434725        manager->state = 2
0043472c        manager->fade = 0f
00434733        manager->fade_step = 0.020833334f
0043473a        update_star_positions(manager, 0f)
004347c2        case 1
004347c2        update_star_positions(manager, 1f)
004347ce        if ((data_4df934 & 4) == 0)
004347d0        manager->fade = 1f
004347d7        manager->fade_step = 0.020833334f
004347de        manager->state = 3
00434747        case 2
00434747        update_star_positions(manager, manager->fade)
00434753        if ((data_4df934 & 4) == 0)
004347de        manager->state = 3
0043475c        long double x87_r7_2 = fconvert.t(manager->fade_step) + fconvert.t(manager->fade)
0043475f        manager->fade = fconvert.s(x87_r7_2)
00434762        long double temp0_1 = fconvert.t(1f)
00434762        x87_r7_2 - temp0_1
0043476d        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043476f        manager->state = 1
0043477e        case 3
0043477e        update_star_positions(manager, manager->fade)
0043478a        if ((data_4df934 & 4) != 0)
0043478c        manager->state = 2
00434794        return
00434798        long double x87_r7_4 = fconvert.t(manager->fade) - fconvert.t(manager->fade_step)
0043479b        manager->fade = fconvert.s(x87_r7_4)
0043479e        long double temp1_1 = fconvert.t(0f)
0043479e        x87_r7_4 - temp1_1
004347a9        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004347ad        destroy_star_field(manager)
004347b2        manager->state = 0
004347e6        return
