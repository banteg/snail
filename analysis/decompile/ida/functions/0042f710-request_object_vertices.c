/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_vertices @ 0x42f710 */
/* selector: request_object_vertices */

void __thiscall request_object_vertices(PathTemplateStripMesh *mesh, int32_t vertex_count)
{
  int32_t v3; // eax

  if ( vertex_count > 0x10000 )
    report_errorf(aTooManyVertice);
  v3 = mesh->vertex_count;
  if ( v3 > 0 && v3 < vertex_count )
  {
    report_errorf(aReallocationOf);
    free_tracked_memory((int)mesh->vertices);
    mesh->vertex_count = 0;
  }
  if ( !mesh->vertex_count )
  {
    mesh->vertex_count = vertex_count;
    mesh->vertices = (Vec3 *)allocate_tracked_memory(12 * vertex_count, (int)aObjectVertexLi);
    request_object_vertex_colours(mesh);
  }
}

