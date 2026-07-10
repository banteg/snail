# `remove_subgame_bods` recovery notes

Target: `SubgameRuntime::remove_subgame_bods @ 0x440910` (`thiscall`, 1644 bytes, 501 instructions).

Initial scratch reconstructs the full cleanup pass:

- 3200 runtime rows, each clearing one row BOD node and eight track-cell sub-lazer/fringe bodies;
- track render cache BOD removal;
- health, speedup, jetpack, garbage, slug, and ring/special-effect runtime slots;
- the singleton player/score/body nodes around `game+0x3bb764`, `game+0x3be0e8`, `game+0x3bf2c8`, and `game+0x3be734`;
- three helper-driven `BodList::recycle_bod_to_free_list` calls;
- the Golb shot cleanup loop and final game-sprite purge.

This scratch intentionally uses the proven inline intrusive-list removal shape from `destroy_subgame` and `remove_track_render_cache_bods` rather than introducing a new helper abstraction.

2026-06-19 focused result: 59.90%, 501 target instructions vs 494 candidate
instructions, 6-instruction prefix, 58 masked operands ok, 0 unresolved, 2
masked string-order mismatches.

The best shape uses cursor loops from the BOD `list_next` lane rather than
typed owner arrays:

- row loop starts at `game+0x5ccad8` and advances by `0xf4`;
- health loop starts at `game+0x35600c` and advances by `0x74`;
- garbage loop starts at `game+0x359150` and advances by `0xc4`;
- slug loop starts at `game+0x3563ac` and advances by `0xec`;
- ring/special-effect loop starts at `game+0x35b798` and advances by `0x1f8`.

Remaining allocator problem: native keeps the row `TrackRowCell` cursor in
`edi`, then reloads `this` into `ebx` after the track-render-cache call and
uses `ebp` as zero. The scratch keeps the row cursor in `ebx`, reloads `this`
into `ebp`, and hoists `~0x200` into `ebx` for later list-flag clears. That
cascades into the speedup/jetpack singleton block layout and produces the two
masked string-order mismatches:

- target `0x440a82` is `"List remove NEXTBOD"`, but the aligned candidate push
  is `"List remove"`;
- target `0x440af3` is `"List remove"`, but the aligned candidate push is
  `"List remove NEXTBOD"`.

Rejected probes:

- Initial typed owner-loop version: 46.54%, 52 masked operands ok, 0 unresolved,
  0 mismatched, but too much topology remained unrecovered.
- A zero-aware list-removal macro preserved the 59.90% score but did not fix
  the string-order audit and added misleading clutter.
- Reordering the first row cursor declarations, adding `register` to the row
  cell cursor, and keeping an explicit `zero` local did not change the final
  allocator shape.

## 2026-07-10 teardown ownership pass

- Recovered the missing call at `0x440f0f`: after unlinking the embedded Player
  and its presentation bodies, native invokes the `Player +0x000` teardown
  hook before killing the twelve embedded Golb shots. Windows folds that hook
  to the shared one-byte `noop_runtime_ai @ 0x407b50` stub; the receiver and
  position in the teardown sequence establish its lifecycle role even though
  the body is empty.
- Player, presentation, jetpack channel, three weapon channels, and invincible
  shell removals are now expressed as embedded subobjects. Their intrusive BOD
  nodes are returned to the shared free list, but their backing storage remains
  owned by `SubgameRuntime::player_storage`.
- `Player +0xa0` is an embedded `ClickStartController`, with its `state` lane at
  `Player +0x120`. The initializer now uses that typed view. A typed spelling of
  the final teardown branch regressed to `59.18%`, so the scratch retains the
  native-shape raw loads there and records the ownership in `player.h`.
- Focused Wibo improves from `59.90%` (`494/501`, `58 ok`) to `59.98%`
  (`496/501`, `59 ok`). The two pre-existing speedup/jetpack string-order
  mismatches remain; no new masked-operand issue was introduced.
- The runtime-grid promotion now spells the opening teardown cursors as
  `runtime_cells[0][0]` and `runtime_rows[0].primary_body.list_next`. Focused
  Wibo remains `59.98%`, cross-confirming that the row body is embedded in the
  fixed row slab while only its intrusive list membership is recycled.
