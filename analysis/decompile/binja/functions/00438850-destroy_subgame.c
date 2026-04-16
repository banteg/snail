/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_subgame @ 0x438850 */

00438854        char* __saved_ebp = "-SubGame::UnInit()\n"
0043886b        *(data_4df904 + 0x4f26c) = 1
00438877        if (*(arg1 + 0x40) == 7)
0043887f        uninit_tutorial()
0043888b        uninit_warning(arg1 + 0x3bbb58)
00438896        clear_active_landscape_entries(arg1 + 0xff7c00)
004388a1        uninit_times_up(arg1 + 0x1272828)
004388a8        remove_subgame_bods(arg1)
004388b7        if (*(arg1 + 0x3c) != 1)
004388bd        int32_t eax_3 = *(arg1 + 0x40)
004388c6        if (eax_3 == 0 || eax_3 == 1)
004388ce        flush_row_event_display(arg1 + 0x12727d8)
004388d4        int32_t* esi_1 = arg1 + 0x356b0c
004388da        int32_t i_4 = 0x14
00438952        int32_t i
004388df        int32_t eax_4 = esi_1[-2]
004388e4        if ((0x200 & eax_4) != 0)
004388ec        void* ecx_7 = data_4df904 + 0x5a8
004388f4        if ((0x200 & eax_4) == 0)
004388fb        report_errorf("List remove")
00438907        if ((eax_4.b & 0x40) == 0)
00438918        void* eax_5 = *esi_1
0043891c        if (eax_5 != 0)
00438921        *(eax_5 + 8) = esi_1[-1]
00438924        void* eax_6 = esi_1[-1]
00438929        if (eax_6 == 0)
00438934        *(ecx_7 + 4) = *esi_1
0043892d        *(eax_6 + 0xc) = *esi_1
0043893d        *esi_1 = *(ecx_7 + 8)
0043893f        *(ecx_7 + 8) = &esi_1[-3]
00438945        int32_t eax_9
00438945        eax_9:1.b = esi_1[-2]:1.b & 0xfd
00438948        esi_1[-2] = eax_9
0043890e        report_errorf("List remove NEXTBOD")
0043894b        esi_1 = &esi_1[0x2c]
00438951        i = i_4
00438951        i_4 -= 1
00438952        do while (i != 1)
00438954        int32_t* esi_2 = arg1 + 0x3578cc
0043895a        int32_t i_5 = 0x28
004389d2        int32_t i_1
0043895f        int32_t eax_10 = esi_2[-2]
00438964        if ((0x200 & eax_10) != 0)
0043896c        void* ecx_9 = data_4df904 + 0x5a8
00438974        if ((0x200 & eax_10) == 0)
0043897b        report_errorf("List remove")
00438987        if ((eax_10.b & 0x40) == 0)
00438998        void* eax_11 = *esi_2
0043899c        if (eax_11 != 0)
004389a1        *(eax_11 + 8) = esi_2[-1]
004389a4        void* eax_12 = esi_2[-1]
004389a9        if (eax_12 == 0)
004389b4        *(ecx_9 + 4) = *esi_2
004389ad        *(eax_12 + 0xc) = *esi_2
004389bd        *esi_2 = *(ecx_9 + 8)
004389bf        *(ecx_9 + 8) = &esi_2[-3]
004389c5        int32_t eax_15
004389c5        eax_15:1.b = esi_2[-2]:1.b & 0xfd
004389c8        esi_2[-2] = eax_15
0043898e        report_errorf("List remove NEXTBOD")
004389cb        esi_2 = &esi_2[0x26]
004389d1        i_1 = i_5
004389d1        i_5 -= 1
004389d2        do while (i_1 != 1)
004389d4        int32_t* esi_3 = arg1 + 0x35908c
004389da        int32_t i_6 = 2
00438a4f        int32_t i_2
004389df        int32_t eax_16 = esi_3[-2]
004389e4        if ((0x200 & eax_16) != 0)
004389ec        void* ecx_11 = data_4df904 + 0x5a8
004389f4        if ((0x200 & eax_16) == 0)
004389fb        report_errorf("List remove")
00438a07        if ((eax_16.b & 0x40) == 0)
00438a18        void* eax_17 = *esi_3
00438a1c        if (eax_17 != 0)
00438a21        *(eax_17 + 8) = esi_3[-1]
00438a24        void* eax_18 = esi_3[-1]
00438a29        if (eax_18 == 0)
00438a34        *(ecx_11 + 4) = *esi_3
00438a2d        *(eax_18 + 0xc) = *esi_3
00438a3d        *esi_3 = *(ecx_11 + 8)
00438a3f        *(ecx_11 + 8) = &esi_3[-3]
00438a45        int32_t eax_21
00438a45        eax_21:1.b = esi_3[-2]:1.b & 0xfd
00438a48        esi_3[-2] = eax_21
00438a0e        report_errorf("List remove NEXTBOD")
00438a4b        esi_3 = &esi_3[0x18]
00438a4e        i_2 = i_6
00438a4e        i_6 -= 1
00438a4f        do while (i_2 != 1)
00438a58        if ((*(arg1 + 0xff7bc8) & 0x200) != 0)
00438a66        void* edx_10 = data_4df904 + 0x5a8
00438a6c        int32_t ecx_13 = *(arg1 + 0xff7bc8)
00438a71        if ((0x200 & ecx_13) == 0)
00438a78        report_errorf("List remove")
00438a85        if ((ecx_13.b & 0x40) == 0)
00438a96        void* ecx_14 = *(arg1 + 0xff7bd0)
00438a9b        if (ecx_14 != 0)
00438aa0        *(ecx_14 + 8) = *(arg1 + 0xff7bcc)
00438aa3        void* ecx_15 = *(arg1 + 0xff7bcc)
00438aa8        if (ecx_15 == 0)
00438ab5        *(edx_10 + 4) = *(arg1 + 0xff7bd0)
00438aad        *(ecx_15 + 0xc) = *(arg1 + 0xff7bd0)
00438abb        *(arg1 + 0xff7bd0) = *(edx_10 + 8)
00438abe        *(edx_10 + 8) = arg1 + 0xff7bc4
00438ac4        int32_t ecx_18
00438ac4        ecx_18:1.b = (*(arg1 + 0xff7bc8)):1.b & 0xfd
00438ac7        *(arg1 + 0xff7bc8) = ecx_18
00438a8c        report_errorf("List remove NEXTBOD")
00438aca        data_4df904
00438adc        kill_border(*(arg1 + 0x35bb88))
00438ae7        data_4df904
00438af4        kill_border(*(arg1 + 0x35bb8c))
00438b02        if (*(arg1 + 0xff25d1) != 0)
00438b09        *(data_4df904 + 0x1bc) = 0x12
00438b13        *(arg1 + 0xff25d1) = 0
00438b1e        if (*(arg1 + 0x40) == 3)
00438b26        *(data_4df904 + 0x74658) = 2
00438b30        int32_t result = *(arg1 + 0x40)
00438b35        if (result == 0)
00438b37        data_4df904
00438b49        kill_border(*(arg1 + 0x35bb90))
00438b54        data_4df904
00438b61        kill_border(*(arg1 + 0x35bb94))
00438b66        int32_t* esi_6 = arg1 + 0x35bb98
00438b6c        int32_t i_7 = 9
00438b89        int32_t i_3
00438b73        data_4df904
00438b80        result = kill_border(*esi_6)
00438b85        esi_6 = &esi_6[1]
00438b88        i_3 = i_7
00438b88        i_7 -= 1
00438b89        do while (i_3 != 1)
00438b8d        return result
