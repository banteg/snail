/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_backdrop_corner_quad @ 0x41a290 */

0041a29d        initialize_backdrop_slice_quad(arg2, arg3, 0f)
0041a2a2        struct Vec3* vertices = arg2->vertices
0041a2b3        int32_t ecx = *((arg1 << 2) + &data_4a3ce0) * 3
0041a2b6        long double x87_r7 = fconvert.t(*(vertices + (ecx << 2)))
0041a2b9        float* ecx_1 = vertices + (ecx << 2)
0041a2bc        long double temp0 = fconvert.t(0f)
0041a2bc        x87_r7 - temp0
0041a2c2        int32_t eax
0041a2c2        eax.w = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
0041a2c7        if ((eax:1.b & 1) == 0)
0041a2d3        long double x87_r7_1 = fconvert.t(*ecx_1)
0041a2d5        long double temp1_1 = fconvert.t(0f)
0041a2d5        x87_r7_1 - temp1_1
0041a2db        arg3 = 0
0041a2e3        eax.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
0041a2e8        if ((eax:1.b & 0x40) == 0)
0041a2ea        arg3 = 1
0041a2c9        arg3 = 0xffffffff
0041a2fc        *ecx_1 = fconvert.s(float.t(arg3) * fconvert.t(0.300000012f))
0041a306        int32_t result = *((arg1 << 2) + &data_4a3ce0) * 3
0041a309        long double x87_r7_4 = fconvert.t((&vertices->z)[result])
0041a30d        float* ecx_2 = &(&vertices->z)[result]
0041a311        long double temp2 = fconvert.t(0f)
0041a311        x87_r7_4 - temp2
0041a317        result.w = (x87_r7_4 < temp2 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2) ? 1 : 0) << 0xa | (x87_r7_4 == temp2 ? 1 : 0) << 0xe
0041a31c        if ((result:1.b & 1) != 0)
0041a330        *ecx_2 = fconvert.s(float.t(0xffffffff) * fconvert.t(0.300000012f))
0041a332        return result
0041a333        long double x87_r7_7 = fconvert.t(*ecx_2)
0041a335        long double temp3 = fconvert.t(0f)
0041a335        x87_r7_7 - temp3
0041a33b        arg3 = 0
0041a343        result.w = (x87_r7_7 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp3) ? 1 : 0) << 0xa | (x87_r7_7 == temp3 ? 1 : 0) << 0xe
0041a348        if ((result:1.b & 0x40) == 0)
0041a34a        arg3 = 1
0041a35c        *ecx_2 = fconvert.s(float.t(arg3) * fconvert.t(0.300000012f))
0041a35e        return result
