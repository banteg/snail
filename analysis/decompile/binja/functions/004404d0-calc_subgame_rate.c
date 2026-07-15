/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_subgame_rate @ 0x4404d0 */

004404d0        struct SubgameRuntime* runtime_1 = runtime
004404dc        if (runtime->subgame_state != 2)
004405f3        runtime->subgame_rate = runtime->rate_or_level_arg.base_rate
004405f3        return
004404e5        long double x87_r7_2 = fconvert.t(runtime->player.body.transform.position.z) / float.t(runtime->completion_row_start)
004404eb        long double temp0_1 = fconvert.t(0f)
004404eb        x87_r7_2 - temp0_1
004404f6        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) == 0)
00440502        long double temp1_1 = fconvert.t(1f)
00440502        x87_r7_2 - temp1_1
0044050d        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00440511        x87_r7_2 = fconvert.t(1f)
004404fa        x87_r7_2 = fconvert.t(0f)
00440517        int32_t level_mode = runtime->level_mode
00440522        long double x87_r7_7
00440522        if (level_mode == 1 || level_mode == 3)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.550000012f) + fconvert.t(runtime->rate_or_level_arg.base_rate)
00440527        if (level_mode != 4)
00440548        x87_r7_7 = x87_r7_2 * fconvert.t(0.200000003f) + fconvert.t(runtime->rate_or_level_arg.base_rate)
00440532        x87_r7_7 = x87_r7_2 * fconvert.t(0.400000006f) + fconvert.t(runtime->rate_or_level_arg.base_rate) + fconvert.t(0.200000003f)
0044054b        enum DamageGuageState state = runtime->player.damage_gauge.state
00440551        runtime->subgame_rate = fconvert.s(x87_r7_7)
00440556        if (state == DAMAGE_GUAGE_STATE_DRAINING)
0044055b        if (level_mode != 1)
00440560        runtime_1 = 0x3f19999a
00440568        if (level_mode == 1 || level_mode == 4)
0044056a        runtime_1 = 0x3ecccccd
00440572        long double x87_r7_9 = fconvert.t(runtime->player.damage_gauge.display_fill)
00440578        long double temp2_1 = fconvert.t(0.25)
00440578        x87_r7_9 - temp2_1
00440583        long double x87_r7_10
00440583        long double temp3_1
00440583        if ((((x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00440585        x87_r7_10 = fconvert.t(runtime->player.damage_gauge.display_fill)
0044058b        temp3_1 = fconvert.t(0.75)
0044058b        x87_r7_10 - temp3_1
00440596        long double x87_r7_11
00440596        if ((((x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0 || (((x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004405aa        int32_t var_c_1 = 2
004405c8        x87_r7_11 = (fconvert.t(1f) - sine(fconvert.s(fconvert.t(runtime->player.damage_gauge.display_fill) * fconvert.t(12.566371f) + fconvert.t(1.57079637f)))) * fconvert.t(0.5f) * fconvert.t(runtime_1)
00440598        x87_r7_11 = fconvert.t(runtime_1)
004405cf        runtime->subgame_rate = fconvert.s(x87_r7_11 + fconvert.t(runtime->subgame_rate))
004405d9        if (runtime->player.sub_hover.state == SUB_HOVER_STATE_ACTIVE)
004405ea        runtime->subgame_rate = fconvert.s(fconvert.t(runtime->player.sub_hover.warning_intensity_latch) * fconvert.t(0.5f) + fconvert.t(runtime->subgame_rate))
004405f8        return
