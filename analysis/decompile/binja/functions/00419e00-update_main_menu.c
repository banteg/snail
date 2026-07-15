/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_main_menu @ 0x419e00 */

00419e00        struct FrontendWidget* new_game_widget = menu->new_game_widget
00419e02        enum FrontendWidgetFlag widget_flags = new_game_widget->widget_flags
00419e0a        if ((widget_flags.b & 0x20) != 0)
00419e0c        widget_flags.b &= 0xdf
00419e0e        new_game_widget->widget_flags = widget_flags
00419e14        destroy_main_menu(menu)
00419e1e        g_game_base->players[0].frontend_state = 2
00419e2e        g_game_base->players[0].redispatch_requested = 1
00419e35        return
00419e36        struct FrontendWidget* credits_widget = menu->credits_widget
00419e39        enum FrontendWidgetFlag widget_flags_1 = credits_widget->widget_flags
00419e41        if ((widget_flags_1.b & 0x20) != 0)
00419e43        widget_flags_1.b &= 0xdf
00419e45        credits_widget->widget_flags = widget_flags_1
00419e4b        destroy_main_menu(menu)
00419e56        g_game_base->players[0].frontend_state = 0xe
00419e65        g_game_base->players[0].redispatch_requested = 1
00419e6c        return
00419e6d        struct FrontendWidget* exit_widget = menu->exit_widget
00419e70        enum FrontendWidgetFlag widget_flags_2 = exit_widget->widget_flags
00419e78        if ((widget_flags_2.b & 0x20) != 0)
00419e7a        widget_flags_2.b &= 0xdf
00419e7c        exit_widget->widget_flags = widget_flags_2
00419e82        struct GameRoot* game_base_1 = g_game_base
00419e8d        game_base_1->exit_controller.previous_frontend_state = game_base_1->players[0].frontend_state
00419ea2        g_game_base->exit_controller.prompt_y = menu->exit_widget->layout_top
00419ead        g_game_base->exit_controller.state = 0xa
00419ebd        g_game_base->players[0].frontend_state = 8
00419ec7        return
00419ec8        struct FrontendWidget* options_widget = menu->options_widget
00419ecb        enum FrontendWidgetFlag widget_flags_3 = options_widget->widget_flags
00419ed3        if ((widget_flags_3.b & 0x20) != 0)
00419ed5        widget_flags_3.b &= 0xdf
00419ed7        options_widget->widget_flags = widget_flags_3
00419ee3        g_game_base->options.active = 1
00419eea        struct GameRoot* game_base_2 = g_game_base
00419ef5        game_base_2->options.previous_frontend_state = game_base_2->players[0].frontend_state
00419f01        g_game_base->players[0].frontend_state = 6
00419f0b        return
00419f0c        struct FrontendWidget* high_scores_widget = menu->high_scores_widget
00419f0f        enum FrontendWidgetFlag widget_flags_4 = high_scores_widget->widget_flags
00419f17        if ((widget_flags_4.b & 0x20) == 0)
00419f17        return
00419f19        widget_flags_4.b &= 0xdf
00419f1b        high_scores_widget->widget_flags = widget_flags_4
00419f21        destroy_main_menu(menu)
00419f2b        g_game_base->players[0].frontend_state = 0x12
00419f3b        g_game_base->high_score.mode = 0
00419f45        return
