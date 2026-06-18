/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: run_frame_update @ 0x40a2a0 */
/* selector: run_frame_update */

int __thiscall sub_40A2A0(int this)
{
  double v2; // st7
  int v3; // ebx
  int v4; // edx
  int *v5; // eax
  int v6; // edi
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int *v10; // edi
  int v11; // ecx
  int v12; // esi
  double v13; // st7
  int v15; // [esp+0h] [ebp-38h]
  int v16; // [esp+4h] [ebp-34h]
  int v17; // [esp+24h] [ebp-14h]
  _DWORD v18[4]; // [esp+28h] [ebp-10h] BYREF

  update_frontend_transition_overlay((float *)(this + 36));
  noop_runtime_ai(unk_753C58);
  update_cheat(&byte_4B2F40);
  update_voice_manager(unk_751498);
  v2 = *(float *)(this + 1304) + 1.0;
  v3 = 0;
  v4 = *(_DWORD *)(this + 1308) + 1;
  *(_DWORD *)(this + 56) = 0;
  *(float *)(this + 1304) = v2;
  *(_DWORD *)(this + 60) = 1;
  *(_DWORD *)(this + 1308) = v4;
  *(_BYTE *)(this + 1312) = 1;
  v17 = 0;
  if ( is_mouse_captured((void *)(this + 656)) )
  {
    if ( *(_BYTE *)(this + 676) )
    {
      *(_BYTE *)(this + 676) = 0;
    }
    else
    {
      v5 = set_color_rgba(v18, 1065353216, 1065353216, 1065353216, 1065353216);
      *(float *)&v16 = *(float *)(this + 672) - 7.0;
      *(float *)&v15 = *(float *)(this + 668) - 8.0;
      queue_axis_aligned_textured_quad(22, v15, v16, 1115684864, 1115684864, 0x1000000, v5, 7);
    }
  }
  if ( *(float *)(this + 1304) <= 1.0 )
    return *(_DWORD *)(this + 56);
  do
  {
    *(float *)(this + 1304) = *(float *)(this + 1304) - 1.0;
    draw_frontend_overlay_color_lerp((void *)(this + 680));
    v6 = *(_DWORD *)(this + 1452);
    if ( v6 )
    {
      while ( 1 )
      {
        if ( (*(_BYTE *)(v6 + 4) & 0x10) != 0 )
          report_errorf(aDebugBodAi);
        v7 = *(_DWORD *)(v6 + 12);
        if ( v7 )
        {
          v8 = *(_DWORD *)(v7 + 4);
          LOBYTE(v8) = v8 | 0x40;
          *(_DWORD *)(v7 + 4) = v8;
        }
        (**(void (__thiscall ***)(int))v6)(v6);
        v6 = v7;
        ++v17;
        if ( !v7 )
          break;
        v9 = *(_DWORD *)(v7 + 4);
        LOBYTE(v9) = v9 & 0xBF;
        *(_DWORD *)(v7 + 4) = v9;
      }
    }
    (**(void (__thiscall ***)(int))(this + 292))(this + 292);
    if ( *(_DWORD *)(this + 476760) == 6 )
      (**(void (__thiscall ***)(int))(this + 796))(this + 796);
    v10 = g_sprite_active_heads;
    do
    {
      v11 = *v10;
      if ( *v10 )
      {
        do
        {
          v12 = *(_DWORD *)(v11 + 12);
          update_sprite(v11);
          ++v3;
          v11 = v12;
        }
        while ( v12 );
      }
      ++v10;
    }
    while ( (int)v10 < (int)&g_sprite_free_head );
    initialize_enemy_manager((#94 *)(this + 19813868));
    v13 = *(float *)(this + 1304);
    *(_BYTE *)(this + 1312) = 0;
  }
  while ( v13 > 1.0 );
  return *(_DWORD *)(this + 56);
}

