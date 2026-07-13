# initialize_global_noop_renderable_bods

CRT constructor body at `0x406bd0` for three global records at `0x4b6fb4`,
`0x4b7078`, and `0x4b713c`. Their `0xc4` stride proves a common aggregate; each
record owns a normal `RenderableBod` prefix and then receives the shared
`noop_runtime_ai` callback table.

No instruction outside this initializer addresses any of the three records, so
the `0x4c` tail and original gameplay class remain deliberately unnamed. The
aggregate begins 0x64 bytes after the independently bounded 0x4000-byte
`g_animation_directory`, correcting the former overlapping global extent.
The three prefix constructions compile to the native 10/10 instructions
exactly, with all 9 masked operands resolved.
