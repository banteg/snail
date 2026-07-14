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

The exact scratch now consumes the canonical `SubgameRuntime` owners for every
touched pool and for the replay snapshot handoff into the embedded `Player`.
No fixed dword indices remain.

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
- Spelling the helper as `void SubgameRuntime::reset_subgame()` removes the artificial
  return-value dependency and matches the native saved snapshot load order:
  score, tail-a, tail-b.
- Focused Wibo is now 100.00%, 75/75 instructions, with 2 clean masked
  operands.
- Binary Ninja readback is now directly typed as `SubgameRuntime`; the old
  root-`Game` and pickup-only owner views were stale import artifacts.

2026-06-18 pool naming correction:

- The subgame runtime carries the contiguous subgame pool band:
  `speedup_pickup`, `jetpack_pickup`, `health_pickups[8]`, `slug_slots[8]`,
  `sub_lazer_pool[20]`, `salt_pool[40]`, `garbage_hazards`, and
  `ring_effects`.
- The health pickup `+0x44` field is `owner_game`, not a visibility/source
  cell. `reset_subgame` writes the containing subgame owner into this lane for all
  eight health slots; the spawned row source remains `source_cell +0x68`.
- Pickup and slug `owner_game` backlinks now point directly to the containing
  `SubgameRuntime`. Its `subgame_pause_gate +0x09` remains distinct from the
  global/UI pause gate at root `Game +0x74621`.
- A broad BN header import preview still disturbed existing shared structs, so
  the sync script field-sets the recovered names on the existing
  `SubgameRuntime` without reimporting `Sprite`, `TrackRowCell`, or `Player`.

2026-07-11 cRSubHealth ownership: the exact eight-record backlink loop now
lands on the primary `SubHealth` array at `+0x356000`. It writes the containing
runtime to each borrowed `owner_game +0x44` lane while leaving the spawned
`source_cell +0x68` distinct. The function remains exact at 75/75.

2026-07-11 cRSubSpeedUp ownership: the singleton backlink store now lands on
the primary `SubSpeedUp::owner_game +0x8c` lane at runtime `+0x355e3c`.
Together with the exact constructor and AI table, this closes the complete
0xb4-byte owner without changing the exact 75/75 reset body.

2026-07-11 cRJetPack ownership: the adjacent singleton backlink store lands on
the primary `JetPack::owner_game +0x44` lane at runtime `+0x355ea8`. Its two
embedded cRVapour children occupy the rest of the exact 0x19c extent. Reset
remains exact at 75/75.

## 2026-07-13 analysis pool-band closure

The path-template and narrow pool analysis lanes now expose the complete
contiguous pool band between `JetPack` and `BannerPool`: eight exact 0x74-byte
`TrackHealthPickup`/cRSubHealth records at `+0x356000`, the eight-slot 0x760
`SlugPool` at `+0x3563a0`, the 20-slot 0xdc0 `SubLazerManager` at `+0x356b00`,
and the 40-slot 0x17c0 `SaltManager` at `+0x3578c0`.

Binary Ninja preview verifies every stride and boundary while keeping
`SubgameRuntime == 0x1272838`, then reverts. The exact reset body remains
75/75 instructions with both masked operands clean.

## 2026-07-13 cRSubRing backlink closure

The final two-slot reset loop now closes the pool's lifetime model: each
embedded `SubRing` is marked inactive and receives a borrowed pointer back to
the enclosing `SubgameRuntime` at `+0x1d0`. `cRSubRing::Init` and `AI` consume
that same owner for `subgame_rate` and the pause gate; there is no separately
allocated rate-source object. The historical generic ring names remain aliases
only, and the exact reset body remains 75/75.

## 2026-07-13 canonical reset ownership

The full exact body now expresses its allocation and lifetime boundaries
directly:

- `speedup_pickup`, `jetpack_pickup`, `health_pickups`, `slug_hazards`,
  `garbage_hazards`, and `ring_effects` receive their state clears and borrowed
  `SubgameRuntime*` backlinks through their primary types;
- the replay restore condition reads `replay_launch_active`, `level_mode`, and
  `current_high_score_record.replay_mode_id`;
- score, `Time`, score-tail, and replay-source values copy from the owned
  `SubSolution` snapshot into the embedded `Player`;
- the non-restore path clears that same Player state, and the final stores name
  the scan/camera latches, ring-spawn position, and garbage active-chain head.

The intrinsic `memcpy` is retained because it is the source-plausible form that
produces the native six-dword `Time` copy. All ownership substitutions remain
byte-exact at 75/75 instructions with both masked operands clean.

## 2026-07-14 reset-pool extent derivation

The health, garbage, slug, and ring reset loops now derive their bounds from
the exact arrays owned by `SubgameRuntime`. The normalized listing is
byte-identical
(`5400e59084b4ded03fa3af9eb7a3db57020f9698f18ba8bcc60b2624bb96a008`)
and remains exact at 75/75 instructions with two clean operands.
