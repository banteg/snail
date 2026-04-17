/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: render_game_frame @ 0x40a490 */

0040a49a        void* edi = arg1
0040a49c        int32_t esi = 0
0040a49e        void* var_78 = edi
0040a4a2        int32_t eax = *(edi + 0x56c)
0040a4aa        if (eax s> 0)
0040a4ad        *(edi + 0x56c) = eax - 1
0040a4bd        return eax - 1
0040a4be        sub_414650()
0040a4c7        int32_t var_70 = 0
0040a4cb        struct TransformMatrix transform
0040a4cb        set_matrix_identity(&transform)
0040a4d0        int32_t result_2 = 0
0040a4d5        int32_t i_7
0040a4d5        __builtin_memset(&i_7, 0xff, 0x14)
0040a4d9        int32_t var_74 = 0
0040a4e1        char* eax_2 = edi + 0x5bc
0040a4f3        int32_t i_8 = 5
0040a502        int32_t i
0040a4fb        if ((*eax_2 & 1) != 0)
0040a4fd        result_2 += 1
0040a4fe        eax_2 = &eax_2[0x28]
0040a501        i = i_8
0040a501        i_8 -= 1
0040a502        do while (i != 1)
0040a50a        int32_t* eax_3 = edi + 0x5b8
0040a516        int32_t result_3 = result_2
0040a520        int32_t i_1 = 0
0040a522        *(edi + 0x5e4) = (*(edi + 0x5e4) & 0xffffff) | 0x2000000
0040a528        int32_t i_6 = 0
0040a52c        int32_t* var_80 = eax_3
0040a534        if ((eax_3[1].b & 1) != 0)
0040a538        if (esi != 0)
0040a545        int32_t edx_3 = 0
0040a549        if (esi s> 0)
0040a54b        int32_t ebp_1 = *eax_3
0040a54d        int32_t eax_4 = 0
0040a561        if (ebp_1 s> *(edi + *(&i_7 + eax_4) * 0x28 + 0x5b8))
0040a566        if (eax_4 s<= 0xc)
0040a56d        int32_t var_44
0040a56d        int32_t* eax_5 = &var_44
0040a571        int32_t j_2 = 4 - edx_3
0040a57c        int32_t j
0040a576        *eax_5 = eax_5[-1]
0040a578        eax_5 = &eax_5[-1]
0040a57b        j = j_2
0040a57b        j_2 -= 1
0040a57c        do while (j != 1)
0040a582        esi += 1
0040a583        int32_t __saved_edi
0040a583        *(&__saved_edi + eax_4 + 0x3c) = i_6
0040a585        edx_3 = esi
0040a587        eax_4 = esi << 2
0040a58e        edx_3 += 1
0040a58f        eax_4 += 4
0040a594        do while (edx_3 s< esi)
0040a596        eax_3 = var_80
0040a59a        result_2 = result_3
0040a59e        i_1 = i_6
0040a53a        i_7 = i_1
0040a53e        esi = 1
0040a5a2        i_1 += 1
0040a5a3        eax_3 = &eax_3[0xa]
0040a5a9        i_6 = i_1
0040a5ad        var_80 = eax_3
0040a5b1        do while (i_1 s< 5)
0040a5b7        int32_t result = 0
0040a5bb        int32_t i_10 = 0
0040a5bf        int32_t var_7c = 0
0040a5c3        if (result_2 s> 0)
0040a5cd        int32_t result_1 = result_2
0040a5d1        int32_t* var_74_1 = &i_7
0040aa2e        bool cond:2_1
0040a5d9        int32_t ebx_1 = *var_74_1
0040a5db        int32_t eax_7 = ebx_1 * 5
0040a5de        void* ebp_2 = edi + (eax_7 << 3)
0040a5e1        eax_7.b = *(edi + (eax_7 << 3) + 0x5bc)
0040a5ea        if ((eax_7.b & 1) != 0)
0040a5f0        void* eax_8 = *(ebp_2 + 0x5d4)
0040a5f6        int32_t* edx_5
0040a5f6        edx_5.b = *(ebp_2 + 0x5d8)
0040a609        int32_t* esi_1 = edi + ((ebx_1 * 5 + 0xb9) << 3)
0040a637        int16_t x87control_1 = render_camera(*(ebp_2 + 0x5c0), *(ebp_2 + 0x5c4), *esi_1, *(ebp_2 + 0x5cc), *(eax_8 + 0xc0), eax_8 + 0x38, eax_8 + 0x80, edx_5.b, 0)
0040a647        if ((*(ebp_2 + 0x5bc) & 2) == 0)
0040a64d        void* i_2 = *(edi + 0x5ac)
0040a653        i_10 = 0
0040a65d        if (i_2 != 0)
0040a663        int32_t* edi_1 = &data_4dfb10
0040a66c        if ((*(i_2 + 4) & 0x10) != 0)
0040a66e        char* var_94_2 = "DEBUG RENDER\n"
0040a67b        int32_t eax_12 = *(i_2 + 4)
0040a69c        if ((eax_12.b & 2) != 0 && (eax_12.b & 0x20) != 0 && (*(ebp_2 + 0x5bc) & eax_12 & 0xff000000) != 0)
0040a6a4        if ((eax_12.b & 0x80) != 0)
0040a6aa        *edi_1 = i_2
0040a6ad        edi_1 = &edi_1[1]
0040a6b0        i_10 += 1
0040a6bf        var_7c += 1
0040a6c3        if (((*(i_2 + 4)).w:1.b & 8) != 0)
0040a6d4        *(*(*(i_2 + 0x24) + 0xbc) + 0xc) = *(*(i_2 + 0x78) + 4)
0040a6dd        int32_t var_a0_2
0040a6dd        float var_9c_2
0040a6dd        int32_t* var_98_2
0040a6dd        char var_94_3
0040a6dd        struct TransformMatrix* ecx_14
0040a6dd        if (((*(i_2 + 4)).w:1.b & 4) == 0)
0040a6fe        transform.position.x = *(i_2 + 0x10)
0040a70a        transform.position.y = *(i_2 + 0x14)
0040a714        transform.position.z = *(i_2 + 0x18)
0040a726        var_94_3 = is_bod_after_sprites(i_2)
0040a72a        var_98_2 = i_2 + 0x28
0040a72b        var_9c_2 = *(i_2 + 0x20)
0040a72c        var_a0_2 = *(i_2 + 0x1c)
0040a72d        ecx_14 = &transform
0040a6ec        var_94_3 = is_bod_after_sprites(i_2)
0040a6f0        var_98_2 = i_2 + 0x28
0040a6f1        var_9c_2 = *(i_2 + 0x20)
0040a6f2        var_a0_2 = *(i_2 + 0x1c)
0040a6f3        ecx_14 = i_2 + 0x38
0040a736        x87control_1 = render_object(*(i_2 + 0x24), ecx_14, var_a0_2, var_9c_2, var_98_2, var_94_3)
0040a73e        i_2 = *(i_2 + 0xc)
0040a743        do while (i_2 != 0)
0040a749        edi = var_78
0040a74d        void* i_3 = *((ebx_1 << 2) + &data_814c94)
0040a754        int32_t* var_6c_1 = &data_4e5510
0040a75c        sub_413540()
0040a763        while (i_3 != 0)
0040a774        var_70 += 1
0040a778        int32_t eax_25 = *(i_3 + 4)
0040a783        if ((*(ebp_2 + 0x5bc) & eax_25 & 0xff000000) == 0)
0040a8a4        report_errorf("Loose Sprite scene viewport")
0040a79c        if ((eax_25.b & 1) != 0 && (eax_25.b & 0x40) != 0 && (eax_25:1.b & 2) == 0)
0040a7ae        int32_t esi_3 = *(ebp_2 + 0x5d4) + 0x80
0040a7b8        float var_60 = *(i_3 + 0x48)
0040a7bc        int32_t ecx_20 = *(i_3 + 0x4c)
0040a7c8        float edx_16 = *(i_3 + 0x50)
0040a7cf        void var_d0
0040a7cf        __builtin_memcpy(&var_d0, esi_3, 0x40)
0040a7d5        multiply_vector_by_matrix(&var_60)
0040a7e0        var_60 = fconvert.s(fneg(fconvert.t(var_60)))
0040a7e8        long double x87_r7_4 = fneg(fconvert.t(edx_16))
0040a7ea        float var_58_2 = fconvert.s(x87_r7_4)
0040a7f6        long double x87_r7_7 = fneg(x87_r7_4) * fconvert.t(4.19672108f) + fconvert.t(*(i_3 + 0x98))
0040a7fe        int32_t eax_27
0040a7fe        eax_27, x87control_1 = __ftol(x87control_1, x87_r7_7)
0040a803        int32_t esi_4 = eax_27
0040a80b        if (esi_4 s>= 0x100)
0040a80d        esi_4 = 0xff
0040a820        label_40a820:
0040a820        int32_t** ecx_22 = *((esi_4 << 2) + &data_4f7050)
0040a827        int32_t* edx_17 = var_6c_1
0040a82e        var_6c_1 = &var_6c_1[6]
0040a832        if (ecx_22 == 0)
0040a86d        *((esi_4 << 2) + &data_4f7050) = edx_17
0040a874        label_40a874:
0040a874        *edx_17 = 0
0040a834        int32_t** edi_2 = nullptr
0040a838        if (ecx_22 == 0)
0040a854        label_40a854:
0040a854        *edi_2 = edx_17
0040a874        label_40a874_1:
0040a874        *edx_17 = 0
0040a83a        while (true)
0040a83a        long double temp4_1 = fconvert.t(ecx_22[4])
0040a83a        x87_r7_7 - temp4_1
0040a83d        int32_t* eax_29
0040a83d        eax_29.w = (x87_r7_7 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp4_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0040a842        if ((eax_29:1.b & 1) == 0)
0040a842        break
0040a844        edi_2 = ecx_22
0040a846        ecx_22 = *ecx_22
0040a84a        if (ecx_22 == 0)
0040a84c        *edi_2 = edx_17
0040a84e        goto label_40a874_1
0040a852        if (ecx_22 == 0)
0040a852        goto label_40a854
0040a85a        if (edi_2 == 0)
0040a862        *edx_17 = ecx_22
0040a864        *((esi_4 << 2) + &data_4f7050) = edx_17
0040a85c        *edi_2 = edx_17
0040a85e        *edx_17 = ecx_22
0040a87a        float ecx_23 = var_60
0040a881        edx_17[4] = fconvert.s(x87_r7_7)
0040a884        edx_17[1] = ecx_23
0040a88a        edx_17[5] = i_3
0040a88d        edx_17[2] = ecx_20
0040a894        edx_17[3] = var_58_2
0040a897        *(i_3 + 0x14) = esi_4
0040a89a        *(i_3 + 0x18) = fconvert.s(x87_r7_7)
0040a816        if (esi_4 s>= 0)
0040a816        goto label_40a820
0040a8b0        edi = var_78
0040a8b4        i_3 = *(i_3 + 0xc)
0040a8bf        int32_t* i_4 = &data_4f744c
0040a906        while (i_4 s>= &data_4f7050)
0040a8c4        void** j_1 = *i_4
0040a8c8        if (j_1 != 0)
0040a8ca        void* ecx_26 = j_1[5]
0040a8d1        if ((*(ecx_26 + 4) & 2) != 0)
0040a8e0        sub_44e410(ecx_26, *(ebp_2 + 0x5d4) + 0x80)
0040a8ed        sub_4137f0(&j_1[1], j_1[5])
0040a8f2        j_1 = *j_1
0040a8f9        do while (j_1 != 0)
0040a8fb        *i_4 = j_1
0040a8fd        i_4 -= 4
0040a908        sub_413650()
0040a90d        sub_411e10()
0040a919        draw_font_text_queue(*(ebp_2 + 0x5bc))
0040a921        sub_411de0()
0040a939        if ((*(ebp_2 + 0x5bc) & 2) == 0 && i_10 != 0)
0040a93f        void* eax_33 = *(ebp_2 + 0x5d4)
0040a97c        render_camera(*(ebp_2 + 0x5c0), *(ebp_2 + 0x5c4), *esi_1, *(ebp_2 + 0x5cc), *(eax_33 + 0xc0), eax_33 + 0x38, eax_33 + 0x80, *(ebp_2 + 0x5d8), 1)
0040a989        int32_t i_9 = i_10
0040a990        int32_t* edi_3 = (i_10 << 2) + &data_4dfb10
0040a997        i_10 = 0
0040a99f        var_7c += i_9
0040aa14        int32_t i_5
0040a9a3        void* eax_38 = edi_3[-1]
0040a9a6        edi_3 -= 4
0040a9af        int32_t var_a0_4
0040a9af        float var_9c_4
0040a9af        int32_t* var_98_5
0040a9af        char var_94_9
0040a9af        struct TransformMatrix* eax_41
0040a9af        void* esi_5
0040a9af        if (((*(eax_38 + 4)).w:1.b & 4) == 0)
0040a9cf        esi_5 = *edi_3
0040a9d3        transform.position.x = *(eax_38 + 0x10)
0040a9dd        transform.position.y = *(eax_38 + 0x14)
0040a9e9        transform.position.z = *(eax_38 + 0x18)
0040a9fb        var_94_9 = is_bod_after_sprites(esi_5)
0040a9ff        var_98_5 = esi_5 + 0x28
0040aa00        var_9c_4 = *(esi_5 + 0x20)
0040aa01        var_a0_4 = *(esi_5 + 0x1c)
0040aa02        eax_41 = &transform
0040a9b1        esi_5 = eax_38
0040a9c0        var_94_9 = is_bod_after_sprites(esi_5)
0040a9c4        var_98_5 = esi_5 + 0x28
0040a9c5        var_9c_4 = *(esi_5 + 0x20)
0040a9c6        var_a0_4 = *(esi_5 + 0x1c)
0040a9c7        eax_41 = esi_5 + 0x38
0040aa0b        render_object(*(esi_5 + 0x24), eax_41, var_a0_4, var_9c_4, var_98_5, var_94_9)
0040aa13        i_5 = i_9
0040aa13        i_9 -= 1
0040aa14        do while (i_5 != 1)
0040aa16        edi = var_78
0040aa25        result = result_1 - 1
0040aa25        cond:2_1 = result_1 != 1
0040aa26        var_74_1 = &var_74_1[1]
0040aa2a        result_1 = result
0040aa2e        do while (cond:2_1)
0040aa43        return result
