# clean_duplicate_vertices @ 0x419f80

Walks the duplicate-vertex remap buffer created by
`initialize_duplicate_vertices`. Each record is ten bytes; for each outer record,
the routine scans records from the same index onward and clears the inner
record's live flag at `+0x08` when its source vertex at `+0x00` matches the
outer record's compare vertex at `+0x02`.

Focused match: 100%, 33/33 instructions, no masked operands. The recovered
`DuplicateVertices` and 10-byte `DuplicateVertexRecord` layout is shared
through `tools/match/include/duplicate_vertices.h`.

The iOS symbol table preserves the containing owner as
`cRDuplicateVertices::Init(int)` in `ObjectProc.o`. Windows embeds the exact
8-byte owner at `DirectXLoader +0x5e08`, and this cleanup method consumes the
same receiver. No corresponding mobile cleanup symbol survives, so the stable
Windows helper name and its `int` result remain unchanged rather than inventing
an authored method name or return contract. The native `retn 4` proves the
otherwise-unused stack argument remains part of the Windows ABI.
