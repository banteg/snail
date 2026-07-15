/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_pause_menu @ 0x4407a0 */

004407a0        struct FrontendWidget* options_widget = pause->options_widget
004407a2        enum FrontendWidgetFlag widget_flags = options_widget->widget_flags
004407aa        if ((widget_flags.b & 0x20) != 0)
004407ac        widget_flags.b &= 0xdf
004407ae        options_widget->widget_flags = widget_flags
004407b9        g_game_base->__offset(0x4f38c).b = 0
004407c0        struct GameRoot* game_base_1 = g_game_base
004407cb        game_base_1->__offset(0x4f388).d = game_base_1->players[0].frontend_state
004407d7        g_game_base->players[0].frontend_state = 6
004407e1        return
004407e2        struct FrontendWidget* resume_widget = pause->resume_widget
004407e5        enum FrontendWidgetFlag widget_flags_1 = resume_widget->widget_flags
004407ed        if ((widget_flags_1.b & 0x20) != 0)
004407ef        widget_flags_1.b &= 0xdf
004407f1        resume_widget->widget_flags = widget_flags_1
004407f7        uninit_pause_menu(pause)
00440801        g_game_base->subgame.subgame_state = 2
00440811        g_game_base->subgame.resume_requested = 1
00440818        return
00440819        struct FrontendWidget* end_game_widget = pause->end_game_widget
0044081c        enum FrontendWidgetFlag widget_flags_2 = end_game_widget->widget_flags
00440824        if ((widget_flags_2.b & 0x20) == 0)
00440824        return
00440826        widget_flags_2.b &= 0xdf
00440829        end_game_widget->widget_flags = widget_flags_2
0044082f        struct GameRoot* game_base_2 = g_game_base
0044083f        game_base_2->__offset(0x4f3b4).d = game_base_2->players[0].frontend_state
00440845        struct GameRoot* game_base_3 = g_game_base
00440858        if (game_base_3->subgame.level_mode == 7)
0044085a        game_base_3->__offset(0x4f3ac).d = 7
00440869        if (game_base_3->subgame.selected_level_record_persistent != 1)
00440877        game_base_3->__offset(0x4f3ac).d = 2
0044086b        game_base_3->__offset(0x4f3ac).d = 3
00440882        g_game_base->subgame.subgame_rebuild_selector = 2
0044088e        g_game_base->players[0].frontend_state = 8
00440898        return
