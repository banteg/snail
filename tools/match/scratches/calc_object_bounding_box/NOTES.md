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
