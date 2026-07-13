# update_smtracks @ 0x441f60

Exact match: 19/19 instructions with two clean masked operands.

The receiver is the complete `0x128`-byte embedded SMTrack height-field
animator at `SubgameRuntime +0x10013a4`:

- inherited `BodBase::object +0x24` borrows the active SMTrack mesh;
- `FrameSequence +0x38` is an `Object`-derived animated texture sequence;
- the sequence publishes its current face's `TextureRef*` at outer `+0x124`;
- that texture is installed into the active mesh's first face and its retained
  TGA bytes are resampled into the mesh vertex-y lane.

`BodBase 0x38 + FrameSequence 0xf0 = 0x128`, ending exactly at the following
`SMTracks +0x10014cc`. The descriptive class name stays distinct from
the reported `0x25cfb4` native `cRSMTracks`/segment-catalog owner.

The 2026-07-13 owner-boundary pass replaced the enclosing runtime pad with
these two exact objects. A previewed Binary Ninja declaration preserved the
`0x128` animator, the following catalog address, and the complete
`0x1272838`-byte `SubgameRuntime`; the focused matcher remains byte-identical.
