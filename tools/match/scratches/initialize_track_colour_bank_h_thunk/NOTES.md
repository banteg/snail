# initialize_track_colour_bank_h_thunk

CRT table entry `0x4a1048` points to this one-instruction thunk at
`0x434aa0`, which tail-jumps over 11 alignment nops to the adjacent
constructor loop. The source-level tail call matches the native 1/1 instruction
exactly, with its single masked target resolved.
