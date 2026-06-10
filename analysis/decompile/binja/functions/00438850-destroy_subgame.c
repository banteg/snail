/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_subgame @ 0x438850 */

00438854        char* __saved_ebp = "-SubGame::UnInit()\n"
0043886b        *(data_4df904 + 0x4f26c) = 1
00438877        if (game->level_mode == 7)
0043887f        uninit_tutorial()
0043888b        uninit_warning(&game->warning_actor)
00438896        clear_active_landscape_entries(&game->__offset(0xff7c00).d)
004388a1        uninit_times_up(&game->times_up)
004388a8        remove_subgame_bods(game)
004388b7        if (game->subgame_state != 1)
004388bd        int32_t level_mode = game->level_mode
004388c6        if (level_mode == 0 || level_mode == 1)
004388ce        flush_row_event_display(&game->row_event_display)
004388d4        uint8_t* esi_1 = &game->sub_lazer_pool[0]._pad_00[0xc]
004388da        int32_t i_4 = 0x14
00438952        int32_t i
004388df        int32_t eax_3
004388df        eax_3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[4]
004388df        eax_3:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[5]
004388df        eax_3:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[6]
004388df        eax_3:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[7]
004388e4        if ((0x200 & eax_3) != 0)
004388ec        void* ecx_7 = data_4df904 + 0x5a8
004388f4        if ((0x200 & eax_3) == 0)
004388fb        report_errorf("List remove")
00438907        if ((eax_3.b & 0x40) == 0)
00438918        void* eax_4
00438918        eax_4.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xc]
00438918        eax_4:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xd]
00438918        eax_4:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xe]
00438918        eax_4:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xf]
0043891c        if (eax_4 != 0)
0043891e        int32_t edx_4
0043891e        edx_4.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[8]
0043891e        edx_4:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[9]
0043891e        edx_4:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xa]
0043891e        edx_4:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xb]
00438921        *(eax_4 + 8) = edx_4
00438924        void* eax_5
00438924        eax_5.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[8]
00438924        eax_5:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[9]
00438924        eax_5:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xa]
00438924        eax_5:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xb]
00438929        if (eax_5 == 0)
00438932        int32_t eax_6
00438932        eax_6.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xc]
00438932        eax_6:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xd]
00438932        eax_6:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xe]
00438932        eax_6:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xf]
00438934        *(ecx_7 + 4) = eax_6.b
00438934        *(ecx_7 + 5) = eax_6:1.b
00438934        *(ecx_7 + 6) = eax_6:2.b
00438934        *(ecx_7 + 7) = eax_6:3.b
0043892b        int32_t edx_5
0043892b        edx_5.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xc]
0043892b        edx_5:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xd]
0043892b        edx_5:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xe]
0043892b        edx_5:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xf]
0043892d        *(eax_5 + 0xc) = edx_5
00438937        int32_t edx_6
00438937        edx_6.b = *(ecx_7 + 8)
00438937        edx_6:1.b = *(ecx_7 + 9)
00438937        edx_6:2.b = *(ecx_7 + 0xa)
00438937        edx_6:3.b = *(ecx_7 + 0xb)
0043893d        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xc] = edx_6.b
0043893d        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xd] = edx_6:1.b
0043893d        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xe] = edx_6:2.b
0043893d        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[0xf] = edx_6:3.b
0043893f        *(ecx_7 + 8) = (&esi_1[0xfffffff4]).b
0043893f        *(ecx_7 + 9) = (&esi_1[0xfffffff4]):1.b
0043893f        *(ecx_7 + 0xa) = (&esi_1[0xfffffff4]):2.b
0043893f        *(ecx_7 + 0xb) = (&esi_1[0xfffffff4]):3.b
00438942        int32_t eax_8
00438942        eax_8.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[4]
00438942        eax_8:1.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[5]
00438942        eax_8:2.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[6]
00438942        eax_8:3.b = (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[7]
00438945        eax_8:1.b &= 0xfd
00438948        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[4] = eax_8.b
00438948        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[5] = eax_8:1.b
00438948        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[6] = eax_8:2.b
00438948        (esi_1 - 0x356b0c)->sub_lazer_pool[0]._pad_00[7] = eax_8:3.b
0043890e        report_errorf("List remove NEXTBOD")
0043894b        esi_1 = &esi_1[0xb0]
00438951        i = i_4
00438951        i_4 -= 1
00438952        do while (i != 1)
00438954        uint8_t* esi_2 = &game->salt_pool[0]._pad_00[0xc]
0043895a        int32_t i_5 = 0x28
004389d2        int32_t i_1
0043895f        int32_t eax_9
0043895f        eax_9.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[4]
0043895f        eax_9:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[5]
0043895f        eax_9:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[6]
0043895f        eax_9:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[7]
00438964        if ((0x200 & eax_9) != 0)
0043896c        void* ecx_9 = data_4df904 + 0x5a8
00438974        if ((0x200 & eax_9) == 0)
0043897b        report_errorf("List remove")
00438987        if ((eax_9.b & 0x40) == 0)
00438998        void* eax_10
00438998        eax_10.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xc]
00438998        eax_10:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xd]
00438998        eax_10:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xe]
00438998        eax_10:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xf]
0043899c        if (eax_10 != 0)
0043899e        int32_t edx_9
0043899e        edx_9.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[8]
0043899e        edx_9:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[9]
0043899e        edx_9:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xa]
0043899e        edx_9:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xb]
004389a1        *(eax_10 + 8) = edx_9
004389a4        void* eax_11
004389a4        eax_11.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[8]
004389a4        eax_11:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[9]
004389a4        eax_11:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xa]
004389a4        eax_11:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xb]
004389a9        if (eax_11 == 0)
004389b2        int32_t eax_12
004389b2        eax_12.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xc]
004389b2        eax_12:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xd]
004389b2        eax_12:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xe]
004389b2        eax_12:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xf]
004389b4        *(ecx_9 + 4) = eax_12.b
004389b4        *(ecx_9 + 5) = eax_12:1.b
004389b4        *(ecx_9 + 6) = eax_12:2.b
004389b4        *(ecx_9 + 7) = eax_12:3.b
004389ab        int32_t edx_10
004389ab        edx_10.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xc]
004389ab        edx_10:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xd]
004389ab        edx_10:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xe]
004389ab        edx_10:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xf]
004389ad        *(eax_11 + 0xc) = edx_10
004389b7        int32_t edx_11
004389b7        edx_11.b = *(ecx_9 + 8)
004389b7        edx_11:1.b = *(ecx_9 + 9)
004389b7        edx_11:2.b = *(ecx_9 + 0xa)
004389b7        edx_11:3.b = *(ecx_9 + 0xb)
004389bd        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xc] = edx_11.b
004389bd        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xd] = edx_11:1.b
004389bd        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xe] = edx_11:2.b
004389bd        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[0xf] = edx_11:3.b
004389bf        *(ecx_9 + 8) = (&esi_2[0xfffffff4]).b
004389bf        *(ecx_9 + 9) = (&esi_2[0xfffffff4]):1.b
004389bf        *(ecx_9 + 0xa) = (&esi_2[0xfffffff4]):2.b
004389bf        *(ecx_9 + 0xb) = (&esi_2[0xfffffff4]):3.b
004389c2        int32_t eax_14
004389c2        eax_14.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[4]
004389c2        eax_14:1.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[5]
004389c2        eax_14:2.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[6]
004389c2        eax_14:3.b = (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[7]
004389c5        eax_14:1.b &= 0xfd
004389c8        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[4] = eax_14.b
004389c8        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[5] = eax_14:1.b
004389c8        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[6] = eax_14:2.b
004389c8        (esi_2 - 0x3578cc)->salt_pool[0]._pad_00[7] = eax_14:3.b
0043898e        report_errorf("List remove NEXTBOD")
004389cb        esi_2 = &esi_2[0x98]
004389d1        i_1 = i_5
004389d1        i_5 -= 1
004389d2        do while (i_1 != 1)
004389d4        void* __offset(Game, 0x35908c) esi_3 = &game->__offset(0x35908c).d
004389da        int32_t i_6 = 2
00438a4f        int32_t i_2
004389df        int32_t eax_15 = (esi_3 - 0x35908c)->__offset(0x359084).d
004389e4        if ((0x200 & eax_15) != 0)
004389ec        void* ecx_11 = data_4df904 + 0x5a8
004389f4        if ((0x200 & eax_15) == 0)
004389fb        report_errorf("List remove")
00438a07        if ((eax_15.b & 0x40) == 0)
00438a18        void* eax_16 = (esi_3 - 0x35908c)->__offset(0x35908c).d
00438a1c        if (eax_16 != 0)
00438a21        *(eax_16 + 8) = (esi_3 - 0x35908c)->__offset(0x359088).d
00438a24        void* eax_17 = (esi_3 - 0x35908c)->__offset(0x359088).d
00438a29        if (eax_17 == 0)
00438a32        int32_t eax_18 = (esi_3 - 0x35908c)->__offset(0x35908c).d
00438a34        *(ecx_11 + 4) = eax_18.b
00438a34        *(ecx_11 + 5) = eax_18:1.b
00438a34        *(ecx_11 + 6) = eax_18:2.b
00438a34        *(ecx_11 + 7) = eax_18:3.b
00438a2d        *(eax_17 + 0xc) = (esi_3 - 0x35908c)->__offset(0x35908c).d
00438a37        int32_t edx_16
00438a37        edx_16.b = *(ecx_11 + 8)
00438a37        edx_16:1.b = *(ecx_11 + 9)
00438a37        edx_16:2.b = *(ecx_11 + 0xa)
00438a37        edx_16:3.b = *(ecx_11 + 0xb)
00438a3d        (esi_3 - 0x35908c)->__offset(0x35908c).d = edx_16
00438a3f        *(ecx_11 + 8) = (esi_3 - 0xc).b
00438a3f        *(ecx_11 + 9) = (esi_3 - 0xc):1.b
00438a3f        *(ecx_11 + 0xa) = (esi_3 - 0xc):2.b
00438a3f        *(ecx_11 + 0xb) = (esi_3 - 0xc):3.b
00438a45        int32_t eax_20
00438a45        eax_20:1.b = (esi_3 - 0x35908c)->__offset(0x359084).d:1.b & 0xfd
00438a48        (esi_3 - 0x35908c)->__offset(0x359084).d = eax_20
00438a0e        report_errorf("List remove NEXTBOD")
00438a4b        esi_3 += 0x60
00438a4e        i_2 = i_6
00438a4e        i_6 -= 1
00438a4f        do while (i_2 != 1)
00438a58        if ((game->__offset(0xff7bc8).d & 0x200) != 0)
00438a66        void* edx_17 = data_4df904 + 0x5a8
00438a6c        int32_t ecx_13 = game->__offset(0xff7bc8).d
00438a71        if ((0x200 & ecx_13) == 0)
00438a78        report_errorf("List remove")
00438a85        if ((ecx_13.b & 0x40) == 0)
00438a96        void* ecx_14 = game->__offset(0xff7bd0).d
00438a9b        if (ecx_14 != 0)
00438a9d        int32_t esi_4 = game->__offset(0xff7bcc).d
00438aa0        *(ecx_14 + 8) = esi_4.b
00438aa0        *(ecx_14 + 9) = esi_4:1.b
00438aa0        *(ecx_14 + 0xa) = esi_4:2.b
00438aa0        *(ecx_14 + 0xb) = esi_4:3.b
00438aa3        void* ecx_15 = game->__offset(0xff7bcc).d
00438aa8        if (ecx_15 == 0)
00438ab5        *(edx_17 + 4) = game->__offset(0xff7bd0).d
00438aaa        int32_t esi_5 = game->__offset(0xff7bd0).d
00438aad        *(ecx_15 + 0xc) = esi_5.b
00438aad        *(ecx_15 + 0xd) = esi_5:1.b
00438aad        *(ecx_15 + 0xe) = esi_5:2.b
00438aad        *(ecx_15 + 0xf) = esi_5:3.b
00438abb        game->__offset(0xff7bd0).d = *(edx_17 + 8)
00438abe        *(edx_17 + 8) = &game->__offset(0xff7bc4).d
00438ac4        int32_t ecx_18
00438ac4        ecx_18:1.b = game->__offset(0xff7bc8).d:1.b & 0xfd
00438ac7        game->__offset(0xff7bc8).d = ecx_18
00438a8c        report_errorf("List remove NEXTBOD")
00438aca        data_4df904
00438adc        kill_border(game->__offset(0x35bb88).d)
00438ae7        data_4df904
00438af4        kill_border(game->__offset(0x35bb8c).d)
00438b02        if (game->selected_level_record_persistent != 0)
00438b09        *(data_4df904 + 0x1bc) = 0x12
00438b13        game->selected_level_record_persistent = 0
00438b1e        if (game->level_mode == 3)
00438b26        *(data_4df904 + 0x74658) = 2
00438b35        if (game->level_mode != 0)
00438b35        return 
00438b37        data_4df904
00438b49        kill_border(game->__offset(0x35bb90).d)
00438b54        data_4df904
00438b61        kill_border(game->__offset(0x35bb94).d)
00438b66        void* __offset(Game, 0x35bb98) esi_6 = &game->__offset(0x35bb98).d
00438b6c        int32_t i_7 = 9
00438b89        int32_t i_3
00438b73        data_4df904
00438b80        kill_border((esi_6 - 0x35bb98)->__offset(0x35bb98).d)
00438b85        esi_6 += 4
00438b88        i_3 = i_7
00438b88        i_7 -= 1
00438b89        do while (i_3 != 1)
00438b8d        return
