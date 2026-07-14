# render_game_frame

Relationship-first scratch for the frame renderer at `0x40a490`.

Current Wibo result after the renderer control-flow and ownership slice: 45.43%,
415 candidate instructions versus 439 target instructions, with 26 masked
operands ok, 0 unresolved, and 0 mismatch. The helper calls at `0x414650`, `0x413540`,
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
  `flags & 1`, and each active slot controls a render-camera pass. The native
  fixed-five ordering loop is not a conventional insertion sort: the first
  active slot seeds the list, later slots are inserted only when their
  `sort_key` exceeds an occupied entry, and the shift always starts at slot 4.
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
- `BOD flags & 0x80` stages the object for the post-sprite pass without
  suppressing its first-pass render. Non-staged BODs do not increment the
  post-sprite stack count.
- Sprite rendering uses `g_sprite_active_heads[camera_index]`, checks the
  sprite and camera high render-mask bytes, depth-sorts visible sprites into
  the `data_4f7050` bucket heads with nodes from `data_4e5510`, then calls
  `update_sprite_facing_angle` for `flags & 2` sprites before `draw_sprite_quad`.
- Sprite projection negates camera-space z for storage, then negates it again
  when building the depth key before multiplying by `4.19672108f` and adding
  `Sprite +0x98`.
- Sprite depth sorting caches the selected depth bucket at `Sprite +0x14` and
  the computed float depth key at `Sprite +0x18`; the projected depth also adds
  the sprite-local `depth_bias` at `+0x98`.
- Sprite depth projection uses the affine by-value `multiply_vector_by_matrix`
  path, not the rotation-only helper.
- The queued font/textured-quad pass is inside the camera slot and is gated by
  `draw_font_text_queue(slot->flags)` after the sprite pass.
- Post-sprite BODs are staged in the `data_4dfb10` pointer stack and rendered
  after a second `render_camera(..., post_sprite_pass=1)` call.
- The sprite-depth workspace is shared ownership rather than a local view:
  `g_sprite_depth_nodes` is exactly 3000 contiguous `0x18`-byte nodes from
  `0x4e5510` through `0x4f6e50`, matching `SpriteManager::sprites[3000]`, and
  `g_sprite_depth_buckets` is exactly 256 pointer heads through `0x4f744c`.
- BN decompilation of `render_camera` confirms its ninth argument is stored to
  `g_object_render_pass_filter` (`data_503260`). The first camera call passes
  `0`; the post-sprite replay call passes `1`, so the two render-frame calls
  are the producer side of the object texture-group pass filter consumed by
  `render_object`.

Expected residuals:

- The native function has a compact `0x80`-byte frame with several overlapping
  locals. In particular, it keeps a rendered-BOD total in the setup-index
  stack lane, increments it after every accepted first-pass BOD, and adds the
  replay count before draining the post-sprite stack. A separately named local
  expands the candidate frame to `0x84`, so this honest partial leaves the
  unused ledger out instead of introducing explicit stack aliasing.
- The BOD prefix through `RenderableBod +0x78` is now shared through
  `bod_types.h` and the existing `BodNode`/`ContactTargetObject` prefix: signed
  flags, list links, position, render-object pass-through arguments, object,
  color, and optional embedded transform. The cast-only renderer view adds only
  the animation-manager binding used by flagged Snail/weapon owners at `+0x78`.
- The five renderer state wrapper calls are named through exact standalone
  scratches; remaining work is the larger frame/register/data-owner shape.
- The native method is void. The only caller ignores its result, the positive
  skip path returns after decrementing the countdown, the no-camera path joins
  the common tail, and iOS independently names the method `cRGame::Render()`.
  The void `GameRoot` declaration and BN/IDA prototypes now agree.

2026-07-10 viewport/camera closure: startup attaches the two cameras embedded
at `Game +0x1c4/+0x3bc` to viewport slots 1 and 4. iOS independently names the
pair `cRViewport::SetCamera(cRCamera*)` and `cRViewport::cRViewport()`. Promoting
that borrowed pointer and the owning GameRoot viewport array is codegen-neutral:
 focused Wibo remains the honest 35.31%, 422/439, with 21 clean masks.

The enclosing owner is now closed as well: those two camera sources are the
owned `camera +0xa0` subobjects of consecutive `GamePlayer`/`cRPlayer` records
at root `+0x124/+0x31c`. Viewports borrow the adjusted subobject pointers; the
players and ultimately `GameRoot` retain lifetime ownership.

2026-07-11 root BOD-list closure: `GameRoot +0x5a8` is now the complete owned
`BodList`, not padding followed by a borrowed head pointer. This renderer walks
its `first +0x04` member at root `+0x5ac`; `update_salt_hazard` independently
proves the same object's active/free-list behavior. The relationship-only
change is codegen-neutral: focused Wibo remains `35.31%`, `422/439`, with `21`
clean masked operands.

2026-07-11 renderer closure: correcting staged-BOD first-pass behavior, the
double-negated sprite depth key, branch order for embedded transforms, the
out-of-line sprite-mask error path, linked-list insertion invariants, native
fixed-five camera ordering, and the void common tail raises focused Wibo from
`35.31%` to `45.43%`. The candidate remains an honest partial at `415/439`
instructions with `26` clean masked operands and no unresolved or mismatched
operands.

2026-07-13 animation-progress ownership closure:

- The old local `texture_owner` / `texture_sink` names were wrong. Windows
  copies `AnimManager::progress +0x04` from the flagged BOD's borrowed manager
  pointer at `+0x78` into `Object::animation->progress +0x0c` before drawing.
- Exact `cRSubGoldy::Init` installs that pointer as the address of the manager
  owned by `cRSnail +0x104` or `cRWeapon +0x108`; it also installs each
  manager's target-model backlink and owned animation-slot bank.
- Android `cRGame::Render()` independently performs the same chain using its
  port-specific offsets (`cRBod +0x6c -> cRAnimManager +0x04` and
  `cRObject +0x104 -> cRObjectAnim +0x10`). This proves the relationship rather
  than merely renaming the Windows operands.
- Replacing three opaque texture views with `AnimManager`, `Object`, and
  `ObjectAnimation` is codegen-neutral. Focused Windows remains the honest
  45.43%, 415/439 instructions, prefix 3, with all 26 operands clean.

2026-07-14 Snail renderable inheritance: the flagged presentation node is now
declared as an actual `RenderableBod` subclass. The renderer's borrowed
transform, object, flags, color, and animation-manager chain therefore traverse
one canonical owner. Focused output remains byte-identical at 45.43%, 415/439
instructions, prefix 3, with all 26 operands clean.

2026-07-14 animation-channel renderable inheritance: weapon and jetpack
channels now reach the renderer through canonical `RenderableBod` inheritance,
matching the existing Snail path. Their inherited transform/object/color and
derived animation-manager backlink form one typed chain. Focused output remains
byte-identical at 45.43%, 415/439 instructions, prefix 3, with all 26 operands
clean.
