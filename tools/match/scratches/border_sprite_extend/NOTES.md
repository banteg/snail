# cRBorder::SpriteExtend @ 0x404540

Exact match: 100.00%, 14/14 instructions, with no masked operands.

The method stores the hot and hit-mask textures plus one retained integer,
enables the extended sprite lane, records the wobble direction, and clears
the three padding targets. Android `Border.o` preserves the authored owner
and `bool` argument. Live Windows analysis confirms the byte-sized argument,
void thiscall, and two native callsites; no iOS export survives.

The stable matcher identity remains `border_sprite_extend`; source and
relocations use the authored member name.
