/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_high_score_screen @ 0x417260 */

00417260        struct HighScore* high_score_1 = high_score
0041726b        if (high_score->entering_name != 0)
00417274        void* ecx = high_score->name_row_widgets[high_score->selected_rank]
00417278        int32_t eax_2 = *(ecx + 0x1a0)
00417281        if ((eax_2:1.b & 0x40) != 0)
00417287        eax_2:1.b &= 0xbf
0041728a        *(ecx + 0x1a0) = eax_2
00417292        destroy_high_score_screen(high_score)
0041729c        kill_game_sprites(&g_sprite_manager)
004172a1        int32_t selected_rank = high_score->selected_rank
004172d3        rstrcpy_checked_ascii(*(g_game_base + 0x6ffae0) + selected_rank * 0x1fac0 + 0x54, &high_score->name_row_widgets[selected_rank]->text_buffer.raw)
004172f1        rstrcpy_checked_ascii(&g_game_base[0x1a4], &high_score->name_row_widgets[high_score->selected_rank]->text_buffer.raw)
00417309        rstrcpy_checked_ascii(&data_4df978, &high_score->name_row_widgets[high_score->selected_rank]->text_buffer.raw)
00417313        exit_high_score_screen(high_score)
0041731c        return
0041731d        struct FrontendWidget* submit_name_button = high_score->submit_name_button
00417320        uint32_t widget_flags = submit_name_button->widget_flags
00417328        if ((widget_flags.b & 0x20) != 0)
0041732a        widget_flags.b &= 0xdf
0041732c        submit_name_button->widget_flags = widget_flags
00417335        void* eax_9 = high_score->name_row_widgets[high_score->selected_rank]
00417339        *(eax_9 + 0x1a0) |= 0x8000000
00417343        struct FrontendWidget* cancel_name_button = high_score->cancel_name_button
00417346        uint32_t widget_flags_1 = cancel_name_button->widget_flags
0041734e        if ((widget_flags_1.b & 0x20) != 0)
00417354        widget_flags_1.b &= 0xdf
00417356        cancel_name_button->widget_flags = widget_flags_1
0041735e        destroy_high_score_screen(high_score)
00417368        kill_game_sprites(&g_sprite_manager)
0041737d        mini_delete_high_score_entry(&g_game_base[0x6ffae0], high_score->selected_rank)
00417384        exit_high_score_screen(high_score)
0041734e        return
0041738e        struct FrontendWidget* bank_toggle_button = high_score->bank_toggle_button
00417391        uint32_t widget_flags_2 = bank_toggle_button->widget_flags
00417399        if ((widget_flags_2.b & 0x20) != 0)
0041739b        widget_flags_2.b &= 0xdf
0041739d        bank_toggle_button->widget_flags = widget_flags_2
004173a5        destroy_high_score_screen(high_score)
004173aa        int32_t selected_bank = high_score->selected_bank
004173b0        if (selected_bank == 0)
004173be        high_score->selected_bank = 1
004173b3        if (selected_bank == 1)
004173b5        high_score->selected_bank = 0
004173ca        g_high_score_selected_bank = high_score->selected_bank
004173d5        initialize_high_score_screen(high_score, high_score->selected_bank, 0xffffffff)
004173de        return
004173df        struct FrontendWidget* back_button = high_score->back_button
004173e2        uint32_t widget_flags_3 = back_button->widget_flags
004173ea        if ((widget_flags_3.b & 0x20) != 0)
004173ec        widget_flags_3.b &= 0xdf
004173f3        back_button->widget_flags = widget_flags_3
004173f9        int32_t mode = high_score->mode
004173fe        if (mode == 1)
00417408        *(g_game_base + 0x1b8) = 0xa
00417417        g_game_base[0x30c] = 1
0041741d        destroy_high_score_screen(high_score)
00417426        return
00417429        if (mode == 0)
00417431        *(g_game_base + 0x1b8) = 4
0041743d        destroy_high_score_screen(high_score)
00417446        return
00417447        char* game_base_3 = g_game_base
0041744d        int32_t i = 0
00417457        if (*(game_base_3 + 0x6ffae4) s<= 0)
00417457        return
00417464        int32_t edi_1 = 0
00417466        high_score_1 = &high_score->replay_row_widgets
00417478        if (*(*(game_base_3 + 0x6ffae0) + edi_1) == 1)
00417482        int32_t field_00 = high_score_1->field_00
00417486        if (field_00 != 0)
0041748c        int32_t eax_17 = *(field_00 + 0x1a0)
00417494        if ((eax_17.b & 0x20) != 0)
00417496        eax_17.b &= 0xdf
00417498        *(field_00 + 0x1a0) = eax_17
004174a4        *(g_game_base + 0x1b8) = 0xa
004174b6        g_game_base[0x30c] = 1
004174bc        destroy_high_score_screen(high_score)
004174c1        char* game_base_1 = g_game_base
004174ce        *(game_base_1 + 0x1066bec) = *(game_base_1 + 0x6ffae0) + edi_1
004174da        g_game_base[0x1066be8] = 1
004174e5        g_game_base[0x1066be9] = 1
004174f1        *(g_game_base + 0x1066bf0) = 0x12
004174fb        char* game_base_2 = g_game_base
00417509        *(game_base_2 + 0x74658) = *(*(game_base_2 + 0x1066bec) + 0x2c)
0041750f        game_base_3 = g_game_base
00417519        i += 1
0041751d        edi_1 += 0x1fac0
00417523        high_score_1 = &high_score_1->mode
0041752f        do while (i s< *(game_base_3 + 0x6ffae4))
0041753a        return
