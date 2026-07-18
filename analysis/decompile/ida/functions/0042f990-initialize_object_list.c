/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object_list @ 0x42f990 */
/* selector: initialize_object_list */

// Initializes the global render-object list with the requested capacity; iOS RObject.o names this `cRObjects::Init(int)`.
void __thiscall initialize_object_list(ObjectList *object_list, int32_t capacity)
{
  int32_t v2; // esi
  int v4; // ebx

  v2 = capacity;
  object_list->count = 0;
  object_list->capacity = capacity;
  object_list->objects = (Object *)allocate_tracked_memory(220 * capacity, aObjectList);
  if ( capacity > 0 )
  {
    v4 = 0;
    do
    {
      initialize_object(&object_list->objects[v4++]);
      --v2;
    }
    while ( v2 );
  }
}
