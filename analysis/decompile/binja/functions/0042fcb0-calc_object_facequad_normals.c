/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals @ 0x42fcb0 */

0042fcb9        request_object_facequad_normals(arg1)
0042fcca        float* eax_2 = allocate_tracked_memory(*(arg1 + 0x2c) << 2, "Normal Tally")
0042fcd4        int32_t ecx_1 = *(arg1 + 0x2c) << 2
0042fcea        __builtin_memset(__builtin_memset(eax_2, 0, ecx_1 & 0xfffffffc), 0, ecx_1 & 3)
0042fcef        float* edi_2 = nullptr
0042fcf3        int32_t var_68 = 0
0042fcf7        if (*(arg1 + 0x54) s> 0)
0042fcfd        int32_t var_64_1 = 0
00430171        bool cond:2_1
0042fd04        int32_t ecx_5 = *(arg1 + 0x38)
0042fd07        void* eax_5 = *(arg1 + 0x5c) + edi_2
0042fd0b        int32_t edx_1
0042fd0b        edx_1.w = *(eax_5 + 2)
0042fd12        float* ebp_1 = ecx_5 + edx_1 * 0xc
0042fd17        int32_t edx_3
0042fd17        edx_3.w = *(eax_5 + 4)
0042fd1b        int32_t edx_4 = edx_3 * 3
0042fd24        void* edx_5 = ecx_5 + (edx_4 << 2)
0042fd3f        struct Vec3 lhs
0042fd3f        lhs.x = fconvert.s(fconvert.t(*(ecx_5 + (edx_4 << 2))) - fconvert.t(*ebp_1))
0042fd47        lhs.y = fconvert.s(fconvert.t(*(edx_5 + 4)) - fconvert.t(ebp_1[1]))
0042fd53        lhs.z = fconvert.s(fconvert.t(*(edx_5 + 8)) - fconvert.t(ebp_1[2]))
0042fd59        int32_t edx_9
0042fd59        edx_9.w = *(eax_5 + 2)
0042fd60        float* ebp_2 = ecx_5 + edx_9 * 0xc
0042fd65        int32_t edx_11
0042fd65        edx_11.w = *(eax_5 + 6)
0042fd69        int32_t eax_6 = edx_11 * 3
0042fd72        void* ecx_6 = ecx_5 + (eax_6 << 2)
0042fd91        struct Vec3 rhs
0042fd91        rhs.x = fconvert.s(fconvert.t(*(ecx_5 + (eax_6 << 2))) - fconvert.t(*ebp_2))
0042fd95        rhs.y = fconvert.s(fconvert.t(*(ecx_6 + 4)) - fconvert.t(ebp_2[1]))
0042fdaf        rhs.z = fconvert.s(fconvert.t(*(ecx_6 + 8)) - fconvert.t(ebp_2[2]))
0042fdb3        struct Vec3 var_54
0042fdb3        cross_vectors(&var_54, &lhs, &rhs)
0042fdbc        normalize_vector(&var_54)
0042fdcc        float* eax_9 = *(arg1 + 0x60) + var_64_1
0042fdd0        *eax_9 = var_54.x
0042fdd6        eax_9[1] = var_54.y
0042fddd        eax_9[2] = var_54.z
0042fde0        char* edx_15 = *(arg1 + 0x5c)
0042fde3        float ecx_11
0042fde3        ecx_11.b = *(edx_15 + edi_2)
0042fde6        void* eax_10 = edx_15 + edi_2
0042fdec        struct Vec3 var_60
0042fdec        if ((ecx_11.b & 0x80) == 0)
0042fdf2        int32_t ecx_12 = *(arg1 + 0x38)
0042fdf7        int32_t edx_16
0042fdf7        edx_16.w = *(eax_10 + 2)
0042fdfe        float* ebp_3 = ecx_12 + edx_16 * 0xc
0042fe03        int32_t edx_18
0042fe03        edx_18.w = *(eax_10 + 6)
0042fe07        int32_t edx_19 = edx_18 * 3
0042fe10        void* edx_20 = ecx_12 + (edx_19 << 2)
0042fe2b        lhs.x = fconvert.s(fconvert.t(*(ecx_12 + (edx_19 << 2))) - fconvert.t(*ebp_3))
0042fe33        lhs.y = fconvert.s(fconvert.t(*(edx_20 + 4)) - fconvert.t(ebp_3[1]))
0042fe3f        lhs.z = fconvert.s(fconvert.t(*(edx_20 + 8)) - fconvert.t(ebp_3[2]))
0042fe45        int32_t edx_24
0042fe45        edx_24.w = *(eax_10 + 2)
0042fe4c        float* ebp_4 = ecx_12 + edx_24 * 0xc
0042fe51        int32_t edx_26
0042fe51        edx_26.w = *(eax_10 + 8)
0042fe55        int32_t eax_11 = edx_26 * 3
0042fe5e        void* ecx_13 = ecx_12 + (eax_11 << 2)
0042fe7d        rhs.x = fconvert.s(fconvert.t(*(ecx_12 + (eax_11 << 2))) - fconvert.t(*ebp_4))
0042fe81        rhs.y = fconvert.s(fconvert.t(*(ecx_13 + 4)) - fconvert.t(ebp_4[1]))
0042fe9b        rhs.z = fconvert.s(fconvert.t(*(ecx_13 + 8)) - fconvert.t(ebp_4[2]))
0042fe9f        cross_vectors(&var_60, &lhs, &rhs)
0042fea8        normalize_vector(&var_60)
0042feb6        float* edx_28 = *(arg1 + 0x60) + var_64_1 + 0xc
0042febe        *edx_28 = var_60.x
0042fec4        edx_28[1] = var_60.y
0042fecb        edx_28[2] = var_60.z
0042fed1        char* ecx_20 = *(arg1 + 0x5c) + edi_2
0042fed6        if ((*ecx_20 & 0x80) == 0)
0042fede        int32_t eax_16
0042fede        eax_16.w = *(ecx_20 + 2)
0042fee6        int32_t edx_29 = eax_16 * 3
0042fee9        int32_t eax_17 = *(arg1 + 0x44)
0042feef        float* eax_18 = eax_17 + (edx_29 << 2)
0042fef2        *eax_18 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(eax_17 + (edx_29 << 2))))
0042fefb        eax_18[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_18[1]))
0042ff05        eax_18[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_18[2]))
0042ff11        int32_t eax_19
0042ff11        eax_19.w = *(*(arg1 + 0x5c) + edi_2 + 4)
0042ff16        int32_t edx_30 = eax_19 * 3
0042ff19        int32_t eax_20 = *(arg1 + 0x44)
0042ff1f        float* eax_21 = eax_20 + (edx_30 << 2)
0042ff22        *eax_21 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(eax_20 + (edx_30 << 2))))
0042ff2b        eax_21[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_21[1]))
0042ff35        eax_21[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_21[2]))
0042ff41        int32_t eax_22
0042ff41        eax_22.w = *(*(arg1 + 0x5c) + edi_2 + 6)
0042ff46        int32_t edx_31 = eax_22 * 3
0042ff49        int32_t eax_23 = *(arg1 + 0x44)
0042ff4f        float* eax_24 = eax_23 + (edx_31 << 2)
0042ff52        *eax_24 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(eax_23 + (edx_31 << 2))))
0042ff5b        eax_24[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_24[1]))
0042ff65        eax_24[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_24[2]))
0042ff71        int32_t eax_25
0042ff71        eax_25.w = *(*(arg1 + 0x5c) + edi_2 + 8)
0042ff76        int32_t edx_32 = eax_25 * 3
0042ff79        int32_t eax_26 = *(arg1 + 0x44)
0042ff7f        float* eax_27 = eax_26 + (edx_32 << 2)
0042ff84        *eax_27 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(eax_26 + (edx_32 << 2))))
0042ff8d        eax_27[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_27[1]))
0042ff97        eax_27[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_27[2]))
0042ff9d        int32_t edx_33
0042ff9d        edx_33.w = *(*(arg1 + 0x5c) + edi_2 + 2)
0042ffb0        eax_2[edx_33] = fconvert.s(fconvert.t(eax_2[edx_33]) + fconvert.t(1f))
0042ffb5        int32_t ecx_25
0042ffb5        ecx_25.w = *(*(arg1 + 0x5c) + edi_2 + 4)
0042ffc6        eax_2[ecx_25] = fconvert.s(fconvert.t(eax_2[ecx_25]) + fconvert.t(1f))
0042ffcd        int32_t eax_31
0042ffcd        eax_31.w = *(*(arg1 + 0x5c) + edi_2 + 6)
0042ffde        eax_2[eax_31] = fconvert.s(fconvert.t(eax_2[eax_31]) + fconvert.t(1f))
0042ffe5        int32_t edx_35
0042ffe5        edx_35.w = *(*(arg1 + 0x5c) + edi_2 + 8)
0042fff6        eax_2[edx_35] = fconvert.s(fconvert.t(eax_2[edx_35]) + fconvert.t(1f))
00430001        int32_t eax_34
00430001        eax_34.w = *(*(arg1 + 0x5c) + edi_2 + 2)
00430006        int32_t edx_36 = eax_34 * 3
00430009        int32_t eax_35 = *(arg1 + 0x44)
0043000f        float* eax_36 = eax_35 + (edx_36 << 2)
00430012        *eax_36 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(eax_35 + (edx_36 << 2))))
0043001b        eax_36[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_36[1]))
00430025        eax_36[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_36[2]))
00430031        int32_t eax_37
00430031        eax_37.w = *(*(arg1 + 0x5c) + edi_2 + 4)
00430036        int32_t edx_37 = eax_37 * 3
00430039        int32_t eax_38 = *(arg1 + 0x44)
0043003f        float* eax_39 = eax_38 + (edx_37 << 2)
00430042        *eax_39 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(eax_38 + (edx_37 << 2))))
0043004b        eax_39[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_39[1]))
00430055        eax_39[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_39[2]))
00430061        int32_t eax_40
00430061        eax_40.w = *(*(arg1 + 0x5c) + edi_2 + 6)
00430066        int32_t edx_38 = eax_40 * 3
00430069        int32_t eax_41 = *(arg1 + 0x44)
0043006f        float* eax_42 = eax_41 + (edx_38 << 2)
00430072        *eax_42 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(eax_41 + (edx_38 << 2))))
0043007b        eax_42[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_42[1]))
00430085        eax_42[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_42[2]))
00430091        int32_t eax_43
00430091        eax_43.w = *(*(arg1 + 0x5c) + edi_2 + 8)
00430096        int32_t edx_39 = eax_43 * 3
00430099        int32_t eax_44 = *(arg1 + 0x44)
0043009f        float* eax_45 = eax_44 + (edx_39 << 2)
004300a4        *eax_45 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(eax_44 + (edx_39 << 2))))
004300ad        eax_45[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_45[1]))
004300b7        eax_45[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_45[2]))
004300bd        int32_t edx_40
004300bd        edx_40.w = *(*(arg1 + 0x5c) + edi_2 + 2)
004300d0        eax_2[edx_40] = fconvert.s(fconvert.t(eax_2[edx_40]) + fconvert.t(2.0999999f))
004300d5        int32_t ecx_32
004300d5        ecx_32.w = *(*(arg1 + 0x5c) + edi_2 + 4)
004300e6        eax_2[ecx_32] = fconvert.s(fconvert.t(eax_2[ecx_32]) + fconvert.t(2.0999999f))
004300ed        int32_t eax_49
004300ed        eax_49.w = *(*(arg1 + 0x5c) + edi_2 + 6)
004300fe        eax_2[eax_49] = fconvert.s(fconvert.t(eax_2[eax_49]) + fconvert.t(2.0999999f))
00430105        int32_t edx_42
00430105        edx_42.w = *(*(arg1 + 0x5c) + edi_2 + 8)
00430118        eax_2[edx_42] = fconvert.s(fconvert.t(eax_2[edx_42]) + fconvert.t(2.0999999f))
0043011d        int32_t ecx_34 = *(arg1 + 0x2c)
00430120        void* eax_53 = *(arg1 + 0x5c) + edi_2
00430122        int32_t edx_43
00430122        edx_43.w = *(eax_53 + 2)
00430128        if (edx_43 s> ecx_34)
0043014d        report_errorf("Invalid Face Vertex Index")
0043012c        int32_t edx_44
0043012c        edx_44.w = *(eax_53 + 4)
00430132        if (edx_44 s> ecx_34)
0043014d        report_errorf("Invalid Face Vertex Index")
00430136        int32_t edx_45
00430136        edx_45.w = *(eax_53 + 6)
0043013c        if (edx_45 s> ecx_34)
0043014d        report_errorf("Invalid Face Vertex Index")
00430140        int32_t edx_46
00430140        edx_46.w = *(eax_53 + 8)
00430146        if (edx_46 s> ecx_34)
0043014d        report_errorf("Invalid Face Vertex Index")
00430164        edi_2 = &edi_2[0xc]
00430167        cond:2_1 = var_68 + 1 s< *(arg1 + 0x54)
00430169        var_68 += 1
0043016d        var_64_1 += 0x18
00430171        do while (cond:2_1)
00430177        edi_2 = nullptr
0043017c        int32_t var_68_1 = 0
00430182        if (*(arg1 + 0x2c) s> 0)
00430188        float* ebp_7 = eax_2
0043020e        bool cond:1_1
0043018a        int32_t ecx_36 = *(arg1 + 0x44)
0043018f        long double x87_r7_93 = fconvert.t(*ebp_7)
00430195        float* eax_58 = edi_2 + ecx_36
0043019b        *eax_58 = fconvert.s(fconvert.t(*(edi_2 + ecx_36)) / x87_r7_93)
004301a2        eax_58[1] = fconvert.s(fconvert.t(eax_58[1]) / x87_r7_93)
004301aa        eax_58[2] = fconvert.s(fconvert.t(eax_58[2]) / x87_r7_93)
004301b4        normalize_vector(edi_2 + *(arg1 + 0x44))
004301bc        ebp_7 = &ebp_7[1]
004301bf        int32_t* eax_61 = *(arg1 + 0x44) + edi_2
004301c1        edi_2 = &edi_2[3]
004301df        float var_8_2 = fconvert.s(fconvert.t(eax_61[1]) * fconvert.t(-1f))
004301e6        long double x87_r7_102 = fconvert.t(eax_61[2]) * fconvert.t(-1f)
004301f0        *eax_61 = fconvert.s(fconvert.t(*eax_61) * fconvert.t(-1f))
004301f2        eax_61[1] = var_8_2
004301fd        eax_61[2] = fconvert.s(x87_r7_102)
00430208        cond:1_1 = var_68_1 + 1 s< *(arg1 + 0x2c)
0043020a        var_68_1 += 1
0043020e        do while (cond:1_1)
00430224        return free_tracked_memory(eax_2)
