# initialize_bod_base @ 0x42f5f0

Exact match: 100.00%, 27/27 instructions.

Initializes the shared BOD base vtable, default flags, color lane, constructor
counter, and zeroed runtime links. The first call targets the no-op `this`
constructor thunk at `0x44db50` (`mov eax, ecx; ret`) before the same storage is
written as a `Color4f`.
