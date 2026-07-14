/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame_camera @ 0x446020 */
/* selector: update_subgame_camera */

// Runs the active subgame camera update, choosing between the live cameraman follow pose, cached camera states, and direct identity handoffs before interpolating the view matrix back into the shared camera. Cross-port Android and iOS symbols match this helper to the outer `cRSubGame::CameraAI()` flow.
char __thiscall update_subgame_camera(SubgameRuntime *game)
{
  int32_t subgame_state; // eax
  float fov_degrees; // edx
  char result; // al
  TransformMatrix transform; // [esp+Ch] [ebp-80h] BYREF
  TransformMatrix from; // [esp+4Ch] [ebp-40h] BYREF

  subgame_state = game->subgame_state;
  qmemcpy(&from, &g_game_base->players[0].transform, sizeof(from));
  game->_pad_00[1] = 0;
  if ( subgame_state == 1 )
  {
    set_matrix_identity(&transform);
    transform.position.y = 3.0;
    g_game_base->players[0].camera.fov_degrees = 110.0;
  }
  else
  {
    update_cameraman(&game->player.cameraman);
    if ( game->player.presentation.cutscene.state )
    {
      game->_pad_00[1] = game->player.presentation.cutscene.force_camera_update;
      qmemcpy(&transform, &game->player.presentation.cutscene.live_matrix, sizeof(transform));
      g_game_base->players[0].camera.fov_degrees = 110.0;
    }
    else
    {
      fov_degrees = game->player.cameraman.fov_degrees;
      qmemcpy(&transform, &game->player.cameraman, sizeof(transform));
      game->_pad_00[1] = game->player.cameraman.force_camera_update;
      g_game_base->players[0].camera.fov_degrees = fov_degrees;
    }
  }
  result = game->_pad_00[1];
  if ( result )
  {
    qmemcpy(&g_game_base->players[0].transform, &transform, sizeof(g_game_base->players[0].transform));
    game->_pad_00[1] = 0;
  }
  else
  {
    linear_interpolate_matrix((TransformMatrix *)&g_game_base->players[0].transform, &from, &transform, 0.89999998);
  }
  return result;
}
