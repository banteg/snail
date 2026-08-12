# initialize_wibble_path_template_pair

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

Ownership reconstruction for `initialize_wibble_path_template_pair @ 0x4289a0`.

Captures the fixed 32-sample wibble template: endpoint samples, sinusoidal
interior up-vector wobble, secondary sample offset, delta recomputation,
generated strip mesh, and finalization.

Current focused result: 62.82% (605/608 candidate/target instructions), with
39 masked operands ok, 0 unresolved, and 0 mismatched. The native `0x54` stack
frame is exact. The remaining mismatch is source-shape/codegen debt in the
interior value schedule, delta owner allocation, and shared mesh tail. No dummy
symbols, inline assembly, flag changes, or volatile/register games were
introduced.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.41% (115/608
candidate/target instructions) to 22.54% (510/608), with masked operands
improving from 7 ok, 0 unresolved, 8 mismatch to 20 ok, 0 unresolved, 4
mismatch.

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 22.54% (510/608) to 22.70% (502/608), with masked
operands unchanged at 20 ok, 0 unresolved, 4 mismatch.

2026-07-03 retained interior-X cleanup: the native interior loop stores the
interpolated lateral value in `center_x` but leaves transform `position.x` at
0.0f. Spelling that through the sample initializer moves focused Wibo from
22.70% (502/608) to 22.72% (501/608), with masked operands unchanged at 20 ok,
0 unresolved, 4 mismatch.

2026-07-03 retained roll schedule cleanup: recomputing
`sine(roll_phase) * 0.30000001f` separately for the cosine and sine basis-up
components, with `roll_phase` materialized before sample initialization but the
outer roll calls after it, moves focused Wibo from 22.72% (501/608) to 24.46%
(504/608), clearing the masked audit from 20 ok, 0 unresolved, 4 mismatch to
27 ok, 0 unresolved, 0 mismatch. Rejected/lesser splits were: folded roll
schedule after init at 23.86% with one mismatch, split turn phase before init at
23.84% with one mismatch, and roll calls after init at 23.92% with one
mismatch.

2026-07-04 retained mesh-face loop cleanup: replacing the direct two-face
`a`/`b` writes with the shared two-iteration `face_index` loop and single
`uv[3].v` tail store moves focused Wibo from 24.46% (504/608) to 29.95%
(514/608), with masked operands improving from 27 ok, 0 unresolved,
0 mismatch to 29 ok, 0 unresolved, 0 mismatch.

2026-07-13 terminal ownership: replacing the helper's `primary_last` and
`secondary_last` aliases with direct count-relative stores through the two
`Path` sample arrays moves focused Wibo from 29.95% (514/608) to 31.86%
(522/608), while the masked audit remains clean at 29 ok, 0 unresolved,
0 mismatch. Expanding the preceding delta loop into the method regressed the
score to 30.84% (527/608) and introduced one masked call mismatch, so `wibble`
retains local loop pointers and only the terminal stores carry direct owner
shape.

2026-07-13 lane ownership: the native interior loop copies exactly the
0x40-byte `TransformMatrix` from each primary sample to its secondary peer;
the scalar fields at offsets `+0x90..+0xa0` remain primary-owned. Removing the
five scratch-only scalar copies moves focused Wibo from 31.86% (522/608) to
35.27% (492/608), with the masked audit still clean at 29 ok, 0 unresolved,
0 mismatch. Recovering the independently initialized primary and secondary
endpoint transforms and their `delta_length = 1.0f` stores moves it further to
36.48% (483/608), with 27 ok, 0 unresolved, 0 mismatch.

2026-07-13 interior orientation ownership: after constructing each primary
sample's up vector, the native loop derives `basis_forward` from the current
position minus the previous primary position, normalizes it, and derives
`basis_right` as `basis_up` cross `basis_forward` before copying the transform
to the secondary lane. Restoring that chain moves focused Wibo from 36.48%
(483/608) to 37.50% (512/608), with the masked audit still clean at 28 ok,
0 unresolved, 0 mismatch.

2026-07-15 sample ownership cascade: expanding the endpoint and interior
sample initializer calls into their directly owned `PathSample` stores recovers
the native endpoint scalar/identity sequence and the split interior
`sample_index`/`local_index` traversal. The interpolated center remains sample
metadata while transform X stays zero, and only the 0x40-byte transform is
copied into the secondary lane before its basis-up offset. Materializing
`roll_phase` before those sample stores preserves the already-evidenced native
trigonometric schedule; leaving it after the stores scored 55.16% but introduced
a `3.0f`/`0.20943952f` operand mismatch. The retained form moves focused Wibo
from 37.50% (512/608) to 55.68% (545/608), with the masked audit improving from
28 to 35 ok and remaining at 0 unresolved, 0 mismatch.

2026-07-15 face-header ownership: the mesh face initializer clears the full
16-bit `header_word`, not merely the low-byte flag view. Naming the owning field
makes that width explicit without changing the generated store.

## 2026-07-17 live constructor ABI closure

Live callsite disassembly shows the six stack arguments in order: `6.0f`, width
`8`, mode `1`, two surface textures, and the vertical texture. The native tail
at `0x429235` is `retn 0x18`, correcting the stale `ret 0x1c` scratch banner,
and the portable iOS symbol independently preserves
`cRPath::BuildWibble(float, int, bool, char*, char*)`.

Guarded recreation and post-write readback now expose the complete seven-
parameter `Path*` prototype with no pending operation. The refreshed caller
uses `path_pairs[0x28].primary` with all six stack operands, and the callee now
ends in void finalizer flow. This is analysis-only: focused matching remains
55.68% (545/608) with 35 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves ten complete live owners: the primary seed,
up/right vectors, secondary position, both terminal deltas, mesh sample and
vertex, and both face records. Their accesses now render through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`. The constructor retains its
16 existing fixed-index `__offset` occurrences for samples 30/31, but the
replay adds none. Focused matching remains 55.68% (545/608) with 35 clean
masked operands.

## 2026-07-26 mesh ownership

Raw native assembly at `0x428f0b..0x428fdb` proves that the vertex-column loop
owns branch-local aggregate positions. Ordinary rows materialize a generated
position from the current primary sample. The terminal row keeps the current
sample cursor, addresses its previous sample, materializes a separate lateral
offset, adds the terminal `+1.0f` Z extension, and then writes the generated
position to the mesh vertex.

That vertex ownership alone moves the candidate from 545 to 563 of 608 target
instructions and grows its frame from `0x30` to `0x3c` against the native
`0x54`. The temporary focused score falls from 55.68% to 54.14% because the
larger frame reschedules the remaining face tail; the source-proven aggregate
owners are retained.

Native `0x42908e..0x429202` and the guarded lifetime replay independently prove
two distinct complete `ObjectFaceQuad*` owners, indexed as
`face_index + 2 * (row * width_cells + column)`. Each branch owns its full
header, vertices, texture reference, and UV record, including redundant parity
arms that select the same branch texture. Recovering those records resolves the
tail rescheduling: focused matching reaches 58.72% (591/608), with 35 clean
masked operands and no unresolved or mismatched masks.

## 2026-07-26 complete mesh-vector ownership

The Turnover-family closure exposes two vector owners still collapsed by the
initial Wibble mesh rewrite. Native `0x428f0d..0x428fdb` first materializes a
lateral-offset vector in the ordinary branch before its generated position.
The terminal branch separately owns an endpoint vector derived from the
previous sample with its Z lane extended by `1.0f`.

Recovering both owners raises focused matching from 58.72% (591/608) to 60.73%
(604/608), improves the masked audit from 35 to 36 clean operands with no
unresolved or mismatched masks, and recovers the exact native `0x54` frame.
The exact prefix expands from zero to 85 instructions. The candidate is now
only four instructions shorter than the target.

## 2026-07-27 paired mobile boolean ownership

The exact Android and iOS symbols both name
`cRPath::BuildWibble(float, int, bool, char*, char*)`, proving that the third
authored scalar is `bool side_exit`. Both mobile bodies end after sample/delta
construction and `CalcLengthZ`; Windows retains its sixth stack argument for
the vertical texture and builds the strip mesh locally. Refining the source,
shared headers, and analysis prototypes is ABI- and byte-neutral: focused
matching remains 60.73% (604/608), with an 85-instruction prefix and 39 clean
masked operands.

The mobile body also exposes the base-phase spelling
`t * 6.2831855f / 30.0f`. VC6 compiles that spelling identically to the
retained `t * 0.20943952f`. Collapsing the distinct turn and roll phase owners,
however, changes the stack schedule and regresses focused agreement to 59.24%.
That probe is rejected; mobile evidence closes the boolean owner without
overriding the independently measured Windows lifetime shape.

## 2026-07-28 paired mobile control ownership

The exact Android and iOS `BuildWibble` bodies independently preserve the
authored fixed topology: endpoints 0 and 31, 30 interior samples, a logical
interior index starting at zero, and a separate `0xa8`-stride sample cursor.
They also preserve distinct base and three-times roll phases. Windows MLIL/SSA
at `0x428b29..0x428ce2` is authoritative for the native definitions and proves
that the one source index was fragmented across register and stack homes.

A guarded split transaction now reunifies that source owner as
`interior_index`, keeps `interior_sample_offset` as an honest integer byte
cursor, and recovers the separate `base_phase` and `roll_phase` lifetimes.
Windows `0x428d13..0x428dda` likewise proves independent `delta_index` and
`delta_sample_offset` owners. Preview, application, live readback, and an
idempotent replay all pass; the constructor retains its existing 16 fixed-index
`__offset` occurrences and gains none.

This is analysis-only. Focused matching remains **60.73%** (604/608), with an
85-instruction prefix and 39 clean masked operands. Strict paired Binary Ninja
and IDA 9.4 export reports zero selector mismatches.

## 2026-07-30 value ownership and bounded mesh schedules

The retained Windows baseline began at **60.73%** (604/608 candidate/target
instructions), with an 85-instruction exact prefix, the exact native `0x54`
frame, and 39 clean masked references. The exact Android and iOS bodies, the
Windows MLIL replay, and the independently improved LoopBow sibling all support
an authored vector value for the secondary basis-up offset. Replacing the three
direct component products with
`primary_samples[sample_index].transform.basis_up * 0.49000001f`, borrowing the
secondary position, and advancing `sample_index` before the three additions
moves focused agreement to **62.59%** (603/608). The early index advance is
byte-neutral but matches the native ownership schedule.

The paired delta-subtraction sweep then proves a non-local compiler interaction:
authoring `operator-` for either lane alone is worse, while authoring it for
both primary and secondary deltas raises the retained result to **62.82%**
(605/608). The exact prefix remains 85 instructions, the frame remains `0x54`,
and all 39 masked references remain clean.

Seven recorded mutation sweeps cover 31 unique variants with no repeats or
errors: 7 better, 16 byte-identical, and 8 worse. The bounded negative and
neutral results are:

- six interior-counter declaration/initializer forms are byte-identical;
- moving `roll_phase` later scores 59.74% or 59.24%;
- named aggregate basis-up forms are byte-identical, while direct component
  stores extend the prefix to 96 instructions but fall to 55.84%;
- a persistent named basis-up value scores 57.52% and is rejected;
- all three guarded/do-while delta schedules are byte-identical;
- facequad/vertex/object acquisition order is byte-identical.

The Windows mesh dumps also bound the tempting sibling-shaped rewrites. A
branch-local vertex destination alone scores 60.25% (607/608). A guarded
row/column `do/while` with the native `0xa8` sample induction and the retained
shared destination is byte-identical at 62.82%. Replaying the complete
LoopBow-shaped terminal-first, branch-local vertex loop falls to 59.64%
(616/608). The native-shaped face schedule grows the prefix from 85 to 103 but
falls to 61.54% (601/608); isolated row initialization and loop-scoped face
counter forms are byte-identical, while explicitly splitting the decompiler's
SSA face selector/completion values falls to 62.21% (604/608). These results
show that Wibble's best VC6 shape keeps the compact shared vertex destination
and single authored face counter even though later analysis views split their
SSA values.

## 2026-07-30 ordinary-first mesh and asymmetric delta owners

Invert and both Twister targets exposed one dependency that the earlier Wibble
mesh tests did not cover: guarded row/column `do` loops, a separate `0xa8`
sample cursor, ordinary-row-first control, and branch-local sample and vertex
destinations must move as one unit. Replaying that complete shape raises
focused agreement from 62.82% to 66.12% (+73 weighted bytes), preserves the
85-instruction exact prefix and all 39 clean references, and grows the
candidate from 605 to 614 instructions against 608 native. The much weaker
terminal-first result is therefore a branch-order interaction, not evidence
against branch-local ownership.

The interior primary forward direction has the same authored `Vector3`
subtraction owner recovered independently in Invert and both Twisters.
Replacing its component constructor with `operator-` adds four weighted bytes
without changing instruction count, prefix, or references, reaching 66.28%.

The delta helper then proves a Wibble-specific asymmetric allocation. Direct
secondary-array ownership raises agreement by another 45 weighted bytes to
**68.30%** (`616/608`, prefix 85, 39 clean references). Primary-only direct
ownership loses six bytes, while moving both lanes directly loses 106. Five
additional primary lifetime forms close the boundary: scoped pointers,
references, and a current-pointer/next-array mix are byte-identical; direct
current-array and position-reference forms lose 150 weighted bytes.

The native face schedule was retested after the row allocation changed. It now
extends the prefix to 103 instructions but still loses 28 weighted bytes,
scoring 65.02%, so it remains rejected. Five new sweeps add eleven variants;
the complete ledger now contains 42 variants across twelve sweeps
(`10 better / 19 identical / 13 worse`). Remaining early drift is concentrated
in the interior sample allocation rather than row induction, vector
subtraction, or delta ownership.

## 2026-07-30 current secondary-offset boundary

The secondary basis-up offset was retested after the ordinary-first mesh and
asymmetric delta-owner changes materially altered allocation. The retained
named vector and two `operator+=` spellings compile byte-identically at
**68.30%** (`616/608`, prefix 85, 39 clean references). Borrowed component
stores fall to 67.21%, a destination pointer followed by direct components
falls to 66.83%, and direct array components fall to 58.61%.

This closes the earlier direct-component lead: it does not survive the current
dependency state, while the cross-port-backed vector owner remains the best
Windows spelling. The ledger now contains 47 unique variants across thirteen
sweeps. No source change is retained.

## 2026-07-30 mesh arithmetic ownership

The exhaustive Twister arithmetic plan was replayed against Wibble's recovered
ordinary-first row schedule. Unlike the paired Twisters, Wibble benefits from
a `double` lateral local, both `Vector3::operator*` scales, and the terminal
`Vector3::operator+` add. Together they add 44.86 weighted bytes.

Both terminal add operand orders compile identically; the position-first form
is retained to match the independently recovered constructor family. Either
ordinary add order is neutral in every winning combination. Focused matching
rises from **68.30%** to **70.33%**, candidate instructions move from 616 to
612 against 608 target instructions, prefix stays 85/608, and all 39
references remain clean.

## 2026-07-30 interior schedule boundary

Native `0x428b29..0x428d0a` keeps distinct zero-based index and `0xa8`-byte
sample-cursor owners. It stores the base phase before sample initialization,
multiplies that stored phase by three after the position stores, and terminates
the loop through the advanced byte cursor.

Those facts do not identify a better current VC6 source shape. Retesting all
four prior roll-phase placements after the mesh and delta changes loses
22..36 weighted bytes. Six equivalent backedge spellings show that deriving
the test from `sample_index * sizeof(PathTemplateSample)` extends the exact
prefix from 85 to 97 instructions, but loses 39 weighted bytes overall.
Coupling that byte-derived backedge with the native phase placement loses
75 weighted bytes and scores 66.94%, so the two individually plausible
tradeoffs do not complete one another.

Finally, named mutable, const, and aggregate basis-Z owners are all
byte-identical to the retained literal zero. The current 70.33% spelling is
therefore retained, and this three-sweep non-improvement boundary closes the
interior phase, termination, and zero-owner neighborhood without register or
volatile forcing.

## 2026-07-31 direct face-offset record ownership

Using the common face offset directly for every facequad field raises focused
matching from **70.33%** to **74.14%**. Candidate size moves from 612 to 606
instructions against the 608-instruction target, prefix remains 85/608, and
all 39 references remain clean. This is a complete record-ownership change;
the surrounding row, parity, and texture control remains untouched.

## 2026-07-31 post-face ordinary position ownership

The ordinary `Vector3::operator+` was byte-neutral in every winning
pre-face arithmetic combination, but direct record ownership changed that
allocation. Replaying it now adds **3.65 weighted bytes** and raises Wibble
from **74.14% to 74.30%**. Candidate/target size remains 606/608, prefix stays
85/608, and all 39 references remain clean. The recorded reverse probe
reproduces the 74.14% predecessor.

The retained source keeps the already proven double lateral owner, both scale
operators, and terminal addition. Only the previously neutral ordinary
addition changes in the post-face dependency context.
