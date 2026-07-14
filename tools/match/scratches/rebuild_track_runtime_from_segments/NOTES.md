# Exact match

`rebuild_track_runtime_from_segments` is the compact bridge from selected
level mode/index into the runtime track rebuild pipeline. It stores the level
argument, applies mode features, rebuilds cells/parcels/tile variants/warnings
and fringe objects, then refreshes render caches with the current track skirt
color.

The exact source shape has two important call ownership details:

- `build_track_colours` is a `Game` member call, so VC6 reloads `ecx` with
  the saved game pointer between the first two rebuild calls.
- `get_track_skirt_color` returns the filled `tColour*`; passing
  `*resolved_color` by value into `build_track_render_caches` reproduces the
  native 16-byte stack argument copy before the render-cache call.

The color query now names the root-owned `GameRoot::subgame` receiver rather
than reconstructing it from `root + 0x74618`. Focused matching remains exact.

## Authored owner hierarchy (2026-07-14)

Cross-port symbol and body evidence identifies this exact Windows dispatcher as
`cRSubGame::GenerateLevel(int)`, not an unnamed normalization helper. Android
stores the incoming level argument and calls `SetFeatures`, `BuildColours`,
`BuildLevel`, `PlaceParcels`, `SmoothTrack`, `WarnTrack`, `SlideSmoothTrack`,
`CondenseTrack`, and `FringeEdgeTrack` in the same nested order. Windows adds
its platform-specific tile-promotion and render-cache calls around that shared
pipeline. The callee at `0x435eb0` is therefore authored `BuildLevel()`, while
the outer caller at `0x437eb0` is authored `StartLevel(int)`.
