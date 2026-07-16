/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_registered_warning_sample @ 0x432de0 */
/* selector: stop_registered_warning_sample */

// Windows RShellSoundStopLooped entry point: forwards one live warning playback handle to the process audio backend's handle-stop method.
int __cdecl stop_registered_warning_sample(int sample_handle)
{
  return stop_sound_sample_handle(sample_handle);
}
