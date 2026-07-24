/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: request_object_facequads @ 0x42f8c0 */
/* selector: request_object_facequads */

// Ensures one render object has the requested face-quad storage; iOS RObject.o names this `cRObject::RequestFaceQuads(int)`.
void __thiscall request_object_facequads(Object *object, int32_t facequad_count)
{
  int32_t facequad_capacity; // eax

  if ( facequad_count )
  {
    facequad_capacity = object->facequad_capacity;
    if ( facequad_capacity > 0 && facequad_capacity < facequad_count )
    {
      report_errorf(aReallocationOf_0);
      free_tracked_memory(object->facequads);
      object->facequad_count = 0;
    }
    if ( !object->facequad_count )
    {
      object->facequads = (ObjectFaceQuad *)allocate_tracked_memory(48 * facequad_count, aObjectFacequad);
      if ( facequad_count > object->facequad_capacity )
        object->facequad_capacity = facequad_count;
    }
    object->facequad_count = facequad_count;
  }
  else
  {
    object->facequad_count = 0;
  }
}
