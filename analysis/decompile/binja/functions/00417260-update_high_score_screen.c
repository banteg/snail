/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_high_score_screen @ 0x417260 */

00417260        struct HighScoreScreen* screen_1 = screen
0041726b        uint32_t widget_flags_1
0041726b        if (screen->entering_name == 0)
0041738e        struct FrontendWidget* bank_toggle_button = screen->bank_toggle_button
00417391        uint32_t widget_flags_2 = bank_toggle_button->widget_flags
00417399        if ((widget_flags_2.b & 0x20) != 0)
0041739b        widget_flags_2.b &= 0xdf
0041739d        bank_toggle_button->widget_flags = widget_flags_2
004173a5        destroy_high_score_screen(screen)
004173aa        int32_t selected_bank = screen->selected_bank
004173b0        if (selected_bank == 0)
004173be        screen->selected_bank = 1
004173b3        if (selected_bank == 1)
004173b5        screen->selected_bank = 0
004173ca        g_high_score_selected_bank = screen->selected_bank
004173de        return initialize_high_score_screen(screen, screen->selected_bank, 0xffffffff)
004173df        struct FrontendWidget* back_button = screen->back_button
004173e2        uint32_t widget_flags_3 = back_button->widget_flags
004173ea        if ((widget_flags_3.b & 0x20) != 0)
004173ec        widget_flags_3.b &= 0xdf
004173f3        back_button->widget_flags = widget_flags_3
004173f9        int32_t mode = screen->mode
004173fe        if (mode == 1)
00417408        *(g_game_base + 0x1b8) = 0xa
00417417        *(g_game_base + 0x30c) = 1
0041741d        destroy_high_score_screen(screen)
00417426        return 0
00417429        if (mode == 0)
00417431        *(g_game_base + 0x1b8) = 4
0041743d        destroy_high_score_screen(screen)
00417446        return 0
00417447        void* game_base_3 = g_game_base
0041744d        int32_t ebp_1 = 0
0041744f        widget_flags_1 = *(game_base_3 + 0x6ffae4)
00417457        if (widget_flags_1 s> 0)
00417464        int32_t edi_1 = 0
00417466        screen_1 = &screen->replay_row_widgets
00417478        if (*(*(game_base_3 + 0x6ffae0) + edi_1) == 1)
00417482        int32_t field_00 = screen_1->field_00
00417486        if (field_00 != 0)
0041748c        int32_t eax_19 = *(field_00 + 0x1a0)
00417494        if ((eax_19.b & 0x20) != 0)
00417496        eax_19.b &= 0xdf
00417498        *(field_00 + 0x1a0) = eax_19
004174a4        *(g_game_base + 0x1b8) = 0xa
004174b6        *(g_game_base + 0x30c) = 1
004174bc        destroy_high_score_screen(screen)
004174c1        void* game_base_1 = g_game_base
004174ce        *(game_base_1 + 0x1066bec) = *(game_base_1 + 0x6ffae0) + edi_1
004174da        *(g_game_base + 0x1066be8) = 1
004174e5        *(g_game_base + 0x1066be9) = 1
004174f1        *(g_game_base + 0x1066bf0) = 0x12
004174fb        void* game_base_2 = g_game_base
00417509        *(game_base_2 + 0x74658) = *(*(game_base_2 + 0x1066bec) + 0x2c)
0041750f        game_base_3 = g_game_base
00417519        ebp_1 += 1
0041751d        edi_1 += 0x1fac0
00417523        screen_1 = &screen_1->mode
00417527        widget_flags_1 = *(game_base_3 + 0x6ffae4)
0041752f        do while (ebp_1 s< widget_flags_1)
00417274        void* ecx = screen->name_row_widgets[screen->selected_rank]
00417278        int32_t eax_2 = *(ecx + 0x1a0)
00417281        if ((eax_2:1.b & 0x40) != 0)
00417287        eax_2:1.b &= 0xbf
0041728a        *(ecx + 0x1a0) = eax_2
00417292        destroy_high_score_screen(screen)
0041729c        kill_game_sprites(&g_sprite_manager)
004172a1        int32_t selected_rank = screen->selected_rank
004172d3        rstrcpy_checked_ascii(*(g_game_base + 0x6ffae0) + selected_rank * 0x1fac0 + 0x54, &screen->name_row_widgets[selected_rank]->_pad_00[0x2cc])
004172f1        rstrcpy_checked_ascii(g_game_base + 0x1a4, &screen->name_row_widgets[screen->selected_rank]->_pad_00[0x2cc])
00417309        rstrcpy_checked_ascii(&data_4df978, &screen->name_row_widgets[screen->selected_rank]->_pad_00[0x2cc])
0041731c        return exit_high_score_screen(screen)
0041731d        struct FrontendWidget* cancel_name_button = screen->cancel_name_button
00417320        uint32_t widget_flags = cancel_name_button->widget_flags
00417328        if ((widget_flags.b & 0x20) != 0)
0041732a        widget_flags.b &= 0xdf
0041732c        cancel_name_button->widget_flags = widget_flags
00417335        void* eax_10 = screen->name_row_widgets[screen->selected_rank]
00417339        *(eax_10 + 0x1a0) |= 0x8000000
00417343        struct FrontendWidget* submit_name_button = screen->submit_name_button
00417346        widget_flags_1 = submit_name_button->widget_flags
0041734e        if ((widget_flags_1.b & 0x20) != 0)
00417354        widget_flags_1.b &= 0xdf
00417356        submit_name_button->widget_flags = widget_flags_1
0041735e        destroy_high_score_screen(screen)
00417368        kill_game_sprites(&g_sprite_manager)
0041737d        mini_delete_high_score_entry(g_game_base + 0x6ffae0, screen->selected_rank)
0041738d        return exit_high_score_screen(screen)
0041753a        return widget_flags_1
