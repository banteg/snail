# Complete distorted vertex body match

`cRDistort::Build` (`apply_distort_to_object`, `0x41aa50`) now matches its entire
**648-byte native body** with `msvc6.5 /O2 /G5 /W3`. Its 197 normalized instructions
and 26 positional references already matched; this closes nine ordinary SIB
encoding differences without changing the normalized coverage total.

The source borrows the live `copied_vertices` member after selecting the input
vertex bank. The wave and squash passes use that destination binding. The final
XYZ scaling pass uses its own local destination binding. Each access still reads
the current member; neither reference snapshots a bank pointer across `Sin` or a
vertex write. The native component calculations, stores, and phase ordering are
preserved.

The two source changes are independently necessary in this compilation context:

| Control | Unequal body byte offsets |
|---|---|
| Original source | 188, 272, 282, 421, 443, 453, 584, 598, 612 |
| Reverse the shared destination binding | 188, 272, 282, 421, 443, 453 |
| Reverse the final scaling binding | 584, 598, 612 |
| Both bindings retained, const or mutable references | None |

Only those nine raw candidate bytes change, and all nine become the literal
native bytes. The [replayable receipt](distort-live-vertex-banks-20260913.json)
contains 16 source reconstructions, fresh native measurements, full byte and
instruction records, an independent audit, and matching forward/reverse probes.
The controls also include phase-local bindings, input-bank borrowing, physical
cursors, scalar references, and a scaling helper. Their unpromoted outcomes remain
explicit. The source-level lifetime effect is reproducible; the precise VC6
optimizer mechanism remains unproven.

The independent audit checks every reference identity at the same instruction
index and byte offset, consumes all body relocations, and compares every other
encoded byte. All 18 local branches match literally and target verified
instruction boundaries. Eight terminal padding bytes are excluded from the
656-byte native extent; no body bytes remain unexplained. This is a native
function-body proof, not linked-image or runtime validation.

All 785 scratch checks, 1,140 tests, strict experiment/spec checks, extern lint,
retained and baseline receipt replays, and exact-reference auditing pass. The
public report is refreshed from native compilation; only this function gains
encoded-body exactness.
