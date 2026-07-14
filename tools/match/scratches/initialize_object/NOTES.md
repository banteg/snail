# initialize_object @ 0x42f6f0

Exact default initializer for one `Object`/`cRObject` slot. It clears the
render flags and blend mode, live vertex and facequad counts, accumulated
vertex-normal pointer/count lane, and live texture-group count. `ObjectList`
owns the surrounding contiguous `0xdc`-byte slot array.

2026-07-14 void constructor ABI: the preserved iOS symbol is
`cRObject::cRObject()`, and every Windows caller either ignores EAX or uses the
separate constructor adapter at `0x42f6e0`, which explicitly returns the
original receiver. The zero left in EAX by this body is the shared assignment
value, not a result contract. Declaring the initializer `void` preserves its
exact 9/9 instructions; the adapter, list initializer, and slot allocator also
remain exact.
