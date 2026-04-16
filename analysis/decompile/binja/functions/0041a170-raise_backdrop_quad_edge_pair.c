/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: raise_backdrop_quad_edge_pair @ 0x41a170 */

0041a17a        int32_t ecx = *(arg2 + 0x38)
0041a17d        float* result
0041a17d        if (arg1 s> 0)
0041a199        label_41a199:
0041a19e        int32_t edx_1 = data_4a3c44 * 3
0041a1ab        result = ecx + (edx_1 << 2) + 4
0041a1af        *result = fconvert.s(fconvert.t(*(ecx + (edx_1 << 2) + 4)) + fconvert.t(0.5f))
0041a184        int32_t eax_1 = data_4a3c40 * 3
0041a191        result = ecx + (eax_1 << 2) + 4
0041a195        *result = fconvert.s(fconvert.t(*(ecx + (eax_1 << 2) + 4)) + fconvert.t(0.5f))
0041a197        if (arg1 s>= 0)
0041a197        goto label_41a199
0041a1b1        return result
