/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_smtrack_heightmap @ 0x41a360 */

0041a36a        int32_t edi = arg1
0041a36e        void* esi = *(arg4 i+ 0x98)
0041a374        long double x87_r7 = float.t(*(edi + 0x1c))
0041a377        arg4 = fconvert.s(x87_r7)
0041a381        void* result
0041a381        int16_t x87control
0041a381        int16_t x87control_1
0041a381        result, x87control_1 = __ftol(x87control, x87_r7 * fconvert.t(*(edi + 0x28)) / fconvert.t(*(edi + 0x24)))
0041a390        int32_t ecx
0041a390        ecx.w = *(esi + 0xc)
0041a39a        int32_t edx
0041a39a        edx.w = *(esi + 0xe)
0041a39e        arg1 = fconvert.s(float.t(result))
0041a3b4        void* ebp = *(edi + 0x38)
0041a3d1        long double x87_r7_8 = fconvert.t(0f)
0041a3d7        long double x87_r6_4 = fconvert.t(0f)
0041a3dd        long double temp0 = fconvert.t(arg1)
0041a3dd        x87_r6_4 - temp0
0041a3e1        result.w = (x87_r6_4 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, temp0) ? 1 : 0) << 0xa | (x87_r6_4 == temp0 ? 1 : 0) << 0xe | 0x3800
0041a3e6        if ((result:1.b & 0x41) != 0)
0041a3ed        int32_t ebx
0041a3ed        ebx.b = arg5
0041a3f1        long double x87_r6_5 = fconvert.t(0f)
0041a3f7        long double x87_r5_1 = fconvert.t(0f)
0041a3fd        long double temp1_1 = fconvert.t(arg4)
0041a3fd        x87_r5_1 - temp1_1
0041a401        result.w = (x87_r5_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r5_1, temp1_1) ? 1 : 0) << 0xa | (x87_r5_1 == temp1_1 ? 1 : 0) << 0xe | 0x3000
0041a406        if ((result:1.b & 0x41) != 0)
0041a412        int32_t eax_1
0041a412        eax_1, x87control_1 = __ftol(x87control_1, x87_r7_8 * fconvert.t(fconvert.s(float.t(edx) / (fconvert.t(arg1) + fconvert.t(1f)))))
0041a41f        int32_t eax_2
0041a41f        eax_2, x87control_1 = __ftol(x87control_1, x87_r6_5 * fconvert.t(fconvert.s(float.t(ecx) / (fconvert.t(arg4) + fconvert.t(1f)))))
0041a428        int32_t ecx_1
0041a428        ecx_1.w = *(esi + 0xe)
0041a42c        int32_t edx_1
0041a42c        edx_1.w = *(esi + 0xc)
0041a43a        int32_t eax_3
0041a43a        eax_3.b = *(esi + 0x10)
0041a442        void* ecx_6 = ((ecx_1 - eax_1 - 1) * edx_1 + eax_2) * (eax_3 u>> 3)
0041a445        int32_t edx_2
0041a445        edx_2.b = *(ecx_6 + esi + 0x13)
0041a449        result = ecx_6 + esi
0041a44e        int32_t ecx_7
0041a44e        ecx_7.b = *(result + 0x14)
0041a451        arg5.d = ecx_7
0041a457        long double x87_r5_6 = float.t(arg5.d)
0041a45b        int32_t ecx_8
0041a45b        ecx_8.b = *(result + 0x12)
0041a45e        arg5.d = edx_2
0041a462        long double x87_r4_1 = float.t(arg5.d)
0041a466        arg5.d = ecx_8
0041a47a        long double x87_r5_10 = (x87_r5_6 + x87_r4_1 + float.t(arg5.d)) * fconvert.t(0.00392156886f) * fconvert.t(0.333333343f)
0041a480        if (ebx.b != 0)
0041a486        x87_r5_10 = x87_r5_10 * x87_r5_10 * x87_r5_10
0041a48c        ebp += 0xc
0041a493        *(ebp - 8) = fconvert.s(x87_r5_10 * fconvert.t(arg3) + fconvert.t(arg2))
0041a496        x87_r6_5 = x87_r6_5 + fconvert.t(1f)
0041a49c        long double temp3_1 = fconvert.t(arg4)
0041a49c        x87_r6_5 - temp3_1
0041a4a0        result.w = (x87_r6_5 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, temp3_1) ? 1 : 0) << 0xa | (x87_r6_5 == temp3_1 ? 1 : 0) << 0xe | 0x3000
0041a4a5        do while ((result:1.b & 0x41) != 0)
0041a4ad        x87_r7_8 = x87_r7_8 + fconvert.t(1f)
0041a4b3        long double temp2_1 = fconvert.t(arg1)
0041a4b3        x87_r7_8 - temp2_1
0041a4b7        result.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0041a4bc        do while ((result:1.b & 0x41) != 0)
0041a4cb        return result
