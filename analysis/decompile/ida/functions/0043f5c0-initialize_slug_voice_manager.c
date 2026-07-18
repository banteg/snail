/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_slug_voice_manager @ 0x43f5c0 */
/* selector: initialize_slug_voice_manager */

// Exact initializer for the 0x0c-byte `SlugVoiceManager` embedded at `SubgameRuntime +0x35bb7c`. Android retains the authored owner as `cRSlugVoiceManager::Init()`.
void __thiscall initialize_slug_voice_manager(SlugVoiceManager *manager)
{
  manager->active = 0;
  manager->progress = 0.0;
  manager->step = 0.016666668;
}
