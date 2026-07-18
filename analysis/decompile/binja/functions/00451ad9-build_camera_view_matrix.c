/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_camera_view_matrix @ 0x451ad9 */

00451aec        float var_10 = fconvert.s(fconvert.t(eye->x) - fconvert.t(target->x))
00451af5        float var_c = fconvert.s(fconvert.t(eye->y) - fconvert.t(target->y))
00451b06        float var_8 = fconvert.s(fconvert.t(eye->z) - fconvert.t(target->z))
00451b09        j_sub_44ebb4(&var_10, &var_10)
00451b25        float var_28 = fconvert.s(fconvert.t(var_8) * fconvert.t(up->y) - fconvert.t(var_c) * fconvert.t(up->z))
00451b35        float var_24 = fconvert.s(fconvert.t(var_10) * fconvert.t(up->z) - fconvert.t(var_8) * fconvert.t(up->x))
00451b4d        float var_20 = fconvert.s(fconvert.t(var_c) * fconvert.t(up->x) - fconvert.t(var_10) * fconvert.t(up->y))
00451b50        float var_1c = var_28
00451b50        float var_18
00451b50        float* edi = &var_18
00451b50        float* esi = &var_24
00451b51        *edi = *esi
00451b52        edi[1] = esi[1]
00451b53        j_sub_44ebb4(&var_1c, &var_1c)
00451b64        matrix->basis_up.x = var_18
00451b70        float var_14
00451b70        matrix->basis_forward.x = var_14
00451b73        long double x87_r7_17 = fconvert.t(var_c) * fconvert.t(var_14) - fconvert.t(var_8) * fconvert.t(var_18)
00451b81        long double x87_r6_10 = fconvert.t(var_8) * fconvert.t(var_1c) - fconvert.t(var_10) * fconvert.t(var_14)
00451b8f        long double x87_r5_4 = fconvert.t(var_10) * fconvert.t(var_18) - fconvert.t(var_c) * fconvert.t(var_1c)
00451b94        matrix->basis_right.x = fconvert.s(fconvert.t(var_1c))
00451bad        matrix->position.x = fconvert.s(fneg(fconvert.t(var_1c) * fconvert.t(eye->x) + fconvert.t(var_18) * fconvert.t(eye->y) + fconvert.t(var_14) * fconvert.t(eye->z)))
00451bb2        matrix->basis_right.y = fconvert.s(x87_r7_17)
00451bbb        matrix->basis_up.y = fconvert.s(x87_r6_10)
00451bbf        matrix->basis_forward.y = fconvert.s(x87_r5_4)
00451bd2        matrix->basis_right.z = var_10
00451bd8        matrix->basis_up.z = var_c
00451be0        matrix->basis_forward.z = var_8
00451be5        matrix->position.y = fconvert.s(fneg(x87_r7_17 * fconvert.t(eye->x) + x87_r6_10 * fconvert.t(eye->y) + x87_r5_4 * fconvert.t(eye->z)))
00451c06        matrix->position.z = fconvert.s(fneg(fconvert.t(var_10) * fconvert.t(eye->x) + fconvert.t(var_c) * fconvert.t(eye->y) + fconvert.t(var_8) * fconvert.t(eye->z)))
00451c0b        matrix->basis_right_w = fconvert.s(float.t(0))
00451c10        matrix->basis_up_w = fconvert.s(float.t(0))
00451c15        matrix->basis_forward_w = fconvert.s(float.t(0))
00451c1a        matrix->position_w = fconvert.s(float.t(1))
00451c1e        return matrix
