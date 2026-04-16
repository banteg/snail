/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_sprite @ 0x44e200 */

0044e207        if ((*(arg1 + 4) & 1) == 0)
0044e20f        int32_t var_8_1 = *(arg1 + 0x1c) + 0xc
0044e215        report_errorf("Sprite kill error, already dead (%s)")
0044e223        if (arg1 == 0x814cb0)
0044e223        return 
0044e22b        *(arg1 + 4) &= 0xfffffffe
0044e238        if (arg1 == *((*(arg1 + 8) << 2) + &data_814c94))
0044e23a        void* eax_3 = *(arg1 + 0xc)
0044e23f        if (eax_3 != 0)
0044e241        *(eax_3 + 0x10) = 0
0044e24e        *((*(arg1 + 8) << 2) + &data_814c94) = *(arg1 + 0xc)
0044e25b        *(arg1 + 0xc) = data_814ca8
0044e25e        data_814ca8 = arg1
0044e265        return 
0044e266        void* eax_5 = *(arg1 + 0x10)
0044e26b        if (eax_5 != 0)
0044e270        *(eax_5 + 0xc) = *(arg1 + 0xc)
0044e273        void* eax = *(arg1 + 0xc)
0044e278        if (eax != 0)
0044e27d        *(eax + 0x10) = *(arg1 + 0x10)
0044e286        *(arg1 + 0xc) = data_814ca8
0044e289        data_814ca8 = arg1
0044e290        return
