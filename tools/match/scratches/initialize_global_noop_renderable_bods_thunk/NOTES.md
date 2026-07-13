# initialize_global_noop_renderable_bods_thunk

One-instruction CRT initializer-table thunk at `0x406bc0`. The table entry at
`0x4a1004` points here; the thunk tail-jumps over 11 alignment nops to the
constructor body at `0x406bd0`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.
