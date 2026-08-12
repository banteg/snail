# cRBorder::InputTextInit @ 0x403410

Exact match: 100.00%, 46/46 instructions, with all three masked operands clean.

The method initializes the complete inline editor tail, appends the visible
cursor marker, relayouts the border, and conditionally initializes its
embedded `cRInputOK`. Android and iOS `Border.o` preserve the authored owner
and lifecycle. Live Windows analysis confirms a void thiscall and two native
callsites.

The stable matcher identity remains `border_input_text_init`; source and
relocations use the authored member name.
