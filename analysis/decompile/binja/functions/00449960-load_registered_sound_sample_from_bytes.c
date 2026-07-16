/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */

00449984        g_registered_sound_sample_handles[sample_id] = g_bass_sample_load(1, bytes, 0, byte_count, normalization_class, 0x20010)
00449998        return
