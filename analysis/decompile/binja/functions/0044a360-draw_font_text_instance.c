/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_font_text_instance @ 0x44a360 */

0044a365        float esi = arg1
0044a36c        arg1 = *(esi i+ 4)
0044a370        int32_t result = *(esi i+ 0x48)
0044a376        if (result == 2)
0044a384        long double st0_1
0044a384        st0_1, result = measure_font_text_width(*(esi i+ 0x44), *(esi i+ 0x3c), *(esi i+ 0x40))
0044a39f        arg1 = fconvert.s(fconvert.t(*(esi i+ 0x4c)) + fconvert.t(320f) - st0_1 * fconvert.t(0.5f))
0044a3a8        if (result == 1)
0044a3b6        int80_t st0_2
0044a3b6        st0_2, result = measure_font_text_width(*(esi i+ 0x44), *(esi i+ 0x3c), *(esi i+ 0x40))
0044a3c9        arg1 = fconvert.s(fconvert.t(*(esi i+ 0x4c)) + fconvert.t(320f))
0044a3d2        if (result == 3)
0044a3e0        long double st0_3
0044a3e0        st0_3, result = measure_font_text_width(*(esi i+ 0x44), *(esi i+ 0x3c), *(esi i+ 0x40))
0044a3f3        arg1 = fconvert.s(fconvert.t(*(esi i+ 0x4c)) + fconvert.t(320f) - st0_3)
0044a3f9        char* ebx = *(esi i+ 0x44)
0044a3fc        float var_38 = 0f
0044a404        char* var_14 = ebx
0044a408        result.b = *ebx
0044a40c        while (result.b != 0)
0044a415        int32_t eax_4 = font_slot_index_for_char(result.b)
0044a41c        int32_t eax_5 = *(esi i+ 0x3c)
0044a437        int32_t ecx_8 = (eax_4 + eax_5 * 0x20a) << 2
0044a43a        float edx_5 = *(ecx_8 + 0x777304)
0044a444        float edx_6 = *(ecx_8 + &data_777504)
0044a455        int32_t ecx_9 = *(ecx_8 + 0x777904)
0044a465        int32_t eax_7 = eax_5 * 0x828
0044a468        float edx_10 = *(eax_7 + 0x777b08)
0044a46e        float eax_8 = *(eax_7 + 0x777b0c)
0044a481        long double x87_r7_13 = sine(fconvert.s(fconvert.t(data_7772e8) + fconvert.t(var_38))) * fconvert.t(*(esi i+ 0x34))
0044a49d        int16_t x87control_1
0044a49d        long double st0_5
0044a49d        st0_5, x87control_1 = cosine(fconvert.s(fconvert.t(var_38) * fconvert.t(3f) + fconvert.t(data_7772e8)))
0044a4a8        long double x87_r7_20 = st0_5 * fconvert.t(*(esi i+ 0x34)) * fconvert.t(4f)
0044a4b8        var_38 = fconvert.s(fconvert.t(var_38) + fconvert.t(1f))
0044a4c4        int32_t eax_9
0044a4c4        int16_t x87control_2
0044a4c4        eax_9, x87control_2 = __ftol(x87control_1, fconvert.t(fconvert.s(x87_r7_13 + x87_r7_13)) + fconvert.t(arg1))
0044a4d1        float var_1c_3 = fconvert.s(float.t(eax_9))
0044a4d8        int32_t eax_10
0044a4d8        int16_t x87control_3
0044a4d8        eax_10, x87control_3 = __ftol(x87control_2, x87_r7_20 + fconvert.t(*(esi i+ 8)))
0044a4e8        float var_20_2 = fconvert.s(float.t(eax_10))
0044a4ec        if (eax_4 != 0x35)
0044a4f2        eax_10.b = *(esi i+ 0x38)
0044a4f7        if (eax_10.b != 0 && *(*(esi i+ 0x3c) * 0x828 + &data_777b1c) s> 0)
0044a519        int32_t eax_13 = *(esi i+ 0x3c)
0044a531        int32_t edi_2 = eax_13 * 0x828
0044a54c        float var_34_1 = fconvert.s(float.t(*(edi_2 + &data_777b1c)))
0044a550        int32_t ebx_2 = eax_13 * 0x20a
0044a552        struct Color4f color
0044a552        struct Color4f* eax_14 = set_color_rgba(&color, 0f, 0f, 0f, 0.800000012f)
0044a57b        float var_68_1 = edx_6
0044a57c        int32_t ecx_16 = ebx_2 + eax_4
0044a590        int32_t var_6c_1 = ecx_16
0044a5b7        int32_t var_88_1 = ecx_16
0044a5c3        int32_t var_8c_1 = ecx_16
0044a5c8        draw_textured_quad_immediate(*(((ebx_2 + ecx_9) << 2) + &data_7772fc), fconvert.s(fconvert.t(var_34_1) + fconvert.t(var_1c_3)), fconvert.s(fconvert.t(var_34_1) + fconvert.t(var_20_2)), 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(*((ecx_16 << 2) + &data_777704)) * fconvert.t(*(esi i+ 0x40)) * fconvert.t(*(edi_2 + 0x777b10))), fconvert.s(fconvert.t(*(edi_2 + &data_777b04)) * fconvert.t(*(esi i+ 0x40)) * fconvert.t(*(edi_2 + 0x777b10))), edx_5, edx_10, edx_6, eax_8, eax_14, 2, 0f)
0044a5cd        ebx = var_14
0044a5d4        int32_t eax_18 = *(esi i+ 0x3c)
0044a5f7        int32_t ecx_21 = eax_18 * 0x828
0044a618        int32_t eax_20 = eax_18 * 0x20a
0044a61b        int32_t var_68_3 = ecx_21
0044a62c        int32_t var_6c_3 = ecx_21
0044a65a        x87control_3 = draw_textured_quad_immediate(*(((eax_20 + ecx_9) << 2) + &data_7772fc), var_1c_3, var_20_2, 0f, 0f, 0f, 0f, 0f, 0f, fconvert.s(fconvert.t(*(((eax_20 + eax_4) << 2) + &data_777704)) * fconvert.t(*(esi i+ 0x40)) * fconvert.t(*(ecx_21 + 0x777b10))), fconvert.s(fconvert.t(*(ecx_21 + &data_777b04)) * fconvert.t(*(esi i+ 0x40)) * fconvert.t(*(ecx_21 + 0x777b10))), edx_5, edx_10, edx_6, eax_8, esi i+ 0x6c, 1, 0f)
0044a662        int32_t eax_22 = *(esi i+ 0x3c)
0044a679        int32_t edi_4 = eax_22 * 0x828
0044a68c        int32_t var_14_1 = __ftol(x87control_3, fconvert.t(*(((eax_4 + eax_22 * 0x20a) << 2) + &data_777704)))
0044a690        result.b = ebx[1]
0044a697        ebx = &ebx[1]
0044a6a0        var_14 = ebx
0044a6b1        arg1 = fconvert.s(float.t(var_14_1) * fconvert.t(*(edi_4 + 0x777b14)) * fconvert.t(*(edi_4 + 0x777b10)) * fconvert.t(*(esi i+ 0x40)) + fconvert.t(arg1))
0044a6c2        return result
