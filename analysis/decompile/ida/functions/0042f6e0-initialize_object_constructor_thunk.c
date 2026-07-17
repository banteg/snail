/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_object_constructor_thunk @ 0x42f6e0 */
/* selector: initialize_object_constructor_thunk */

// Object constructor thunk that calls the recovered object initializer and returns the original receiver.
Object *__thiscall initialize_object_constructor_thunk(Object *object)
{
  initialize_object(object);
  return object;
}
