# ObjectProcLandScapeUpdate

`0x41a360` is the authored free function
`ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool)` from
`ObjectProc.o`, retained by Android and iOS. It samples retained TGA pixels,
averages RGB, optionally cubes the value, and writes scaled vertex heights for
`cRFace::AI`.

- VC6 symbol: `?ObjectProcLandScapeUpdate@@YAXPAUcRObject@@MMPAUcRTexture@@_N@Z`
- semantic-complete Windows result: 79.26%, 108 candidate / 109 target instructions
- exact prefix: 37/109 instructions
- masked operands: 13/13 audited
- residual: compiler-shaped row-index and RGB scheduling; no semantic gap known
- live caller: `cRFace::AI`

## 2026-08-13 row ownership recovery

The former 60.36% candidate left the bottom-up row expression inside the
column loop and trusted VC6 to recover its ownership. Native evidence is more
specific: the row coordinate is converted once after the inner-loop guard,
while the output vertex cursor persists in `ebp` across both loops. Android
also owns the bottom-up width-scaled row base outside its column loop; iOS
independently owns the converted row coordinate there.

Making that row base explicit recovers the native 8-byte frame and persistent
`ebp` vertex cursor, reduces the candidate from 113 to 108 instructions, raises
the score to 76.50%, and advances the exact prefix from 0 to 37 instructions.
Spelling the inner traversal as its native prechecked `do` loop then raises the
score to **79.26%** without changing the instruction count, references, or
behavior. Both retained changes are ordinary source ownership/control flow,
not register hints or synthetic dependencies.

The remaining region is bounded. Moving only `y` outside the loop, delaying or
repeating the row-base calculation, staging the arithmetic, changing signed
offset types, reordering or regrouping RGB conversions, and indexing from the
TGA header base all compile either to the old 60.36% allocation, the same
79.26% body, or a regression. Windows schedules the width-scaled row term
after the column conversion and loads green before red; the best natural VC6
source still hoists that term and chooses the opposite transient register
schedule. Those are retained as an honest compiler/source-shape residual.

## 2026-09-05 whole pixel/row lifetime probes

Fourteen combinations of RGB expression ownership and bottom-up row arithmetic
placement do not improve 79.26%. Separate byte/int components, one expression,
and an image-base pixel view all regress; moving the row term inside the loop
also changes the saved-register/frame shape. Canonical source is unchanged.
These results bound the tested source shapes, not the remaining investigation.
