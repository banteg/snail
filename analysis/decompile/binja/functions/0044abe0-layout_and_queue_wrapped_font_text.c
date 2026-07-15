/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: layout_and_queue_wrapped_font_text @ 0x44abe0 */

0044abe6        int32_t ebx
0044abe6        int32_t var_420 = ebx
0044ac11        struct tColour color_1
0044ac11        color_1.r = color->r
0044ac18        color_1.g = color->g
0044ac1f        color_1.b = color->b
0044ac34        color_1.a = color->a
0044ac3f        float x_1 = x
0044ac43        float y_1 = y
0044ac47        char* text_2 = text
0044ac4b        char text_1[0x400]
0044ac4b        char (* eax_2)[0x400] = &text_1
0044ad4d        char i
0044ac53        i = *text_2
0044ac5c        if (i == 0x3e || i == 0)
0044ac6a        *eax_2 = 0
0044ac6f        if (eax_2 != &text_1)
0044ac7c        int32_t ecx_5
0044ac7c        long double st0_1
0044ac7c        st0_1, ecx_5 = measure_font_text_width(&text_1, font_id, text_scale)
0044ac81        long double x87_r7_2 = st0_1 + fconvert.t(x)
0044ac8b        long double temp0_1 = fconvert.t(x_1)
0044ac8b        x87_r7_2 - temp0_1
0044ac8f        int16_t eax_4 = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0044ac94        if ((eax_4:1.b & 0x41) == 0)
0044ac96        x_1 = fconvert.s(x87_r7_2)
0044ac9e        eax_4.b = measure_only
0044aca7        if (eax_4.b == 0)
0044aca9        eax_4.b = pulse_alpha
0044acb2        if (eax_4.b != 0)
0044acbe        int32_t var_430_2 = ecx_5
0044acc7        color_1.a = fconvert.s(sine(fconvert.s(fconvert.t(y_1) * fconvert.t(0.00654498488f))))
0044ad08        queue_font_text_instance(&text_1, font_id, text_scale, x, y_1, horizontal_align, anchor_x, flags, &color_1, text_wave_amplitude, text_wave_enabled)
0044ad2f        eax_2 = &text_1
0044ad3e        y_1 = fconvert.s(fconvert.t(g_font_sheets[font_id].height_scale) * fconvert.t(g_font_sheets[font_id].spacing_scale) * fconvert.t(g_font_sheets[font_id].line_marker_y) * fconvert.t(text_scale) + fconvert.t(y_1))
0044ac5e        *eax_2 = i
0044ac60        eax_2 = &(*eax_2)[1]
0044ad49        text_2 = &text_2[1]
0044ad4d        do while (i != 0)
0044ad72        *out_x = fconvert.s(fconvert.t(x))
0044ad7b        *out_y = fconvert.s(fconvert.t(y))
0044ad8f        *out_width = fconvert.s(fconvert.t(x_1) - fconvert.t(x))
0044ad9c        *out_height = fconvert.s(fconvert.t(y_1) - fconvert.t(y))
0044ad9e        if (horizontal_align == 1)
0044adb1        *out_x = fconvert.s(fconvert.t(anchor_x) + fconvert.t(320f))
0044adb9        return out_x
0044adbd        if (horizontal_align == 3)
0044add2        *out_x = fconvert.s(fconvert.t(anchor_x) + fconvert.t(320f) - fconvert.t(*out_width))
0044adda        return out_x
0044adde        if (horizontal_align == 2)
0044adf7        *out_x = fconvert.s(fconvert.t(anchor_x) + fconvert.t(320f) - fconvert.t(*out_width) * fconvert.t(0.5f))
0044ae03        return out_x
