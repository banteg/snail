/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_track_jetpack_pickup @ 0x43ee50 */

0043ee56        void* result = *(arg1 + 0x8c)
0043ee5f        if (*(result + 9) == 0)
0043ee65        int32_t result_1 = *(arg1 + 0x80)
0043ee6b        result = result_1
0043ee6d        if (result_1 != 0)
0043ee73        void* eax = result - 1
0043ee74        void* ecx_1
0043ee74        if (result == 1)
0043eefa        long double x87_r7_1 = fconvert.t(*(arg1 + 0x70))
0043eefd        long double temp2_1 = fconvert.t(*(*(arg1 + 0x84) + 0x2980))
0043eefd        x87_r7_1 - temp2_1
0043ef03        result.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0043ef08        if ((result:1.b & 1) != 0)
0043ef0e        int16_t eax_6 = (*(arg1 + 4)).w
0043ef11        *(arg1 + 0x80) = 0
0043ef1d        ecx_1 = data_4df904 + 0x5a8
0043ef26        if ((eax_6:1.b & 2) == 0)
0043ef2d        report_errorf("List remove")
0043ef42        return kill_sprite(*(arg1 + 0xac))
0043ef45        if ((eax_6.b & 0x40) != 0)
0043ef4c        report_errorf("List remove NEXTBOD")
0043ef61        return kill_sprite(*(arg1 + 0xac))
0043ef62        void* eax_9 = *(arg1 + 0xc)
0043ef67        if (eax_9 != 0)
0043ef6c        *(eax_9 + 8) = *(arg1 + 8)
0043ef6f        void* eax_10 = *(arg1 + 8)
0043ef74        if (eax_10 == 0)
0043ef81        label_43ef81:
0043ef81        *(ecx_1 + 4) = *(arg1 + 0xc)
0043ef81        goto label_43ef87
0043ef79        *(eax_10 + 0xc) = *(arg1 + 0xc)
0043ef87        label_43ef87:
0043ef87        *(arg1 + 0xc) = *(ecx_1 + 8)
0043ef8a        *(ecx_1 + 8) = arg1
0043ef90        void* ecx_7 = *(arg1 + 0xac)
0043ef96        int32_t eax_12
0043ef96        eax_12:1.b = (*(arg1 + 4)):1.b & 0xfd
0043ef99        *(arg1 + 4) = eax_12
0043ef9c        return kill_sprite(ecx_7)
0043ee76        result = eax - 1
0043ee77        if (eax == 1)
0043ee7d        int16_t eax_1 = (*(arg1 + 4)).w
0043ee80        *(arg1 + 0x80) = 0
0043ee8c        ecx_1 = data_4df904 + 0x5a8
0043ee95        if ((eax_1:1.b & 2) == 0)
0043ee9c        report_errorf("List remove")
0043eeb1        return kill_sprite(*(arg1 + 0xac))
0043eeb4        if ((eax_1.b & 0x40) != 0)
0043eebb        report_errorf("List remove NEXTBOD")
0043eed0        return kill_sprite(*(arg1 + 0xac))
0043eed1        void* eax_4 = *(arg1 + 0xc)
0043eed6        if (eax_4 != 0)
0043eedb        *(eax_4 + 8) = *(arg1 + 8)
0043eede        void* eax_5 = *(arg1 + 8)
0043eee3        if (eax_5 == 0)
0043eee3        goto label_43ef81
0043eeec        *(eax_5 + 0xc) = *(arg1 + 0xc)
0043eeef        goto label_43ef87
0043efa3        return result
