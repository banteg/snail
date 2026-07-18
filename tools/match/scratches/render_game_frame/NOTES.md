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
`tColour`, and the font queue.

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
  `update_sprite_facing_angle` for `SPRITE_FLAG_ORIENT_TO_MOTION` sprites before
  `draw_sprite_quad`.
- The renderer admits only `SPRITE_FLAG_ACTIVE | SPRITE_FLAG_RENDER_ENABLED`
  sprites and excludes `SPRITE_FLAG_DELAYED_RENDER`; exact initialization and
  update functions independently prove the producer side of all three bits.
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
- The complete BOD prefix through `RenderableBod +0x7f` is now shared through
  `bod_types.h` and the existing `BodNode`/`ContactTargetObject` prefix: signed
  flags, list links, position, render-object pass-through arguments, object,
  color, transform, the conditional animation-manager binding at `+0x78`, and
  the still-unknown final word at `+0x7c`. No renderer-only derived view is
  needed.
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

## 2026-07-14 camera-slot extent derivation

The two viewport scans, local order buffer, and insertion-sort tail now derive
their capacity and final index from `GameRoot::render_camera_slots`. The
manual five-store buffer initialization remains intact because it is part of
the accepted VC6 source shape; only duplicated extent literals are removed.
The normalized candidate listing remains byte-identical
(`df9e91e723f12aeabea17578a3fae2b3fbba67527c0495eb46e00cd56a17b8c6`)
at the honest 45.43% focused result (`415/439`, prefix `3/439`, 26 clean
operands).

## 2026-07-14 complete RenderableBod extent

The generic active-list traversal itself reads `BOD +0x78` under the `0x800`
render-sync flag, while exact Snail and weapon setup install their self-owned
`AnimManager` pointers in that lane. Every known Windows renderable child
starts its own state at `+0x80`; Android preserves the same conditional lane at
`cRBod +0x6c` and starts ClickStart state at `+0x74`, exactly 0x0c bytes earlier.
The canonical Windows `RenderableBod` is therefore 0x80 bytes, not a 0x78-byte
prefix followed by repeated child padding. Promoting the borrowed manager and
unknown `+0x7c` word into the base removes the local renderer subclass and all
known duplicated child gaps. Focused output remains byte-identical at 45.43%,
415/439 instructions, prefix 3, with all 26 operands clean.

## 2026-07-14 vector operator ownership

Sprite depth projection now spells the existing by-value affine call as the
recovered void `Vector3::operator*=`. Focused output remains at the prior honest
45.43% baseline; only the decorated call identity changes, and the function
reference alias keeps all 26 operands clean.

## 2026-07-14 BOD render-flag ownership

The render traversal now names the independently proved BOD flag contract:
`HAS_OBJECT`, `RENDER_ENABLED`, and the shared high-byte scene mask gate entry;
`AFTER_SPRITES` stages the replay pass; `SYNC_ANIMATION` borrows the embedded
manager; and `USE_TRANSFORM` selects the full matrix path. The same shared word
also carries the diagnostic bit consumed by both `cRGame::AI()` and
`cRGame::Render()`. Exact constructors/setters and the exact after-sprites
helper prove the producer side. Focused output remains the honest 45.43%,
415/439 result with all 26 masked operands clean.

The high byte is now owned separately as `RenderSceneFlag`: startup binds the
five bits to three overlays and two player camera slots, while this method uses
`RENDER_SCENE_MASK` identically for BOD, sprite, and queued-text selection.
This broader owner replaces the temporary BOD-local viewport naming without
changing the focused result.

## 2026-07-16 render-policy propagation

The remaining recovered BOD producers and consumers now use the same render
policy names: fringe, landscape, banner, intro-logo, and shell lifecycles own
`BOD_FLAG_RENDER_ENABLED`; attachment scheduling produces
`BOD_FLAG_AFTER_SPRITES`; and this post-sprite replay consumes
`BOD_FLAG_USE_TRANSFORM`. Exact constructors, the exact after-sprites query,
and both render passes already prove those meanings. Replacing the residual
raw constants leaves the full matcher board unchanged.

## 2026-07-18 sprite render-workspace ownership

The renderer's active-list source and temporary depth nodes now preserve the
canonical sprite owner end to end. `g_sprite_active_heads` is the exact
five-pointer alias at `SpriteManager +0x83d64`, not independent storage, and
each `SpriteDepthNode +0x14` borrows the selected `Sprite*`. The frame replay
only forward-declares `Sprite`, then requires the complete sprite lane to be
exactly 0xb4 bytes before applying that relationship; it cannot replace the
owner with a renderer-local projection.

The camera-pass register remains intentionally raw. Native code keeps
`game + camera_index * 0x28`, a pre-biased containing-root cursor, then reaches
the slot at `+0x5b4`. Treating that register as either `GameRoot*` or
`FrameRenderCameraSlot*` would require an overlapping anchor with false base
semantics. The replay therefore persists the real slot layout but does not
fakematch the compiler cursor.

The generic root `BodList` remains a `BodNode*` anchor because insertion and
recycling operate only on the intrusive header. Render performs an explicit
zero-offset cast of the borrowed head to `RenderableBod*` before reading the
body, transform, object, and animation-manager fields. Both replay lanes now
persist that local cast and name `g_post_sprite_bods` as the base of the
transient `RenderableBod*` staging stack. Only the first pointer type is
claimed because no independent bound for that stack has been recovered yet.

The bucket insertion and drain lanes now keep their borrowed owners through
both decompilers as well. Binary Ninja's `bucket_node` is the exact register
loaded from `g_sprite_depth_buckets[index]`; IDA's `depth_bucket_cursor` walks
the same 256-head array and its local `sprite` is the `Sprite*` borrowed from
`SpriteDepthNode::sprite`. The exact 100% `draw_sprite_quad` scratch proves the
`int __cdecl draw_sprite_quad(Vec3*, Sprite*)` helper ABI, while the sprite
member declaration and call convention prove
`void __thiscall update_sprite_facing_angle(Sprite*, const TransformMatrix*)`.
These are ownership replays only: no matcher source or operand exception was
changed, and the camera cursor remains intentionally unclaimed.
