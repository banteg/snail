/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_vertex_colours @ 0x42f850 */
/* selector: request_object_vertex_colours */

void __fastcall request_object_vertex_colours(PathTemplateStripMesh *mesh)
{
  signed int v2; // ecx
  int v3; // eax

  mesh->vertex_colours = (Color4f *)allocate_tracked_memory(16 * mesh->vertex_count, (int)aObjectVertexCo);
  v2 = 0;
  if ( (int)mesh->vertex_count > 0 )
  {
    v3 = 0;
    do
    {
      ++v2;
      mesh->vertex_colours[v3].r = 1.0;
      mesh->vertex_colours[v3].g = 1.0;
      mesh->vertex_colours[v3++].b = 1.0;
    }
    while ( v2 < (signed int)mesh->vertex_count );
  }
}

