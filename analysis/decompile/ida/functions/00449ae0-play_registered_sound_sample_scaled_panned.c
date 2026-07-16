/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled_panned @ 0x449ae0 */
/* selector: play_registered_sound_sample_scaled_panned */

// AudioBackend method that plays one registered runtime sample through BASS with normalized volume plus explicit pitch and pan overrides.
void __stdcall play_registered_sound_sample_scaled_panned(int a1, float a2, float a3, float a4)
{
  if ( a2 >= 0.0 && (a2 > 1.0 || a2 != 0.0) )
    g_bass_sample_play_ex(g_registered_sound_sample_handles[a1], 0, (__int64)a3, -1, (__int64)a4, 0);
}
