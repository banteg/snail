/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_registered_sound_sample_playing @ 0x449a40 */

00449a58        return g_bass_channel_is_active(g_registered_sound_sample_handles[sample_id]) == 1
