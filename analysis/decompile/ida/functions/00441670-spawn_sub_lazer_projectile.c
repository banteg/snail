/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_sub_lazer_projectile @ 0x441670 */
/* selector: spawn_sub_lazer_projectile */

// Activates one slot from the 20-slot SubLazer projectile pool (`cRSubLazerManager`): stores world position and velocity, seeds the arming step from `game->track_center_x`, links the slot into the shared intrusive-list machinery, and refreshes the nested render or body object. Historically labelled `spawn_wall2_ambient_hazard`.
void __thiscall sub_441670(int this, _DWORD *a2, _DWORD *a3)
{
  int v4; // edi
  int v5; // edx
  int v6; // eax
  int v7; // edx
  double v8; // st7
  int v9; // eax
  int v10; // eax

  v4 = this + 56;
  *(_DWORD *)(this + 128) = 1;
  set_matrix_identity((_DWORD *)(this + 56));
  *(_DWORD *)(this + 104) = *a2;
  *(_DWORD *)(this + 108) = a2[1];
  *(_DWORD *)(this + 112) = a2[2];
  *(_DWORD *)(this + 140) = *a3;
  *(_DWORD *)(this + 144) = a3[1];
  v5 = a3[2];
  *(_DWORD *)(this + 152) = 0;
  *(_DWORD *)(this + 148) = v5;
  v6 = *(_DWORD *)(this + 136);
  v7 = *(_DWORD *)(this + 4);
  v8 = *(float *)(v6 + 56) * 0.0055555557;
  v9 = v6 + 3496916;
  *(float *)(this + 156) = v8;
  if ( (v7 & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
    set_matrix_z_direction(v4, v8, (_DWORD *)(this + 140));
  }
  else
  {
    *(_DWORD *)(this + 8) = v9;
    *(_DWORD *)(this + 12) = *(_DWORD *)(v9 + 12);
    *(_DWORD *)(v9 + 12) = this;
    v10 = *(_DWORD *)(this + 12);
    if ( v10 )
      *(_DWORD *)(v10 + 8) = this;
    *(_DWORD *)(this + 4) |= 0x200u;
    set_matrix_z_direction(v4, v8, (_DWORD *)(this + 140));
  }
}

