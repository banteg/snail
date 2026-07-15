/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_slug_voice @ 0x43f560 */
/* selector: play_slug_voice */

// Exact per-slug voice trigger, gated by the embedded `SlugVoiceManager` and the slug's own cooldown. Android retains the authored member as `cRSlug::VoicePlay(int)`.
void __thiscall play_slug_voice(Slug *slug, int32_t sample_index)
{
  if ( !slug->voice_active && !g_game_base->subgame.slug_voice_manager.active )
  {
    g_game_base->subgame.slug_voice_manager.progress = g_game_base->subgame.slug_voice_manager.step;
    g_game_base->subgame.slug_voice_manager.active = 1;
    slug->voice_active = 1;
    slug->voice_progress = 0.0;
    play_voice_backend(sample_index, 1.0, -1.0, 0.0);
  }
}
