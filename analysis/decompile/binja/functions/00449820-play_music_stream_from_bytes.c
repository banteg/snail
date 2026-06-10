/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_music_stream_from_bytes @ 0x449820 */

0044982a        char* edi = arg2
0044982c        int32_t i = 0xffffffff
00449832        while (i != 0)
00449832        bool cond:0_1 = 0 != *edi
00449832        edi = &edi[1]
00449832        i -= 1
00449832        if (not(cond:0_1))
00449832        break
0044983e        rstrcpy_checked_ascii(&data_7516a0, arg2)
0044984d        if (data_753c20 != 0)
00449851        stop_music_stream(arg1)
00449859        data_753c20 = 0
00449863        if (not.d(i) - 1 s> 4)
00449875        int32_t eax_2 = data_753bf8(1, arg3, 0, arg4, 0)
0044987d        data_753c20 = eax_2
00449882        if (eax_2 != 0)
0044988a        if (arg5 == 0)
004498a7        int32_t eax_4 = data_7517a0(eax_2, 0, 0)
004498ae        *arg1 = 1
004498b5        return eax_4
00449891        int32_t eax_3 = data_7517a0(eax_2, 0, 4)
00449898        *arg1 = 1
0044989f        return eax_3
004498be        report_errorf("Music Play Memory Failed %s", arg2)
004498ca        return 0
