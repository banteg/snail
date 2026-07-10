# render_game_frame

Relationship-first scratch for the frame renderer at `0x40a490`.

Current Wibo result after the renderer-helper slice: 35.31%, 422 candidate
instructions versus 439 target instructions, with 21 masked operands ok, 0
unresolved, and 0 mismatch. The helper calls at `0x414650`, `0x413540`,
`0x413650`, `0x411e10`, and `0x411de0` now resolve to standalone exact
scratches.

The broader `GameRoot` remains sparse, but its renderer ownership window is now
shared: the skip counter, borrowed active-BOD head, and owned five-entry
viewport array are typed alongside `RenderCamera`, `Sprite`, `TransformMatrix`,
`Color4f`, and the font queue.

Recovered relationships:

- `Game +0x56c` is a render-skip countdown; positive values decrement and
  return before any render state is touched.
- Five `RenderCameraSlot` entries live at `Game +0x5b4`, are filtered by
  `flags & 1`, insertion-sorted by `sort_key`, and each active slot controls a
  render-camera pass.
- The borrowed `RenderCamera*` at `RenderCameraSlot +0x20` inherits
  `RenderableBod`, so its world camera matrix is the inherited transform at
  `+0x38`; an 8-byte gap is followed by its view matrix at `+0x80`, float FOV
  in degrees at `+0xc0`, and render mask at `+0xc4`.
- `Game +0x5e4` is not a standalone renderer flag: it is
  `render_camera_slots[1].flags`, whose high render-mask byte is forced to
  `0x02` before the passes.
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
- BN decompilation of `render_camera` confirms its ninth argument is stored to
  `g_object_render_pass_filter` (`data_503260`). The first camera call passes
  `0`; the post-sprite replay call passes `1`, so the two render-frame calls
  are the producer side of the object texture-group pass filter consumed by
  `render_object`.

Expected residuals:

- The native function has a compact 0x80-byte frame with several overlapping
  locals; this first scratch favors named relationships over stack-slot
  mimicry.
- The BOD prefix through `RenderableBod +0x78` is now shared through
  `bod_types.h` and the existing `BodNode`/`ContactTargetObject` prefix: signed
  flags, list links, position, render-object pass-through arguments, object,
  color, and optional embedded transform. `RenderBodView` remains local only for
  the renderer-specific pointer at `+0x78` and the unknown tail.
- The five renderer state wrapper calls are named through exact standalone
  scratches; remaining work is the larger frame/register/data-owner shape.

2026-07-10 viewport/camera closure: startup attaches the two cameras embedded
at `Game +0x1c4/+0x3bc` to viewport slots 1 and 4. iOS independently names the
pair `cRViewport::SetCamera(cRCamera*)` and `cRViewport::cRViewport()`. Promoting
that borrowed pointer and the owning GameRoot viewport array is codegen-neutral:
 focused Wibo remains the honest 35.31%, 422/439, with 21 clean masks.

The enclosing owner is now closed as well: those two camera sources are the
owned `camera +0xa0` subobjects of consecutive `GamePlayer`/`cRPlayer` records
at root `+0x124/+0x31c`. Viewports borrow the adjusted subobject pointers; the
players and ultimately `GameRoot` retain lifetime ownership.
