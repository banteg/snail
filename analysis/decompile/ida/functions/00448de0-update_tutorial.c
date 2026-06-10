/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tutorial @ 0x448de0 */
/* selector: update_tutorial */

TrackRowCell *__fastcall update_tutorial(TutorialController *controller)
{
  return get_track_grid_cell_at_world_position((#26 *)controller->game, (Vec3 *)((char *)controller->game + 3913676));
}

