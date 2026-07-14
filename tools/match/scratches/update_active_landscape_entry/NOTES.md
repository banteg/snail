# update_active_landscape_entry @ 0x418ac0

Exact match: 41/41 instructions, clean masks.

`update_active_landscape_entry` is the active background/landscape slice
updater. It skips while `GameRoot::subgame.subgame_pause_gate` is set, then only
runs state `1`.

Recovered layout:

- `ActiveLandscapeEntry` extends `RenderableBod`; the repeated z offset is the
  inherited `transform.position.z` at `+0x70`.
- `+0x80` state
- `+0x88` repeat z span
- `+0x8c` reference BOD pointer; `reference_bod->transform.position.z` is the
  live source z used for wrapping and visibility.
- object bounds are `Object::bounds_min.z` / `Object::bounds_max.z` at
  `+0xac/+0xb8`.

The visibility bit is `list_flags & 0x20`.

Correction made while matching: `+0x8c` is not a raw `TransformMatrix*`.
Native reads the source z at `reference + 0x70`, which is
`RenderableBod::transform.position.z`.

The state gate is a label-shaped switch (`case 0/default` to the shared return
label, `case 1` to the active body). That preserves VC6's native
`sub eax, 0; je; dec eax; jne` dispatch without adding dummy arithmetic.

2026-07-11 pause-owner closure: removing the synthetic root-wide pause view is
codegen-neutral. Focused Wibo remains exact at 41/41 instructions with clean
masks.

2026-07-14 object/root closure: the updater now borrows the retained `Object*`
directly, reads the canonical bounds members, and reaches the pause gate and
fog-end plane through `GameRoot`. Retiring the duplicate bounds type preserves
the exact 41/41 instructions and all four operands.
