# update_active_landscape_entry @ 0x418ac0

Exact match: 41/41 instructions, clean masks.

`update_active_landscape_entry` is the active background/landscape slice
updater. It skips while the global pause gate at `Game+0x74621` is set, then
only runs state `1`.

Recovered layout:

- `ActiveLandscapeEntry` extends `RenderableBod`; the repeated z offset is the
  inherited `transform.position.z` at `+0x70`.
- `+0x80` state
- `+0x88` repeat z span
- `+0x8c` reference BOD pointer; `reference_bod->transform.position.z` is the
  live source z used for wrapping and visibility.
- object bounds use object `+0xac` / `+0xb8` as min/max z.

The visibility bit is `list_flags & 0x20`.

Correction made while matching: `+0x8c` is not a raw `TransformMatrix*`.
Native reads the source z at `reference + 0x70`, which is
`RenderableBod::transform.position.z`.

The state gate is a label-shaped switch (`case 0/default` to the shared return
label, `case 1` to the active body). That preserves VC6's native
`sub eax, 0; je; dec eax; jne` dispatch without adding dummy arithmetic.
