/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_all_objects @ 0x42f9e0 */
/* selector: build_all_objects */

// Builds every object in the global render-object list; iOS RObject.o names this `cRObjects::BuildObjects()`.
void __thiscall build_all_objects(ObjectList *object_list)
{
  int32_t v2; // ebx
  int v3; // edi
  Object *v4; // ecx
  Object *v5; // ecx

  v2 = 0;
  if ( object_list->count > 0 )
  {
    v3 = 0;
    do
    {
      if ( !(v2 % 4) )
        update_loading_screen(&g_loading_bar);
      v4 = &object_list->objects[v3];
      if ( v4->vertex_count )
      {
        calc_object_bounding_box(v4);
        sort_object_faces_by_texture_group(&object_list->objects[v3]);
        calc_object_texture_groups(&object_list->objects[v3]);
        v5 = &object_list->objects[v3];
        if ( (v5->flags & 0x4000) != 0 )
        {
          calc_object_facequad_normals(v5);
          calc_object_edges(&object_list->objects[v3]);
        }
        build_object_texture_group_buffers(&object_list->objects[v3]);
      }
      ++v2;
      ++v3;
    }
    while ( v2 < object_list->count );
  }
}
