/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: load_registered_texture_refs @ 0x412a00 */
/* selector: load_registered_texture_refs */

// Windows `G0TextureSetLoad(int)`: allocates the renderer's indexed texture-slot array, resets the shared VRAM estimate, invokes G0TextureLoad for every cRTexture owned by cRTextures, then reports kilobytes. Android and iOS retain the same authored lifecycle plus OpenGL-only name/residency setup.
int32_t load_registered_texture_refs()
{
  int32_t v0; // esi

  g_d3d_texture_slots = (Direct3DTexture8 **)allocate_tracked_memory(4 * g_texture_refs.count, aDirectxTexture);
  v0 = 0;
  for ( g_estimated_texture_vram_bytes = 0; v0 < g_texture_refs.count; ++v0 )
    load_registered_texture_ref(v0);
  return debug_report_stub("Estimate %i K VRAM\n", g_estimated_texture_vram_bytes / 1024);
}
