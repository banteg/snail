# update_smtracks / cRFace::AI() @ 0x441f60

Exact match: 19/19 instructions with two clean masked operands.

The receiver is the complete `0x128`-byte Windows `Face` owner
(`cRFace` on Android/iOS) embedded at `cRSubGame +0x10013a4`:

- inherited `BodBase::object +0x24` borrows the active SMTrack mesh;
- `Movie +0x38` is the `Object`-derived authored `cRMovie`;
- the sequence publishes its current face's `TextureRef*` at outer `+0x124`;
- that texture is installed into the active mesh's first face and its retained
  TGA bytes are resampled into the mesh vertex-y lane.

`BodBase 0x38 + Movie 0xf0 = 0x128`, ending exactly at the following
`SMTracks +0x10014cc`. The authored `Face` class stays distinct from the
reported `0x25cfb4` native `cRSMTracks`/segment-catalog owner.

The 2026-07-13 owner-boundary pass replaced the enclosing runtime pad with
these two exact objects. A previewed Binary Ninja declaration preserved the
`0x128` animator, the following catalog address, and the complete
`0x1272838`-byte `cRSubGame`; the focused matcher remains byte-identical.

## 2026-07-16 frame/sampler handoff closure

- Both analysis databases now receive the authored
  `void Face::update_smtracks()` receiver rather than a
  raw integer base. The complete handoff reads as
  `Face -> Movie -> TextureRef -> borrowed Object`.
- The sole sampler call proves
  `void sample_smtrack_heightmap(Object*, float, float, TextureRef*, bool)`;
  the old analysis prototype incorrectly modeled its fourth argument as a
  float and promised an unused pointer result.
- The exact 19/19 body and both operands remain unchanged. Paired strict export
  now contains no raw `+0x38`/`+0x124` reconstruction or result forwarding.

## 2026-07-27 authored cRFace owner

The expanded Android and iOS corpora independently retain this exact method as
`cRFace::AI()`. Both bodies advance the embedded `cRMovie` sequence, install
its current `cRTexture*` on the borrowed object's first face, and call
`ObjectProcLandScapeUpdate(object, 0.0f, 5.0f, texture, false)`. That is the
same complete call chain as the exact Windows body.

The descriptive `SmtrackHeightfieldAnimator` type is therefore retired in
favor of the authored `Face` owner. Windows independently proves its
`BodBase + Movie` layout and exact 0x128-byte extent; the wider mobile
`cRBod + cRMovie` offsets are not imported. The Windows table at `0x4972f8` is
now named `g_face_callback_table`, with the old SMTracks label retained only as
an alias. Focused matching remains exact at 19/19 instructions with both
operands clean.
