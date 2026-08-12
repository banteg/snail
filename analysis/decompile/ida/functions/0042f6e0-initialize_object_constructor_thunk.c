/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object_constructor_thunk @ 0x42f6e0 */
/* selector: initialize_object_constructor_thunk */

// Exact Windows `cRObject::cRObject()` constructor: calls the adjacent `Init()` member at 0x42f6f0 and returns the receiver through the constructor ABI. Android preserves the same split constructor/Init lifecycle; iOS keeps the constructor but inlines the initialization body.
Object *__thiscall initialize_object_constructor_thunk(Object *object)
{
  initialize_object(object);
  return object;
}
