/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: switch_track_mirror @ 0x435e60 */
/* selector: switch_track_mirror */

// Windows `void cRSubGame::SwitchMirror()`: selects a row-mirror state from a strict random > 0.5 test, counts repeated choices, and forces an inversion after four repeats. Android preserves the owner and algorithm while leaving RAND's float bits in R0; both Windows call sites ignore EAX.
void __thiscall switch_track_mirror(cRSubGame *runtime)
{
  uint8_t v2; // al

  v2 = random_float_below(1.0, g_rng_tag_mirror) > 0.5;
  if ( v2 == runtime->track_mirror_enabled )
    ++runtime->track_mirror_repeat_count;
  else
    runtime->track_mirror_repeat_count = 0;
  if ( runtime->track_mirror_repeat_count >= 4 )
  {
    runtime->track_mirror_repeat_count = 0;
    v2 = v2 == 0;
  }
  runtime->track_mirror_enabled = v2;
}
