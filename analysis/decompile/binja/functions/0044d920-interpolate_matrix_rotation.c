/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: interpolate_matrix_rotation @ 0x44d920 */

0044d93e        float var_60
0044d93e        initialize_quaternion_from_matrix(&var_60, transform)
0044d943        long double x87_r7 = fconvert.t(var_60)
0044d94f        long double temp1 = fconvert.t(-0.00100000005f)
0044d94f        x87_r7 - temp1
0044d959        float var_70 = var_60
0044d961        float var_5c
0044d961        float var_6c = var_5c
0044d965        int32_t var_54
0044d965        int32_t var_64 = var_54
0044d969        float var_58
0044d969        float var_68 = var_58
0044d96d        int32_t eax_1
0044d96d        eax_1.w = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
0044d972        if ((eax_1:1.b & 0x41) == 0)
0044d974        long double x87_r7_1 = fconvert.t(var_60)
0044d978        long double temp3_1 = fconvert.t(0.00100000005f)
0044d978        x87_r7_1 - temp3_1
0044d97e        eax_1.w = (x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe
0044d983        if ((eax_1:1.b & 1) != 0)
0044d985        var_70 = 0f
0044d98d        long double x87_r7_2 = fconvert.t(var_6c)
0044d991        long double temp2 = fconvert.t(-0.00100000005f)
0044d991        x87_r7_2 - temp2
0044d997        eax_1.w = (x87_r7_2 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2) ? 1 : 0) << 0xa | (x87_r7_2 == temp2 ? 1 : 0) << 0xe
0044d99c        if ((eax_1:1.b & 0x41) == 0)
0044d99e        long double x87_r7_3 = fconvert.t(var_6c)
0044d9a2        long double temp5_1 = fconvert.t(0.00100000005f)
0044d9a2        x87_r7_3 - temp5_1
0044d9a8        eax_1.w = (x87_r7_3 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp5_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp5_1 ? 1 : 0) << 0xe
0044d9ad        if ((eax_1:1.b & 1) != 0)
0044d9af        var_6c = 0f
0044d9b7        long double x87_r7_4 = fconvert.t(var_68)
0044d9bb        long double temp4 = fconvert.t(-0.00100000005f)
0044d9bb        x87_r7_4 - temp4
0044d9c1        eax_1.w = (x87_r7_4 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4) ? 1 : 0) << 0xa | (x87_r7_4 == temp4 ? 1 : 0) << 0xe
0044d9c6        if ((eax_1:1.b & 0x41) == 0)
0044d9c8        long double x87_r7_5 = fconvert.t(var_68)
0044d9cc        long double temp7_1 = fconvert.t(0.00100000005f)
0044d9cc        x87_r7_5 - temp7_1
0044d9d2        eax_1.w = (x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe
0044d9d7        if ((eax_1:1.b & 1) != 0)
0044d9d9        var_68 = 0f
0044d9e1        long double x87_r7_6 = fconvert.t(var_70)
0044d9e5        long double temp6 = fconvert.t(0f)
0044d9e5        x87_r7_6 - temp6
0044d9eb        eax_1.w = (x87_r7_6 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp6) ? 1 : 0) << 0xa | (x87_r7_6 == temp6 ? 1 : 0) << 0xe
0044d9f0        float var_40[0x10]
0044d9f0        if ((eax_1:1.b & 0x40) != 0)
0044d9f2        long double x87_r7_7 = fconvert.t(var_6c)
0044d9f6        long double temp9_1 = fconvert.t(0f)
0044d9f6        x87_r7_7 - temp9_1
0044d9fc        eax_1.w = (x87_r7_7 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp9_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp9_1 ? 1 : 0) << 0xe
0044da01        if ((eax_1:1.b & 0x40) != 0)
0044da03        long double x87_r7_8 = fconvert.t(var_68)
0044da07        long double temp10_1 = fconvert.t(0f)
0044da07        x87_r7_8 - temp10_1
0044da0d        eax_1.w = (x87_r7_8 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp10_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp10_1 ? 1 : 0) << 0xe
0044da12        if ((eax_1:1.b & 0x40) != 0)
0044da1d        float* eax_2 = initialize_matrix_from_quaternion(&var_40, &var_70)
0044da2b        __builtin_memcpy(transform, &var_40, 0x40)
0044da32        return eax_2
0044da3e        float var_50
0044da3e        initialize_axis_from_quaternion(&var_50, &var_70)
0044da43        float var_44
0044da43        long double x87_r7_9 = fconvert.t(var_44)
0044da47        long double temp8 = fconvert.t(0f)
0044da47        x87_r7_9 - temp8
0044da4d        float* eax_3
0044da4d        eax_3.w = (x87_r7_9 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp8) ? 1 : 0) << 0xa | (x87_r7_9 == temp8 ? 1 : 0) << 0xe
0044da52        if ((eax_3:1.b & 0x40) == 0)
0044da65        float var_44_1 = fconvert.s(fconvert.t(var_44) * fconvert.t(alpha))
0044da69        initialize_quaternion_from_axis(&var_70, &var_50)
0044da77        eax_3 = initialize_matrix_from_quaternion(&var_40, &var_70)
0044da85        __builtin_memcpy(transform, &var_40, 0x40)
0044da8c        return eax_3
