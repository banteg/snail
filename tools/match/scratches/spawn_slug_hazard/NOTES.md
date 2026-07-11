# spawn_slug_hazard

First scratch for `spawn_slug_hazard` @ `0x43dc80`
(`cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)`).

Recovered relationships:

- scans the eight-slot slug pool at `game+0x3563a0`, stride `0xec`, using
  `state +0x80`;
- seeds the renderable transform position from `TrackRowCell::anchor_position`
  with a fixed `+1.7f` Y lift, then projects through
  `project_position_onto_track_attachment`;
- inserts the slot's zero-offset `BodNode` before the shared BOD-list tail;
- allocates sprite texture `118`, forces white color, size `2.0f`, and mirrors
  the projected position into `Sprite::position`;
- confirms `SlugHazardRuntime::player +0xc0`, `sprite +0xac`,
  `source_cell +0xb0`, `passed_player +0xb4`,
  `player_encounter_latched +0xd9`, and the blink/voice progress tail.

2026-06-20 larger source-shape pass: focused Wibo improves from `86.52%` to
`92.79%` (`159/160` instructions, `48/160` prefix, 16 clean masked operands).
Three source-shaped changes were retained:

- splitting the initial state/player destinations into `state_ref` and
  `player_ref` keeps the native state store before the player store and
  recovers the first 48-instruction prefix;
- using the proven typed `BodNode`/`BodList` tail-insertion idiom recovers the
  native `g_game_base + 0x5a8` materialization and adds the extra clean masked
  operand;
- spelling the hit-flash step, hit-points, and node-flags tail through local
  destination references keeps the x87 flash-step store before the HP/flag
  writes and fixes the HP/flag scheduling residual.

At that frontier, the velocity staging still differed. Native keeps
`game+0x38` live on x87, loads a float zero, stores that zero through the local
vector x/y lanes, then multiplies the z lane by `-0.2f`; the candidate still
pre-multiplies z and writes x/y with integer zero stores.

Rejected probes:

- Promoting the initial state/player/matrix setup to a typed
  `SlugHazardRuntime*` regressed to 53.92% by changing saved-register
  ownership and keeping the slot node live too broadly.
- Keeping the list node live through the later flag clear regressed to 59.56%.
  Reload the flag dword at `+0x04` instead.
- Naming a `float zero`, using a `Vector3(0.0f, 0.0f, z)` constructor, seeding
  `velocity.z` before scaling it, splitting `velocity_x/velocity_y/velocity_z`
  locals, and using double `0.0` literals are neutral for the retained score
  and do not recover the native x87 zero stores.
- Staging `g_game_base + 0x5a8` and the initial node flags as raw locals is
  neutral after the prefix fix; the typed BOD idiom is the accepted list shape.
- 2026-06-20 continuation velocity audit: direct destination stores through a
  named `Vector3* velocity` regress to 91.37% by moving the BOD-list tail setup
  before the native velocity stack staging. Ordering the local vector as
  `z` seed, x/y zero, then z scale is codegen-neutral at 92.79%; VC6 still
  pre-multiplies z before the integer zero stores. Keep the accepted local
  vector copy until new source evidence explains the native `fld zero` form.
- 2026-06-20 larger velocity-construction audit: focused Wibo still reports
  92.79%, 159/160 candidate/target instructions, 48/160 prefix, and 16 clean
  masked operands. An assignment-chain zero (`velocity.x = velocity.y = 0.0f`)
  plus delayed `velocity.z *= -0.2f`, and a zero-constructed
  `Vector3(0.0f, 0.0f, 0.0f)` followed by z assignment/scale, are both
  codegen-neutral. They move the z multiply after integer zero stores but still
  do not produce native's `fld zero; fst/fstp` x87 zero spills. Removing the
  scalar z local and assigning `velocity.z = game_rate` directly before x/y
  zeroing is also neutral and returns to the premultiplied z schedule. Leave
  the current compact local-vector spelling; recovering the native form likely
  needs original evidence for a real floating zero producer, not artificial
  arithmetic-zero source.
- 2026-06-20 shared position-copy audit: replacing the raw three-word sprite
  position copy with `sprite->position = *live_position` is codegen-neutral at
  92.79% with the same 159/160 instruction count, 48/160 prefix, and 16 clean
  masked operands. Unlike the pickup spawners, this slug scratch already has
  the native destination-register ownership for the position copy; the
  remaining residual is still the velocity zero/x87 staging plus one tail
  branch label.
- 2026-06-21 subgame receiver cleanup: the allocator now lives on
  `SubgameRuntime`, sharing the recovered slug spawn declaration and projection
  call surface without changing the raw slot layout. Focused Wibo remains
  `92.79%`, `159/160`, with `16` clean masked operands.

## 2026-07-11 exact vector-scale recovery

The bundled Android `cRSubGame::AddSlug` provides the missing independent
source evidence: it scales all three components of the direction vector
`(0, 0, -0.2)` by the subgame rate. That is the source-level vector operation
the earlier scalar assignments had erased. Recovering `Vector3::operator*`
with a component-wise result temporary and spelling the velocity as
`Vector3(0.0f, 0.0f, -0.2f) * subgame_rate` reproduces Windows' retained x87
zero, its paired X/Y stores, and the delayed Z multiply/store exactly.

Focused Wibo is now **100.00%**, `160/160` instructions, full `160/160`
prefix, and `18 ok / 0 unresolved / 0 mismatch` in the masked audit. This is a
semantic source recovery backed by the named cross-port function, not a
register or padding accommodation.

The same pass records the surrounding owners without changing codegen:

- the insertion anchor is `GameRoot::active_bod_list`;
- its tail sentinel is the embedded `SubgameRuntime::player` object;
- the hit-flash rate comes from `GameRoot::subgame.subgame_rate`; and
- `SubgameRuntime::next_slug_voice_trigger_z` starts at `50.0f` and advances by
  `slug_voice_trigger_spacing_z` (`100.0f`) whenever a spawned slug receives
  `engagement_voice_gate`. `update_slug_hazard_ai` later consumes that gate at
  the player's 16-unit approach threshold.

## 2026-07-11 cRSlug ownership

The eight inline records are now primarily named `Slug`, matching the retained
Android/iOS `cRSlug` owner; `SlugHazardRuntime` is a compatibility alias only.
The exact 160-instruction allocator still keeps its narrow raw slot-base
spelling because a broad typed receiver changes saved-register ownership. Its
scan nevertheless starts at `SlugPool::slots`, uses `sizeof(Slug) == 0xec`, and
closes the complete 0x760 native allocation.
