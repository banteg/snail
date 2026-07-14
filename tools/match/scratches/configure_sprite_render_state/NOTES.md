# configure_sprite_render_state

Small sprite-renderer state mapper used only by `draw_sprite_quad`.

- `Sprite +0x28` is the sprite draw/render-state mode. The exact helper and its
  exact `draw_sprite_quad` caller now share the canonical `Sprite*` contract.
- The Direct3D device and vtable calls use the shared
  `Direct3DDevice8` wrapper.
- Native modes `0`, `1`, `2`, `9`, `10`, and `13` program D3D render state
  `0x1b/0x13/0x14`; other modes return the mode unchanged.
- The native sparse switch lowers through a lookup table before the case jump
  table, so the repeated default path is intentional.

## 2026-07-14 Sprite owner recovery

The previous scratch-local `SpriteRenderStateView` was not a distinct runtime
owner; it was a prefix-only workaround for an older jump-table audit issue.
Retesting the complete shared `Sprite` owner now preserves the exact 109/109
instruction stream and all 18 audited operands. The function declaration also
lives in `sprite.h`, so the renderer caller and implementation can no longer
drift to incompatible parameter types.
