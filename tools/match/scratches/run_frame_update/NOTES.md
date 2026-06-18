# run_frame_update

Source-shaped scratch for the frame update loop at `0x40a2a0`.

Current match: 97.78% (`135/135` candidate instructions, 23 masked
operands ok). Remaining differences are local scheduling/argument evaluation:
the target prepares the mouse-state `this` pointer one instruction earlier, and
pushes the cursor draw layer before evaluating the `Color4f::set_color_rgba`
argument.

Rejected/neutral probes:

- Inlining `color.set_color_rgba(...)` as the queue-call argument matched the
  target's layer-before-tint evaluation order, but grew the stack frame and
  regressed the function to 75.74%.
- Naming the mouse-state pointer is source-legible but codegen-neutral; the
  target still schedules the `lea ecx, [this+0x290]` before the float store.

The main Sprite evidence is the active-bucket traversal:

- starts at `g_sprite_active_heads`;
- walks each `Sprite::next` chain while saving `next` before `update_sprite`;
- increments a local sprite update counter;
- stops by signed pointer comparison against `&g_sprite_free_head`.

This mirrors the exact `kill_game_sprites` bucket topology but calls
`Sprite::update_sprite` instead of conditionally killing `0x800` sprites.

## Type consolidation (2026-06-17)

`MouseCursorState` and `FrontendOverlayColorLerp` now live in shared headers.
`run_frame_update`, `is_mouse_captured`,
`release_mouse_cursor`, `resolve_uncaptured_cursor_sensitivity_scale`, and
`initialize_frontend_overlay_color_lerp` all keep their previous focused match
results with those headers.

Two mouse callsites remain local on purpose: `uninit_pause_menu` declares
`release_mouse_cursor` as returning `int` to preserve the native tail-return
shape, while `update_frontend_state_machine` keeps the compact
`capture_mouse_cursor` declaration because including the full header dirties
the jump-table/global masked operand audit without improving structure.

2026-06-18 cheat header cleanup: `CheatState` is now shared with
`initialize_cheat`, `match_cheat_text`, and `update_cheat`. Focused Wibo remains
pinned at 97.78%, 135/135 instructions, with the same mouse-state/tint
argument scheduling residuals and 23 clean masked operands.
