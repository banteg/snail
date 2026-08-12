# cRGame::InitLast @ 0x410720

Exact match: 100.00%, 4/4 instructions, with its call operand clean.

The method completes root startup by initializing the owned cRBackdrop in
last-mode 1. Android and iOS `Game.o` preserve the authored lifecycle name;
Android also preserves the complete Windows backdrop operation inside its
larger platform finalizer. Live Windows analysis confirms a void thiscall and
one startup caller.

The stable matcher identity remains `initialize_game_last`; source and
relocations use the authored member name.
