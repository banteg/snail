/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: create_golb @ 0x415280 */

0041528f        arg1[0x6f].b = 0
00415295        *(arg1 + 0x1bd) = 0
0041529e        if ((arg1[1] & 0x200) == 0)
004152b4        int32_t* eax_2 = data_4df904 + 0x5ac
004152b9        void* ecx = *eax_2
004152bd        if (ecx != 0)
004152cb        *(ecx + 8) = arg1
004152ce        void* ecx_2 = *eax_2
004152d3        *(*(ecx_2 + 8) + 0xc) = ecx_2
004152d8        void* ecx_4 = *(*eax_2 + 8)
004152db        *eax_2 = ecx_4
004152dd        *(ecx_4 + 8) = 0
004152bf        *eax_2 = arg1
004152c1        arg1[2] = 0
004152c6        *(*eax_2 + 0xc) = 0
004152e0        arg1[1] |= 0x200
004152a5        report_errorf("List ADD")
004152e7        arg1[0x9e] = arg2
004152ed        char eax_4 = (*(arg2 + 0x338)).b
004152f5        if ((eax_4 & 7) != 0)
004152f7        arg1[0x70] = 0
00415301        if ((eax_4 & 0x18) != 0)
00415303        arg1[0x70] = 1
00415311        if ((eax_4 & 0x60) != 0)
00415313        arg1[0x70] = 2
00415324        set_matrix_identity(&arg1[0x9f])
00415329        void* eax_5 = arg1[0x9e]
00415335        arg1[0x91] = 1
00415347        arg1[0x7d] = *(eax_5 + 0x68)
0041534c        arg1[0x7e] = *(eax_5 + 0x6c)
00415352        arg1[0x7f] = *(eax_5 + 0x70)
00415367        float var_c = fconvert.s(fconvert.t(*(eax_5 + 0x5c)) * fconvert.t(0.5f))
00415374        float var_8 = fconvert.s(fconvert.t(*(eax_5 + 0x60)) * fconvert.t(0.5f))
0041537a        arg1[0x7d] = fconvert.s(fconvert.t(*(eax_5 + 0x58)) * fconvert.t(0.5f) + fconvert.t(arg1[0x7d]))
00415383        arg1[0x7e] = fconvert.s(fconvert.t(var_c) + fconvert.t(arg1[0x7e]))
0041538d        arg1[0x7f] = fconvert.s(fconvert.t(var_8) + fconvert.t(arg1[0x7f]))
00415390        void* ecx_7 = arg1[0x9e]
00415396        char eax_6 = (*(ecx_7 + 0x338)).b
0041539e        int32_t var_10
0041539e        int32_t* eax_11
0041539e        long double x87_r7_16
0041539e        if ((eax_6 & 5) != 0)
00415606        int32_t* edx_15
00415606        if (arg3 != 3)
00415613        if (arg3 == 2)
00415615        edx_15 = ecx_7 + 0x414c
0041561b        goto label_41562c
00415620        if (arg3 == 1)
00415622        edx_15 = ecx_7 + 0x4164
00415622        goto label_41562c
00415608        edx_15 = ecx_7 + 0x4134
0041562c        label_41562c:
0041562c        arg1[0x7d] = *edx_15
00415631        arg1[0x7e] = edx_15[1]
00415637        arg1[0x7f] = edx_15[2]
00415643        if ((*(ecx_7 + 0x338) & 4) == 0)
00415724        long double x87_r7_34 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
0041572a        var_10 = 0
00415736        eax_11 = &arg1[0x93]
00415748        *eax_11 = var_10
00415752        eax_11[1] = 0
00415755        eax_11[2] = fconvert.s(x87_r7_34)
0041564c        if (arg3 == 3)
00415654        long double x87_r7_25 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
0041565a        var_10 = 0x3dcccccd
00415678        float var_8_6 = fconvert.s(x87_r7_25)
0041567e        long double x87_r7_27 = fconvert.t(arg1[0x7d]) + fconvert.t(0.5f)
00415684        arg1[0x93] = var_10
0041568a        arg1[0x94] = 0
0041568d        arg1[0x7d] = fconvert.s(x87_r7_27)
0041568f        arg1[0x95] = var_8_6
0041569a        if (arg3 != 2)
004156e8        long double x87_r7_32 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
004156ee        var_10 = 0
0041570c        arg1[0x93] = var_10
0041570e        float var_8_8 = fconvert.s(x87_r7_32)
00415716        arg1[0x94] = 0
00415719        arg1[0x95] = var_8_8
004156a2        long double x87_r7_29 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
004156a8        var_10 = 0xbdcccccd
004156c6        arg1[0x93] = var_10
004156c8        float var_8_7 = fconvert.s(x87_r7_29)
004156d0        arg1[0x94] = 0
004156d3        x87_r7_16 = fconvert.t(arg1[0x7d])
004156d5        arg1[0x95] = var_8_7
004156de        arg1[0x7d] = fconvert.s(x87_r7_16 - fconvert.t(0.5f))
004153a6        if ((eax_6 & 2) != 0)
004153b3        if (arg3 == 2)
004153bf        arg1[0x7d] = *(ecx_7 + 0x4134)
004153c4        arg1[0x7e] = *(ecx_7 + 0x4138)
004153ca        arg1[0x7f] = *(ecx_7 + 0x413c)
004153fc        arg1[0x7d] = fconvert.s(fconvert.t(arg1[0x7d]) + fconvert.t(0.5f))
004153da        if (arg3 == 1)
004153e6        arg1[0x7d] = *(ecx_7 + 0x414c)
004153eb        arg1[0x7e] = *(ecx_7 + 0x4150)
004153f1        arg1[0x7f] = *(ecx_7 + 0x4154)
004153fc        arg1[0x7d] = fconvert.s(fconvert.t(arg1[0x7d]) - fconvert.t(0.5f))
00415404        long double x87_r7_11 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
0041540a        var_10 = 0
00415416        eax_11 = &arg1[0x93]
00415428        *eax_11 = var_10
00415432        eax_11[1] = 0
00415755        eax_11[2] = fconvert.s(x87_r7_11)
0041543c        if ((eax_6 & 0x18) != 0)
0041554b        if (arg3 != 2)
0041558b        arg1[0x7d] = *(ecx_7 + 0x4188)
00415590        arg1[0x7e] = *(ecx_7 + 0x418c)
00415596        arg1[0x7f] = *(ecx_7 + 0x4190)
00415599        long double x87_r7_21 = fconvert.t(*(ecx_7 + 0x60))
0041559c        long double temp1_1 = fconvert.t(0f)
0041559c        x87_r7_21 - temp1_1
004155a2        int32_t eax_21
004155a2        eax_21.w = (x87_r7_21 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp1_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp1_1 ? 1 : 0) << 0xe
004155a7        if ((eax_21:1.b & 0x41) != 0)
004155b5        arg3 = 0
004155af        arg3 = ecx_7 + 0x4184
00415557        arg1[0x7d] = *(ecx_7 + 0x417c)
0041555c        arg1[0x7e] = *(ecx_7 + 0x4180)
00415562        arg1[0x7f] = *(ecx_7 + 0x4184)
00415565        long double x87_r7_20 = fconvert.t(*(ecx_7 + 0x60))
00415568        long double temp2_1 = fconvert.t(0f)
00415568        x87_r7_20 - temp2_1
0041556e        int32_t eax_19
0041556e        eax_19.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe
00415573        if ((eax_19:1.b & 0x41) != 0)
004155b5        arg3 = 0
0041557b        arg3 = ecx_7 + 0x4184
004155bf        long double x87_r7_23 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
004155c5        var_10 = 0
004155e3        arg1[0x6f].b = 1
004155ea        arg1[0x93] = var_10
004155ec        float var_8_5 = fconvert.s(x87_r7_23)
004155f4        arg1[0x94] = 0
004155f7        arg1[0x95] = var_8_5
00415444        if ((eax_6 & 0x60) != 0)
004154f3        var_10 = 0
004154fb        int32_t var_c_1 = 0
00415505        arg1[0x7d] = *(ecx_7 + 0x41ac)
0041550a        arg1[0x7e] = *(ecx_7 + 0x41b0)
00415510        arg1[0x7f] = *(ecx_7 + 0x41b4)
0041551d        long double x87_r7_19 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(0.600000024f)
0041552d        arg1[0x93] = var_10
00415533        float var_8_4 = fconvert.s(x87_r7_19)
0041553b        arg1[0x94] = var_c_1
0041553e        arg1[0x95] = var_8_4
0041544c        if ((eax_6 & 0x29) != 0)
00415454        long double x87_r7_13 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
0041545a        var_10 = 0
00415478        arg1[0x93] = var_10
0041547a        float var_8_2 = fconvert.s(x87_r7_13)
00415482        arg1[0x94] = 0
00415485        arg1[0x95] = var_8_2
0041548f        if ((eax_6 & 0x52) != 0)
0041549b        long double x87_r7_15 = fconvert.t(*(ecx_7 + 0x418)) + fconvert.t(1f)
004154a1        var_10 = 0
004154bf        arg1[0x93] = var_10
004154c1        float var_8_3 = fconvert.s(x87_r7_15)
004154c9        arg1[0x94] = 0
004154d0        x87_r7_16 = fconvert.t(arg1[0x7d])
004154d5        arg1[0x95] = var_8_3
004154d8        if (arg3 != 2)
004156de        arg1[0x7d] = fconvert.s(x87_r7_16 - fconvert.t(0.5f))
004154e4        arg1[0x7d] = fconvert.s(x87_r7_16 + fconvert.t(0.5f))
0041575f        if (arg1[0x70] == 1)
00415761        long double x87_r7_35 = fconvert.t(arg1[0x93])
00415769        arg1[0x93] = fconvert.s(x87_r7_35 + x87_r7_35)
0041576f        long double x87_r7_37 = fconvert.t(arg1[0x94])
00415777        arg1[0x94] = fconvert.s(x87_r7_37 + x87_r7_37)
0041577d        long double x87_r7_39 = fconvert.t(arg1[0x95])
00415785        arg1[0x95] = fconvert.s(x87_r7_39 + x87_r7_39)
00415792        if (arg1[0x70] == 2)
004157a0        arg1[0x93] = fconvert.s(fconvert.t(arg1[0x93]) * fconvert.t(0.800000012f))
004157b2        arg1[0x94] = fconvert.s(fconvert.t(arg1[0x94]) * fconvert.t(0.800000012f))
004157c4        arg1[0x95] = fconvert.s(fconvert.t(arg1[0x95]) * fconvert.t(0.800000012f))
004157d8        arg1[0x96] = arg1[0x93]
004157dd        arg1[0x97] = arg1[0x94]
004157e3        arg1[0x98] = arg1[0x95]
004157e6        int32_t eax_29 = arg1[0x70]
004157ee        int32_t* eax_32
004157ee        if (eax_29 == 0)
004159b6        void* ecx_32 = arg1[0x9c]
004159bc        void* edx_34 = arg1[0x9e]
004159c2        arg1[0x9a] = 0
004159df        arg1[0x9b] = fconvert.s(fconvert.t(*(ecx_32 + 0x38)) * fconvert.t(0.0416666679f))
004159ec        int32_t* eax_44 = allocate_sprite(&data_790f30, *(edx_34 + 0x380), 0x82, 0xffffffff, 0xffffffff)
004159f1        arg1[0x92] = eax_44
00415a05        eax_44[1] |= 0x800
00415a18        *(arg1[0x92] + 0x68) = 0
00415a2a        *(arg1[0x92] + 0x6c) = 0
00415a33        *(arg1[0x92] + 0x78) = 0
00415a36        int32_t* eax_46 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00415a43        int32_t* ecx_36 = arg1[0x92] + 0x2c
00415a46        *ecx_36 = *eax_46
00415a4b        ecx_36[1] = eax_46[1]
00415a51        ecx_36[2] = eax_46[2]
00415a57        ecx_36[3] = eax_46[3]
00415a65        *(arg1[0x92] + 0x60) = 0x3efae148
00415a70        *(arg1[0x92] + 0x64) = 0x3efae148
00415a7b        float* eax_49 = arg1[0x92] + 0x48
00415a7e        *eax_49 = arg1[0x7d]
00415a83        eax_49[1] = arg1[0x7e]
00415a89        eax_49[2] = arg1[0x7f]
00415aab        *(arg1[0x92] + 0x7c) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f))
00415ac7        *(arg1[0x92] + 0x80) = fconvert.s(fconvert.t(arg1[0x9c][0xe]) * fconvert.t(0.58177644f))
00415acd        arg1[0x9d] = arg4
004157f5        if (eax_29 == 1)
00415900        void* ecx_26 = arg1[0x9c]
00415906        arg1[0x9a] = 0
00415915        long double x87_r7_50 = fconvert.t(*(ecx_26 + 0x38)) * fconvert.t(0.0416666679f)
0041591b        arg1[0x45] = arg1
00415926        arg1[0x9b] = fconvert.s(x87_r7_50)
00415932        void* eax_39 = data_4df904 + 0x3ca33c
0041593d        if ((0x200 & arg1[0x21]) == 0)
0041594e        arg1[0x22] = eax_39
00415954        arg1[0x23] = *(eax_39 + 0xc)
00415957        *(eax_39 + 0xc) = &arg1[0x20]
0041595a        void* eax_40 = arg1[0x23]
0041595f        if (eax_40 != 0)
00415961        *(eax_40 + 8) = &arg1[0x20]
00415964        arg1[0x21] |= 0x200
00415944        report_errorf("List ADDafter")
0041596e        reset_vapour(&arg1[0x20], arg3)
0041598d        sub_44dbb0(&arg1[0x2a], 0x3f800000, 0x3f800000, 0x3f800000, 0x3f7d70a4)
0041599c        arg1[0x9d] = arg4
004159a5        add_vapour_point(&arg1[0x20], &arg1[0x71])
004159af        (*arg1[0x20])()
004157fc        if (eax_29 == 2)
00415802        void* ecx_20 = arg1[0x9c]
00415808        arg1[0x9a] = 0
00415811        long double x87_r7_48 = fconvert.t(*(ecx_20 + 0x38)) * fconvert.t(0.0277777761f)
0041581d        arg1[0x6a] = arg1
00415823        arg1[0x6d] = 0
00415829        __builtin_strncpy(&arg1[0x6e], "PwV>", 4)
00415833        arg1[0x66] = 0
00415839        arg1[0x9b] = fconvert.s(x87_r7_48)
00415845        if (((arg1[0x47]).w:1.b & 2) == 0)
00415856        void* edx_21 = data_4df904
00415862        void* edx_22 = *(edx_21 + 0x5ac)
0041586a        if (edx_22 != 0)
00415878        *(edx_22 + 8) = &arg1[0x46]
0041587b        void* edx_23 = *(edx_21 + 0x5ac)
00415880        *(*(edx_23 + 8) + 0xc) = edx_23
00415885        void* edx_25 = *(*(edx_21 + 0x5ac) + 8)
00415888        *(edx_21 + 0x5ac) = edx_25
0041588a        *(edx_25 + 8) = 0
0041586c        *(edx_21 + 0x5ac) = &arg1[0x46]
0041586e        arg1[0x48] = 0
00415873        *(*(edx_21 + 0x5ac) + 0xc) = 0
00415890        int32_t eax_36
00415890        eax_36:1.b = arg1[0x47]:1.b | 2
00415893        arg1[0x47] = eax_36
0041584c        report_errorf("List ADD")
004158a1        int32_t* ecx_23 = arg1[0x9c] + 0x1270fd4
004158a7        arg1[0x9d] = arg4
004158ad        eax_32 = search_path_for_golb(ecx_23, &arg1[0x7d])
004158b4        if (eax_32 != 0)
004158ba        void* ecx_24 = eax_32[5]
004158bd        arg1[0x66] = ecx_24
004158c7        if (*eax_32 == 0)
004158cc        int32_t edx_27
004158cc        edx_27:1.b = (*(ecx_24 + 4)):1.b | 0x10
004158cf        *(ecx_24 + 4) = edx_27
004158dd        arg1[0x67] = eax_32[1]
004158e2        arg1[0x68] = eax_32[2]
004158e5        eax_32 = eax_32[3]
004158e8        arg1[0x6b] = 0
004158ee        arg1[0x69] = eax_32
004158f1        arg1[0x6c] = 0x3d088889
00415ad3        void* ecx_41 = arg1[0x9e]
00415ae1        if (*(ecx_41 + 0x384) == 1)
00415ae7        long double x87_r7_58 = fconvert.t(*(ecx_41 + 0x398))
00415aed        long double temp6_1 = fconvert.t(0.5f)
00415aed        x87_r7_58 - temp6_1
00415af3        eax_32.w = (x87_r7_58 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_58, temp6_1) ? 1 : 0) << 0xa | (x87_r7_58 == temp6_1 ? 1 : 0) << 0xe
00415af8        if (*(ecx_41 + 0x384) != 1 || (eax_32:1.b & 1) == 0)
00415b67        arg1[0xaf].b = 0
00415b6d        arg1[0xb9] = 0xbf800000
00415afa        arg1[0xaf].b = 1
00415b07        arg1[0xb0] = *(ecx_41 + 0x388)
00415b13        arg1[0xb1] = *(ecx_41 + 0x38c)
00415b1f        arg1[0xb2] = *(ecx_41 + 0x390)
00415b31        arg1[0xb3] = *(ecx_41 + 0x394)
00415b37        arg1[0xb4] = 0
00415b45        arg1[0xb5] = *(ecx_41 + 0x3b0)
00415b4a        arg1[0xb6] = *(ecx_41 + 0x3b4)
00415b4d        int32_t eax_54 = *(ecx_41 + 0x3b8)
00415b50        arg1[0xb8] = arg1
00415b56        arg1[0xb7] = eax_54
00415b5f        arg1[0xb9] = *(ecx_41 + 0x3b8)
00415b7d        long double st0 = vector_magnitude(&arg1[0x93])
00415b82        float eax_55 = arg1[0x7d]
00415b84        int32_t ecx_44 = arg1[0x7e]
00415b8d        arg1[0x99] = fconvert.s(st0)
00415b93        arg1[0x8d] = eax_55
00415b95        int32_t eax_56 = arg1[0x7f]
00415b98        arg1[0x8e] = ecx_44
00415b9d        arg1[0x8f] = eax_56
00415baa        return (**arg1)()
