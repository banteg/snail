/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: ensure_music_stream_from_path @ 0x449720 */

0044972b        if (*arg1 != 0)
00449733        int32_t eax_1 = strings_equal_case_insensitive_path(arg2, &g_cached_music_path)
0044973d        if (eax_1 != 0)
004497dd        return eax_1
00449745        stop_music_stream(arg1)
0044974b        char* edi_1 = arg2
0044974d        int32_t i = 0xffffffff
00449752        while (i != 0)
00449752        bool cond:0_1 = 0 != *edi_1
00449752        edi_1 = &edi_1[1]
00449752        i -= 1
00449752        if (not(cond:0_1))
00449752        break
0044975f        rstrcpy_checked_ascii(&g_cached_music_path, arg2)
0044976e        if (g_active_music_stream != 0)
00449772        stop_music_stream(arg1)
0044977a        g_active_music_stream = 0
00449785        if (not.d(i) - 1 s> 4)
00449790        int32_t eax_3 = g_bass_stream_create_file(0, arg2, 0, 0, 0)
00449798        g_active_music_stream = eax_3
0044979d        if (eax_3 != 0)
004497a5        if (arg3 == 0)
004497bf        int32_t eax_5 = g_bass_channel_play(eax_3, 0, 0)
004497c5        *arg1 = 1
004497ca        return eax_5
004497ac        int32_t eax_4 = g_bass_channel_play(eax_3, 0, 4)
004497b2        *arg1 = 1
004497b7        return eax_4
004497d3        return report_errorf("Music Play Memory Failed %s", arg2)
