/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_active_bod @ 0x433e80 */

00433e83        long double x87_r7 = fconvert.t(*(arg1 + 0x38)) + fconvert.t(24f)
00433e89        void* edx = data_4df904
00433e8f        long double temp0 = fconvert.t(*(edx + 0x4326fc))
00433e8f        x87_r7 - temp0
00433e95        int32_t eax
00433e95        eax.w = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
00433e9a        if ((eax:1.b & 1) != 0)
00433e9c        int16_t eax_1 = (*(arg1 + 4)).w
00433ea8        if ((eax_1:1.b & 2) == 0)
00433eaf        report_errorf("List remove")
00433eb7        return 0
00433eba        if ((eax_1.b & 0x40) != 0)
00433ec1        report_errorf("List remove NEXTBOD")
00433ec9        return 0
00433eca        void* eax_2 = *(arg1 + 0xc)
00433ed0        if (eax_2 != 0)
00433ed5        *(eax_2 + 8) = *(arg1 + 8)
00433ed8        void* eax_3 = *(arg1 + 8)
00433edd        if (eax_3 != 0)
00433ee2        *(eax_3 + 0xc) = *(arg1 + 0xc)
00433ee8        *(arg1 + 0xc) = *(edx + 0x5b0)
00433eeb        *(edx + 0x5b0) = arg1
00433ef2        int32_t eax_5
00433ef2        eax_5:1.b = (*(arg1 + 4)):1.b & 0xfd
00433ef5        *(arg1 + 4) = eax_5
00433ef8        return eax_5
00433efd        *(edx + 0x5ac) = *(arg1 + 0xc)
00433f03        *(arg1 + 0xc) = *(edx + 0x5b0)
00433f06        *(edx + 0x5b0) = arg1
00433f0c        eax:1.b = (*(arg1 + 4)):1.b & 0xfd
00433f0f        *(arg1 + 4) = eax
00433f12        return eax
