/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_wall2_ambient_hazard @ 0x43efb0 */

0043efb6        void* result = *(arg1 + 0x44)
0043efbc        if (*(result + 9) == 0)
0043efc2        int32_t result_1 = *(arg1 + 0x38)
0043efc5        result = result_1
0043efc7        if (result_1 != 0)
0043efce        void* eax_1
0043efce        void* ecx_1
0043efce        if (result == 1)
0043f048        long double x87_r7_1 = fconvert.t(*(arg1 + 0x18))
0043f04b        long double temp2_1 = fconvert.t(*(*(arg1 + 0x3c) + 0x2980))
0043f04b        x87_r7_1 - temp2_1
0043f051        eax_1.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043f056        if ((eax_1:1.b & 1) != 0)
0043f05c        int16_t eax_7 = (*(arg1 + 4)).w
0043f05f        *(arg1 + 0x38) = 0
0043f068        ecx_1 = data_4df904 + 0x5a8
0043f071        if ((eax_7:1.b & 2) == 0)
0043f078        report_errorf("List remove")
0043f08a        return kill_sprite(*(arg1 + 0x64))
0043f08d        if ((eax_7.b & 0x40) != 0)
0043f094        report_errorf("List remove NEXTBOD")
0043f0a6        return kill_sprite(*(arg1 + 0x64))
0043f0a7        void* eax_10 = *(arg1 + 0xc)
0043f0ac        if (eax_10 != 0)
0043f0b1        *(eax_10 + 8) = *(arg1 + 8)
0043f0b4        void* eax_11 = *(arg1 + 8)
0043f0b9        if (eax_11 == 0)
0043f0c6        label_43f0c6:
0043f0c6        *(ecx_1 + 4) = *(arg1 + 0xc)
0043f0c6        goto label_43f0cc
0043f0be        *(eax_11 + 0xc) = *(arg1 + 0xc)
0043f0cc        label_43f0cc:
0043f0cc        *(arg1 + 0xc) = *(ecx_1 + 8)
0043f0cf        *(ecx_1 + 8) = arg1
0043f0d5        void* ecx_7 = *(arg1 + 0x64)
0043f0d8        int32_t eax_13
0043f0d8        eax_13:1.b = (*(arg1 + 4)):1.b & 0xfd
0043f0db        *(arg1 + 4) = eax_13
0043f0e5        return kill_sprite(ecx_7)
0043efd1        if (result == 2)
0043efd7        int16_t eax_2 = (*(arg1 + 4)).w
0043efda        *(arg1 + 0x38) = 0
0043efe3        ecx_1 = data_4df904 + 0x5a8
0043efec        if ((eax_2:1.b & 2) == 0)
0043eff3        report_errorf("List remove")
0043f005        return kill_sprite(*(arg1 + 0x64))
0043f008        if ((eax_2.b & 0x40) != 0)
0043f00f        report_errorf("List remove NEXTBOD")
0043f021        return kill_sprite(*(arg1 + 0x64))
0043f022        void* eax_5 = *(arg1 + 0xc)
0043f027        if (eax_5 != 0)
0043f02c        *(eax_5 + 8) = *(arg1 + 8)
0043f02f        void* eax_6 = *(arg1 + 8)
0043f034        if (eax_6 == 0)
0043f034        goto label_43f0c6
0043f03d        *(eax_6 + 0xc) = *(arg1 + 0xc)
0043f040        goto label_43f0cc
0043f0e9        long double x87_r7_3 = fconvert.t(*(arg1 + 0x70)) + fconvert.t(*(arg1 + 0x6c))
0043f0ec        long double temp4_1 = fconvert.t(1f)
0043f0ec        x87_r7_3 - temp4_1
0043f0f2        *(arg1 + 0x6c) = fconvert.s(x87_r7_3)
0043f0f2        bool c1_1 = unimplemented  {fst dword [esi+0x6c], st0}
0043f0f5        eax_1.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0043f0fa        if ((eax_1:1.b & 0x41) == 0)
0043f102        *(arg1 + 0x6c) = fconvert.s(x87_r7_3 - fconvert.t(1f))
0043f112        void* var_c_1 = arg1
0043f11b        long double x87_r7_9 = sine(fconvert.s(fconvert.t(*(arg1 + 0x6c)) * fconvert.t(6.28318548f))) * fconvert.t(0.300000012f)
0043f121        result = *(arg1 + 0x64)
0043f12a        *(result + 0x4c) = fconvert.s(x87_r7_9 + fconvert.t(*(arg1 + 0x14)))
0043f12f        return result
