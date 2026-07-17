/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_slug_hazard @ 0x43dc80 */
/* selector: spawn_slug_hazard */

// Exact allocator for one live `Slug`: scans the eight owned 0xec-byte records, installs the borrowed owner Player, scales `(0, 0, -0.2)` by the subgame rate, links the inherited body before the embedded Player tail, and arms the spaced engagement-voice gate. Android and iOS identify the owning caller as `cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)`. The Windows result shape remains intentionally unresolved: its sole caller discards EAX, but a void probe removes two native instructions.
int __thiscall spawn_slug_hazard(int this, int a2, int a3)
{
  int result; // eax
  _DWORD *i; // ecx
  int v6; // esi
  double v7; // st7
  double v8; // st7
  BodNode *v9; // eax
  BodList *p_active_bod_list; // edx
  BodNode *v11; // ecx
  int v12; // ecx
  _DWORD *sprite; // eax
  int v14; // ecx
  _DWORD *v15; // eax
  int v16; // eax
  float v17; // [esp+8h] [ebp-8h]
  int v18; // [esp+Ch] [ebp-4h]
  float v19; // [esp+Ch] [ebp-4h]

  result = 0;
  for ( i = (_DWORD *)(this + 3499040); *i; i += 59 )
  {
    if ( ++result >= 8 )
      return result;
  }
  v6 = this + 236 * result;
  *(_DWORD *)(v6 + 3499040) = 1;
  *(_DWORD *)(v6 + 3499104) = a3;
  set_matrix_identity((TransformMatrix *)(v6 + 3498968));
  v7 = *(float *)(a2 + 20) + 1.7;
  v18 = *(_DWORD *)(a2 + 24);
  *(_DWORD *)(v6 + 3499016) = *(_DWORD *)(a2 + 16);
  v17 = v7;
  *(float *)(v6 + 3499020) = v17;
  *(_DWORD *)(v6 + 3499024) = v18;
  project_position_onto_track_attachment((void *)this, (float *)(v6 + 3499016), (float *)(v6 + 3499064));
  v8 = *(float *)(this + 56) * -0.2;
  *(float *)(v6 + 3499052) = 0.0;
  *(float *)(v6 + 3499056) = 0.0;
  v9 = (BodNode *)(v6 + 3498912);
  v19 = v8;
  *(float *)(v6 + 3499060) = v19;
  p_active_bod_list = &g_game_base->active_bod_list;
  v11 = (BodNode *)(this + 3913572);
  if ( (*(_BYTE *)(v6 + 3498917) & 2) != 0 )
  {
    report_errorf(aListAddbefore);
  }
  else
  {
    *(_DWORD *)(v6 + 3498924) = v11;
    if ( p_active_bod_list->first == v11 )
    {
      *(_DWORD *)(this + 3913580) = v9;
      p_active_bod_list->first = v9;
      *(_DWORD *)(v6 + 3498920) = 0;
    }
    else
    {
      *(_DWORD *)(v6 + 3498920) = *(_DWORD *)(this + 3913580);
      *(_DWORD *)(this + 3913580) = v9;
      *(_DWORD *)(*(_DWORD *)(v6 + 3498920) + 12) = v9;
    }
    v12 = *(_DWORD *)(v6 + 3498916);
    BYTE1(v12) |= 2u;
    *(_DWORD *)(v6 + 3498916) = v12;
  }
  sprite = allocate_sprite(g_sprite_manager, *(_DWORD *)(a3 + 896), 118, -1, -1);
  *(_DWORD *)(v6 + 3499084) = sprite;
  v14 = sprite[1];
  BYTE1(v14) |= 8u;
  sprite[1] = v14;
  set_color_white((tColour *)(*(_DWORD *)(v6 + 3499084) + 44));
  *(_DWORD *)(*(_DWORD *)(v6 + 3499084) + 120) = 0;
  *(_DWORD *)(*(_DWORD *)(v6 + 3499084) + 104) = 0;
  *(_DWORD *)(*(_DWORD *)(v6 + 3499084) + 108) = 0;
  *(_DWORD *)(*(_DWORD *)(v6 + 3499084) + 96) = 0x40000000;
  *(_DWORD *)(*(_DWORD *)(v6 + 3499084) + 100) = 0x40000000;
  v15 = (_DWORD *)(*(_DWORD *)(v6 + 3499084) + 72);
  *v15 = *(_DWORD *)(v6 + 3499016);
  v15[1] = *(_DWORD *)(v6 + 3499020);
  v15[2] = *(_DWORD *)(v6 + 3499024);
  *(_DWORD *)(v6 + 3499088) = a2;
  *(_BYTE *)(v6 + 3499092) = 0;
  *(_BYTE *)(v6 + 3499116) = 0;
  *(_DWORD *)(v6 + 3499120) = 0;
  *(float *)(v6 + 3499124) = g_game_base->subgame.subgame_rate * 0.16666667;
  *(_DWORD *)(v6 + 3499112) = 7;
  v16 = *(_DWORD *)(v6 + 3498916);
  BYTE1(v16) &= ~0x10u;
  *(_DWORD *)(v6 + 3498916) = v16;
  *(_BYTE *)(v6 + 3499128) = 0;
  *(_BYTE *)(v6 + 3499129) = 0;
  *(_DWORD *)(v6 + 3499132) = 0;
  *(_DWORD *)(v6 + 3499136) = 1023969417;
  if ( *(float *)(a2 + 24) > (double)*(float *)(this + 19337164) )
  {
    *(_DWORD *)(v6 + 3499108) = 1;
    *(float *)(this + 19337164) = *(float *)(this + 19337168) + *(float *)(this + 19337164);
  }
  *(_DWORD *)(v6 + 3499140) = 0;
  result = next_math_random_value();
  *(float *)(v6 + 3499144) = 1.0 / (((double)result * 0.000030517578 + 1.0) * 60.0);
  return result;
}
