# ObjectProcLandScapeUpdate

`0x41a360` is the authored free function
`ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool)` from
`ObjectProc.o`, retained by Android and iOS. It samples retained TGA pixels,
averages RGB, optionally cubes the value, and writes scaled vertex heights for
`cRFace::AI`.

- VC6 symbol: `?ObjectProcLandScapeUpdate@@YAXPAUcRObject@@MMPAUcRTexture@@_N@Z`
- semantic-complete Windows result: 97.25%, 109 candidate / 109 target instructions
- exact prefix: 67/109 instructions
- masked operands: 13/13 audited
- residual: pixel-pointer base encoding; no semantic gap known
- live caller: `cRFace::AI`

## 2026-09-22 coordinate and average ownership

The [replayable recovery](../../heightmap-coordinates-20260922.md) supersedes
the earlier row-index scheduling boundary. A local integer coordinate pair
keeps the converted column value alive across row-address formation, recovering
the native saved registers, 109-instruction count and row/column order. Starting
the running average directly from red then restores the cubic-test position.
The pair is a source reconstruction; its original spelling is not known.

The retained result is **97.25%**, prefix **67/109**, with **13/13** positional
references and all five local branches exact. Only the seven-instruction
region `[233,254)` differs: the candidate pixel pointer includes the 18-byte
TGA header displacement, while native keeps that displacement in the red/blue
loads. A separate affine-address and register-liveness check proves equivalent
reads and ordered writes there, but does not award encoded-match credit.

All 72 controls were recompiled. Removing the coordinate pair restores the
60.36% inside-row form; moving its row base outside restores 79.26%. Reordering
the pair fields or changing their scope preserves the 96.33% intermediate
metrics. Header-base, channel-owner and complete-average alternatives do not
close the encoded residual. These are bounded controls, not source exhaustion.

The [pointer-origin follow-up](../../heightmap-address-20260922.md) preserves
53 controls under this recovered coordinate lifetime. The C2 observations
show that header-base addressing selects a destructive addition before
scheduling, while payload-base addressing keeps a separate LEA result. Both
retain the pointer assignment; no tested sampling helper, channel cursor or
address record recovers native's unbiased LEA. All controls and both traces
were replayed. The canonical 97.25% source is unchanged.

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

## 2026-09-05 pixel sampling operation

Eight `whole-pixel-sample-operation-20260905-mutations.json` forms separate
pixel address lookup or complete grayscale sampling, borrowing the row value
by value/reference. Passing the existing row base is neutral at 79.26%;
passing the converted row coordinate and deriving the base inside the operation
reproduces 60.36%. All thirteen references remain clean. No helper is retained.
The native saved row coordinate and green-before-red load schedule remain
unrecovered; these results do not establish a compiler limitation.


## 2026-09-07 five-function campaign evidence

Sixty-three row-base, RGB-value, pixel-pointer, and output-vertex lifetime
combinations do not improve 79.26%. Moving row formation after X conversion
changes broader allocation instead of recovering the complete native loop.
No source or image layout change is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.

## 2026-09-07 continuation: row conversion and loop formation

Seventeen paired probes vary the converted row's scope, for/while/guarded-do
outer traversal, and placement of the width-scaled row term. They preserve
float bounds and row-before-column conversion. The best forms are byte-neutral
at 79.26%, 108/109 instructions, prefix 37, with all 13 references clean.
Deferred row arithmetic still changes broader allocation; no source change is
retained. These receipts bound the tested combinations only.
