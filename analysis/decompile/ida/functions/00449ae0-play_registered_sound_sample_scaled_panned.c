/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled_panned @ 0x449ae0 */
/* selector: play_registered_sound_sample_scaled_panned */

// AudioBackend method that plays one registered runtime sample through BASS with normalized volume plus explicit pitch and pan overrides.
void __thiscall play_registered_sound_sample_scaled_panned(
        AudioBackend *backend,
        int32_t sample_id,
        float volume,
        float pitch,
        float pan)
{
  if ( volume >= 0.0 && (volume > 1.0 || volume != 0.0) )
    g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, (__int64)pitch, -1, (__int64)pan, 0);
}
