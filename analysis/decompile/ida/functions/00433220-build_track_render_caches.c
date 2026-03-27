/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_render_caches @ 0x433220 */
/* selector: build_track_render_caches */

// Builds the Floor, Slide, Warn, Ramp, and Fringe track render caches after runtime track normalization.
int32_t __fastcall build_track_render_caches(TrackRenderCacheManager *manager)
{
  int v2; // ecx
  int v3; // edi
  int v4; // esi
  uint8_t *v5; // eax
  int v6; // ecx
  int v7; // ebp
  TrackRenderGrid *track_render_grid; // eax
  int v9; // edx
  TrackRenderGrid *v10; // edx
  uint8_t *v11; // eax
  int v12; // ecx
  RenderObjectTextureGroups *render_object; // eax
  TrackRenderGrid *v14; // edx
  int v15; // ebp
  uint8_t *v16; // eax
  int v17; // ebp
  uint8_t *v18; // eax
  uint8_t *v19; // eax
  int v20; // ecx
  int32_t *max_vertex_counts; // edi
  RenderObjectTextureGroups **p_render_object; // ebp
  int v23; // eax
  unsigned int v24; // eax
  char *v25; // esi
  char *v26; // edi
  char *v27; // edi
  char *v28; // esi
  char v29; // cl
  int v30; // eax
  int v31; // ecx
  RenderObjectTextureGroups *v32; // eax
  int v33; // esi
  int v34; // edx
  int32_t *texture_group_primcounts; // eax
  int v36; // esi
  int v37; // edi
  int v38; // ebp
  int v39; // edx
  RenderObjectTextureGroups **v40; // esi
  int32_t result; // eax
  int v42; // [esp+18h] [ebp-64h]
  int v43; // [esp+1Ch] [ebp-60h]
  int v44; // [esp+30h] [ebp-4Ch]
  int v45; // [esp+34h] [ebp-48h] BYREF
  int v46; // [esp+38h] [ebp-44h]
  int v47; // [esp+3Ch] [ebp-40h]
  int v48; // [esp+40h] [ebp-3Ch]
  int v49; // [esp+44h] [ebp-38h]
  char *v50; // [esp+48h] [ebp-34h] BYREF
  void *v51; // [esp+4Ch] [ebp-30h] BYREF
  int v52; // [esp+50h] [ebp-2Ch]
  int v53; // [esp+54h] [ebp-28h] BYREF
  int v54; // [esp+58h] [ebp-24h] BYREF
  int v55; // [esp+5Ch] [ebp-20h] BYREF
  int v56; // [esp+60h] [ebp-1Ch] BYREF
  int v57; // [esp+64h] [ebp-18h] BYREF
  int v58; // [esp+68h] [ebp-14h] BYREF
  int v59; // [esp+6Ch] [ebp-10h] BYREF
  int v60; // [esp+70h] [ebp-Ch] BYREF
  int v61; // [esp+74h] [ebp-8h] BYREF
  int v62; // [esp+78h] [ebp-4h] BYREF
  Color4f v63; // [esp+80h] [ebp+4h] BYREF

  Iostream_init::Iostream_init((#93 *)&v45);
  pack_color_rgba_u8(&manager->clear_color, &v63);
  v45 = -1;
  noop_runtime_ai();
  v2 = 0;
  v44 = 0;
  if ( manager->track_render_grid->cell_count <= 0 )
    goto LABEL_37;
  v3 = 0;
  while ( 2 )
  {
    v49 = v2 % 24;
    if ( v2 % 24 )
    {
      v4 = v47;
    }
    else
    {
      v4 = v2 / 24;
      v47 = v2 / 24;
      v58 = 0;
      v59 = 0;
      v60 = 0;
      v61 = 0;
      v62 = 0;
      v5 = &manager->slots[5 * (v2 / 24)]._pad_2c[12];
      v53 = 0;
      v54 = 0;
      *(float *)manager->_pad_a7bc = (double)(v2 / 24) * 24.0;
      v55 = 0;
      v56 = 0;
      v57 = 0;
      v6 = 5;
      do
      {
        *(_DWORD *)v5 = *(_DWORD *)manager->_pad_a7bc;
        v5 += 60;
        --v6;
      }
      while ( v6 );
    }
    v48 = 8;
    do
    {
      v7 = v3 + 3930892;
      v46 = 4;
      do
      {
        track_render_grid = manager->track_render_grid;
        v9 = *(_DWORD *)&track_render_grid->_pad_00[v7];
        if ( v9 )
        {
          sub_433960(
            (float *)&manager->clear_color,
            v44,
            *(_DWORD *)(v9 + 36),
            (float *)((char *)&track_render_grid->cells[0].anchor_position.x + v3),
            (int)manager->shared_vertex_buffers[4],
            &v57,
            (int)manager->shared_index_buffers[4],
            &v62,
            manager->max_vertex_counts[4],
            manager->max_index_counts[4],
            *(_DWORD *)&manager->clear_color,
            0);
          *manager->slots[5 * v4 + 4].render_object->texture_group_texture_refs = *(TextureRef **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&manager->track_render_grid->_pad_00[v7] + 36) + 92)
                                                                                                 + 12);
          *(_DWORD *)&manager->track_render_grid->_pad_00[v7] = 0;
        }
        v7 += 4;
        --v46;
      }
      while ( v46 );
      v10 = manager->track_render_grid;
      v11 = &v10->_pad_00[v3];
      if ( (*(_DWORD *)&v10->cells[0]._pad_3e[v3 + 2] & 0x20) != 0
        && (*(_DWORD *)&v10->cells[0]._pad_3e[v3 + 2] & 0x4000) == 0x4000 )
      {
        sub_433960(
          (float *)&manager->clear_color,
          v44,
          *((_DWORD *)v11 + 982715),
          (float *)v11 + 982710,
          (int)manager->shared_vertex_buffers[2],
          &v55,
          (int)manager->shared_index_buffers[2],
          &v60,
          manager->max_vertex_counts[2],
          manager->max_index_counts[2],
          v45,
          1);
        v12 = *(_DWORD *)(*(_DWORD *)&manager->track_render_grid->cells[0]._pad_1c[v3 + 8] + 92);
        render_object = manager->slots[5 * v4 + 2].render_object;
        goto LABEL_28;
      }
      if ( (unsigned __int8)is_slide_cache_tile_family((TrackRowCell *)(v11 + 3930824)) )
      {
        v14 = manager->track_render_grid;
        v15 = *(_DWORD *)&v14->cells[0]._pad_3e[v3 + 2];
        v16 = &v14->_pad_00[v3];
        if ( (v15 & 0x4000) == 0x4000 )
        {
          v42 = v45;
          if ( (v15 & 0x40) == 0x40 )
            goto LABEL_20;
LABEL_24:
          sub_433960(
            (float *)&manager->clear_color,
            v44,
            *((_DWORD *)v16 + 982715),
            (float *)v16 + 982710,
            (int)manager->shared_vertex_buffers[0],
            &v53,
            (int)manager->shared_index_buffers[0],
            &v58,
            manager->max_vertex_counts[0],
            manager->max_index_counts[0],
            v42,
            1);
          v12 = *(_DWORD *)(*(_DWORD *)&manager->track_render_grid->cells[0]._pad_1c[v3 + 8] + 92);
          render_object = manager->slots[5 * v4].render_object;
          goto LABEL_28;
        }
      }
      if ( (unsigned __int8)is_floor_cache_tile_family((TrackRowCell *)((char *)manager->track_render_grid->cells + v3)) )
      {
        v16 = &manager->track_render_grid->_pad_00[v3];
        v17 = *((_DWORD *)v16 + 982722);
        if ( (v17 & 0x4000) == 0x4000 )
        {
          v42 = v45;
          if ( (v17 & 0x40) == 0x40 )
            goto LABEL_24;
LABEL_20:
          sub_433960(
            (float *)&manager->clear_color,
            v44,
            *((_DWORD *)v16 + 982715),
            (float *)v16 + 982710,
            (int)manager->shared_vertex_buffers[1],
            &v54,
            (int)manager->shared_index_buffers[1],
            &v59,
            manager->max_vertex_counts[1],
            manager->max_index_counts[1],
            v42,
            1);
          v12 = *(_DWORD *)(*(_DWORD *)&manager->track_render_grid->cells[0]._pad_1c[v3 + 8] + 92);
          render_object = manager->slots[5 * v4 + 1].render_object;
LABEL_28:
          *render_object->texture_group_texture_refs = *(TextureRef **)(v12 + 12);
          v19 = &manager->track_render_grid->cells[0]._pad_3e[v3 + 2];
          v20 = *(_DWORD *)v19;
          BYTE1(v20) = BYTE1(*(_DWORD *)v19) & 0xBF;
          *(_DWORD *)v19 = v20;
          goto LABEL_29;
        }
      }
      if ( (unsigned __int8)is_ramp_cache_tile_family((TrackRowCell *)((char *)manager->track_render_grid->cells + v3)) )
      {
        v18 = &manager->track_render_grid->_pad_00[v3];
        if ( (*((_DWORD *)v18 + 982722) & 0x4000) == 0x4000 )
        {
          sub_433960(
            (float *)&manager->clear_color,
            v44,
            *((_DWORD *)v18 + 982715),
            (float *)v18 + 982710,
            (int)manager->shared_vertex_buffers[3],
            &v56,
            (int)manager->shared_index_buffers[3],
            &v61,
            manager->max_vertex_counts[3],
            manager->max_index_counts[3],
            v45,
            0);
          v12 = *(_DWORD *)(*(_DWORD *)&manager->track_render_grid->cells[0]._pad_1c[v3 + 8] + 92);
          render_object = manager->slots[5 * v4 + 3].render_object;
          goto LABEL_28;
        }
      }
LABEL_29:
      v3 += 84;
      --v48;
    }
    while ( v48 );
    v52 = v3;
    if ( v49 == 23 || v44 == manager->track_render_grid->cell_count - 1 )
    {
      max_vertex_counts = manager->max_vertex_counts;
      v46 = (int)manager->max_vertex_counts;
      v48 = 0;
      p_render_object = &manager->slots[5 * v4].render_object;
      while ( 1 )
      {
        v23 = *((_DWORD *)(*p_render_object)->vertex_buffer + 2);
        (*(void (__stdcall **)(int, _DWORD, int, char **, _DWORD))(*(_DWORD *)v23 + 44))(
          v23,
          0,
          24 * *max_vertex_counts,
          &v50,
          0);
        (*(void (__stdcall **)(_DWORD, _DWORD, int, void **, _DWORD))(**(_DWORD **)(*p_render_object)->index_buffer + 44))(
          *(_DWORD *)(*p_render_object)->index_buffer,
          0,
          2 * max_vertex_counts[5],
          &v51,
          0);
        v24 = *max_vertex_counts;
        v25 = (char *)max_vertex_counts[10];
        v26 = v50;
        v24 *= 24;
        qmemcpy(v50, v25, 4 * (v24 >> 2));
        v28 = &v25[4 * (v24 >> 2)];
        v27 = &v26[4 * (v24 >> 2)];
        v29 = v24;
        v30 = v46;
        qmemcpy(v27, v28, v29 & 3);
        qmemcpy(v51, *(const void **)(v30 + 60), 2 * *(_DWORD *)(v30 + 20));
        v43 = *((_DWORD *)(*p_render_object)->vertex_buffer + 2);
        (*(void (__stdcall **)(int))(*(_DWORD *)v43 + 48))(v43);
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(*p_render_object)->index_buffer + 48))(*(_DWORD *)(*p_render_object)->index_buffer);
        v31 = v48;
        v32 = *p_render_object;
        v33 = v46;
        p_render_object += 15;
        v32->vertex_count = *(int *)((char *)&v53 + v48);
        v34 = *(int *)((char *)&v58 + v31) / 3;
        texture_group_primcounts = (*(p_render_object - 15))->texture_group_primcounts;
        v46 = v33 + 4;
        *texture_group_primcounts = v34;
        *(_DWORD *)&(*(p_render_object - 15))->_pad_00[44] = *(int *)((char *)&v53 + v31);
        v48 = v31 + 4;
        if ( v31 + 4 >= 20 )
          break;
        max_vertex_counts = (int32_t *)v46;
      }
      v3 = v52;
    }
    if ( ++v44 < manager->track_render_grid->cell_count )
    {
      v2 = v44;
      continue;
    }
    break;
  }
LABEL_37:
  v36 = 0;
  *(_DWORD *)&manager->_pad_a7bc[4] = 0;
  *(_DWORD *)&manager->_pad_a7bc[8] = 0;
  v48 = 0;
  do
  {
    v37 = 0;
    v38 = 0;
    v39 = manager->track_render_grid->cell_count / 24;
    if ( v39 > 0 )
    {
      v40 = &manager->slots[v36].render_object;
      do
      {
        if ( *(_DWORD *)&(*v40)->_pad_00[44] > v37 )
          v37 = *(_DWORD *)&(*v40)->_pad_00[44];
        if ( 4 * *(*v40)->texture_group_primcounts > v38 )
          v38 = 4 * *(*v40)->texture_group_primcounts;
        v40 += 75;
        --v39;
      }
      while ( v39 );
      v36 = v48;
    }
    result = sub_449C00();
    v48 = ++v36;
  }
  while ( v36 < 5 );
  return result;
}

