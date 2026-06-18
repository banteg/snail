# reset_subgame

First relationship scratch for the subgame runtime reset helper at `0x437b10`.

Recovered behavior:

- clears the eight health pickup slots, two singleton pickup runtimes, the
  fifty garbage slots, eight slug slots, and two ring/special-effect parents;
- preserves/restores the saved run score/timer snapshot when the replay/restore
  byte is armed and the current level mode matches the saved level mode;
- otherwise clears score buckets for mode `2`, zeros the live timer counters,
  and clears the two saved score/timer tail fields;
- re-arms the two live subgame bytes, clears the replay/restore byte, and
  resets the active garbage chain head.

The scratch still uses raw dword lanes for the unresolved score/timer snapshot
band, but it now relies on the shared `Game` declaration for the recovered
pickup and hazard pool band.

Current focused result:

- 100.00%, 75/75 instructions, prefix 75/75
- masked comparison: 2 ok, 0 unresolved, 0 mismatch

Important source-shape correction:

- The saved timer snapshot copy must be spelled as C-linkage intrinsic
  `memcpy`. A manual six-dword copy regressed the function to 35.06% by keeping
  `this` in `esi`; a plain declared `memcpy` regressed to 30.07% by emitting a
  real call. `extern "C"` plus `#pragma intrinsic(memcpy)` recovers the native
  `push esi; push edi; mov ecx, 6; rep movsd` block and the `ebp` owner
  register.

2026-06-18 signature correction:

- The native function is void-shaped. The old `int result` source was a
  decompiler artifact from the leftover `eax` value and made VC6 hoist the saved
  tail-b load before tail-a.
- Spelling the helper as `void Game::reset_subgame()` removes the artificial
  return-value dependency and matches the native saved snapshot load order:
  score, tail-a, tail-b.
- Focused Wibo is now 100.00%, 75/75 instructions, with 2 clean masked
  operands.
- Binary Ninja readback now reports the member-shaped prototype
  `void __thiscall(struct Game* game)`.

2026-06-18 pool naming correction:

- `Game` now carries the contiguous subgame pool band:
  `speedup_pickup`, `jetpack_pickup`, `health_pickups[8]`, `slug_slots[8]`,
  `sub_lazer_pool[20]`, `salt_pool[40]`, `garbage_hazards`, and
  `ring_effects`.
- The health pickup `+0x44` field is `owner_game`, not a visibility/source
  cell. `reset_subgame` writes the containing `Game*` into this lane for all
  eight health slots; the spawned row source remains `source_cell +0x68`.
- A broad BN header import preview still disturbed existing shared structs, so
  the sync script declares only the tiny `TrackHealthPickupGameView` type when
  missing and field-sets the recovered names without reimporting `Sprite`,
  `TrackRowCell`, or `Player`.
