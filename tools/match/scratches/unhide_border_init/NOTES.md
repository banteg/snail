# cRBorder::UnHideInit @ 0x401110

Exact match: 100.00%, 5/5 instructions, with no masked operands.

The method restores `hide_blend` to one and clears the hidden-transition flag.
Android and iOS `Border.o` preserve the authored owner and stores. Live
Windows analysis confirms a void thiscall and 32 native callsites.

The stable matcher identity remains `unhide_border_init`; source and
relocations use the authored member name.
