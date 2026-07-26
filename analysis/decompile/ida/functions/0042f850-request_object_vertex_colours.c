/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_vertex_colours @ 0x42f850 */
/* selector: request_object_vertex_colours */

// Authored `cRObject::RequestColours()` member: allocates one Object-owned `tColour` bank sized by `vertex_count`, initializes each record's red, green, and blue lanes to 1.0, and intentionally leaves alpha untouched. The Android body confirms the same 16-byte stride and initialization contract.
void __fastcall request_object_vertex_colours(Object *object)
{
  int32_t v2; // ecx
  int v3; // eax

  object->vertex_colours = (tColour *)allocate_tracked_memory(16 * object->vertex_count, aObjectVertexCo);
  v2 = 0;
  if ( object->vertex_count > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      object->vertex_colours[v3].r = 1.0;
      object->vertex_colours[v3].g = 1.0;
      object->vertex_colours[v3++].b = 1.0;
    }
    while ( v2 < object->vertex_count );
  }
}
