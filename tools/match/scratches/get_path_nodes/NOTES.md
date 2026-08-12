# cRPath::GetNodes @ 0x41b0a0

Exact match: 100.00%, 23/23 instructions.

This authored lifecycle member allocates the two `0xa8`-stride sample banks
owned by one `cRPath`: `primary_samples` at `Path +0x58` and
`secondary_samples` at `Path +0x5c`, using the native labels
`Path Tile Nodes` and `Path Ball nodes`. The allocation count comes from
`segment_count` at `Path +0x44`.

Live Windows xrefs show 30 path-builder and mirror callsites using this
receiver. Android `Path.o` independently exports `cRPath::GetNodes()` and
preserves the paired allocations. Its body additionally seeds sample defaults;
iOS inlines that broader mobile lifecycle form, so no exact iOS body is
claimed for the narrower Windows allocator.

The stable matcher identity remains `get_path_nodes`; the scratch and native
relocations now use the authored member name.
