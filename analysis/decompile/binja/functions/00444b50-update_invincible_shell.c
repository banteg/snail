/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_invincible_shell @ 0x444b50 */

00444b66        void* eax
00444b66        switch (*(arg1 + 0x80))
00444b6d        case nullptr
00444b6d        void* result = data_4df904
00444b79        if ((*(result + 0x4300b4) & 0x80) != 0)
00444b83        return start_invincible_shell(arg1)
00444b8e        *(result + 0x433f98) &= 0xffffffdf
00444b94        return result
00444b9b        case 1
00444b9b        long double x87_r7_2 = fconvert.t(*(arg1 + 0x90)) + fconvert.t(*(arg1 + 0x8c))
00444ba1        *(arg1 + 0x8c) = fconvert.s(x87_r7_2)
00444ba7        long double temp1_1 = fconvert.t(1f)
00444ba7        x87_r7_2 - temp1_1
00444bad        eax.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
00444bb2        if ((eax:1.b & 0x41) == 0)
00444bb4        *(arg1 + 0x8c) = 0x3f800000
00444bbe        *(arg1 + 0x80) = 2
00444bd4        if ((*(data_4df904 + 0x4300b4) & 0x80) == 0)
00444bd6        *(arg1 + 0x80) = 3
00444beb        case 2
00444beb        if ((*(data_4df904 + 0x4300b4) & 0x80) == 0)
00444bed        *(arg1 + 0x80) = 3
00444bfb        case 3
00444bfb        long double x87_r7_4 = fconvert.t(*(arg1 + 0x8c)) - fconvert.t(*(arg1 + 0x90))
00444c01        *(arg1 + 0x8c) = fconvert.s(x87_r7_4)
00444c07        long double temp2_1 = fconvert.t(0f)
00444c07        x87_r7_4 - temp2_1
00444c0d        eax.w = (x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe
00444c12        if ((eax:1.b & 1) != 0)
00444c17        *(arg1 + 0x8c) = 0
00444c1d        *(arg1 + 0x80) = 0
00444c35        return change_snail_skin(data_4df904 + 0x434038, 0, 0f)
00444c43        if ((*(data_4df904 + 0x4300b4) & 0x80) != 0)
00444c45        *(arg1 + 0x80) = 1
00444c55        long double x87_r7_6 = fconvert.t(*(arg1 + 0x88)) + fconvert.t(*(arg1 + 0x84))
00444c5b        long double temp0 = fconvert.t(1f)
00444c5b        x87_r7_6 - temp0
00444c61        *(arg1 + 0x84) = fconvert.s(x87_r7_6)
00444c61        bool c1 = unimplemented  {fst dword [ebx+0x84], st0}
00444c67        eax.w = (x87_r7_6 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe | 0x3800
00444c6c        if ((eax:1.b & 0x41) == 0)
00444c74        *(arg1 + 0x84) = fconvert.s(x87_r7_6 - fconvert.t(1f))
00444c90        change_snail_skin(data_4df904 + 0x434038, 2, 0f)
00444c98        set_color_white()
00444cae        *(arg1 + 0x34) = fconvert.s(fconvert.t(*(arg1 + 0x8c)) * fconvert.t(0.800000012f))
00444cb7        long double x87_r6_2 = fconvert.t(*(arg1 + 0x84))
00444cd0        int32_t var_10 = __builtin_memcpy(arg1 + 0x38, data_4df904 + 0x432738, 0x40)
00444cde        return rotate_matrix_world_y(arg1 + 0x38, fconvert.s(x87_r6_2 * fconvert.t(6.28318548f)))
