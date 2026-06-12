# Native distance fog - 2026-06-12

Prompted by original-game screenshots of the level start where the ground
visibly "continues back" to the horizon, while the port shows the start
platform hard-cutting against the nebula backdrop.

## Geometry is identical; the difference is fog

Checked first whether the original renders any track geometry behind the
start. It does not:

- `get_track_runtime_cell_at_world_z` @ 0x43d480 clamps `(int)z < 0` to
  row 0; the runtime grid covers rows `0..runtime_row_count` only.
- `build_track_render_caches` @ 0x433220 emits one render-cache slot per
  24-row block at `block * 24`, block indices from the grid cell count —
  no slot before z 0.
- `initialize_start_path_template_pair` @ 0x426400 seeds the start-slide
  samples at local z `0..n` (5 flat at the top, the half-cosine drop, 11
  flat at the bottom) — no backward extension.
- The original's own Frida trace (`artifacts/frida/...152743...`)
  records `attachment_begin` kind 36 at `(0, 0, 4.0)`, row 4 — the same
  spawn the port uses (`starting_runtime_track_index = 4`). `START.TXT`
  gives the spawn ~4 rows of checkered pad behind it and nothing else.

## What the original actually does

`render_camera` @ 0x411fa0 sets up D3D linear fog for every gameplay
camera pass when the fog flag at `game + 0x4` is set:

- `SetRenderState(D3DRS_FOGENABLE (0x1c), 1)`
- `SetRenderState(D3DRS_FOGCOLOR (0x22), pack(game + 0x14), alpha 0)`
- `SetRenderState(D3DRS_FOGVERTEXMODE (0x8c), D3DFOG_LINEAR (3))`
- `SetRenderState(D3DRS_FOGSTART (0x24), game + 0x8)`
- `SetRenderState(D3DRS_FOGEND (0x25), game + 0xc)`
- `SetRenderState(D3DRS_RANGEFOGENABLE (0x26), game + 0x10)`

The fog color comes from the background script's `Fog:` line, parsed by
`load_landscape_script_by_name` @ 0x418440 (`BACKGROUNDS/SPACERED.TXT`
carries `Fog:(128,0,128)`; each component is scaled by 1/255).

With linear fog every 3D surface fades into the purple haze with
distance: the start pad's back edge, the track's far end, the side
edges, and the start gantry all dissolve into the fog color instead of
terminating in a crisp polygon edge. That is what reads as "the track
continues back" in the original captures — four rows of checkered pad
viewed at a grazing angle, fully fogged out before the edge.

The original click-to-start camera angles compound it: the original
idles in low, surface-grazing shots (side and centered low views) where
the platform fills the frame to the fogged horizon, while the port holds
a higher chase-style camera that looks down past the platform edge.

## Port status

Ported. The gameplay alpha-cutout shader pair (world-space batch
variant and `matModel` mesh variant in `gameplay/billboard.zig`) carries
the linear range-fog lanes; `viewport_render` seeds them per frame with
the native 30/50 start/end, the loaded background's `Fog:` color, and
the live camera position, enabled only while a runner is active. Track
surfaces, attachments, fringe, placed models, billboards, mesh actors,
and the barrier all take the fogged path; the 2D nebula backdrop and
HUD stay unfogged like native.

Remaining gap at the level start: the original's wide ground apron
around the start platform (visible in original captures between the pad
edge and the fog band) is separate geometry the port does not draw yet,
so the platform edge inside the fog-start radius still reads as a hard
line during the intro.
