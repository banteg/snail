# cRBorder::SetBelow @ 0x4027b0

Exact match: 100.00%, 9/9 instructions, with its call operand clean.

The method copies the previous border's x anchor, stacks below its y extent,
and relayouts the receiver. Android and iOS `Border.o` preserve the authored
owner and operation. Live Windows analysis confirms a void thiscall and 36
native callsites.

The stable matcher identity remains `stack_widget_below`; source and
relocations use the authored member name.
