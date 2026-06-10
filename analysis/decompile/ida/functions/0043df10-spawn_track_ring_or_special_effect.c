/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_ring_or_special_effect @ 0x43df10 */
/* selector: spawn_track_ring_or_special_effect */

// Dispatches authored Ring=* rows into the ring, explode, or slow particle effect families.
TrackRowCell *__thiscall spawn_track_ring_or_special_effect(#26 *this, int a2, int a3, int a4, float a5)
{
  TrackRowCell *result; // eax
  _DWORD *i; // ecx
  char *v8; // esi
  int v9; // ebp
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  int v17; // eax
  _DWORD *v18; // esi
  char *v19; // eax
  int v20; // ecx
  int v21; // ecx
  float v22; // [esp+10h] [ebp-10h]
  float v23; // [esp+18h] [ebp-8h]
  float v24; // [esp+18h] [ebp-8h]
  float v25; // [esp+18h] [ebp-8h]
  float v26; // [esp+18h] [ebp-8h]
  float v27; // [esp+18h] [ebp-8h]
  float v28; // [esp+18h] [ebp-8h]
  float v29; // [esp+1Ch] [ebp-4h]
  float v30; // [esp+1Ch] [ebp-4h]
  float v31; // [esp+1Ch] [ebp-4h]
  int v32; // [esp+1Ch] [ebp-4h]
  int v33; // [esp+1Ch] [ebp-4h]
  int v34; // [esp+1Ch] [ebp-4h]

  result = nullptr;
  for ( i = (_DWORD *)((char *)this + 3520524); *i; i += 126 )
  {
    result = (TrackRowCell *)((char *)result + 1);
    if ( (int)result >= 2 )
      return result;
  }
  v8 = (char *)this + 504 * (_DWORD)result;
  v22 = 1.0
      / ((2.0 - *((float *)this + 18) * 0.30000001)
       * 60.0)
      * ((double)*(int *)(a4 + 776)
       * 0.125)
      * *((float *)this + 14)
      * 6.2831855;
  set_matrix_identity((TransformMatrix *)(v8 + 3520452));
  v9 = a3;
  *((_DWORD *)v8 + 880132) = a4;
  if ( a3 == 4 && (random_float_below(1.0) > 0.93000001 || random_float_below(1.0) > 0.5 && *((_DWORD *)this + 16) == 4) )
    v9 = 3;
  switch ( v9 )
  {
    case 0:
    case 4:
      v25 = *(float *)(a2 + 20) + 2.5;
      v14 = *(float *)(a2 + 24) + 6.0;
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      v31 = v14;
      *((float *)v8 + 880126) = v25;
      *((float *)v8 + 880127) = v31;
      v15 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v15 - 0.5 + v15 - 0.5) * 3.0;
      goto LABEL_13;
    case 1:
    case 3:
      v24 = *(float *)(a2 + 20) + 2.5;
      v12 = *(float *)(a2 + 24) + 6.0;
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      v30 = v12;
      *((float *)v8 + 880126) = v24;
      *((float *)v8 + 880127) = v30;
      v13 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v13 - 0.5 + v13 - 0.5) * 3.0;
      goto LABEL_13;
    case 2:
      v23 = *(float *)(a2 + 20) + 3.5;
      v10 = *(float *)(a2 + 24) + 17.0;
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      v29 = v10;
      *((float *)v8 + 880126) = v23;
      *((float *)v8 + 880127) = v29;
      v11 = random_float_below(1.0);
      *((float *)v8 + 880125) = (v11 - 0.5 + v11 - 0.5) * 3.0;
LABEL_13:
      *((float *)v8 + 880219) = random_float_below(1.0) * 6.2831855;
      *((float *)v8 + 880220) = v22;
      break;
    case 5:
      v32 = *(_DWORD *)(a2 + 24);
      v26 = *(float *)(a2 + 20) + 2.5;
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      *((float *)v8 + 880126) = v26;
      *((_DWORD *)v8 + 880127) = v32;
      goto LABEL_19;
    case 6:
      v33 = *(_DWORD *)(a2 + 24);
      v27 = *(float *)(a2 + 20) + 2.5;
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      *((float *)v8 + 880126) = v27;
      *((_DWORD *)v8 + 880127) = v33;
      goto LABEL_19;
    case 7:
    case 8:
      v16 = *(float *)(a2 + 20) + 2.5;
      v34 = *(_DWORD *)(a2 + 24);
      *((_DWORD *)v8 + 880125) = *(_DWORD *)(a2 + 16);
      v28 = v16;
      *((float *)v8 + 880126) = v28;
      *((_DWORD *)v8 + 880127) = v34;
LABEL_19:
      *((float *)v8 + 880219) = random_float_below(1.0) * 6.2831855;
      *((float *)v8 + 880220) = 1.0 / (a5 * 60.0) * *((float *)this + 14) * 6.2831855;
      break;
    default:
      break;
  }
  result = get_track_grid_cell_at_world_position((Game *)this, (Vec3 *)v8 + 293375);
  if ( result->tile_id != 14 )
  {
    *((_DWORD *)v8 + 880133) = v9;
    *((_DWORD *)v8 + 880134) = *(_DWORD *)(a4 + 1028);
    *((_DWORD *)v8 + 880131) = 1;
    if ( random_float_below(1.0) > 0.5 )
      *((float *)v8 + 880220) = *((float *)v8 + 880220) * -1.0;
    v17 = *((_DWORD *)v8 + 880100);
    v18 = v8 + 3520396;
    if ( (v17 & 0x200) != 0 )
    {
      report_errorf(aListAdd);
    }
    else
    {
      v19 = (char *)MEMORY[0x4DF904] + 1452;
      v20 = *((_DWORD *)MEMORY[0x4DF904] + 363);
      if ( v20 )
      {
        *(_DWORD *)(v20 + 8) = v18;
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v19 + 8) + 12) = *(_DWORD *)v19;
        v21 = *(_DWORD *)(*(_DWORD *)v19 + 8);
        *(_DWORD *)v19 = v21;
        *(_DWORD *)(v21 + 8) = 0;
      }
      else
      {
        *(_DWORD *)v19 = v18;
        v18[2] = 0;
        *(_DWORD *)(*(_DWORD *)v19 + 12) = 0;
      }
      v18[1] |= 0x200u;
    }
    initialize_ring_or_special_effect_particles(v18, *(_DWORD *)(a4 + 1028));
    return (*(TrackRowCell *(__thiscall **)(_DWORD *))*v18)(v18);
  }
  return result;
}

