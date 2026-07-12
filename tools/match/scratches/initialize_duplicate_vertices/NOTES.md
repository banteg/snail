# initialize_duplicate_vertices @ 0x419f50

The iOS symbol table preserves this exact owner and method as
`cRDuplicateVertices::Init(int)` in `ObjectProc.o`. Windows initializes the
same 8-byte embedded owner: `active_count` at `+0x00` and a pointer to
10-byte `DuplicateVertexRecord` entries at `+0x04`. `DirectXLoader::Init()`
passes 2000 and retains the owner at loader `+0x5e08`.

Focused match: 100%, 13/13 instructions, with both masked operands clean. The
Windows body leaves the allocation pointer in `eax`, stores it in `records`,
and returns it. The cross-port C++ symbol does not encode a return type, and
the sole caller ignoring `eax` is insufficient to prove `void`, so the exact
Windows pointer result is retained rather than normalized speculatively.
