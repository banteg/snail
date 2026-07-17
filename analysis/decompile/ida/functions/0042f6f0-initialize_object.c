/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object @ 0x42f6f0 */
/* selector: initialize_object */

// Constructs one render object with empty geometry buffers and default render flags; iOS RObject.o names this `cRObject::cRObject()`.
void __thiscall initialize_object(Object *object)
{
  object->flags = 0;
  object->blend_mode = 0;
  object->vertex_count = 0;
  object->facequad_count = 0;
  object->vertex_normals = nullptr;
  object->field_40 = 0;
  object->texture_group_count = 0;
}
