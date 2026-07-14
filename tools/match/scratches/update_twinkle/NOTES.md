# `update_twinkle` notes

- Twinkle records are 0x30 bytes, matching `update_twinkle_manager`.
- The borrowed owner is the containing `FrontendWidget`/authored `cRBorder`:
  `widget_flags` at +0x1a0, layout position at +0x238/+0x23c, and layout size
  at +0x248/+0x24c.
- Twinkles advance only while the owner is highlighted and does not carry
  `FRONTEND_WIDGET_FLAG_DISABLED`, matching the interaction update's dimmed,
  non-interactive disabled state.
- The function is modeled as `void`; native exits leave state-dependent scratch
  registers in `eax`.
- 2026-06-20 ABI cleanup: the `Twinkle` record now lives in
  `include/twinkle.h` with the exact 0x30 layout, `void update_twinkle()`, and
  the member `draw_twinkle()` call shape needed by this scratch. Focused matcher
  stayed exact at 181/181 instructions with 48 clean masked operands.

- 2026-07-14 draw-owner closure: the exact callee now defines
  `Twinkle::draw_twinkle()` directly. Android independently retains
  `cRTwinkle::Draw()`, confirming that the unused receiver is still an authored
  member rather than a free temporary-color helper.

## 2026-07-14 border owner recovery

The scratch-local `TwinkleOwner` shadow is retired. Its four observed field
groups already coincide exactly with the recovered 0x724-byte
`FrontendWidget`, and Android supplies the missing nominal evidence:
`cRTwinkleManager::Init(cRBorder*)` stores its `cRBorder*` argument into every
0x30-byte twinkle at `+0x2c`. `Twinkle::owner_widget` is therefore a borrowed
widget pointer, not an independent owner class. The typed member accesses keep
the Windows function exact at 181/181 instructions.
