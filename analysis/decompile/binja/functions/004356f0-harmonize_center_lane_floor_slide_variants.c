/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: harmonize_center_lane_floor_slide_variants @ 0x4356f0 */

004356f4        struct Game* game_1 = game
004356f6        int32_t i = 0
004356f8        struct Game* game_2 = game_1
004356ff        int32_t i_1 = 0
00435706        if (game_1->runtime_row_count - 1 s> 0)
00435716        int32_t ecx_2 = 0
00435718        int32_t edx_2 = i & 7
0043571b        int32_t var_c_1 = 0
0043571f        int32_t var_4_1 = edx_2
00435734        while (true)
00435734        if (edx_2 == 3)
00435746        int32_t edx_3 = (ecx_2 + (i << 3)) * 0x15
00435749        int32_t eax_1
00435749        eax_1.b = game_1->_pad_00[(edx_3 << 2) + 0x3bfb08]
00435752        void* esi = &game_1->_pad_00[edx_3 << 2]
00435755        if ((eax_1.b & 0x20) == 0)
00435762        if ((*(esi + 0x3bfda8) & 0x20) == 0 && is_sub_loc_floor(esi + 0x3bfac8) == 1 && (is_sub_loc_slide(esi + 0x3bfd68) == 1 || *(esi + 0x3bfda4) == 0x1e))
00435795        void* eax_4 = data_4df904
004357a6        if (*(esi + 0x3bfaec) == *(eax_4 + 0x447b4))
004357b1        set_bod_object(esi + 0x3bfac8, *(eax_4 + 0x44b34))
004357be        *(esi + 0x3bfb08) |= 0x40
004357c4        eax_4 = data_4df904
004357c9        int32_t j = 0
00435807        while (j s< 0xe0)
004357da        if (*(esi + 0x3bfaec) == *(j + eax_4 + 0x4423c))
004357e6        set_bod_object(esi + 0x3bfac8, *(j + eax_4 + 0x443fc))
004357f3        *(esi + 0x3bfb08) |= 0x40
004357f9        eax_4 = data_4df904
004357fe        j += 0x38
0043581d        if ((*(esi + 0x3bfb08) & 0x20) == 0 && (*(esi + 0x3bfda8) & 0x20) == 0 && is_sub_loc_slide(esi + 0x3bfac8) == 1 && is_sub_loc_floor(esi + 0x3bfd68) == 1)
0043584b        void* eax_11 = data_4df904
0043585c        if (*(esi + 0x3bfaec) == *(eax_11 + 0x44b34))
00435867        set_bod_object(esi + 0x3bfac8, *(eax_11 + 0x447b4))
00435874        *(esi + 0x3bfb08) |= 0x40
0043587a        eax_11 = data_4df904
0043587f        int32_t j_1 = 0
004358bd        while (j_1 s< 0xe0)
00435890        if (*(esi + 0x3bfaec) == *(j_1 + eax_11 + 0x443fc))
0043589c        set_bod_object(esi + 0x3bfac8, *(j_1 + eax_11 + 0x4423c))
004358a9        *(esi + 0x3bfb08) |= 0x40
004358af        eax_11 = data_4df904
004358b4        j_1 += 0x38
004358c7        if (edx_2 == 5)
004358dc        void* esi_1 = &game_1->_pad_00[(ecx_2 + (i << 3)) * 0x54]
004358e6        if ((*(esi_1 + 0x3bfb08) & 0x20) == 0)
004358f3        if ((*(esi_1 + 0x3bf868) & 0x20) == 0 && is_sub_loc_floor(esi_1 + 0x3bfac8) == 1 && (is_sub_loc_slide(esi_1 + 0x3bf828) == 1 || *(esi_1 + 0x3bf864) == 0x20))
00435926        void* eax_21 = data_4df904
00435937        if (*(esi_1 + 0x3bfaec) == *(eax_21 + 0x447b4))
00435942        set_bod_object(esi_1 + 0x3bfac8, *(eax_21 + 0x44b34))
0043594f        *(esi_1 + 0x3bfb08) |= 0x40
00435955        eax_21 = data_4df904
0043595a        int32_t j_2 = 0
00435998        while (j_2 s< 0xe0)
0043596b        if (*(esi_1 + 0x3bfaec) == *(j_2 + eax_21 + 0x4423c))
00435977        set_bod_object(esi_1 + 0x3bfac8, *(j_2 + eax_21 + 0x443fc))
00435984        *(esi_1 + 0x3bfb08) |= 0x40
0043598a        eax_21 = data_4df904
0043598f        j_2 += 0x38
004359ae        if ((*(esi_1 + 0x3bfb08) & 0x20) == 0 && (*(esi_1 + 0x3bf868) & 0x20) == 0 && is_sub_loc_slide(esi_1 + 0x3bfac8) == 1 && is_sub_loc_floor(esi_1 + 0x3bf828) == 1)
004359d8        void* eax_28 = data_4df904
004359e9        if (*(esi_1 + 0x3bfaec) == *(eax_28 + 0x44b34))
004359f4        set_bod_object(esi_1 + 0x3bfac8, *(eax_28 + 0x447b4))
00435a01        *(esi_1 + 0x3bfb08) |= 0x40
00435a07        eax_28 = data_4df904
00435a0c        int32_t j_3 = 0
00435a4a        while (j_3 s< 0xe0)
00435a1d        if (*(esi_1 + 0x3bfaec) == *(j_3 + eax_28 + 0x443fc))
00435a29        set_bod_object(esi_1 + 0x3bfac8, *(j_3 + eax_28 + 0x4423c))
00435a36        *(esi_1 + 0x3bfb08) |= 0x40
00435a3c        eax_28 = data_4df904
00435a41        j_3 += 0x38
00435a50        ecx_2 = var_c_1 + 1
00435a54        var_c_1 = ecx_2
00435a58        if (ecx_2 s>= 8)
00435a58        break
00435725        edx_2 = var_4_1
00435729        game_1 = game_2
0043572d        i = i_1
00435a5e        game_1 = game_2
00435a66        i = i_1 + 1
00435a6a        i_1 = i
00435a71        do while (i s< game_1->runtime_row_count - 1)
00435a7e        return i
