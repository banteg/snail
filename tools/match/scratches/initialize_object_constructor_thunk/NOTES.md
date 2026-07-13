# initialize_object_constructor_thunk @ 0x42f6e0

Constructor adapter used by the root runtime's object-pool array initializer.
It preserves the incoming `Object*`, runs the recovered empty/default object
initializer at `0x42f6f0`, and returns the original receiver.
