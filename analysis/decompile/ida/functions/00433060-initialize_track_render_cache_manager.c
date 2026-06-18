/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_render_cache_manager @ 0x433060 */
/* selector: initialize_track_render_cache_manager */

// Initializes the fixed 143x5 track-render cache bod grid plus its shared GDX cache vertex/index buffers and per-cache texture-group scratch arrays.
void *__fastcall initialize_track_render_cache_manager(TrackRenderCacheManager *manager)
{
  int i; // edi
  char *v3; // esi
  _DWORD *v4; // eax
  bool v5; // cc
  void **shared_vertex_buffers; // esi
  int v7; // edi
  void *result; // eax
  int v9; // [esp+10h] [ebp-8h]
  RenderObjectTextureGroups **p_render_object; // [esp+14h] [ebp-4h]

  manager->max_vertex_counts[0] = 560;
  manager->max_vertex_counts[1] = 560;
  manager->max_index_counts[0] = 1280;
  manager->max_index_counts[1] = 1280;
  manager->max_vertex_counts[2] = 160;
  manager->max_index_counts[2] = 240;
  manager->max_vertex_counts[3] = 80;
  manager->max_index_counts[3] = 160;
  manager->max_vertex_counts[4] = 800;
  manager->max_index_counts[4] = 1280;
  manager->track_render_grid = (TrackRenderGrid *)((char *)g_game_base + 476696);
  v9 = 0;
  p_render_object = &manager->slots[4].render_object;
  do
  {
    for ( i = 0; i < 5; ++i )
    {
      v3 = (char *)manager + 60 * v9 + 60 * i;
      v4 = add_object_to_list(unk_4B7648);
      set_bod_object((_DWORD *)v3 + 22, (int)v4);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 16) = 0x80000;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 44) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 56) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 84) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 92) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 100) = 1;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 192) = create_object_vertex_buffer_resource(
                                                  (int *)&unk_4DFAFC[24151],
                                                  manager->max_vertex_counts[i],
                                                  322);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 200) = create_object_index_buffer_resource(
                                                  (int *)&unk_4DFAFC[33152],
                                                  manager->max_index_counts[i]);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 204) = allocate_tracked_memory(4, (int)aDxTexturegroup);
      **(_DWORD **)(*((_DWORD *)v3 + 31) + 204) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 208) = allocate_tracked_memory(4, (int)aDxTexturegroup_0);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 212) = allocate_tracked_memory(4, (int)aDxTexturegroup_1);
      if ( i == 4 )
        *(_DWORD *)&(*p_render_object)->_pad_00[20] = 5;
    }
    v5 = v9 + 5 < 715;
    v9 += 5;
    p_render_object += 75;
  }
  while ( v5 );
  shared_vertex_buffers = manager->shared_vertex_buffers;
  v7 = 5;
  do
  {
    *shared_vertex_buffers = allocate_tracked_memory(24 * (_DWORD)*(shared_vertex_buffers - 10), (int)aGdxCacheVertex);
    result = allocate_tracked_memory(2 * (_DWORD)*(shared_vertex_buffers - 5), (int)aGdxCacheIndexB);
    shared_vertex_buffers[5] = result;
    ++shared_vertex_buffers;
    --v7;
  }
  while ( v7 );
  return result;
}

