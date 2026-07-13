# initialize_global_temp_colour_thunk

CRT table entry `0x4a1028` points to this one-instruction thunk at `0x42f8a0`,
which tail-jumps over 11 alignment nops to the adjacent `GTempColour`
constructor. The source-level tail call matches the native 1/1 instruction
exactly, with its target resolved.
