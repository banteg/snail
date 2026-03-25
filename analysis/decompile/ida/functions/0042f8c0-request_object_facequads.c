/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_facequads @ 0x42f8c0 */
/* selector: request_object_facequads */

void __thiscall request_object_facequads(PathTemplateStripMesh *mesh, int32_t facequad_count)
{
  int32_t facequad_capacity; // eax

  if ( facequad_count )
  {
    facequad_capacity = mesh->facequad_capacity;
    if ( facequad_capacity > 0 && facequad_capacity < facequad_count )
    {
      report_errorf(aReallocationOf_0);
      free_tracked_memory((int)mesh->facequads);
      mesh->facequad_count = 0;
    }
    if ( !mesh->facequad_count )
    {
      mesh->facequads = (ObjectFaceQuad *)allocate_tracked_memory(48 * facequad_count, (int)aObjectFacequad);
      if ( facequad_count > (signed int)mesh->facequad_capacity )
        mesh->facequad_capacity = facequad_count;
    }
    mesh->facequad_count = facequad_count;
  }
  else
  {
    mesh->facequad_count = 0;
  }
}

