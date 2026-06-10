/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame_camera @ 0x446020 */
/* selector: update_subgame_camera */

// Runs the active subgame camera update, choosing between the live cameraman follow pose, cached camera states, and direct identity handoffs before interpolating the view matrix back into the shared camera. Cross-port Android and iOS symbols match this helper to the outer `cRSubGame::CameraAI()` flow.
char __thiscall update_subgame_camera(Game *game)
{
  int32_t subgame_state; // eax
  int v3; // edx
  char result; // al
  TransformMatrix transform; // [esp+Ch] [ebp-80h] BYREF
  TransformMatrix from; // [esp+4Ch] [ebp-40h] BYREF

  subgame_state = game->subgame_state;
  qmemcpy(&from, (char *)MEMORY[0x4DF904] + 348, sizeof(from));
  game->_pad_00[1] = 0;
  if ( subgame_state == 1 )
  {
    set_matrix_identity(&transform);
    transform.position.y = 3.0;
    *((_DWORD *)MEMORY[0x4DF904] + 161) = 1121714176;
  }
  else
  {
    update_cameraman((CameramanState *)&game->_pad_74622[3437378]);
    if ( *(_DWORD *)&game->_pad_74622[3453994] )
    {
      game->_pad_00[1] = game->_pad_74622[3454070];
      qmemcpy(&transform, &game->_pad_74622[3453998], sizeof(transform));
      *((_DWORD *)MEMORY[0x4DF904] + 161) = 1121714176;
    }
    else
    {
      v3 = *(_DWORD *)&game->_pad_74622[3437578];
      qmemcpy(&transform, &game->_pad_74622[3437378], sizeof(transform));
      game->_pad_00[1] = game->_pad_74622[3437582];
      *((_DWORD *)MEMORY[0x4DF904] + 161) = v3;
    }
  }
  result = game->_pad_00[1];
  if ( result )
  {
    qmemcpy((char *)MEMORY[0x4DF904] + 348, &transform, 0x40u);
    game->_pad_00[1] = 0;
  }
  else
  {
    linear_interpolate_matrix((TransformMatrix *)((char *)MEMORY[0x4DF904] + 348), &from, &transform, 0.89999998);
  }
  return result;
}

