# rotate_object_facequad_uv_pairs

`rotate_object_facequad_uv_pairs @ 0x430a30` is the small fastcall helper used
by `initialize_backdrop_tile_quad` orientation cases. It rotates the four
`ObjectFaceQuad::uv` pairs forward by one slot:

- `uv[0] <- uv[1]`
- `uv[1] <- uv[2]`
- `uv[2] <- uv[3]`
- `uv[3] <- old uv[0]`

The helper sits between `calc_object_edges @ 0x4308b0` and
`request_object_animation @ 0x430a70`; splitting it out explains the six
previous unresolved calls from the backdrop tile scratch.

Current focused result:

- match: 100.00%
- target/candidate instructions: 17 / 17
- prefix: 17 / 17
- masked operands: none

Source-shape notes:

- The target uses `ecx` as the only argument, matching a fastcall/thiscall-style
  helper over one `ObjectFaceQuad*`.
- MSVC keeps `uv[0].u` live on the x87 stack while rotating the four U values
  through integer moves, then repeats the same pattern for V. Straight scalar
  assignments over `quad->uv[N].u/v` reproduce that schedule exactly.

## 2026-07-17 named fastcall owner replay

The function is now a first-class tracked artifact and both databases pin
`void __fastcall(ObjectFaceQuad*)`. That replaces the anonymous integer
receiver/return view and lets the tile builder call the named UV owner directly.
The 17/17 matcher remains byte-identical.
