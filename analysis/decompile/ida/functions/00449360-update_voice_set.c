/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_voice_set @ 0x449360 */
/* selector: update_voice_set */

void __thiscall update_voice_set(VoiceSet *set)
{
  double v1; // st7

  if ( set->cooldown > 0.0 )
  {
    v1 = set->cooldown_step + set->cooldown;
    set->cooldown = v1;
    if ( v1 > 1.0 )
      set->cooldown = 0.0;
  }
}
