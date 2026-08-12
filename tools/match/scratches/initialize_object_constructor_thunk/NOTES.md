# initialize_object_constructor_thunk @ 0x42f6e0

Constructor adapter used by the root runtime's object-pool array initializer.
It preserves the incoming `Object*`, runs the recovered empty/default object
initializer at `0x42f6f0`, and returns the original receiver.

2026-07-17: exact 6/6 code and the Object-derived `Movie` caller close
the adapter ABI as `Object* __thiscall initialize_object_constructor_thunk(Object*)`.
The unrelated `std::_Vector_iterator::operator++` symbol previously imported
at this address is retired; it described neither the code nor its callers.

## 2026-08-12 source-unit closure

The thunk is the only function between the verified `RObject.o` bodies
`cRBod::ApplyPos` and `cRObject::cRObject`. It has one native xref, from the
object-pool array initializer, and its sole outbound call is the immediately
following recovered object initializer. This closes its Windows compilation
unit as `RObject.o` without claiming a standalone mobile constructor-thunk
symbol.
