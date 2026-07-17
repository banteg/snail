/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_warning_sample_backend @ 0x44de20 */
/* selector: play_warning_sample_backend */

// Exact SoundEffectManager warning wrapper that plays one sample id through the shared registered-sample backend and returns the live sample handle.
int32_t __thiscall play_warning_sample_backend(SoundEffectManager *manager, int32_t sample_id)
{
  return play_registered_warning_sample(sample_id);
}
