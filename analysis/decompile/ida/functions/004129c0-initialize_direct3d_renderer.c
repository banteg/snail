/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_direct3d_renderer @ 0x4129c0 */
/* selector: initialize_direct3d_renderer */

// Initializes renderer defaults, creates the Direct3D8 device, and allocates the shared transient 8-vertex sprite/object buffer.
uint8_t __cdecl initialize_direct3d_renderer()
{
  initialize_direct3d_renderer_defaults(&g_direct3d_renderer);
  initialize_d3d8_device(&g_direct3d_renderer, 0);
  g_direct3d_renderer.renderer_state = create_vertex_buffer(&g_direct3d_renderer.vertex_buffer_factory, 8, 322);
  return 1;
}
