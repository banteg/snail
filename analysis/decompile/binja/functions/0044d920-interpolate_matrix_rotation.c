/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: interpolate_matrix_rotation @ 0x44d920 */

0044d93e        struct Quaternion out
0044d93e        initialize_quaternion_from_matrix(&out, transform)
0044d943        long double x87_r7 = fconvert.t(out.x)
0044d94f        long double temp1 = fconvert.t(-0.00100000005f)
0044d94f        x87_r7 - temp1
0044d959        struct Quaternion var_70
0044d959        var_70.x = out.x
0044d961        var_70.y = out.y
0044d965        var_70.w = out.w
0044d969        var_70.z = out.z
0044d972        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d974        long double x87_r7_1 = fconvert.t(out.x)
0044d978        long double temp3_1 = fconvert.t(0.00100000005f)
0044d978        x87_r7_1 - temp3_1
0044d983        if ((((x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d985        var_70.x = 0
0044d98d        long double x87_r7_2 = fconvert.t(var_70.y)
0044d991        long double temp2 = fconvert.t(-0.00100000005f)
0044d991        x87_r7_2 - temp2
0044d99c        if ((((x87_r7_2 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2) ? 1 : 0) << 0xa | (x87_r7_2 == temp2 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d99e        long double x87_r7_3 = fconvert.t(var_70.y)
0044d9a2        long double temp5_1 = fconvert.t(0.00100000005f)
0044d9a2        x87_r7_3 - temp5_1
0044d9ad        if ((((x87_r7_3 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp5_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d9af        var_70.y = 0
0044d9b7        long double x87_r7_4 = fconvert.t(var_70.z)
0044d9bb        long double temp4 = fconvert.t(-0.00100000005f)
0044d9bb        x87_r7_4 - temp4
0044d9c6        if ((((x87_r7_4 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4) ? 1 : 0) << 0xa | (x87_r7_4 == temp4 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d9c8        long double x87_r7_5 = fconvert.t(var_70.z)
0044d9cc        long double temp7_1 = fconvert.t(0.00100000005f)
0044d9cc        x87_r7_5 - temp7_1
0044d9d7        if ((((x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d9d9        var_70.z = 0
0044d9e1        long double x87_r7_6 = fconvert.t(var_70.x)
0044d9e5        long double temp6 = fconvert.t(0f)
0044d9e5        x87_r7_6 - temp6
0044d9f0        struct TransformMatrix out_1
0044d9f0        if ((((x87_r7_6 < temp6 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp6) ? 1 : 0) << 0xa | (x87_r7_6 == temp6 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044d9f2        long double x87_r7_7 = fconvert.t(var_70.y)
0044d9f6        long double temp9_1 = fconvert.t(0f)
0044d9f6        x87_r7_7 - temp9_1
0044da01        if ((((x87_r7_7 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp9_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044da03        long double x87_r7_8 = fconvert.t(var_70.z)
0044da07        long double temp10_1 = fconvert.t(0f)
0044da07        x87_r7_8 - temp10_1
0044da12        if ((((x87_r7_8 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp10_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp10_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044da1d        initialize_matrix_from_quaternion(&out_1, &var_70)
0044da2b        __builtin_memcpy(transform, &out_1, 0x40)
0044da32        return
0044da3e        struct AxisAngle var_50
0044da3e        initialize_axis_from_quaternion(&var_50, &var_70)
0044da43        long double x87_r7_9 = fconvert.t(var_50.angle)
0044da47        long double temp8 = fconvert.t(0f)
0044da47        x87_r7_9 - temp8
0044da52        if ((((x87_r7_9 < temp8 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp8) ? 1 : 0) << 0xa | (x87_r7_9 == temp8 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0044da52        return
0044da65        var_50.angle = fconvert.s(fconvert.t(var_50.angle) * fconvert.t(alpha))
0044da69        initialize_quaternion_from_axis(&var_70, &var_50)
0044da77        initialize_matrix_from_quaternion(&out_1, &var_70)
0044da85        __builtin_memcpy(transform, &out_1, 0x40)
0044da8c        return
