# calc_object_bounding_box

Object bounds pass at `0x42fb10`.

- Confirms `Object +0x38` is the `Vector3* vertices` array.
- Confirms `Object +0x94` is the maximum vertex magnitude used as a bounding
  radius.
- Confirms `Object +0xa4..+0xaf` is the minimum xyz bound and
  `+0xb0..+0xbb` is the maximum xyz bound.
- Current source is relationship-first, not proof-grade. A 2026-06-21 source
  pass improves focused Wibo from 52.14% to 67.81%, 114/119 candidate/target
  instructions, 28/119 prefix, and one clean masked operand.
- Using the return variable as the processed-vertex counter recovers the native
  longer prefix and preserves the zero-or-negative vertex-count return. Spelling
  the min/max tests in bound-first form (`bound <= vertex`, `vertex <= bound`)
  improves the x87 compare shape.
- Rejected followups: manual min-bound component initialization regressed below
  52% by changing the prologue saves, seeding a separate index local was
  codegen-neutral, and `register` on the byte offset stayed at 58.12%. The
  remaining mismatch is initialization store order plus compare-branch
  scheduling, not a recovered field-layout issue.
- 2026-06-21 partial min-bound retry: splitting only the min x/y stores before
  `bounding_radius = 0.0f` and writing min z afterward also regresses to
  51.33%. It recovers the desired local store order but loses the native
  saved-register/prologue shape, so the aggregate min vector remains retained.
- 2026-06-21 scalar-temp sweep: forcing vertex x/y/z through scalar locals,
  forcing only x through a scalar, adding a byte cursor for the vertex array,
  and combining those with the split manual init order all failed to beat the
  retained 67.81% shape. The scalar variants either overgrew the frame or moved
  the prologue off the native saved-register set; the byte cursor lost the
  native prefix almost immediately. Keep the aggregate min/max initialization
  and direct vertex expression form.

## 2026-07-10 void mutator and loop-owner correction

The sole native caller in `cRObjects::BuildObjects()` checks that
`vertex_count` is nonzero, calls this method, then immediately reloads the next
object state without consuming EAX. The apparent count return is incidental:
EAX holds `vertex_count` on the empty path and the final loop counter on the
non-empty path. The shared declaration and scratch now model the real
`void cRObject` mutator contract.

Initializing the processed-vertex counter to zero before testing
`vertex_count` also matches the native counter lifetime more closely and
raises focused Wibo from 67.81% to 68.67%, with 114/119 instructions, prefix
28/119, and one clean operand. Direct ternaries with both comparison
polarities and additional scalar temporaries were rejected: they reduce the
score and still fail to recover native's six `fld`/`fcompp` min/max schedules.

## 2026-07-12 extended min/max comparison recovery

The native bounds tests load both `float` operands into x87, compare them in
extended precision with `fcompp`, and use strict keep-the-existing-bound
branches. Expressing that source shape directly raises focused Wibo from
68.67% to 84.52%, with 120 candidate instructions versus 119 target,
28/119 exact prefix instructions, and one clean masked operand.

This is also a semantic correction. For each maximum component the native
shape is “keep max while `vertex < max`, otherwise take vertex”; for each
minimum it is “keep min while `min < vertex`, otherwise take vertex.” The
unordered x87 status therefore takes the vertex path, so a NaN vertex
propagates into the derived bounds instead of retaining the prior sentinel or
component.

The remaining residual starts in initialization scheduling: native clears
`bounding_radius` before spilling the processed-vertex counter and finishing
the aggregate minimum-vector store, while VC6 schedules the candidate's radius
clear after the initial vertex-count comparison. That also leaves candidate
vertex setup as three instructions (`vertices` load, offset copy, add) versus
native's two-instruction load/add. The six compare/select bodies and the
derived-radius update otherwise have the recovered field ownership and native
extended-comparison behavior; no volatile qualifiers or synthetic locals were
added to force the final schedule.

## 2026-07-12 analysis ABI sync

The Windows build loop calls this as an `Object` member and immediately
continues to the next object without consuming EAX. The empty path leaves
`vertex_count` in EAX while the populated path leaves the processed count, so
the register cannot carry one stable authored result. The repeatable BN/IDA
slice now records the proved `void __thiscall` owner instead of the stale
free/fastcall integer transcription; focused matching remains honestly partial
at 84.52%.

## 2026-07-13 shared zero owner recovery

Native clears EBP once, uses it as the byte offset, and writes those same zero
bits into `bounding_radius` before spilling the processed-vertex counter. The
plausible old-C++ chained clear `bounding_radius = offset = 0` recovers that
shared zero owner. It also lets VC6 form the loop vertex directly as
`vertices + offset`, eliminating the previous synthetic register copy.

Focused Wibo rises from 84.52% (120/119 instructions) to 99.16% with the exact
119/119 instruction count, 28/119 exact prefix instructions, and one clean
masked operand. The sole remaining difference is scheduling: native writes the
radius zero before the counter spill and vertex-count test, while the candidate
sinks that independent store to just after the comparison. No volatile store
or artificial dependency is used to force the final instruction across the
test.

## 2026-07-15 checked-in owner replay

The refreshed Binary Ninja artifact now renders the receiver as `Object*` and
names `vertices`, `vertex_count`, `bounding_radius`, `bounds_min`, and
`bounds_max`. A health check rejects the old raw-offset receiver and synthetic
integer return while the honest 99.16% scheduling residual stays unchanged.

## 2026-07-18 paired replay and health proof

The IDA lane is now address-anchored and fail-closed on the complete
0xdc-byte `Object` owner before this prototype is applied. Its tracked artifact
matches the Binary Ninja ownership view: a void Object mutator over typed
vertices, minimum/maximum bounds, and bounding radius. A paired IDA health
check now rejects the old `_DWORD* this`, raw offsets, and incidental return.

No matcher source changed. Focused Wibo remains `99.16%`, exactly `119/119`
instructions, prefix `28`, with one clean mask; only the independent radius
zero-store scheduling remains.

## 2026-07-27 mobile negative evidence

Android and iOS both export `cRObjects::BuildObjects()`, the authored owner
already mapped to the Windows caller at `0x42f9e0`. Both mobile bodies preserve
the surrounding object-build sequence—texture joining, texture-group and GL
vertex-array construction, optional toon normals/edges, save, and static VBO
handling—but neither calls nor inlines a position min/max or radius scan.

Neither mobile symbol inventory exports a separate object-bounds member.
The scorer's nearby `cRObject::AddEdge`, `CalcEdges`, `CalcTextureGroups`,
`GLObjectVBO`, and constructor candidates have distinct build-time owners and
were explicitly rejected. This is therefore a Windows-only pass inside the
shared `cRObjects::BuildObjects()` lifecycle, not a missing one-to-one mobile
mapping. Mobile layout offsets and scheduling provide no further matching
claim; focused Wibo honestly remains `99.16%` with the single independent
zero-store scheduling residual.

## 2026-07-29 bounded zero-chain audit

Nine plausible chained-initialization orders were tested around the recovered
shared zero owner. Four compile byte-identically to 99.16%, 119/119, prefix
28; the other five regress as far as 84.52%. None moves only the desired
store.

Native writes `bounding_radius` at `[esi+0x94]` before spilling the zero
counter to `[esp+0x10]`, finishing `bounds_min.z`, and testing
`vertex_count`. The candidate performs the same radius store immediately
after that independent compare. All subsequent loop semantics and the one
masked operand are exact. This is a single-function scheduler choice with no
call or shared definition at the boundary, so a TU would add no source
constraint and is not introduced.

## 2026-07-29 formal zero-store boundary

Three recorded sweeps extend that audit across every independent owner in the
opening schedule. Nine zero-order variants cover combined result/radius/offset
chains, separated declarations, and all ordinary store orders. Six are
byte-identical; the three forms that prevent the shared zero register regress
to 84.52%.

Fifteen signed/unsigned `int`/`long` combinations for the byte offset and
processed-vertex counter produce seven neutral and eight worse builds.
Unsigned counter ownership adds a second signedness mismatch without moving
the radius store. Six aggregate-bounds forms then cover direct member
assignment, references, named values, pointer declaration order, and const
pointer ownership. Three are neutral and two regress; the const-pointer form
is invalid because the recovered max/min pointers intentionally rebind during
the component updates.

Across 29 compilable unique variants, none improve: 16 are byte-identical and
13 regress. The three-sweep non-improvement streak formally stalls this lane
at **99.16%** (`119/119`, prefix 28, one clean reference). The only difference
remains the independent `bounding_radius = 0` store on opposite sides of the
counter spill/min-z completion/count test. Further work needs original compiler
provenance, not another zero chain, integer width, or aggregate owner spelling.

## 2026-08-11 aliasing-profile proof

The residual was a compiler-mode difference, not a missing source dependency.
VC6's `/Ow` cross-function-aliasing mode keeps the independent
`bounding_radius` store ahead of the count test. The retained source then
matches exactly: **100%**, `119/119` instructions, prefix `119`, and one clean
masked reference.

The result reproduces with the RTM, SP3, and canonical VC6 backends, isolating
the change to `/Ow`; no source scheduling dependency or volatile fake-match is
needed. `scratch.conf` now records that function's proved compiler mode.
