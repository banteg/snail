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
0044983e        rstrcpy_checked_ascii(&g_cached_music_path, arg2)
0044984d        if (g_active_music_stream != 0)
00449851        stop_music_stream(arg1)
00449859        g_active_music_stream = 0
00449863        if (not.d(i) - 1 s> 4)
00449875        int32_t stream = g_bass_stream_create_file(1, arg3, 0, arg4, 0)
0044987d        g_active_music_stream = stream
00449882        if (stream != 0)
0044988a        if (arg5 == 0)
004498a7        int32_t eax_3 = g_bass_channel_play(stream, 0, 0)
004498ae        *arg1 = 1
004498b5        return eax_3
00449891        int32_t eax_2 = g_bass_channel_play(stream, 0, 4)
00449898        *arg1 = 1
0044989f        return eax_2
004498be        report_errorf("Music Play Memory Failed %s", arg2)
004498ca        return 0
