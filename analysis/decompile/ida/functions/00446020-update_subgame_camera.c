/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame_camera @ 0x446020 */
/* selector: update_subgame_camera */

// Runs the active subgame camera update, choosing between the live cameraman follow pose, cached camera states, and direct identity handoffs before interpolating the view matrix back into the shared camera. Cross-port Android and iOS symbols match this helper to the outer `cRSubGame::CameraAI()` flow.
void __thiscall update_subgame_camera(SubgameRuntime *runtime)
{
  int32_t subgame_state; // eax
  float fov_degrees; // edx
  TransformMatrix transform; // [esp+Ch] [ebp-80h] BYREF
  TransformMatrix from; // [esp+4Ch] [ebp-40h] BYREF

  subgame_state = runtime->subgame_state;
  qmemcpy(&from, &g_game_base->players[0].body.transform, sizeof(from));
  runtime->camera_snap_requested = 0;
  if ( subgame_state == 1 )
  {
    set_matrix_identity(&transform);
    transform.position.y = 3.0;
    g_game_base->players[0].camera.fov_degrees = 110.0;
  }
  else
  {
    update_cameraman(&runtime->player.cameraman);
    if ( runtime->player.presentation.cutscene.state )
    {
      runtime->camera_snap_requested = runtime->player.presentation.cutscene.force_camera_update;
      qmemcpy(&transform, &runtime->player.presentation.cutscene.live_matrix, sizeof(transform));
      g_game_base->players[0].camera.fov_degrees = 110.0;
    }
    else
    {
      fov_degrees = runtime->player.cameraman.fov_degrees;
      qmemcpy(&transform, &runtime->player.cameraman, sizeof(transform));
      runtime->camera_snap_requested = runtime->player.cameraman.force_camera_update;
      g_game_base->players[0].camera.fov_degrees = fov_degrees;
    }
  }
  if ( runtime->camera_snap_requested )
  {
    qmemcpy(&g_game_base->players[0].body.transform, &transform, sizeof(g_game_base->players[0].body.transform));
    runtime->camera_snap_requested = 0;
  }
  else
  {
    linear_interpolate_matrix((TransformMatrix *)&g_game_base->players[0].body.transform, &from, &transform, 0.89999998);
  }
}
