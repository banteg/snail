/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_render_cache_manager @ 0x433060 */
/* selector: initialize_track_render_cache_manager */

// Initializes the fixed 143x5 track-render cache bod grid plus its shared GDX cache vertex/index buffers and per-cache texture-group scratch arrays.
_BYTE *__thiscall sub_433060(_DWORD *this)
{
  int i; // edi
  _DWORD *v3; // esi
  _DWORD *v4; // eax
  bool v5; // cc
  _DWORD *v6; // esi
  int v7; // edi
  _BYTE *result; // eax
  int v9; // [esp+10h] [ebp-8h]
  _DWORD *v10; // [esp+14h] [ebp-4h]

  *(this + 1) = 560;
  *(this + 2) = 560;
  *(this + 6) = 1280;
  *(this + 7) = 1280;
  *(this + 3) = 160;
  *(this + 8) = 240;
  *(this + 4) = 80;
  *(this + 9) = 160;
  *(this + 5) = 800;
  *(this + 10) = 1280;
  *(this + 21) = (char *)MEMORY[0x4DF904] + 476696;
  v9 = 0;
  v10 = this + 91;
  do
  {
    for ( i = 0; i < 5; ++i )
    {
      v3 = this + 15 * v9 + 15 * i;
      v4 = add_object_to_list(unk_4B7648);
      set_bod_object(v3 + 22, (int)v4);
      *(_DWORD *)(v3[31] + 16) = 0x80000;
      *(_DWORD *)(v3[31] + 44) = 0;
      *(_DWORD *)(v3[31] + 56) = 0;
      *(_DWORD *)(v3[31] + 84) = 0;
      *(_DWORD *)(v3[31] + 92) = 0;
      *(_DWORD *)(v3[31] + 100) = 1;
      *(_DWORD *)(v3[31] + 192) = sub_4114B0(MEMORY[0x4F7458], *(this + i + 1), 322);
      *(_DWORD *)(v3[31] + 200) = sub_4115D0(MEMORY[0x5000FC], *(this + i + 6));
      *(_DWORD *)(v3[31] + 204) = allocate_tracked_memory(4, (int)aDxTexturegroup);
      **(_DWORD **)(v3[31] + 204) = 0;
      *(_DWORD *)(v3[31] + 208) = allocate_tracked_memory(4, (int)aDxTexturegroup_0);
      *(_DWORD *)(v3[31] + 212) = allocate_tracked_memory(4, (int)aDxTexturegroup_1);
      if ( i == 4 )
        *(_DWORD *)(*v10 + 20) = 5;
    }
    v5 = v9 + 5 < 715;
    v9 += 5;
    v10 += 75;
  }
  while ( v5 );
  v6 = this + 11;
  v7 = 5;
  do
  {
    *v6 = allocate_tracked_memory(24 * *(v6 - 10), (int)aGdxCacheVertex);
    result = allocate_tracked_memory(2 * *(v6 - 5), (int)aGdxCacheIndexB);
    v6[5] = result;
    ++v6;
    --v7;
  }
  while ( v7 );
  return result;
}

