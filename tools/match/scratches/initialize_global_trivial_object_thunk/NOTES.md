# initialize_global_trivial_object_thunk

One-instruction CRT initializer-table thunk at `0x406d10`. The table entry at
`0x4a100c` points here; the thunk tail-jumps over 11 alignment nops to the
constructor body at `0x406d20`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.
