/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_warning_sample @ 0x432dd0 */
/* selector: play_registered_warning_sample */

// Windows RShellSoundPlayLooped entry point: forwards one registered warning sample id to the process audio backend's looped default sample-play method and returns the live playback handle.
int __cdecl play_registered_warning_sample(int sample_id)
{
  return play_registered_sound_sample_default((AudioBackend *)g_audio_backend, sample_id);
}
