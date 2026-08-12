# cRBorder::AddTextNumber @ 0x401030

Exact match: 100.00%, 68/68 instructions, with no masked operands.

The method appends a non-negative decimal value to the owned text buffer,
including the authored thousands separators and zero special case. Android
and iOS `Border.o` both preserve the owner and algorithm. Live Windows
analysis confirms a void thiscall and ten callsites across completion, high
score, and subgame presentation code.

The stable matcher identity remains `border_add_text_number`; source and
relocations use the authored member name.
