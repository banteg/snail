/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_voice_ai @ 0x43f520 */
/* selector: update_slug_voice_ai */

// Exact per-slug voice cooldown update. Android retains the authored member as `cRSlug::VoiceAI()`.
void __thiscall update_slug_voice_ai(Slug *slug)
{
  double v1; // st7

  if ( slug->voice_active )
  {
    v1 = slug->voice_progress_step + slug->voice_progress;
    slug->voice_progress = v1;
    if ( v1 > 1.0 )
    {
      slug->voice_progress = 0.0;
      slug->voice_active = 0;
    }
  }
}
