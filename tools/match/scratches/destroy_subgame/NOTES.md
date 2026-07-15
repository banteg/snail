# destroy_subgame

Exact scratch for the subgame teardown helper at `0x438850`.

Match status: 100% (`246/246` target instructions, `41` masked operands, no
unresolved or mismatched operands).

Recovered behavior:

- emits the stripped `"-SubGame::UnInit()\n"` debug report and marks the
  frontend/subgame bridge dirty byte at `app+0x4f26c`;
- if the level mode is tutorial (`7`), calls
  `Tutorial::uninit_tutorial()` at `game+0xa858`;
- always uninitializes the embedded player warning, the complete landscape
  manager's ten active entries, authored `TimesUp`, and the broader subgame BOD set through
  `SubgameRuntime::remove_subgame_bods()`;
- for every non-state-1 teardown, removes active BOD nodes from the embedded
  20-slot SubLazer pool, 40-slot Salt pool, and two-slot start/completion
  `BannerPool`; row-event display is additionally flushed for modes `0`/`1`;
- removes the embedded tutorial `BarrierActor` at `game+0xff7bc4` when linked;
- kills the gameplay HUD widgets at `game+0x35bb88/8c`, clears persistent
  selected-record state, restores frontend state `0x12` for persistent record
  teardown, and sets selected subgame mode `2` when destroying mode `3`;
- in postal mode (`level_mode == 0`), kills the extra two score widgets plus
  the nine lives/widgets starting at `game+0x35bb98`.

The repeated pool loops use a `BodNode::list_next` cursor because native
iterates from the `+0x0c` link field, loading flags from `-0x08` and prev from
`-0x04`. The removal body still mirrors
`BodList::recycle_bod_to_free_list`, but this function inlines it for each
pool and for the barrier actor.

## 2026-07-10 ownership audit

The exact initializer and actor update helpers disambiguate two formerly
misnamed teardown ranges. `game+0x359080` is a fixed pair of 0x60-byte
`cRBanner` actors whose `+0x54` fields borrow the embedded player as their row
position source; these are not the ring/effect parents at `game+0x35b78c`.
Likewise, `game+0xff7bc4` is the 0x3c-byte `cRBarrier` actor with a borrowed
player pointer at `+0x38`; the adjacent selected-level replay bytes at
`+0xff25d0/+0xff25d1` do not own that BOD.

`SubgameRuntime` now exposes those actors and the teardown's other fixed pools
as embedded storage. The global BOD list only links the embedded nodes while
live, and `destroy_subgame` recycles their links without freeing object
storage. HUD fields remain borrowed `BorderManager` handles and are returned
through `kill_border()`. Focused Wibo remains exact at `246/246` with all 41
masked operands resolved.

The same lifetime rule applies to the adjacent path-template bank at
`SubgameRuntime +0xff2914`: `destroy_subgame` does not destruct its 63 embedded
pairs or free their sample/mesh allocations. Those are game-runtime assets
created after the tracked allocation mark and released together by
`free_tracked_allocations_to_mark` during main-loop shutdown.

## 2026-07-11 cRCompletion owner

The mode-0/1 teardown now calls
`SubgameRuntime::completion.flush_row_event_display()` directly. Mobile symbols
name the exact callee `cRCompletion::UnInit()`, and its 0x50-byte owner ends
exactly at `times_up`. The old independent row-event controller view is
retired; the teardown remains exact at 246/246 with all 41 operands clean.

The adjacent tail call now resolves to the primary
`SubgameRuntime::times_up.uninit_times_up()` owner. Android retains the exact
callee as `cRTimesUp::UnInit()`; the code remains exact.

Tutorial-mode teardown likewise reaches the primary embedded `Tutorial`.
Android/iOS retain the exact three-instruction thunk as
`cRTutorial::UnInit()`; the complete 0x1c owner ends at `SubTracks` with no
wrapper padding. The teardown remains exact.

## 2026-07-13 root teardown owners

The inlined unlink blocks now borrow `GameRoot::active_bod_list`, HUD handles
return through `GameRoot::border_manager`, and the persistent-replay exit state
lands in `players[0].saved_frontend_state`. The mode-3 teardown write now names
`g_game->subgame.level_mode`: changing it to `this->level_mode` removes a
native game-base reload and regresses the object, proving the root-owned alias
is part of the original source shape. The retained form stays exact at 246/246
with all 41 operands clean.

The opening teardown latch at root `+0x4f26c` is also inside the exact
`GameRoot::backdrop` extent, at `Backdrop +0x65c`. Its semantics remain
unproven, so the shared field stays honestly named `unknown_65c`; naming the
owner is codegen-neutral and does not invent a role.

## 2026-07-14 pool-stride ownership

The two remaining literal pool advances now derive from `sizeof(SubLazer)`
and `sizeof(Salt)`, agreeing with their complete embedded manager layouts.
The exact function remains 246/246 with all 41 operands clean.

The next-link cursor's `-8/-4/-0xc` spellings remain intentional. Replacing
them with equivalent `offsetof(BodNode, ...)` expressions changes VC6's live
mask choice (`0x200` versus `~0x200`) and regresses the function to 76.70%.
The shared `BodNode` ownership is proven, but forcing the prettier expression
would discard the exact native source-shape evidence.

## 2026-07-14 fixed-array counts

The SubLazer, Salt, Banner, and postal life-stock loops now derive their counts
from their embedded arrays. Together with the existing `sizeof(SubLazer)`,
`sizeof(Salt)`, and `sizeof(Banner)` cursor steps, teardown no longer duplicates
the `20/40/2/9` owner extents in executable source. The function remains exact
at 246/246 instructions with all 41 masked operands clean.

## 2026-07-14 analysis receiver closure

The live Binary Ninja `Game*` receiver was the same stale named-type identity
seen on the initializer, not a distinct aggregate. The guarded catalog repair
recreated only this exact function as a `SubgameRuntime*` method, preserved its
sole user-defined receiver, and saved after verified readback. Its tracked
decompile falls from 28 raw receiver-offset expressions to none and now exposes
the player warning, landscape manager, completion display, embedded hazard
pools, barrier, HUD widgets, and replay teardown lane directly.

The saved IDA receiver lvar now agrees with its already-correct prototype, so
the tracked Hex-Rays artifact also contains no `int this` arithmetic. No matcher
source changed: teardown remains exact at 246/246 with all 41 operands clean.
