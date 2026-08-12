# Exact cRSnail::BuildHotSpots

`0x445cd0` is the authored `cRSnail::BuildHotSpots()` method.

Evidence:

- Live Windows analysis gives a void `__thiscall` on the complete Snail owner;
  its sole caller is the exact per-frame `cRSnail::AIGoldy()` method.
- Android `SubGame.o` preserves the exact owner, name, and 19-element transform
  pass.
- VC6 emits `?BuildHotSpots@cRSnail@@QAEXXZ`; the candidate matches all 44
  instructions with its operand clean, while the 339-instruction caller also
  remains exact.

The method transforms `snail_hotspots_local[19]` at `+0x16cc` into
`snail_hotspots_world[19]` at `+0x17b0`. Weapon hotspots `0..10` use
`snail_hotspot_body.transform` at `+0x1684`; parcel, camera, jetpack, and base
hotspots `11..18` use `snail_hotspot_source_body.transform` at `+0x1604`.
The world bank feeds cutscene consumers, including camera anchors at slots 12,
17, and 18.

Exact source-shape constraints retained by the matcher:

- a plain indexed loop keeps the native index and world cursor allocation;
- each local vector and selected 0x40-byte matrix is copied by value before
  `tVector::operator*=`;
- the source matrix switches at `SNAIL_HOTSPOT_PARCEL_POINT` (11).

Windows independently proves the two complete `cRBodPos` source owners and
both 19-vector banks; mobile object offsets are not transferred.
