/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: harmonize_center_lane_floor_slide_variants @ 0x4356f0 */
/* selector: harmonize_center_lane_floor_slide_variants */

// Normalizes center-lane floor and slide seam variants after the main edge pass. Cross-port Android and iOS symbols match this pass to `cRSubGame::SlideSmoothTrack()`.
int __thiscall sub_4356F0(_DWORD *this)
{
  _DWORD *v1; // esi
  int result; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  char v6; // al
  _DWORD *v7; // esi
  char *v8; // eax
  int j; // edi
  char *v10; // eax
  int k; // edi
  _DWORD *v12; // esi
  char *v13; // eax
  int m; // edi
  char *v15; // eax
  int n; // edi
  int i; // [esp+4h] [ebp-10h]
  int v18; // [esp+8h] [ebp-Ch]
  int v20; // [esp+10h] [ebp-4h]

  v1 = this;
  result = 0;
  for ( i = 0; result < *(this + 21) - 1; i = result )
  {
    v3 = 0;
    v4 = result & 7;
    v18 = 0;
    v20 = v4;
    while ( 1 )
    {
      if ( v4 == 3 )
      {
        v5 = v3 + 8 * result;
        v6 = v1[21 * v5 + 982722];
        v7 = &v1[21 * v5];
        if ( (v6 & 0x20) == 0 )
        {
          if ( (v7[982890] & 0x20) == 0
            && is_slide_cache_tile_family((_BYTE *)v7 + 3930824)
            && (is_floor_cache_tile_family((_BYTE *)v7 + 3931496) || *((_BYTE *)v7 + 3931556) == 30) )
          {
            v8 = (char *)MEMORY[0x4DF904];
            if ( v7[982715] == *((_DWORD *)MEMORY[0x4DF904] + 70125) )
            {
              set_bod_object(v7 + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
              v7[982722] |= 0x40u;
              v8 = (char *)MEMORY[0x4DF904];
            }
            for ( j = 0; j < 224; j += 56 )
            {
              if ( v7[982715] == *(_DWORD *)&v8[j + 279100] )
              {
                set_bod_object(v7 + 982706, *(_DWORD *)&v8[j + 279548]);
                v7[982722] |= 0x40u;
                v8 = (char *)MEMORY[0x4DF904];
              }
            }
          }
          if ( (v7[982722] & 0x20) == 0
            && (v7[982890] & 0x20) == 0
            && is_floor_cache_tile_family((_BYTE *)v7 + 3930824)
            && is_slide_cache_tile_family((_BYTE *)v7 + 3931496) )
          {
            v10 = (char *)MEMORY[0x4DF904];
            if ( v7[982715] == *((_DWORD *)MEMORY[0x4DF904] + 70349) )
            {
              set_bod_object(v7 + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
              v7[982722] |= 0x40u;
              v10 = (char *)MEMORY[0x4DF904];
            }
            for ( k = 0; k < 224; k += 56 )
            {
              if ( v7[982715] == *(_DWORD *)&v10[k + 279548] )
              {
                set_bod_object(v7 + 982706, *(_DWORD *)&v10[k + 279100]);
                v7[982722] |= 0x40u;
                v10 = (char *)MEMORY[0x4DF904];
              }
            }
          }
        }
      }
      else if ( v4 == 5 )
      {
        v12 = &v1[168 * result + 21 * v3];
        if ( (v12[982722] & 0x20) == 0 )
        {
          if ( (v12[982554] & 0x20) == 0
            && is_slide_cache_tile_family((_BYTE *)v12 + 3930824)
            && (is_floor_cache_tile_family((_BYTE *)v12 + 3930152) || *((_BYTE *)v12 + 3930212) == 32) )
          {
            v13 = (char *)MEMORY[0x4DF904];
            if ( v12[982715] == *((_DWORD *)MEMORY[0x4DF904] + 70125) )
            {
              set_bod_object(v12 + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70349));
              v12[982722] |= 0x40u;
              v13 = (char *)MEMORY[0x4DF904];
            }
            for ( m = 0; m < 224; m += 56 )
            {
              if ( v12[982715] == *(_DWORD *)&v13[m + 279100] )
              {
                set_bod_object(v12 + 982706, *(_DWORD *)&v13[m + 279548]);
                v12[982722] |= 0x40u;
                v13 = (char *)MEMORY[0x4DF904];
              }
            }
          }
          if ( (v12[982722] & 0x20) == 0
            && (v12[982554] & 0x20) == 0
            && is_floor_cache_tile_family((_BYTE *)v12 + 3930824)
            && is_slide_cache_tile_family((_BYTE *)v12 + 3930152) )
          {
            v15 = (char *)MEMORY[0x4DF904];
            if ( v12[982715] == *((_DWORD *)MEMORY[0x4DF904] + 70349) )
            {
              set_bod_object(v12 + 982706, *((_DWORD *)MEMORY[0x4DF904] + 70125));
              v12[982722] |= 0x40u;
              v15 = (char *)MEMORY[0x4DF904];
            }
            for ( n = 0; n < 224; n += 56 )
            {
              if ( v12[982715] == *(_DWORD *)&v15[n + 279548] )
              {
                set_bod_object(v12 + 982706, *(_DWORD *)&v15[n + 279100]);
                v12[982722] |= 0x40u;
                v15 = (char *)MEMORY[0x4DF904];
              }
            }
          }
        }
      }
      v3 = ++v18;
      if ( v18 >= 8 )
        break;
      v4 = v20;
      v1 = this;
      result = i;
    }
    v1 = this;
    result = i + 1;
  }
  return result;
}

