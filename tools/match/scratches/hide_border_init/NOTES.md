# cRBorder::HideInit @ 0x4010e0

Exact match: 100.00%, 9/9 instructions, with its call operand clean.

The method starts the hidden transition once, clears `hide_blend`, and resets
the owned `cRToolTip`. Android and iOS `Border.o` preserve the authored owner
and behavior. Live Windows analysis confirms a void thiscall and 45 native
callsites.

The stable matcher identity remains `hide_border_init`; source and relocations
use the authored member name.
