# `initialize_screw_path_template_pair` starter

Current recovery: semantic-complete (`compiler,references` residual). The
verified Android/iOS bodies establish the portable sample/control graph, and
the Windows scratch covers its native mesh/face tail. Two known per-lane trig
calls remain unaudited; no reference is unresolved or mismatched.

This is an honest semantic starter for the path-template initializer at
`0x41eda0`.

It reconstructs the screw template setup, three-sample entrance, five-sample
exit, helical middle section, recovered `rotation_scalar_94` angle, rotated
secondary lane, adjacent-sample orientation, deltas, strip mesh, and final
template pass.

The scratch is partial and keeps the source plausible. Any future tightening
should focus on real lifetime/control-flow shape.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments
(`curve_count`, `width_cells`, an unused mode, two textures, and a cap texture)
and the native tail is `ret 0x18`. Updating the scratch and shared declaration
from the stale four-argument prototype moves focused Wibo from 18.80% (613/685)
to 18.95% (613/685), with masked operands unchanged at 19 ok, 0 unresolved, 4
mismatch.

2026-07-03 sample setup lifetime pass: the screw-only entrance, exit, and
helical middle loops now spell the native sample setup directly instead of
calling the generic sample-pair helper. The retained shape delays the Z counter
conversion until after primary identity, removes the helper's extra helical
secondary-X store, and computes the previous-sample up-vector cosine before the
negated sine. Focused Wibo moves from 18.95% (613/685) to 30.95% (601/685),
with the masked audit improving from 19 ok, 0 unresolved, 4 mismatch to 33 ok,
0 unresolved, 0 mismatch.

2026-07-04 header schedule probe rejected: moving the mirror/side/scale header
writes into the active screw branch so `width_cells`, `kind`, and segment-count
setup precede them matched the native-looking entry order more closely, but was
metric-neutral at 30.95% (601/685) with the masked audit unchanged at 33 ok, 0
unresolved, 0 mismatch. The scratch keeps the shared header spelling rather
than adding branch-local boilerplate without a matcher win.

2026-07-15 mesh ownership recovery: the native face builder preserves parity
branches even though both arms of each orientation currently request the same
texture, advances face columns with a `do/while`, and materializes an ordinary
row position as a `Vector3` before storing it. Recovering those source facts
raises focused Wibo from 30.95% (601/685) to 39.88% (619/685), with 32 clean
masked operands and no unresolved or mismatched operands. The parity branches
provide the largest independently measured gain, reaching 39.41% (614/685);
the face-column lifetime then reaches 39.78% (612/685).

2026-07-15 rejected lifetime probes: an explicit byte cursor for the
three-sample entrance regressed focused Wibo to 39.63% (617/685), and direct
array-member spelling regressed it to 39.21% (631/685) while introducing a
masked call mismatch. An explicit helical byte cursor fell to 33.18% (617/685)
with four call mismatches; separately duplicating the secondary up-vector trig
calls fell to 26.77% (630/685) with one call mismatch. A mutating five-sample
departure loop remained audit-clean but regressed to 39.72% (619/685). These
forms are not retained until the surrounding orientation lifetimes explain the
native schedule as a whole.

2026-07-17 live owner-ABI closure: the native tail is `retn 0x18`, the iOS
counterpart is `cRPath::BuildScrew(int, int, bool, char*, char*)`, and the
Windows caller supplies the additional final cap-texture argument. Binary
Ninja's stale five-parameter view had shifted the first texture onto the mode
slot, retained a user-authored `char*` at stack `+0x14`, and omitted `+0x18`.
The guarded recreation now owns the exact `Path*` receiver and six stack
arguments through `cap_texture`; direct readback confirms storages `+4..+24`.
This is analysis-only: focused Wibo remains 39.88% (619/685), with 32 clean
masked operands and no unresolved or mismatched operands.

## 2026-07-20 path-lifetime ownership replay

The screw constructor independently proves seven complete owners: primary and
secondary basis-up vectors, both terminal deltas, the primary mesh sample, the
shared ordinary/terminal vertex, and one facequad cursor reused by the native
two-pass inner loop. That single face lifetime is deliberately distinct from
the adjacent dip builder's simultaneous first/second records.

The two byte-biased forward-vector candidates were rejected because they added
four backward `__offset` expressions to neighboring sample reads. The guarded
replay retains only the zero-offset set behind canonical layout checks. The
scratch remains unchanged at its honest 39.88% focused match with 32 clean
masked operands.

## 2026-07-26 mesh and shared-face ownership

Raw instructions at `0x41f43e..0x41f50e` prove the same branch-dependent vector
construction as the adjacent path builders: an ordinary lateral offset plus
generated position, and a terminal lateral offset, raised endpoint, and
generated position. Both paths materialize their destination late and converge
on the final Z store, matching Binary Ninja's one shared `vertex` lifetime.
Replaying these owners alone raises focused matching from 39.88% to 43.96%.

Screw's face loop remains structurally distinct from Dip. Native instructions
at `0x41f5ce` materialize one face cursor before the two-pass branch and reuse
it for either orientation. Each pass nevertheless owns a complete record,
including its final `uv[3].v` write. Keeping the shared pointer while completing
the two branch-local records produces:

```text
match: 48.53%
target: 685 insns, candidate: 646 insns
prefix: 6/685 target insns
masked operands: 34 ok, 0 unresolved, 0 mismatch
```

The complete recovery gains 8.65 focused points, 27 candidate instructions,
two clean operands, and the exact native `0x50` frame without inventing a
second face owner.

## 2026-07-27 paired-mobile boolean ABI

The exact Android and iOS `cRPath::BuildScrew(int, int, bool, char*, char*)`
symbols prove that the third input is a boolean. Both mobile bodies stop after
building the sample/delta data and calling `CalcLengthZ`; the Windows-only
tail adds the cap texture and builds the mesh locally. The Binary Ninja type
change was previewed, applied, read back, and followed by lifetime replay with
all recovered owners still current.

The focused Windows build remains **48.53%**, **646/685** candidate
instructions, and a six-instruction exact prefix; its masked audit has 38
accepted and 2 unaudited operands with no unresolved or mismatched operands.
Replacing the native `sample_index <= 3` spelling with the mobile logical
`i == 0` guard was measured and rejected: it regressed matching to 46.92% and
645 candidate instructions. Only the proved boolean ABI is retained.

## 2026-07-28 paired-mobile control ownership

The exact Android
`analysis/decompile/android/functions/0005681c-_ZN6cRPath10BuildScrewEiibPcS0_.c`
and iOS
`analysis/decompile/ios/functions/000586dc-_ZN6cRPath10BuildScrewEiibPcS0_.c`
bodies independently preserve the three-sample entrance, five-sample
departure, helical middle, adjacent-sample orientation, and final
delta/`CalcLengthZ` passes. Windows remains authoritative for exact definition
identities, `0xa8` byte cursors, the six-argument ABI, and its native-only
cap-texture/strip-mesh tail.

A transactional Binary Ninja replay now records 15 exact Windows owners: five
direct variables plus ten merged definition clusters covering the total count,
entrance and departure indices/offsets, departure Z, helical curve
index/offset, and delta index/offset. The preview changed all ten clusters,
rolled them back cleanly, and produced no `__offset` artifacts. Live readback
confirms exact types and user-defined provenance, while a second replay found
every operation already current.

The strict export also corrected IDA's stale five-argument `PathTemplate*`
rendering to the recovered `Path*`, boolean mode, and cap-texture ABI. No
matcher source changed: focused Windows matching remains honestly **48.53%**,
**646/685** candidate instructions, a six-instruction exact prefix, 38 accepted
and two unaudited masked operands, with no unresolved or mismatched operands.

## 2026-07-30 per-lane orientation schedule bound

The two remaining unaudited references are the second `cosine(angle)` and
`sine(angle)` calls at native offsets `+0x3b1` and `+0x3bb`. Android and iOS
independently recompute that pair after finishing the primary orientation and
before building the secondary orientation. The retained matcher source shares
one pair because direct transfer of the semantic source fact destabilizes
VC6's surrounding loop schedule.

Three bounded sweeps cover 21 variants of that boundary: sequential and scoped
per-lane locals, direct helper arguments, explicit lane bodies, angle-taking
helpers, and a split between assigning the up vector and running the
normalize/cross tail. Per-lane helper forms audit all 40 references but regress
to 37.26%; the best exact-reference split reaches only 40.24%. The strongest
non-exact explicit form reaches 44.03%, still below the retained 48.53%.

No source variant improves the canonical metric. The semantic
per-lane recomputation remains recorded from both ports, but recovering it in
matcher source now requires a broader neighboring-loop lifetime change rather
than another local trig spelling.

## 2026-07-30 authored terminal-delta subtraction

The independent terminal-delta block is exact across the constructor family
despite the recorded trig schedule. Replacing both component constructors with
`Vector3::operator-` adds 7.50 weighted bytes and raises focused matching from
48.53% to **48.84%**. Candidate and target counts remain 646/685, prefix stays
6/685, and the receipt remains 38 clean plus 2 unaudited references.

## 2026-07-30 orientation subtraction bound

Both shared orientation helpers were tested independently and together with
the authored operator form. Every variant is byte-identical, preserving
**48.84%**, 646/685 instructions, prefix 6/685, and the same 38 clean plus 2
unaudited references.

## 2026-07-30 mesh arithmetic ownership

The independently proved native block at `0x41f43e..0x41f50e` uses distinct
ordinary and terminal right-vector/position pairs before converging on Screw's
shared late vertex destination. A `double` lateral local, both
`Vector3::operator*` scales, and both `Vector3::operator+` position adds
recover that arithmetic boundary and add 37.52 weighted bytes.

The position-add result is interaction-dependent: before the scale rewrites,
the ordinary add gains 3.76 weighted bytes and the terminal add regresses;
after both scales, the complete add pair gains 11.28. Split-float is neutral,
the full double expression adds reference debt, and volatile float collapses
the prefix, so those lateral variants are rejected. Focused matching rises
from **48.84%** to **50.34%**, candidate instructions move from 646 to 642
against 685 target instructions, prefix stays 6/685, and the existing trig
receipt remains 38 clean plus 2 explicitly unaudited references.

## 2026-07-30 interacting sample ownership and control

The native entrance, departure, and curve blocks keep `this` in ESI and a
sample byte offset in EDI while reloading both arrays. An exhaustive
seven-variant ownership sweep shows why the older isolated probes failed:
direct entrance and departure ownership each regress alone, but together they
add 48.83 weighted bytes and raise focused matching from **50.34%** to
**52.30%**. The curve owner still regresses in that intermediate state.

The native departure then exposes its mutating count-relative source boundary:
it starts at `curve_count + 3` and tests
`departure_index - 3 - curve_count < 5`. Retesting that exact post-tested
control on the paired-owner baseline adds another 56.45 weighted bytes and
reaches **54.56%**. It removes one candidate instruction, but the resulting
664/685 count remains close and the large byte gain follows the recovered
native control rather than a metric-only spelling.

That control change unlocks the previously losing curve owner. Replacing only
the curve's primary/secondary aliases with direct array ownership now adds
183.45 weighted bytes, grows the candidate to 675/685 instructions, raises
matching to **61.91%**, and extends the exact prefix from 6 to 14 instructions.
The order is essential: applying all three owners before recovering the
departure control had fallen to 48.16%.

Finally, moving Screw's original-function header schedule into its active
variant—width, kind, mirror/side/scale, then counts—adds 7.34 weighted bytes
and extends the exact prefix to **26/685**. The retained frontier is
**62.21%**, 675/685 instructions, with 38 clean plus 2 unaudited references.
The shared macro header remains guarded for inactive variants.

All three earlier per-lane trig families were exhaustively rerun after this
register-ownership recovery. Across 21 variants, the forms that reproduce both
native trig calls audit all 40 references but lose at least 103.79 weighted
bytes. Five equivalent departure predicates are neutral or regress, and two
post-tested delta controls each lose 12.41 bytes. Those local schedules remain
bounded; the material result comes from the interacting sample/control graph.

## 2026-07-30 face-pointer ownership bound

Screw's native tail computes a common integer face index but materializes the
pointer and zero header inside each parity arm. Reproducing that ownership
literally is strongly negative on the recovered sample/control baseline:
focused matching falls from **62.21%** to **49.34%**, candidate instructions
grow from 675 to exact count parity at 685/685, and the exact prefix contracts
from 26 to 6. The receipt remains 38 clean plus 2 unaudited references, so the
instruction-count coincidence is not evidence of a better decomp. The
branch-local pointer form is recorded and rejected.

## 2026-07-30 fixed and curved byte-owner cascade

The recovered Windows owners keep a logical entrance index beside a `0xa8`
sample cursor, a count-relative departure index beside its derived cursor, and
the helical logical index beside a cursor starting at `0x1f8`. Replaying those
owners on the 62.21% frontier exposes another allocation cascade.

The departure cursor improves alone to **62.69%** and the curve cursor improves
alone to **62.59%**. The entrance cursor initially falls to 59.16%, but makes
the first 58 instructions exact instead of 26. Entrance plus departure reaches
60.97%; adding the curve cursor recovers to 63.42% while preserving the longer
prefix. The final missing owner is identity rather than width: the entrance
must reuse the constructor's shared `i` slot instead of introducing a
lead-only logical index. A recorded reverse mutation loses 128.80 weighted
bytes, while the shared owner produces the retained result:

```text
match: 68.58% (was 62.21%)
target: 685 insns, candidate: 671 insns (was 675)
prefix: 58/685 target insns (was 26/685)
masked operands: 38 ok, 0 unresolved, 0 mismatch, 2 unaudited
```

The complete source recovery adds 159.14 weighted bytes and follows the exact
native index/cursor graph; the four-instruction count tradeoff is not used as
the evidence for retaining it.

Adjacent owners are bounded again on this frontier. Five equivalent departure
predicates are neutral or strongly negative, and an explicit precomputed
`-3 - curve_count` local collapses matching to 45.56%. Three per-lane trig
spelling variants, four split up-vector/tail variants, and four angle-helper
interactions resolve both unaudited calls but remain 117.60–126.11 weighted
bytes below the retained source. The branch-local face pointer still reproduces
its prior 49.34% result exactly. A derived entrance cursor falls to 62.34%;
swapping the entrance declarations cuts the prefix to 23, and moving the index
increment into the loop condition is byte-identical.

## 2026-07-31 direct face-offset record ownership

Replacing the face pointer with a semantic integer offset and direct indexed
record writes raises focused matching from **68.58%** to **69.90%** and moves
candidate size from 671 to 674 instructions against the 685-instruction
target. Prefix remains 58/685, and the existing 38 clean plus two unaudited
references are unchanged. The independently rejected branch-local pointer
result remains bounded; this retained form has one offset owner for both
winding branches.

## 2026-07-31 post-face sample-owner replay

Moving the mesh sample above the ordinary/terminal branch destroys the
recovered leading allocation: matching falls from **69.90%** to **54.68%**,
the exact prefix contracts from 58 to 6 instructions, and candidate size
moves from 674 to 672 against 685 native. The complete probe preserves the
reference audit and decisively retains the two branch-local sample records.

## 2026-07-31 mesh-to-face counter ownership

Screw's native mesh and face tail carries both scalar counter owners across the
phase boundary. The mesh ends at `0x41f531`; the face setup at
`0x41f537..0x41f54b` resets the carried row/column storage rather than
introducing two additional source lifetimes. Reusing both source counters adds
18 weighted bytes and raises focused matching from **69.90%** to **70.64%**.
Reusing only the column adds 11 bytes, while row-only reuse is byte-neutral.

The retained complete ownership does not change candidate size: it remains
674/685 instructions with prefix 58/685 and 38 clean plus two unaudited
references. The three-way recorded sweep contains the neutral and partial
alternatives.

## 2026-07-31 post-counter trig replay bound

The two native per-lane trig calls were replayed once more after mesh/face
counter reuse changed the final allocation. All three call-complete source
families remain decisively negative while preserving the 58-instruction
prefix:

- sequential, scoped, and direct per-lane calls lose 124 weighted bytes;
- local/direct angle helpers lose 126;
- the best split up-vector/orientation-tail form loses 117.

Each complete form audits all 40 references, but falls to 65.59-65.93% from
the retained **70.64%**. The matcher source therefore keeps its shared trig
pair and records the two native calls as explicit unaudited debt rather than
accepting a five-point whole-function regression.

The ledger now contains 37 records, 34 mutation sweeps, three probes, and 153
evaluated variants (147 unique). Those results document this post-counter
call-schedule frontier.
