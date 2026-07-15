/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_challenge_setup_screen @ 0x416370 */

00416376        hide_gameplay_scores(gui->game)
0041637d        int32_t level_mode = gui->game->level_mode
00416383        if (level_mode == 0)
004166bf        struct FrontendWidget* next_level_button_3 = gui->next_level_button
004166c2        enum FrontendWidgetFlag widget_flags_8 = next_level_button_3->widget_flags
004166ca        if ((widget_flags_8.b & 0x20) != 0)
004166cc        widget_flags_8.b &= 0xdf
004166ce        next_level_button_3->widget_flags = widget_flags_8
004166d4        struct SubgameRuntime* game_4 = gui->game
004166da        game_4->level_mode_arg += 1
004166dd        struct SubgameRuntime* game_5 = gui->game
004166ed        load_frontend_level_by_mode_and_index(&game_5->level_definition, game_5->level_mode, game_5->level_mode_arg)
00416704        rstrcpy_checked_ascii(&gui->level_name_widget->text_buffer, &gui->game->level_definition.level_display_name)
0041670f        layout_frontend_widget(gui->level_name_widget)
00416714        struct FrontendWidget* previous_level_button_3 = gui->previous_level_button
00416717        enum FrontendWidgetFlag widget_flags_9 = previous_level_button_3->widget_flags
0041671f        if ((widget_flags_9.b & 0x20) != 0)
00416721        widget_flags_9.b &= 0xdf
00416723        previous_level_button_3->widget_flags = widget_flags_9
00416729        struct SubgameRuntime* game_6 = gui->game
0041672f        game_6->level_mode_arg -= 1
00416732        struct SubgameRuntime* game_7 = gui->game
00416742        load_frontend_level_by_mode_and_index(&game_7->level_definition, game_7->level_mode, game_7->level_mode_arg)
00416759        rstrcpy_checked_ascii(&gui->level_name_widget->text_buffer, &gui->game->level_definition.level_display_name)
00416764        layout_frontend_widget(gui->level_name_widget)
00416778        struct FrontendWidget* previous_level_button_1 = gui->previous_level_button
0041677d        enum FrontendWidgetFlag widget_flags_13 = previous_level_button_1->widget_flags
00416783        enum FrontendWidgetFlag edi_7
00416783        if (gui->game->level_mode_arg != 0)
00416789        edi_7 = widget_flags_13 & ~FRONTEND_WIDGET_FLAG_DISABLED
00416785        edi_7 = widget_flags_13 | FRONTEND_WIDGET_FLAG_DISABLED
0041678b        previous_level_button_1->widget_flags = edi_7
0041679e        struct FrontendWidget* next_level_button_1 = gui->next_level_button
004167a1        if (gui->game->level_mode_arg != g_runtime_config.highest_galaxy_route_index)
004167ab        next_level_button_1->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED
004167a3        next_level_button_1->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED
004167b1        struct FrontendWidget* back_button_2 = gui->back_button
004167b4        enum FrontendWidgetFlag widget_flags_10 = back_button_2->widget_flags
004167bc        if ((widget_flags_10.b & 0x20) != 0)
004167be        widget_flags_10.b &= 0xdf
004167c0        back_button_2->widget_flags = widget_flags_10
004167c8        destroy_challenge_setup_screen(gui)
004167d4        return 3
004167d5        struct FrontendWidget* play_button_2 = gui->play_button
004167d8        enum FrontendWidgetFlag widget_flags_11 = play_button_2->widget_flags
004167e0        if ((widget_flags_11.b & 0x20) != 0)
004167e2        widget_flags_11.b &= 0xdf
004167e4        play_button_2->widget_flags = widget_flags_11
004167ec        destroy_challenge_setup_screen(gui)
004167f8        return 1
0041638a        if (level_mode == 1)
004165fa        struct FrontendWidget* back_button_1 = gui->back_button
004165fd        enum FrontendWidgetFlag widget_flags_5 = back_button_1->widget_flags
00416605        if ((widget_flags_5.b & 0x20) != 0)
00416607        widget_flags_5.b &= 0xdf
00416609        back_button_1->widget_flags = widget_flags_5
00416611        destroy_challenge_setup_screen(gui)
0041661d        return 3
0041661e        struct FrontendWidget* play_button_1 = gui->play_button
00416621        enum FrontendWidgetFlag widget_flags_6 = play_button_1->widget_flags
00416629        if ((widget_flags_6.b & 0x20) != 0)
0041662b        widget_flags_6.b &= 0xdf
0041662d        play_button_1->widget_flags = widget_flags_6
00416635        destroy_challenge_setup_screen(gui)
00416641        return 1
00416657        int32_t eax_30
00416657        int16_t x87control
00416657        int16_t x87control_1
00416657        eax_30, x87control_1 = ftol(x87control, fconvert.t(gui->speed_slider->slider_position_target) * fconvert.t(100f) + fconvert.t(0.100000001f))
0041665c        g_runtime_config.completion_bonus_x_source = eax_30
0041667b        g_runtime_config.completion_bonus_y_source = ftol(x87control_1, fconvert.t(gui->difficulty_slider->slider_position_target) * fconvert.t(100f) + fconvert.t(0.100000001f))
00416680        struct FrontendWidget* replay_button_2 = gui->replay_button
00416683        enum FrontendWidgetFlag widget_flags_7 = replay_button_2->widget_flags
0041668b        if ((widget_flags_7.b & 0x20) != 0)
00416691        widget_flags_7.b &= 0xdf
00416693        replay_button_2->widget_flags = widget_flags_7
0041669b        destroy_challenge_setup_screen(gui)
004166a3        gui->game->selected_level_record_active = 1
004166aa        struct SubgameRuntime* game_12 = gui->game
004166b7        game_12->selected_level_record = &game_12->sub_high_score.survival_pending_record
004166be        return 1
00416393        if (level_mode == 4)
00416399        struct FrontendWidget* next_level_button_2 = gui->next_level_button
0041639c        enum FrontendWidgetFlag widget_flags = next_level_button_2->widget_flags
004163a4        if ((widget_flags.b & 0x20) != 0)
004163aa        widget_flags.b &= 0xdf
004163ac        next_level_button_2->widget_flags = widget_flags
004163b2        struct SubgameRuntime* game = gui->game
004163b8        game->level_mode_arg += 1
004163bb        struct SubgameRuntime* game_1 = gui->game
004163cb        load_frontend_level_by_mode_and_index(&game_1->level_definition, game_1->level_mode, game_1->level_mode_arg)
004163e2        rstrcpy_checked_ascii(&gui->level_name_widget->text_buffer, &gui->game->level_definition.level_display_name)
004163ed        layout_frontend_widget(gui->level_name_widget)
004163f2        struct SubgameRuntime* game_8 = gui->game
00416418        format_time_trial_string(&game_8->time_trial, &game_8->sub_high_score.time_trial_route_records[game_8->level_mode_arg].score_or_time)
0041642d        rstrcpy_checked_ascii(&gui->game->bottom_score_widget->text_buffer, 0x751478)
00416435        struct FrontendWidget* previous_level_button_2 = gui->previous_level_button
00416438        enum FrontendWidgetFlag widget_flags_1 = previous_level_button_2->widget_flags
00416440        if ((widget_flags_1.b & 0x20) != 0)
00416446        widget_flags_1.b &= 0xdf
00416448        previous_level_button_2->widget_flags = widget_flags_1
0041644e        struct SubgameRuntime* game_2 = gui->game
00416454        game_2->level_mode_arg -= 1
00416457        struct SubgameRuntime* game_3 = gui->game
00416467        load_frontend_level_by_mode_and_index(&game_3->level_definition, game_3->level_mode, game_3->level_mode_arg)
0041647e        rstrcpy_checked_ascii(&gui->level_name_widget->text_buffer, &gui->game->level_definition.level_display_name)
00416489        layout_frontend_widget(gui->level_name_widget)
0041648e        struct SubgameRuntime* game_9 = gui->game
004164b4        format_time_trial_string(&game_9->time_trial, &game_9->sub_high_score.time_trial_route_records[game_9->level_mode_arg].score_or_time)
004164c9        rstrcpy_checked_ascii(&gui->game->bottom_score_widget->text_buffer, 0x751478)
004164e0        struct FrontendWidget* previous_level_button = gui->previous_level_button
004164e5        enum FrontendWidgetFlag widget_flags_12 = previous_level_button->widget_flags
004164eb        enum FrontendWidgetFlag edi_2
004164eb        if (gui->game->level_mode_arg != 0)
004164f1        edi_2 = widget_flags_12 & ~FRONTEND_WIDGET_FLAG_DISABLED
004164ed        edi_2 = widget_flags_12 | FRONTEND_WIDGET_FLAG_DISABLED
004164f3        previous_level_button->widget_flags = edi_2
00416506        struct FrontendWidget* next_level_button = gui->next_level_button
00416509        if (gui->game->level_mode_arg != g_runtime_config.highest_galaxy_route_index)
00416513        next_level_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED
0041650b        next_level_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED
00416519        struct SubgameRuntime* game_10 = gui->game
00416538        struct FrontendWidget* replay_button = gui->replay_button
0041653e        struct FrontendWidget* previous_widget
0041653e        if (game_10->sub_high_score.time_trial_route_records[game_10->level_mode_arg].active == 1)
0041654b        unhide_border_init(replay_button)
00416553        previous_widget = gui->replay_button
00416540        hide_border_init(replay_button)
00416548        previous_widget = gui->play_button
00416557        stack_widget_below(gui->back_button, previous_widget)
0041655c        struct FrontendWidget* back_button = gui->back_button
0041655f        enum FrontendWidgetFlag widget_flags_2 = back_button->widget_flags
00416567        if ((widget_flags_2.b & 0x20) != 0)
00416569        widget_flags_2.b &= 0xdf
0041656b        back_button->widget_flags = widget_flags_2
00416573        destroy_challenge_setup_screen(gui)
0041657f        return 3
00416580        struct FrontendWidget* play_button = gui->play_button
00416583        enum FrontendWidgetFlag widget_flags_3 = play_button->widget_flags
0041658b        if ((widget_flags_3.b & 0x20) != 0)
0041658d        widget_flags_3.b &= 0xdf
0041658f        play_button->widget_flags = widget_flags_3
00416597        destroy_challenge_setup_screen(gui)
004165a3        return 1
004165a4        struct FrontendWidget* replay_button_1 = gui->replay_button
004165a7        enum FrontendWidgetFlag widget_flags_4 = replay_button_1->widget_flags
004165af        if ((widget_flags_4.b & 0x20) != 0)
004165b5        widget_flags_4.b &= 0xdf
004165b7        replay_button_1->widget_flags = widget_flags_4
004165bf        destroy_challenge_setup_screen(gui)
004165c7        gui->game->selected_level_record_active = 1
004165ce        struct SubgameRuntime* game_11 = gui->game
004165ed        game_11->selected_level_record = &game_11->sub_high_score.time_trial_route_records[game_11->level_mode_arg]
004165f9        return 1
004167fd        return 0
