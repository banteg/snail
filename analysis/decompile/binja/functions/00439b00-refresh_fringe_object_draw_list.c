/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: refresh_fringe_object_draw_list @ 0x439b00 */

00439b17        void var_10
00439b17        int32_t* eax = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
00439b21        long double x87_r7 = fconvert.t(*(arg1 + 0x18))
00439b24        *(arg1 + 0x28) = *eax
00439b29        *(arg1 + 0x2c) = eax[1]
00439b2f        *(arg1 + 0x30) = eax[2]
00439b35        *(arg1 + 0x34) = eax[3]
00439b38        void* ecx_5 = data_4df904
00439b3e        long double temp0 = fconvert.t(*(ecx_5 + 0x4326fc))
00439b3e        x87_r7 - temp0
00439b44        int32_t result
00439b44        result.w = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
00439b49        if ((result:1.b & 1) != 0)
00439b4b        int16_t eax_1 = (*(arg1 + 4)).w
00439b57        if ((eax_1:1.b & 2) == 0)
00439b5e        report_errorf("List remove")
00439b6a        return 0
00439b6d        if ((eax_1.b & 0x40) != 0)
00439b74        report_errorf("List remove NEXTBOD")
00439b80        return 0
00439b81        void* eax_2 = *(arg1 + 0xc)
00439b86        if (eax_2 != 0)
00439b8b        *(eax_2 + 8) = *(arg1 + 8)
00439b8e        void* eax_3 = *(arg1 + 8)
00439b93        if (eax_3 == 0)
00439ba0        *(ecx_5 + 0x5ac) = *(arg1 + 0xc)
00439b98        *(eax_3 + 0xc) = *(arg1 + 0xc)
00439ba6        *(arg1 + 0xc) = *(ecx_5 + 0x5b0)
00439ba9        *(ecx_5 + 0x5b0) = arg1
00439baf        result:1.b = (*(arg1 + 4)):1.b & 0xfd
00439bb2        *(arg1 + 4) = result
00439bb9        return result
