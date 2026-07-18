/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: create_vertex_buffer @ 0x4114b0 */
/* selector: create_vertex_buffer */

// Allocates one Direct3D vertex buffer in the renderer's fixed 3000-slot ObjectRenderBuffers pool using the requested FVF layout.
ObjectRenderBuffers *__thiscall create_vertex_buffer(VertexBufferFactory *factory, int32_t vertex_count, int32_t fvf)
{
  int32_t v4; // edi
  int32_t next_count; // edx

  factory->buffers[factory->count].fvf = fvf;
  switch ( fvf )
  {
    case 2:
      v4 = g_direct3d_renderer.device->vtbl->CreateVertexBuffer(
             g_direct3d_renderer.device,
             12 * vertex_count,
             8,
             2,
             1,
             &factory->buffers[factory->count].vertex_buffer);
      break;
    case 258:
      v4 = g_direct3d_renderer.device->vtbl->CreateVertexBuffer(
             g_direct3d_renderer.device,
             20 * vertex_count,
             8,
             258,
             1,
             &factory->buffers[factory->count].vertex_buffer);
      break;
    case 322:
      v4 = g_direct3d_renderer.device->vtbl->CreateVertexBuffer(
             g_direct3d_renderer.device,
             24 * vertex_count,
             8,
             322,
             1,
             &factory->buffers[factory->count].vertex_buffer);
      break;
    default:
      v4 = vertex_count;
      break;
  }
  if ( v4 )
  {
    report_errorf(aVertexBufferRe);
    if ( v4 == -2005532292 || v4 == -2147024882 || v4 == -2005530516 )
      debug_report_stub();
  }
  next_count = factory->count + 1;
  factory->count = next_count;
  if ( next_count == 3000 )
  {
    report_errorf(aDxVertexbuffer);
    while ( 1 )
      ;
  }
  return (ObjectRenderBuffers *)((char *)factory + 12 * next_count - 8);
}
