# initialize_default_runtime_config_thunk

One-instruction CRT initializer-table thunk at `0x406c10`. The table entry at
`0x4a1008` points here; the thunk tail-jumps over 11 alignment nops to the
`SnailMail.cfg` default-state initializer at `0x406c20`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.
