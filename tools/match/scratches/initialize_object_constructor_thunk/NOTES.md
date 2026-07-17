# initialize_object_constructor_thunk @ 0x42f6e0

Constructor adapter used by the root runtime's object-pool array initializer.
It preserves the incoming `Object*`, runs the recovered empty/default object
initializer at `0x42f6f0`, and returns the original receiver.

2026-07-17: exact 6/6 code and the Object-derived `FrameSequence` caller close
the adapter ABI as `Object* __thiscall initialize_object_constructor_thunk(Object*)`.
The unrelated `std::_Vector_iterator::operator++` symbol previously imported
at this address is retired; it described neither the code nor its callers.
