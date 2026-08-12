# cRInputOK::AI @ 0x4034d0

Exact match: 100.00%, 32/32 instructions, with no masked operands.

This layout method positions the BorderManager-owned OK widget to the right or
left of its borrowed source border according to the source input flags, then
copies the top and authored anchors. The 0x24-byte `cRInputOK` owns neither of
its two `cRBorder*` handles.

Android `Border.o` exports `cRInputOK::AI()` with the same field pair and
placement formulas, and `cRInputOK::Init()` calls it directly. No iOS export
survives. Live Windows analysis confirms a void thiscall and two callers: the
initializer and the text-input updater.

The stable matcher identity remains `update_input_ok`; source and relocations
now use the authored member name.
