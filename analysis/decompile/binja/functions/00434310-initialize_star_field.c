/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_star_field @ 0x434310 */

0043431e        int32_t i = 0
00434322        if (arg1[0x10] s> 0)
00434324        int32_t ebx_1 = 0
0043433b        i += 1
0043433c        *(ebx_1 + arg1[0xf] + 0x1c) = allocate_sprite(&data_790f30, 2, 0x20, 0xffffffff, 0xffffffff)
00434343        ebx_1 += 0x2c
00434348        do while (i s< arg1[0x10])
0043434d        int32_t i_1 = 0
0043434f        bool cond:0 = arg1[0x10] s<= 0
00434351        arg1[0x11] = 0x3f800000
00434358        if (not(cond:0))
0043436b        int32_t edi_1 = i_1 * 0x2c
00434370        *(edi_1 + arg1[0xf]) = 1
00434377        if (i_1 != 0)
004343a7        *(edi_1 + arg1[0xf] + 0x28) = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351572e-06f) + fconvert.t(0.400000006f))
0043437c        *(arg1[0xf] + 0x28) = 0x3ecccccd
004343ab        void* eax_6 = data_4df904
004343f4        float var_54_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_6 + 0x6d8)) * fconvert.t(50f))) + fconvert.t(*(eax_6 + 0x6e8)))
00434405        float* ecx_2 = edi_1 + arg1[0xf] + 4
0043440d        float var_50_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_6 + 0x6dc)) * fconvert.t(50f))) + fconvert.t(*(eax_6 + 0x6ec)))
00434411        *ecx_2 = fconvert.s(fconvert.t(*(eax_6 + 0x6d4)) * fconvert.t(50f) + fconvert.t(*(eax_6 + 0x6e4)))
00434417        ecx_2[1] = var_54_1
0043441a        ecx_2[2] = var_50_1
00434436        float var_5c_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
0043443a        int32_t eax_10 = next_math_random_value()
0043444e        int32_t* edx_5 = edi_1 + arg1[0xf] + 0x10
0043446e        *edx_5 = fconvert.s((float.t(eax_10) - fconvert.t(16384f)) * fconvert.t(6.10351562e-05f))
00434474        edx_5[1] = var_5c_1
00434477        edx_5[2] = 0
00434481        normalize_vector(edi_1 + arg1[0xf] + 0x10)
00434488        int32_t eax_13 = next_math_random_value()
00434498        float* eax_14 = edi_1 + arg1[0xf] + 0x10
004344a2        long double x87_r7_22 = float.t(eax_13) * fconvert.t(1.83105476e-05f) + fconvert.t(0.300000012f)
004344ac        *eax_14 = fconvert.s(x87_r7_22 * fconvert.t(*eax_14))
004344b3        eax_14[1] = fconvert.s(x87_r7_22 * fconvert.t(eax_14[1]))
004344b9        eax_14[2] = fconvert.s(x87_r7_22 * fconvert.t(eax_14[2]))
004344bf        *(edi_1 + arg1[0xf] + 0x18) = 0
004344d2        *(edi_1 + arg1[0xf] + 0x20) = fconvert.s(vector_magnitude(edi_1 + arg1[0xf] + 0x10))
00434500        *(edi_1 + arg1[0xf] + 0x24) = fconvert.s(float.t(next_math_random_value()) * fconvert.t(0.00106811523f))
00434504        int32_t ecx_9 = arg1[0xf]
00434507        long double x87_r7_27 = fconvert.t(*(edi_1 + ecx_9 + 0x24))
0043450b        void* eax_18 = edi_1 + ecx_9
00434526        long double x87_r6_13 = fconvert.t(*(eax_18 + 0x20))
0043455a        float var_3c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(*(eax_18 + 0x14)))) / x87_r6_13)) + fconvert.t(*(eax_18 + 8)))
00434562        long double x87_r7_31 = x87_r7_27 * fconvert.t(*(eax_18 + 0x18)) / x87_r6_13 + fconvert.t(*(eax_18 + 0xc))
00434565        *(eax_18 + 4) = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r7_27 * fconvert.t(*(eax_18 + 0x10)))) / x87_r6_13)) + fconvert.t(*(eax_18 + 4)))
00434567        *(eax_18 + 8) = var_3c_1
00434572        *(eax_18 + 0xc) = fconvert.s(x87_r7_31)
00434578        void* eax_21 = *(edi_1 + arg1[0xf] + 0x1c)
00434585        *(eax_21 + 4) |= 0x402
0043458f        *(*(edi_1 + arg1[0xf] + 0x1c) + 0x68) = 0
00434599        *(*(edi_1 + arg1[0xf] + 0x1c) + 0x6c) = 0
004345a7        *(*(edi_1 + arg1[0xf] + 0x1c) + 0x78) = 0
004345aa        struct Color4f color
004345aa        struct Color4f* eax_24 = set_color_rgba(&color, 0.800000012f, 0.800000012f, 1f, 0.400000006f)
004345b8        float* edx_13 = *(edi_1 + arg1[0xf] + 0x1c) + 0x2c
004345bb        *edx_13 = eax_24->r
004345c0        edx_13[1] = eax_24->g
004345c6        edx_13[2] = eax_24->b
004345cc        edx_13[3] = eax_24->a
004345d6        *(*(edi_1 + arg1[0xf] + 0x1c) + 0x60) = 0x3f4ccccd
004345e0        void* eax_27 = *(edi_1 + arg1[0xf] + 0x1c)
004345e7        *(eax_27 + 0x64) = *(eax_27 + 0x60)
004345ea        int32_t edx_15 = arg1[0xf]
00434603        *(*(edi_1 + edx_15 + 0x1c) + 0x88) = fconvert.s((fconvert.t(*(edi_1 + edx_15 + 0x20)) + fconvert.t(1f)) * fconvert.t(4f))
0043460c        void* eax_30 = edi_1 + arg1[0xf]
00434615        int32_t* eax_32 = *(eax_30 + 0x1c) + 0x54
0043461a        *eax_32 = *(eax_30 + 0x10)
0043461f        eax_32[1] = *(eax_30 + 0x14)
00434625        eax_32[2] = *(eax_30 + 0x18)
0043462b        void* eax_34 = arg1[0xf] + edi_1
00434633        int32_t* edx_19 = *(eax_34 + 0x1c) + 0x48
00434636        i_1 += 1
00434639        *edx_19 = *(eax_34 + 4)
0043463e        edx_19[1] = *(eax_34 + 8)
00434644        edx_19[2] = *(eax_34 + 0xc)
0043464e        *(*(edi_1 + arg1[0xf] + 0x1c) + 0x8c) = 0
00434659        do while (i_1 s< arg1[0x10])
0043466c        return (**arg1)()
