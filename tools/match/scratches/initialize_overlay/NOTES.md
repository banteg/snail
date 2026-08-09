# initialize_overlay @ 0x40a240

Initializes a complete root-owned `cROverlay`:

- the inherited `RenderableBod::transform` is at overlay `+0x38`;
- an embedded `RenderCamera` begins at overlay `+0x80`, placing its inherited
  transform at `+0xb8`, view matrix at `+0x100`, FOV at `+0x140`, and overlay
  rotation alias at `+0x144`;
- `rotation_step` is the final word at `+0x148`, closing the object at `0x14c`.

The rotation starts at zero, advances by `0.00036547193f`, and the embedded
camera starts at `38.0f` FOV.

Focused match: 100%, 17/17 instructions, with three clean masked operands.
The `cROverlay` layout is shared in `include/overlay.h`; its narrow Binary Ninja
companion exposes the same nested fields in the live decompile.

Android retains the lifecycle member as `void cROverlay::Init()` with the same
zero rotation, `0.00036547193f` step, identity transforms, 38-degree FOV, and
inverse-view initialization. No matching iOS Init export survives, so Android
confirms the Windows owner without transferring its platform layout.

2026-08-09 primary owner promotion: the matcher now emits the exact no-argument
member as `cROverlay::Init()` and binds its owner-qualified VC6 spelling
`?Init@cROverlay@@QAEXXZ`. `Overlay` remains a compatibility typedef for the
tracked analyzer vocabulary. Live Windows xrefs prove exactly three calls from
root initialization, at `0x40ae73`, `0x40b067`, and `0x40b113`, corresponding
to the consecutive owners at `GameRoot +0x67c/+0x914/+0x7c8`. The ownership
spelling is codegen-neutral and keeps the exact 17/17 stream with all three
masked operands clean.
