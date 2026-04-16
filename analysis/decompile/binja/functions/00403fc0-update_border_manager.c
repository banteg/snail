/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_border_manager @ 0x403fc0 */

00403fc0        void* result
00403fc0        result.b = *(arg1 + 0x435a0)
00403fc9        if (result.b != 0)
00403fd1        long double x87_r7_2 = fconvert.t(*(arg1 + 0x435a8)) + fconvert.t(*(arg1 + 0x435a4))
00403fd7        *(arg1 + 0x435a4) = fconvert.s(x87_r7_2)
00403fdd        long double temp0_1 = fconvert.t(1f)
00403fdd        x87_r7_2 - temp0_1
00403fe3        result.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
00403fe8        if ((result:1.b & 0x41) == 0)
00403fea        result = *(arg1 + 0x435ac)
00403ff0        *(arg1 + 0x435a4) = 0x3f800000
00403ffa        int32_t edx_1 = *(result + 0x1a0)
00404016        if ((edx_1 & 0x40000000) == 0 || *(data_4df904 + 0x24) == 4)
00404020        *(result + 0x1a0) = *(arg1 + 0x4359c) | edx_1
00404026        *(arg1 + 0x435a0) = 0
0040402e        return result
