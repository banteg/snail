/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: register_sound_sample @ 0x432f10 */

00432f18        char* esi
00432f18        if (g_archive_index_records == 0)
00432f60        esi = arg1
00432f6c        load_registered_sound_sample_from_path(esi, g_registered_sound_sample_count, arg2)
00432f20        esi = arg1
00432f2b        load_file_bytes_from_archive_or_fs(esi, g_music_memory_buffer, &arg1)
00432f4f        load_registered_sound_sample_from_bytes(g_music_memory_buffer, arg1, g_registered_sound_sample_count, arg2)
00432f82        rstrcpy_checked_ascii((g_registered_sound_sample_count << 7) + &g_registered_sound_sample_names, esi)
00432f8f        int32_t eax_3 = g_registered_sound_sample_count + 1
00432f95        g_registered_sound_sample_count = eax_3
00432f9b        if (eax_3 == 0x100)
00432fa2        g_registered_sound_sample_count = 0xff
00432fac        report_errorf("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h")
00432fb1        eax_3 = g_registered_sound_sample_count
00432fba        return eax_3 - 1
