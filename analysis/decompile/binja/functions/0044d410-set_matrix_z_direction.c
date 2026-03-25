/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_matrix_z_direction @ 0x44d410 */

0044d423        float lhs
0044d423        long double st0 = normalize_vector_from_source(&lhs, arg2)
0044d428        long double temp1 = fconvert.t(0f)
0044d428        st0 - temp1
0044d42e        int16_t result = (st0 < temp1 ? 1 : 0) << 8 | (is_unordered.t(st0, temp1) ? 1 : 0) << 0xa | (st0 == temp1 ? 1 : 0) << 0xe
0044d433        if ((result:1.b & 0x40) != 0)
0044d4d1        return result
0044d439        long double x87_r7_1 = fconvert.t(lhs)
0044d43d        long double temp2_1 = fconvert.t(0f)
0044d43d        x87_r7_1 - temp2_1
0044d447        float lhs_1 = lhs
0044d44f        float var_4
0044d44f        arg1[0xa] = var_4
0044d452        arg1[8] = lhs_1
0044d455        int32_t var_8
0044d455        arg1[9] = var_8
0044d458        float eax
0044d458        eax.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0044d45d        struct Vec3 var_18
0044d45d        if ((eax:1.b & 0x40) == 0)
0044d48c        var_18.z = fconvert.s(fneg(fconvert.t(lhs)))
0044d490        var_18.x = var_4
0044d45f        long double x87_r7_2 = fconvert.t(var_4)
0044d463        long double temp3_1 = fconvert.t(0f)
0044d463        x87_r7_2 - temp3_1
0044d469        eax.w = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
0044d46e        if ((eax:1.b & 0x40) == 0)
0044d48c        var_18.z = fconvert.s(fneg(fconvert.t(lhs)))
0044d490        var_18.x = var_4
0044d470        var_18.x = 0x3f800000
0044d478        var_18.z = 0
0044d498        var_18.y = 0
0044d4a0        normalize_vector(&var_18)
0044d4a9        float y = var_18.y
0044d4ad        float z = var_18.z
0044d4b1        *arg1 = var_18.x
0044d4b3        arg1[1] = y
0044d4be        arg1[2] = z
0044d4c7        return cross_vectors(&arg1[4], &lhs, &var_18)
