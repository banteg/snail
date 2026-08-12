# initialize_object @ 0x42f6f0

Exact 9/9-instruction `void cRObject::Init()` member. It clears the render
flags and blend mode, live geometry counts and pointers, accumulated-normal
state, and texture-group count for one `0xdc`-byte object slot.

Windows calls it from `cRObject::cRObject()`, `cRObjects::Init(int)`, and
`cRObjects::Add()`. Android exports the same `Init()` member and constructor
edge. iOS inlines the corresponding writes into `cRObject::cRObject()` and has
no standalone `Init` symbol. This cross-port split corrects the old mapping
that assigned the iOS constructor name directly to the Windows initializer.

All Windows callers and the natural member spelling remain instruction-exact;
the zero left in EAX is assignment residue, not a return contract.
