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

## 2026-07-26 cross-port member recovery

Android and iOS both export the exact-demangled
`cRFaceQuad::RotateUVCCW()` method, and both bodies perform the same four-pair
rotation as Windows. The canonical source is therefore now an authored
`ObjectFaceQuad` member rather than a merely thiscall-shaped free helper.
Member spelling remains exactly 17/17 with no masked operands, and propagating
it through all six calls in `initialize_backdrop_tile_quad` leaves that caller
exactly 367/367 with all 63 operands clean.

The repeatable Binary Ninja and IDA contracts now use the ABI-equivalent
`void __thiscall(ObjectFaceQuad*)` signature. The existing Windows function
name is retained as the matching identifier while the mobile symbols preserve
the original `RotateUVCCW` provenance.

## 2026-07-29 primary cRFaceQuad ownership

The matcher now promotes the shared authored owner itself: `struct cRFaceQuad`
is the primary 0x30-byte Windows face record, `ObjectFaceQuad` is retained only
as an analyzer-facing compatibility typedef, and the exact body is emitted as
`cRFaceQuad::RotateUVCCW()`. Binary Ninja confirms six ECX-receiver callsites,
all in `initialize_backdrop_tile_quad`; replaying those calls through the
authored member preserves the callee at 17/17 instructions and the caller at
367/367 with all 63 operands clean.
