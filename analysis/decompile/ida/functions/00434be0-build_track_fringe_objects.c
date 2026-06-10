/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_fringe_objects @ 0x434be0 */
/* selector: build_track_fringe_objects */

// Allocates directional fringe objects around runtime cells for the post-build renderer, using the shared fringe-manager pool at `data_4df904 + 0x3d01d4`.
int32_t __thiscall build_track_fringe_objects(Game *game)
{
  Game *v1; // ebp
  int v2; // ebx
  char *v3; // edx
  uint8_t *v4; // esi
  uint8_t v5; // cl
  int v6; // edi
  uint8_t v7; // al
  int v8; // ebp
  _DWORD *fringe_object; // eax
  _DWORD *v10; // eax
  _DWORD *track_skirt_color; // eax
  _DWORD *v12; // edx
  int v13; // ebp
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  _DWORD *v17; // edx
  int v18; // ebp
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  _DWORD *v21; // eax
  _DWORD *v22; // edx
  int v23; // ebp
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  _DWORD *v26; // eax
  _DWORD *v27; // edx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  bool v32; // cc
  int v35; // [esp+Ch] [ebp-4Ch]
  int v36; // [esp+10h] [ebp-48h]
  char *v37; // [esp+14h] [ebp-44h]
  _DWORD v38[4]; // [esp+18h] [ebp-40h] BYREF
  _DWORD v39[4]; // [esp+28h] [ebp-30h] BYREF
  _DWORD v40[4]; // [esp+38h] [ebp-20h] BYREF
  _DWORD v41[4]; // [esp+48h] [ebp-10h] BYREF

  v1 = game;
  initialize_fringe_manager((_DWORD *)MEMORY[0x4DF904] + 999541);
  v2 = 0;
  v36 = 0;
  if ( v1->runtime_row_count > 0 )
  {
    v3 = &byte_5CCAC8[(_DWORD)v1];
    v4 = &v1->_pad_74622[3454118];
    v37 = &byte_5CCAC8[(_DWORD)v1];
    do
    {
      v35 = 8;
      do
      {
        v5 = v4[61];
        v6 = 0;
        switch ( v5 )
        {
          case 9u:
            v6 = 1;
            break;
          case 5u:
            v6 = 3;
            break;
          case 0xAu:
            v6 = 2;
            break;
          case 6u:
            v6 = 4;
            break;
        }
        v7 = v4[60];
        if ( v7 == 2 || v7 == 8 || v7 == 5 )
          v6 = 5;
        if ( v7 == 3 || v7 == 9 || v7 == 11 || v7 == 12 || v7 == 13 || v7 == 6 )
          v6 = 6;
        if ( v7 == 4 || v7 == 10 || v7 == 7 )
          v6 = 7;
        if ( (*v3 & 4) != 0 || !v5 || v7 == 32 || (byte_4DF934 & 0x20) == 0 )
        {
          *((_DWORD *)v4 + 17) = 0;
          *((_DWORD *)v4 + 18) = 0;
          *((_DWORD *)v4 + 19) = 0;
LABEL_64:
          *((_DWORD *)v4 + 20) = 0;
          goto LABEL_65;
        }
        if ( !is_neighbor_cell_solid(v1, v4, 0, 0) )
          goto LABEL_65;
        if ( is_neighbor_cell_solid(v1, v4, 0, 1) )
        {
          *((_DWORD *)v4 + 17) = 0;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, 1, 1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 1, 0) + 1;
          if ( is_neighbor_cell_solid(v1, v4, -1, 1) )
            v8 = 0;
          else
            v8 = !is_neighbor_cell_solid(v1, v4, -1, 0) + 1;
          fringe_object = allocate_fringe_object((_DWORD *)MEMORY[0x4DF904] + 999541);
          *((_DWORD *)v4 + 17) = fringe_object;
          set_bod_object(
            fringe_object,
            *((_DWORD *)MEMORY[0x4DF904] + 336 * v6 + 168 * v6 + 28 * v2 + 14 * v8 + 14 * v2 + 70517));
          *(_DWORD *)(*((_DWORD *)v4 + 17) + 4) |= 0x20u;
          v10 = (_DWORD *)(*((_DWORD *)v4 + 17) + 16);
          *v10 = *((_DWORD *)v4 + 4);
          v10[1] = *((_DWORD *)v4 + 5);
          v10[2] = *((_DWORD *)v4 + 6);
          track_skirt_color = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v38);
          v12 = (_DWORD *)(*((_DWORD *)v4 + 17) + 40);
          v1 = game;
          v2 = 0;
          *v12 = *track_skirt_color;
          v12[1] = track_skirt_color[1];
          v12[2] = track_skirt_color[2];
          v12[3] = track_skirt_color[3];
        }
        if ( is_neighbor_cell_solid(v1, v4, 1, 0) )
        {
          *((_DWORD *)v4 + 18) = 0;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, 1, -1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 0, -1) + 1;
          if ( is_neighbor_cell_solid(v1, v4, 1, 1) )
            v13 = 0;
          else
            v13 = !is_neighbor_cell_solid(v1, v4, 0, 1) + 1;
          v14 = allocate_fringe_object((_DWORD *)MEMORY[0x4DF904] + 999541);
          *((_DWORD *)v4 + 18) = v14;
          set_bod_object(
            v14,
            *((_DWORD *)MEMORY[0x4DF904] + 336 * v6 + 168 * v6 + 28 * v2 + 14 * v13 + 14 * v2 + 70643));
          *(_DWORD *)(*((_DWORD *)v4 + 18) + 4) |= 0x20u;
          v15 = (_DWORD *)(*((_DWORD *)v4 + 18) + 16);
          *v15 = *((_DWORD *)v4 + 4);
          v15[1] = *((_DWORD *)v4 + 5);
          v15[2] = *((_DWORD *)v4 + 6);
          v16 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v39);
          v17 = (_DWORD *)(*((_DWORD *)v4 + 18) + 40);
          v1 = game;
          v2 = 0;
          *v17 = *v16;
          v17[1] = v16[1];
          v17[2] = v16[2];
          v17[3] = v16[3];
        }
        if ( is_neighbor_cell_solid(v1, v4, -1, 0) )
        {
          *((_DWORD *)v4 + 19) = 0;
        }
        else
        {
          if ( !is_neighbor_cell_solid(v1, v4, -1, 1) )
            v2 = !is_neighbor_cell_solid(v1, v4, 0, 1) + 1;
          if ( is_neighbor_cell_solid(v1, v4, -1, -1) )
            v18 = 0;
          else
            v18 = !is_neighbor_cell_solid(v1, v4, 0, -1) + 1;
          v19 = allocate_fringe_object((_DWORD *)MEMORY[0x4DF904] + 999541);
          *((_DWORD *)v4 + 19) = v19;
          set_bod_object(
            v19,
            *((_DWORD *)MEMORY[0x4DF904] + 336 * v6 + 168 * v6 + 28 * v2 + 14 * v18 + 14 * v2 + 70769));
          *(_DWORD *)(*((_DWORD *)v4 + 19) + 4) |= 0x20u;
          v20 = (_DWORD *)(*((_DWORD *)v4 + 19) + 16);
          *v20 = *((_DWORD *)v4 + 4);
          v20[1] = *((_DWORD *)v4 + 5);
          v20[2] = *((_DWORD *)v4 + 6);
          v21 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v40);
          v22 = (_DWORD *)(*((_DWORD *)v4 + 19) + 40);
          v1 = game;
          v2 = 0;
          *v22 = *v21;
          v22[1] = v21[1];
          v22[2] = v21[2];
          v22[3] = v21[3];
        }
        if ( is_neighbor_cell_solid(v1, v4, 0, -1) )
          goto LABEL_64;
        if ( !is_neighbor_cell_solid(v1, v4, -1, -1) )
          v2 = !is_neighbor_cell_solid(v1, v4, -1, 0) + 1;
        if ( is_neighbor_cell_solid(v1, v4, 1, -1) )
          v23 = 0;
        else
          v23 = !is_neighbor_cell_solid(v1, v4, 1, 0) + 1;
        v24 = allocate_fringe_object((_DWORD *)MEMORY[0x4DF904] + 999541);
        *((_DWORD *)v4 + 20) = v24;
        set_bod_object(v24, *((_DWORD *)MEMORY[0x4DF904] + 336 * v6 + 168 * v6 + 28 * v2 + 14 * v23 + 14 * v2 + 70895));
        *(_DWORD *)(*((_DWORD *)v4 + 20) + 4) |= 0x20u;
        v25 = (_DWORD *)(*((_DWORD *)v4 + 20) + 16);
        *v25 = *((_DWORD *)v4 + 4);
        v25[1] = *((_DWORD *)v4 + 5);
        v25[2] = *((_DWORD *)v4 + 6);
        v26 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v41);
        v27 = (_DWORD *)(*((_DWORD *)v4 + 20) + 40);
        v1 = game;
        v2 = 0;
        *v27 = *v26;
        v27[1] = v26[1];
        v27[2] = v26[2];
        v27[3] = v26[3];
LABEL_65:
        v3 = v37;
        if ( (*v37 & 4) != 0 )
        {
          v28 = *((_DWORD *)v4 + 17);
          if ( v28 )
            *(_DWORD *)(v28 + 4) &= ~0x20u;
          v29 = *((_DWORD *)v4 + 20);
          if ( v29 )
            *(_DWORD *)(v29 + 4) &= ~0x20u;
          v30 = *((_DWORD *)v4 + 18);
          if ( v30 )
            *(_DWORD *)(v30 + 4) &= ~0x20u;
          v31 = *((_DWORD *)v4 + 19);
          if ( v31 )
            *(_DWORD *)(v31 + 4) &= ~0x20u;
        }
        v4 += 84;
        --v35;
      }
      while ( v35 );
      v3 = v37 + 244;
      v32 = ++v36 < v1->runtime_row_count;
      v37 += 244;
    }
    while ( v32 );
  }
  return sub_449C00();
}

