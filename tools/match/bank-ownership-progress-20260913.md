# Dump and LooptheloopW: smaller, audited residuals

Both builders improve substantially, but **neither is a new full match**.
The independent byte comparison leaves exactly 12 unequal body bytes in each.
The work began on September 13 and was validated on September 14, 2026.

| Builder | Before | Retained | Candidate/native instructions | Strict positional references |
| --- | ---: | ---: | ---: | ---: |
| Dump | 95.57650471% | 99.71014493% | 689 to 690/690 | 43 |
| LooptheloopW | 92.71255061% | 99.19463087% | 737 to 745/745 | 55 |

The [receipt](bank-ownership-progress-20260913.json) preserves 240 compiling,
reconstructible controls: 133 Dump, 95 LooptheloopW and 12 TurnoverDouble.
It includes baseline and retained native captures, independent byte audits,
forward/reverse probes, build inputs and a preserving Dump compiler trace.
Two compiler-rejected generated alternatives are recorded separately. Controls
are diagnostic observations, not a claim that the source search is exhausted.

## Source changes and intermediate results

Dump borrows its secondary pointer field across sample initialization. This
initially **regresses** the score to 93.41057205%, while recovering the native
primary-matrix receiver sequences in the departure and curve phases. Keeping
that stage, writing the approach X coordinate before converting its Z index
recovers the primary-position schedule. Reading the ordinary mesh sample
directly from the bank, instead of retaining a sample pointer, then recovers
the mesh. The temporary position helper can be inlined without changing the
result; the retained source contains that simpler inline form.

LooptheloopW borrows both sample pointer fields across geometry, delta and
mesh processing. This recovers eight instructions and advances the normalized
prefix from 118 to 335 instructions. Its mesh operation consumes the real
width, count, mesh and primary-bank references. This recovers the face-index
multiply's operand order. The texture parity branches use the even-first form
seen in solved siblings; their two arms retain identical texture calls.
Keeping the double lateral coordinate within each vertex branch recovers the
vertex-buffer stack home, leaving only the two integer-conversion homes
exchanged. All helper parameters are consumed.

The borrows refer to pointer **fields**, not snapshots of their current values.
They retain the original reads around allocation, matrix and vector calls.
No shared layout, call contract, compiler flag, extent or matcher rule changes.

## Remaining encoded bytes

Dump's native extent is `[0x41da30, 0x41e440)`: 2,563 body bytes and 13 bytes
of terminal padding. Its remaining differences are all in the approach loop:

- Offsets 230–238: the primary Z store and secondary `Identity()` receiver
  have different instruction ordering and address materialization.
- Offsets 263, 270 and 281: three ordinary scale-one SIB bytes in the secondary
  position stores. Normalized instruction text does not expose these bytes.

LooptheloopW's native extent is `[0x41bb40, 0x41c5f0)`: 2,725 body bytes and
11 bytes of terminal padding. Its remaining differences are:

- Offsets 835 and 859: interpolation source/store SIB bytes.
- Offsets 1317–1320: the secondary rotation argument push and bank load swap.
- Offsets 1830, 1834, 1844, 1848, 2099 and 2103: the mesh column and width
  conversion slots swap between `esp+0x74` and `esp+0x78`.

Every other body byte agrees after masking only independently verified COFF
relocation fields at identical positions. All candidate body relocations are
consumed. The 27 Dump and 28 LooptheloopW local branches have literal matching
encodings and valid instruction-boundary destinations; branch displacements
and ordinary address bytes are not masked. Padding is accounted for separately
and never used to shorten a residual away.

## Compiler evidence and bounded negatives

The Dump near-stage trace preserves whole COFF output across normal compile,
capture, replay and observation, apart from timestamps. At `C2+0x281cd`, the
approach offset has packed cost `0x1db00`, above both bank operands
(`0x10007` primary and `0x12007` secondary). The named departure offset instead
has cost `0x101e0`, between the banks. This exposes a concrete operand-ordering
boundary; it does not authorize altering compiler costs or certify exactness.

The controls retain unsuccessful bank scopes, logical/physical loop owners,
position and orientation operations, mesh input ownership, vector construction
and scalar lifetimes. Compiling each builder beside its actual adjacent sibling,
in either order, is neutral. Descriptive local renaming is also neutral.
TurnoverDouble's logical-offset stage remains partial under all six tested
value/reference integer forms; its canonical source is unchanged.

The forward probes report no tradeoffs, and the reverse probes reproduce both
original code hashes. Repository-wide checks and public-report validation are
recorded in the receipt. Full-match counts remain unchanged.
