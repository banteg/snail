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
