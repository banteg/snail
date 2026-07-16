/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_registered_sound_sample_playing @ 0x449a40 */
/* selector: is_registered_sound_sample_playing */

// AudioBackend method that reports whether one registered runtime sample index is active by querying its shared sound-bank table entry through BASS.
bool __thiscall is_registered_sound_sample_playing(AudioBackend *backend, int32_t sample_id)
{
  return g_bass_sample_is_active(g_registered_sound_sample_handles[sample_id]) == 1;
}
