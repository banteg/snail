/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_subgame @ 0x438850 */

0043886b        *(g_game_base + 0x4f26c) = 1
00438877        if (game->level_mode == 7)
0043887f        uninit_tutorial(&game->tutorial)
0043888b        uninit_warning(&game->player.warning)
00438896        clear_active_landscape_entries(&game->landscape_manager)
004388a1        uninit_times_up(&game->times_up)
004388a8        remove_subgame_bods(game)
004388b7        if (game->subgame_state != 1)
004388bd        int32_t level_mode = game->level_mode
004388c6        if (level_mode == 0 || level_mode == 1)
004388ce        flush_row_event_display(&game->completion)
004388d4        struct BodNode** esi_1 = &game->sub_lazers.slots[0].bod.list_next
004388da        int32_t i_4 = 0x14
00438952        int32_t i
004388df        uint32_t list_flags = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_flags
004388e4        if ((0x200 & list_flags) != 0)
004388ec        void* ecx_7 = &g_game_base[0x5a8]
004388f4        if ((0x200 & list_flags) == 0)
004388fb        report_errorf("List remove")
00438907        if ((list_flags.b & 0x40) == 0)
00438918        struct BodNode* list_next = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_next
0043891c        if (list_next != 0)
00438921        list_next->list_prev = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_prev
00438924        struct BodNode* list_prev = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_prev
00438929        if (list_prev == 0)
00438934        *(ecx_7 + 4) = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_next
0043892d        list_prev->list_next = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_next
00438937        struct BodNode* edx_6
00438937        edx_6.b = *(ecx_7 + 8)
00438937        edx_6:1.b = *(ecx_7 + 9)
0043893d        (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_next = edx_6
0043893f        *(ecx_7 + 8) = (esi_1.w - 0xc).b
0043893f        *(ecx_7 + 9) = (esi_1.w - 0xc):1.b
00438942        uint32_t list_flags_1 = (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_flags
00438945        list_flags_1:1.b &= 0xfd
00438948        (esi_1 - 0x356b0c)->sub_lazers.slots[0].bod.list_flags = list_flags_1
0043890e        report_errorf("List remove NEXTBOD")
0043894b        esi_1 = &esi_1[0x2c]
00438951        i = i_4
00438951        i_4 -= 1
00438952        do while (i != 1)
00438954        struct BodNode** esi_2 = &game->salt_hazards.slots[0].bod.list_next
0043895a        int32_t i_5 = 0x28
004389d2        int32_t i_1
0043895f        uint32_t list_flags_2 = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_flags
00438964        if ((0x200 & list_flags_2) != 0)
0043896c        void* ecx_9 = &g_game_base[0x5a8]
00438974        if ((0x200 & list_flags_2) == 0)
0043897b        report_errorf("List remove")
00438987        if ((list_flags_2.b & 0x40) == 0)
00438998        struct BodNode* list_next_1 = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_next
0043899c        if (list_next_1 != 0)
004389a1        list_next_1->list_prev = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_prev
004389a4        struct BodNode* list_prev_1 = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_prev
004389a9        if (list_prev_1 == 0)
004389b4        *(ecx_9 + 4) = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_next
004389ad        list_prev_1->list_next = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_next
004389b7        struct BodNode* edx_11
004389b7        edx_11.b = *(ecx_9 + 8)
004389b7        edx_11:1.b = *(ecx_9 + 9)
004389bd        (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_next = edx_11
004389bf        *(ecx_9 + 8) = (esi_2.w - 0xc).b
004389bf        *(ecx_9 + 9) = (esi_2.w - 0xc):1.b
004389c2        uint32_t list_flags_3 = (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_flags
004389c5        list_flags_3:1.b &= 0xfd
004389c8        (esi_2 - 0x3578cc)->salt_hazards.slots[0].bod.list_flags = list_flags_3
0043898e        report_errorf("List remove NEXTBOD")
004389cb        esi_2 = &esi_2[0x26]
004389d1        i_1 = i_5
004389d1        i_5 -= 1
004389d2        do while (i_1 != 1)
004389d4        struct BodNode** esi_3 = &game->banners.slots[0].bod.bod.list_next
004389da        int32_t i_6 = 2
00438a4f        int32_t i_2
004389df        uint32_t list_flags_4 = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_flags
004389e4        if ((0x200 & list_flags_4) != 0)
004389ec        void* ecx_11 = &g_game_base[0x5a8]
004389f4        if ((0x200 & list_flags_4) == 0)
004389fb        report_errorf("List remove")
00438a07        if ((list_flags_4.b & 0x40) == 0)
00438a18        struct BodNode* list_next_2 = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_next
00438a1c        if (list_next_2 != 0)
00438a21        list_next_2->list_prev = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_prev
00438a24        struct BodNode* list_prev_2 = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_prev
00438a29        if (list_prev_2 == 0)
00438a34        *(ecx_11 + 4) = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_next
00438a2d        list_prev_2->list_next = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_next
00438a37        struct BodNode* edx_16
00438a37        edx_16.b = *(ecx_11 + 8)
00438a37        edx_16:1.b = *(ecx_11 + 9)
00438a3d        (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_next = edx_16
00438a3f        *(ecx_11 + 8) = (esi_3.w - 0xc).b
00438a3f        *(ecx_11 + 9) = (esi_3.w - 0xc):1.b
00438a42        uint32_t list_flags_5 = (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_flags
00438a45        list_flags_5:1.b &= 0xfd
00438a48        (esi_3 - 0x35908c)->banners.slots[0].bod.bod.list_flags = list_flags_5
00438a0e        report_errorf("List remove NEXTBOD")
00438a4b        esi_3 = &esi_3[0x18]
00438a4e        i_2 = i_6
00438a4e        i_6 -= 1
00438a4f        do while (i_2 != 1)
00438a58        if ((game->barrier.bod.bod.list_flags & 0x200) != 0)
00438a66        void* edx_17 = &g_game_base[0x5a8]
00438a6c        uint32_t list_flags_6 = game->barrier.bod.bod.list_flags
00438a71        if ((0x200 & list_flags_6) == 0)
00438a78        report_errorf("List remove")
00438a85        if ((list_flags_6.b & 0x40) == 0)
00438a96        struct BodNode* list_next_3 = game->barrier.bod.bod.list_next
00438a9b        if (list_next_3 != 0)
00438a9d        int16_t list_prev_4 = (game->barrier.bod.bod.list_prev).w
00438aa0        list_next_3->list_prev.b = list_prev_4.b
00438aa0        list_next_3->list_prev:1.b = list_prev_4:1.b
00438aa3        struct BodNode* list_prev_3 = game->barrier.bod.bod.list_prev
00438aa8        if (list_prev_3 == 0)
00438ab5        *(edx_17 + 4) = game->barrier.bod.bod.list_next
00438aad        list_prev_3->list_next = game->barrier.bod.bod.list_next
00438abb        game->barrier.bod.bod.list_next = *(edx_17 + 8)
00438abe        *(edx_17 + 8) = &game->barrier
00438ac1        uint32_t list_flags_7 = game->barrier.bod.bod.list_flags
00438ac4        list_flags_7:1.b &= 0xfd
00438ac7        game->barrier.bod.bod.list_flags = list_flags_7
00438a8c        report_errorf("List remove NEXTBOD")
00438aca        g_game_base
00438adc        kill_border(game->top_score_widget)
00438ae7        g_game_base
00438af4        kill_border(game->bottom_score_widget)
00438b02        if (game->selected_level_record_persistent != 0)
00438b09        *(g_game_base + 0x1bc) = 0x12
00438b13        game->selected_level_record_persistent = 0
00438b1e        if (game->level_mode == 3)
00438b26        *(g_game_base + 0x74658) = 2
00438b35        if (game->level_mode != 0)
00438b35        return
00438b37        g_game_base
00438b49        kill_border(game->lives_icon_widget)
00438b54        g_game_base
00438b61        kill_border(game->lives_text_widget)
00438b66        struct FrontendWidget* (* esi_5)[0x9] = &game->life_stock_widgets
00438b6c        int32_t i_7 = 9
00438b89        int32_t i_3
00438b73        g_game_base
00438b80        kill_border((esi_5 - 0x35bb98)->life_stock_widgets[0])
00438b85        esi_5 = &(*esi_5)[1]
00438b88        i_3 = i_7
00438b88        i_7 -= 1
00438b89        do while (i_3 != 1)
00438b8d        return
