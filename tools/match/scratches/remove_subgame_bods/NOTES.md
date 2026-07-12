# `remove_subgame_bods` recovery notes

Target: `SubgameRuntime::remove_subgame_bods @ 0x440910` (`thiscall`, 1644 bytes, 501 instructions).

Initial scratch reconstructs the full cleanup pass:

- 3200 runtime rows, each clearing one row BOD node and eight track-cell sub-lazer/fringe bodies;
- track render cache BOD removal;
- health, speedup, jetpack, garbage, slug, and ring/special-effect runtime slots;
- the singleton player/score/body nodes around `game+0x3bb764`, `game+0x3be0e8`, `game+0x3bf2c8`, and `game+0x3be734`;
- three helper-driven `BodList::recycle_bod_to_free_list` calls;
- the Golb shot cleanup loop and final game-sprite purge.

The inline teardown sites now route through the proven `BodList::remove_bod`
owner method; the three native out-of-line sites continue to call
`recycle_bod_to_free_list`.

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
  owned by `SubgameRuntime::player`.
- `Player +0xa0` is the exact embedded `ClickStart` (`cRClickStart`), with its `state` lane at
  `Player +0x120`. The initializer now uses that typed view. A typed spelling of
  the final teardown branch regressed to `59.18%`, so the scratch retains the
  native-shape raw loads there and records the ownership in `player.h`.
- Focused Wibo improves from `59.90%` (`494/501`, `58 ok`) to `59.98%`
  (`496/501`, `59 ok`). The two pre-existing speedup/jetpack string-order
  mismatches remain; no new masked-operand issue was introduced.
- The runtime-grid promotion now spells the opening teardown cursors as
  `runtime_cells[0][0]` and `runtime_rows[0].row_model.list_next`. Focused
  Wibo remains `59.98%`, cross-confirming that the row body is embedded in the
  fixed row slab while only its intrusive list membership is recycled.

2026-07-11 speedup ownership: the first singleton teardown arm is now backed by
the primary `SubSpeedUp` owner at `+0x355db0`; its storage remains embedded
while only inherited BOD-list membership is recycled. The existing 59.98%
frontier and two speedup/jetpack string-order mismatches remain unchanged.

2026-07-11 JetPack ownership: the second singleton teardown arm is backed by
the primary `JetPack` owner at `+0x355e64`; only its inherited BOD membership
and sprite are released, while the parent and two embedded cRVapour objects
remain owned by `SubgameRuntime`. The 59.98% frontier is unchanged.

## 2026-07-12 shared list-owner recovery

The repeated row, pickup, hazard, ring, player, and presentation teardown
blocks do not own their unlink algorithm. Each embedded record remains stored
inside `SubgameRuntime`; its containing `BodNode` is merely lent to the global
`BodList`, whose inline `remove_bod` method owns active-list unlinking and the
free-stack push. Replacing both hand-expanded macros with that shared method
also preserves the required early exits after either list diagnostic.

Focused Wibo rises from 59.98% (496/501, 59 clean operands) to **67.67%**
(495/501, 63 clean operands). The two existing speedup/JetPack string-order
mismatches remain alignment fallout from their combined register allocation;
the source strings and owner paths themselves are correct. Hoisting the row
lane counter and expanding the shared method again are codegen-neutral or
regressive, so the remaining receiver/counter register rotation is left
visible rather than forced.

## 2026-07-13 embedded pool and Player-bank closure

- Health, garbage, slug, and ring teardown cursors now start from their owned
  `SubgameRuntime` arrays, and their inactive writes name each slot's `state`.
  The speedup and JetPack singleton state clears use their embedded owners too.
- The final projectile loop is `player.golb_shots`: 12 complete `GolbShot`
  records at `Player +0x450`, ending exactly at the next Player field at
  `+0x2730`. The same bank is constructed during runtime-pool initialization
  and scanned by movement-flag emission.
- The remaining tail names `player.movement_mode_selector` and the embedded
  `player.click_start` body/state instead of reaching through SubgameRuntime
  offsets. Intrusive-list removal still borrows only their `BodNode` prefixes.
- These owner substitutions are codegen-neutral: focused Wibo remains 67.67%
  with 495/501 instructions, 63 clean operands, and the same two documented
  string-order mismatches.
