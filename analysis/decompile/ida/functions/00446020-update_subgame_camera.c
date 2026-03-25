/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgame_camera @ 0x446020 */
/* selector: update_subgame_camera */

// Runs the active subgame camera update, choosing between the live cameraman follow pose, cached camera states, and direct identity handoffs before interpolating the view matrix back into the shared camera. Cross-port Android and iOS symbols match this helper to the outer `cRSubGame::CameraAI()` flow.
char __thiscall sub_446020(int this)
{
  int v2; // eax
  int v3; // edx
  char result; // al
  int v5[16]; // [esp+Ch] [ebp-80h] BYREF
  int v6[16]; // [esp+4Ch] [ebp-40h] BYREF

  v2 = *(_DWORD *)(this + 60);
  qmemcpy(v6, (char *)MEMORY[0x4DF904] + 348, sizeof(v6));
  *(_BYTE *)(this + 1) = 0;
  if ( v2 == 1 )
  {
    set_matrix_identity(v5);
    v5[13] = 1077936128;
    *((_DWORD *)MEMORY[0x4DF904] + 161) = 1121714176;
  }
  else
  {
    update_cameraman(this + 3914084);
    if ( *(_DWORD *)(this + 3930700) )
    {
      *(_BYTE *)(this + 1) = *(_BYTE *)(this + 3930776);
      qmemcpy(v5, (const void *)(this + 3930704), sizeof(v5));
      *((_DWORD *)MEMORY[0x4DF904] + 161) = 1121714176;
    }
    else
    {
      v3 = *(_DWORD *)(this + 3914284);
      qmemcpy(v5, (const void *)(this + 3914084), sizeof(v5));
      *(_BYTE *)(this + 1) = *(_BYTE *)(this + 3914288);
      *((_DWORD *)MEMORY[0x4DF904] + 161) = v3;
    }
  }
  result = *(_BYTE *)(this + 1);
  if ( !result )
    return linear_interpolate_matrix((float *)MEMORY[0x4DF904] + 87, (float *)v6, (float *)v5, 0.89999998);
  qmemcpy((char *)MEMORY[0x4DF904] + 348, v5, 0x40u);
  *(_BYTE *)(this + 1) = 0;
  return result;
}

