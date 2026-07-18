/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_matrix_from_quaternion @ 0x44d820 */

0044d825        struct Quaternion* quaternion_1 = quaternion
0044d829        long double x87_r7 = fconvert.t(quaternion_1->x)
0044d82d        long double x87_r7_1 = x87_r7 * x87_r7
0044d832        long double x87_r6_2 = fconvert.t(quaternion_1->y) * fconvert.t(quaternion_1->x)
0044d839        float var_14 = fconvert.s(fconvert.t(quaternion_1->z) * fconvert.t(quaternion_1->x))
0044d842        float var_8 = fconvert.s(fconvert.t(quaternion_1->w) * fconvert.t(quaternion_1->x))
0044d846        long double x87_r5_4 = fconvert.t(quaternion_1->y)
0044d84d        float var_4 = fconvert.s(x87_r5_4 * x87_r5_4)
0044d859        float var_c = fconvert.s(fconvert.t(quaternion_1->z) * fconvert.t(quaternion_1->y))
0044d863        float var_10 = fconvert.s(fconvert.t(quaternion_1->w) * fconvert.t(quaternion_1->y))
0044d867        long double x87_r5_10 = fconvert.t(quaternion_1->z)
0044d86e        quaternion = fconvert.s(x87_r5_10 * x87_r5_10)
0044d877        long double x87_r5_13 = fconvert.t(quaternion_1->w) * fconvert.t(quaternion_1->z)
0044d87e        long double x87_r4_5 = fconvert.t(quaternion) + fconvert.t(var_4)
0044d88c        out->basis_right.x = fconvert.s(fconvert.t(1f) - (x87_r4_5 + x87_r4_5))
0044d890        long double x87_r4_9 = x87_r6_2 - x87_r5_13
0044d894        out->basis_up.x = fconvert.s(x87_r4_9 + x87_r4_9)
0044d89b        long double x87_r4_12 = fconvert.t(var_10) + fconvert.t(var_14)
0044d8a1        out->basis_forward.x = fconvert.s(x87_r4_12 + x87_r4_12)
0044d8a4        long double x87_r5_14 = x87_r5_13 + x87_r6_2
0044d8a8        out->basis_right.y = fconvert.s(x87_r5_14 + x87_r5_14)
0044d8b1        long double x87_r6_5 = fconvert.t(quaternion) + x87_r7_1
0044d8bb        out->basis_up.y = fconvert.s(fconvert.t(1f) - (x87_r6_5 + x87_r6_5))
0044d8c2        long double x87_r6_9 = fconvert.t(var_c) - fconvert.t(var_8)
0044d8c8        out->basis_forward.y = fconvert.s(x87_r6_9 + x87_r6_9)
0044d8cf        long double x87_r6_12 = fconvert.t(var_14) - fconvert.t(var_10)
0044d8d5        out->basis_right.z = fconvert.s(x87_r6_12 + x87_r6_12)
0044d8dc        long double x87_r6_15 = fconvert.t(var_c) + fconvert.t(var_8)
0044d8e2        out->basis_up.z = fconvert.s(x87_r6_15 + x87_r6_15)
0044d8e9        long double x87_r6_18 = fconvert.t(var_4) + x87_r7_1
0044d8f3        out->basis_forward.z = fconvert.s(fconvert.t(1f) - (x87_r6_18 + x87_r6_18))
0044d8f8        out->basis_forward_w = 0f
0044d8fb        out->basis_up_w = 0f
0044d8fe        out->basis_right_w = 0f
0044d901        out->position.z = 0f
0044d904        out->position.y = 0f
0044d907        out->position.x = 0
0044d90a        out->position_w = 1f
0044d914        return out
