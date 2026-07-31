# render_game_frame

Relationship-first scratch for the frame renderer at `0x40a490`.

Current Wibo result after the depth-node and replay-copy ownership replay:
67.28%, 429 candidate instructions versus 439 target instructions, with
a 6-instruction exact prefix, 34 masked operands ok, 0 unresolved, and 0
mismatch. The helper calls at `0x414650`, `0x413540`, `0x413650`, `0x411e10`,
and `0x411de0` resolve to standalone exact scratches.

The broader `GameRoot` remains sparse, but its renderer ownership window is now
shared: the skip counter, borrowed active-BOD head, and owned five-entry
viewport array are typed alongside `RenderCamera`, `Sprite`, `TransformMatrix`,
`tColour`, and the font queue.

Recovered relationships:

- `Game +0x56c` is a render-skip countdown; positive values decrement and
  return before any render state is touched.
- Five `Viewport` entries live at `Game +0x5b4`, are filtered by
  `flags & 1`, and each active slot controls a render-camera pass. The native
  fixed-five ordering loop is not a conventional insertion sort: the first
  active slot seeds the list, later slots are inserted only when their
  `sort_key` exceeds an occupied entry, and the shift always starts at slot 4.
- The borrowed `RenderCamera*` at `Viewport +0x20` inherits
  `RenderableBod`, so its world camera matrix is the inherited transform at
  `+0x38`; an 8-byte gap is followed by its view matrix at `+0x80`, float FOV
  in degrees at `+0xc0`, and render mask at `+0xc4`.
- `Game +0x5e4` is not a standalone renderer flag: it is
  `viewports[1].flags`, whose high render-mask byte is forced to
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
  `build_sprite_tail` for `SPRITE_FLAG_ORIENT_TO_MOTION` sprites before
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

- The compact native `0x80`-byte frame and its distinct staged, total-rendered,
  and replay ledgers are now reproduced without explicit stack aliasing. The
  remaining mismatch is compiler register scheduling across the camera,
  sprite, and replay lanes; the evidence-backed camera-order source shapes
  are formally bounded below.
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
their capacity and final index from `GameRoot::viewports`. The
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
`Viewport*` would require an overlapping anchor with false base
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
`void __thiscall build_sprite_tail(Sprite*, const TransformMatrix*)`.
These are ownership replays only: no matcher source or operand exception was
changed. The pre-biased camera-pass register remains intentionally unclaimed;
the distinct stack-backed `camera_order_cursor` is recovered below.

## 2026-07-18 frame-ledger and viewport-cursor source shape

The renderer now keeps the three native counters as separate source owners.
`post_sprite_count` counts only staged BODs, `rendered_bod_count` increments for
every accepted first-pass BOD, and `replay_count` snapshots the staged count.
Before reverse replay, the staged count clears and the snapshot is added to the
total ledger. This is the native control flow at `0x40a989..0x40a99f`, not a
synthetic alias introduced for code generation.

Removing the persistent local `Viewport*` and `RenderCamera*` views was
the complementary ownership correction. The authored expression indexes the
root-owned `viewports` array at each use; VC6 consequently selects
the native camera index in `EBX` and keeps `EBP` as the pre-biased containing-
root cursor (`game + camera_index * 0x28`). The real ledgers then fit in the
native `0x80` frame without overlap tricks. The two fixed-five scans use
separate scoped induction variables because VC6 retains `for` declarations to
the enclosing scope.

Focused Wibo rises from 45.43% (`415/439`, prefix 3) to 56.22% (`429/439`,
prefix 6), with all 26 masked operands clean and no unresolved or mismatched
operands. A bounded probe that replaced the insertion `break` with
`insert = ordered_count` reached 439 candidate instructions but reduced the
honest similarity and destabilized unrelated register allocation; reversing
the Sprite/depth-node declaration order also regressed. Both were rejected
instead of retaining instruction-count padding.

Binary Ninja now persists the exact compiler-split staged, total-rendered,
rendered-sprite, camera-order-cursor, and remaining-camera locals. A proposed
user override for the depth-node allocator was rejected after a reversible
preview proved that it erased the independently recovered `Sprite*` chain.
The IDA replay now loads its rich Object and canonical BOD dependencies before
the narrow frame header and invalidates only the owned renderer caches, so the
tracked `Object::animation` relationship cannot remain hidden behind stale
pseudocode.

## 2026-07-24 cRViewport owner naming

The root array and renderer expressions now use `viewports`, matching the
retained Android/iOS `cRViewport` class rather than the provisional
render-camera-slot label. Each viewport owns its ordering, render flags,
normalized rectangle, and draw-world state while borrowing one
`RenderCamera*` at `+0x20`. This relationship-only source change preserves the
current 56.16% renderer match and does not guess the constructor-only
`unknown_1c` lane.

## 2026-07-27 direct camera-matrix borrow

The verified Android and iOS `cRGame::Render()` bodies both copy each live
sprite position and transform it directly with the selected viewport camera's
view matrix. The scratch now spells that same borrowed relationship directly
instead of materializing a decompiler-invented `camera_matrix` local. The
cross-port bodies also retain the authored `gBodZList`, `ZBuffer`, and
`ZBufferIndex` symbols for the post-sprite stack, depth-node workspace, and
bucket heads, independently confirming the three Windows global roles.

This ownership correction is codegen-neutral under VC6: focused Windows stays
at the honest 56.16% result (`430/439`, prefix `6/439`, 28 clean masked
operands, 12 unaudited). The remaining renderer gap is still register
allocation and platform-specific viewport scheduling, not an excuse to add
aliases or synthetic locals.

## 2026-07-30 camera-order source-shape boundary

The target keeps zero in `ESI` from the skip check through the initial sprite
ledger store and later reuses that register for the ordered-camera count.
Android and iOS independently retain the same active-slot scan and insertion
exit: after insertion they assign the scan index from the incremented ordered
count, then execute the common loop increment. These observations motivated
three recorded mutation sweeps rather than speculative aliases.

The complete 32-variant boundary covers:

- three earlier ordered-count declaration lifetimes around the matrix and
  rendered-sprite ledger;
- five sentinel/array initialization spellings, three active-slot traversal
  forms, and all 15 two-site interactions between them;
- indexed and explicit-cursor outer scans, `for` and `do` inner scans, the
  retained `break`, the mobile common-increment exit, and the mobile comparison
  spelling.

None improves the clean 56.16% baseline. All five sentinel spellings are
byte-identical; the best explicit cursor form loses eight weighted bytes, the
earlier count lifetimes lose thirteen, and the mobile insertion exits lose
between 28 and 146. The append-only `experiments.jsonl` therefore reports
`0/5/27` better/same/worse variants and a three-sweep stalled streak. The
mobile control flow remains valuable provenance, but forcing it into the
Windows scratch destabilizes the broader VC6 allocation and is not an honest
match improvement.

## 2026-07-31 depth-node and replay-copy ownership

The native sprite insertion allocates its current depth node before entering
the bucket branches: it snapshots the workspace cursor and advances that
cursor by one `0x18`-byte node immediately after loading the selected bucket.
The scratch previously mutated the cursor only after filling the node, which
kept the allocator in a register and distorted the entire insertion lane.
Spelling the recovered event as `node = next_depth_node++` raises focused Wibo
from 56.16% to 63.51% (+107.37 weighted bytes), with the same six-instruction
prefix and all 34 operands clean. Its three post-increment/split-increment
spellings are byte-identical; the retained form follows native evaluation
order.

Two smaller native control relationships compound that ownership correction.
Scoping `previous` and `cursor` under the non-empty head guard adds 6.75
weighted bytes, and testing the non-null previous node before the head-replace
case adds another 6.75. The insertion lane consequently reaches 64.43%
without casts, duplicated tests, or instruction-count padding.

The post-sprite replay also uses a transient `Vector3` value before copying
the staged BOD position into the reusable transform. This matches the native
stack copy and the mobile replay's temporary position owner; the former three
component stores were a decompiler-shaped spelling unique to the scratch.
Retaining the copied value restores two candidate instructions and adds 41.57
weighted bytes. The focused renderer now reaches 67.28%, 429/439
instructions, prefix 6, with 34/34 clean resolved operands.

Eight new recorded sweeps cover 32 unique variants. Six replay-ledger orders,
six legal current-body owner splits, and six workspace-acquisition spellings
are byte-neutral; initializing the node before the sprite regresses by 164
weighted bytes. Three base-prefix/derived-body splits remain neutral both
before and after the copied position is introduced. The complete renderer
ledger now contains 11 sweeps and 64 unique variants, with four newly retained
source-shape wins and no experiment errors.

## 2026-07-31 conditional replay reset and frame-tail owner

The native first pass tests the selected viewport's world-render bit before
clearing the post-sprite BOD count. Android and iOS preserve the same
relationship: their `gBodZList` count is reset only inside the branch that
walks the active BOD list. Moving the Windows reset into that branch restores
the native two stack-backed counter owners, the saved `GameRoot` slot, and the
first-pass store order. Focused Wibo rises from 67.28% to 68.20%, adding 13.45
weighted bytes and bringing the candidate from 429 to 432 instructions against
439 native.

The final folded call at `0x407b50` is likewise a global frame-tail callback,
not `GameRoot::noop_runtime_ai()`. Native does not establish `this` in ECX,
and both mobile renderers end through the global `G0RenderEnd()` surface.
Spelling the global qualification removes the false receiver setup and raises
the focused score again to 68.28%. It also removes one instruction, so the
ledger records the honest instruction-count tradeoff rather than hiding it;
the ABI and target callsite evidence justify retaining the source correction.

A final two-variant probe wrapped the non-empty depth bucket in a redundant
inner cursor guard to explain native's repeated null test. VC6 removes both
ordinary spellings and emits the current bytes, so no volatile owner or
duplicated condition is retained. The complete ledger now contains 14 sweeps
and 68 unique variants: 12 improve, 26 are neutral, 30 regress, and the
trailing no-improvement streak is one. The focused candidate is 431/439
instructions, prefix 6, with all 34 masked operands clean.

## 2026-07-31 post-reset dependency replay bounded

The conditional reset changed the renderer's stack and register allocation, so
the four earlier ownership grids that cross that frame boundary were replayed
once against the 68.28% frontier. All 35 variants compile with clean
references and none improves:

- the exact indexed mobile insertion exit now comes within 0.24 weighted byte
  of the retained camera loop, but remains lower;
- all three branch-local base/derived BOD reloads are byte-identical;
- moving the ordered-count lifetime earlier loses 6.71 weighted bytes; and
- five sentinel initializations remain neutral while the three explicit active
  camera traversals lose between 7.66 and 104.05 weighted bytes.

The native six-instruction camera-exit residual and replay-branch reload
therefore do not transfer as isolated source owners even after the accepted
frame change. The ledger now contains 18 sweeps and 103 unique variants:
12 improve, 34 are neutral, and 57 regress. Five consecutive non-improving
sweeps formally stall the function at **68.28%**, 431/439 instructions,
prefix 6/439, and 34 clean masked operands.
