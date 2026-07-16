/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: prepare_music_stream_reload_if_path_changed @ 0x4497e0 */

004497e6        int32_t eax
004497e6        if (*arg1 != 0)
004497f2        int32_t eax_2 = strings_equal_case_insensitive_path(arg2, &g_cached_music_path)
004497fc        if (eax_2 != 0)
004497fe        eax_2.b = 0
00449801        return eax_2
00449806        eax = stop_music_stream(arg1)
0044980b        eax.b = 1
0044980e        return eax
