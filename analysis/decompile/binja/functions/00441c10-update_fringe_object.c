/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_fringe_object @ 0x441c10 */

00441c11        void* esi = arg1
00441c13        void* eax = *(esi + 0x88)
00441c19        arg1.b = *(eax + 9)
00441c1e        if (arg1.b == 0)
00441c24        int32_t ecx = *(esi + 0x80)
00441c2b        if (ecx == 1)
00441cd0        long double x87_r7_4 = fconvert.t(1f) - (fconvert.t(*(esi + 0x70)) - fconvert.t(*(eax + 0x3bb7d4))) * fconvert.t(0.0217391308f)
00441cd6        long double temp1_1 = fconvert.t(0f)
00441cd6        x87_r7_4 - temp1_1
00441cdc        *(esi + 0x8c) = fconvert.s(x87_r7_4)
00441cdc        bool c1_1 = unimplemented  {fst dword [esi+0x8c], st0}
00441ce2        eax.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00441ce7        if ((eax:1.b & 1) == 0)
00441cf3        long double temp3_1 = fconvert.t(1f)
00441cf3        x87_r7_4 - temp3_1
00441cf9        eax.w = (x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe | 0x3800
00441cfe        if ((eax:1.b & 0x41) == 0)
00441d02        x87_r7_4 = fconvert.t(1f)
00441ceb        x87_r7_4 = fconvert.t(0f)
00441d08        *(esi + 0x8c) = fconvert.s(x87_r7_4)
00441d16        set_color_alpha(esi + 0x28, 0.899999976f)
00441d21        long double x87_r6_1 = fconvert.t(*(esi + 0x70))
00441d24        long double temp4_1 = fconvert.t(*(*(esi + 0x88) + 0x3be0e4))
00441d24        x87_r6_1 - temp4_1
00441d2a        eax.w = (x87_r6_1 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, temp4_1) ? 1 : 0) << 0xa | (x87_r6_1 == temp4_1 ? 1 : 0) << 0xe | 0x3800
00441d2f        if ((eax:1.b & 1) != 0)
00441d31        *(esi + 0x80) = 2
00441c32        if (ecx == 2)
00441c3d        void* ecx_3 = data_4df904 + 0x5a8
00441c43        int16_t eax_2 = (*(esi + 4)).w
00441c49        if ((eax_2:1.b & 2) == 0)
00441c50        report_errorf("List remove")
00441c58        *(esi + 0x80) = 0
00441c63        return 0
00441c66        if ((eax_2.b & 0x40) != 0)
00441c6d        report_errorf("List remove NEXTBOD")
00441c75        *(esi + 0x80) = 0
00441c80        return 0
00441c81        void* eax_3 = *(esi + 0xc)
00441c86        if (eax_3 != 0)
00441c8b        *(eax_3 + 8) = *(esi + 8)
00441c8e        void* eax_4 = *(esi + 8)
00441c93        if (eax_4 == 0)
00441ca0        *(ecx_3 + 4) = *(esi + 0xc)
00441c98        *(eax_4 + 0xc) = *(esi + 0xc)
00441ca6        *(esi + 0xc) = *(ecx_3 + 8)
00441ca9        *(ecx_3 + 8) = esi
00441cac        int32_t eax_6 = *(esi + 4)
00441caf        *(esi + 0x80) = 0
00441cb9        eax_6:1.b &= 0xfd
00441cbc        *(esi + 4) = eax_6
00441cc0        return eax_6
00441d3c        return eax
