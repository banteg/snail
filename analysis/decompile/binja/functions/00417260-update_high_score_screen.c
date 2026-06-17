/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_high_score_screen @ 0x417260 */

00417260        struct HighScoreScreen* screen_1 = screen
0041726b        int32_t result
0041726b        if (screen->entering_name == 0)
0041738e        struct FrontendWidget* bank_toggle_button = screen->bank_toggle_button
00417391        int32_t eax_13 = bank_toggle_button->__offset(0x1a0).d
00417399        if ((eax_13.b & 0x20) != 0)
0041739b        eax_13.b &= 0xdf
0041739d        bank_toggle_button->__offset(0x1a0).d = eax_13
004173a5        destroy_high_score_screen(screen)
004173aa        int32_t selected_bank = screen->selected_bank
004173b0        if (selected_bank == 0)
004173be        screen->selected_bank = 1
004173b3        if (selected_bank == 1)
004173b5        screen->selected_bank = 0
004173ca        data_4df9c0 = screen->selected_bank
004173de        return initialize_high_score_screen(screen, screen->selected_bank, 0xffffffff)
004173df        struct FrontendWidget* back_button = screen->back_button
004173e2        int32_t eax_18 = back_button->__offset(0x1a0).d
004173ea        if ((eax_18.b & 0x20) != 0)
004173ec        eax_18.b &= 0xdf
004173f3        back_button->__offset(0x1a0).d = eax_18
004173f9        int32_t mode = screen->mode
004173fe        if (mode == 1)
00417408        *(data_4df904 + 0x1b8) = 0xa
00417417        *(data_4df904 + 0x30c) = 1
0041741d        destroy_high_score_screen(screen)
00417426        return 0
00417429        if (mode == 0)
00417431        *(data_4df904 + 0x1b8) = 4
0041743d        destroy_high_score_screen(screen)
00417446        return 0
00417447        void* edx_12 = data_4df904
0041744d        int32_t ebp_1 = 0
0041744f        result = *(edx_12 + 0x6ffae4)
00417457        if (result s> 0)
00417464        int32_t edi_1 = 0
00417466        screen_1 = &screen->replay_row_widgets
00417478        if (*(*(edx_12 + 0x6ffae0) + edi_1) == 1)
00417482        int32_t field_00 = screen_1->field_00
00417486        if (field_00 != 0)
0041748c        int32_t eax_22 = *(field_00 + 0x1a0)
00417494        if ((eax_22.b & 0x20) != 0)
00417496        eax_22.b &= 0xdf
00417498        *(field_00 + 0x1a0) = eax_22
004174a4        *(data_4df904 + 0x1b8) = 0xa
004174b6        *(data_4df904 + 0x30c) = 1
004174bc        destroy_high_score_screen(screen)
004174c1        void* eax_23 = data_4df904
004174ce        *(eax_23 + 0x1066bec) = *(eax_23 + 0x6ffae0) + edi_1
004174da        *(data_4df904 + 0x1066be8) = 1
004174e5        *(data_4df904 + 0x1066be9) = 1
004174f1        *(data_4df904 + 0x1066bf0) = 0x12
004174fb        void* eax_25 = data_4df904
00417509        *(eax_25 + 0x74658) = *(*(eax_25 + 0x1066bec) + 0x2c)
0041750f        edx_12 = data_4df904
00417519        ebp_1 += 1
0041751d        edi_1 += 0x1fac0
00417523        screen_1 = &screen_1->mode
00417527        result = *(edx_12 + 0x6ffae4)
0041752f        do while (ebp_1 s< result)
00417274        void* ecx = screen->name_row_widgets[screen->selected_rank]
00417278        int32_t eax_2 = *(ecx + 0x1a0)
00417281        if ((eax_2:1.b & 0x40) != 0)
00417287        eax_2:1.b &= 0xbf
0041728a        *(ecx + 0x1a0) = eax_2
00417292        destroy_high_score_screen(screen)
0041729c        kill_game_sprites()
004172a1        int32_t selected_rank = screen->selected_rank
004172d3        rstrcpy_checked_ascii(*(data_4df904 + 0x6ffae0) + selected_rank * 0x1fac0 + 0x54, screen->name_row_widgets[selected_rank] + 0x2cc)
004172f1        rstrcpy_checked_ascii(data_4df904 + 0x1a4, screen->name_row_widgets[screen->selected_rank] + 0x2cc)
00417309        rstrcpy_checked_ascii(&data_4df978, screen->name_row_widgets[screen->selected_rank] + 0x2cc)
0041731c        return exit_high_score_screen()
0041731d        struct FrontendWidget* cancel_name_button = screen->cancel_name_button
00417320        int32_t eax_9 = cancel_name_button->__offset(0x1a0).d
00417328        if ((eax_9.b & 0x20) != 0)
0041732a        eax_9.b &= 0xdf
0041732c        cancel_name_button->__offset(0x1a0).d = eax_9
00417335        void* eax_11 = screen->name_row_widgets[screen->selected_rank]
00417339        *(eax_11 + 0x1a0) |= 0x8000000
00417343        struct FrontendWidget* submit_name_button = screen->submit_name_button
00417346        result = submit_name_button->__offset(0x1a0).d
0041734e        if ((result.b & 0x20) != 0)
00417354        result.b &= 0xdf
00417356        submit_name_button->__offset(0x1a0).d = result
0041735e        destroy_high_score_screen(screen)
00417368        kill_game_sprites()
0041737d        commit_high_score_entry_into_top_ten(data_4df904 + 0x6ffae0, screen->selected_rank)
0041738d        return exit_high_score_screen()
0041753a        return result
