# Original bugs

The shipped `SnailMail.exe` has a few behaviours that read as genuine bugs once
the recovered source shows how they arise. The port fixes them **by default**,
with no switch. The one large switch is [Mobile extras](README.md#enhancements),
for content backported from the Android release.

Each fix wraps the matched function (`port/wrapped.txt`) and lives in
`port/shell/fixes.cpp` or `port/shell/render_fixes.cpp`. The recovered source in
`decomp/` stays as the original compiled it. So far every fix changes only what is drawn, so the replay and
session oracles still match with the fixes in.

## 1) Slugs and garbage appear upright for a frame

Native behaviour:

- `cRSubGame::AddSlug` (`spawn_slug_hazard`, `0x43dc80`) and
  `cRSubGame::AddGarbage` (`spawn_track_garbage_hazard`, `0x43da80`) place the
  hazard on its cell and call `CalcRealPos`, which returns the track's tilt
  there as `attachment_facing_angle`. They then allocate the hazard's sprite
  but leave its `facing_angle` at the 0 that `cRSprite::Init` sets.
- The sprite only turns in the hazard's own update. `cRSlug::AI`
  (`update_slug_hazard_ai`, `0x43f930`) and `cRSubGarbage::AI`
  (`update_garbage_hazard`, `0x43f200`) set
  `facing_angle = heading_roll + attachment_facing_angle`, plus the player's
  `follow_state.orientation_b` while the player rides a path.
- A hazard spawns during `cRSubGame::AI`, after that tick's hazard updates have
  run, so the frame drawn on its spawn tick shows it upright. On the next
  tick it snaps to the track's angle.

Why it's a bug:

- The spawn code already has the angle, and every later frame uses it. Only the
  first frame draws the hazard upright.
- On flat track the angle is 0 and nothing shows. It shows where hazards spawn
  on tilted cells: `Angle=` segments, Wibble, and half-pipes. In Pro-Challenge's
  "Pros Only" (HalfPole, `Wibble.txt Angle=±30`), a slug at z 110.5 has a facing
  of 0 on its spawn tick and 0.196 from the next tick on.
- All four functions are byte-matched, so this is the original's code. Android's
  `cRSubGame::AddSlug` (`0007953c`) doesn't set the facing at spawn either.

Evidence: with `--trace`, the headless build prints `upright_hazards N`
whenever the number of active hazards drawn upright on a tilted cell changes.
Before the fix, replays A1, A3, A4 and A5 each showed such a hazard on three
spawn ticks. After it, none of the 20 replays does.

Port behaviour:

- `AddSlug` and `AddGarbage` run unchanged, then the wrapper gives the new
  sprite the facing its first update would give it.
- The facing is presentation only. Nothing in play reads it, and both oracles
  match (20/20 replays, 10/10 sessions).

## 2) Background streaks cut holes in the road

The starfield renders before the world, using `Sprites/StarTail.tga` in
`RENDER_SCENE_OVERLAY_1`. Its sprites sit 50 units from their camera, while
`render_camera` uses a far plane of 52. The recovered sprite draw inherits
enabled depth writes, so a streak can prevent the last two units of road
from rendering. The moving background then shows through the road horizon.

This was reproduced in the browser on Pro 1 (Pros Only), including its paused
view. A captured frame replay with streaks shifted across the horizon lost
31 road pixels at 640 by 480; suppressing only their depth writes restored
them. The foreground mailbox is nearer and is unaffected by this fix.

![The same road horizon with and without streak depth writes](images/starfield-depth.png)

The comparison replays the same captured scene and moves the captured streaks
across the horizon to hold the overlap fixed. Only their depth writes differ.

`port/shell/render_fixes.cpp` wraps `draw_sprite_quad` and suppresses depth
writes only for StarTail sprites in the background scene. It restores the
previous setting after each draw. The streaks still blend over the backdrop;
world geometry and foreground particles retain their depth writes. The fix
runs in the shared shell, so browser and native presenters receive the same
corrected state. Recovered source in `decomp/` is unchanged.

The matched Windows functions already contain the cause:
`initialize_star_field` (0x434310) puts the stars at distance 50;
`render_camera` (0x411fa0) enables depth writes with a far plane of 52;
`draw_sprite_quad` (0x4137f0) does not disable them. Their retained matching
receipts show 247/247, 180/180 and 259/259 instructions respectively. This
identifies a bug inherited from the shipped renderer; the visual reproduction
above was performed in the port, rather than the original Windows executable.

The runtime regression test drives the real browser WASM with both PC content
and mobile extras, checks all 36 background draws, and verifies that the world
and foreground draws following them still write depth.
