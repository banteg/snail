# render_game_frame

Relationship-first scratch for the frame renderer at `0x40a490`.

Current Wibo result after the renderer-helper slice: 35.31%, 422 candidate
instructions versus 439 target instructions, with 21 masked operands ok, 0
unresolved, and 0 mismatch. The helper calls at `0x414650`, `0x413540`,
`0x413650`, `0x411e10`, and `0x411de0` now resolve to standalone exact
scratches.

This is deliberately not a promoted `GameRoot` or renderer layout yet. The
scratch keeps the large game owner as raw offsets while using established
shared views for `RenderCameraSlot`, `Sprite`, `TransformMatrix`, `Color4f`,
and the font queue.

Recovered relationships:

- `Game +0x56c` is a render-skip countdown; positive values decrement and
  return before any render state is touched.
- Five `RenderCameraSlot` entries live at `Game +0x5b4`, are filtered by
  `flags & 1`, insertion-sorted by `sort_key`, and each active slot controls a
  render-camera pass.
- The camera source pointer at `RenderCameraSlot +0x20` has a matrix at `+0x38`,
  an 8-byte gap, a second matrix at `+0x80`, and a camera mode lane at `+0xc0`.
- `Game +0x5e4` has its high render-mask byte forced to `0x02` before passes.
- `Game +0x5ac` is the active BOD/render object list walked before sprites
  unless the slot has `flags & 2`.
- `BOD flags & 0x400` selects the embedded transform at `+0x38`; when clear,
  the renderer builds a temporary transform from the position at `+0x10`.
- `BOD flags & 0x80` stages the object for the post-sprite pass; immediate BODs
  do not increment the post-sprite stack count.
- Sprite rendering uses `g_sprite_active_heads[camera_index]`, checks the
  sprite and camera high render-mask bytes, depth-sorts visible sprites into
  the `data_4f7050` bucket heads with nodes from `data_4e5510`, then calls
  `update_sprite_facing_angle` for `flags & 2` sprites before `draw_sprite_quad`.
- Sprite depth sorting caches the selected depth bucket at `Sprite +0x14` and
  the computed float depth key at `Sprite +0x18`; the projected depth also adds
  the sprite-local `depth_bias` at `+0x98`.
- Sprite depth projection uses the affine by-value `multiply_vector_by_matrix`
  path, not the rotation-only helper.
- The queued font/textured-quad pass is inside the camera slot and is gated by
  `draw_font_text_queue(slot->flags)` after the sprite pass.
- Post-sprite BODs are staged in the `data_4dfb10` pointer stack and rendered
  after a second `render_camera(..., post_sprite_pass=1)` call.

Expected residuals:

- The native function has a compact 0x80-byte frame with several overlapping
  locals; this first scratch favors named relationships over stack-slot
  mimicry.
- The BOD prefix through `RenderableBod +0x78` is now shared through
  `bod_types.h`: list links, position, render-object pass-through arguments,
  object, color, and optional embedded transform. `RenderBodView` remains local
  only for the renderer-specific pointer at `+0x78` and the unknown tail.
- The five renderer state wrapper calls are named through exact standalone
  scratches; remaining work is the larger frame/register/data-owner shape.
