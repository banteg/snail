# calc_object_bounding_box

Object bounds pass at `0x42fb10`.

- Confirms `Object +0x38` is the `Vector3* vertices` array.
- Confirms `Object +0x94` is the maximum vertex magnitude used as a bounding
  radius.
- Confirms `Object +0xa4..+0xaf` is the minimum xyz bound and
  `+0xb0..+0xbb` is the maximum xyz bound.
- Current source is relationship-first, not proof-grade: the remaining mismatch
  is the min-bound pointer/offset register allocation and x87 compare spelling,
  not the recovered field layout.
