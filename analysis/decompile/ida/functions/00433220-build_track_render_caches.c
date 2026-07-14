/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_render_caches @ 0x433220 */
/* selector: build_track_render_caches */

// Builds the cRSegmentCache Floor, Slide, Warn, Ramp, and Fringe families from the owning SubgameRuntime’s fixed runtime-cell slab, using each embedded TrackRowCell anchor as the mesh-instance position.
int32_t __thiscall build_track_render_caches(SegmentCache *manager, Color4f skirt_color)
{
  int32_t v3; // ecx
  int32_t saved_cell_offset; // edi
  int32_t cache_row; // esi
  float *p_cache_row_base; // eax
  int v7; // ecx
  int v8; // ebp
  SubgameRuntime *owner_subgame; // eax
  int v10; // edx
  SubgameRuntime *v11; // edx
  uint8_t *v12; // eax
  int v13; // ecx
  _DWORD **object; // eax
  SubgameRuntime *v15; // edx
  int v16; // ebp
  uint8_t *v17; // eax
  int v18; // ebp
  uint8_t *v19; // eax
  uint8_t *v20; // eax
  int v21; // ecx
  int32_t *max_vertex_counts; // edi
  void **p_object; // ebp
  int v24; // eax
  unsigned int v25; // eax
  char *v26; // esi
  char *locked_vertices; // edi
  char *v28; // edi
  char *v29; // esi
  char v30; // cl
  int32_t work_value; // eax
  int32_t cells_remaining_or_family_index; // ecx
  _DWORD *v33; // eax
  int32_t v34; // esi
  int v35; // edx
  int *v36; // eax
  int32_t v37; // esi
  int v38; // edi
  int v39; // ebp
  int v40; // edx
  void **v41; // esi
  int32_t result; // eax
  uint32_t white_color; // [esp+18h] [ebp-64h]
  int v44; // [esp+1Ch] [ebp-60h]
  int32_t v45; // [esp+30h] [ebp-4Ch]
  struct TrackRenderCacheBuildLocals locals; // [esp+34h] [ebp-48h] BYREF
  int v47; // [esp+68h] [ebp-14h] BYREF
  int v48; // [esp+6Ch] [ebp-10h] BYREF
  int v49; // [esp+70h] [ebp-Ch] BYREF
  int v50; // [esp+74h] [ebp-8h] BYREF
  int v51; // [esp+78h] [ebp-4h] BYREF

  noop_this_constructor(&locals);
  pack_color_rgba_u8(&manager->skirt_color_bgra, &skirt_color);
  locals.white_color = (tColourSmall)-1;
  noop_runtime_ai();
  v3 = 0;
  v45 = 0;
  if ( manager->owner_subgame->runtime_row_count <= 0 )
    goto LABEL_37;
  saved_cell_offset = 0;
  while ( 2 )
  {
    locals.row_mod = v3 % 24;
    if ( v3 % 24 )
    {
      cache_row = locals.cache_row;
    }
    else
    {
      cache_row = v3 / 24;
      locals.cache_row = v3 / 24;
      v47 = 0;
      v48 = 0;
      v49 = 0;
      v50 = 0;
      v51 = 0;
      p_cache_row_base = &manager->slots[v3 / 24][0].cache_row_base;
      locals.vertex_counts[0] = 0;
      locals.vertex_counts[1] = 0;
      manager->build_cache_row_base = (double)(v3 / 24) * 24.0;
      memset(&locals.vertex_counts[2], 0, 12);
      v7 = 5;
      do
      {
        *p_cache_row_base = manager->build_cache_row_base;
        p_cache_row_base += 15;
        --v7;
      }
      while ( v7 );
    }
    locals.cells_remaining_or_family_index = 8;
    do
    {
      v8 = saved_cell_offset + 3930892;
      locals.work_value = 4;
      do
      {
        owner_subgame = manager->owner_subgame;
        v10 = *(_DWORD *)&owner_subgame->_pad_00[v8];
        if ( v10 )
        {
          append_track_cache_object(
            manager,
            v45,
            *(Object **)(v10 + 36),
            (Vec3 *)((char *)&owner_subgame->runtime_cells[0][0].anchor_position + saved_cell_offset),
            manager->shared_vertex_buffers[4],
            &locals.vertex_counts[4],
            manager->shared_index_buffers[4],
            &v51,
            manager->max_vertex_counts[4],
            manager->max_index_counts[4],
            *(_DWORD *)&manager->skirt_color_bgra,
            0);
          **((_DWORD **)manager->slots[cache_row][4].bod.object + 52) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&manager->owner_subgame->_pad_00[v8] + 36)
                                                                                              + 92)
                                                                                  + 12);
          *(_DWORD *)&manager->owner_subgame->_pad_00[v8] = 0;
        }
        v8 += 4;
        --locals.work_value;
      }
      while ( locals.work_value );
      v11 = manager->owner_subgame;
      v12 = &v11->_pad_00[saved_cell_offset];
      if ( (*(_DWORD *)&v11->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2] & 0x20) != 0
        && (*(_DWORD *)&v11->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2] & 0x4000) == 0x4000 )
      {
        append_track_cache_object(
          manager,
          v45,
          *((Object **)v12 + 982715),
          (Vec3 *)v12 + 327570,
          manager->shared_vertex_buffers[2],
          &locals.vertex_counts[2],
          manager->shared_index_buffers[2],
          &v49,
          manager->max_vertex_counts[2],
          manager->max_index_counts[2],
          *(_DWORD *)&locals.white_color,
          1u);
        v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
        object = (_DWORD **)manager->slots[cache_row][2].bod.object;
        goto LABEL_28;
      }
      if ( (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v12 + 3930824)) )
      {
        v15 = manager->owner_subgame;
        v16 = *(_DWORD *)&v15->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2];
        v17 = &v15->_pad_00[saved_cell_offset];
        if ( (v16 & 0x4000) == 0x4000 )
        {
          white_color = (uint32_t)locals.white_color;
          if ( (v16 & 0x40) == 0x40 )
            goto LABEL_20;
LABEL_24:
          append_track_cache_object(
            manager,
            v45,
            *((Object **)v17 + 982715),
            (Vec3 *)v17 + 327570,
            manager->shared_vertex_buffers[0],
            locals.vertex_counts,
            manager->shared_index_buffers[0],
            &v47,
            manager->max_vertex_counts[0],
            manager->max_index_counts[0],
            white_color,
            1u);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = (_DWORD **)manager->slots[cache_row][0].bod.object;
          goto LABEL_28;
        }
      }
      if ( (unsigned __int8)is_sub_loc_slide((TrackRowCell *)((char *)manager->owner_subgame->runtime_cells[0]
                                                            + saved_cell_offset)) )
      {
        v17 = &manager->owner_subgame->_pad_00[saved_cell_offset];
        v18 = *((_DWORD *)v17 + 982722);
        if ( (v18 & 0x4000) == 0x4000 )
        {
          white_color = (uint32_t)locals.white_color;
          if ( (v18 & 0x40) == 0x40 )
            goto LABEL_24;
LABEL_20:
          append_track_cache_object(
            manager,
            v45,
            *((Object **)v17 + 982715),
            (Vec3 *)v17 + 327570,
            manager->shared_vertex_buffers[1],
            &locals.vertex_counts[1],
            manager->shared_index_buffers[1],
            &v48,
            manager->max_vertex_counts[1],
            manager->max_index_counts[1],
            white_color,
            1u);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = (_DWORD **)manager->slots[cache_row][1].bod.object;
LABEL_28:
          *object[52] = *(_DWORD *)(v13 + 12);
          v20 = &manager->owner_subgame->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2];
          v21 = *(_DWORD *)v20;
          BYTE1(v21) = BYTE1(*(_DWORD *)v20) & 0xBF;
          *(_DWORD *)v20 = v21;
          goto LABEL_29;
        }
      }
      if ( (unsigned __int8)is_sub_loc_ramp((TrackRowCell *)((char *)manager->owner_subgame->runtime_cells[0]
                                                           + saved_cell_offset)) )
      {
        v19 = &manager->owner_subgame->_pad_00[saved_cell_offset];
        if ( (*((_DWORD *)v19 + 982722) & 0x4000) == 0x4000 )
        {
          append_track_cache_object(
            manager,
            v45,
            *((Object **)v19 + 982715),
            (Vec3 *)v19 + 327570,
            manager->shared_vertex_buffers[3],
            &locals.vertex_counts[3],
            manager->shared_index_buffers[3],
            &v50,
            manager->max_vertex_counts[3],
            manager->max_index_counts[3],
            *(_DWORD *)&locals.white_color,
            0);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = (_DWORD **)manager->slots[cache_row][3].bod.object;
          goto LABEL_28;
        }
      }
LABEL_29:
      saved_cell_offset += 84;
      --locals.cells_remaining_or_family_index;
    }
    while ( locals.cells_remaining_or_family_index );
    locals.saved_cell_offset = saved_cell_offset;
    if ( locals.row_mod == 23 || v45 == manager->owner_subgame->runtime_row_count - 1 )
    {
      max_vertex_counts = manager->max_vertex_counts;
      locals.work_value = (int32_t)manager->max_vertex_counts;
      locals.cells_remaining_or_family_index = 0;
      p_object = &manager->slots[cache_row][0].bod.object;
      while ( 1 )
      {
        v24 = *(_DWORD *)(*((_DWORD *)*p_object + 48) + 8);
        (*(void (__stdcall **)(int, _DWORD, int, void **, _DWORD))(*(_DWORD *)v24 + 44))(
          v24,
          0,
          24 * *max_vertex_counts,
          &locals.locked_vertices,
          0);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, void **, _DWORD))(***((_DWORD ***)*p_object + 50) + 44))(
          **((_DWORD **)*p_object + 50),
          0,
          2 * max_vertex_counts[5],
          &locals.locked_indices,
          0);
        v25 = *max_vertex_counts;
        v26 = (char *)max_vertex_counts[10];
        locked_vertices = (char *)locals.locked_vertices;
        v25 *= 24;
        qmemcpy(locals.locked_vertices, v26, 4 * (v25 >> 2));
        v29 = &v26[4 * (v25 >> 2)];
        v28 = &locked_vertices[4 * (v25 >> 2)];
        v30 = v25;
        work_value = locals.work_value;
        qmemcpy(v28, v29, v30 & 3);
        qmemcpy(locals.locked_indices, *(const void **)(work_value + 60), 2 * *(_DWORD *)(work_value + 20));
        v44 = *(_DWORD *)(*((_DWORD *)*p_object + 48) + 8);
        (*(void (__stdcall **)(int))(*(_DWORD *)v44 + 48))(v44);
        (*(void (__stdcall **)(_DWORD))(***((_DWORD ***)*p_object + 50) + 48))(**((_DWORD **)*p_object + 50));
        cells_remaining_or_family_index = locals.cells_remaining_or_family_index;
        v33 = *p_object;
        v34 = locals.work_value;
        p_object += 15;
        v33[49] = *(int32_t *)((char *)locals.vertex_counts + locals.cells_remaining_or_family_index);
        v35 = *(int *)((char *)&v47 + cells_remaining_or_family_index) / 3;
        v36 = *((int **)*(p_object - 15) + 53);
        locals.work_value = v34 + 4;
        *v36 = v35;
        *((_DWORD *)*(p_object - 15) + 11) = *(int32_t *)((char *)locals.vertex_counts + cells_remaining_or_family_index);
        locals.cells_remaining_or_family_index = cells_remaining_or_family_index + 4;
        if ( cells_remaining_or_family_index + 4 >= 20 )
          break;
        max_vertex_counts = (int32_t *)locals.work_value;
      }
      saved_cell_offset = locals.saved_cell_offset;
    }
    if ( ++v45 < manager->owner_subgame->runtime_row_count )
    {
      v3 = v45;
      continue;
    }
    break;
  }
LABEL_37:
  v37 = 0;
  manager->next_cache_row_z = 0.0;
  manager->next_cache_row_index = 0;
  locals.cells_remaining_or_family_index = 0;
  do
  {
    v38 = 0;
    v39 = 0;
    v40 = manager->owner_subgame->runtime_row_count / 24;
    if ( v40 > 0 )
    {
      v41 = &manager->slots[0][v37].bod.object;
      do
      {
        if ( *((_DWORD *)*v41 + 11) > v38 )
          v38 = *((_DWORD *)*v41 + 11);
        if ( 4 * **((_DWORD **)*v41 + 53) > v39 )
          v39 = 4 * **((_DWORD **)*v41 + 53);
        v41 += 75;
        --v40;
      }
      while ( v40 );
      v37 = locals.cells_remaining_or_family_index;
    }
    result = debug_report_stub();
    locals.cells_remaining_or_family_index = ++v37;
  }
  while ( v37 < 5 );
  return result;
}

