/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_invincible_shell @ 0x444b50 */

00444b66        int32_t eax
00444b66        switch (shell->state)
00444b6d        case 0
00444b6d        void* eax_1 = data_4df904
00444b79        if ((*(eax_1 + 0x4300b4) & 0x80) == 0)
00444b8e        *(eax_1 + 0x433f98) &= 0xffffffdf
00444b94        return 
00444b7d        start_invincible_shell(shell)
00444b83        return 
00444b9b        case 1
00444b9b        long double x87_r7_2 = fconvert.t(shell->fade_step) + fconvert.t(shell->fade_progress)
00444ba1        shell->fade_progress = fconvert.s(x87_r7_2)
00444ba7        long double temp1_1 = fconvert.t(1f)
00444ba7        x87_r7_2 - temp1_1
00444bad        eax.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
00444bb2        if ((eax:1.b & 0x41) == 0)
00444bb4        shell->fade_progress = 1f
00444bbe        shell->state = 2
00444bd4        if ((*(data_4df904 + 0x4300b4) & 0x80) == 0)
00444bd6        shell->state = 3
00444beb        case 2
00444beb        if ((*(data_4df904 + 0x4300b4) & 0x80) == 0)
00444bed        shell->state = 3
00444bfb        case 3
00444bfb        long double x87_r7_4 = fconvert.t(shell->fade_progress) - fconvert.t(shell->fade_step)
00444c01        shell->fade_progress = fconvert.s(x87_r7_4)
00444c07        long double temp2_1 = fconvert.t(0f)
00444c07        x87_r7_4 - temp2_1
00444c0d        eax.w = (x87_r7_4 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp2_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp2_1 ? 1 : 0) << 0xe
00444c12        if ((eax:1.b & 1) != 0)
00444c17        shell->fade_progress = 0f
00444c1d        shell->state = 0
00444c2f        change_snail_skin(data_4df904 + 0x434038, 0, 0f)
00444c35        return 
00444c43        if ((*(data_4df904 + 0x4300b4) & 0x80) != 0)
00444c45        shell->state = 1
00444c55        long double x87_r7_6 = fconvert.t(shell->spin_phase_step) + fconvert.t(shell->spin_phase)
00444c5b        long double temp0 = fconvert.t(1f)
00444c5b        x87_r7_6 - temp0
00444c61        shell->spin_phase = fconvert.s(x87_r7_6)
00444c61        bool c1 = unimplemented  {fst dword [ebx+0x84], st0}
00444c67        eax.w = (x87_r7_6 < temp0 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe | 0x3800
00444c6c        if ((eax:1.b & 0x41) == 0)
00444c74        shell->spin_phase = fconvert.s(x87_r7_6 - fconvert.t(1f))
00444c90        change_snail_skin(data_4df904 + 0x434038, 2, 0f)
00444c98        set_color_white()
00444cae        shell->_pad_00[0x34].d = fconvert.s(fconvert.t(shell->fade_progress) * fconvert.t(0.800000012f))
00444cb7        long double x87_r6_2 = fconvert.t(shell->spin_phase)
00444cd0        int32_t var_10 = __builtin_memcpy(&shell->_pad_00[0x38], data_4df904 + 0x432738, 0x40)
00444cd6        rotate_matrix_world_y(&shell->_pad_00[0x38], fconvert.s(x87_r6_2 * fconvert.t(6.28318548f)))
00444cde        return
