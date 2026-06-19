# configure_sprite_render_state

Small sprite-renderer state mapper used only by `draw_sprite_quad`.

- `Sprite +0x28` is the sprite draw/render-state mode. The scratch keeps a
  narrow `SpriteRenderStateView` instead of including `sprite.h`: direct
  inclusion preserves the instructions but degrades the switch-table masked
  audit from 18 ok to 16 ok / 2 mismatch.
- The same switch-table audit issue happens if this scratch includes the shared
  `Direct3DDevice8` wrapper, so the device wrapper is kept local here even
  though `draw_sprite_quad` can use the shared view cleanly.
- Native modes `0`, `1`, `2`, `9`, `10`, and `13` program D3D render state
  `0x1b/0x13/0x14`; other modes return the mode unchanged.
- The native sparse switch lowers through a lookup table before the case jump
  table, so the repeated default path is intentional.
