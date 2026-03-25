/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_axis_aligned_textured_quad @ 0x44a8b0 */

0044a8b0        int32_t result
0044a8b0        result.b = data_4b7236
0044a8b9        if (result.b != 0)
0044a8bf        int32_t ecx_1 = data_777b24
0044a8cb        if (ecx_1 == 0x400)
0044a8d2        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044a8da        return 0
0044a8db        long double x87_r7_1 = fconvert.t(arg4)
0044a8df        long double temp0_1 = fconvert.t(0f)
0044a8df        x87_r7_1 - temp0_1
0044a8e5        result.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
0044a8ea        if ((result:1.b & 0x40) == 0)
0044a8f0        long double x87_r7_2 = fconvert.t(arg5)
0044a8f4        long double temp1_1 = fconvert.t(0f)
0044a8f4        x87_r7_2 - temp1_1
0044a8fa        result.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0044a8ff        if ((result:1.b & 0x40) == 0)
0044a915        result = ecx_1 * 0x84
0044a91d        *(result + &data_7544e8) = arg6 | 2
0044a927        *(result + 0x754538) = arg1
0044a936        *(result + 0x754554) = *arg7
0044a93b        *(result + 0x754558) = arg7[1]
0044a941        *(result + 0x75455c) = arg7[2]
0044a944        int32_t edi_2 = arg7[3]
0044a947        data_777b24 = ecx_1 + 1
0044a94d        *(result + 0x754560) = edi_2
0044a954        *(result + 0x7544ec) = arg2
0044a95e        *(result + 0x7544f0) = arg3
0044a968        *(result + 0x75453c) = arg4
0044a972        *(result + 0x754540) = arg5
0044a978        *(result + 0x754544) = 0
0044a983        *(result + 0x754548) = 0
0044a989        *(result + 0x75454c) = 0x3f800000
0044a98f        *(result + 0x754550) = 0x3f800000
0044a99a        *(result + 0x754564) = arg8
0044a9a1        *(result + 0x754568) = 0
0044a9a8        return result
