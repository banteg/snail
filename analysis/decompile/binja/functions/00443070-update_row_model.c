/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_row_model @ 0x443070 */

00443079        *(arg1 + 0x68) = fconvert.s(fconvert.t(*(arg1 + 0x80)) + fconvert.t(*(arg1 + 0x68)))
00443085        *(arg1 + 0x6c) = fconvert.s(fconvert.t(*(arg1 + 0x84)) + fconvert.t(*(arg1 + 0x6c)))
00443091        *(arg1 + 0x70) = fconvert.s(fconvert.t(*(arg1 + 0x88)) + fconvert.t(*(arg1 + 0x70)))
00443097        void* edx = data_4df904
004430a3        long double x87_r7_6 = fconvert.t(*(*(arg1 + 0x24) + 0xb8)) + fconvert.t(*(edx + 0x4326fc))
004430a9        long double temp0 = fconvert.t(*(arg1 + 0x70))
004430a9        x87_r7_6 - temp0
004430ac        void* eax
004430ac        eax.w = (x87_r7_6 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp0) ? 1 : 0) << 0xa | (x87_r7_6 == temp0 ? 1 : 0) << 0xe
004430b1        if ((eax:1.b & 0x41) == 0)
004430b3        int16_t eax_1 = (*(arg1 + 4)).w
004430bf        if ((eax_1:1.b & 2) == 0)
004430c6        report_errorf("List remove")
004430ce        return 0
004430d1        if ((eax_1.b & 0x40) != 0)
004430d8        report_errorf("List remove NEXTBOD")
004430e0        return 0
004430e1        void* eax_2 = *(arg1 + 0xc)
004430e7        if (eax_2 != 0)
004430ec        *(eax_2 + 8) = *(arg1 + 8)
004430ef        void* eax_3 = *(arg1 + 8)
004430f4        if (eax_3 != 0)
004430f9        *(eax_3 + 0xc) = *(arg1 + 0xc)
004430ff        *(arg1 + 0xc) = *(edx + 0x5b0)
00443102        *(edx + 0x5b0) = arg1
00443109        int32_t eax_5
00443109        eax_5:1.b = (*(arg1 + 4)):1.b & 0xfd
0044310c        *(arg1 + 4) = eax_5
0044310f        return eax_5
00443114        *(edx + 0x5ac) = *(arg1 + 0xc)
0044311a        *(arg1 + 0xc) = *(edx + 0x5b0)
0044311d        *(edx + 0x5b0) = arg1
00443123        eax:1.b = (*(arg1 + 4)):1.b & 0xfd
00443126        *(arg1 + 4) = eax
00443129        return eax
