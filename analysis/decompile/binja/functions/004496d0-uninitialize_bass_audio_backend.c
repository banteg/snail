/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninitialize_bass_audio_backend @ 0x4496d0 */

004496d0        g_bass_stop()
004496de        if (g_bass_free() == 0)
004496e5        report_errorf("Cannot Free BASS_Free()")
004496fb        if (FreeLibrary(g_bass_module) == 0)
00449702        report_errorf("Cannot Free bass.dll library")
0044970f        delete_file_path_with_directory_walk("tBass.dll")
00449715        return
