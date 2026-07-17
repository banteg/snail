/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_render_caches @ 0x433220 */
/* selector: build_track_render_caches */

// Authored void cRSegmentCache builder for the Floor, Slide, Warn, Ramp, and Fringe families: consumes the owning SubgameRuntime’s fixed runtime-cell slab and uses each embedded TrackRowCell anchor as the mesh-instance position. The final debug-report result is incidental call state.
void __thiscall build_track_render_caches(SegmentCache *manager, tColour skirt_color)
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
  Object *object; // eax
  SubgameRuntime *v15; // edx
  int v16; // ebp
  uint8_t *v17; // eax
  int v18; // ebp
  uint8_t *v19; // eax
  uint8_t *v20; // eax
  int v21; // ecx
  int32_t *max_vertex_counts; // edi
  Object **p_object; // ebp
  ObjectVertexBuffer *vertex_buffer; // eax
  unsigned int v25; // eax
  char *v26; // esi
  char *locked_vertices; // edi
  char *v28; // edi
  char *v29; // esi
  char v30; // cl
  int32_t work_value; // eax
  int32_t cells_remaining_or_family_index; // ecx
  Object *v33; // eax
  int32_t v34; // esi
  int v35; // edx
  int32_t *group_primitive_counts; // eax
  int32_t v37; // esi
  int32_t vertex_count; // edi
  int v39; // ebp
  int v40; // edx
  Object **v41; // esi
  uint32_t white_color; // [esp+18h] [ebp-64h]
  ObjectVertexBuffer *v43; // [esp+1Ch] [ebp-60h]
  int32_t row_index; // [esp+30h] [ebp-4Ch]
  struct TrackRenderCacheBuildLocals locals; // [esp+34h] [ebp-48h] BYREF
  int32_t v46; // [esp+68h] [ebp-14h] BYREF
  int32_t v47; // [esp+6Ch] [ebp-10h] BYREF
  int32_t v48; // [esp+70h] [ebp-Ch] BYREF
  int32_t v49; // [esp+74h] [ebp-8h] BYREF
  int32_t index_count; // [esp+78h] [ebp-4h] BYREF

  noop_this_constructor(&locals);
  pack_color_rgba_u8(&manager->skirt_color_bgra, &skirt_color);
  locals.white_color = (tColourSmall)-1;
  noop_runtime_ai();
  v3 = 0;
  row_index = 0;
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
      v46 = 0;
      v47 = 0;
      v48 = 0;
      v49 = 0;
      index_count = 0;
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
        v10 = *(_DWORD *)(&owner_subgame->scan_reset + v8);
        if ( v10 )
        {
          append_track_cache_object(
            manager,
            row_index,
            *(Object **)(v10 + 36),
            (Vec3 *)((char *)&owner_subgame->runtime_cells[0][0].anchor_position + saved_cell_offset),
            manager->shared_vertex_buffers[4],
            &locals.vertex_counts[4],
            manager->shared_index_buffers[4],
            &index_count,
            manager->max_vertex_counts[4],
            manager->max_index_counts[4],
            *(_DWORD *)&manager->skirt_color_bgra,
            0);
          *manager->slots[cache_row][4].bod.object->group_texture_refs = *(TextureRef **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(&manager->owner_subgame->scan_reset + v8) + 36) + 92)
                                                                                        + 12);
          *(_DWORD *)(&manager->owner_subgame->scan_reset + v8) = 0;
        }
        v8 += 4;
        --locals.work_value;
      }
      while ( locals.work_value );
      v11 = manager->owner_subgame;
      v12 = &v11->scan_reset + saved_cell_offset;
      if ( (*(_DWORD *)&v11->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2] & 0x20) != 0
        && (*(_DWORD *)&v11->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2] & 0x4000) == 0x4000 )
      {
        append_track_cache_object(
          manager,
          row_index,
          *((Object **)v12 + 982715),
          (Vec3 *)v12 + 327570,
          manager->shared_vertex_buffers[2],
          &locals.vertex_counts[2],
          manager->shared_index_buffers[2],
          &v48,
          manager->max_vertex_counts[2],
          manager->max_index_counts[2],
          *(_DWORD *)&locals.white_color,
          1u);
        v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
        object = manager->slots[cache_row][2].bod.object;
        goto LABEL_28;
      }
      if ( (unsigned __int8)is_sub_loc_floor((TrackRowCell *)(v12 + 3930824)) )
      {
        v15 = manager->owner_subgame;
        v16 = *(_DWORD *)&v15->runtime_cells[0][0]._pad_3e[saved_cell_offset + 2];
        v17 = &v15->scan_reset + saved_cell_offset;
        if ( (v16 & 0x4000) == 0x4000 )
        {
          white_color = (uint32_t)locals.white_color;
          if ( (v16 & 0x40) == 0x40 )
            goto LABEL_20;
LABEL_24:
          append_track_cache_object(
            manager,
            row_index,
            *((Object **)v17 + 982715),
            (Vec3 *)v17 + 327570,
            manager->shared_vertex_buffers[0],
            locals.vertex_counts,
            manager->shared_index_buffers[0],
            &v46,
            manager->max_vertex_counts[0],
            manager->max_index_counts[0],
            white_color,
            1u);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = manager->slots[cache_row][0].bod.object;
          goto LABEL_28;
        }
      }
      if ( (unsigned __int8)is_sub_loc_slide((TrackRowCell *)((char *)manager->owner_subgame->runtime_cells[0]
                                                            + saved_cell_offset)) )
      {
        v17 = &manager->owner_subgame->scan_reset + saved_cell_offset;
        v18 = *((_DWORD *)v17 + 982722);
        if ( (v18 & 0x4000) == 0x4000 )
        {
          white_color = (uint32_t)locals.white_color;
          if ( (v18 & 0x40) == 0x40 )
            goto LABEL_24;
LABEL_20:
          append_track_cache_object(
            manager,
            row_index,
            *((Object **)v17 + 982715),
            (Vec3 *)v17 + 327570,
            manager->shared_vertex_buffers[1],
            &locals.vertex_counts[1],
            manager->shared_index_buffers[1],
            &v47,
            manager->max_vertex_counts[1],
            manager->max_index_counts[1],
            white_color,
            1u);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = manager->slots[cache_row][1].bod.object;
LABEL_28:
          *object->group_texture_refs = *(TextureRef **)(v13 + 12);
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
        v19 = &manager->owner_subgame->scan_reset + saved_cell_offset;
        if ( (*((_DWORD *)v19 + 982722) & 0x4000) == 0x4000 )
        {
          append_track_cache_object(
            manager,
            row_index,
            *((Object **)v19 + 982715),
            (Vec3 *)v19 + 327570,
            manager->shared_vertex_buffers[3],
            &locals.vertex_counts[3],
            manager->shared_index_buffers[3],
            &v49,
            manager->max_vertex_counts[3],
            manager->max_index_counts[3],
            *(_DWORD *)&locals.white_color,
            0);
          v13 = (*(_DWORD **)((char *)&manager->owner_subgame->runtime_cells[0][0].object + saved_cell_offset))[23];
          object = manager->slots[cache_row][3].bod.object;
          goto LABEL_28;
        }
      }
LABEL_29:
      saved_cell_offset += 84;
      --locals.cells_remaining_or_family_index;
    }
    while ( locals.cells_remaining_or_family_index );
    locals.saved_cell_offset = saved_cell_offset;
    if ( locals.row_mod == 23 || row_index == manager->owner_subgame->runtime_row_count - 1 )
    {
      max_vertex_counts = manager->max_vertex_counts;
      locals.work_value = (int32_t)manager->max_vertex_counts;
      locals.cells_remaining_or_family_index = 0;
      p_object = &manager->slots[cache_row][0].bod.object;
      while ( 1 )
      {
        vertex_buffer = (*p_object)->render_buffers->vertex_buffer;
        vertex_buffer->vtbl->Lock(vertex_buffer, 0, 24 * *max_vertex_counts, &locals.locked_vertices, 0);
        (*p_object)->index_buffer->buffer->vtbl->Lock(
          (*p_object)->index_buffer->buffer,
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
        v43 = (*p_object)->render_buffers->vertex_buffer;
        v43->vtbl->Unlock(v43);
        (*p_object)->index_buffer->buffer->vtbl->Unlock((*p_object)->index_buffer->buffer);
        cells_remaining_or_family_index = locals.cells_remaining_or_family_index;
        v33 = *p_object;
        v34 = locals.work_value;
        p_object += 15;
        v33->grouped_vertex_count = *(int32_t *)((char *)locals.vertex_counts + locals.cells_remaining_or_family_index);
        v35 = *(int32_t *)((char *)&v46 + cells_remaining_or_family_index) / 3;
        group_primitive_counts = (*(p_object - 15))->group_primitive_counts;
        locals.work_value = v34 + 4;
        *group_primitive_counts = v35;
        (*(p_object - 15))->vertex_count = *(int32_t *)((char *)locals.vertex_counts + cells_remaining_or_family_index);
        locals.cells_remaining_or_family_index = cells_remaining_or_family_index + 4;
        if ( cells_remaining_or_family_index + 4 >= 20 )
          break;
        max_vertex_counts = (int32_t *)locals.work_value;
      }
      saved_cell_offset = locals.saved_cell_offset;
    }
    if ( ++row_index < manager->owner_subgame->runtime_row_count )
    {
      v3 = row_index;
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
    vertex_count = 0;
    v39 = 0;
    v40 = manager->owner_subgame->runtime_row_count / 24;
    if ( v40 > 0 )
    {
      v41 = &manager->slots[0][v37].bod.object;
      do
      {
        if ( (*v41)->vertex_count > vertex_count )
          vertex_count = (*v41)->vertex_count;
        if ( 4 * *(*v41)->group_primitive_counts > v39 )
          v39 = 4 * *(*v41)->group_primitive_counts;
        v41 += 75;
        --v40;
      }
      while ( v40 );
      v37 = locals.cells_remaining_or_family_index;
    }
    debug_report_stub();
    locals.cells_remaining_or_family_index = ++v37;
  }
  while ( v37 < 5 );
}
