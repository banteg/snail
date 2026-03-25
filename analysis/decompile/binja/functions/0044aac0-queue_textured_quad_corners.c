/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: queue_textured_quad_corners @ 0x44aac0 */

0044aac0        int32_t result
0044aac0        result.b = data_4b7236
0044aac9        if (result.b != 0)
0044aacf        int32_t ecx_1 = data_777b24
0044aadb        if (ecx_1 == 0x400)
0044aae2        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h")
0044aaea        return 0
0044aafb        result = ecx_1 * 0x84
0044ab03        *(result + &data_7544e8) = arg10 | 2
0044ab0d        *(result + 0x754538) = arg1
0044ab1c        *(result + 0x754554) = *arg11
0044ab21        *(result + 0x754558) = arg11[1]
0044ab27        *(result + 0x75455c) = arg11[2]
0044ab2a        int32_t edi_2 = arg11[3]
0044ab2d        data_777b24 = ecx_1 + 1
0044ab33        *(result + 0x754560) = edi_2
0044ab3a        *(result + 0x7544ec) = arg2
0044ab44        *(result + 0x7544f0) = arg3
0044ab4e        *(result + 0x7544f8) = arg4
0044ab58        *(result + 0x7544fc) = arg5
0044ab62        *(result + 0x754504) = arg6
0044ab6c        *(result + 0x754508) = arg7
0044ab76        *(result + 0x754510) = arg8
0044ab80        *(result + 0x754514) = arg9
0044ab86        *(result + 0x75453c) = 0
0044ab8c        *(result + 0x754540) = 0
0044ab96        *(result + 0x754544) = arg12
0044aba0        *(result + 0x754548) = arg13
0044abaa        *(result + 0x75454c) = arg14
0044abb4        *(result + 0x754550) = arg15
0044abbe        *(result + 0x754564) = arg16
0044abca        *(result + 0x754568) = arg17
0044abd1        return result
