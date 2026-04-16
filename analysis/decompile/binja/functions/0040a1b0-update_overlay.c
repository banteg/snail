/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_overlay @ 0x40a1b0 */

0040a1b0        int32_t ebx
0040a1b0        int32_t var_4 = ebx
0040a1b3        int32_t ebp
0040a1b3        int32_t var_8 = ebp
0040a1b4        int32_t esi
0040a1b4        int32_t var_c = esi
0040a1bb        long double x87_r7_1 = fconvert.t(*(arg1 + 0x148)) + fconvert.t(*(arg1 + 0x144))
0040a1c1        int32_t edi
0040a1c1        int32_t var_10 = edi
0040a1c2        long double temp0 = fconvert.t(6.28318548f)
0040a1c2        x87_r7_1 - temp0
0040a1c8        *(arg1 + 0x144) = fconvert.s(x87_r7_1)
0040a1c8        bool c1 = unimplemented  {fst dword [ebx+0x144], st0}
0040a1d3        if ((((x87_r7_1 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_1, temp0) ? 1 : 0) << 0xa | (x87_r7_1 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0040a1e3        long double temp1_1 = fconvert.t(0f)
0040a1e3        x87_r7_1 - temp1_1
0040a1ee        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0040a1f6        *(arg1 + 0x144) = fconvert.s(x87_r7_1 + fconvert.t(6.28318548f))
0040a1db        *(arg1 + 0x144) = fconvert.s(x87_r7_1 - fconvert.t(6.28318548f))
0040a205        set_matrix_identity(arg1 + 0x38)
0040a213        struct TransformMatrix* source = rotate_matrix_world_z(arg1 + 0x38, *(arg1 + 0x144))
0040a225        struct TransformMatrix* var_14_1 = arg1 + 0x38
0040a226        __builtin_memcpy(arg1 + 0xb8, arg1 + 0x38, 0x40)
0040a22e        invert_matrix_from_source(arg1 + 0x100, source)
0040a237        return 0
