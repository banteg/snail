/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_object_to_list @ 0x42fad0 */
/* selector: add_object_to_list */

// Appends one render object to the global object list and returns the new slot; iOS RObject.o names this `cRObjects::Add()`.
Object *__thiscall add_object_to_list(ObjectList *object_list)
{
  int32_t v2; // ecx
  Object *v3; // edi

  if ( object_list->count == object_list->capacity )
    report_errorf(aTooManyObjects);
  v2 = object_list->count++;
  v3 = &object_list->objects[v2];
  initialize_object(v3);
  return v3;
}
