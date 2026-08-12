# Exact cRFace::AI

`0x441f60` is the authored `cRFace::AI()` callback.

Evidence:

- The Windows callback table at `0x4972f8` points directly to this method.
- Live Windows analysis gives a void `__thiscall` on the complete 0x128-byte
  owner and a single call to its embedded `cRMovie::AI()`.
- Android and iOS `SubGame.o` preserve the same owner, name, and behavior.
- VC6 emits `?AI@cRFace@@QAEXXZ`; the candidate matches all 19 instructions
  with two clean operands.

The inherited `BodBase::object` borrows the active SMTrack mesh. The method
advances the `cRMovie` at `+0x38`, installs its current `cRTexture*` on the
mesh's first facequad, then calls
`ObjectProcLandScapeUpdate(object, 0.0f, 5.0f, texture, false)` to resample the
retained image into the mesh vertex-height grid.

Windows independently proves `BodBase 0x38 + cRMovie 0xf0 = 0x128`; the wider
mobile object layouts are not imported.
