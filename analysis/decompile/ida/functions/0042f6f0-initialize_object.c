/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object @ 0x42f6f0 */
/* selector: initialize_object */

// Exact void Windows `cRObject::Init()`: clears one render object's geometry pointers/counts and default render state. Android independently preserves this member and calls it from `cRObject::cRObject()`; iOS inlines the same initialization into its constructor.
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
