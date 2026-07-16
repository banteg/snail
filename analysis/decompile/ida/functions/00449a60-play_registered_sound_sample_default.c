/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_default @ 0x449a60 */
/* selector: play_registered_sound_sample_default */

// Plays one registered runtime sample index through the default `BASS_SamplePlayEx` wrapper with the hard-coded playback parameters used by the warning-owned sample path.
int32_t __thiscall play_registered_sound_sample_default(AudioBackend *backend, int32_t sample_id)
{
  return g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, -1, -1, 101, 1);
}
