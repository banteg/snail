/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_or_reuse_cached_x_mesh @ 0x405cc0 */
/* selector: load_or_reuse_cached_x_mesh */

// Searches the root DirectX loader's fixed 128-slot X-mesh cache by name and returns the existing index on a hit; on a miss it appends a new entry, allocates its backing object from the global object list, loads the mesh, and returns the new index.
int32_t __thiscall load_or_reuse_cached_x_mesh(DirectXLoader *loader, char *mesh_name)
{
  int32_t v3; // edi
  char *name; // ebx
  Object *v5; // eax
  int32_t v6; // eax

  v3 = 0;
  if ( loader->cached_x_mesh_count <= 0 )
  {
LABEL_5:
    rstrcpy_checked_ascii(loader->cached_x_mesh_slots[loader->cached_x_mesh_count].name, mesh_name);
    v5 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)&loader->cached_x_mesh_slots[loader->cached_x_mesh_count], v5);
    load_x_mesh(loader, mesh_name, loader->cached_x_mesh_slots[v3].object, 1);
    v6 = loader->cached_x_mesh_count + 1;
    loader->cached_x_mesh_count = v6;
    return v6 - 1;
  }
  else
  {
    name = loader->cached_x_mesh_slots[0].name;
    while ( !strings_equal_case_insensitive_path(mesh_name, name) )
    {
      ++v3;
      name += 188;
      if ( v3 >= loader->cached_x_mesh_count )
        goto LABEL_5;
    }
    return v3;
  }
}
