/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_sound_sample_from_path @ 0x449920 */

00449936        int32_t result = g_bass_sample_load(0, path, 0, 0, normalization_class, 0x20010)
00449942        g_registered_sound_sample_handles[sample_id] = result
00449949        if (result != 0)
0044995a        return result
00449951        return debug_report_stub("Bass Sample Load Fail %s\n", path)
