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
