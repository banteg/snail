# border_sprite_extend @ 0x404540

Exact authored `FrontendWidget`/`cRBorder` helper for the contextual extended
sprite lane.

- Stores the first, third, and second integer arguments at widget
  `+0x60/+0x64/+0x68`, respectively, then enables the lane at `+0x5c` and
  records the wobble direction at `+0x5d`.
- Clears the shared target, idle, and hot padding fields at
  `+0x21c/+0x214/+0x218`.
- `initialize_frontend_widget` calls it as `(44, 43, 45, 1)` for the slider's
  more button and `(40, 39, 41, 0)` for the less button. Draw consumes `+0x60`
  as the hot texture, while exact hit-test code consumes `+0x64` as the texture
  mask. The retained second argument at `+0x68` has no Windows image consumer;
  it must not be assigned a texture role from its adjacency alone.
- Promoting the method from a duplicate scratch-local class to the shared
  `FrontendWidget` owner remains instruction-exact at `14/14` with no masked
  operands.
- Android preserves this owner as
  `cRBorder::SpriteExtend(int, int, int, bool)` and performs the same three
  texture stores, enable/wobble byte stores, and three zero clears. Both
  Windows callers discard EAX; the zero retained there is the source for the
  three stores, not a result contract. The corrected `void` member remains
  exact at 14/14 instructions.

## 2026-07-15 persisted member ABI

The rollback-safe Binary Ninja replay now applies and independently verifies
the authored `void cRBorder::SpriteExtend(int, int, int, bool)` contract on a
typed `FrontendWidget*` receiver. IDA carries the same argument ownership. The
exact 14/14 scratch remains unchanged with no masked operands.

## 2026-08-09 Windows retained-state closure

Full-image Binary Ninja field xrefs distinguish all three adjacent stores:

- `FrontendWidget +0x60` has the producer at `0x404548` and the draw read at
  `0x4013bd`;
- `FrontendWidget +0x64` has the producer at `0x40454f` and the mouse-mask read
  at `0x404608`; and
- `FrontendWidget +0x68` has exactly one unique code reference, the producer
  store at `0x404556`, with no data references.

Complete disassembly checks of `draw_frontend_widget`, `border_mouse_test`, and
`update_frontend_widget_interaction` independently find no receiver-relative
`+0x68` read. The only adjacent consumer operands are `[esi+0x60]` in draw and
`[ecx+0x64]` in hit-test. Android `cRBorder::SpriteExtend(int, int, int, bool)`
corroborates that the helper preserves three integer arguments, but supplies no
consumer or semantic role for the third stored lane on Windows. Treat `+0x68`
as retained, write-only platform state until a consumer appears in another
artifact; do not infer a texture purpose from the mobile producer or the two
neighboring texture fields.

The focused Windows scratch remains exact at 14/14 instructions, full prefix,
with no masked operands.
