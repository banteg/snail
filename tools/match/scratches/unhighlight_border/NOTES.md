# cRBorder::UnHighlight @ 0x4027e0

Exact match: 100.00%, 4/4 instructions, with no masked operands.

The method clears the hover blend target and restores idle padding. Android
`Border.o` preserves the authored owner and stores. Live Windows analysis
confirms a void thiscall and three native callsites; the padding bits left in
EAX are incidental. No iOS export survives.

The stable matcher identity remains `unhighlight_border`; source and
relocations use the authored member name.
