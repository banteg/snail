/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: create_index_buffer @ 0x4115d0 */
/* selector: create_index_buffer */

// Allocates one 16-bit Direct3D index buffer in the renderer's embedded fixed 3000-slot IndexBufferFactory pool.
ObjectIndexBuffer *__thiscall create_index_buffer(IndexBufferFactory *factory, int32_t index_count)
{
  int32_t v3; // edi
  int32_t next_count; // eax

  v3 = g_direct3d_renderer.device->vtbl->CreateIndexBuffer(
         g_direct3d_renderer.device,
         2 * index_count,
         40,
         101,
         1,
         (ObjectIndexBufferResource **)&factory->buffers[factory->count]);
  next_count = factory->count + 1;
  factory->count = next_count;
  if ( next_count == 3000 )
    report_errorf(aTooManyIndexBu);
  if ( v3 )
    report_errorf(aVertexBufferRe);
  return (ObjectIndexBuffer *)(&factory->count + factory->count);
}
