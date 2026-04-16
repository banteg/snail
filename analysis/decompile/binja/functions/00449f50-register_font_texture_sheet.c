/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_font_texture_sheet @ 0x449f50 */

00449f5d        int32_t ebx = 0
00449f64        if (data_777b20 == 1)
00449f6b        report_errorf("Too many Fonts RFONT_FONT_MAX in font.h")
00449f7d        char* eax = load_file_bytes(arg1, nullptr)
00449f8d        char texture_path[0x100]
00449f8d        char texture_path_1[0x100]
00449f8d        if (*(eax + 0xc) == 0x800)
00449f8f        char i = *arg1
00449f93        int32_t eax_1 = 0
00449f97        while (i != 0x2e)
00449f99        texture_path[eax_1] = i
00449f9d        texture_path_1[eax_1] = i
00449fa4        i = arg1[eax_1 + 1]
00449fa8        eax_1 += 1
00449fad        texture_path[eax_1] = 0x30
00449fb2        texture_path_1[eax_1] = 0x31
00449fbd        ebx = 0x3c0
00449fc2        texture_path_1[eax_1 + 1] = 0x2e
00449fc9        texture_path[eax_1 + 1] = 0x2e
00449fce        texture_path_1[eax_1 + 2] = 0x74
00449fd5        texture_path[eax_1 + 2] = 0x74
00449fdc        texture_path_1[eax_1 + 3] = 0x67
00449fe3        texture_path[eax_1 + 3] = 0x67
00449fea        texture_path_1[eax_1 + 4] = 0x61
00449ff1        texture_path[eax_1 + 4] = 0x61
00449ff6        texture_path_1[eax_1 + 5] = 0
00449ffe        texture_path[eax_1 + 5] = 0
0044a003        int32_t edi_1 = 0
0044a005        int32_t ebp = 0xffffffff
0044a00c        int32_t var_204 = 0
0044a014        int32_t var_20c = 0xffffffff
0044a018        int32_t var_210 = 0
0044a01c        int32_t edx_1
0044a01c        if (*(eax + 0xc) u<= 0)
0044a190        edx_1 = data_777b20
0044a188        int32_t eax_16
0044a026        int32_t eax_7 = sub_44e780(eax, edi_1, 0)
0044a02b        edx_1 = data_777b20
0044a039        if (eax_7 == 0xffffff)
0044a056        int32_t eax_13 = (var_204 + edx_1 * 0x20a) << 2
0044a059        int32_t ecx_3 = edi_1 - ebp
0044a05d        *(eax_13 + &data_777704) = fconvert.s(float.t(var_20c))
0044a067        int32_t ebp_1
0044a067        ebp_1.w = *(eax + 0xc)
0044a07b        float var_208_1 = fconvert.s(float.t(ecx_3) + fconvert.t(0.5f))
0044a087        *(eax_13 + 0x777304) = fconvert.s(fconvert.t(var_208_1) / float.t(ebp_1))
0044a091        int32_t ebp_2
0044a091        ebp_2.w = *(eax + 0xc)
0044a099        ebp = 0
0044a0a1        float var_20c_3 = fconvert.s(float.t(var_210) + fconvert.t(0.5f))
0044a0ad        *(eax_13 + &data_777504) = fconvert.s(fconvert.t(var_20c_3) / float.t(ebp_2))
0044a0b3        *(eax_13 + 0x777904) = 0
0044a0bf        if (*(eax + 0xc) == 0x800)
0044a0c7        if (ecx_3 s<= ebx)
0044a128        *(eax_13 + 0x777304) = fconvert.s(fconvert.t(var_208_1) * fconvert.t(0.0009765625f))
0044a12e        ecx_3.w = *(eax + 0xc)
0044a132        ecx_3.w u>>= 1
0044a147        *(eax_13 + &data_777504) = fconvert.s(fconvert.t(var_20c_3) / float.t(ecx_3 & 0xffff))
0044a14d        *(eax_13 + 0x777904) = 0
0044a0e7        *(eax_13 + 0x777304) = fconvert.s((float.t(ecx_3 - ebx) + fconvert.t(0.5f)) * fconvert.t(0.0009765625f))
0044a0ed        int32_t ecx_6
0044a0ed        ecx_6.w = *(eax + 0xc)
0044a0f5        ecx_6.w u>>= 1
0044a10c        *(eax_13 + &data_777504) = fconvert.s((float.t(edi_1 - ebx) + fconvert.t(0.5f)) / float.t(ecx_6 & 0xffff))
0044a112        *(eax_13 + 0x777904) = 1
0044a158        bool cond:3_1 = var_204 != 0x7f
0044a15d        var_204 += 1
0044a161        if (not(cond:3_1))
0044a168        report_errorf("Too many Font letters increase RFONT_LETTERS_MAX in font.h")
0044a16d        edx_1 = data_777b20
0044a178        ebp += 1
0044a179        eax_16.w = *(eax + 0xc)
0044a17d        edi_1 += 1
0044a180        var_20c = ebp
0044a184        var_210 = edi_1
0044a188        do while (edi_1 s< eax_16)
0044a196        int32_t edi_2 = 1
0044a19f        int32_t var_208_2 = 1
0044a1a3        if (*(eax + 0xe) u> 1)
0044a1a9        while (true)
0044a1b6        if (sub_44e780(eax, 0, edi_2) == 0xffffff)
0044a1cf        edx_1 = data_777b20
0044a1e7        *(edx_1 * 0x828 + &data_777b04) = fconvert.s(float.t(edi_2))
0044a1e7        break
0044a1ba        edi_2 += 1
0044a1bb        int32_t ecx_9
0044a1bb        ecx_9.w = *(eax + 0xe)
0044a1c1        if (edi_2 s>= ecx_9)
0044a1c3        edx_1 = data_777b20
0044a1c9        int32_t var_208_3 = edi_2
0044a1cd        break
0044a1f2        int32_t ecx_11
0044a1f2        ecx_11.w = *(eax + 0xe)
0044a204        int32_t eax_25 = edx_1 * 0x828
0044a21a        *(eax_25 + 0x777b08) = fconvert.s(fconvert.t(3f) / float.t(ecx_11 - 1))
0044a220        int32_t edx_2
0044a220        edx_2.w = *(eax + 0xe)
0044a23a        *(eax_25 + 0x777b0c) = fconvert.s(fconvert.t(*(eax_25 + &data_777b04)) / float.t(edx_2 - 1))
0044a240        *(eax_25 + 0x7772f8) = var_204
0044a246        *(eax_25 + &data_777b1c) = arg2
0044a252        struct TextureRef* eax_27
0044a252        int32_t ecx_19
0044a252        if (*(eax + 0xc) != 0x800)
0044a2c8        eax_27 = get_or_create_texture_ref(&data_4b7790, arg1, 0, 0)
0044a2dd        *(data_777b20 * 0x828 + &data_7772fc) = eax_27
0044a2e6        ecx_19:1.b = eax_27->__offset(0x0).d:1.b | 4
0044a25e        struct TextureRef* eax_26 = get_or_create_texture_ref(&data_4b7790, &texture_path, 0, 0)
0044a277        *(data_777b20 * 0x828 + &data_7772fc) = eax_26
0044a28b        eax_26->__offset(0x0).d |= 0x420
0044a295        eax_27 = get_or_create_texture_ref(&data_4b7790, &texture_path_1, 0, 0)
0044a2aa        *(data_777b20 * 0x828 + &data_777300) = eax_27
0044a2b3        ecx_19 = eax_27->__offset(0x0).d | 0x420
0044a2e9        eax_27->__offset(0x0).d = ecx_19
0044a310        int32_t eax_30 = data_777b20 * 0x828
0044a313        *(eax_30 + 0x777b10) = 0x3f800000
0044a31d        *(eax_30 + 0x777b14) = arg3
0044a323        *(eax_30 + 0x777b18) = arg4
0044a32f        *(eax_30 + &data_777b04) = fconvert.s(fconvert.t(arg4) * fconvert.t(*(eax_30 + &data_777b04)))
0044a335        free_tracked_memory(eax)
0044a33a        int32_t result = data_777b20
0044a349        data_777b20 = result + 1
0044a356        return result
