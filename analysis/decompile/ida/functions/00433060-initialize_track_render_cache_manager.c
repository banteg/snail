/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_render_cache_manager @ 0x433060 */
/* selector: initialize_track_render_cache_manager */

// Initializes the embedded cRSegmentCache owner: a fixed 143x5 track-render BOD grid plus shared GDX cache vertex/index buffers and per-family scratch arrays. Its complete 0xa7f8-byte extent matches the Windows runtime size ledger.
void __thiscall initialize_track_render_cache_manager(SegmentCache *manager)
{
  int i; // edi
  char *v3; // esi
  Object *v4; // eax
  bool v5; // cc
  ObjectRenderVertex **shared_vertex_buffers; // esi
  int v7; // edi
  int v8; // [esp+10h] [ebp-8h]
  Object **p_object; // [esp+14h] [ebp-4h]

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
  manager->owner_subgame = (SubgameRuntime *)&g_game_base->subgame;
  v8 = 0;
  p_object = &manager->slots[0][4].bod.object;
  do
  {
    for ( i = 0; i < 5; ++i )
    {
      v3 = (char *)manager + 60 * v8 + 60 * i;
      v4 = add_object_to_list(&g_object_list);
      set_bod_object((BodBase *)(v3 + 88), v4);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 16) = 0x80000;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 44) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 56) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 84) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 92) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 100) = 1;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 192) = create_vertex_buffer(
                                                  &g_direct3d_renderer.vertex_buffer_factory,
                                                  manager->max_vertex_counts[i],
                                                  322);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 200) = create_index_buffer(
                                                  &g_direct3d_renderer.index_buffer_factory,
                                                  manager->max_index_counts[i]);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 204) = allocate_tracked_memory(4, (int)aDxTexturegroup);
      **(_DWORD **)(*((_DWORD *)v3 + 31) + 204) = 0;
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 208) = allocate_tracked_memory(4, (int)aDxTexturegroup_0);
      *(_DWORD *)(*((_DWORD *)v3 + 31) + 212) = allocate_tracked_memory(4, (int)aDxTexturegroup_1);
      if ( i == 4 )
        (*p_object)->blend_mode = 5;
    }
    v5 = v8 + 5 < 715;
    v8 += 5;
    p_object += 75;
  }
  while ( v5 );
  shared_vertex_buffers = manager->shared_vertex_buffers;
  v7 = 5;
  do
  {
    *shared_vertex_buffers = (ObjectRenderVertex *)allocate_tracked_memory(
                                                     24 * (_DWORD)*(shared_vertex_buffers - 10),
                                                     (int)aGdxCacheVertex);
    shared_vertex_buffers[5] = (ObjectRenderVertex *)allocate_tracked_memory(
                                                       2 * (_DWORD)*(shared_vertex_buffers - 5),
                                                       (int)aGdxCacheIndexB);
    ++shared_vertex_buffers;
    --v7;
  }
  while ( v7 );
}
