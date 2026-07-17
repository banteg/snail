/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_warning_sample_handle @ 0x44de30 */
/* selector: stop_warning_sample_handle */

// Exact SoundEffectManager warning wrapper that stops one live warning-sample handle through the shared registered-sample backend.
void __thiscall stop_warning_sample_handle(SoundEffectManager *manager, int32_t handle)
{
  stop_registered_warning_sample(handle);
}
