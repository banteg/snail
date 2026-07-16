/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_default @ 0x449a60 */

00449a7c        return g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, 0xffffffff, 0xffffffff, 0x65, 1)
