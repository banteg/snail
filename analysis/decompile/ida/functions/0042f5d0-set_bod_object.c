/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_bod_object @ 0x42f5d0 */
/* selector: set_bod_object */

// Stores the render-object pointer on one body record; iOS RObject.o names this `cRBod::SetObject(cRObject*)`.
int32_t __thiscall set_bod_object(BodBase *bod, Object *object)
{
  int32_t result; // eax

  bod->object = object;
  result = bod->bod.list_flags;
  LOBYTE(result) = result | 2;
  bod->bod.list_flags = result;
  return result;
}
