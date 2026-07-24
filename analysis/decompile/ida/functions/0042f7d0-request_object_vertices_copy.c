/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_vertices_copy @ 0x42f7d0 */
/* selector: request_object_vertices_copy */

// Ensures one render object has the secondary copied-vertex storage; iOS RObject.o names this `cRObject::RequestVerticesCopy()`.
void __thiscall request_object_vertices_copy(Object *object)
{
  object->copied_vertices = (Vec3 *)allocate_tracked_memory(12 * object->vertex_count, aObjectVertexLi);
  copy_object_vertices(object);
}
