# initialize_overlay @ 0x40a240

Initializes a complete root-owned `Overlay`:

- the inherited `RenderableBod::transform` is at overlay `+0x38`;
- an embedded `RenderCamera` begins at overlay `+0x80`, placing its inherited
  transform at `+0xb8`, view matrix at `+0x100`, FOV at `+0x140`, and overlay
  rotation alias at `+0x144`;
- `rotation_step` is the final word at `+0x148`, closing the object at `0x14c`.

The rotation starts at zero, advances by `0.00036547193f`, and the embedded
camera starts at `38.0f` FOV.

Focused match: 100%, 17/17 instructions, with three clean masked operands.
The `Overlay` layout is shared in `include/overlay.h`; its narrow Binary Ninja
companion exposes the same nested fields in the live decompile.
