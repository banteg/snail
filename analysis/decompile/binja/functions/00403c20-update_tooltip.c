/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tooltip @ 0x403c20 */

00403c26        int32_t eax = *(arg1 + 4)
00403c2a        void* eax_2
00403c2a        if (eax == 1)
00403f33        eax_2 = *(arg1 + 0xc)
00403f40        if ((*(eax_2 + 0x1a0) & 0x20000) != 0)
00403f42        *(arg1 + 0x10) = 0
00403f49        *(arg1 + 4) = 2
00403c31        if (eax == 2)
00403c75        void* ecx_2 = *(arg1 + 0xc)
00403c82        if ((*(ecx_2 + 0x1a0) & 0x20000) == 0)
00403f27        *(arg1 + 4) = 1
00403f32        return eax - 2
00403c8b        long double x87_r7_2 = fconvert.t(*(arg1 + 0x14)) + fconvert.t(*(arg1 + 0x10))
00403c8e        *(arg1 + 0x10) = fconvert.s(x87_r7_2)
00403c91        long double temp3_1 = fconvert.t(1f)
00403c91        x87_r7_2 - temp3_1
00403c97        eax_2.w = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
00403c9c        if ((eax_2:1.b & 0x41) == 0)
00403caa        float var_54
00403caa        if (*(ecx_2 + 0x25c) == 0)
00403cd0        var_54 = fconvert.s(fconvert.t(*(ecx_2 + 0x248)) * fconvert.t(0.5f) + fconvert.t(*(ecx_2 + 0x6f4)) - fconvert.t(320f))
00403cb2        var_54 = *(ecx_2 + 0x260)
00403cd4        int32_t eax_6 = *(arg1 + 0x18)
00403cd7        *(arg1 + 4) = 3
00403ce0        if (eax_6 == 0)
00403d02        *(arg1 + 0x18) = allocate_border(data_4df904 + 0xb4c)
00403ce7        report_errorf("Tool tip overload")
00403d05        float* eax_11 = *(arg1 + 8)
00403d0b        if ((eax_11.b & 1) != 0)
00403d15        float var_60_1 = var_54
00403d2c        void var_50
00403d2c        int32_t* eax_8
00403d2c        int32_t ecx_6
00403d2c        eax_8, ecx_6 = set_color_rgba(&var_50, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00403d32        void* eax_9 = data_4df904
00403d37        int32_t var_6c_1 = ecx_6
00403d56        initialize_frontend_widget(*(arg1 + 0x18), 2, arg1, 7, *(eax_9 + 0x29c), fconvert.s(fconvert.t(*(eax_9 + 0x2a0)) + fconvert.t(64f)), eax_8, 1.40129846e-45f)
00403d62        float var_64_1
00403d62        int32_t* ecx_9
00403d62        void* edi_1
00403d62        if ((eax_11.b & 4) != 0)
00403d68        edi_1 = *(arg1 + 0xc)
00403d6b        float var_60_2 = var_54
00403d7d        int32_t var_74_1
00403d7d        __builtin_memcpy(&var_74_1, "\x00\x00\x80\x3f\x00\x00\x80\x3f\x00\x00\x80\x3f\x00\x00\x80\x3f\x01\x00\x00\x00", 0x14)
00403d82        void var_40
00403d82        ecx_9 = &var_40
00403df9        label_403df9:
00403df9        int32_t* eax_14
00403df9        int32_t ecx_13
00403df9        eax_14, ecx_13 = set_color_rgba(ecx_9, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00403e11        int32_t var_6c_6 = ecx_13
00403e1e        initialize_frontend_widget(*(arg1 + 0x18), 2, arg1, 7, *(edi_1 + 0x6f4), fconvert.s(fconvert.t(*(edi_1 + 0x6f8)) - fconvert.t(*(edi_1 + 0x220))), eax_14, var_64_1)
00403e23        eax_11 = *(arg1 + 0x18)
00403e9c        eax_11[0x1be] = fconvert.s(fconvert.t(eax_11[0x1be]) - (fconvert.t(eax_11[0x93]) + fconvert.t(eax_11[0x88])))
00403d8a        int32_t var_70_2
00403d8a        float var_6c_4
00403d8a        int32_t* var_68_2
00403d8a        float var_64_2
00403d8a        if ((eax_11.b & 2) == 0)
00403dd8        if ((eax_11.b & 0x10) != 0)
00403dda        edi_1 = *(arg1 + 0xc)
00403ddd        int32_t var_60_4 = 0
00403ddf        var_64_1 = 0f
00403de1        int32_t var_68_3 = 0x3f800000
00403de6        int32_t var_6c_5 = 0x3f800000
00403deb        int32_t var_70_3 = 0x3f800000
00403df0        int32_t var_74_2 = 0x3f800000
00403df5        void var_20
00403df5        ecx_9 = &var_20
00403df5        goto label_403df9
00403e3c        if ((eax_11.b & 8) != 0)
00403e3e        void* edi_3 = *(arg1 + 0xc)
00403e41        int32_t var_60_5 = 0
00403e43        var_64_2 = 0f
00403e5d        void var_10
00403e5d        int32_t* eax_15
00403e5d        int32_t ecx_16
00403e5d        eax_15, ecx_16 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00403e6e        var_68_2 = eax_15
00403e75        int32_t var_6c_8 = ecx_16
00403e7c        var_6c_4 = fconvert.s(fconvert.t(*(edi_3 + 0x6f8)) + fconvert.t(*(edi_3 + 0x24c)) + fconvert.t(*(edi_3 + 0x220)))
00403e7f        var_70_2 = *(edi_3 + 0x6f4)
00403e7f        goto label_403e88
00403d90        void* edi_2 = *(arg1 + 0xc)
00403d93        float var_60_3 = var_54
00403d94        var_64_2 = 1.40129846e-45f
00403dae        void var_30
00403dae        int32_t* eax_13
00403dae        int32_t ecx_11
00403dae        eax_13, ecx_11 = set_color_rgba(&var_30, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00403dbf        var_68_2 = eax_13
00403dc0        int32_t var_6c_3 = ecx_11
00403dcd        var_6c_4 = fconvert.s(fconvert.t(*(edi_2 + 0x6f8)) + fconvert.t(*(edi_2 + 0x24c)) + fconvert.t(*(edi_2 + 0x220)))
00403dd0        var_70_2 = *(edi_2 + 0x6f4)
00403e88        label_403e88:
00403e88        initialize_frontend_widget(*(arg1 + 0x18), 2, arg1, 7, var_70_2, var_6c_4, var_68_2, var_64_2)
00403e8d        eax_11 = *(arg1 + 0x18)
00403e9c        eax_11[0x1be] = fconvert.s(fconvert.t(eax_11[0x88]) + fconvert.t(eax_11[0x1be]))
00403ea2        void* ecx_18 = *(arg1 + 0x18)
00403eb2        long double x87_r7_23 = fconvert.t(*(ecx_18 + 0x238)) - fconvert.t(*(ecx_18 + 0x218)) - fconvert.t(*(ecx_18 + 0x26c))
00403eb8        long double temp4 = fconvert.t(0f)
00403eb8        x87_r7_23 - temp4
00403ebe        eax_11.w = (x87_r7_23 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp4) ? 1 : 0) << 0xa | (x87_r7_23 == temp4 ? 1 : 0) << 0xe
00403ec3        if ((eax_11:1.b & 1) != 0)
00403ecb        *(ecx_18 + 0x6f4) = *(ecx_18 + 0x26c)
00403ed1        void* ecx_19 = *(arg1 + 0x18)
00403ee6        long double x87_r7_27 = fconvert.t(*(ecx_19 + 0x26c)) + fconvert.t(*(ecx_19 + 0x248)) + fconvert.t(*(ecx_19 + 0x238)) + fconvert.t(*(ecx_19 + 0x218))
00403eec        long double temp5 = fconvert.t(640f)
00403eec        x87_r7_27 - temp5
00403ef2        eax_11.w = (x87_r7_27 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_27, temp5) ? 1 : 0) << 0xa | (x87_r7_27 == temp5 ? 1 : 0) << 0xe | 0x3800
00403ef7        if ((eax_11:1.b & 0x41) != 0)
00403f26        return layout_frontend_widget(*(arg1 + 0x18))
00403f05        *(ecx_19 + 0x6f4) = fconvert.s(fconvert.t(*(ecx_19 + 0x6f4)) - (x87_r7_27 - fconvert.t(640f)))
00403f17        return layout_frontend_widget(*(arg1 + 0x18))
00403c33        eax_2 = eax - 3
00403c34        if (eax == 3)
00403c3a        eax_2 = *(arg1 + 0xc)
00403c47        if ((*(eax_2 + 0x1a0) & 0x20000) == 0)
00403c4d        void* ecx = *(arg1 + 0x18)
00403c50        *(arg1 + 4) = 1
00403c57        data_4df904
00403c64        int32_t eax_3 = kill_border(ecx)
00403c69        *(arg1 + 0x18) = 0
00403c74        return eax_3
00403f54        return eax_2
