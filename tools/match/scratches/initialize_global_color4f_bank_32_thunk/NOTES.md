# initialize_global_color4f_bank_32_thunk

CRT table entry `0x4a1014` points to this one-instruction thunk at `0x410c00`,
which tail-jumps over 11 alignment nops to the adjacent 32-entry Color4f
constructor loop. The source-level tail call matches the native 1/1 instruction
exactly, with its target resolved.
