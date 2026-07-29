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
same receiver. The native `retn 4` proves the otherwise-unused stack argument
remains part of the Windows ABI.

## 2026-07-27 Android Clean owner and void ABI

The expanded Android corpus now retains
`cRDuplicateVertices::Clean(int)`. Its body preserves the same 8-byte owner,
10-byte record stride, outer compare-vertex selection, and inner
source-vertex/live-flag cleanup as Windows.

Raw ARM disassembly also closes the return contract: the empty path returns
with `r0` still holding `this`, while the populated path returns with `r0`
holding the last compared signed short. Those incompatible residues cannot be
one authored result. The sole Windows caller also ignores EAX, and the natural
void scratch remains exactly 33/33 instructions with no masked operands.

## 2026-07-29 primary cRDuplicateVertices ownership

The matcher now emits the exact Windows body as
`cRDuplicateVertices::Clean(int)`, while the analyzer-facing
`DuplicateVertices` name remains a compatibility alias. Binary Ninja confirms
the only Windows caller borrows the same `DirectXLoader +0x5e08` subobject and
passes the animation keyframe count. The ownership change preserves all 33/33
instructions with no masked operands.
