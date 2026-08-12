# initialize_input @ 0x40aa50

Exact Windows `cRInput::Init()` at 12/12 instructions with no masked
references. Android independently preserves the owner, method, and field
semantics in `Game.o`.

Root initialization assigns controller slots 0 and 1 to the two embedded
`cRInput` records and calls this initializer with each subobject in ECX. It
seeds the edge masks, axes, 320x240 authored pointer position, and pointer
value. The caller ignores EAX, while Android leaves a different incidental
receiver value, confirming the void contract.
