/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_warning_sample @ 0x446f60 */
/* selector: stop_warning_sample */

// cRWarning::StopSample ownership recovered from Android and iOS. The Windows method stops the warning sample through the shared sound manager without reading its receiver; Android's port-specific body is a no-op.
void __thiscall stop_warning_sample(Warning *warning)
{
  int32_t v1; // eax

  v1 = play_warning_sample_backend(&g_sound_effect_manager, 50);
  stop_warning_sample_handle(&g_sound_effect_manager, v1);
}
