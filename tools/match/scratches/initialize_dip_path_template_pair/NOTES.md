## 2026-09-25 controls (no source change)

Still 99.54%, 3/3 structural. Neither residual moved:

- **Phase zero from `ebx` (native) vs `ebp` (candidate).** `phase = i`,
  declaration order, `phase = i = 0`, and assigning it inside the guard all
  collapse to the constant (the guard forms give 60/52). Sharing `i` with the
  endpoint (`i = endpoint_index; ... i = 0`) is also byte-identical.
- **Early `[esp+0x20]` spill of `endpoint_index`.** Z/offset spelled
  `curve_count + 1` or `width_cells_ + 1`, a separate `terminal_index` (with
  or without offset), reassigning `endpoint_index`, a copy variable, and a
  Hump-style `curved` primary helper for the endpoint are neutral or worse
  (8/7 to 16/15). The HillValley late-copy recipe depends on its `centered`
  branch; Dip has no branch at the endpoint.

## Current canonical source: paired Identity owners (2026-09-21)

**98.77862595% → 99.54198473%, 655/655 instructions**, prefix 22;
37 clean references, with 33 now at both the native instruction index and byte
offset (previously 30). Primary Identity moves into the primary curve operation;
secondary Identity moves to the caller before its position operation. Either
move alone regresses. The pair recovers the 27-instruction region
`[0x41e626,0x41e684)` after four independently audited relocations, with every
candidate byte outside body offsets `[486,575)` unchanged.

Header/endpoint scheduling, phase-zero ownership and 17 total SIB bytes remain.
The body is not encoded-exact. See the [controls and byte proof](../../dip-identity-owners-20260921.md).

## Previous canonical source: branch-local lateral values (2026-09-21)

Current result: **98.77862595%, 655/655 instructions**, prefix 22, with
37 clean aligned references. Computing the lateral value inside each real
vertex branch fixes all six mesh stack displacement bytes; every other raw
candidate byte is unchanged. Header/receiver differences and eight later
SIB bytes remain. No whole-function exactness is claimed.

See the [source controls, native byte proof and replay](../../mesh-owner-frontier-20260921.md).
All measurements below are historical.

## Historical source: orientation and counter owners (2026-09-11)

The canonical source improves **75.96302003% → 85.78016910%**, with
**646/655** instructions, **37 clean aligned references**, and the native
**0x50-byte** frame. Its encoded prefix remains **8 instructions / 22 bytes**.
Direct sample-bank expressions replace helper-held pointers around
Normalize/Cross and RotIdentity; vector subtraction, curve/phase preheaders
and endpoint Z lifetime supply the coupled native source structure.

The 91-instruction region **[0x41e6d0, 0x41e84b)** maps to candidate
**[651, 1030)** with six strict positional references and a verified local
jump. Three SIB bytes differ, so this region is not encoded-exact. Full native
extent remains 2400 bytes, with [0,2390) compared and [2390,2400) recognized
terminal padding; no unexplained bytes. Whole-function, linked-code and data
exactness are not claimed. Header/register lifetimes, counters, encoded
addressing and mesh/face details remain open.

See [the current receipt](../../dip-orientation-counter-owners-20260911.md)
and its JSON for full sources, bytes, instruction positions, controls and
validation. The 58 distinct forward sources and nine reversals are replayable
on their stated parents. All eight individual reversals regress and all-reverse
restores the original function fingerprint. The slightly higher logical-cursor
alternative remains preserved, not promoted. Finite controls establish no
compiler ceiling. All entries below are historical measurements.

# `initialize_dip_path_template_pair` starter

Current recovery: declared semantic-complete, with native differences still under
analysis. This is a partial recovery, not an exact match or a compiler ceiling.

2026-09-11 current measurement: **66.46% → 75.96%**,
642 → 643 candidate instructions / 655 native, with a
8-instruction exact prefix. All 37 aligned references are clean;
only 2 share the native instruction index and 5 share the byte
offset. `body_byte_exact` is false. Compiler, flags, shared headers, ABI, and
matcher rules are unchanged.

The retained change recovers the ordinary/terminal vertex lifetimes and separates face UV assignment from texture selection.

Endpoint index allocation, previous-sample orientation ownership, and curve/mesh scheduling still differ. Direct physical orientation and delta controls do not improve this retained body.

The [recovery report](../../path-builder-source-recovery-20260911.md) and
[complete receipt](../../path-builder-source-recovery-20260911.json) contain the
before/after sources, identities, remaining assembly diff, reference positions,
and compared/excluded ranges. The promotion is recorded in `experiments.jsonl`.
Earlier observations below remain historical; finite controls do not establish
source exhaustion.

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

## 2026-09-05 terminal vector family replay

The complete terminal-position expression raises the current shared-header
baseline from **66.10% to 66.46%**, with 642/655 candidate/native
instructions and prefix 8. Reference audit: 37 ok, 0 unresolved, 0 mismatch, 0 unaudited.

The retained endpoint is previous position + Vector3(0,0,1), followed by
the existing lateral offset. This recovers the native aggregate temporary
lifetime without changing shared vector definitions or reference rules. The full
function remains partial; earlier percentages above belong to prior source
or dependency epochs. Existing reference debt, where present, is unchanged.

## 2026-09-25: endpoint cursor converted in place (Codex consult)

**99.54% → 99.85% normalized**, 655/655, prefix 22 → 100, 37 clean references, structural 1/1.

**Change.** The endpoint index becomes a byte cursor in place:

```cpp
int endpoint = curve_count + 1;
...
int endpoint_index = endpoint;
endpoint *= sizeof(PathAttachmentSample);
```

The saved logical index still supplies `(float)endpoint_index`.

**Why it works.** The endpoint register keeps its value until the multiply, so the conversion home store
`mov [esp+0x20], edi` lands just before the reuse, exactly where native has it. That also fixes the
adjacent `fild` order.

**Remaining.** The `curve_phase_index = 0` store before the curve loop uses ebp (the function-wide
constant 0) where native uses ebx.
- Single-index loop forms give native's store source but move constant 0 into ebx, and mesh allocation
  regresses.
- Evidence and tried families: `/private/tmp/claude-501/sm/codex/dip/RESULTS.md` (46 probes).

## 2026-09-26: guard placement and invisible ranges (crimson-88 Q8, Q9)

Mechanism: crimson's `../crimson/tools/match/c2/compiler/guard-placement.md` (where loop inits land, and
what the extra block costs) and `../crimson/tools/match/c2/compiler/invisible-ranges.md` (what P counts).
Everything below was compiled and traced on copies. No source change is retained: the live form stays at
99.85% (655/655), with the single ebp/ebx store.

The three loop forms:
- `tied_single` (the live form): the cursor is a user variable initialised in the for-init;
- `tied_guarded`: `int i = 0; if (i < width_cells_) { int sample_offset = sizeof; do {…; ++i;} while (i < width_cells_); }`;
- `iv_lead`: a strength-reduced cursor.

### Where the cursor init lands

- `tied_single`: flow graph after 0x107053de. Block 1 ends `i = 0; sample_offset = 168; cmp i, width; jcc`,
  and block 2 is the empty preheader, flag 0x8000000. So `mov edi, 0xa8` comes before `jle`.
- `tied_guarded`: at `build_live_ranges`, block 2 holds `sample_offset = 168` and block 3 is the empty
  preheader.
- `iv_lead`: at `build_live_ranges`, block 2 (flags 1) holds `#1877 = 168` and block 3 (flags 0x8000000)
  is empty.

Native has `mov edi, 0xa8` after `jle`, so native's cursor init is in its own block (SR-derived or
explicitly guarded).

### What the extra block costs

The range that decides the colouring is constant 0's second-level split piece (rescore after colouring
#30). The competitor is the `vertices` piece (build_strip_mesh), allowed {ebp}:

| source | block 1 | init block | loop and rest | piece priority | competitor (`vertices` piece, allowed {ebp}) |
|---|---|---|---|---|---|
| `tied_single` (init before the guard) | +182 = 14·13 | n/a | −34 | **148** | 144 |
| `iv_lead` (SR cursor) | +169 = 13·13 | −2 (P = 2: D and constant 168) | −34 | **133** | 144 |
| `tied_guarded` (explicit guard) | +169 | −2 | −34 | **133** | 144 |

The piece's allowed set is {ebp} in all three.

- **148 > 144.** Zero is coloured first and gets ebp. `vertices` then loses ebp and is split. The loop
  index gets ebx. This is native's allocation.
- **133 < 144.** `vertices` takes ebp first, which leaves the zero piece with an empty allowed set.
  0x107204d6 splits it at the markers. The new piece covers blocks 1..22 and has allowed {ebx}; after
  rescoring its priority is 187. It gets ebx, and the index then gets ebp. The earlier "187 vs 148"
  compared this post-split piece with the tied piece. **187 is a consequence of losing ebp, not the
  cause.** The decision is 133 against 144.

So every after-guard shape costs exactly 15 on zero's piece: 13 because the entry block references one
range fewer (P 14 → 13, times S = 13), and 2 because the piece lives through the new block (P = 2). That
is why every "after the guard" shape tried flips the colouring (`iv_lead` 85.80%, `tied_guarded` 86.18%,
60 probes).

Threshold check (intervention, not a source form: add N once to every constant-0 range that starts in
block 1, at every scoring return) on `tied_guarded`:

| N | piece | result |
|---|---|---|
| 11 | 144, which ties `vertices`. On equal priority the higher tie key goes first, and a constant's tie key is 0. | unchanged object (86.18%) |
| 12 | 145 | **100% normalized**, 655/655, native allocation, with `mov edi,0xa8` after `jle` |
| 13, applied to `iv_lead` | 146 | native allocation and init placement; one receiver left (`mov edx,[esi+0x58]; mov ecx,edi; add ecx,edx`) |

**Rule.** With the init after the guard, native's function must reference one more candidate range in the
entry block (P 13→14, worth +13 here) with the same instructions, or have any other difference worth at
least +12 on that piece. The +12 intervention shows that nothing else is missing.

Source search, all neutral (86.18% unchanged): guard spelled `width_cells_ > 0`, `curve_count > 0` or
`i < width_cells_`; latch on `curve_count`; `while (++i < …)`; `sample_offset` declared outside the `if`
or at the top of the function. Worse: `endpoint_z` computed early (84.42%), a separate `endpoint_offset`
variable instead of `endpoint *= sizeof` (85.87%), and the tied cursor declared early, live through the
endpoint code, which steals edi from `endpoint` (91.3%).

### What P counts in Dip

P computed from the IL at `score_live_ranges` entry equals the one implied by the priority deltas in every
block checked (block 1: 13, block 2: 2, block 4: 9, block 5: 6, block 7: 5, block 18: 8, block 19: 11,
block 23: 5). `block+0x48` is not P: in block 5 it has 11 members while P is 6. They agree in block 1,
where nothing is live-through.

- Block 23 (the mesh preheader) has P = 5 at score0 (constants 1 and 2, the `&g_texture_refs` address,
  and the reloads of `texture_a` and `texture_b`). All five are pruned, and at every rescoring block 23
  has P = 0. The zero piece is scored in the second rescoring, so ranges pruned after score0 do not help
  it.
- Block 1 at colouring entry has 18 candidate ranges. The coalescer removes `#1812 = endpoint` (17).
  Forward substitution removes the four `lea this+disp` temporaries #1190, #1198, #1208 (=
  `&this->primary_samples`), #1228 (13). The x87 fold changes nothing in the integer class (13). The
  pressure pass folds `#1807 = #1808` and `endpoint = #1802` into their ranges (13). At score0 P = 13.
- The latch `i = #1294` (#1294 = `i + 1`, defined mid-body) is a copy the coalescer refuses. Both ranges
  count in block 7; the chooser gives them one register, so there is no `mov`: ours `inc ebp;
  mov [esp+0x20], ebp`, native `inc ebx; mov [esp+0x20], ebx`.
- `width_cells_` is read once inside one block and becomes local temp #1477 (not counted).

Invisible ranges already in the function:

| Class | Example |
|---|---|
| a: LOADCONST of a constant with ≥ 2 eligible uses that ends uncoloured | block 1: `0.49f` (two stores) and `168` (load placed at the end of block 1, uses in blocks 2, 4, 7, 11, 21) |
| b: reload with one use in another block | block 23: `texture_a`, `texture_b` (`mov eax,[esp+0x78]; push eax`) |
| c: refused copy into a multi-definition range | block 7: `i = #1294` |
| d: candidate demoted late | block 4: `#1066`, the integer view of `angle` pushed for `Cos`, alive in every rescoring |

Constant loads: 0, 1.0f and 0.49f are placed right before their first use in block 1; 168 at the end of
block 1; 1, 2 and `&g_texture_refs` at the end of the mesh preheader, block 23.

### Block 1 at the deciding rescoring (run 2)

`tied_guarded`: P = 13: `this`, 1.0f, **0.49f**, `curve_count` #9, `endpoint` webs 1 and 2, `i` #14, zero
piece, **168 piece**, and the temporaries #1197 (`endpoint + 1`), #1210 (`primary_samples` CSE), #1238
(`primary + endpoint`) and #1807/#1808 (`endpoint * 7`). `tied_single` has the same set plus
`sample_offset` #15 (P = 14). The earlier list of 12 left out 168. Two of the 13 are already invisible
(class a: 0.49f and 168).

### Why block 1 cannot supply a fourteenth range with native's instructions

Native's block 1 is identical to ours instruction for instruction (the +12 intervention is 655/655
normalized), so the new range must be invisible and must still be alive at run 2.

- **Class a** needs a new constant value with two eligible uses whose load lands in block 1. Native's
  function has none spare. Block 1's eligible immediates are 0x14 (a single use, turned back before
  scoring), byte and dword 0, 1.0f, 0.49f and 168, which are all already counted. `+1` is `inc` and
  `-1` is `dec` before promotion (0x21/0x1e at `build_live_ranges` entry). Every other immediate in the
  function is an address displacement (`lea`), a shift count (refused), a store that is still an
  unpromoted immediate at scoring (the `Vector3(1,0,0)` temporaries in the loop), or a mesh-only
  constant whose load sits in block 23.
- **Class b** is pruned after score0, so it cannot move the run-2 zero piece. Native also has no later
  memory read that could be such a use.
- **Class c** needs a multi-definition range in block 1 fed by a copy from a separate single-def range
  that dies there. Block 1 has only `i` (initialised from constant 0, and constant sources are never
  recorded) and the two-operand results of `endpoint *= 168`. Their sources are lowering temps (#1808,
  #1802) that the pressure pass folds. Turning one into a candidate needs a second use, and that use is
  visible.
- **Class d**: the only memory-only local in block 1, `endpoint_index`, is demoted inside
  `build_live_ranges`, because its register value is dead at block end (its only use, `fild`, reads
  memory). A `(float)i` reuse of `i` behaves the same (`s4`). Keeping it alive needs a register use or a
  later `fild`, and both are visible.

Compiled on copies of the guarded form. Every row keeps P(block 1) = 13 in score0 and run 2 unless noted:

| Variant | Change | Result |
|---|---|---|
| e1 | `endpoint = endpoint_index * sizeof` | 86.18%, identical (copy propagated) |
| e2 | `endpoint_index` from `curve_count + 1`, new `endpoint = endpoint_index * sizeof` | 85.87% |
| z1, z2 | `endpoint_z` from `(float)(curve_count + 1)` / before the multiply | 85.50%, 84.05% |
| z3 | `(float)(endpoint / sizeof)` (control, a visible divide) | **P 14, zero 146, ebp**, but 90.05% (+7 instructions) |
| x_idx | endpoint stores in index form `primary_samples[endpoint]` | 85.50% |
| p1..p8 | pointer local, `identity_at(bank, offset)`, `identity_sample(ptr)` helpers for the endpoint and sample-0 `Identity` calls | 86.18%, identical (propagated) |
| r1..r4 | Dump-style `PathAttachmentSample* const& bank = …` bindings | 85.78–86.18% |
| s1..s4 | `sample_index` / reuse of `i` for the endpoint z (Hump departure style) | 86.18%, 83.96% (s4) |
| w1..w5 | `width_cells_` and `curve_count` roles swapped or mixed | 83.72–86.18% |
| k3, k6, k7 | cursor also initialised before the `if`, SR cursor inside the `if`, `while (++i < …)` | 85.80–86.18% |
| i2, i3, i4 | `++i` moved (zero 135 in i2: a loop-block effect) | 85.71%, 69.49% |
| h1, m_dump, m_hump | Hump's `compute_terminal_deltas`; Dump's and Hump's `build_strip_mesh` | 86.18%, unchanged priorities |
| live_i | live scratch with `int curve_phase_index = i;` | 99.85%, same as `= 0` (constant propagated) |

### Where +12 can still come from

The zero piece's run-2 budget is block 1 +169 (P 13 × S 13), block 4 +72 (P 9 × w 2 × S 4), and
live-through charges of −108 over blocks 2, 5, 6, 7, 11, 17, 18, 20, 21, 25 and 40 (block 18 alone is
−32 = P 8 × w 4). The `vertices` piece gets +64 in block 18 (S 2) and +88 in block 19 (P 11 × w 4 × S 2),
and pays small charges elsewhere. From these numbers [inferred, not source-tested]:

| Change | Zero piece | `vertices` piece | Enough? |
|---|---|---|---|
| One more range in block 1 | +13 (P 13 × S 13) | 0 | yes |
| One more range still alive at run 2 in the loop head (block 4) | +8 (w 2, S 4) | 0 | no; two are needed |
| One range fewer in vertex-loop block 18 | +4 | −8 | yes: zero 137, `vertices` 136, and zero goes first |
| One range fewer in vertex-loop block 19 | 0 | −8 | no; needs +4 elsewhere |

- One more zero **store** in block 1 is +13 via S, not P. This is the live scratch's
  `curve_phase_index = 0`, 148. It is visible as `mov [esp+0x14], ebp`, where native has ebx. Writing
  `= i` changes nothing, because constant propagation turns it back into `0`.
- `i2` already changes the zero piece by +2 through loop-block P, so loop-head and mesh reference sets are
  where to look. The instructions must still be native's.

### Also hidden in `tied_single`: 14 SIB swaps

Behind its normalized mismatch, 14 curve-loop instructions have swapped SIB base and index. `tied_single`
at +0x1af is `89 ac 07 90` = `[edi+eax+0x90]`; native is `89 ac 38 90` = `[eax+edi+0x90]`. The intervened
`tied_guarded` object is 100% normalized but `body_byte_exact=false` for exactly these bytes. This is the
address-order hash ([address-order.md](../../c2/address-order.md)). The source that supplies the +12 may
also shift the temporary ids that decide it. Every variant above keeps our register-plus-register order.

### Next

1. Take `tied_guarded` as the loop form.
2. Rerun the header/endpoint mutation families on top of it; they were judged with the tied loop, where the
   cursor itself supplied the fourteenth range. The block-1 route is closed for the constructs above, so
   favour loop-head (block 4) and mesh (blocks 18/19) reference sets with identical instructions.
3. Judge each candidate by the run-2 zero piece against the `vertices` piece (zero ≥ 145 against 144),
   not by P(block 1):

```sh
uv run tools/match/c2/crimson_tool.py priority_trace <copy> --out <new-dir> --constant 0 --symbol 549
uv run tools/match/c2/crimson_tool.py block_refs_trace <copy> --out <new-dir> --block 4 --block 18 --block 19 --rescore
# intervention (not a source form): +N to constant 0's ranges that start in block 1
uv run tools/match/c2/crimson_tool.py priority_trace <copy> --out <new-dir> --bump-constant 0 --bonus 12
```
