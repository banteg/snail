/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_click_start @ 0x442290 */

00442290        void* result = data_4df904
00442296        void* esi = arg1
00442298        arg1.b = *(result + 0x74621)
004422a0        if (arg1.b == 0)
004422a6        result.b = *(esi + 0xa8)
004422ac        void* ecx = *(esi + 0x84)
004422b4        if (result.b == 0)
004422bd        unhide_border_init(ecx)
004422b6        hide_border_init(ecx)
004422c2        result = *(esi + 0x80)
004422d1        switch (result)
004422de        case 2
004422de        *(data_4df904 + 0x4f270) = 1
004422e5        result = data_4df904
004422f1        if (*(result + 0x1066bf4) s> 8)
004422f3        *(result + 0x1066bf4) = 8
004422fd        result = data_4df904
00442302        char edx = *(result + 0x1066be8)
0044230a        if (edx == 0)
0044232c        label_44232c:
0044232c        void* ecx_1
0044232c        ecx_1.b = *(esi + 0xa8)
00442346        if (ecx_1.b == 0 && ((*(*(result + 0x28c) + 0x3c)).w:1.b & 0x40) != 0)
00442346        goto label_442358
00442322        if ((*(*(result + 0x1066bec) + *(result + 0x1066bf4) * 6 + 0x74) & 0x20) != 0)
00442358        label_442358:
00442358        *(*(esi + 0x98) + 0x304) = *(result + 0x1066bf4)
0044235e        *(esi + 0x80) = 3
00442368        void* ecx_5 = data_4df904
0044236e        result.b = *(ecx_5 + 0x1066be8)
00442376        if (result.b == 0)
0044237e        int32_t eax_1 = *(ecx_5 + 0x1066bf4) * 3
00442381        *(ecx_5 + (eax_1 << 1) + 0x104719c) |= 0x20
00442390        void* ecx_6 = data_4df904
0044239c        int32_t edx_3 = *(ecx_6 + 0x1066bf4) * 3
0044239f        *(ecx_6 + (edx_3 << 1) + 0x104719c) &= 0xfffe
004423b0        void* eax_3 = data_4df904
004423bb        *(eax_3 + 0x104714c) = *(eax_3 + 0x1066bf4)
004423cd        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004423de        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004423f3        return play_sound_effect(8)
00442326        if (edx == 0)
00442326        goto label_44232c
00442401        case 3
00442401        set_math_random_seed(*(data_4df904 + 0x1047190))
00442406        void* ecx_9 = *(esi + 0x84)
0044240f        *(esi + 0x80) = 4
00442419        *(esi + 0x88) = 0
00442423        *(esi + 0x8c) = 0x3c888889
0044242d        data_4df904
0044243a        kill_border(ecx_9)
0044244e        label_44244e:
0044244e        *(esi + 0x6c) = fconvert.s(fconvert.t(*(esi + 0x88)) * fconvert.t(16f) + fconvert.t(*(esi + 0x6c)))
0044245d        *(esi + 0x88) = fconvert.s(fconvert.t(*(esi + 0x8c)) + fconvert.t(*(esi + 0x88)))
00442468        void* ecx_11 = data_4df904 + 0x5a8
0044246e        int16_t eax_7 = (*(esi + 4)).w
00442474        if ((eax_7:1.b & 2) == 0)
0044247b        report_errorf("List remove")
00442483        *(esi + 0x80) = 0
0044248e        return 0
00442491        if ((eax_7.b & 0x40) != 0)
00442498        report_errorf("List remove NEXTBOD")
004424a0        *(esi + 0x80) = 0
004424ab        return 0
004424ac        void* eax_8 = *(esi + 0xc)
004424b1        if (eax_8 != 0)
004424b6        *(eax_8 + 8) = *(esi + 8)
004424b9        void* eax_9 = *(esi + 8)
004424be        if (eax_9 == 0)
004424cb        *(ecx_11 + 4) = *(esi + 0xc)
004424c3        *(eax_9 + 0xc) = *(esi + 0xc)
004424d1        *(esi + 0xc) = *(ecx_11 + 8)
004424d4        *(ecx_11 + 8) = esi
004424d7        result = *(esi + 4)
004424da        *(esi + 0x80) = 0
004424e4        result:1.b &= 0xfd
004424e7        *(esi + 4) = result
004422d1        case 4
004422d1        goto label_44244e
004424eb        return result
