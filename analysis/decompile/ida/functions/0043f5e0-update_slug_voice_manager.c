/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_voice_manager @ 0x43f5e0 */
/* selector: update_slug_voice_manager */

// Exact update for the embedded 0x0c-byte `SlugVoiceManager`; Android retains the authored member as `cRSlugVoiceManager::AI()`.
void __thiscall update_slug_voice_manager(SlugVoiceManager *manager)
{
  double v1; // st7

  if ( manager->progress > 0.0 )
  {
    v1 = manager->step + manager->progress;
    manager->progress = v1;
    if ( v1 > 1.0 )
    {
      manager->progress = 0.0;
      manager->active = 0;
    }
  }
}
