/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop_tile_quad @ 0x41a4d0 */
/* selector: initialize_backdrop_tile_quad */

// Builds one oriented textured backdrop tile quad by choosing one of the eight UV-orientation cases and offsetting the local tile with the supplied row and column selectors.
void __cdecl sub_41A4D0(int *a1, int a2, int a3, int a4, int a5, _BYTE *a6)
{
  int v6; // edi
  int v7; // esi
  float *v8; // ecx
  int v9; // edi
  double v10; // st7
  double v11; // st7
  float v12; // [esp+0h] [ebp-4h]
  float v13; // [esp+14h] [ebp+10h]
  int v14; // [esp+14h] [ebp+10h]
  int v15; // [esp+14h] [ebp+10h]
  int v16; // [esp+14h] [ebp+10h]
  int v17; // [esp+14h] [ebp+10h]

  v12 = (double)a4 * 0.40000001;
  v13 = (double)a5 * 0.40000001;
  request_object_vertices(a1, 4);
  request_object_facequads(a1, 1);
  v6 = a1[14];
  v7 = a1[23];
  *(_DWORD *)(v6 + 4) = 0;
  *(_DWORD *)(v6 + 16) = 0;
  *(_DWORD *)(v6 + 28) = 0;
  *(_DWORD *)(v6 + 40) = 0;
  *(_WORD *)v7 = 0;
  *(_WORD *)(v7 + 2) = 0;
  *(_WORD *)(v7 + 4) = 1;
  *(_WORD *)(v7 + 6) = 3;
  *(_WORD *)(v7 + 8) = 2;
  *(_DWORD *)(v7 + 12) = get_or_create_texture_ref(&dword_4B7790, a6, 0, 0);
  *(_DWORD *)(v7 + 24) = 1045220557;
  *(_DWORD *)(v7 + 32) = 1045220557;
  *(_DWORD *)(v7 + 16) = 1061997773;
  *(_DWORD *)(v7 + 20) = 1065353216;
  *(_DWORD *)(v7 + 28) = 1065353216;
  *(_DWORD *)(v7 + 36) = 0;
  *(_DWORD *)(v7 + 40) = 1061997773;
  *(_DWORD *)(v7 + 44) = 0;
  switch ( a3 )
  {
    case 0:
      *(_DWORD *)(v6 + 24) = 1056964608;
      *(_DWORD *)(v6 + 8) = 1063675494;
      *(_DWORD *)(v6 + 20) = 1063675494;
      *(_DWORD *)(v6 + 32) = 1056964608;
      *(_DWORD *)(v6 + 36) = -1090519040;
      *(float *)v6 = v12 + 0.5;
      *(_DWORD *)(v6 + 44) = 1056964608;
      *(float *)(v6 + 12) = -0.5 - v13;
      break;
    case 1:
      sub_430A30(v7);
      *(_DWORD *)(v6 + 12) = 1056964608;
      *(_DWORD *)v6 = 1063675494;
      *(_DWORD *)(v6 + 20) = 1056964608;
      *(_DWORD *)(v6 + 24) = 1063675494;
      *(_DWORD *)(v6 + 36) = 1056964608;
      *(float *)(v6 + 8) = v13 + 0.5;
      *(_DWORD *)(v6 + 44) = -1090519040;
      *(float *)(v6 + 32) = -0.5 - v12;
      break;
    case 2:
      sub_430A30(v7);
      sub_430A30(v7);
      sub_430A30(v7);
      *(_DWORD *)v6 = -1090519040;
      *(_DWORD *)(v6 + 8) = 1056964608;
      *(_DWORD *)(v6 + 12) = -1083808154;
      *(_DWORD *)(v6 + 24) = -1090519040;
      *(float *)(v6 + 20) = v12 + 0.5;
      *(_DWORD *)(v6 + 32) = -1090519040;
      *(_DWORD *)(v6 + 36) = -1083808154;
      *(float *)(v6 + 44) = -0.5 - v13;
      break;
    case 3:
      sub_430A30(v7);
      sub_430A30(v7);
      *(_DWORD *)v6 = 1056964608;
      *(_DWORD *)(v6 + 8) = -1090519040;
      *(_DWORD *)(v6 + 12) = -1090519040;
      *(_DWORD *)(v6 + 20) = -1090519040;
      *(float *)(v6 + 24) = v13 + 0.5;
      *(_DWORD *)(v6 + 32) = -1083808154;
      *(_DWORD *)(v6 + 44) = -1083808154;
      *(float *)(v6 + 36) = -0.5 - v12;
      break;
    default:
      break;
  }
  v8 = (float *)(v6 + 8);
  v9 = 4;
  do
  {
    switch ( a2 )
    {
      case 1:
        if ( *(v8 - 2) < 0.0 && *v8 < 0.0 )
        {
          if ( *(v8 - 2) >= 0.0 )
            v14 = *(v8 - 2) != 0.0;
          else
            v14 = -1;
          *(v8 - 2) = *(v8 - 2) - (double)v14 * 0.2;
          if ( *v8 >= 0.0 )
            *v8 = *v8 - (double)(*v8 != 0.0) * 0.2;
          else
            *v8 = *v8 - (double)-1 * 0.2;
        }
        break;
      case 2:
        if ( *(v8 - 2) < 0.0 && *v8 > 0.0 )
        {
          if ( *(v8 - 2) >= 0.0 )
            v15 = *(v8 - 2) != 0.0;
          else
            v15 = -1;
          *(v8 - 2) = *(v8 - 2) - (double)v15 * 0.2;
          if ( *v8 >= 0.0 )
            *v8 = *v8 - (double)(*v8 != 0.0) * 0.2;
          else
            *v8 = *v8 - (double)-1 * 0.2;
        }
        break;
      case 3:
        if ( *(v8 - 2) > 0.0 && *v8 < 0.0 )
        {
          if ( *(v8 - 2) >= 0.0 )
            v16 = *(v8 - 2) != 0.0;
          else
            v16 = -1;
          *(v8 - 2) = *(v8 - 2) - (double)v16 * 0.2;
          if ( *v8 >= 0.0 )
            *v8 = *v8 - (double)(*v8 != 0.0) * 0.2;
          else
            *v8 = *v8 - (double)-1 * 0.2;
        }
        break;
      case 4:
        if ( *(v8 - 2) > 0.0 && *v8 > 0.0 )
        {
          if ( *(v8 - 2) >= 0.0 )
            v17 = *(v8 - 2) != 0.0;
          else
            v17 = -1;
          *(v8 - 2) = *(v8 - 2) - (double)v17 * 0.2;
          if ( *v8 >= 0.0 )
            *v8 = *v8 - (double)(*v8 != 0.0) * 0.2;
          else
            *v8 = *v8 - (double)-1 * 0.2;
        }
        break;
      case 5:
        if ( *(v8 - 2) > 0.0 )
          goto LABEL_43;
        break;
      case 6:
        goto LABEL_43;
      case 7:
        if ( *(v8 - 2) < 0.0 )
        {
LABEL_43:
          if ( *v8 > 0.0 )
          {
            v10 = *(v8 - 1);
            if ( *(_DWORD *)v8 == 1056964608 )
              v11 = v10 + 0.5;
            else
              v11 = v10 + 0.60000002;
            *(v8 - 1) = v11;
          }
        }
        break;
      default:
        break;
    }
    v8 += 3;
    --v9;
  }
  while ( v9 );
}

