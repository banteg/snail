/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_player @ 0x408000 */
/* selector: initialize_game_player */

// Constructs one 0x1f8-byte Windows cRPlayer record: initializes its inherited renderable body, constructs the owned cRCamera subobject at +0xa0, constructs two owned colors at +0x188/+0x198, and installs the cRPlayer::AI callback.
GamePlayer *__thiscall initialize_game_player(GamePlayer *player)
{
  initialize_renderable_bod(player);
  initialize_renderable_bod(player->camera.unknown_00);
  *(_DWORD *)player->camera.unknown_00 = &g_overlay_stream_callback_table;
  noop_this_constructor(&player->frontend_overlay.target);
  noop_this_constructor(&player->frontend_overlay.current);
  player->vtable = g_unknown_composite_runtime_callback_table;
  return player;
}
