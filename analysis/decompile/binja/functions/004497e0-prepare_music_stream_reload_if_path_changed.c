/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: prepare_music_stream_reload_if_path_changed @ 0x4497e0 */

004497e6        if (backend->music_stream_active != 0)
004497fc        if (strings_equal_case_insensitive_path(path, &g_cached_music_path) != 0)
004497fe        int32_t eax_2
004497fe        eax_2.b = 0
00449801        return 0
00449806        stop_music_stream(backend)
0044980b        int32_t eax_3
0044980b        eax_3.b = 1
0044980e        return 1
