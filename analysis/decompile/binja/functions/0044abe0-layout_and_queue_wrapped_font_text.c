/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: layout_and_queue_wrapped_font_text @ 0x44abe0 */

0044abe6        int32_t ebx
0044abe6        int32_t var_420 = ebx
0044ac11        int32_t var_410 = *arg15
0044ac18        int32_t var_40c = arg15[1]
0044ac1f        int32_t var_408 = arg15[2]
0044ac34        int32_t var_404 = arg15[3]
0044ac3f        float var_418 = arg4
0044ac43        float var_41c = arg5
0044ac47        char* var_414 = arg1
0044ac4b        char var_400[0x400]
0044ac4b        char (* eax_2)[0x400] = &var_400
0044ac53        ebx.b = *var_414
0044ac5c        if (ebx.b == 0x3e || ebx.b == 0)
0044ac6a        *eax_2 = 0
0044ac6f        if (eax_2 != &var_400)
0044ac7c        int32_t ecx_5
0044ac7c        long double st0_1
0044ac7c        st0_1, ecx_5 = measure_font_text_width(&var_400, arg2, arg3)
0044ac81        long double x87_r7_2 = st0_1 + fconvert.t(arg4)
0044ac8b        long double temp0_1 = fconvert.t(var_418)
0044ac8b        x87_r7_2 - temp0_1
0044ac94        if ((((x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
0044ac96        var_418 = fconvert.s(x87_r7_2)
0044ac9e        int16_t eax_3
0044ac9e        eax_3.b = arg16
0044aca7        if (eax_3.b == 0)
0044aca9        eax_3.b = arg17
0044acb2        if (eax_3.b != 0)
0044acbe        int32_t var_430_2 = ecx_5
0044acc7        float var_404_1 = fconvert.s(sine(fconvert.s(fconvert.t(var_41c) * fconvert.t(0.00654498488f))))
0044ad08        queue_font_text_instance(&var_400, arg2, arg3, arg4, var_41c, arg12, arg13, arg14, &var_410, arg10, arg11)
0044ad1a        int32_t eax_9 = arg2 * 0x828
0044ad2f        eax_2 = &var_400
0044ad3e        var_41c = fconvert.s(fconvert.t(*(eax_9 + 0x777b18)) * fconvert.t(*(eax_9 + 0x777b10)) * fconvert.t(*(eax_9 + &data_777b04)) * fconvert.t(arg3) + fconvert.t(var_41c))
0044ac5e        *eax_2 = ebx.b
0044ac60        eax_2 = &(*eax_2)[1]
0044ad49        var_414 = &var_414[1]
0044ad4d        do while (ebx.b != 0)
0044ad72        *arg6 = fconvert.s(fconvert.t(arg4))
0044ad7b        *arg7 = fconvert.s(fconvert.t(arg5))
0044ad8f        *arg8 = fconvert.s(fconvert.t(var_418) - fconvert.t(arg4))
0044ad9c        *arg9 = fconvert.s(fconvert.t(var_41c) - fconvert.t(arg5))
0044ad9e        if (arg12 == 1)
0044adb1        *arg6 = fconvert.s(fconvert.t(arg13) + fconvert.t(320f))
0044adb9        return arg6
0044adbd        if (arg12 == 3)
0044add2        *arg6 = fconvert.s(fconvert.t(arg13) + fconvert.t(320f) - fconvert.t(*arg8))
0044adda        return arg6
0044adde        if (arg12 == 2)
0044adf7        *arg6 = fconvert.s(fconvert.t(arg13) + fconvert.t(320f) - fconvert.t(*arg8) * fconvert.t(0.5f))
0044ae03        return arg6
