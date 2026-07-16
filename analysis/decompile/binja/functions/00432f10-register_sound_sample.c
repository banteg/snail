/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_sound_sample @ 0x432f10 */

00432f18        char* path_1
00432f18        if (g_archive_index_records == 0)
00432f60        path_1 = path
00432f6c        load_registered_sound_sample_from_path(path_1, g_registered_sound_sample_count, normalization_class)
00432f20        path_1 = path
00432f2b        load_file_bytes_from_archive_or_fs(path_1, g_music_memory_buffer, &path)
00432f4f        load_registered_sound_sample_from_bytes(g_music_memory_buffer, path, g_registered_sound_sample_count, normalization_class)
00432f82        rstrcpy_checked_ascii(&g_registered_sound_sample_names[g_registered_sound_sample_count], path_1)
00432f8f        int32_t registered_sound_sample_count_1 = g_registered_sound_sample_count + 1
00432f95        g_registered_sound_sample_count = registered_sound_sample_count_1
00432f9b        if (registered_sound_sample_count_1 == 0x100)
00432fa2        g_registered_sound_sample_count = 0xff
00432fac        report_errorf("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h")
00432fb1        registered_sound_sample_count_1 = g_registered_sound_sample_count
00432fba        return registered_sound_sample_count_1 - 1
