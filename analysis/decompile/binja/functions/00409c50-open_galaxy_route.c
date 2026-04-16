/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: open_galaxy_route @ 0x409c50 */

00409c50        float eax_32 = arg2
00409c5a        void* ecx = *(arg1 + 0x10f90)
00409c60        *(arg1 + 8) = 1
00409c67        *(arg1 + 0x10f80) = eax_32
00409c6d        unhide_border_init(ecx)
00409ca6        sub_44e5b0(*(arg1 + 0x10f90) + 0x2cc, *(*(arg1 + 0x10f80) * 0x2a0 + arg1 + 0x14) * 0xa0 + arg1 + 0x10930)
00409cd3        *(*(arg1 + 0x10f90) + 0x6f4) = fconvert.s(fconvert.t(*(*(arg1 + 0x10f80) * 0x2a0 + arg1 + 0x1c)) + fconvert.t(60f))
00409cfe        *(*(arg1 + 0x10f90) + 0x6f8) = fconvert.s(fconvert.t(*(*(arg1 + 0x10f80) * 0x2a0 + arg1 + 0x20)) - fconvert.t(130f))
00409d0a        float var_c
00409d0a        float var_8
00409d0a        float var_4
00409d0a        while (true)
00409d0a        layout_frontend_widget(*(arg1 + 0x10f90))
00409d15        unhide_border_init(*(arg1 + 0x10f94))
00409d41        sub_44e5b0(*(arg1 + 0x10f94) + 0x2cc, *(arg1 + 0x10f80) * 0x2a0 + arg1 + 0x30)
00409d56        stack_widget_below(*(arg1 + 0x10f94), *(arg1 + 0x10f90))
00409d61        unhide_border_init(*(arg1 + 0x10f98))
00409d8f        sub_44e5b0(*(arg1 + 0x10f98) + 0x2cc, *(arg1 + 0x10f80) * 0x2a0 + arg1 + 0xb0)
00409da4        stack_widget_below(*(arg1 + 0x10f98), *(arg1 + 0x10f94))
00409daf        unhide_border_init(*(arg1 + 0x10f9c))
00409db4        void* eax_18 = *(arg1 + 0x10f90)
00409dd8        *(*(arg1 + 0x10f9c) + 0x260) = fconvert.s(fconvert.t(*(eax_18 + 0x248)) * fconvert.t(0.5f) + fconvert.t(*(eax_18 + 0x238)) - fconvert.t(320f))
00409deb        stack_widget_below(*(arg1 + 0x10f9c), *(arg1 + 0x10f98))
00409e1d        if (*(*(arg1 + 0x10f80) * 0x1fac0 + *(arg1 + 0x10f70) + 0x944150) != 1 || *(arg1 + 4) != 2)
00409e80        hide_border_init(*(arg1 + 0x10fa0))
00409e25        unhide_border_init(*(arg1 + 0x10fa0))
00409e2a        void* eax_22 = *(arg1 + 0x10f90)
00409e4e        *(*(arg1 + 0x10fa0) + 0x260) = fconvert.s(fconvert.t(*(eax_22 + 0x248)) * fconvert.t(0.5f) + fconvert.t(*(eax_22 + 0x238)) - fconvert.t(320f))
00409e61        stack_widget_below(*(arg1 + 0x10fa0), *(arg1 + 0x10f98))
00409e73        stack_widget_below(*(arg1 + 0x10f9c), *(arg1 + 0x10fa0))
00409e8b        unhide_border_init(*(arg1 + 0x10f8c))
00409e90        void* ecx_33 = *(arg1 + 0x10f90)
00409ead        var_8 = 1000f
00409eb5        arg2 = -1000f
00409ebd        var_4 = 1000f
00409ec5        var_c = -1000f
00409ecd        galaxy_border_bound(&var_8, &arg2, &var_4, &var_c, ecx_33)
00409eef        galaxy_border_bound(&var_8, &arg2, &var_4, &var_c, *(arg1 + 0x10f94))
00409f11        galaxy_border_bound(&var_8, &arg2, &var_4, &var_c, *(arg1 + 0x10f98))
00409f33        galaxy_border_bound(&var_8, &arg2, &var_4, &var_c, *(arg1 + 0x10f9c))
00409f42        var_c = fconvert.s(fconvert.t(var_c) + fconvert.t(8f))
00409f50        var_8 = fconvert.s(fconvert.t(var_8) - fconvert.t(8f))
00409f58        long double x87_r7_17 = fconvert.t(arg2) + fconvert.t(8f)
00409f5e        arg2 = fconvert.s(x87_r7_17)
00409f62        long double temp1_1 = fconvert.t(630f)
00409f62        x87_r7_17 - temp1_1
00409f68        float eax_25
00409f68        eax_25.w = (x87_r7_17 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp1_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp1_1 ? 1 : 0) << 0xe
00409f6d        if ((eax_25:1.b & 0x41) == 0)
00409f9c        *(*(arg1 + 0x10f90) + 0x6f4) = fconvert.s(fconvert.t(*(*(arg1 + 0x10f80) * 0x2a0 i+ arg1 + 0x1c)) - (fconvert.t(arg2) - fconvert.t(var_8)) - fconvert.t(40f))
00409fa2        long double x87_r7_22 = fconvert.t(var_4)
00409fa6        long double temp2_1 = fconvert.t(50f)
00409fa6        x87_r7_22 - temp2_1
00409fac        eax_25.w = (x87_r7_22 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp2_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp2_1 ? 1 : 0) << 0xe
00409fb1        if ((eax_25:1.b & 1) != 0)
00409fb9        *(*(arg1 + 0x10f90) + 0x6f8) = 0x42480000
00409fc3        long double x87_r7_23 = fconvert.t(var_c)
00409fc7        long double temp3_1 = fconvert.t(450f)
00409fc7        x87_r7_23 - temp3_1
00409fcd        eax_25.w = (x87_r7_23 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp3_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp3_1 ? 1 : 0) << 0xe
00409fd2        if ((eax_25:1.b & 0x41) == 0)
00409fe8        *(*(arg1 + 0x10f90) i+ 0x6f8) = fconvert.s(fconvert.t(450f) - (fconvert.t(var_c) - fconvert.t(var_4)))
00409fee        long double x87_r7_27 = fconvert.t(arg2)
00409ff2        long double temp4_1 = fconvert.t(631f)
00409ff2        x87_r7_27 - temp4_1
00409ff8        eax_25.w = (x87_r7_27 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_27, temp4_1) ? 1 : 0) << 0xa | (x87_r7_27 == temp4_1 ? 1 : 0) << 0xe
00409ffd        if ((eax_25:1.b & 0x41) != 0)
0040a003        long double x87_r7_28 = fconvert.t(var_4)
0040a007        long double temp5_1 = fconvert.t(49f)
0040a007        x87_r7_28 - temp5_1
0040a00d        eax_25.w = (x87_r7_28 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp5_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp5_1 ? 1 : 0) << 0xe
0040a012        if ((eax_25:1.b & 1) == 0)
0040a018        long double x87_r7_29 = fconvert.t(var_c)
0040a01c        long double temp6_1 = fconvert.t(451f)
0040a01c        x87_r7_29 - temp6_1
0040a022        eax_25.w = (x87_r7_29 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp6_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp6_1 ? 1 : 0) << 0xe
0040a027        if ((eax_25:1.b & 0x41) != 0)
0040a027        break
0040a03b        *(*(arg1 + 0x10f8c) + 0x54) = fconvert.s(fconvert.t(arg2) - fconvert.t(var_8))
0040a04c        *(*(arg1 + 0x10f8c) + 0x58) = fconvert.s(fconvert.t(var_c) - fconvert.t(var_4))
0040a059        *(*(arg1 + 0x10f8c) + 0x4c) = var_8
0040a066        *(*(arg1 + 0x10f8c) + 0x50) = var_4
0040a069        void* eax_31 = *(arg1 + 0x10f8c)
0040a087        *(*(arg1 + 0x10f9c) + 0x260) = fconvert.s(fconvert.t(*(eax_31 + 0x54)) * fconvert.t(0.5f) + fconvert.t(*(eax_31 + 0x4c)) - fconvert.t(320f))
0040a08d        void* result = *(arg1 + 0x10f8c)
0040a0ac        *(*(arg1 + 0x10fa0) + 0x260) = fconvert.s(fconvert.t(*(result + 0x54)) * fconvert.t(0.5f) + fconvert.t(*(result + 0x4c)) - fconvert.t(320f))
0040a0b5        return result
