# border_sprite_extend @ 0x404540

Exact authored `FrontendWidget`/`cRBorder` helper for the contextual extended
sprite lane.

- Stores the first, third, and second texture arguments at widget
  `+0x60/+0x64/+0x68`, respectively, then enables the lane at `+0x5c` and
  records the wobble direction at `+0x5d`.
- Clears the shared target, idle, and hot padding fields at
  `+0x21c/+0x214/+0x218`.
- `initialize_frontend_widget` calls it as `(44, 43, 45, 1)` for the slider's
  more button and `(40, 39, 41, 0)` for the less button. Draw consumes `+0x60`
  as the hot texture, while exact hit-test code consumes `+0x64` as the texture
  mask; the `+0x68` consumer is still unresolved.
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
