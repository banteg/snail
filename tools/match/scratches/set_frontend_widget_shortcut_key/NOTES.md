# cRBorder::SetKeyLeft @ 0x402790

Exact match: 100.00%, 6/6 instructions, with no masked operands.

The method stores one shortcut key and enables its dispatch flag. Android and
iOS `Border.o` preserve the authored member and behavior. Live Windows
analysis confirms a void thiscall and five native callsites; the flags word
left in EAX is incidental.

The stable matcher identity remains `set_frontend_widget_shortcut_key`;
source and relocations use the authored member name.
