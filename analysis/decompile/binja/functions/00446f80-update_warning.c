/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_warning @ 0x446f80 */

00446f91        if (g_game_base->subgame.subgame_pause_gate != 0)
00446f91        return
00446f97        enum WarningState state = warning->state
00446f9b        if (state == WARNING_STATE_INACTIVE)
00446f9b        return
00446fa2        if (state == 1)
00447009        warning->border->hot_text_color.a = 0.999000013f
00447016        long double x87_r7_8 = fconvert.t(warning->phase_step) + fconvert.t(warning->phase)
00447019        warning->phase = fconvert.s(x87_r7_8)
0044701c        long double temp2_1 = fconvert.t(1f)
0044701c        x87_r7_8 - temp2_1
00447027        if ((((x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00447029        warning->phase = 0f
0044702c        warning->state = 2
00446fa5        if (state == 2)
00446fab        long double x87_r7_1 = fconvert.t(warning->phase)
00446fae        long double temp4_1 = fconvert.t(0.5f)
00446fae        x87_r7_1 - temp4_1
00446fb9        if ((((x87_r7_1 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp4_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00446fd4        warning->border->hot_text_color.a = 0f
00446fbb        long double x87_r7_2 = fconvert.t(warning->phase)
00446fc9        warning->border->hot_text_color.a = fconvert.s(fconvert.t(1f) - (x87_r7_2 + x87_r7_2))
00446fdd        long double x87_r7_6 = fconvert.t(warning->phase_step) + fconvert.t(warning->phase)
00446fe0        warning->phase = fconvert.s(x87_r7_6)
00446fe3        long double temp5_1 = fconvert.t(1f)
00446fe3        x87_r7_6 - temp5_1
00446fee        if ((((x87_r7_6 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp5_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00446ff0        warning->phase = 0f
00446ff3        warning->state = 1
00447000        play_sound_effect(&g_sound_effect_manager, 0x32)
00447032        return
