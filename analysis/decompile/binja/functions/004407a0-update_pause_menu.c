/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_pause_menu @ 0x4407a0 */

004407a0        void* edx_3 = *arg1
004407a2        int32_t eax = *(edx_3 + 0x1a0)
004407aa        if ((eax.b & 0x20) != 0)
004407ac        eax.b &= 0xdf
004407ae        *(edx_3 + 0x1a0) = eax
004407b9        *(data_4df904 + 0x4f38c) = 0
004407c0        void* eax_2 = data_4df904
004407cb        *(eax_2 + 0x4f388) = *(eax_2 + 0x1b8)
004407d7        *(data_4df904 + 0x1b8) = 6
004407e1        return eax_2
004407e2        void* edx_1 = arg1[2]
004407e5        int32_t eax_3 = *(edx_1 + 0x1a0)
004407ed        if ((eax_3.b & 0x20) != 0)
004407ef        eax_3.b &= 0xdf
004407f1        *(edx_1 + 0x1a0) = eax_3
004407f7        uninit_pause_menu(arg1)
004407fc        void* eax_4 = data_4df904
00440801        *(eax_4 + 0x74654) = 2
00440811        *(data_4df904 + 0x74620) = 1
00440818        return eax_4
00440819        void* ecx_2 = arg1[1]
0044081c        void* eax_5 = *(ecx_2 + 0x1a0)
00440824        if ((eax_5.b & 0x20) != 0)
00440826        eax_5.b &= 0xdf
00440829        *(ecx_2 + 0x1a0) = eax_5
0044082f        void* eax_6 = data_4df904
0044083f        *(eax_6 + 0x4f3b4) = *(eax_6 + 0x1b8)
00440845        void* eax_7 = data_4df904
00440858        if (*(eax_7 + 0x74658) == 7)
0044085a        *(eax_7 + 0x4f3ac) = 7
00440869        if (*(eax_7 + 0x1066be9) != 1)
00440877        *(eax_7 + 0x4f3ac) = 2
0044086b        *(eax_7 + 0x4f3ac) = 3
0044087d        eax_5 = data_4df904
00440882        *(eax_5 + 0x12e55e0) = 2
0044088e        *(data_4df904 + 0x1b8) = 8
00440898        return eax_5
