/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_backend @ 0x449a80 */
/* selector: play_registered_sound_sample_backend */

// AudioBackend method that forwards one registered runtime sample index plus normalized volume and pitch into the `BASS_SamplePlayEx` lane shared by the SFX and voice wrappers.
void __stdcall play_registered_sound_sample_backend(int a1, float a2, float a3)
{
  if ( a2 >= 0.0 && (a2 > 1.0 || a2 != 0.0) )
    g_bass_sample_play_ex(g_registered_sound_sample_handles[a1], 0, (__int64)a3, -1, 101, 0);
}
