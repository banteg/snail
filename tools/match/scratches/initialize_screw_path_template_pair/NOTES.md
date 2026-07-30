# `initialize_screw_path_template_pair` starter

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

No source variant improves the canonical metric, and the append-only ledger is
formally stalled after three consecutive non-improving sweeps. The semantic
per-lane recomputation remains recorded from both ports, but recovering it in
matcher source now requires a broader neighboring-loop lifetime change rather
than another local trig spelling.

## 2026-07-30 authored terminal-delta subtraction

The independent terminal-delta block is exact across the constructor family
despite the stalled trig schedule. Replacing both component constructors with
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
