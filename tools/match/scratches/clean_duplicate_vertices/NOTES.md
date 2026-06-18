# clean_duplicate_vertices @ 0x419f80

Walks the duplicate-vertex remap buffer created by
`initialize_duplicate_vertices`. Each record is ten bytes; for each outer record,
the routine scans records from the same index onward and clears the inner
record's live flag at `+0x08` when its source vertex at `+0x00` matches the
outer record's compare vertex at `+0x02`.

Focused match: 100%, 33/33 instructions, no masked operands. The recovered
`DuplicateVertexBuffer` and 10-byte `DuplicateVertexRecord` layout is shared
through `tools/match/include/duplicate_vertices.h`.
