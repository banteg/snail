/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_banner @ 0x441d40 */

00441d41        void* esi = arg1
00441d43        int32_t eax = *(esi + 0x38)
00441d49        void* eax_2
00441d49        bool c0_1
00441d49        bool c2_1
00441d49        bool c3_1
00441d49        if (eax == 0)
00441d5f        arg1 = *(esi + 0x54)
00441d62        long double x87_r7_3 = fconvert.t(*(arg1 + 0x70))
00441d65        long double temp1_1 = fconvert.t(40f)
00441d65        x87_r7_3 - temp1_1
00441d65        c0_1 = x87_r7_3 < temp1_1
00441d65        c2_1 = is_unordered.t(x87_r7_3, temp1_1)
00441d65        c3_1 = x87_r7_3 == temp1_1
00441d6b        label_441d6b:
00441d6b        void* eax_1
00441d6b        eax_1.w = (c0_1 ? 1 : 0) << 8 | (c2_1 ? 1 : 0) << 0xa | (c3_1 ? 1 : 0) << 0xe
00441d70        eax_2 = *(esi + 4)
00441d73        if ((eax_1:1.b & 1) == 0)
00441d79        eax_2.b &= 0xdf
00441d75        eax_2.b |= 0x20
00441d7b        *(esi + 4) = eax_2
00441d4c        if (eax == 1)
00441d54        long double x87_r7_2 = fconvert.t(*(esi + 0x18)) - fconvert.t(*(*(esi + 0x54) + 0x70))
00441d57        long double temp4_1 = fconvert.t(46f)
00441d57        x87_r7_2 - temp4_1
00441d57        c0_1 = x87_r7_2 < temp4_1
00441d57        c2_1 = is_unordered.t(x87_r7_2, temp4_1)
00441d57        c3_1 = x87_r7_2 == temp4_1
00441d5d        goto label_441d6b
00441d81        long double x87_r7_5 = fconvert.t(*(esi + 0x5c)) + fconvert.t(*(esi + 0x58))
00441d84        long double temp3 = fconvert.t(1f)
00441d84        x87_r7_5 - temp3
00441d8a        *(esi + 0x58) = fconvert.s(x87_r7_5)
00441d8a        bool c1 = unimplemented  {fst dword [esi+0x58], st0}
00441d8d        eax_2.w = (x87_r7_5 < temp3 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_5, temp3) ? 1 : 0) << 0xa | (x87_r7_5 == temp3 ? 1 : 0) << 0xe | 0x3800
00441d92        if ((eax_2:1.b & 0x41) == 0)
00441d9a        *(esi + 0x58) = fconvert.s(x87_r7_5 - fconvert.t(1f))
00441daa        void* var_8 = arg1
00441dae        int32_t result
00441dae        long double st0
00441dae        st0, result = sine(fconvert.s(fconvert.t(*(esi + 0x58)) * fconvert.t(6.28318548f)))
00441dbc        *(esi + 0x14) = fconvert.s(st0 * fconvert.t(0.25999999f))
00441dc0        return result
