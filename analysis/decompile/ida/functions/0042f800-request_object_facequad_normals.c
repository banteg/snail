/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_facequad_normals @ 0x42f800 */
/* selector: request_object_facequad_normals */

// Ensures one object's toon-normal storage exists by allocating the per-vertex accumulated normal list and the per-face quad-normal pairs consumed by the outline pass. Android names the authored owner `cRObject::RequestFaceQuadNormals()`, but uses a different mobile normal representation; Windows layout and retained-pointer return remain independently proved.
Vec3 *__thiscall request_object_facequad_normals(Object *object)
{
  Vec3 *result; // eax

  if ( object->vertex_normals == nullptr )
    object->vertex_normals = (Vec3 *)allocate_tracked_memory(12 * object->vertex_count, aObjectVertexNo);
  result = object->facequad_normals;
  if ( result == nullptr )
  {
    result = (Vec3 *)allocate_tracked_memory(24 * object->facequad_count, aObjectFacequad_0);
    object->facequad_normals = result;
  }
  return result;
}
