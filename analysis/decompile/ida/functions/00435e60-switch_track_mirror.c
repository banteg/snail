/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: switch_track_mirror @ 0x435e60 */
/* selector: switch_track_mirror */

// Randomizes the runtime track mirror flag while preventing long runs of the
// same state. Game::populate_runtime_track_cells_from_segments clears the
// +0x02/+0x04 pair before row generation and reads +0x02 to mirror rows.
bool __thiscall switch_track_mirror(Game *game)
{
  double random_value; // st7
  bool mirror_enabled; // al

  random_value = random_float_below(1.0, "Mirror");
  mirror_enabled = random_value > 0.5;
  if ( random_value > 0.5 == game->track_mirror_enabled )
    ++game->track_mirror_repeat_count;
  else
    game->track_mirror_repeat_count = 0;
  if ( game->track_mirror_repeat_count >= 4 )
  {
    game->track_mirror_repeat_count = 0;
    mirror_enabled = random_value <= 0.5;
  }
  game->track_mirror_enabled = mirror_enabled;
  return mirror_enabled;
}
