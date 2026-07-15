/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tutorial @ 0x448de0 */
/* selector: update_tutorial */

// Exact void Windows Tutorial::update_tutorial thunk: samples the live Goldy position through the borrowed containing SubgameRuntime. Its only native caller discards the lookup result, and Android/iOS retain cRTutorial::AI().
void __thiscall update_tutorial(Tutorial *tutorial)
{
  get_track_grid_cell_at_world_position(tutorial->game, &tutorial->game->player.body.transform.position);
}
