# WIP scratch — 47.99%, 648/673 insns (2026-06-16 ring reward ladder pass)

Structure complete: all eight pool sweeps in order with asm-verified
offsets. The low ratio is systematic small deltas, leads for next pass:

2026-06-16 slug runtime consolidation: the first-hit/cutscene branch now uses
the shared `SlugHazardRuntime::player_encounter_latched` byte at `+0xd9` instead of a
raw byte poke. Collision and `update_golb_ai` both prove the pool stride is
`0xec`, so `slug_hazard_types.h` now carries explicit tail padding and a
`sizeof(SlugHazardRuntime) == 0xec` assertion. Focused Wibo remains `47.99%`,
`648/673`, `77 ok / 1 mismatch`; the remaining mismatch is still the known
slug-block alignment debt.

2026-06-16 sub-lazer renderable-prefix consolidation: `SubLazerSlot` now
exposes the renderable transform rows at `+0x38..+0x77`, keeping
`position +0x68` as `RenderableBod::transform.position` while retaining the
zero-offset `BodNode` list overlay. This collision scratch consumes the same
sub-lazer position/state lanes as the initializer, spawner, updater, and
deactivator. Focused Wibo remains `47.99%`, `648/673`, with the same known
slug-block masked mismatch.

2026-06-16 speedup renderable-prefix consolidation: `TrackSpeedupRuntime` now
exposes the same transform row window, with `world_position +0x68` as
`RenderableBod::transform.position`. This collision scratch consumes the full
speedup x/y/z vector, while the exact updater consumes the z lane and the
initializer proves the renderable constructor path. The singleton still keeps
the zero-offset `BodNode` list overlay for teardown.

2026-06-16 salt BOD/renderable consolidation: `SaltHazardSlot` now uses the
shared `BodNode` prefix and `BodList` anchor, and exposes the BodBase/renderable
fields through `position +0x68`. This collision scratch consumes the salt
position vector and the low byte at `+0x94`; the latter remains represented as
`*(unsigned char*)&slot->velocity.z` because spawn and collision prove the
byte latch but not a clean source-level field name.

2026-06-16 ring reward ladder pass: the ring/special-effect reward ladder is
not a native `switch`. Replacing the scratch `switch (effect_kind)` with a
source-equivalent `if` / `else if` compare chain removes VC6's jump table and
matches the target's authored compare chain for kinds `4/5`, `8`, `1`, and
`2/6`. Focused match improves from `45.43%` to `47.99%`, candidate
instructions move from `639` to `648`, and the masked audit rises from
`70 ok` to `77 ok`. The known slug-block masked call mismatch remains.

2026-06-16 slug/sub-lazer local pool-field pass: the local `Game` window now
types the slug and sub-lazer pools as `SlugHazardRuntime[8]` and
`SubLazerSlot[20]`, matching the shared `0xec` and `0xb0` stride assertions.
The sweep bodies deliberately keep the existing byte-strided loop expressions:
previous typed-loop probes changed VC6 register ownership. Focused Wibo remains
`47.99%`, `648/673`, `77 ok / 1 mismatch`.

2026-06-16 garbage pool promotion: the local `Game` window now uses the shared
`GarbageHazardPool` at `+0x359140` instead of split local active-head/slot
fields. This agrees with exact `destroy_garbage_hazard`, the collision active
chain, and `spawn_track_garbage_hazard`'s pool scan (`active_head + 50 * 0xc4`
slots, total `0x264c`). The spawner remains raw-offset shaped because its typed
slot rewrite was already rejected on saved-register ownership.

2026-06-16 ring parent pool promotion: the local `Game` window now uses the
shared `RingOrSpecialEffectPool` at `+0x35b78c`, matching the spawner's two
parent slots and stride `0x1f8` (`0x3f0` total). The collision sweep remains
byte-strided for codegen shape, but the surrounding `Game` relationship now
uses the promoted pool view.

2026-06-16 shared Player consolidation pass: the scratch now consumes the
shared `Player` definition instead of carrying a private broad player window.
This promoted `Player::handle_subgoldy_collisions`, direct
`Player::parcels_collected` at `+0x4338`, and
`Snail::wobble_lift_phase_step` at presentation
`+0x15c8` (`Player +0x3f4c`). The slug first-hit cutscene write now goes
through `presentation.cutscene.state`, the ring nuke pickup uses the shared
`Nuke::initialize_nuke()` method at `Player +0x150`, and the local
three-float collision probes alias the shared `Vector3` view. Focused match
moves from `45.36%` / 641 candidate insns to `45.43%` / 639 with the masked
audit unchanged (`70 ok`, one known slug-block alignment mismatch).

2026-06-16 audio/voice call-surface pass: replaced the scratch-local free
`play_sound_effect`/`play_voice_manager` declarations with compact manager
method views (`g_sound_effect_manager` and `g_voice_manager`). This matches the
native global-thiscall call shape without importing the broader shared audio
headers, improves the focused match from `43.33%` to `45.15%`, and raises the
masked audit from `65 ok` to `70 ok`. The remaining masked mismatch is still the
slug-block alignment debt (`kill_slug_hazard` vs `begin_post_follow_carryover`),
not an audio-symbol problem.

2026-06-20 shared audio/voice header pass: the compact manager method views are
now supplied by `sound_effect_manager.h` and `voice_manager.h`. Focused Wibo is
unchanged at `47.99%`, `648/673`, `77 ok / 1`, with the same slug-block masked
call mismatch. This clears the remaining `SoundEffectManager`/`VoiceManager`
type-report rows without importing broader audio backend layout into this
large collision scratch.

2026-06-16 slug method call-surface pass: replaced the scratch-local free
`kill_slug_hazard(int)` / `play_slug_voice(int, int)` declarations with the
shared `SlugHazardRuntime` method declarations. BN prototypes and the exact
`kill_slug_hazard` / `play_slug_voice` scratches agree these are methods, and
the collision scratch now emits real thiscall setup at the slug callsites.
Focused match improves from `45.15%` / 647 candidate insns to `45.36%` / 641.
The masked mismatch still reports `kill_slug_hazard` vs
`begin_post_follow_carryover`, so this did not solve the slug-block alignment
debt. The later slug runtime consolidation proved the `0xec` pool stride in
the shared `SlugHazardRuntime` header; keep the slug loop byte-strided here for
codegen shape, not because the slot layout is uncertain.

- Rejected probe: spelling a local `unsigned char movement_kill_mask = 0x80`
  did not produce native's `bl` mask register reuse. VC6 propagated it back to
  literal `test byte [esi+0x338], 0x80`, leaving the match at `43.33%`; keep the
  literal mask tests until the loop/register shape has a real owner.
- 2026-06-16 sub-lazer typing retry: replacing the raw sub-lazer collision sweep
  with the shared `SubLazerSlot` view is semantically valid, but both the typed
  `Game::lazer_slots[20]` field and a narrower cast-only spelling regressed the
  focused match from `45.43%` to `44.16%` (`636/673` candidate/target
  instructions) by changing the loop constants/register ownership. Keep the
  byte-strided sub-lazer sweep in this large scratch until the surrounding frame
  shape improves; this does not weaken the shared `SubLazerSlot` layout already
  confirmed by spawn/update/deactivate.

2026-06-16 Player field promotion: `damage_retrigger_timer`/`step`
(`+0x1d4/+0x1d8`), `control_override_active` (`+0x2d8`), and
`completion_handoff_active` (`+0x440`) are now promoted in shared
`player.h`. These are cross-confirmed by this collision scratch and
`update_subgoldy`; `completion_handoff_active` is also aligned with the
post-follow carryover/camera exit gate notes. The collision scratch keeps its
local `Player` window for codegen, so this is a struct consolidation step, not
a score change.

2026-06-16 typed runtime-pool pass: the scratch now includes the shared
health, speedup, jetpack, garbage, salt, slug, sub-lazer, parcel, and
ring/special-effect headers in the local `Game` window. This is a
relationship/field-certainty pass rather than a source-shape win: typed loop
rewrites changed VC6's loop base registers and stack slots, so the slug and
sub-lazer sweeps still use byte-strided loop expressions even though the local
pool fields are typed as `SlugHazardRuntime[8]` and `SubLazerSlot[20]`. The
useful cross-confirmations are:

- `TrackSpeedupRuntime` has a full `world_position` vector at `+0x68..+0x70`
  and `state` at `+0x80`; `update_track_speedup` only needed the z lane, but
  collision consumes x/y/z.
- `TrackHealthPickup`, `JetPack`, `Parcel`,
  `GarbageHazardSlot`, and `RingOrSpecialEffectParent` all line up with their
  shared headers at the collision callsites. Ring/special-effect centers now
  come through inherited `RenderableBod::transform.position`.
- `GarbageHazardSlot` now inherits the shared zero-offset
  `ContactTargetObject` prefix used by `append_subgame_contact_target`; this
  collision scratch consumes the same state/list node/body fields, while the
  per-frame registry append path consumes the prefix flags.
- `Player +0x404` is the lives counter used by the ring/special-effect reward
  ladder; this cross-confirms the shared `Player::lives` promotion.
- `Player::damage_gauge` at `+0x3c4`, `Player::sub_hover` at `+0x2750`,
  and `Player::cached_camera_target_world` at `+0x2964` are now promoted in
  `player.h`. This collision scratch still keeps a broad local `Player` window
  because it touches several not-yet-promoted lanes, but these three fields are
  no longer scratch-only evidence.
- The salt collision live byte remains deliberately spelled as
  `*(unsigned char*)&slot->velocity.z`: the byte is cross-confirmed by the
  salt spawner, but the surrounding semantic field is still not named.

2026-06-16 player subobject consolidation: shared `player.h` now records the
`Nuke nuke` object at `Player +0x150` and embedded
`Snail::cutscene.state` at presentation `+0x1964`
(`Player +0x42e8`). This collision scratch consumes both through the ring
nuke pickup (`initialize_nuke(player+0x150)`) and slug first-hit cutscene state
`10`; `update_subgoldy` independently drives the nuke update/uninit path and
sets cutscene state `5` during completion handoff. The scratch keeps its broad
local `Player` window because replacing it with the shared header would also
pull in include-sensitive math/sprite/controller views.

2026-06-21 runtime owner cleanup: `Player::game` is now a `SubgameRuntime*`,
and the collision scratch includes `subgame_runtime.h` directly instead of
carrying a local `Game` field window. `SubgameRuntime` now exposes the proven
`parcel_total` lane at `+0x1b01e0`; the parcel HUD writer uses the existing
`lives_text_widget` field at `+0x35bb94`. Focused Wibo is unchanged at
`52.85%`, `659/673`, prefix `8/673`, with `86 ok / 0 mismatch` in the masked
audit. `uv run snail match types --paths` no longer reports any generic
`Game` owner row; only the intended header-compatible `GolbShot` and `Player`
rows remain.

2026-06-16 pickup/runtime offset correction pass: corrected the scratch-local
`Game` and `Player` windows to agree with the already matched/update-spawner
evidence:

- Game core fields now use `level_mode +0x40`, `level_mode_arg +0x44`,
  `base_subgame_rate +0x48`, and `runtime_flags +0x4c`, matching
  `set_subgame_features`, `populate_runtime_track_cells_from_segments`, and
  `update_subgoldy`.
- The five collision-adjacent runtime regions are now aligned to the target:
  health pool `+0x356000`, speedup singleton `position +0x355e18/state
  +0x355e30`, jetpack singleton `position +0x355e74/state +0x355e9c`,
  ring/special-effect parents `+0x35b78c`, and the parcel HUD/total lanes
  `+0x35bb94/+0x1b01e0`.
- Corrected adjacent pool anchors that had drifted by one region:
  slug `+0x3563a0`, sub-lazer `+0x356b00`, salt `+0x3578c0`, garbage list
  head `+0x359140`, and track parcel/ring slots `+0x125e480`.
- Switched proven helpers back to method-call shape:
  `Player::add_subgoldy_score`, `Player::health_collect_particles`,
  `DamageGuage::apply_damage_gauge_delta`, and
  `SubHover::arm_jetpack_gauge` (`cRSubHover::On`).

Matcher impact: score improved from `45.71%` to `48.79%`, and the
speedup/jetpack/garbage/parcel offsets now agree with the target asm. The
matcher reports one masked call mismatch in the still-low-score slug block
(`kill_slug_hazard` vs the nearby carryover call); treat that as alignment
debt, not proof of the slug branch.

2026-06-13 matcher padding rebaseline: terminal object-padding normalization
removes untargeted bytes after final `ret` instructions, so the same source now
reports 45.15%, 656/673 instructions. This is a measurement correction, not a
source-shape change.

- frame 0x74 vs 0x5c: native stages MORE locals — the slug first-hit
  writes an unused staging triple (IDA v70=0/v71/v72 before the velocity
  stores) and the per-loop delta/probe pairs each own slots; add the
  staging Vec3 and check slot reuse
- the movement-flags 0x80 test rides a REGISTER (mov bl, 0x80; test bl,
  al) reused by the garbage-loop test — try a local mask variable
- delta.z wants fst+fcomp straight off the FPU (store z, compare in one
  flow) — the struct copy `probe = delta` currently intervenes; try
  per-component copies ordered after the z compare like the health loop
- velocity.z = -0.1f at ring kinds 3/7 compiles to `mov ebp, 0xbdcccccd`
  hoisted before the loop + reg store — NOT a byte-poke bug (IDA's -0.1
  confirmed); should fall out once loop shape aligns

2026-06-15 slug-hit shape pass: focused matcher now verifies 45.71%,
657/673 instructions, masked operands 64 ok / 0 mismatch. BN confirms the
repeat-hit native code multiplies by subgame_rate, then 0.0040000002f, then
-8.0f; staging the scaled rate prevents VC6 from folding the constants into
-0.032. Rewriting the slug-hit branch as normal-control paths first and the
movement-flag kill path last matches the native physical block order and
clears the previous `kill_slug_hazard`/`begin_post_follow_carryover` audit
misalignment.

Asm-verified field finds (cross-findings for the campaign):

- player+0x408 = SubgameRuntime* (the back-pointer; previously tracked as a
  scratch-local `Game*`)
- player+0x440 = completion_handoff_active — cross-confirms the
  unification's "damage-warning drain blocker at 0x4301bc"
- nuke_effect_progress/step at player+0x374/+0x378 (NOT 0x4180);
  initialize_nuke receives player+0x150 as this (overlaps the
  player_slot read — settle when the nuke port lands)
- pools (game-relative): salt state 0x357940/live byte 0x357954/pos
  0x357928; sub-lazer state 0x356b80/pos 0x356b68; garbage list head
  0x359140 (node: pos +0x68, next +0x80, state +0x84, direction +0x88);
  slug state 0x356420/pos 0x356408/object 0x3563a0/hit byte 0x356479;
  track rings state 0x125e4b8/pos 0x125e490; health state 0x356038/pos
  0x356010/particles 0x356000; speedup single 0x355e30/0x355e18;
  jetpack single 0x355e9c/0x355e74; ring effects state 0x35b80c/pos
  0x35b7f4/kind 0x35b814; parcel hud owner dword 0x35bb94, total
  0x1b01e0

# Dossier — scratch not yet written (673 insns, 2887 bytes)

cRSubGoldy::Collision() per cross-port symbols. target.asm committed.
The contact table, from the IDA export (line refs in 00444cf0-*.c):

| pool | walk | gate | effect |
|---|---|---|---|
| salt | 6080 bytes / stride 152 (40 x 0x98) | pre-gate < 1.0 then normalized dist < 0.98 | damage 0.15, damage_retrigger_timer seeded from retrigger_step when zero |
| sub-lazer | 3520 / 176 (20 x 0xb0) | < 1.0 then < 0.49 | damage 0.02 |
| garbage | (stride from loop) | < 1.0 then < 0.98 | velocity.x -= dir.x * vz * 0.18, velocity.z -= dir.z * vz * 0.1, direction byte from dir.x >= 0, score event 0, damage 0.04, random voice via next_math_random_value * -0.000061035156 |
| slugs | 1888 / 236 (8 x 0xec) | < 2.0 then < 1.5675001 | repeat hit: velocity.z = subgame_rate^2 * 0.004 * -8, damage 1.0; first hit: velocity = (0, tc*0.2, tc*-0.2), wobble lift_phase_step = 0, carryover/cutscene lanes |
| rings/pickups | 7000 / 140 (50 x 0x8c) | < 1.0 then < 1.24 | score event 3, ring ladder dispatch |

Validates the harvested checklist formulas (slug triplet, repeat-hit
knockback) and adds the garbage knockback pair and the ring 1.24 gate.
All damage flows through apply_damage_gauge_delta(state, amount, 0) —
the force parameter from the hit-flash harvest is visibly 0 here.

Verify-pass targets for the Zig port: salt/sub-lazer gates ported per
checklist; slug velocity lanes and garbage knockback are motion-slice
consumers (not yet portable); ring gate and score-event ids worth
diffing against the runner's pickup collision slots.

Match plan: five sequential pool loops with the shared
pre-gate-then-normalize idiom — start the scratch from the salt loop and
extend pool by pool; reuse the salt slot layout from the quartet.

## Verify pass (2026-06-12): Zig gates all confirmed

Diffed against the runner: salt 0.98, sub-lazer 0.49, garbage 0.98,
ring 1.24, slug 1.5675001 with the 2.0 z-gate, health 0.98, and the
damage_retrigger_timer seeded from retrigger_step when zero — all
present and correct (gameplay.zig constants + processRuntimeHazard /
pickup lanes). The June-10 audit fixes hold against the matched-grade
table. Remaining gaps are exactly the motion-slice consumers already on
the checklist: slug first-hit/repeat velocity lanes and the garbage
0.18/0.1 knockback pair. The eventual full match is proof-polish over a
now-verified model, so cluster 3's priority drops below the cameraman
and golb matches.

## Parcel ownership follow-up (2026-07-10)

The collision path now consumes inherited `Parcel::position`, and
the HUD total comes from the embedded
`SubgameRuntime::level_definition.parcel_count`. The focused result remains
52.85%, 659/673, prefix 8/673, with all 86 masked operands clean.

## Collision-pool ownership closure (2026-07-10)

`SubgameRuntime` now owns the complete fixed collision band: eight `Slug`
slots through `SlugPool`, twenty sub-lazers, forty
salt hazards, the `ParcelManager`, eight health pickups, and the two ring-effect
parents. The salt, slug, parcel, health, and ring sweeps now derive their byte
cursors from those named members while retaining the native byte-strided loop
shape.

The parcel sweep now names the primary `Parcel` records and derives its base
from `SubgameRuntime::parcel_manager.slots`. This is codegen-neutral at 52.85%,
659/673, prefix 8/673, with all 86 masked operands clean.

The salt byte at slot `+0x94` is now `collision_armed`: the exact spawner sets
it, this collision path tests it, and a successful contact clears it. A typed
sub-lazer cursor was rejected because it regressed the focused score from
52.85% to 51.54%; that loop remains byte-strided even though ownership is
already represented by `SubLazerPool`. No register-shaped locals or fake
control flow were retained. Focused Wibo remains 52.85%, 659/673, prefix
8/673, with all 86 masked operands clean.

The live Binary Ninja type also now agrees with the shared source view at salt
slot `+0x88`: this is `owner_game`, not the stale `Path*` label. The
neighboring `state`, `fade_alpha`, and spawn-time y-velocity lanes were read
back with the same offsets.

## Firework and vector-expression ownership (2026-07-11)

The first slug-contact path now uses the named cross-port source forms that
became available when `spawn_slug_hazard` recovered `Vector3::operator*`:

- knockback is `Vector3(0, 0.2, -0.2) * subgame_rate`;
- the half-distance burst offset is `normalized_delta * (distance * 0.5)`;
- the burst position is a real `Vector3`, not an anonymous float array; and
- the burst call is `Player::firework.firework_shoot(...)`, with the embedded
  authored `FireWork` receiver at `Player +0x1d0` proven by both the Windows
  `lea ecx, [esi+0x1d0]` and Android `cRFireWork::Shoot(player+440, ...)`.

These semantic expressions inline to the existing best collision code. The
focused result remains `52.85%`, `659/673`, prefix `8/673`, with all `86`
masked operands clean; the change removes a false free-function ownership
surface rather than claiming compiler-allocation progress.

## cRSlug primary owner (2026-07-11)

The slug sweep now consumes the primary `Slug` type; `SlugHazardRuntime` and
`SlugHazardPool` remain compatibility aliases only. Android and iOS retain the
same class as `cRSlug`, while the Windows constructor table points to its AI
method. The byte-strided collision loop is preserved because it is the closest
native allocation shape. Focused Wibo remains 52.85%, 659/673, with all 86
masked operands clean.

## cRSubHealth primary owner (2026-07-11)

The eight-record health sweep now consumes `SubHealth` and passes that exact
borrowed object to the exact `Player::health_collect_particles` method.
Android/iOS preserve the pair as `cRSubHealth` and
`cRSubGoldy::HealthCollect(cRSubHealth*)`. The native byte-strided loop shape
is unchanged; focused Wibo remains 52.85%, 659/673, with 86 clean operands.

## cRSubSpeedUp primary owner (2026-07-11)

The singleton collision check now uses the primary `SubSpeedUp` object at
`SubgameRuntime +0x355db0`. Its full position vector, state, owner backlink,
and sprite are independently established by the exact constructor and exact
AI. Focused Wibo remains 52.85%, 659/673, with all 86 operands clean.

## cRJetPack primary owner (2026-07-11)

The adjacent singleton collision check now uses the primary `JetPack` at
`SubgameRuntime +0x355e64`. Android/iOS retain `cRJetPack`, the exact Windows
constructor table points to its AI, and its two embedded cRVapour children
close the full 0x19c allocation. Focused Wibo remains 52.85%, 659/673, with
all 86 operands clean.

## cRNuke embedded owner (2026-07-11)

The collision kinds that arm the ring effect now call the exact 0x7c-byte
`Nuke` embedded at Player +0x150. Android `cRSubGoldy::Collision()` calls
`cRNuke::Init()` through the same relationship and preserves every owner field
offset. Focused Wibo remains 52.85%, 659/673, with all 86 operands clean.

## Player tail cross-tool closure (2026-07-13)

The live Binary Ninja `Player` type was eight bytes short and still carried
the pre-ownership tail: `Player +0x4338` was mislabeled as
`visible_life_stock`, `Squidge` and the commentary timers were consequently
shifted, and the enclosing-runtime backlink remained `Game*`. The canonical
BN and IDA-facing headers now agree with the exact 0x4364-byte matching owner:

- `score_tail +0x300`, `last_ring_spawn_z +0x37c`, and
  `boost_one_tick +0x41c` replace proven opaque lanes;
- `game +0x408` is the borrowed enclosing `SubgameRuntime*`;
- `parcels_collected +0x4338` precedes `visible_life_stock +0x4340`; and
- `Squidge +0x4344` plus the commentary timers at `+0x435c/+0x4360` close the
  real tail.

This corrects the analysis owner used by collision, completion, parcel HUD,
and subgoldy update paths without reshaping the matcher scratch. The 52.85%,
659/673 instruction result with 86 clean operands remains the honest baseline.

## Pickup and hazard manager analysis closure (2026-07-13)

The analysis `SubgameRuntime` now embeds the health, slug, sub-lazer, and salt
owners consumed by this function rather than spanning them with one anonymous
pad. Their exact slot counts and extents meet at `+0x356000`, `+0x3563a0`,
`+0x356b00`, `+0x3578c0`, and the existing `BannerPool +0x359080` boundary.
Borrowed `Player*` and `SubgameRuntime*` backlinks remain distinct from row-cell
sources inside each slot.

Binary Ninja declaration preview verifies the manager layouts and reverts.
Focused Wibo remains honestly unchanged at 52.85%, 659/673 instructions, with
all 86 masked operands clean and no mismatch.
