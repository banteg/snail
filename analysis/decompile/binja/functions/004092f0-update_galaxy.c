/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_galaxy @ 0x4092f0 */

00409308        hide_gameplay_scores(*(arg1 + 0x10f70))
00409312        int32_t i = 0
00409316        if (data_4df9b8 s>= 0)
00409318        void* ebx_1 = arg1 + 0x10
0040931d        sub_409bd0(ebx_1)
00409327        i += 1
00409328        ebx_1 += 0x2a0
00409330        do while (i s<= data_4df9b8)
00409351        int32_t var_10
00409351        if (*(arg1 + 8) == 1 && ((*(*(arg1 + 0x10f8c) + 0x1a0)).w:1.b & 0x10) == 0)
0040936f        sub_44dbb0(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f7fbe77)
0040937a        void* edx_1 = *(arg1 + 0x10f8c)
00409389        long double x87_r7_1 = fconvert.t(*(edx_1 + 0x4c))
00409392        void* ecx_8 = *(arg1 + 0x10f80) * 0x2a0 + arg1
00409394        long double temp0_1 = fconvert.t(*(ecx_8 + 0x1c))
00409394        x87_r7_1 - temp0_1
00409397        int32_t eax_5
00409397        eax_5.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
0040939c        float eax_6 = *(ecx_8 + 0x20)
004093b2        float var_60_1
004093b2        float var_5c_2
004093b2        long double x87_r7_5
004093b2        if ((eax_5:1.b & 0x41) != 0)
004093d3        void* var_5c_3 = ecx_8
004093da        var_5c_2 = fconvert.s(fconvert.t(*(edx_1 + 0x54)) + fconvert.t(*(edx_1 + 0x4c)) + fconvert.t(6f))
004093e0        x87_r7_5 = fconvert.t(*(ecx_8 + 0x1c)) - fconvert.t(16f)
004093e6        var_60_1 = eax_6
004093bd        void* var_5c_1 = ecx_8
004093be        var_5c_2 = fconvert.s(fconvert.t(*(edx_1 + 0x4c)) - fconvert.t(6f))
004093c4        x87_r7_5 = fconvert.t(*(ecx_8 + 0x1c)) + fconvert.t(16f)
004093ca        var_60_1 = eax_6
004093e7        void* var_64_1 = ecx_8
004093f2        draw_galaxy_line(0x99, fconvert.s(x87_r7_5), var_60_1, var_5c_2, eax_6, 4f, &var_10)
004093fc        int32_t i_1 = 1
00409400        float var_20
00409400        if (data_4df9b8 s>= 1)
00409412        int32_t ecx_11 = i_1 * 0x2a0
00409419        void* edi = ecx_11 + arg1
0040941f        int32_t edx_3 = *(ecx_11 + arg1 + 0x14) * 0xa0
00409432        var_10 = *(edx_3 + arg1 + 0x109b4)
00409439        int32_t var_c_1 = *(edx_3 + arg1 + 0x109b8)
0040943d        int32_t ecx_13 = *(edx_3 + arg1 + 0x109bc)
00409440        int32_t var_8_1 = ecx_13
00409444        int32_t edx_5 = *(edx_3 + arg1 + 0x109c0)
00409447        var_10 = 0x3f800000
0040944f        int32_t var_4_1 = edx_5
00409453        int32_t var_c_2 = 0x3f800000
0040945b        int32_t var_8_2 = 0x3f800000
00409463        int32_t var_4_2 = 0x3f7d70a4
0040946b        int32_t var_7c_1
0040946b        if (i_1 == 0)
0040946e        int32_t var_54_1 = 0xf
00409470        int32_t var_58_2 = 0x3f800000
00409475        int32_t var_5c_4 = 0x3f800000
0040948c        int32_t* eax_13
0040948c        eax_13, ecx_13 = set_color_rgba(&var_20, 0x3f800000, i_1, i_1, 0x3f7d70a4)
0040949b        int32_t var_6c_2 = 0x1000000
004094a0        int32_t var_70_2 = 0x42000000
004094a5        int32_t var_74_1 = 0x42000000
004094aa        int32_t var_78_1 = ecx_13
004094fc        var_7c_1 = ecx_13
00409505        queue_axis_aligned_textured_quad_uv(0x97, fconvert.s(fconvert.t(*(arg1 + 0x1c)) - fconvert.t(16f)), fconvert.s(fconvert.t(*(arg1 + 0x20)) - fconvert.t(16f)), 32f, 32f, 0x1000000, eax_13, i_1, i_1, 0x3f800000, 0x3f800000, 0xf, i_1)
004094be        if (*(arg1 + 4) != 1 || i_1 s<= *(arg1 + 0x10f80))
004094c5        int32_t var_54_2 = 0xf
004094cd        int32_t var_58_3 = 0x3f800000
004094d2        int32_t var_5c_5 = 0x3f800000
004094e0        int32_t var_6c_3 = 0x1000000
004094e5        int32_t var_70_3 = 0x42000000
004094ea        int32_t var_74_2 = 0x42000000
004094ef        int32_t var_78_3 = ecx_13
004094fc        var_7c_1 = ecx_13
00409505        queue_axis_aligned_textured_quad_uv(0x97, fconvert.s(fconvert.t(*(edi + 0x1c)) - fconvert.t(16f)), fconvert.s(fconvert.t(*(edi + 0x20)) - fconvert.t(16f)), 32f, 32f, 0x1000000, &var_10, 0, 0, 0x3f800000, 0x3f800000, 0xf, 0)
0040950d        long double x87_r7_16 = fconvert.t(*(edi + 0x28))
00409510        long double temp1_1 = fconvert.t(0f)
00409510        x87_r7_16 - temp1_1
00409516        void* eax_12
00409516        eax_12.w = (x87_r7_16 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_16, temp1_1) ? 1 : 0) << 0xa | (x87_r7_16 == temp1_1 ? 1 : 0) << 0xe
0040951b        if ((eax_12:1.b & 0x41) == 0)
0040951d        int32_t ecx_15 = *(edi + 0x28)
00409534        int32_t var_4_3 = ecx_15
00409553        int32_t var_78_4 = ecx_15
00409560        int32_t var_7c_3 = ecx_15
00409569        queue_axis_aligned_textured_quad_uv(0x96, fconvert.s(fconvert.t(*(edi + 0x1c)) - fconvert.t(32f)), fconvert.s(fconvert.t(*(edi + 0x20)) - fconvert.t(32f)), 64f, 64f, 0x1000000, &var_10, 0, 0, 0x3f800000, 0x3f800000, 0xf, 0)
00409576        i_1 += 1
00409579        do while (i_1 s<= data_4df9b8)
00409583        set_color_white()
0040958d        int32_t var_4_4 = 0x3e4ccccd
00409597        int32_t i_2 = 1
00409599        if (data_4df9b8 s> 1)
0040959b        int32_t* edi_1 = arg1 + 0x55c
004095a7        if (i_2 s< *(arg1 + 0x10f80))
004095ad        int32_t var_4_5 = 0x3f4ccccd
004095c1        int32_t var_54_3 = 0x40800000
00409605        draw_galaxy_line(0x9a, edi_1[-0xa8], edi_1[-0xa7], *edi_1, edi_1[1], 4f, &var_10)
004095d5        if (*(arg1 + 4) != 1)
004095db        int32_t var_4_6 = 0x3e4ccccd
004095ef        int32_t var_54_4 = 0x40800000
00409605        draw_galaxy_line(0x9a, edi_1[-0xa8], edi_1[-0xa7], *edi_1, edi_1[1], 4f, &var_10)
0040960f        i_2 += 1
00409610        edi_1 = &edi_1[0xa8]
00409618        do while (i_2 s< data_4df9b8)
0040961e        set_color_white()
00409623        int32_t i_3 = 0
00409625        float* ebp = arg1 + 0x109c4
0040965a        int32_t* var_78_6 = &var_10
0040966d        int32_t* var_7c_5 = &var_10
00409672        queue_axis_aligned_textured_quad_uv(i_3 + 0x8b, fconvert.s(fconvert.t(*ebp) - fconvert.t(128f)), fconvert.s(fconvert.t(ebp[1]) - fconvert.t(128f)), 256f, 256f, 0x1000000, &var_10, 0, 0, 0x3f800000, 0x3f800000, 0xf, 0)
0040967a        i_3 += 1
0040967b        ebp = &ebp[0x28]
00409684        do while (i_3 s< 0xa)
0040968b        float i_5 = 1.40129846e-45f
00409690        float i_6 = nanf
00409693        void* eax_21 = *(data_4df904 + 0x28c)
00409699        float ecx_20 = *(eax_21 + 0x60)
0040969c        float edx_9 = *(eax_21 + 0x64)
004096a6        bool cond:3 = *(arg1 + 8) != 1
004096ac        *(arg1 + 0x10f84) = 0
004096b6        if (not(cond:3))
004096bc        void* ecx_21 = *(arg1 + 0x10f8c)
004096c5        long double x87_r7_26 = fconvert.t(*(ecx_21 + 0x4c)) - fconvert.t(*(ecx_21 + 0x220))
004096cb        long double temp2_1 = fconvert.t(ecx_20)
004096cb        x87_r7_26 - temp2_1
004096cf        int32_t eax_22
004096cf        eax_22.w = (x87_r7_26 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp2_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp2_1 ? 1 : 0) << 0xe
004096d4        if ((eax_22:1.b & 1) != 0)
004096e3        long double x87_r7_29 = fconvert.t(*(ecx_21 + 0x54)) + fconvert.t(*(ecx_21 + 0x220)) + fconvert.t(*(ecx_21 + 0x4c))
004096e6        long double temp3_1 = fconvert.t(ecx_20)
004096e6        x87_r7_29 - temp3_1
004096ea        eax_22.w = (x87_r7_29 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp3_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp3_1 ? 1 : 0) << 0xe
004096ef        if ((eax_22:1.b & 0x41) == 0)
004096f4        long double x87_r7_31 = fconvert.t(*(ecx_21 + 0x50)) - fconvert.t(*(ecx_21 + 0x220))
004096fa        long double temp4_1 = fconvert.t(edx_9)
004096fa        x87_r7_31 - temp4_1
004096fe        eax_22.w = (x87_r7_31 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp4_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp4_1 ? 1 : 0) << 0xe
00409703        if ((eax_22:1.b & 1) != 0)
0040970b        long double x87_r7_34 = fconvert.t(*(ecx_21 + 0x58)) + fconvert.t(*(ecx_21 + 0x50)) + fconvert.t(*(ecx_21 + 0x220))
00409711        long double temp6_1 = fconvert.t(edx_9)
00409711        x87_r7_34 - temp6_1
00409715        eax_22.w = (x87_r7_34 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp6_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp6_1 ? 1 : 0) << 0xe
0040971a        if ((eax_22:1.b & 0x41) == 0)
0040971c        *(arg1 + 0x10f84) = 1
0040972a        int32_t i_4 = 1
0040972c        if (data_4df9b8 s>= 1)
0040972e        int32_t* ecx_23 = arg1 + 0x2cc
0040973a        if (i_4 != *(arg1 + 0x10f80))
00409744        *ecx_23 = 0
0040973c        *ecx_23 = 0x3f800000
00409750        i_4 += 1
00409751        ecx_23 = &ecx_23[0xa8]
00409759        do while (i_4 s<= data_4df9b8)
0040975e        int32_t eax_26
0040975e        if (*(arg1 + 4) == 1)
00409775        *(*(arg1 + 0x10f80) * 0x2a0 + arg1 + 0x2c) = 0x3f800000
0040978a        if (*(arg1 + 0x10f84) == 0)
00409793        struct Vec3 vector
00409793        if (*(arg1 + 8) == 1)
004097ab        int32_t ecx_27 = *(arg1 + 0x10f80) * 0x2a0
004097ba        int32_t edx_11 = *(ecx_27 + arg1 + 0x24)
004097bd        var_20 = fconvert.s(fconvert.t(*(ecx_27 + arg1 + 0x1c)) - fconvert.t(ecx_20))
004097cc        int32_t var_18_1 = edx_11
004097d0        vector.x = var_20
004097d4        vector.z = edx_11
004097e0        vector.y = fconvert.s(fconvert.t(*(ecx_27 + arg1 + 0x20)) - fconvert.t(edx_9))
004097e8        long double st0_1
004097e8        st0_1, eax_26 = normalize_vector(&vector)
004097ed        long double temp5_1 = fconvert.t(17f)
004097ed        st0_1 - temp5_1
004097f3        eax_26.w = (st0_1 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp5_1) ? 1 : 0) << 0xa | (st0_1 == temp5_1 ? 1 : 0) << 0xe
00409802        if ((eax_26:1.b & 1) != 0 && *(arg1 + 0x10f84) == 0)
00409804        i_6 = *(arg1 + 0x10f80)
0040980a        *(arg1 + 0x10f84) = 2
00409823        *(i_6 i* 0x2a0 + arg1 + 0x2c) = 0x3f800000
00409832        if (data_4df9b8 s>= 1)
00409838        int32_t* edi_2 = arg1 + 0x2cc
00409845        int32_t ecx_30 = edi_2[-2]
00409848        int32_t var_18_2 = ecx_30
0040984c        var_20 = fconvert.s(fconvert.t(edi_2[-4]) - fconvert.t(ecx_20))
0040985b        vector.z = ecx_30
00409863        vector.x = var_20
0040986f        vector.y = fconvert.s(fconvert.t(edi_2[-3]) - fconvert.t(edx_9))
00409873        long double st0_2 = normalize_vector(&vector)
00409878        long double temp7_1 = fconvert.t(17f)
00409878        st0_2 - temp7_1
0040988d        if ((((st0_2 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp7_1) ? 1 : 0) << 0xa | (st0_2 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0 && *(arg1 + 0x10f84) == 0)
0040988f        *(arg1 + 0x10f84) = 2
00409899        i_6 = i_5
0040989b        *edi_2 = 0x3f800000
004098af        if (*(arg1 + 8) != 1 || i_5 != *(arg1 + 0x10f80))
004098b9        *edi_2 = 0
004098b1        *edi_2 = 0x3f800000
004098c4        i_5 += 1
004098c5        edi_2 = &edi_2[0xa8]
004098cd        do while (i_5 s<= data_4df9b8)
004098d8        void* edi_3 = data_4df904
004098de        eax_26.b = *(edi_3 + 0x440ec)
004098e6        if (eax_26.b == 0)
004098ec        void* ecx_32 = *(arg1 + 0x10f74)
004098f2        int32_t eax_37 = *(ecx_32 + 0x1a0)
004098fa        if ((eax_37.b & 0x20) != 0)
004098fc        eax_37.b &= 0xdf
004098fe        *(ecx_32 + 0x1a0) = eax_37
00409909        if (*(arg1 + 4) != 1)
00409947        destroy_galaxy(arg1)
00409958        return 3
0040990b        void* eax_39 = data_4df904
0040991a        *(eax_39 + 0x4f3b4) = *(eax_39 + 0x1b8)
00409925        *(data_4df904 + 0x4f3ac) = 0xb
00409937        *(data_4df904 + 0x1b8) = 8
00409944        return 0
00409959        int32_t edx_14 = *(arg1 + 8)
0040995e        int32_t eax_43
0040995e        void* ecx_35
0040995e        if (edx_14 == 1)
00409960        ecx_35 = *(arg1 + 0x10f9c)
00409966        eax_43 = *(ecx_35 + 0x1a0)
0040996e        if (edx_14 == 1 && (eax_43.b & 0x20) != 0)
00409970        eax_43.b &= 0xdf
00409972        *(ecx_35 + 0x1a0) = eax_43
0040997a        destroy_galaxy(arg1)
0040998b        *(*(arg1 + 0x10f70) + 0x44) = *(arg1 + 0x10f80)
0040998e        void* eax_45 = *(arg1 + 0x10f70)
004099a2        load_frontend_level_by_mode_and_index(eax_45 + 0xa874, *(eax_45 + 0x40), *(eax_45 + 0x44))
004099a7        void* esi_1 = *(arg1 + 0x10f70)
004099be        if (*(esi_1 + 0x40) == 0 && *(esi_1 + 0x1270fc8) == 1)
004099d0        return 2
00409a5a        return 1
004099d1        void* ecx_39 = *(arg1 + 0x10fa0)
004099d7        int32_t eax_48 = *(ecx_39 + 0x1a0)
004099df        if ((eax_48.b & 0x20) != 0)
004099e1        eax_48.b &= 0xdf
004099e3        *(ecx_39 + 0x1a0) = eax_48
004099eb        destroy_galaxy(arg1)
004099fc        *(*(arg1 + 0x10f70) + 0x44) = *(arg1 + 0x10f80)
004099ff        void* eax_50 = *(arg1 + 0x10f70)
00409a13        load_frontend_level_by_mode_and_index(eax_50 + 0xa874, *(eax_50 + 0x40), *(eax_50 + 0x44))
00409a1e        *(*(arg1 + 0x10f70) + 0xff25d0) = 1
00409a25        void* eax_51 = *(arg1 + 0x10f70)
00409a4b        *(eax_51 + 0xff25d4) = *(arg1 + 0x10f80) * 0x1fac0 + eax_51 + 0x944150
00409a5a        return 1
00409a69        if (*(edi_3 + 0x24) == 0 && *(arg1 + 4) != 1)
00409a6b        int32_t eax_54 = *(arg1 + 0x10f84)
00409a73        if (eax_54 != 1)
00409a88        if (eax_54 != 2 || (*(*(edi_3 + 0x28c) + 0x3c) & 0x4000) == 0)
00409ad4        if (eax_54 == 0 && (*(*(edi_3 + 0x28c) + 0x3c) & 0x4000) != 0 && edx_14 == 1 && data_4df9b8 s> 1)
00409ad8        close_galaxy_route(arg1)
00409ae4        play_sound_effect(8)
00409a90        if (i_6 != *(arg1 + 0x10f80))
00409a95        if (edx_14 == 1)
00409a99        close_galaxy_route(arg1)
00409aa1        open_galaxy_route(arg1, i_6)
00409ae4        play_sound_effect(8)
00409aaa        if (edx_14 == 0)
00409aaf        open_galaxy_route(arg1, i_6)
00409ae4        play_sound_effect(8)
00409af2        return 0
