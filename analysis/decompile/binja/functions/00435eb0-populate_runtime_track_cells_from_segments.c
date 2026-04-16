/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: populate_runtime_track_cells_from_segments @ 0x435eb0 */

00435ec7        int32_t esi
00435ec7        int16_t top
00435ec7        if (arg1[0xff25d0] == 0)
00435ed4        int32_t eax_2 = *(arg1 + 0x40)
00435edf        if (eax_2 == 4 || eax_2 == 7)
00435efc        esi = 0
00435ee1        char* var_58_1 = "Seed"
00435ef3        top = 0
00435ef8        int16_t x87control
00435ef8        esi = __ftol(x87control, random_float_below(32768f))
00435ecf        esi = *(*(arg1 + 0xff25d4) + 0x68)
00435efe        int32_t eax_4 = *(arg1 + 0x40)
00435f08        int32_t eax_8
00435f08        if (eax_4 == 0)
00435f21        eax_8 = *(arg1 + 0x44)
00435f36        initialize_high_score_entry(&arg1[0xfd2b10], esi, eax_8, *(arg1 + 0x30), *(arg1 + 0x4c), 0, eax_8)
00435f0b        if (eax_4 == 1)
00435f19        eax_8 = *(arg1 + 0x44)
00435f36        initialize_high_score_entry(&arg1[0xfd2b10], esi, eax_8, *(arg1 + 0x30), *(arg1 + 0x4c), 1, eax_8)
00435f0f        if (eax_4 == 4)
00435f11        eax_8 = *(arg1 + 0x44)
00435f36        initialize_high_score_entry(&arg1[0xfd2b10], esi, eax_8, *(arg1 + 0x30), *(arg1 + 0x4c), 2, eax_8)
00435f3b        int32_t eax_9 = *(arg1 + 0x1270fc8)
00435f41        *(arg1 + 0xff25dc) = 0
00435f49        if (eax_9 == 3)
00435f51        *(arg1 + 0x1270fc8) = 1
00435f5b        *(arg1 + 0x3bba48) = 0
00435f61        clear_subgoldy_score_buckets(&arg1[0x3bb764])
00435f66        *(arg1 + 0x3bfaa4) = 3
00435f72        zero_timer_counters()
00435f78        *(arg1 + 0x3bba64) = 0
00435f7e        *(arg1 + 0x3bba6c) = 0
00435f84        set_math_random_seed(esi)
00435f9f        int16_t x87control_1 = select_level_track_texture_set(data_4df904 + 0xb24, *(arg1 + 0x1b01e4))
00435fa4        int32_t eax_11 = *(arg1 + 0x40)
00435fb8        int32_t var_24
00435fb8        if (eax_11 == 0 || eax_11 == 7 || eax_11 == 4 || eax_11 == 1)
0043601e        *(arg1 + 0x50) = *(arg1 + 0x1a7cfc)
00436021        int32_t ecx_9 = *(arg1 + 0x1b0138)
0043602b        *(arg1 + 0x54) = ecx_9
0043602e        if (eax_11 == 1)
00436043        eax_11, x87control_1 = __ftol(x87control_1, (fconvert.t(*(arg1 + 0x34)) * fconvert.t(0.649999976f) + fconvert.t(0.349999994f)) * float.t(ecx_9))
00436043        top = 0
00436048        *(arg1 + 0x54) = eax_11
0043604b        eax_11.b = arg1[0x1b013c]
00436053        if (eax_11.b == 0)
00436063        int32_t i = 0
00436065        *(arg1 + 0x54) = *(arg1 + 0x1abf1c) + *(arg1 + 0x1a7cfc)
00436070        if (*(arg1 + 0xa874) s> 0)
00436072        int32_t* ecx_11 = &arg1[0xa87c]
0043607f        i += 1
00436080        *(arg1 + 0x54) += *ecx_11
00436089        ecx_11 = &ecx_11[0x1088]
00436091        do while (i s< *(arg1 + 0xa874))
00436093        var_24 = 0
004360a2        *(arg1 + 0x58) = *(arg1 + 0x54) - *(arg1 + 0x1abf1c)
004360ad        if (*(arg1 + 0x54) s>= 0xc1c)
004360b5        int32_t var_58_5 = 0xc1c
004360ba        void* var_5c_2 = &arg1[0x1b0150]
004360c0        report_errorf("Track (%s) too long, Maximum Length %i")
00435fbc        if (eax_11 == 3)
00435fc8        *(arg1 + 0x50) = *(arg1 + 0x1a7cfc)
00435fd9        int32_t i_6 = 0x10
00435fde        *(arg1 + 0x54) = *(arg1 + 0x1abf1c) + *(arg1 + 0x1a7cfc)
00435ff2        int32_t esi_2
00435ff2        int32_t i_1
00435fea        esi_2 = *(arg1 + 0x54) + *(arg1 + 0xa87c)
00435fec        i_1 = i_6
00435fec        i_6 -= 1
00435fed        *(arg1 + 0x54) = esi_2
00435ff2        do while (i_1 != 1)
00435ffa        var_24 = 0
00436000        *(arg1 + 0x58) = esi_2 - *(arg1 + 0x1abf1c)
0043600d        *(arg1 + 0x58) = esi_2 - *(arg1 + 0x1abf1c)
004360ce        arg1[2] = 0
004360d2        *(arg1 + 4) = 0
004360d5        int32_t var_20 = 0
004360d9        char var_42 = 0
004360de        int32_t var_2c = 0
004360e2        arg1[0x3bbb24] = 0
004360e9        int32_t* var_28 = &arg1[0x3bfb0c]
004360ed        int32_t* edi = &arg1[0x5ccb5c]
004360f3        int32_t var_30 = 0xc80
00436192        char* i_7
00436192        bool cond:3_1
004360fd        int32_t i_8 = 8
00436102        edi[-0x25] = 0
00436108        edi[6] = 0
0043610b        edi[3] = 0
0043610e        edi[0x15] = 0
00436111        edi[4] = 0
00436114        edi[1] = 0
00436117        *edi = 0
00436119        edi[-1] = 0
0043611c        edi[2] = 0
0043611f        edi[0x16] = 0
00436122        edi[0x17] = 0
00436129        int16_t* esi_6 = &var_28[-1]
0043615f        int32_t i_2
0043612e        int32_t ecx_14
0043612e        ecx_14:1.b = (*esi_6):1.b & 0x5f
00436131        *esi_6 = ecx_14
00436133        *(esi_6 - 3) = 0
00436137        *esi_6 = 0
00436146        *esi_6 &= 0xffffafa7
00436148        *esi_6 = 0
00436150        int32_t edx_10
00436150        edx_10.b = (*(esi_6 - 0x3c)).b & 0x7f
00436153        *(esi_6 - 0x3c) = edx_10
00436156        set_color_white()
00436156        top -= 1
0043615b        esi_6 = &esi_6[0x2a]
0043615e        i_2 = i_8
0043615e        i_8 -= 1
0043615f        do while (i_2 != 1)
00436161        int32_t* eax_24 = var_28
00436165        i_7 = 8
0043617d        char* i_3
0043616a        int32_t* esi_7 = eax_24
0043616e        eax_24 = &eax_24[0x15]
00436171        i_3 = i_7
00436171        i_7 -= 1
00436172        *esi_7 = 0
00436174        esi_7[1] = 0
00436177        esi_7[2] = 0
0043617a        esi_7[3] = 0
0043617d        do while (i_3 != 1)
0043617f        var_28 = eax_24
00436187        edi = &edi[0x3d]
0043618d        cond:3_1 = var_30 != 1
0043618e        var_30 -= 1
00436192        do while (cond:3_1)
0043619f        if (arg1[0x1b013c] == 1)
004361a1        i_7 = *(arg1 + 0xa874)
004361a7        int32_t i_4 = 0
004361ab        if (i_7 s> 0)
004361ad        i_7 = &arg1[0xa880]
004361b3        *i_7 = 0
004361bc        i_4 += 1
004361bd        i_7 = &i_7[0x4220]
004361c5        do while (i_4 s< *(arg1 + 0xa874))
004361c7        int32_t* j = *(arg1 + 0x54)
004361ca        int32_t* j_1 = nullptr
004361d4        if (j s> 0)
004361da        int32_t* i_5 = nullptr
004361de        char* i_11 = arg1
004361e4        int32_t* j_2
004361e4        int32_t* j_4
004361e4        if (i_5 != 0)
004361ff        if (i_5 == *(i_11 + 0x58))
00436201        j.b = i_11[0x1b013c]
00436209        if (i_5 != *(i_11 + 0x58) || j.b != 0)
00436221        *(i_11 + 0x48) = 0x3f800000
00436228        j.b = i_11[0x1b013c]
00436230        if (j.b != 1)
004362a4        int32_t eax_29 = var_24
004362a9        var_24 += 1
004362ba        j_4 = &i_11[eax_29 * 0x4220 + 0xa878]
004362c1        j_2 = j_4
00436236        int16_t top_1
00436236        if (*(i_11 + 0x40) != 1)
00436254        top_1 = top - 1
00436254        unimplemented  {fild st0, dword [ebp+0xa874]}
0043625a        char* var_58_7 = "Segtra"
00436238        top_1 = top - 1
00436238        unimplemented  {fld st0, dword [ebp+0x34]}
0043623b        unimplemented  {fmul st0, dword [0x49726c]}
00436241        char* var_58_6 = "Segdif"
00436246        unimplemented  {fadd dword [0x497258]}
0043624c        unimplemented  {fimul st0, dword [ebp+0xa874]}
0043625f        char* i_9 = i_7
00436260        float var_5c_3 = fconvert.s(unimplemented  {fstp dword [esp], st0})
00436260        unimplemented  {fstp dword [esp], st0}
00436263        long double st0_2 = random_float_below(var_5c_3)
00436263        unimplemented  {call 0x44dc90}
0043626b        int32_t eax_27
0043626b        int16_t x87control_2
0043626b        eax_27, x87control_2 = __ftol(x87control_1, st0_2)
00436270        int32_t var_28_1 = eax_27
00436274        unimplemented  {fild st0, dword [esp+0x2c]}
00436278        unimplemented  {fmul st0, dword [ebp+0x48]}
0043627b        int32_t eax_28
0043627b        eax_28, x87control_1 = __ftol(x87control_2, st0_2)
0043627b        top = top_1 + 1
0043628f        j_4 = &i_11[eax_28 * 0x4220 + 0xa878]
00436296        j_2 = j_4
0043629a        j_4[2].b = 1
0043620b        j_4 = &i_11[0x1abf18]
00436211        var_42 = 1
00436216        j_2 = j_4
0043621a        *j_4 = i_5
004361e6        j_4 = &i_11[0x1a7cf8]
004361ec        var_42 = 1
004361f1        j_2 = j_4
004361f5        *j_4 = i_5
004362c7        i_7 = switch_track_mirror(i_11)
004362cc        int32_t eax_30 = j_4[1]
004362cf        *j_4 = i_5
004362d3        if (eax_30 s< 0)
004362da        i_7 = report_errorf("Negative Segment Length")
004362e2        j = *(i_11 + 0x54)
004362e5        char* i_10 = nullptr
004362ef        if (i_5 s< j)
004362f5        j = j_2
004362f9        i_7 = i_10
00436300        if (i_7 s>= j[1])
00436300        break
00436306        int32_t ecx_25 = *(i_11 + 0x40)
0043630c        if (ecx_25 != 2)
0043630e        j = *(i_11 + 0x58)
00436313        int32_t* j_3
00436313        if (ecx_25 == 2 || i_5 s< j)
0043634b        j_3 = j_2
00436326        if (ecx_25 != 0 && ecx_25 != 4 && ecx_25 != 1 && ecx_25 != 7)
0043632b        j_3 = &i_11[0x1b4410]
00436331        if (ecx_25 == 0 || ecx_25 == 4 || ecx_25 == 1 || ecx_25 == 7 || ecx_25 == 3)
00436333        j_3 = &i_11[0x1abf18]
0043633b        j_2 = j_3
0043633f        if (i_5 == j)
00436341        i_10 = nullptr
00436352        if (ecx_25 != 2)
00436354        j = j_3[1]
0043635b        void* esi_8 = *(i_11 + 0x58)
00436366        if (j - i_10 + i_5 s<= esi_8)
004363c5        j_3 = j_2
00436368        j_3 = j_2
004363a0        if (j_3 != &i_11[0x1b4410] && j_3 != &i_11[0x1bc850] && j_3 != &i_11[0x1c0a70] && (ecx_25 == 0 || ecx_25 == 4 || ecx_25 == 1 || ecx_25 == 7 || ecx_25 == 3) && j_3 != &i_11[0x1abf18])
004363b7        j = j - esi_8 - i_10 + i_5
004363bb        void* ecx_29 = *(i_11 + 0x54) + j
004363bd        *(i_11 + 0x58) = esi_8 + j
004363c0        *(i_11 + 0x54) = ecx_29
004363c9        j.b = i_11[2]
004363ce        if (j.b != 0)
004363d6        void* ecx_30 = &i_5[i_5 * 0xf]
004363ea        *(i_11 + (ecx_30 << 2) + 0x5ccac8) |= 0x20
004363f7        void* ecx_34 = i_10 * 7
00436403        void* esi_10 = &j_3[ecx_34 * 2]
00436406        if (((j_3[ecx_34 * 2 + 0x205]).w:1.b & 1) != 0)
0043640e        void* ecx_35 = &i_5[i_5 * 0xf]
0043641f        int32_t ecx_36
0043641f        ecx_36:1.b = (*(i_11 + (ecx_35 << 2) + 0x5ccac8)):1.b | 1
00436422        *(i_11 + (ecx_35 << 2) + 0x5ccac8) = ecx_36
0043642d        if (((*(esi_10 + 0x814)).w:1.b & 0x80) != 0)
00436435        void* ecx_37 = &i_5[i_5 * 0xf]
00436446        int32_t ecx_38
00436446        ecx_38:1.b = (*(i_11 + (ecx_37 << 2) + 0x5ccac8)):1.b | 0x80
00436449        *(i_11 + (ecx_37 << 2) + 0x5ccac8) = ecx_38
00436458        void* ebx_5 = &i_11[&i_5[i_5 * 0xf] << 2]
0043645c        *(ebx_5 + 0x5ccbb4) = j_3
00436462        *(ebx_5 + 0x5ccbb8) = var_2c
0043646f        if ((*(esi_10 + 0x814) & 2) != 0)
0043647b        int32_t eax_48
0043647b        eax_48.b = (*(ebx_5 + 0x5ccac8)).b | 2
0043647d        *(ebx_5 + 0x5ccac8) = eax_48
004364a5        set_bod_object(ebx_5 + 0x5ccacc, *(data_4df904 + *(esi_10 + 0x828) * 0xbc + 0x48e2c))
004364b0        set_matrix_identity(ebx_5 + 0x5ccb04)
004364c1        unimplemented  {fild st0, dword [esp+0x14]}
004364c7        *(ebx_5 + 0x5ccb34) = *(esi_10 + 0x82c)
004364cc        *(ebx_5 + 0x5ccb38) = *(esi_10 + 0x830)
004364d2        *(ebx_5 + 0x5ccb3c) = *(esi_10 + 0x834)
004364d5        unimplemented  {fadd dword [ebx+0x5ccb3c]}
004364db        *(ebx_5 + 0x5ccb3c) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb3c], st0})
004364db        unimplemented  {fstp dword [ebx+0x5ccb3c], st0}
004364e8        if ((*(esi_10 + 0x814) & 8) == 0)
0043651c        *(ebx_5 + 0x5ccb54) = 0
00436522        *(ebx_5 + 0x5ccb50) = 0
00436528        *(ebx_5 + 0x5ccb4c) = 0
004364f6        int32_t eax_53
004364f6        eax_53.b = (*(ebx_5 + 0x5ccac8)).b | 8
004364f8        *(ebx_5 + 0x5ccac8) = eax_53
00436506        *(ebx_5 + 0x5ccb4c) = *(esi_10 + 0x838)
0043650f        *(ebx_5 + 0x5ccb50) = *(esi_10 + 0x83c)
00436515        *(ebx_5 + 0x5ccb54) = *(esi_10 + 0x840)
0043652e        j_3 = j_2
00436539        if ((*(esi_10 + 0x814) & 1) != 0)
00436546        *(ebx_5 + 0x5ccac8) |= 0x4001
0043656b        *(ebx_5 + 0x5ccb64) = j_3[&i_10[0x25] * 0xe]
00436573        *(ebx_5 + 0x5ccb58) = *(esi_10 + 0x81c)
00436578        *(ebx_5 + 0x5ccb5c) = *(esi_10 + 0x820)
0043657e        *(ebx_5 + 0x5ccb60) = *(esi_10 + 0x824)
00436588        if ((*(esi_10 + 0x814) & 8) != 0)
00436590        int32_t eax_61
00436590        eax_61.b = (*(ebx_5 + 0x5ccac8)).b | 8
00436592        *(ebx_5 + 0x5ccac8) = eax_61
0043659e        *(ebx_5 + 0x5ccb68) = *(esi_10 + 0x844)
004365ab        if ((*(esi_10 + 0x814) & 4) != 0)
004365b3        int32_t eax_62
004365b3        eax_62.b = (*(ebx_5 + 0x5ccac8)).b | 4
004365b5        *(ebx_5 + 0x5ccac8) = eax_62
004365c8        if ((0x200 & *(esi_10 + 0x814)) != 0)
004365ca        *(ebx_5 + 0x5ccac8) |= 0x200
004365dd        if ((0x400 & *(esi_10 + 0x814)) != 0)
004365df        *(ebx_5 + 0x5ccac8) |= 0x400
004365f2        if ((0x2000 & *(esi_10 + 0x814)) != 0)
004365f4        *(ebx_5 + 0x5ccac8) |= 0x2000
00436607        if ((0x800 & *(esi_10 + 0x814)) != 0)
00436609        *(ebx_5 + 0x5ccac8) |= 0x800
0043661c        if ((0x1000 & *(esi_10 + 0x814)) != 0)
0043661e        *(ebx_5 + 0x5ccac8) |= 0x1000
00436631        char var_41_1 = 0
00436636        void* var_30_1 = nullptr
00436648        *(i_11 + (&i_5[(i_5 * 3 + 0x12414) * 5 + 0x1857] << 2)) = *(esi_10 + 0x848)
00437143        bool cond:12_1
00436650        void* eax_64
00436650        eax_64.b = arg1[2]
00436655        void* edx_29
00436655        void* ebp_1
00436655        if (eax_64.b == 0)
00436664        edx_29 = var_30_1
00436668        ebp_1 = edx_29
00436657        edx_29 = var_30_1
00436660        ebp_1 = 7 - edx_29
00436682        void* esi_12 = &arg1[(edx_29 + (j_1 << 3)) * 0x54]
0043668b        int32_t eax_68
0043668b        eax_68.b = (*(esi_12 + 0x3bfb08)).b & 0xe0
0043668f        *(esi_12 + 0x3bfb08) = eax_68 ^ (edx_29 & 7)
0043669f        *(esi_12 + 0x3bfb0c) = 0
004366a1        *(esi_12 + 0x3bfb10) = 0
004366a4        *(esi_12 + 0x3bfb14) = 0
004366a7        *(esi_12 + 0x3bfb18) = 0
004366b1        int32_t var_1c
004366b1        if (j_1 s>= *(arg1 + 0x50))
004366b6        var_1c.b = 0
004366bd        if (j_1 s< *(arg1 + 0x50) || j_1 s>= *(arg1 + 0x58))
004366bf        var_1c.b = 1
004366ce        set_bod_object(esi_12 + 0x3bfac8, 0)
004366f2        int32_t* edx_32
004366f2        edx_32.b = *(j_2 + &i_10[ebp_1 << 8] + 0x14)
004366f6        char eax_73 = normalize_segment_glyph_for_track_flags(arg1, edx_32.b, j_1, var_1c.b)
00436704        struct ColorBGRA8* eax_74
00436704        if (sx.d(eax_73) - 0x20 u> 0x5d)
00436ec0        label_436ec0:
00436ec0        int32_t* edx_58
00436ec0        edx_58.b = *(j_2 + &i_10[ebp_1 << 8] + 0x14)
00436ec3        int32_t var_58_36 = j_2[4]
00436ed4        int32_t var_5c_5 = sx.d(normalize_segment_glyph_for_track_flags(arg1, edx_58.b, j_1, 1))
00436ed5        char* var_60_4 = "TrackError:%c in Segment %s\n"
0043670c        int32_t edx_33
0043670c        edx_33.b = *(sx.d(eax_73) + &jump_table_437194[0x14])
00436712        switch (edx_33)
00436719        case 0
00436719        *(esi_12 + 0x3bfb04) = 0
00436726        eax_74.b = (*(esi_12 + 0x3bfacc)).b & 0xdf
00436728        *(esi_12 + 0x3bfacc) = eax_74
0043674d        case 1
0043674d        *(esi_12 + 0x3bfb04) = 0x20
0043675a        eax_74.b = (*(esi_12 + 0x3bfacc)).b & 0xdf
0043675c        *(esi_12 + 0x3bfacc) = eax_74
004367f4        case 2
004367f4        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
004367f9        *(esi_12 + 0x3bfb04) = 0x17
00436806        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436808        *(esi_12 + 0x3bfacc) = eax_74
00436906        case 3
00436906        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x447b4))
0043690b        *(esi_12 + 0x3bfb04) = 0x22
00436918        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
0043691a        *(esi_12 + 0x3bfacc) = eax_74
00436a13        case 4
00436a13        int32_t ecx_91 = var_20 + 1
00436a14        struct ColorBGRA8* ebp_6 = *(esi_12 + 0x3bfacc) & 0xffffffdf
00436a1a        var_20 = ecx_91
00436a1e        *(esi_12 + 0x3bfacc) = ebp_6
00436a26        if (ecx_91 == 0xf)
00436a28        var_20 = 0
00436a30        *(esi_12 + 0x3bfb04) = 0x16
00436a3f        if (ecx_91 != 8)
00436aab        eax_74.b = ebp_6.b & 0xdf
00436aad        *(esi_12 + 0x3bfacc) = eax_74
00436ab3        *(esi_12 + 0x3bfb04) = 0x16
00436a50        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x444dc))
00436a72        *(esi_12 + 0x3bfacc) |= 0x20
00436a9a        store_color4f(&arg1[(var_30_1 + (j_1 << 3) + 0xb6cc) * 0x54], 1f, 1f, 1f, 0.999000013f)
00436a9a        top -= 1
00436a9f        *(esi_12 + 0x3bfb04) = 0x16
00436961        case 5
00436961        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436966        *(esi_12 + 0x3bfb04) = 0x18
00436973        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436975        *(esi_12 + 0x3bfacc) = eax_74
00436933        case 6
00436933        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44124))
00436938        *(esi_12 + 0x3bfb04) = 0x1c
00436945        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436947        *(esi_12 + 0x3bfacc) = eax_74
004369bc        case 7
004369bc        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x447b4))
004369c1        *(esi_12 + 0x3bfb04) = 0x15
004369ce        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004369d0        *(esi_12 + 0x3bfacc) = eax_74
004368aa        case 8
004368aa        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x447b4))
004368af        *(esi_12 + 0x3bfb04) = 1
004368bc        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004368be        *(esi_12 + 0x3bfacc) = eax_74
00436e02        case 9
00436e02        if (*(arg1 + 0x40) == 1)
00436e04        unimplemented  {fild st0, dword [esp+0x24]}
00436e0e        int32_t ecx_123
00436e0e        ecx_123:1.b = (*(ebx_5 + 0x5ccac8)):1.b & 0xbf
00436e11        unimplemented  {fsub st0, dword [0x497210]}
00436e1a        *(ebx_5 + 0x5ccac8) = ecx_123 | 1
00436e20        *(ebx_5 + 0x5ccb64) = 0
00436e2a        unimplemented  {fadd dword [0x497228]}
00436e30        *(ebx_5 + 0x5ccb58) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb58], st0})
00436e30        unimplemented  {fstp dword [ebx+0x5ccb58], st0}
00436e36        unimplemented  {fild st0, dword [esp+0x14]}
00436e40        *(ebx_5 + 0x5ccb5c) = *(esi_12 + 0x3bfadc)
00436e46        unimplemented  {fadd dword [0x497228]}
00436e4c        *(ebx_5 + 0x5ccb60) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb60], st0})
00436e4c        unimplemented  {fstp dword [ebx+0x5ccb60], st0}
00436e52        int32_t ecx_124
00436e52        ecx_124.b = arg1[2]
00436e57        if (ecx_124.b != 0)
00436e59        unimplemented  {fld st0, dword [ebx+0x5ccb58]}
00436e5f        unimplemented  {fmul st0, dword [0x497214]}
00436e65        *(ebx_5 + 0x5ccb58) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb58], st0})
00436e65        unimplemented  {fstp dword [ebx+0x5ccb58], st0}
00436e02        goto label_436e6b
00436e6b        case 0xa
00436e6b        label_436e6b:
00436e72        if ((*(ebx_5 + 0x5ccac8) & 0xc0) != 0)
00436ea4        eax_74.b = (*(esi_12 + 0x3bfacc)).b & 0xdf
00436ea6        *(esi_12 + 0x3bfacc) = eax_74
00436eac        *(esi_12 + 0x3bfb04) = 0
00436e82        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436e87        *(esi_12 + 0x3bfb04) = 0xf
00436e94        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436e96        *(esi_12 + 0x3bfacc) = eax_74
00436c76        case 0xb
00436c76        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44d2c))
00436c7d        *(esi_12 + 0x3bfae4) = 0
00436c83        *(esi_12 + 0x3bfae8) = 0
00436c89        *(esi_12 + 0x3bfb04) = 6
00436c96        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436c98        *(esi_12 + 0x3bfacc) = eax_74
004369ea        case 0xc
004369ea        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x445f4))
004369ef        *(esi_12 + 0x3bfb04) = 0xe
004369fc        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004369fe        *(esi_12 + 0x3bfacc) = eax_74
00436ad0        case 0xd
00436ad0        if (j_1 s<= 0 || *(esi_12 + 0x3bf864) != 3)
00436b21        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44d2c))
00436b26        *(esi_12 + 0x3bfae4) = 0
00436b2c        *(esi_12 + 0x3bfae8) = 0
00436b32        *(esi_12 + 0x3bfb04) = 3
00436b3f        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436b41        *(esi_12 + 0x3bfacc) = eax_74
00436ae1        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44d2c))
00436ae6        *(esi_12 + 0x3bfae4) = 0
00436aec        *(esi_12 + 0x3bfae8) = 0
00436af2        *(esi_12 + 0x3bfb04) = 9
00436aff        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436b01        *(esi_12 + 0x3bfacc) = eax_74
00436b07        *(esi_12 + 0x3bf864) = 0xc
0043676b        case 0xe
0043676b        *(esi_12 + 0x3bfb04) = 0
00436778        int32_t eax_75
00436778        eax_75.b = (*(esi_12 + 0x3bfacc)).b & 0xdf
0043677a        *(esi_12 + 0x3bfacc) = eax_75
00436780        switch_track_mirror(arg1)
0043687d        case 0xf
0043687d        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436882        *(esi_12 + 0x3bfb04) = 0x13
0043688f        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436891        *(esi_12 + 0x3bfacc) = eax_74
00436798        case 0x10
00436798        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
0043679d        *(esi_12 + 0x3bfb04) = 0x11
004367aa        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004367ac        *(esi_12 + 0x3bfacc) = eax_74
0043698f        case 0x11
0043698f        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436994        *(esi_12 + 0x3bfb04) = 0x19
004369a1        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004369a3        *(esi_12 + 0x3bfacc) = eax_74
0043684f        case 0x12
0043684f        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436854        *(esi_12 + 0x3bfb04) = 0x12
00436861        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436863        *(esi_12 + 0x3bfacc) = eax_74
00436ce0        case 0x13
00436ce0        if (eax_73 == 0x50)
00436ce2        *(esi_12 + 0x3bfb04) = 0x1e
00436ced        if (eax_73 == 0x70)
00436cef        *(esi_12 + 0x3bfb04) = 0x1d
00436cfa        int32_t ecx_111 = *(ebx_5 + 0x5ccb68)
00436d05        int32_t eax_98 = ecx_111 << 3
00436d0c        void* ecx_112
00436d0c        if (arg1[2] == 0)
00436d27        ecx_112 = (eax_98 - ecx_111) * 0x30 + arg1 + 0xff2914
00436d16        ecx_112 = (eax_98 - ecx_111) * 0x30 + arg1 + 0xff29bc
00436d2e        eax_74.b = var_41_1
00436d32        *(esi_12 + 0x3bfb00) = ecx_112
00436d43        *(esi_12 + 0x3bfacc) &= 0xffffffdf
00436d49        if (eax_74.b == 0)
00436d57        var_41_1 = 1
00436d60        set_bod_object(esi_12 + 0x3bfac8, *(*(esi_12 + 0x3bfb00) + 0x24))
00436d72        *(esi_12 + 0x3bfacc) |= 0x20
00436d8b        set_bod_object(ebx_5 + 0x5ccb78, *(*(esi_12 + 0x3bfb00) + 0x84))
00436d9c        *(ebx_5 + 0x5ccb7c) |= 0x20
00436da8        *(ebx_5 + 0x5ccb74) = j_2[0x1005]
00436db4        int32_t k = 0
00436dbb        if ((*(esi_12 + 0x3bfb00))->__offset(0x48).d s> 0)
00436dc1        int32_t* ecx_122 = ebx_5 + 0x5ccac8
00436dc7        int32_t eax_105 = *ecx_122
00436dcb        if ((eax_105.b & 0x40) == 0)
00436dd9        eax_105.b |= 0x40
00436ddb        *ecx_122 = eax_105
00436ddd        ecx_122[0x29] = esi_12 + 0x3bfac8
00436dcd        eax_105.b |= 0x80
00436dcf        *ecx_122 = eax_105
00436dd1        ecx_122[0x2a] = esi_12 + 0x3bfac8
00436de9        k += 1
00436dea        ecx_122 = &ecx_122[0x3d]
00436df3        do while (k s< (*(esi_12 + 0x3bfb00))->__offset(0x48).d)
00436733        case 0x14
00436733        *(esi_12 + 0x3bfb04) = 0x23
00436740        eax_74.b = (*(esi_12 + 0x3bfacc)).b & 0xdf
00436742        *(esi_12 + 0x3bfacc) = eax_74
00436cb1        case 0x15
00436cb1        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436cb8        *(esi_12 + 0x3bfae4) = 0
00436cbe        *(esi_12 + 0x3bfae8) = 0
00436cc4        *(esi_12 + 0x3bfb04) = 5
00436cd1        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436cd3        *(esi_12 + 0x3bfacc) = eax_74
004367c6        case 0x16
004367c6        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
004367cb        *(esi_12 + 0x3bfb04) = 0xf
004367d8        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004367da        *(esi_12 + 0x3bfacc) = eax_74
00436821        case 0x17
00436821        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44b34))
00436826        *(esi_12 + 0x3bfb04) = 0x10
00436833        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436835        *(esi_12 + 0x3bfacc) = eax_74
004368d8        case 0x18
004368d8        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x447b4))
004368dd        *(esi_12 + 0x3bfb04) = 0x21
004368ea        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
004368ec        *(esi_12 + 0x3bfacc) = eax_74
00436beb        case 0x19
00436beb        if (j_1 s<= 0 || *(esi_12 + 0x3bf864) != 3)
00436c3c        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436c41        *(esi_12 + 0x3bfae4) = 0
00436c47        *(esi_12 + 0x3bfae8) = 0
00436c4d        *(esi_12 + 0x3bfb04) = 2
00436c5a        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436c5c        *(esi_12 + 0x3bfacc) = eax_74
00436bfb        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44cf4))
00436c00        *(esi_12 + 0x3bfae4) = 0
00436c06        *(esi_12 + 0x3bfae8) = 0
00436c0c        *(esi_12 + 0x3bfb04) = 8
00436c19        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436c1b        *(esi_12 + 0x3bfacc) = eax_74
00436c21        *(esi_12 + 0x3bf864) = 0xb
00436b5d        case 0x1a
00436b5d        if (j_1 s<= 0 || *(esi_12 + 0x3bf864) != 3)
00436baf        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44d64))
00436bb4        *(esi_12 + 0x3bfae4) = 0
00436bba        *(esi_12 + 0x3bfae8) = 0
00436bc0        *(esi_12 + 0x3bfb04) = 4
00436bcd        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436bcf        *(esi_12 + 0x3bfacc) = eax_74
00436b6e        set_bod_object(esi_12 + 0x3bfac8, *(data_4df904 + 0x44d64))
00436b73        *(esi_12 + 0x3bfae4) = 0
00436b79        *(esi_12 + 0x3bfae8) = 0
00436b7f        *(esi_12 + 0x3bfb04) = 0xa
00436b8c        eax_74.b = (*(esi_12 + 0x3bfacc)).b | 0x20
00436b8e        *(esi_12 + 0x3bfacc) = eax_74
00436b94        *(esi_12 + 0x3bf864) = 0xd
00436712        case 0x1b
00436712        goto label_436ec0
00436eea        *(esi_12 + 0x3bfae0) = 0
00436eed        *(esi_12 + 0x3bfadc) = 0
00436ef0        *(esi_12 + 0x3bfad8) = 0
00436ef2        *(ebx_5 + 0x5ccb90) = 0
00436ef8        *(ebx_5 + 0x5ccb8c) = 0
00436efe        *(ebx_5 + 0x5ccb88) = 0
00436f04        eax_74.b = *(esi_12 + 0x3bfb04)
00436f10        float var_28_2
00436f10        if (eax_74.b == 0x1d || eax_74.b == 0x1e)
00436f63        unimplemented  {fild st0, dword [esp+0x14]}
00436f67        *(esi_12 + 0x3bfad8) = 0
00436f69        unimplemented  {fadd dword [0x497228]}
00436f6f        var_28_2 = fconvert.s(unimplemented  {fst dword [esp+0x2c], st0})
00436f73        unimplemented  {fsub st0, dword [0x497228]}
00436f79        *(esi_12 + 0x3bfae0) = fconvert.s(unimplemented  {fst dword [esi+0x3bfae0], st0})
00436f86        if ((data_4df934 & 0x20) == 0)
00436ff9        eax_74.b = (*(ebx_5 + 0x5ccb7c)).b & 0xdf
00436ffb        unimplemented  {fstp st0, st0}
00436ffb        unimplemented  {fstp st0, st0}
00436ffd        *(ebx_5 + 0x5ccb7c) = eax_74
00436f88        *(ebx_5 + 0x5ccb88) = 0
00436f92        *(ebx_5 + 0x5ccb90) = fconvert.s(unimplemented  {fstp dword [ebx+0x5ccb90], st0})
00436f92        unimplemented  {fstp dword [ebx+0x5ccb90], st0}
00436fa4        float var_10[0x4]
00436fa4        float* eax_112 = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
00436fb6        *(ebx_5 + 0x5ccba0) = *eax_112
00436fbb        *(ebx_5 + 0x5ccba4) = eax_112[1]
00436fc1        *(ebx_5 + 0x5ccba8) = eax_112[2]
00436fc7        *(ebx_5 + 0x5ccbac) = eax_112[3]
00436fce        float var_64_3 = *eax_112
00436fd3        int32_t var_60_5 = eax_112[1]
00436fdc        int32_t var_5c_6 = eax_112[2]
00436fdf        int32_t var_58_38 = eax_112[3]
00436fe9        eax_74, x87control_1 = sub_4141d0(*(ebx_5 + 0x5ccb9c))
00436f12        unimplemented  {fild st0, dword [esp+0x24]}
00436f16        unimplemented  {fsub st0, dword [0x497210]}
00436f1c        unimplemented  {fadd dword [0x497228]}
00436f22        *(esi_12 + 0x3bfad8) = fconvert.s(unimplemented  {fstp dword [edi], st0})
00436f22        unimplemented  {fstp dword [edi], st0}
00436f24        *(esi_12 + 0x3bfadc) = 0
00436f2a        eax_74.b = *(esi_12 + 0x3bfb04)
00436f3a        if (eax_74.b == 8 || eax_74.b == 9 || eax_74.b == 0xa)
00436f3c        *(esi_12 + 0x3bfadc) = 0x3f000000
00436f46        unimplemented  {fild st0, dword [esp+0x14]}
00436f4a        unimplemented  {fadd dword [0x497228]}
00436f50        var_28_2 = fconvert.s(unimplemented  {fstp dword [esp+0x2c], st0})
00436f50        unimplemented  {fstp dword [esp+0x2c], st0}
00436f58        *(esi_12 + 0x3bfae0) = var_28_2
00437014        if (j_1 s< 4 && *(arg1 + 0x40) != 2)
0043701f        *(esi_12 + 0x3bfadc) = *(*(arg1 + 0xff58ac) + 0x34)
0043702c        if (*(esi_12 + 0x3bfb04) == 0x1c)
0043702e        unimplemented  {fld st0, dword [esi+0x3bfadc]}
00437034        unimplemented  {fsub st0, dword [0x497548]}
0043703a        *(esi_12 + 0x3bfadc) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfadc], st0})
0043703a        unimplemented  {fstp dword [esi+0x3bfadc], st0}
00437040        eax_74.b = *(esi_12 + 0x3bfb04)
00437080        if (eax_74.b == 1 || eax_74.b == 0x15 || eax_74.b == 0x14 || eax_74.b == 0x21 || eax_74.b == 0x22 || eax_74.b == 0xf || eax_74.b == 0x10 || eax_74.b == 0x17 || eax_74.b == 0x18 || eax_74.b == 0x19 || eax_74.b == 0x1a || eax_74.b == 0x1b || eax_74.b == 0x12 || eax_74.b == 0x13 || eax_74.b == 0x11)
0043708d        void* ecx_134 = j_1 & 0x80000007
00437093        void* var_18_1 = 8 - var_30_1
00437097        unimplemented  {fild st0, dword [esp+0x3c]}
0043709b        unimplemented  {fmul st0, dword [0x497428]}
004370a1        *(esi_12 + 0x3bfae4) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfae4], st0})
004370a1        unimplemented  {fstp dword [esi+0x3bfae4], st0}
004370a7        if (ecx_134 s< 0)
004370ad        ecx_134 = ((ecx_134 - 1) | 0xfffffff8) + 1
004370ae        void* var_18_2 = ecx_134
004370b2        unimplemented  {fild st0, dword [esp+0x3c]}
004370b6        unimplemented  {fmul st0, dword [0x497428]}
004370bc        *(esi_12 + 0x3bfae8) = fconvert.s(unimplemented  {fstp dword [esi+0x3bfae8], st0})
004370bc        unimplemented  {fstp dword [esi+0x3bfae8], st0}
004370c9        if (*(esi_12 + 0x3bfb04) == 0x1f)
004370cb        unimplemented  {fld st0, dword [edi]}
004370cd        unimplemented  {fmul st0, dword [0x497434]}
004370d3        *(esi_12 + 0x3bfad8) = fconvert.s(unimplemented  {fstp dword [edi], st0})
004370d3        unimplemented  {fstp dword [edi], st0}
004370dc        if (*(esi_12 + 0x3bfb04) == 0x16)
004370ea        if (*(arg1 + 0x40) != 3 || ((*(arg1 + 0x4c)).w:1.b & 4) != 0)
004370ec        *(esi_12 + 0x3bfadc) = 0xc0400000
004370fa        *(esi_12 + 0x3bfae0) = var_28_2
00437100        int32_t* ecx_138 = esi_12 + 0x3bfb0c
00437104        int32_t k_2 = 4
00437135        int32_t k_1
00437109        void* eax_117 = *ecx_138
0043710f        if (eax_117 != 0)
00437111        *(eax_117 + 0x18) = 0
00437114        *(eax_117 + 0x14) = 0
00437117        *(eax_117 + 0x10) = 0
0043711e        int32_t* eax_119 = *ecx_138 + 0x10
00437123        *eax_119 = *(esi_12 + 0x3bfad8)
00437128        eax_119[1] = *(esi_12 + 0x3bfadc)
0043712e        eax_119[2] = *(esi_12 + 0x3bfae0)
00437131        ecx_138 = &ecx_138[1]
00437134        k_1 = k_2
00437134        k_2 -= 1
00437135        do while (k_1 != 1)
0043713c        cond:12_1 = var_30_1 + 1 s< 8
0043713f        var_30_1 += 1
00437143        do while (cond:12_1)
0043714d        i_7 = arg1
00437159        j = j_1 + 1
0043715a        i_10 = &i_10[1]
00437160        j_1 = j
00437164        i_5 = j
00437166        i_11 = i_7
00437168        do while (j s< *(i_7 + 0x54))
00437172        if (*(i_11 + 0x40) == 3)
00437174        j.b = var_42
0043717a        if (*(i_11 + 0x40) != 3 || j.b == 0)
0043717c        var_2c += 1
00437183        do while (i_5 s< *(i_11 + 0x54))
00437190        return j
