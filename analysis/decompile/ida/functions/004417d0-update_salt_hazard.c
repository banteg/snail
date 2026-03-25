/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_salt_hazard @ 0x4417d0 */
/* selector: update_salt_hazard */

// Integrates one active salt hazard, tests track attachment intersection, and deactivates it after collision or exit.
void __thiscall sub_4417D0(int this)
{
  int v2; // eax
  char *v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  double v7; // st7
  float *v8; // edi
  char *v9; // ebp
  char *v10; // ebx
  int v11; // [esp+10h] [ebp-18h]
  float v12; // [esp+10h] [ebp-18h]
  int v13; // [esp+14h] [ebp-14h]
  float v14; // [esp+14h] [ebp-14h]
  int v15; // [esp+18h] [ebp-10h]
  float v16; // [esp+18h] [ebp-10h]
  float v17; // [esp+1Ch] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-Ch]
  float v19; // [esp+20h] [ebp-8h]
  int v20; // [esp+20h] [ebp-8h]
  float v21; // [esp+24h] [ebp-4h]
  int v22; // [esp+24h] [ebp-4h]

  if ( *(_BYTE *)(*(_DWORD *)(this + 136) + 9) )
    return;
  if ( *(_DWORD *)(this + 128) == 1 )
  {
    v7 = *(float *)(this + 156) + *(float *)(this + 152);
    *(float *)(this + 152) = v7;
    if ( v7 > 1.0 )
    {
      *(_DWORD *)(this + 128) = 2;
      return;
    }
    v8 = (float *)(this + 104);
    *(float *)(this + 104) = *(float *)(this + 140) + *(float *)(this + 104);
    *(float *)(this + 108) = *(float *)(this + 144) + *(float *)(this + 108);
    *(float *)(this + 112) = *(float *)(this + 148) + *(float *)(this + 112);
    if ( *(float *)(this + 108) >= 0.0
      && *(float *)(this + 112) >= (double)*(float *)(*(_DWORD *)(this + 136) + 3924196) )
    {
      v9 = get_track_grid_cell_at_world_position((char *)MEMORY[0x4DF904] + 476696, (float *)(this + 104));
      v10 = get_track_runtime_cell_at_world_z((char *)MEMORY[0x4DF904] + 476696, this + 104);
      if ( v9[60] != 14 || *(float *)(this + 108) >= 7.0 )
      {
        if ( (*v10 & 0x40) == 0
          || (*(float *)&v11 = *(float *)(this + 140) * 1.05,
              *(float *)&v13 = *(float *)(this + 144) * 1.05,
              *(float *)&v15 = *(float *)(this + 148) * 1.05,
              v17 = *(float *)(this + 140) + *v8,
              v19 = *(float *)(this + 144) + *(float *)(this + 108),
              v21 = *(float *)(this + 148) + *(float *)(this + 112),
              !is_point_inside_track_attachment(
                 *(_DWORD **)(*((_DWORD *)v10 + 41) + 56),
                 v17,
                 v19,
                 v21,
                 v11,
                 v13,
                 v15,
                 *((float **)v10 + 41))) )
        {
          if ( *v10 >= 0 )
            return;
          *(float *)&v18 = *(float *)(this + 140) * 1.05;
          *(float *)&v20 = *(float *)(this + 144) * 1.05;
          *(float *)&v22 = *(float *)(this + 148) * 1.05;
          v12 = *(float *)(this + 140) + *v8;
          v14 = *(float *)(this + 144) + *(float *)(this + 108);
          v16 = *(float *)(this + 148) + *(float *)(this + 112);
          if ( !is_point_inside_track_attachment(
                  *(_DWORD **)(*((_DWORD *)v10 + 42) + 56),
                  v12,
                  v14,
                  v16,
                  v18,
                  v20,
                  v22,
                  *((float **)v10 + 42)) )
            return;
        }
        sub_449C00();
      }
    }
    deactivate_salt_hazard((_DWORD *)this);
    return;
  }
  if ( *(_DWORD *)(this + 128) == 2 )
  {
    v2 = *(_DWORD *)(this + 4);
    v3 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v2 & 0x200) != 0 )
    {
      if ( (v2 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        *(_DWORD *)(this + 128) = 0;
      }
      else
      {
        v4 = *(_DWORD *)(this + 12);
        if ( v4 )
          *(_DWORD *)(v4 + 8) = *(_DWORD *)(this + 8);
        v5 = *(_DWORD *)(this + 8);
        if ( v5 )
          *(_DWORD *)(v5 + 12) = *(_DWORD *)(this + 12);
        else
          *((_DWORD *)v3 + 1) = *(_DWORD *)(this + 12);
        *(_DWORD *)(this + 12) = *((_DWORD *)v3 + 2);
        *((_DWORD *)v3 + 2) = this;
        v6 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 128) = 0;
        BYTE1(v6) &= ~2u;
        *(_DWORD *)(this + 4) = v6;
      }
    }
    else
    {
      report_errorf(aListRemove);
      *(_DWORD *)(this + 128) = 0;
    }
  }
}

