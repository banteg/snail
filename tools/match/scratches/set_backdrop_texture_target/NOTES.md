# cRBackdrop::SetWorld @ 0x410f40

Exact Windows member: 14/14 instructions with both masked operands clean.
Android independently preserves `cRBackdrop::SetWorld(int)` and the same seven
field operations.

For each owned `BackdropWorldBlend` lane, the method inverts the blend fraction,
moves the current world into the previous slot, and installs the new world.
Both Windows calls come from `cRBackdrop::Init` and discard EAX, confirming the
void result contract.

The stable matcher identity remains `set_backdrop_texture_target`, with the
authored VC6 decorated symbol selected by `scratch.conf`.
