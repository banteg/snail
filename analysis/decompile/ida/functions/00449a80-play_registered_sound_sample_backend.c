/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_backend @ 0x449a80 */
/* selector: play_registered_sound_sample_backend */

// AudioBackend method that forwards one registered runtime sample index plus normalized volume and pitch into the `BASS_SamplePlayEx` lane shared by the SFX and voice wrappers.
void __thiscall play_registered_sound_sample_backend(
        AudioBackend *backend,
        int32_t sample_id,
        float volume,
        float pitch)
{
  if ( volume >= 0.0 && (volume > 1.0 || volume != 0.0) )
    g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, (__int64)pitch, -1, 101, 0);
}
