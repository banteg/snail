# update_track_render_cache_rows @ 0x433b30

Initial relationship-first scratch for the track-render-cache row activator called
only by `update_subgame` after the forward runtime-row scan.

Evidence:

- Native `update_subgame` calls this helper with `game + 0x5c`, the same
  `SegmentCache` base used by `rebuild_track_runtime_from_segments`
  and `remove_track_render_cache_bods`.
- The function compares `g_game_base + 0x42fdec + 46.0f` against manager
  `+0xa7f0`, then advances `+0xa7f0` by `24.0f` and increments `+0xa7f4`.
  The old BN-only names `scratch_max_vertices` / `scratch_max_indices` were
  therefore wrong; these are now `next_cache_row_z` and
  `next_cache_row_index`.
- The repeated slot blocks link `BodBase` nodes into sentinel-style active
  lists at `g_game_base + 0x3ca1b4` for Floor/Slide/Warn/Ramp and
  `g_game_base + 0x3ca17c` for Fringe, reporting `"List ADDafter"` if the
  slot is already live.
- The exact source shape reloads the main active list for each slot block and
  uses short-lived `TrackRenderCacheSlot*` / `Vector3*` views. Keeping the main
  active list across the four non-fringe slots pushed the live mask into `ebp`;
  reloading it per block keeps native `ebx = 0x200` and `edi = 0`.

Match status:

- 2026-06-18: 100.00%, 227/227 instructions, 27 masked operands all resolved.
- 2026-07-11: promoted the exact 0xa7f8-byte receiver to the authored
  `SegmentCache` / cRSegmentCache owner. The method remains exact at 227/227
  with all 27 operands clean.

## 2026-07-14 draw-list and player owner closure

The two root-relative list anchors are embedded `SubgameRuntime` owners:
`+0x355b64` is `fringe_attachment_list_head`, used only by the Fringe cache
family, and `+0x355b9c` is `track_body_list_head`, used by Floor, Slide, Ramp,
and Warn. The row activation threshold at root `+0x42fdec` is the embedded
player's `position.z`, and the skirt color comes from the same subgame owner.

All accesses retain the native independent `g_game` reloads while following
the canonical `GameRoot -> SubgameRuntime` graph. The method remains exact at
227/227 instructions with all 27 operands clean.

## 2026-07-18 cross-tool owner graph

Address-anchored IDA replay now preserves the exact `SegmentCache*` receiver
and the full `GameRoot -> SubgameRuntime` owner graph in the checked-in
artifact. The activation threshold names the embedded player's `position.z`;
Fringe links through `fringe_attachment_list_head`, the other four families
link through `track_body_list_head`, and skirt color is borrowed from the same
subgame. These are decompiler ownership improvements only: the scratch remains
exact at 227/227 instructions with all 27 operands clean.

## 2026-07-23 durable cache-row borrow lifetimes

The guarded Binary Ninja replay now preserves 22 physical lifetimes across the
five family activation blocks. `SegmentCache` remains the sole owner of its
143-by-5 embedded `TrackRenderCacheSlot` grid; each block temporarily borrows
the selected complete slot, its `Vec3` position, its `tColour`, and the
root-owned `BodNode` draw-list sentinel. The Fringe block also names the
stack-backed skirt-color result and the returned `tColour*` borrow.

This resolves each three-component position clear to one typed `Vec3` memset,
keeps intrusive-list accesses under `TrackRenderCacheSlot -> BodBase ->
BodNode`, and removes the false `BodBase*` view of the list sentinels. Binary
Ninja may inline the short-lived slot/position/color locals into those owner
expressions, but their user-variable types are retained and replayed.

Native computes the 300-byte row stride through multiply/add stages. Those
registers remain integers: typing any scaled offset as a slot pointer would be
fakematching. A second replay is fully idempotent. Matcher source is unchanged
and remains proof-grade at **100.00%**, 227/227 instructions, with all 27
masked operands clean.
