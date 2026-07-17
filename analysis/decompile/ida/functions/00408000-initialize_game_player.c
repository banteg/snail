/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_player @ 0x408000 */
/* selector: initialize_game_player */

// Constructs one 0x1f8-byte Windows cRPlayer record: initializes its inherited renderable body, constructs the owned cRCamera subobject at +0xa0, constructs the target/current colors of the owned FrontendOverlayColorLerp at +0x184, and installs the cRPlayer::AI callback.
GamePlayer *__thiscall initialize_game_player(GamePlayer *player)
{
  initialize_renderable_bod((RenderableBod *)player);
  initialize_renderable_bod((RenderableBod *)&player->camera);
  player->camera.body.bod.bod.vtable = &g_noop_runtime_callback_table;
  noop_this_constructor(&player->frontend_overlay.target);
  noop_this_constructor(&player->frontend_overlay.current);
  player->body.bod.bod.vtable = &g_game_player_callback_table;
  return player;
}
