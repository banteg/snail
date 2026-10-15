# Original bug: background streaks cut holes in the road

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
