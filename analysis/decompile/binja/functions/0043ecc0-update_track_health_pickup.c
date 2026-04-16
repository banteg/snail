/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_health_pickup @ 0x43ecc0 */

0043ecc6        void* result = *(arg1 + 0x44)
0043eccc        if (*(result + 9) == 0)
0043ecd2        int32_t result_1 = *(arg1 + 0x38)
0043ecd5        result = result_1
0043ecd7        if (result_1 != 0)
0043ecde        void* eax_1
0043ecde        void* ecx_1
0043ecde        if (result == 1)
0043ed58        long double x87_r7_1 = fconvert.t(*(arg1 + 0x18))
0043ed5b        long double temp2_1 = fconvert.t(*(*(arg1 + 0x3c) + 0x2980))
0043ed5b        x87_r7_1 - temp2_1
0043ed61        eax_1.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043ed66        if ((eax_1:1.b & 1) != 0)
0043ed6c        int16_t eax_7 = (*(arg1 + 4)).w
0043ed6f        *(arg1 + 0x38) = 0
0043ed78        ecx_1 = data_4df904 + 0x5a8
0043ed81        if ((eax_7:1.b & 2) == 0)
0043ed88        report_errorf("List remove")
0043ed9a        return kill_sprite(*(arg1 + 0x64))
0043ed9d        if ((eax_7.b & 0x40) != 0)
0043eda4        report_errorf("List remove NEXTBOD")
0043edb6        return kill_sprite(*(arg1 + 0x64))
0043edb7        void* eax_10 = *(arg1 + 0xc)
0043edbc        if (eax_10 != 0)
0043edc1        *(eax_10 + 8) = *(arg1 + 8)
0043edc4        void* eax_11 = *(arg1 + 8)
0043edc9        if (eax_11 == 0)
0043edd6        label_43edd6:
0043edd6        *(ecx_1 + 4) = *(arg1 + 0xc)
0043edd6        goto label_43eddc
0043edce        *(eax_11 + 0xc) = *(arg1 + 0xc)
0043eddc        label_43eddc:
0043eddc        *(arg1 + 0xc) = *(ecx_1 + 8)
0043eddf        *(ecx_1 + 8) = arg1
0043ede5        void* ecx_7 = *(arg1 + 0x64)
0043ede8        int32_t eax_13
0043ede8        eax_13:1.b = (*(arg1 + 4)):1.b & 0xfd
0043edeb        *(arg1 + 4) = eax_13
0043edf5        return kill_sprite(ecx_7)
0043ece1        if (result == 2)
0043ece7        int16_t eax_2 = (*(arg1 + 4)).w
0043ecea        *(arg1 + 0x38) = 0
0043ecf3        ecx_1 = data_4df904 + 0x5a8
0043ecfc        if ((eax_2:1.b & 2) == 0)
0043ed03        report_errorf("List remove")
0043ed15        return kill_sprite(*(arg1 + 0x64))
0043ed18        if ((eax_2.b & 0x40) != 0)
0043ed1f        report_errorf("List remove NEXTBOD")
0043ed31        return kill_sprite(*(arg1 + 0x64))
0043ed32        void* eax_5 = *(arg1 + 0xc)
0043ed37        if (eax_5 != 0)
0043ed3c        *(eax_5 + 8) = *(arg1 + 8)
0043ed3f        void* eax_6 = *(arg1 + 8)
0043ed44        if (eax_6 == 0)
0043ed44        goto label_43edd6
0043ed4d        *(eax_6 + 0xc) = *(arg1 + 0xc)
0043ed50        goto label_43eddc
0043edf9        long double x87_r7_3 = fconvert.t(*(arg1 + 0x70)) + fconvert.t(*(arg1 + 0x6c))
0043edfc        long double temp4_1 = fconvert.t(1f)
0043edfc        x87_r7_3 - temp4_1
0043ee02        *(arg1 + 0x6c) = fconvert.s(x87_r7_3)
0043ee02        bool c1_1 = unimplemented  {fst dword [esi+0x6c], st0}
0043ee05        eax_1.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe | 0x3800
0043ee0a        if ((eax_1:1.b & 0x41) == 0)
0043ee12        *(arg1 + 0x6c) = fconvert.s(x87_r7_3 - fconvert.t(1f))
0043ee22        void* var_c_1 = arg1
0043ee2b        long double x87_r7_9 = sine(fconvert.s(fconvert.t(*(arg1 + 0x6c)) * fconvert.t(6.28318548f))) + fconvert.t(1f)
0043ee31        result = *(arg1 + 0x64)
0043ee40        *(result + 0x4c) = fconvert.s(x87_r7_9 * fconvert.t(0.300000012f) + fconvert.t(*(arg1 + 0x14)))
0043ee45        return result
