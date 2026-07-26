/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_object_vertices @ 0x42f790 */
/* selector: copy_object_vertices */

// Copies exactly `vertex_count` source `Vec3` records from one Object's borrowed `vertices` view into its owned `copied_vertices` bank, preserving the x, y, and z components used by the non-destructive distortion path. Android names the owner `cRObject::CopyVertices()` and preserves this 12-byte path, while its additional packed six-byte branch is port-specific.
void __thiscall copy_object_vertices(Object *object)
{
  int32_t v1; // edx
  int v2; // eax
  Vec3 *v3; // esi
  Vec3 *v4; // edi

  v1 = 0;
  if ( object->vertex_count > 0 )
  {
    v2 = 0;
    do
    {
      v3 = &object->vertices[v2];
      v4 = &object->copied_vertices[v2];
      ++v1;
      ++v2;
      v4->x = v3->x;
      v4->y = v3->y;
      v4->z = v3->z;
    }
    while ( v1 < object->vertex_count );
  }
}
