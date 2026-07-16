/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_thanks_for_playing_screen @ 0x4340f0 */

004340fe        enum InputButtonFlag result = g_game_base->players[0].game_input->input.pressed_buttons
00434104        if ((result:1.b & 0x40) != 0)
0043410f        label_43410f:
00434113        if (*(arg1 + 8) s>= 2)
0043411b        result = g_game_base->fade.state
00434120        if (result == 0)
00434129        play_sound_effect(8)
00434138        result = begin_frontend_fade_out(&g_game_base->fade, 0)
00434106        result = read_pressed_text_input_key_code()
0043410d        if (result.b == 0xb)
0043410d        goto label_43410f
00434147        if (g_game_base->fade.state == 4)
0043414b        result = uninit_thanks_screen(arg1)
00434153        long double x87_r7_1 = fconvert.t(*(arg1 + 0xc)) + fconvert.t(*(arg1 + 0x10))
00434156        *(arg1 + 0xc) = fconvert.s(x87_r7_1)
00434159        long double temp0 = fconvert.t(1f)
00434159        x87_r7_1 - temp0
0043415f        result.w = (x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe
00434164        if ((result:1.b & 0x41) == 0)
0043416a        result = *(arg1 + 8)
0043416d        *(arg1 + 0xc) = 0
0043417d        switch (result)
00434184        case 0
00434184        struct FrontendWidget* widget = *(arg1 + 4)
00434187        *(arg1 + 8) = 1
0043418e        *(arg1 + 0x10) = 0x3d088889
0043419b        return hide_border_init(widget)
0043419f        case 0x1
004341a4        char* edx_3 = *(arg1 + 4) + 0x2cc
004341aa        *(arg1 + 8) = 2
004341b1        *(arg1 + 0x10) = 0x3b888889
00434226        rstrcpy_checked_ascii(edx_3, "Test your reflexes in Challenge Mode!")
00434237        return unhide_border_init(*(arg1 + 4))
004341bb        case 0x2
004341bb        struct FrontendWidget* widget_1 = *(arg1 + 4)
004341be        *(arg1 + 8) = 3
004341c5        *(arg1 + 0x10) = 0x3d088889
004341d2        return hide_border_init(widget_1)
004341d6        case 0x3
004341db        char* eax_4 = *(arg1 + 4) + 0x2cc
004341e0        *(arg1 + 8) = 4
004341e7        *(arg1 + 0x10) = 0x3b888889
00434226        rstrcpy_checked_ascii(eax_4, "Improve your skills in Time Trial!")
00434237        return unhide_border_init(*(arg1 + 4))
004341f1        case 0x4
004341f1        struct FrontendWidget* widget_2 = *(arg1 + 4)
004341f4        *(arg1 + 8) = 5
004341fb        *(arg1 + 0x10) = 0x3d088889
00434208        return hide_border_init(widget_2)
0043420c        case 0x5
00434211        char* ecx_6 = *(arg1 + 4) + 0x2cc
00434217        *(arg1 + 8) = 6
0043421e        *(arg1 + 0x10) = 0x3b888889
00434226        rstrcpy_checked_ascii(ecx_6, "Click to Continue")
00434237        return unhide_border_init(*(arg1 + 4))
00434238        case 0x6
00434238        *(arg1 + 8) = 7
0043423f        *(arg1 + 0x10) = 0
0043423f        case 0x7
0043423f        *(arg1 + 0x10) = 0
00434247        return result
