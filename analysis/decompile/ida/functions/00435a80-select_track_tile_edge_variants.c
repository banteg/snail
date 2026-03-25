/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_track_tile_edge_variants @ 0x435a80 */
/* selector: select_track_tile_edge_variants */

// Computes neighbor masks and chooses edge or corner variants for special runtime tile classes. Cross-port Android and iOS symbols match this pass to `cRSubGame::SmoothTrack()`.
int __thiscall sub_435A80(int *this)
{
  int result; // eax
  int v2; // edi
  _DWORD *v3; // esi
  int i; // ebp
  int v5; // edx
  char v6; // al
  char v7; // al
  int v8; // edx
  char v9; // al
  char v10; // al
  char v11; // al
  int v12; // [esp-10h] [ebp-1Ch]
  int v13; // [esp+4h] [ebp-8h]

  result = *(this + 21);
  v2 = 0;
  v13 = 0;
  if ( result > 0 )
  {
    v3 = this + 982721;
    do
    {
      for ( i = 0; i < 8; ++i )
      {
        *((_BYTE *)v3 + 1) = 0;
        v5 = v3[1];
        BYTE1(v5) &= ~0x80u;
        v3[1] = v5;
        v6 = *(_BYTE *)v3;
        if ( *(_BYTE *)v3 && v6 != 35 && v6 != 28 && v6 != 29 && v6 != 30 && v6 != 14 )
        {
          if ( !i || is_open_neighbor_tile_family((_BYTE *)v3 - 144) )
            *((_BYTE *)v3 + 1) |= 8u;
          if ( i == 7 || is_open_neighbor_tile_family((_BYTE *)v3 + 24) )
            *((_BYTE *)v3 + 1) |= 4u;
          if ( !v2 || is_open_neighbor_tile_family((_BYTE *)v3 - 732) )
            *((_BYTE *)v3 + 1) |= 1u;
          if ( v2 >= *(this + 21) - 1 || is_open_neighbor_tile_family((_BYTE *)v3 + 612) )
            *((_BYTE *)v3 + 1) |= 2u;
          switch ( *((_BYTE *)v3 + 1) )
          {
            case 5:
              v3[1] |= 0x8000u;
              v9 = *(_BYTE *)v3;
              if ( *(_BYTE *)v3 == 1 || v9 == 20 || v9 == 21 || v9 == 27 || v9 == 33 || v9 == 34 )
              {
                v12 = *((_DWORD *)MEMORY[0x4DF904] + 69789);
                goto LABEL_68;
              }
              if ( v9 != 22 && v9 != 14 && !is_ramp_cache_tile_family((_BYTE *)v3 - 60) )
                set_bod_object(v3 - 15, *((_DWORD *)MEMORY[0x4DF904] + 69901));
              break;
            case 6:
              v3[1] |= 0x8000u;
              v11 = *(_BYTE *)v3;
              if ( *(_BYTE *)v3 == 1 || v11 == 20 || v11 == 21 || v11 == 27 || v11 == 33 || v11 == 34 )
              {
                v8 = *((_DWORD *)MEMORY[0x4DF904] + 69817);
                goto LABEL_67;
              }
              if ( v11 != 22 && v11 != 14 && !is_ramp_cache_tile_family((_BYTE *)v3 - 60) )
                set_bod_object(v3 - 15, *((_DWORD *)MEMORY[0x4DF904] + 69929));
              break;
            case 9:
              v3[1] |= 0x8000u;
              v7 = *(_BYTE *)v3;
              if ( *(_BYTE *)v3 == 1 || v7 == 20 || v7 == 21 || v7 == 27 || v7 == 33 || v7 == 34 )
              {
                v8 = *((_DWORD *)MEMORY[0x4DF904] + 69775);
LABEL_67:
                v12 = v8;
                goto LABEL_68;
              }
              if ( v7 != 22 && v7 != 14 && !is_ramp_cache_tile_family((_BYTE *)v3 - 60) )
                set_bod_object(v3 - 15, *((_DWORD *)MEMORY[0x4DF904] + 69887));
              break;
            case 0xA:
              v3[1] |= 0x8000u;
              v10 = *(_BYTE *)v3;
              if ( *(_BYTE *)v3 == 1 || v10 == 20 || v10 == 21 || v10 == 27 || v10 == 33 || v10 == 34 )
              {
                v12 = *((_DWORD *)MEMORY[0x4DF904] + 69803);
LABEL_68:
                set_bod_object(v3 - 15, v12);
              }
              else if ( v10 != 22 && v10 != 14 && !is_ramp_cache_tile_family((_BYTE *)v3 - 60) )
              {
                set_bod_object(v3 - 15, *((_DWORD *)MEMORY[0x4DF904] + 69915));
              }
              break;
            default:
              break;
          }
        }
        v2 = v13;
        v3 += 21;
      }
      result = (int)this;
      v2 = v13 + 1;
      v13 = v2;
    }
    while ( v2 < *(this + 21) );
  }
  return result;
}

