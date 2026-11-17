/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: load_registered_texture_ref @ 0x412a70 */
/* selector: load_registered_texture_ref */

// Windows `G0TextureLoad(int, int)`: loads one cRTexture by index, honors the shared skip/retain-source flags, installs the platform texture, accounts VRAM, and publishes width/height into the same 0xa4-byte record used by both mobile ports. All three retain the legacy second argument without reading it; Direct3D/OpenGL upload and missing-file policy remain platform-specific.
TextureRefFlags __cdecl load_registered_texture_ref(uint32_t color_key)
{
  uint32_t v2; // esi
  TextureRefFlags result; // eax
  uint32_t v4; // ebx
  void *archive_data_base; // ebx
  uint32_t v6; // edi
  int32_t texture_from_file_in_memory; // eax
  int v8; // edi
  int v9; // edx
  int out_size; // [esp+7Ch] [ebp-18h] BYREF
  char Buffer[12]; // [esp+80h] [ebp-14h] BYREF
  unsigned __int16 v12; // [esp+8Ch] [ebp-8h]
  unsigned __int16 v13; // [esp+8Eh] [ebp-6h]
  char v14; // [esp+90h] [ebp-4h]
  uint32_t color_keya; // [esp+98h] [ebp+4h]

  v2 = color_key;
  result = g_texture_refs.entries[color_key].flags;
  if ( SBYTE1(result) >= 0 )
  {
    if ( archive_or_file_exists(g_texture_refs.entries[v2].name, 0) != 0 )
    {
      if ( (g_texture_refs.entries[color_key].flags & 0x20) != 0 )
        g_texture_refs.entries[color_key].texture_ref = load_file_bytes(g_texture_refs.entries[color_key].name, nullptr);
      else
        g_texture_refs.entries[color_key].texture_ref = nullptr;
      load_file_bytes_fixed_size_from_archive_or_fs(g_texture_refs.entries[v2].name, Buffer, 20);
      v4 = v14 != 32 ? 0 : 0xFFFFFF;
      color_keya = v4;
      if ( is_archive_index_loaded() != 0 )
      {
        archive_data_base = get_archive_data_base();
        load_file_bytes_from_archive_or_fs(g_texture_refs.entries[v2].name, archive_data_base, &out_size);
        v6 = color_key;
        texture_from_file_in_memory = d3dx_create_texture_from_file_in_memory_ex(
                                        g_direct3d_renderer.device,
                                        archive_data_base,
                                        out_size,
                                        0,
                                        0,
                                        g_texture_refs.entries[v2].mip_levels,
                                        0,
                                        0x15u,
                                        1u,
                                        3u,
                                        3u,
                                        color_keya,
                                        nullptr,
                                        nullptr,
                                        (void **)&g_d3d_texture_slots[v6]);
      }
      else
      {
        v6 = color_key;
        texture_from_file_in_memory = d3dx_create_texture_from_file_ex(
                                        g_direct3d_renderer.device,
                                        g_texture_refs.entries[v2].name,
                                        0,
                                        0,
                                        g_texture_refs.entries[v2].mip_levels,
                                        0,
                                        0x15u,
                                        1u,
                                        3u,
                                        3u,
                                        v4,
                                        nullptr,
                                        nullptr,
                                        (void **)&g_d3d_texture_slots[v6]);
      }
      if ( texture_from_file_in_memory >= 0 )
      {
        g_direct3d_renderer.device->vtbl->SetTexture(g_direct3d_renderer.device, 0, g_d3d_texture_slots[v6]);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 16, 3);
        g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 17, 3);
        if ( v14 == 32 )
        {
          g_texture_refs.entries[v2].flags |= 0x10000u;
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 1, 4);
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 2, 2);
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 3, 0);
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 4, 4);
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 5, 2);
          g_direct3d_renderer.device->vtbl->SetTextureStageState(g_direct3d_renderer.device, 0, 6, 0);
        }
        result = v13;
        v8 = g_estimated_texture_vram_bytes;
        v9 = v13 * v12;
        g_texture_refs.entries[v2].loaded_width = v12;
        g_texture_refs.entries[v2].loaded_height = result;
        g_estimated_texture_vram_bytes = v8 + 4 * v9;
      }
      else
      {
        report_errorf("Failed to Create DirectX Texture %s", g_texture_refs.entries[v2].name);
        return d3dx_create_texture_from_file(
                 g_direct3d_renderer.device,
                 (char *)aSpritesDebugTg,
                 (void **)&g_d3d_texture_slots[v6]);
      }
    }
    else
    {
      report_warningf("Texture File Missing using Debug.tga (%s)", g_texture_refs.entries[v2].name);
      return d3dx_create_texture_from_file(
               g_direct3d_renderer.device,
               (char *)aSpritesDebugTg,
               (void **)&g_d3d_texture_slots[color_key]);
    }
  }
  return result;
}
