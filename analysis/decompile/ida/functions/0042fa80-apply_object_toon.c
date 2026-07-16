/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_object_toon @ 0x42fa80 */
/* selector: apply_object_toon */

// Marks one object as toon-enabled and prepares its outline support buffers. Cross-port Android and iOS symbols match this helper to `cRObject::ApplyToon(int)`, but the Windows split also allocates support storage here.
void __thiscall apply_object_toon(Object *object, int32_t toon_flags)
{
  int32_t vertex_count; // eax

  vertex_count = object->vertex_count;
  object->flags |= toon_flags | 0x4001;
  object->toon_vertices = (Vec3 *)allocate_tracked_memory(12 * vertex_count, aObjectToonVert);
  object->toon_facequad_normals = (ObjectToonFaceQuadNormal *)allocate_tracked_memory(
                                                                24 * object->facequad_count,
                                                                aObjectToonFace);
}
