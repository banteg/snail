/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_axis_aligned_textured_quad_uv @ 0x44a9b0 */

0044a9b0        int32_t result
0044a9b0        result.b = data_4b7236
0044a9b7        if (result.b != 0)
0044a9bd        int32_t ecx_1 = data_777b24
0044a9c9        if (ecx_1 == 0x400)
0044a9d0        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044a9d8        return 0
0044a9d9        long double x87_r7_1 = fconvert.t(arg4)
0044a9dd        long double temp0_1 = fconvert.t(0f)
0044a9dd        x87_r7_1 - temp0_1
0044a9e3        result.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
0044a9e8        if ((result:1.b & 0x40) == 0)
0044a9ee        long double x87_r7_2 = fconvert.t(arg5)
0044a9f2        long double temp1_1 = fconvert.t(0f)
0044a9f2        x87_r7_2 - temp1_1
0044a9f8        result.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
0044a9fd        if ((result:1.b & 0x40) == 0)
0044aa11        result = ecx_1 * 0x84
0044aa19        *(result + &data_7544e8) = arg6 | 2
0044aa23        *(result + 0x754538) = arg1
0044aa33        *(result + 0x754554) = *arg7
0044aa38        *(result + 0x754558) = arg7[1]
0044aa3e        *(result + 0x75455c) = arg7[2]
0044aa41        int32_t esi_2 = arg7[3]
0044aa45        data_777b24 = ecx_1 + 1
0044aa4b        *(result + 0x754560) = esi_2
0044aa52        *(result + 0x7544ec) = arg2
0044aa5c        *(result + 0x7544f0) = arg3
0044aa66        *(result + 0x75453c) = arg4
0044aa70        *(result + 0x754540) = arg5
0044aa7a        *(result + 0x754544) = arg8
0044aa84        *(result + 0x754548) = arg9
0044aa8e        *(result + 0x75454c) = arg10
0044aa98        *(result + 0x754550) = arg11
0044aaa2        *(result + 0x754564) = arg12
0044aaac        *(result + 0x754568) = arg13
0044aab3        return result
