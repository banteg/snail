/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_challenge_setup_screen @ 0x416370 */

00416376        hide_gameplay_scores(*arg1)
0041637d        int32_t eax_1 = *(*arg1 + 0x40)
00416383        if (eax_1 == 0)
004166bf        void* ecx_43 = arg1[1]
004166c2        int32_t eax_49 = *(ecx_43 + 0x1a0)
004166ca        if ((eax_49.b & 0x20) != 0)
004166cc        eax_49.b &= 0xdf
004166ce        *(ecx_43 + 0x1a0) = eax_49
004166d4        void* eax_50 = *arg1
004166da        *(eax_50 + 0x44) += 1
004166dd        void* eax_51 = *arg1
004166ed        load_frontend_level_by_mode_and_index(eax_51 + 0xa874, *(eax_51 + 0x40), *(eax_51 + 0x44))
00416704        sub_44e5b0(arg1[3] + 0x2cc, *arg1 + 0x1b0150)
0041670f        layout_frontend_widget(arg1[3])
00416714        void* ecx_49 = arg1[2]
00416717        int32_t eax_54 = *(ecx_49 + 0x1a0)
0041671f        if ((eax_54.b & 0x20) != 0)
00416721        eax_54.b &= 0xdf
00416723        *(ecx_49 + 0x1a0) = eax_54
00416729        void* eax_55 = *arg1
0041672f        *(eax_55 + 0x44) -= 1
00416732        void* eax_56 = *arg1
00416742        load_frontend_level_by_mode_and_index(eax_56 + 0xa874, *(eax_56 + 0x40), *(eax_56 + 0x44))
00416759        sub_44e5b0(arg1[3] + 0x2cc, *arg1 + 0x1b0150)
00416764        layout_frontend_widget(arg1[3])
00416778        void* eax_60 = arg1[2]
0041677d        int32_t edi_8 = *(eax_60 + 0x1a0)
00416783        int32_t edi_9
00416783        if (*(*arg1 + 0x44) != 0)
00416789        edi_9 = edi_8 & 0xffff7fff
00416785        edi_9 = edi_8 | 0x8000
0041678b        *(eax_60 + 0x1a0) = edi_9
0041679e        void* eax_63 = arg1[1]
004167a1        if (*(*arg1 + 0x44) != data_4df9b8)
004167ab        *(eax_63 + 0x1a0) &= 0xffff7fff
004167a3        *(eax_63 + 0x1a0) |= 0x8000
004167b1        void* ecx_55 = arg1[6]
004167b4        int32_t eax_64 = *(ecx_55 + 0x1a0)
004167bc        if ((eax_64.b & 0x20) != 0)
004167be        eax_64.b &= 0xdf
004167c0        *(ecx_55 + 0x1a0) = eax_64
004167c8        destroy_challenge_setup_screen(arg1)
004167d4        return 3
004167d5        void* ecx_57 = arg1[4]
004167d8        int32_t eax_66 = *(ecx_57 + 0x1a0)
004167e0        if ((eax_66.b & 0x20) != 0)
004167e2        eax_66.b &= 0xdf
004167e4        *(ecx_57 + 0x1a0) = eax_66
004167ec        destroy_challenge_setup_screen(arg1)
004167f8        return 1
0041638a        if (eax_1 == 1)
004165fa        void* ecx_35 = arg1[6]
004165fd        int32_t eax_40 = *(ecx_35 + 0x1a0)
00416605        if ((eax_40.b & 0x20) != 0)
00416607        eax_40.b &= 0xdf
00416609        *(ecx_35 + 0x1a0) = eax_40
00416611        destroy_challenge_setup_screen(arg1)
0041661d        return 3
0041661e        void* ecx_37 = arg1[4]
00416621        int32_t eax_42 = *(ecx_37 + 0x1a0)
00416629        if ((eax_42.b & 0x20) != 0)
0041662b        eax_42.b &= 0xdf
0041662d        *(ecx_37 + 0x1a0) = eax_42
00416635        destroy_challenge_setup_screen(arg1)
00416641        return 1
00416657        int32_t eax_44
00416657        int16_t x87control
00416657        int16_t x87control_1
00416657        eax_44, x87control_1 = __ftol(x87control, fconvert.t(*(arg1[7] + 0x17c)) * fconvert.t(100f) + fconvert.t(0.100000001f))
0041665c        data_4df958 = eax_44
0041667b        data_4df960 = __ftol(x87control_1, fconvert.t(*(arg1[8] + 0x17c)) * fconvert.t(100f) + fconvert.t(0.100000001f))
00416680        void* ecx_40 = arg1[9]
00416683        int32_t eax_46 = *(ecx_40 + 0x1a0)
0041668b        if ((eax_46.b & 0x20) != 0)
00416691        eax_46.b &= 0xdf
00416693        *(ecx_40 + 0x1a0) = eax_46
0041669b        destroy_challenge_setup_screen(arg1)
004166a3        *(*arg1 + 0xff25d0) = 1
004166aa        void* esi_2 = *arg1
004166b7        *(esi_2 + 0xff25d4) = esi_2 + 0xfb3050
004166be        return 1
00416393        if (eax_1 == 4)
00416399        void* ecx_1 = arg1[1]
0041639c        int32_t eax_5 = *(ecx_1 + 0x1a0)
004163a4        if ((eax_5.b & 0x20) != 0)
004163aa        eax_5.b &= 0xdf
004163ac        *(ecx_1 + 0x1a0) = eax_5
004163b2        void* eax_6 = *arg1
004163b8        *(eax_6 + 0x44) += 1
004163bb        void* eax_7 = *arg1
004163cb        load_frontend_level_by_mode_and_index(eax_7 + 0xa874, *(eax_7 + 0x40), *(eax_7 + 0x44))
004163e2        sub_44e5b0(arg1[3] + 0x2cc, *arg1 + 0x1b0150)
004163ed        layout_frontend_widget(arg1[3])
004163f2        void* ecx_9 = *arg1
00416418        format_time_trial_string(*(ecx_9 + 0x44) * 0x1fac0 + ecx_9 + 0x944158)
0041642d        sub_44e5b0(*(*arg1 + 0x35bb8c) + 0x2cc, 0x751478)
00416435        void* ecx_13 = arg1[2]
00416438        int32_t eax_14 = *(ecx_13 + 0x1a0)
00416440        if ((eax_14.b & 0x20) != 0)
00416446        eax_14.b &= 0xdf
00416448        *(ecx_13 + 0x1a0) = eax_14
0041644e        void* eax_15 = *arg1
00416454        *(eax_15 + 0x44) -= 1
00416457        void* eax_16 = *arg1
00416467        load_frontend_level_by_mode_and_index(eax_16 + 0xa874, *(eax_16 + 0x40), *(eax_16 + 0x44))
0041647e        sub_44e5b0(arg1[3] + 0x2cc, *arg1 + 0x1b0150)
00416489        layout_frontend_widget(arg1[3])
0041648e        void* ecx_17 = *arg1
004164b4        format_time_trial_string(*(ecx_17 + 0x44) * 0x1fac0 + ecx_17 + 0x944158)
004164c9        sub_44e5b0(*(*arg1 + 0x35bb8c) + 0x2cc, 0x751478)
004164e0        void* eax_24 = arg1[2]
004164e5        int32_t edi_2 = *(eax_24 + 0x1a0)
004164eb        int32_t edi_3
004164eb        if (*(*arg1 + 0x44) != 0)
004164f1        edi_3 = edi_2 & 0xffff7fff
004164ed        edi_3 = edi_2 | 0x8000
004164f3        *(eax_24 + 0x1a0) = edi_3
00416506        void* eax_27 = arg1[1]
00416509        if (*(*arg1 + 0x44) != data_4df9b8)
00416513        *(eax_27 + 0x1a0) &= 0xffff7fff
0041650b        *(eax_27 + 0x1a0) |= 0x8000
00416519        void* ecx_21 = *arg1
00416538        void* ecx_22 = arg1[9]
0041653e        void* var_c_7
0041653e        if (*(*(ecx_21 + 0x44) * 0x1fac0 + ecx_21 + 0x944150) == 1)
0041654b        unhide_border_init(ecx_22)
00416553        var_c_7 = arg1[9]
00416540        hide_border_init(ecx_22)
00416548        var_c_7 = arg1[4]
00416557        stack_widget_below(arg1[6], var_c_7)
0041655c        void* ecx_25 = arg1[6]
0041655f        int32_t eax_31 = *(ecx_25 + 0x1a0)
00416567        if ((eax_31.b & 0x20) != 0)
00416569        eax_31.b &= 0xdf
0041656b        *(ecx_25 + 0x1a0) = eax_31
00416573        destroy_challenge_setup_screen(arg1)
0041657f        return 3
00416580        void* ecx_27 = arg1[4]
00416583        int32_t eax_33 = *(ecx_27 + 0x1a0)
0041658b        if ((eax_33.b & 0x20) != 0)
0041658d        eax_33.b &= 0xdf
0041658f        *(ecx_27 + 0x1a0) = eax_33
00416597        destroy_challenge_setup_screen(arg1)
004165a3        return 1
004165a4        void* ecx_29 = arg1[9]
004165a7        int32_t eax_35 = *(ecx_29 + 0x1a0)
004165af        if ((eax_35.b & 0x20) != 0)
004165b5        eax_35.b &= 0xdf
004165b7        *(ecx_29 + 0x1a0) = eax_35
004165bf        destroy_challenge_setup_screen(arg1)
004165c7        *(*arg1 + 0xff25d0) = 1
004165ce        void* esi_1 = *arg1
004165ed        *(esi_1 + 0xff25d4) = *(esi_1 + 0x44) * 0x1fac0 + esi_1 + 0x944150
004165f9        return 1
004167fd        return 0
