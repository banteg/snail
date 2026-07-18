/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_quaternion_from_matrix @ 0x44d5d0 */

0044d5d0        int32_t __saved_esi_1
0044d5d0        int32_t __saved_esi = __saved_esi_1
0044d5d1        struct TransformMatrix* matrix_4 = matrix
0044d5d5        int32_t __saved_edi_1
0044d5d5        int32_t __saved_edi = __saved_edi_1
0044d5e0        long double x87_r7_3 = fconvert.t(matrix_4->basis_up.y) + fconvert.t(matrix_4->basis_right.x) + fconvert.t(matrix_4->basis_forward.z) + fconvert.t(1f)
0044d5ea        long double temp1 = fconvert.t(9.99999997e-07f)
0044d5ea        x87_r7_3 - temp1
0044d5f5        if ((((x87_r7_3 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d5fb        struct TransformMatrix* var_c = fconvert.s(x87_r7_3)
0044d601        long double x87_r7_5 = fconvert.t(0.5f) / square_root()
0044d614        out->w = fconvert.s(fconvert.t(0.25f) / x87_r7_5)
0044d61f        out->x = fconvert.s((fconvert.t(matrix_4->basis_up.z) - fconvert.t(matrix_4->basis_forward.y)) * x87_r7_5)
0044d629        out->y = fconvert.s((fconvert.t(matrix_4->basis_forward.x) - fconvert.t(matrix_4->basis_right.z)) * x87_r7_5)
0044d634        out->z = fconvert.s((fconvert.t(matrix_4->basis_right.y) - fconvert.t(matrix_4->basis_up.x)) * x87_r7_5)
0044d63b        return out
0044d63e        long double x87_r7_7 = fconvert.t(matrix_4->basis_right.x)
0044d640        long double temp2 = fconvert.t(matrix_4->basis_up.y)
0044d640        x87_r7_7 - temp2
0044d648        if ((((x87_r7_7 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2) ? 1 : 0) << 0xa | (x87_r7_7 == temp2 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044d64e        long double x87_r7_8 = fconvert.t(matrix_4->basis_right.x)
0044d650        long double temp4_1 = fconvert.t(matrix_4->basis_forward.z)
0044d650        x87_r7_8 - temp4_1
0044d658        if ((((x87_r7_8 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp4_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d71c        label_44d71c:
0044d71c        long double x87_r7_23 = fconvert.t(matrix_4->basis_right.x) + fconvert.t(1f) - fconvert.t(matrix_4->basis_up.y) - fconvert.t(matrix_4->basis_forward.z)
0044d71f        matrix = fconvert.s(x87_r7_23)
0044d723        long double temp7 = fconvert.t(0f)
0044d723        x87_r7_23 - temp7
0044d72e        if ((((x87_r7_23 < temp7 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp7) ? 1 : 0) << 0xa | (x87_r7_23 == temp7 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d73a        char* var_14_2 = "ERROR:sqrt %f\n"
0044d747        matrix = nullptr
0044d753        struct TransformMatrix* matrix_2 = matrix
0044d754        long double st0_2 = square_root()
0044d759        long double x87_r7_26 = st0_2 + st0_2
0044d768        out->x = fconvert.s(x87_r7_26 * fconvert.t(0.25f))
0044d772        out->y = fconvert.s((fconvert.t(matrix_4->basis_up.x) + fconvert.t(matrix_4->basis_right.y)) / x87_r7_26)
0044d77d        out->z = fconvert.s((fconvert.t(matrix_4->basis_forward.x) + fconvert.t(matrix_4->basis_right.z)) / x87_r7_26)
0044d788        out->w = fconvert.s((fconvert.t(matrix_4->basis_forward.y) + fconvert.t(matrix_4->basis_up.z)) / x87_r7_26)
0044d78f        return out
0044d65e        long double x87_r7_9 = fconvert.t(matrix_4->basis_up.y)
0044d661        long double temp8_1 = fconvert.t(matrix_4->basis_forward.z)
0044d661        x87_r7_9 - temp8_1
0044d669        if ((((x87_r7_9 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp8_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d669        goto label_44d79d
0044d669        goto label_44d67a
0044d6f0        long double x87_r7_18 = fconvert.t(matrix_4->basis_up.y)
0044d6f3        long double temp3_1 = fconvert.t(matrix_4->basis_forward.z)
0044d6f3        x87_r7_18 - temp3_1
0044d6fb        if ((((x87_r7_18 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_18, temp3_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0044d79d        label_44d79d:
0044d79d        long double x87_r7_31 = fconvert.t(matrix_4->basis_up.y) + fconvert.t(1f) - fconvert.t(matrix_4->basis_right.x) - fconvert.t(matrix_4->basis_forward.z)
0044d7a0        matrix = fconvert.s(x87_r7_31)
0044d7a4        long double temp5 = fconvert.t(0f)
0044d7a4        x87_r7_31 - temp5
0044d7af        if ((((x87_r7_31 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp5) ? 1 : 0) << 0xa | (x87_r7_31 == temp5 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d7bb        char* var_14_3 = "ERROR:sqt %f\n"
0044d7c8        matrix = nullptr
0044d7d4        struct TransformMatrix* matrix_3 = matrix
0044d7d5        long double st0_3 = square_root()
0044d7da        long double x87_r7_34 = st0_3 + st0_3
0044d7e9        out->x = fconvert.s((fconvert.t(matrix_4->basis_up.x) + fconvert.t(matrix_4->basis_right.y)) / x87_r7_34)
0044d7f3        out->y = fconvert.s(x87_r7_34 * fconvert.t(0.25f))
0044d7fe        out->z = fconvert.s((fconvert.t(matrix_4->basis_forward.y) + fconvert.t(matrix_4->basis_up.z)) / x87_r7_34)
0044d809        out->w = fconvert.s((fconvert.t(matrix_4->basis_forward.x) + fconvert.t(matrix_4->basis_right.z)) / x87_r7_34)
0044d810        return out
0044d701        long double x87_r7_19 = fconvert.t(matrix_4->basis_right.x)
0044d703        long double temp6_1 = fconvert.t(matrix_4->basis_forward.z)
0044d703        x87_r7_19 - temp6_1
0044d70b        if ((((x87_r7_19 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp6_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044d70b        goto label_44d71c
0044d67a        label_44d67a:
0044d67a        long double x87_r7_13 = fconvert.t(matrix_4->basis_forward.z) + fconvert.t(1f) - fconvert.t(matrix_4->basis_right.x) - fconvert.t(matrix_4->basis_up.y)
0044d67d        matrix = fconvert.s(x87_r7_13)
0044d681        long double temp9 = fconvert.t(0f)
0044d681        x87_r7_13 - temp9
0044d68c        if ((((x87_r7_13 < temp9 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp9) ? 1 : 0) << 0xa | (x87_r7_13 == temp9 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044d698        char* var_14_1 = "ERROR:sqt %f\n"
0044d6a5        matrix = nullptr
0044d6b1        struct TransformMatrix* matrix_1 = matrix
0044d6b2        long double st0_1 = square_root()
0044d6b7        long double x87_r7_16 = st0_1 + st0_1
0044d6c6        out->x = fconvert.s((fconvert.t(matrix_4->basis_forward.x) + fconvert.t(matrix_4->basis_right.z)) / x87_r7_16)
0044d6d0        out->y = fconvert.s((fconvert.t(matrix_4->basis_forward.y) + fconvert.t(matrix_4->basis_up.z)) / x87_r7_16)
0044d6db        out->z = fconvert.s(x87_r7_16 * fconvert.t(0.25f))
0044d6e6        out->w = fconvert.s((fconvert.t(matrix_4->basis_up.x) + fconvert.t(matrix_4->basis_right.y)) / x87_r7_16)
0044d6ed        return out
