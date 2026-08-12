# `initialize_dip_path_template_pair` starter

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

This is an honest semantic starter for the path-template initializer at
`0x41e440`.

It models the compact dip template: first and last flat samples, a cosine-based
downward middle section, adjacent-sample orientation, delta vectors, strip mesh
vertices/faces, and finalization.

This is a starter partial. The unusual native layout around endpoint samples and
VC6 x87 scheduling remains open.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments and
the native tail is `ret 0x18`. Updating the scratch and shared declaration from
the stale four-argument prototype moves focused Wibo from 30.02% (564/655) to
30.19% (564/655), with masked operands unchanged at 30 ok, 0 unresolved, 1
mismatch.

2026-07-03 prologue scheduling cleanup: native begins the `curve_source * 5.0f`
x87 multiply at entry, writes the dip header fields, then performs the integer
curve-count conversion before `width_or_scale` and `segment_count`. The scratch
now preserves that order. Focused Wibo remains 30.19% (564/655), with masked
operands unchanged at 30 ok, 0 unresolved, 1 mismatch, so this is retained as
source-shape documentation rather than a score win.

2026-07-04 middle initializer expansion rejection: expanding the curved middle
sample initializer into direct primary/secondary writes regressed focused Wibo
from 30.19% (564/655) to 23.50% (579/655). The masked audit also dropped from
30 ok, 0 unresolved, 1 mismatch to 28 ok, 0 unresolved, 1 mismatch, with the
remaining call mismatch still pairing native `cosine` against matrix identity
setup. The scratch keeps the shared `initialize_sample_pair` spelling for the
middle loop until the surrounding endpoint/local lifetime is isolated.

2026-07-15 ownership recovery: the endpoint index is now retained as
`curve_count + 1`, both endpoint sample pairs are initialized through their
owned fields, and the curved middle uses the native explicit sample-byte cursor
and `do/while` lifetime. The middle initializer increments its logical index
between matrix identity and Y/Z placement, then orients the preceding pair.
Together these target-backed changes raise focused Wibo from 30.19% (564/655)
to 33.41% (596/655), while recovering 25 clean masked operands and reducing the
temporary four call mismatches back to the single pre-existing alignment
mismatch.

2026-07-15 mesh ownership recovery: the native acquires `facequads` before
`vertices`, retains an aggregate `Vector3` for ordinary rows, uses a
face-column `do/while`, and contains explicit parity branches even though both
arms currently request the same texture. Preserving those source facts raises
focused Wibo from 33.41% (596/655) to 34.74% (600/655), with 25 clean masked
operands and one mismatch. The remaining audit issue pairs the native first mesh
allocation call with the candidate's second call because the still-shorter
sample-orientation region shifts structural alignment; it is kept visible
rather than hidden with a dummy relocation or reordered behavior.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildDip(float, int, bool, char*, char*)`, and the
Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale five-parameter view had shifted the first texture onto the mode
slot, retained a user-authored `char*` at stack `+0x14`, and omitted `+0x18`.
The guarded recreation now owns the exact `Path*` receiver and six stack
arguments through `cap_texture`; direct readback confirms storages `+4..+24`.
This is analysis-only: focused Wibo remains 34.74% (600/655), with 26 clean
masked operands and no unresolved or mismatched operands.

## 2026-07-20 path-lifetime ownership replay

Live Binary Ninja inspection recovers nine complete owners from the remaining
body: primary and secondary basis-right vectors, both terminal deltas, the
primary mesh sample, ordinary and terminal vertices, and the two simultaneous
facequad records. The replay verifies canonical `Vec3`,
`PathTemplateSample`, and `ObjectFaceQuad` layouts before applying their exact
register-variable IDs.

Two tempting forward-vector addresses were rejected. Although each points at a
real preceding-sample member, typing the byte-biased lifetimes introduced eight
backward `__offset` expressions in adjacent position reads. The retained set
previews and exports with zero offsets. No scratch source changed, preserving
the honest 34.74% focused match and 26 clean masked operands.

## 2026-07-26 coupled mesh ownership

Raw instructions at `0x41ea51..0x41eb28` prove distinct ordinary and terminal
mesh owners. The ordinary branch first materializes a lateral-offset vector,
then a generated-position vector, and only then its destination vertex. The
terminal branch separately owns its lateral offset, raised endpoint, generated
position, and terminal destination vertex. Dip's native acquisition order
remains intentionally distinct from Hump and Dump: `facequads` precedes
`vertices`.

The face loop simultaneously proves independent records at `0x41ebf8` and
`0x41ecab`. Each branch owns its face pointer and header word, preserves the
redundant parity-selected texture call, and writes all four UV pairs. Replaying
the complete dependent owner set produces:

```text
match: 38.95%
target: 655 insns, candidate: 644 insns
prefix: 8/655 target insns
masked operands: 30 ok, 0 unresolved, 0 mismatch
```

This raises the focused result by 4.21 points, recovers 44 candidate
instructions and four clean operands, and gives the candidate the exact native
`0x50` frame. The remaining broad alignment drift begins in the earlier sample
construction/orientation region rather than this mesh tail.

## 2026-07-26 Dip count and cursor ownership

Windows raw assembly, IDA Professional 9.4, and the optimized ARM sibling
inspected with Ghidra 12.1.2 agree on the two early aliases. The dead
`width_cells_` argument owns the integer curve count after conversion, while
the consumed `curve_source` argument owns the derived dip radius. IDA also
shows the input stack slots being reused for exactly those values. Keeping
either rewrite in isolation was not sufficient; the coupled aliases raise the
focused result from 38.95% to 39.88%.

The curved middle keeps its current primary and secondary samples owned by
their member arrays and a `0xa8` byte cursor across the identity and cosine
calls. Hoisting those current samples into pointer locals was the main source
of drift. Leaving the array expressions explicit raises the focused result to
50.08%. The preceding samples are different owners: removing their two
explicit pointers regressed the result to 46.13%, so they remain local aliases.

The endpoint and strip-mesh passes likewise expose distinct byte cursors, and
the face loop computes one common record index before selecting one of two
branch-local `ObjectFaceQuad` records. A single face pointer shortened the
candidate by another ten instructions and contradicted the two native
materializations at `0x41ebf8` and `0x41ecab`, so it was rejected despite a
higher scalar score. The retained ownership model produces:

```text
match: 48.89%
target: 655 insns, candidate: 646 insns
prefix: 20/655 target insns
masked operands: 31 ok, 0 unresolved, 0 mismatch
```

This final scalar is lower than the transient current-sample-only result
because the common face index changes global register allocation, but it
extends the exact prefix from 8 to 20 instructions and preserves every audited
relocation. Branch-scoped preceding-sample pointers, a shared face pointer,
explicit delta cursors, direct orientation expansion, and statement-order-only
micro-adjustments were all measured and rejected. No dummy calls, dead
relocations, or equal-arm texture rewrites were introduced.

## 2026-07-27 paired-mobile boolean ABI

The exact Android and iOS `cRPath::BuildDip(float, int, bool, char*, char*)`
symbols prove that the third input is a boolean. Both mobile bodies stop after
building the sample/delta data and calling `CalcLengthZ`; the Windows-only
tail adds the cap texture and builds the mesh locally, so that boundary does
not justify transplanting mobile source statements. The Binary Ninja type
change was previewed, applied, read back, and followed by lifetime replay with
all recovered owners still current.

The focused Windows build remains honestly neutral at **48.89%**, **646/655**
candidate instructions, a 20-instruction exact prefix, and a clean masked
audit with 37 accepted operands. No source expression changed.

The same paired body also corrects the shared enum identity. Windows writes
kind `0x14` and both mobile siblings write their platform-specific Dip kind
`0x18`; the stale Windows label `CAGE2` was inherited from the function's
superseded pre-mobile name. The canonical label is now
`PATH_TEMPLATE_KIND_DIP`, with guarded Binary Ninja replay and IDA header
reimport carrying the correction without changing matcher source.

## 2026-07-28 paired-mobile control ownership

The exact Android
`analysis/decompile/android/functions/00056d14-_ZN6cRPath8BuildDipEfibPcS0_.c`
and iOS
`analysis/decompile/ios/functions/000591b8-_ZN6cRPath8BuildDipEfibPcS0_.c`
bodies independently preserve the portable control graph: a derived curve
count, the far endpoint, the cosine middle, the adjacent-sample orientation
pass, and the final delta/`CalcLengthZ` pass. Windows remains authoritative for
the exact variable definitions, `0xa8` sample-byte cursors, six-argument ABI,
and native-only cap-texture/strip-mesh tail.

A transactional Binary Ninja replay now records 14 exact Windows owners: five
direct variables plus nine merged definition clusters for the curve count and
radius, endpoint, curve phase/index/offset, and delta index/offset. The preview
changed all nine clusters, rolled them back cleanly, and produced no
`__offset` artifacts. Live readback confirms every owner is user-defined with
the expected type; an idempotency replay found all operations already current.

This is analysis-only. The scratch remains at the honest **48.89%** focused
match, **646/655** candidate instructions, a 20-instruction exact prefix, and
37 accepted masked operands. No source expression or matcher exception changed.

## 2026-07-30 authored terminal-delta subtraction

The exact Slalom-family terminal-delta block proves the paired
`Vector3::operator-` expression boundary. The exhaustive two-site sweep adds
7.35 weighted bytes and raises focused matching from 48.89% to **49.19%**.
Candidate and target counts remain 646/655, prefix remains 20/655, and all 37
references stay clean.

## 2026-07-30 orientation subtraction bound

Both shared orientation helpers were tested independently and together with
the authored `Vector3::operator-` form. All three variants are byte-identical,
leaving **49.19%**, 646/655 instructions, prefix 20/655, and all 37 references
unchanged. Dip retains the expanded component spelling.

## 2026-07-30 mesh arithmetic ownership

The native five-vector mesh block at `0x41ea51..0x41eb28` distinguishes the
ordinary sample position/right-vector pair from the terminal endpoint and
previous-sample pair. Retaining a `double` lateral local, both authored
`Vector3::operator*` scales, and the terminal `Vector3::operator+` reproduces
that ownership and adds 69.96 weighted bytes.

The ordinary position add remains byte-identical both alone and after the
scale rewrites. Split-float and volatile lateral locals regress or stay
neutral, and the full double-expression spelling adds reference debt, so none
is retained. Focused matching rises from **49.19%** to **52.12%**, candidate
instructions move from 646 to 642 against 655 target instructions, the exact
prefix remains 20/655, and all 37 references remain clean.

## 2026-07-30 header count ownership

Native `0x41e46f..0x41e491` keeps the derived far-end index in `edi`, writes
`width_or_scale` at `0x41e480`, then stores and converts the total sample count.
Placing the width write before the source declaration of `endpoint_index`
recovers that observable header schedule. It adds 3.69 weighted bytes and
extends the exact prefix without changing candidate size or relocation health:

```text
match: 52.27% (was 52.12%)
target: 655 insns, candidate: 642 insns
prefix: 22/655 target insns (was 20/655)
masked operands: 37 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The retained-baseline header grid closes seven alternate count expressions.
Restoring the endpoint declaration before the width write or introducing a
named total count returns to 52.12% and prefix 20; direct count expressions,
a separate curve count, and moving the endpoint declaration after the total
count fall to 50.12%..51.66% and shorten the prefix.

The adjacent ownership hypotheses do not resolve the next register split.
Five ways to capture, convert, or reuse the endpoint byte offset are either
byte-identical or lose 8.32 weighted bytes. References are byte-identical,
branch-local pointers lose 4.65 weighted bytes, direct preceding-sample
addresses lose 13.80, and keeping only one preceding pointer collapses the
exact prefix. An explicit persistent curve-phase owner raises the scalar score
to 52.53%, but moves the first mismatch earlier and cuts the exact prefix from
22 to 7 instructions; it is recorded as a metric tradeoff and rejected.

## 2026-07-30 endpoint register-lifetime bound

The native header retains the far-end index in `edi` through both sample-zero
initializers, retains the `1.0f` word in `ebx`, and only then turns `edi` into
the endpoint byte offset. The retained candidate instead spills the index
early and reuses `ebx` for the offset. A complete 17-variant interaction grid
combines the two strongest target-backed header owners with all five endpoint
capture/conversion forms. None improves the retained 52.27% result: two forms
remain byte-identical, three lose 8 weighted bytes alone, and their header
interactions lose 4 or 12 weighted bytes.

Four height-scale owners—direct constant, `const`, split assignment, and
`register` local—are all byte-identical, ruling out that source spelling as
the cause of the `ebx` lifetime. Member-sourced and chained total-count
conversions were also tested because native stores `segment_count` before the
x87 conversion. A named chained assignment is byte-identical; direct
member-sourced forms fall to 48.15% and add reference debt.

Finally, the explicit curve sample/phase split was used as a temporary baseline
for all five endpoint forms and all ten header forms. No interaction improves
its 52.53% scalar tradeoff or restores the lost prefix. The scratch therefore
keeps the 52.27%, 642/655-instruction, 22-prefix baseline with all 37 references
clean.

## 2026-07-31 phase and cursor ownership recovery

The earlier phase result was incomplete rather than intrinsically regressive.
Windows keeps separate logical sample and cosine-phase owners, hands the
incremented sample index back to the phase owner at `0x41e84d`, and lays out
the orientation branch as a fallthrough into the full adjacent-sample path.
The exact Android and iOS `cRPath::BuildDip` bodies independently preserve
that phase/control separation and branch-local preceding samples.

The native orientation order is byte-neutral by itself. A complete phase split
raises the retained 52.27% baseline to 52.53%, while phase plus native branch
order reaches 52.84%; both temporarily shorten the exact prefix from 22 to 7
instructions. On that dependency-complete baseline, moving the primary and
secondary preceding-sample pointers into their respective branches adds
39.71 weighted bytes, raises the focused match to **54.50%**, reduces the
candidate from 647 to 644 instructions, and restores the 22-instruction
prefix. This reverses the earlier isolated result, where the same pointer
ownership lost 4.65 weighted bytes.

The target delta pass separately carries a logical index and a `0xa8` byte
cursor. Replaying both with direct array-plus-offset expressions adds another
24.12 weighted bytes and produces:

```text
match: 55.51%
target: 655 insns, candidate: 642 insns
prefix: 22/655 target insns
masked operands: 37 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

Pointer-local and record-cursor spellings lose 236 and 259 weighted bytes,
respectively. The direct form is retained because both desktop instructions
and the paired mobile bodies support the two owners, the exact prefix is
preserved, and the reference receipt remains clean.

The new allocation closes the adjacent header, endpoint, and mesh questions.
All ten header/count forms, five endpoint-offset forms, four height-scale
forms, and three orientation-subtraction spellings are neutral or regressive.
At the mesh prologue, native keeps the facequad and vertex arrays on the stack,
the logical row in EDX, the byte cursor in EBX, and the column in EDI. Twenty-
seven acquisition/declaration interactions are byte-neutral. Reusing the
native logical row across the face pass is also neutral, while reusing the
column loses 25.80 to 29.48 weighted bytes. The mesh register-role inversion is
therefore recorded as a surrounding-allocation residual rather than forced
with volatile storage, dummy uses, or register directives.

## 2026-07-31 direct face-record indexing

Windows computes one common record index at `0x41ebe1` before selecting the two
complete winding records. Consuming that owner directly as
`facequads[face_record_index]`, rather than rebuilding branch-local pointers,
raises focused matching from **55.51%** to **63.47%** and adds 190 weighted
bytes. Candidate size moves from 642 to 640 instructions against the
655-instruction target, with all 37 references still clean.

The first mismatch moves earlier and the exact prefix contracts from 22 to 8
instructions; both tradeoffs are recorded. The direct form is retained because
it matches the native common-index dataflow, is semantically simpler, and
produces a dependency-complete face-region recovery rather than an allocator
or instruction-count trick.

## 2026-07-31 post-face sample-owner replay

Sharing the current mesh sample across the terminal branch loses 120 weighted
bytes and falls from **63.47%** to **58.46%**, while growing the candidate
from 640 to 645 instructions. Prefix remains 8/655 and all 37 references stay
clean. Dip therefore keeps the branch-local sample and preceding-sample owners
on its direct-face baseline.

## 2026-07-31 post-face count and counter ownership

The direct face-record recovery changed Dip's global allocation enough to
invalidate the earlier header and mesh-counter conclusions. Replaying those
native-backed grids on the 63.47% baseline recovers two source owners.

The converted curve count is a distinct logical value before it is copied to
the reused `width_cells_` argument slot. Windows stores that value at
`0x41e472`, and both exact mobile bodies independently retain their integer
curve-count value across the count, endpoint, and loop calculations. Restoring
the existing `curve_count` local adds **3.69 weighted bytes** without changing
candidate size, prefix, or reference quality.

The generated-mesh row and column are then reused by the face pass rather than
being redeclared as new source variables. This is consistent with the
function-family's shared counter declarations and with Windows carrying the
mesh and face columns through `edi`; the decompiler's different SSA names do
not require different authored variables. Retaining both owners together adds
another **7.38 weighted bytes**. Either row reuse alone or the required outer
column declaration alone is byte-neutral, while column reuse without its
declaration is incomplete. The dependency-complete result is:

```text
match: 63.94%
target: 655 insns, candidate: 640 insns
prefix: 8/655 target insns
masked operands: 37 ok, 0 unresolved, 0 mismatch, 0 unaudited
```

The superficially improving outer mesh-cursor scope is rejected. Moving
`mesh_sample_offset = 0` before the segment-count guard adds 3.69 weighted
bytes, but raw Windows initializes the cursor in `ebx` only after the signed
guard at `0x41ea14..0x41ea20`; extending that lifetime would be a score-only
register intervention. Seven delayed height-scale declaration/assignment
forms are byte-neutral. On the retained baseline, all five endpoint-offset
forms and all three orientation-subtraction combinations are also neutral or
regressive.

The ledger now contains 45 records, 42 mutation sweeps, 3 probes, and 250
unique variants. Those results document the current Dip frontier.
