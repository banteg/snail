/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_completion_screen @ 0x4067e0 */

004067f4        switch (exit_controller->state - 2)
0040690d        case 0
0040690d        struct FrontendWidget* yes_button_3 = exit_controller->yes_button
00406910        enum FrontendWidgetFlag widget_flags_3 = yes_button_3->widget_flags
00406918        if ((widget_flags_3.b & 0x20) != 0)
0040691e        widget_flags_3.b &= 0xdf
00406922        yes_button_3->widget_flags = widget_flags_3
00406934        complete_subgame(&g_game_base->subgame, 1)
00406939        struct GameRoot* game_base_3 = g_game_base
00406945        if (game_base_3->players[0].high_score_entry_pending != 1)
00406996        destroy_completion_screen(exit_controller)
004069a6        uninit_pause_menu(&g_game_base->subgame.sub_pause)
004069b2        g_game_base->subgame.subgame_pause_gate = 0
004069bd        set_sprite_manager_paused(&g_sprite_manager, 0)
004069ce        destroy_subgame(&g_game_base->subgame)
004069d3        struct GameRoot* game_base_5 = g_game_base
004069d9        int32_t level_mode = game_base_5->subgame.level_mode
004069e7        if (level_mode == 4 || level_mode == 1)
004069fe        initialize_subgame(&game_base_5->subgame)
004069e9        game_base_5->players[0].frontend_state = 2
0040694f        exit_controller->previous_frontend_state = game_base_3->players[0].frontend_state
00406952        destroy_completion_screen(exit_controller)
00406962        uninit_pause_menu(&g_game_base->subgame.sub_pause)
0040696e        g_game_base->subgame.subgame_pause_gate = 0
00406979        set_sprite_manager_paused(&g_sprite_manager, 0)
0040698a        destroy_subgame(&g_game_base->subgame)
00406a54        case 1
00406a54        struct FrontendWidget* yes_button_5 = exit_controller->yes_button
00406a57        enum FrontendWidgetFlag widget_flags_5 = yes_button_5->widget_flags
00406a5f        if ((widget_flags_5.b & 0x20) != 0)
00406a65        widget_flags_5.b &= 0xdf
00406a67        yes_button_5->widget_flags = widget_flags_5
00406a6f        destroy_completion_screen(exit_controller)
00406a80        uninit_pause_menu(&g_game_base->subgame.sub_pause)
00406a91        g_game_base->subgame.subgame_pause_gate = 0
00406a97        set_sprite_manager_paused(&g_sprite_manager, 0)
00406aa7        destroy_subgame(&g_game_base->subgame)
00406aac        struct GameRoot* game_base_4 = g_game_base
00406ab7        game_base_4->players[0].frontend_state = game_base_4->subgame.selected_level_record_cursor
00406ac2        case 2
00406ac2        struct FrontendWidget* yes_button_6 = exit_controller->yes_button
00406ac5        enum FrontendWidgetFlag widget_flags_6 = yes_button_6->widget_flags
00406acd        if ((widget_flags_6.b & 0x20) != 0)
00406ad3        widget_flags_6.b &= 0xdf
00406ad5        yes_button_6->widget_flags = widget_flags_6
00406add        label_406add:
00406add        destroy_completion_screen(exit_controller)
00406aee        destroy_subgame(&g_game_base->subgame)
00406af8        g_game_base->players[0].frontend_state = 2
00406a08        case 5
00406a08        struct FrontendWidget* yes_button_4 = exit_controller->yes_button
00406a0b        enum FrontendWidgetFlag widget_flags_4 = yes_button_4->widget_flags
00406a13        if ((widget_flags_4.b & 0x20) != 0)
00406a19        widget_flags_4.b &= 0xdf
00406a1b        yes_button_4->widget_flags = widget_flags_4
00406a23        destroy_completion_screen(exit_controller)
00406a33        uninit_pause_menu(&g_game_base->subgame.sub_pause)
00406a3f        g_game_base->subgame.subgame_pause_gate = 0
00406a4a        set_sprite_manager_paused(&g_sprite_manager, 0)
00406aee        destroy_subgame(&g_game_base->subgame)
00406af8        g_game_base->players[0].frontend_state = 2
00406b10        case 6
00406b10        update_new_game_menu(&g_game_base->intro)
00406b15        struct FrontendWidget* yes_button_7 = exit_controller->yes_button
00406b18        enum FrontendWidgetFlag widget_flags_7 = yes_button_7->widget_flags
00406b20        if ((widget_flags_7.b & 0x20) != 0)
00406b22        widget_flags_7.b &= 0xdf
00406b29        yes_button_7->widget_flags = widget_flags_7
00406b2f        launch_alpha72_url("Alpha72.url")
00406b3f        g_game_base->players[0].frontend_state = 0
00406b4a        g_game_base->frontend_link_latch = 0
00406b50        destroy_completion_screen(exit_controller)
004067fb        case 7
004067fb        struct FrontendWidget* yes_button = exit_controller->yes_button
004067fe        enum FrontendWidgetFlag widget_flags = yes_button->widget_flags
00406806        if ((widget_flags.b & 0x20) != 0)
0040680c        widget_flags.b &= 0xdf
0040680e        yes_button->widget_flags = widget_flags
00406816        destroy_completion_screen(exit_controller)
00406820        g_game_base->frontend_quit_requested = 3
00406838        case 8
00406838        update_main_menu(&g_game_base->main_menu)
0040683d        struct FrontendWidget* yes_button_1 = exit_controller->yes_button
00406840        enum FrontendWidgetFlag widget_flags_1 = yes_button_1->widget_flags
00406848        if ((widget_flags_1.b & 0x20) != 0)
0040684e        widget_flags_1.b &= 0xdf
00406850        yes_button_1->widget_flags = widget_flags_1
00406858        destroy_completion_screen(exit_controller)
00406869        destroy_main_menu(&g_game_base->main_menu)
0040686e        struct GameRoot* game_base_1 = g_game_base
00406876        if (game_base_1->frontend_quit_requested == 0)
0040687c        game_base_1->frontend_quit_requested = 1
00406893        case 9
00406893        update_galaxy(&g_game_base->subgame.galaxy)
00406898        struct FrontendWidget* yes_button_2 = exit_controller->yes_button
0040689b        enum FrontendWidgetFlag widget_flags_2 = yes_button_2->widget_flags
004068a3        if ((widget_flags_2.b & 0x20) != 0)
004068a9        widget_flags_2.b &= 0xdf
004068ab        yes_button_2->widget_flags = widget_flags_2
004068bd        destroy_galaxy(&g_game_base->subgame.galaxy)
004068d0        complete_subgame(&g_game_base->subgame, 1)
004068d5        struct GameRoot* game_base_2 = g_game_base
004068e1        if (game_base_2->players[0].high_score_entry_pending != 1)
004068e1        goto label_406add
004068ef        exit_controller->previous_frontend_state = game_base_2->players[0].frontend_state
004068f2        destroy_completion_screen(exit_controller)
00406903        destroy_subgame(&g_game_base->subgame)
00406b55        struct FrontendWidget* no_button = exit_controller->no_button
00406b58        enum FrontendWidgetFlag widget_flags_8 = no_button->widget_flags
00406b60        if ((widget_flags_8.b & 0x20) == 0)
00406b60        return
00406b62        widget_flags_8.b &= 0xdf
00406b64        no_button->widget_flags = widget_flags_8
00406b73        g_game_base->players[0].frontend_state = exit_controller->previous_frontend_state
00406b80        g_game_base->frontend_link_latch = 0
00406b86        destroy_completion_screen(exit_controller)
00406b8d        return
