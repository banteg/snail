/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_thanks_for_playing_screen @ 0x4340f0 */

00434104        enum InputButtonFlag eax
00434104        if ((g_game_base->players[0].game_input->input.pressed_buttons:1.b & 0x40) == 0)
00434106        eax = read_pressed_text_input_key_code()
00434120        if (((g_game_base->players[0].game_input->input.pressed_buttons:1.b & 0x40) != 0 || eax.b == 0xb) && thanks_screen->message_state s>= 2 && g_game_base->fade.state == 0)
00434129        play_sound_effect(&g_sound_effect_manager, 8)
00434138        begin_frontend_fade_out(&g_game_base->fade.state, 0)
00434147        if (g_game_base->fade.state == 4)
0043414b        uninit_thanks_screen(thanks_screen)
00434153        long double x87_r7_1 = fconvert.t(thanks_screen->message_progress) + fconvert.t(thanks_screen->message_progress_step)
00434156        thanks_screen->message_progress = fconvert.s(x87_r7_1)
00434159        long double temp0 = fconvert.t(1f)
00434159        x87_r7_1 - temp0
00434164        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00434164        return
0043416a        int32_t message_state = thanks_screen->message_state
0043416d        thanks_screen->message_progress = 0f
0043417d        struct FrontendWidgetTextBuffer* var_c
0043417d        char* var_8
0043417d        switch (message_state)
00434184        case 0
00434184        struct FrontendWidget* message_widget = thanks_screen->message_widget
00434187        thanks_screen->message_state = 1
0043418e        thanks_screen->message_progress_step = 0.0333333351f
00434195        hide_border_init(message_widget)
0043419f        case 1
0043419f        var_8 = "Test your reflexes in Challenge Mode!"
004341aa        thanks_screen->message_state = 2
004341b1        thanks_screen->message_progress_step = 0.00416666688f
004341b8        var_c = &thanks_screen->message_widget->text_buffer
00434226        label_434226:
00434226        rstrcpy_checked_ascii(var_c, var_8)
00434231        unhide_border_init(thanks_screen->message_widget)
004341bb        case 2
004341bb        struct FrontendWidget* message_widget_1 = thanks_screen->message_widget
004341be        thanks_screen->message_state = 3
004341c5        thanks_screen->message_progress_step = 0.0333333351f
004341cc        hide_border_init(message_widget_1)
004341d6        case 3
004341d6        var_8 = "Improve your skills in Time Trial!"
004341e0        thanks_screen->message_state = 4
004341e7        thanks_screen->message_progress_step = 0.00416666688f
004341ee        var_c = &thanks_screen->message_widget->text_buffer
004341ef        goto label_434226
004341f1        case 4
004341f1        struct FrontendWidget* message_widget_2 = thanks_screen->message_widget
004341f4        thanks_screen->message_state = 5
004341fb        thanks_screen->message_progress_step = 0.0333333351f
00434202        hide_border_init(message_widget_2)
0043420c        case 5
0043420c        var_8 = "Click to Continue"
00434217        thanks_screen->message_state = 6
0043421e        thanks_screen->message_progress_step = 0.00416666688f
00434225        var_c = &thanks_screen->message_widget->text_buffer
00434225        goto label_434226
00434238        case 6
00434238        thanks_screen->message_state = 7
0043423f        thanks_screen->message_progress_step = 0f
0043423f        case 7
0043423f        thanks_screen->message_progress_step = 0f
00434247        return
