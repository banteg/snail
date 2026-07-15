/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: switch_track_mirror @ 0x435e60 */
/* selector: switch_track_mirror */

bool __thiscall switch_track_mirror(SubgameRuntime *runtime)
{
  bool result; // al

  result = random_float_below(1.0) > 0.5;
  if ( result == runtime->track_mirror_enabled )
    ++runtime->track_mirror_repeat_count;
  else
    runtime->track_mirror_repeat_count = 0;
  if ( runtime->track_mirror_repeat_count >= 4 )
  {
    runtime->track_mirror_repeat_count = 0;
    result = !result;
  }
  runtime->track_mirror_enabled = result;
  return result;
}
