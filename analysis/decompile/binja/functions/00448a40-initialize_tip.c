/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tip @ 0x448a40 */

00448a4f        *arg1 = 1
00448a55        if (arg2 == 0)
00448a5c        arg1[2] = 0x4ac5c8
00448a57        arg1[2] = arg2
00448a74        arg1[3] = allocate_border(data_4df904 + 0xb4c)
00448a7a        void* edi = arg1[2]
00448a8a        int32_t var_20 = *(edi + 4)
00448a8b        uint32_t eax_5 = (sx.d(not.b((*arg1[2]).b)) & 4) u>> 1
00448aa6        void var_10
00448aa6        int32_t* eax_6 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00448abf        initialize_frontend_widget(arg1[3], 2, *(edi + 0x10), 0x14, *(edi + 4), *(edi + 8), eax_6, eax_5)
00448ac4        char* eax_8 = arg1[2]
00448acb        if ((*eax_8 & 2) != 0)
00448acd        arg1[6] = 0
00448adf        arg1[7] = fconvert.s(fconvert.t(1f) / (fconvert.t(*(eax_8 + 0xc)) * fconvert.t(60f)))
00448ae5        if ((*eax_8 & 1) == 0)
00448c09        arg1[4] = 0
00448c0c        arg1[5] = 0
00448afb        arg1[4] = allocate_border(data_4df904 + 0xb4c)
00448b04        if (arg3 != 0)
00448bc8        int32_t __saved_edi_7 = *(arg1[2] + 4)
00448bdf        int32_t* eax_17 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00448bf3        initialize_frontend_widget(arg1[4], 0x14, "OK", 0x14, 0, 0f, eax_17, 2.80259693e-45f)
00448bf8        void* ecx_17 = arg1[3]
00448bfb        arg1[5] = 0
00448c02        stack_widget_below(arg1[4], ecx_17)
00448b0a        void* __saved_edi_9 = arg1[2]
00448b0d        void* __saved_edi_1 = __saved_edi_9
00448b1b        float __saved_edi_2 = fconvert.s(fconvert.t(*(__saved_edi_9 + 4)) + fconvert.t(40f))
00448b34        int32_t* eax_12 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00448b48        initialize_frontend_widget(arg1[4], 0x14, "OK", 0x14, 0, 0f, eax_12, 2.80259693e-45f)
00448b59        void* eax_13
00448b59        int32_t __saved_edi_10
00448b59        eax_13, __saved_edi_10 = allocate_border(data_4df904 + 0xb4c)
00448b5e        arg1[5] = eax_13
00448b64        int32_t __saved_edi_3 = __saved_edi_10
00448b72        float __saved_edi_4 = fconvert.s(fconvert.t(*(arg1[2] + 4)) - fconvert.t(60f))
00448b8b        int32_t* eax_15 = set_color_rgba(&var_10, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000)
00448b9f        initialize_frontend_widget(arg1[5], 0x14, "Disable", 0x14, 0, 0f, eax_15, 2.80259693e-45f)
00448bab        stack_widget_below(arg1[5], arg1[3])
00448bb7        stack_widget_below(arg1[4], arg1[3])
00448c15        char* ecx_19 = arg1[2]
00448c1e        arg1[1] = *(data_4df904 + 0x1b8)
00448c21        int32_t result
00448c21        result.b = *ecx_19
00448c27        if ((result.b & 1) != 0)
00448c2f        *(data_4df904 + 0x1b8) = 0x16
00448c3c        return result
