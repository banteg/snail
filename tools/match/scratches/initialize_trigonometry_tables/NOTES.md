# RMathInit @ 0x44c930

Exact match: 100.00%, 18/18 instructions.

Builds the shared Cos and Sin lookup tables, then resets the companion
gameplay random table. The angle scale is kept as two `float` multiplies so VC6
emits the native two `fmul dword` sequence before `fcos`/`fsin`.

The init loop increments the table index before storing, so VC6 relocates the
writes against one-float-before bases at `data_777f38` and `data_77ff88`. The
lookup helpers still read the canonical table starts at `data_777f3c` and
`data_77ff8c`.

## 2026-07-27 authored RMathInit boundary

Android and iOS export this startup phase as void `RMathInit()`. All three
ports build the Sin/Cos lookup banks and then initialize the gameplay
random table. Windows uses 0x2000 entries and calls its separate
`gRMathRand2Init()` implementation; mobile uses 0x8000 entries and also
constructs platform color defaults. Those platform-specific extents and the
mobile-only color tail are not transferred.

The sole Windows caller discards EAX. Restoring the void outer and inner
initializer contracts remains byte-identical: this body is 18/18 instructions
with five clean operands, and `gRMathRand2Init` is 10/10 with four clean
operands.

## 2026-09-08 canonical array ownership

The retained zero-based for-loop names the actual arrays directly and remains
18/18 with five clean references. VC6 schedules the increment before the stores
and emits the native -4 relocation addends itself. Separate biased-array externs
are no longer needed. The manifest retains those old names as historical offset
identities and records the verified extents/prebase displacement on the owners.

The resulting arrays also link and run with the exact lookup/random helpers.
See [the storage and executable report](../../rmath-storage-and-runtime-20260908.md)
for the native bounds, rejected two-index rewrite, and runtime controls.
