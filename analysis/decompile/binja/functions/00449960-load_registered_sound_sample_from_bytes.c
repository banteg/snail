/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */

00449978        int32_t result = g_bass_sample_load(1, arg1, 0, arg2, arg4, 0x20010)
00449984        g_registered_sound_sample_handles[arg3] = result
0044998b        if (result == 0)
00449992        result = debug_report_stub("***ERROR:Bass Sample Load Memory Fail\n")
00449998        return result
