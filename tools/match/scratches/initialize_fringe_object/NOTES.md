# initialize_fringe_object @ 0x408650

Exact constructor wrapper for one authored `Fringe` (`cRFringe` on Android):
runs the shared BodBase constructor, installs the Windows fringe vtable at
`0x497344`, and returns the receiver. That table points directly to
`refresh_fringe_object_draw_list @ 0x439b00`.

The exact runtime-pool constructor creates 7000 consecutive 0x38-byte records
inside the owned `FringeManager`. The scratch now defines the method on the
shared `Fringe` class; `FringeObject` remains only a compatibility alias.
Focused matching remains exact at 7/7 instructions with two clean operands.

2026-07-17: the compatibility analysis type now nests the complete inherited
`BodBase` instead of duplicating its fields, and the wrapper ABI is preserved
as `FringeObject* __thiscall initialize_fringe_object(FringeObject*)`.
