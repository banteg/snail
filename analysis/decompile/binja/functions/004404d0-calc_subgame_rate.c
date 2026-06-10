/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_subgame_rate @ 0x4404d0 */

004404d0        struct Game* game_1 = game
004404dc        if (game->subgame_state != 2)
004405f0        float eax_1
004405f0        eax_1.b = game->_pad_00[0x30]
004405f0        eax_1:1.b = game->_pad_00[0x31]
004405f0        eax_1:2.b = game->_pad_00[0x32]
004405f0        eax_1:3.b = game->_pad_00[0x33]
004405f3        game->subgame_rate = eax_1
004405f3        return 
004404e5        long double x87_r7_2 = fconvert.t(game->__offset(0x3bb7d4).d) / float.t(game->completion_row_start)
004404eb        long double temp0_1 = fconvert.t(0f)
004404eb        x87_r7_2 - temp0_1
004404f6        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00440502        long double temp1_1 = fconvert.t(1f)
00440502        x87_r7_2 - temp1_1
0044050d        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00440511        x87_r7_2 = fconvert.t(1f)
004404fa        x87_r7_2 = fconvert.t(0f)
00440517        int32_t level_mode = game->level_mode
00440522        long double x87_r7_7
00440522        if (level_mode == 1 || level_mode == 3)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.550000012f) + fconvert.t(game->_pad_00[0x30].d)
00440527        if (level_mode != 4)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.200000003f) + fconvert.t(game->_pad_00[0x30].d)
00440532        x87_r7_7 = x87_r7_2 * fconvert.t(0.400000006f) + fconvert.t(game->_pad_00[0x30].d) + fconvert.t(0.200000003f)
0044054b        int32_t edx_1 = game->__offset(0x3bbb28).d
00440551        game->subgame_rate = fconvert.s(x87_r7_7)
00440556        if (edx_1 == 2)
0044055b        if (level_mode != 1)
00440560        game_1 = 0x3f19999a
00440568        if (level_mode == 1 || level_mode == 4)
0044056a        game_1 = 0x3ecccccd
00440572        long double x87_r7_9 = fconvert.t(game->__offset(0x3bbb48).d)
00440578        long double temp2_1 = fconvert.t(0.25)
00440578        x87_r7_9 - temp2_1
0044057e        level_mode.w = (x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe
00440583        long double x87_r7_11
00440583        int32_t var_c_1
00440583        if ((level_mode:1.b & 1) != 0)
004405aa        var_c_1 = 2
004405c8        x87_r7_11 = (fconvert.t(1f) - sine(fconvert.s(fconvert.t(game->__offset(0x3bbb48).d) * fconvert.t(12.566371f) + fconvert.t(1.57079637f)))) * fconvert.t(0.5f) * fconvert.t(game_1)
00440585        long double x87_r7_10 = fconvert.t(game->__offset(0x3bbb48).d)
0044058b        long double temp3_1 = fconvert.t(0.75)
0044058b        x87_r7_10 - temp3_1
00440591        level_mode.w = (x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe
00440596        if ((level_mode:1.b & 0x41) == 0)
004405aa        var_c_1 = 2
004405c8        x87_r7_11 = (fconvert.t(1f) - sine(fconvert.s(fconvert.t(game->__offset(0x3bbb48).d) * fconvert.t(12.566371f) + fconvert.t(1.57079637f)))) * fconvert.t(0.5f) * fconvert.t(game_1)
00440598        x87_r7_11 = fconvert.t(game_1)
004405cf        game->subgame_rate = fconvert.s(x87_r7_11 + fconvert.t(game->subgame_rate))
004405d9        if (game->__offset(0x3bdec0).d == 1)
004405ea        game->subgame_rate = fconvert.s(fconvert.t(game->__offset(0x3be0c0).d) * fconvert.t(0.5f) + fconvert.t(game->subgame_rate))
004405f8        return
