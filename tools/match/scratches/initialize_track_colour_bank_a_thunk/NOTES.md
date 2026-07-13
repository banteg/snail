# initialize_track_colour_bank_a_thunk

CRT table entry `0x4a1030` points to this one-instruction thunk at `0x434980`,
which tail-jumps over 11 alignment nops to the bank-A constructor loop.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.
