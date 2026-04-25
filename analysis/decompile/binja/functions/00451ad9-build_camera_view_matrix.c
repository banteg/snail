/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_camera_view_matrix @ 0x451ad9 */

00451aec        float var_10 = fconvert.s(fconvert.t(*arg2) - fconvert.t(*arg3))
00451af5        float var_c = fconvert.s(fconvert.t(arg2[1]) - fconvert.t(arg3[1]))
00451b06        float var_8 = fconvert.s(fconvert.t(arg2[2]) - fconvert.t(arg3[2]))
00451b09        j_sub_44ebb4(&var_10, &var_10)
00451b25        float var_28 = fconvert.s(fconvert.t(var_8) * fconvert.t(arg4[1]) - fconvert.t(var_c) * fconvert.t(arg4[2]))
00451b35        float var_24 = fconvert.s(fconvert.t(var_10) * fconvert.t(arg4[2]) - fconvert.t(var_8) * fconvert.t(*arg4))
00451b4d        float var_20 = fconvert.s(fconvert.t(var_c) * fconvert.t(*arg4) - fconvert.t(var_10) * fconvert.t(arg4[1]))
00451b50        float var_1c = var_28
00451b50        float var_18
00451b50        float* edi = &var_18
00451b50        float* esi = &var_24
00451b51        *edi = *esi
00451b52        edi[1] = esi[1]
00451b53        j_sub_44ebb4(&var_1c, &var_1c)
00451b64        arg1[4] = var_18
00451b6d        long double x87_r6_7 = fconvert.t(var_8) * fconvert.t(var_18)
00451b70        float var_14
00451b70        arg1[8] = var_14
00451b73        long double x87_r7_17 = fconvert.t(var_c) * fconvert.t(var_14) - x87_r6_7
00451b81        long double x87_r6_10 = fconvert.t(var_8) * fconvert.t(var_1c) - fconvert.t(var_10) * fconvert.t(var_14)
00451b8f        long double x87_r5_4 = fconvert.t(var_10) * fconvert.t(var_18) - fconvert.t(var_c) * fconvert.t(var_1c)
00451b94        *arg1 = fconvert.s(fconvert.t(var_1c))
00451bad        arg1[0xc] = fconvert.s(fneg(fconvert.t(var_1c) * fconvert.t(*arg2) + fconvert.t(var_18) * fconvert.t(arg2[1]) + fconvert.t(var_14) * fconvert.t(arg2[2])))
00451bb2        arg1[1] = fconvert.s(x87_r7_17)
00451bb5        float ecx_2 = var_10
00451bbb        arg1[5] = fconvert.s(x87_r6_10)
00451bbf        arg1[9] = fconvert.s(x87_r5_4)
00451bcb        long double x87_r4_12 = x87_r7_17 * fconvert.t(*arg2) + x87_r6_10 * fconvert.t(arg2[1])
00451bcf        long double x87_r3_7 = x87_r5_4 * fconvert.t(arg2[2])
00451bd2        arg1[2] = ecx_2
00451bd8        arg1[6] = var_c
00451be0        arg1[0xa] = var_8
00451be5        arg1[0xd] = fconvert.s(fneg(x87_r4_12 + x87_r3_7))
00451c06        arg1[0xe] = fconvert.s(fneg(fconvert.t(var_10) * fconvert.t(*arg2) + fconvert.t(var_c) * fconvert.t(arg2[1]) + fconvert.t(var_8) * fconvert.t(arg2[2])))
00451c0b        arg1[3] = fconvert.s(float.t(0))
00451c10        arg1[7] = fconvert.s(float.t(0))
00451c15        arg1[0xb] = fconvert.s(float.t(0))
00451c1a        arg1[0xf] = fconvert.s(float.t(1))
00451c1e        return arg1
