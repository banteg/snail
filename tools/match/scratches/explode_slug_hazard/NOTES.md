# Structure-first scratch - 97.61%, 146/147 insns

`explode_slug_hazard` is recovered as the 70-particle slug goo burst spawned
by `kill_slug_hazard`. Each iteration allocates sprite texture `129`, sets
sprite flags `0x802`, seeds grayscale, size, progress/lifetime, gravity, and
corner-scale fields, builds a velocity vector from the game track-center scale
and random spread terms, then offsets the sprite position from the slug world
position by a random multiple of that velocity.

Source-shape wins from the first pass:

- splitting the size expression into `random * 0.000030517578f`, then
  `* 0.75f + 0.25f`, preserves the native two-`fmul` size schedule;
- splitting the gravity expression keeps the native separate
  `track_center * track_center * -0.01 * 2.2` operations;
- staging `velocity` and `position` as `Vector3` aggregates improves the frame
  from `0x14` to `0x38` and recovers most of the native vector stack staging.

Historical residuals before the returned-vector pass:

- target frame is still `0x40` versus candidate `0x38`;
- flag update uses `ebx` where native uses `edx`;
- grayscale argument setup uses a local store then push, while native reserves
  the argument slot first and writes the float directly there;
- owner-game and random side/up locals use different registers/slots around
  the velocity block;
- final position y/z scheduling and the loop return differ; VC6 still emits a
  final `xor eax, eax` instead of returning the already-zero loop counter.

2026-06-16 consolidation/rejection pass:

- `SlugHazardRuntime` now carries the proven `0xec` pool stride and the
  `player_encounter_latched` byte at `+0xd9`; this explosion scratch still verifies
  at `73.22%`, `148/147`, with `32` masked operands OK.
- Rewriting the loop tail as `while (--count != 0); return count;` compiled
  identically and did not remove VC6's final `xor eax, eax`, so the scratch
  keeps the previous result-local spelling.
- Direct `sprite->position` field stores regressed to `70.83%` and shrank the
  frame to `0x2c`; direct `sprite->velocity` component stores regressed to
  `69.69%`. Keep the aggregate `Vector3 staged_velocity`,
  `position_offset`, and `staged_position` locals because they preserve the
  closest native stack shape.

2026-06-20 call-argument staging pass:

- Focused Wibo improves from 73.22% to 81.63% and recovers the instruction
  count to 147/147, with 32 clean masked operands.
- Retained: inlining the grayscale intensity expression directly in the
  `set_color_grayscale` call. This matches native's source shape where VC6
  reserves the cdecl argument slot first, computes the float directly into
  `[esp]`, and then calls the color helper. The previous named `intensity`
  local forced a store/reload/push sequence and created an extra candidate
  instruction.
- Rejected: saving the second RNG draw as an `int up_seed` regresses to 79.04%
  by using an integer multiply path; naming scalar velocity components is
  codegen-neutral at 81.63%; decompiler-shaped scalar position offsets regress
  to 81.38% and shrink the frame to `0x2c`; moving `Game* game` before the up
  RNG is score-neutral but loads `owner_game` too early; and a single-result
  loop spelling is still neutral and does not remove the final `xor eax, eax`.

Remaining residuals are now the `0x40` versus `0x38` frame, side/up stack-slot
ownership, velocity x87 ordering, final position-copy scheduling, and the
known loop-return zeroing. Do not force them with volatile, dummy locals, raw
offset macros, or fake aliases.

2026-06-21 owner-view cleanup:

- The generic scratch-local `Game` shell is now a named `SlugExplosionGameView`
  sparse owner view. Focused Wibo remains at 81.63%, 147/147 instructions, and
  32 clean masked operands.
- A broad `cRSubGame*` hoist was rejected. It regressed to 69.86% by
  shrinking the frame and extending the owner register lifetime through the
  burst setup, so the local sparse view remains the closer source shape.
- After `SlugHazardRuntime::owner_game` was promoted to `cRSubGame*`, this
  scratch still keeps the explicit `SlugExplosionGameView` cast for the proven
  source shape. Focused Wibo remains unchanged at 81.63%.

2026-07-11 owner closure:

- The two lanes have distinct real owners: `subgame_rate` is the
  `cRSubGame` clock at `+0x38`, while runtime `+0x3bbb7c` is the embedded
  `Player::velocity.z`. `SlugHazardRuntime::owner_game` borrows the runtime and
  reaches the latter through `owner_game->player`.
- Preserving the separate repeated rate reads and the late `game` local avoids
  the earlier broad-hoist lifetime regression, so the synthetic
  `SlugExplosionGameView` can be retired with no codegen loss. Focused Wibo
  remains the honest `81.63%`, `147/147`, with `32` clean masked operands.

## 2026-07-11 void member contract

Android and iOS v1.5 retain the side-effect-only member as
`cRSlug::Explode()`; iOS v1.9 only adds the owning `cRSubGoldy*` argument. Every
Windows caller discards EAX. Changing the primary `Slug` declaration from an
artificial `int` return to `void` removes the candidate-only final
`xor eax, eax` and improves focused Wibo from 81.63% to **81.91%**. The result
is 146/147 instructions with all 32 masked operands clean. The remaining gap is
the documented 0x40-versus-0x38 frame and local x87/register scheduling; no
dummy local or padding fakematch is introduced.

## 2026-07-12 raw/scaled velocity recovery

The side, up, and forward draws are one semantic `Vector3 random_velocity`,
and the emitted sprite receives a separate `staged_velocity` scaled by the
live subgame rate. This two-vector source shape recovers the native raw X/Y
slots, scaled X/Y/Z result slots, and exact `0x40` frame. Focused Wibo improves
from 81.91% to 97.61%, with 146/147 instructions, prefix 79, and all 32 masked
operands clean.

The remaining one-instruction gap is x87 scheduling: native loads the owner
between saving and converting the up RNG draw, then uses an explicit `fxch`
before scaling forward Z; VC6 legally commutes the same multiplies in the
candidate. A named integer RNG seed regresses to 95.89% by emitting `fimul`,
and moving the owner lifetime earlier shortens the prefix, so neither probe is
retained. No volatile or fake alias is used to force the `fxch`.

## 2026-07-13 vector result ownership

The scaled velocity is now expressed as the real by-value
`random_velocity * speed` operation assigned directly to the sprite. VC6 still
materializes the same three-component result in the native-sized `0x40` frame,
so the focused result remains 97.61%, 146/147 instructions, prefix 79, and 32
clean masked operands. This retires the artificial named `staged_velocity`
owner without changing bytes; the remaining gap is still only the documented
owner-load/x87 schedule and is not forced.

## 2026-07-19 analysis owner lift

Reanalysis through the complete `Slug` and shared sprite prototypes lifts the
IDA artifact from raw `char*`/dword arithmetic to an owned `Sprite*` with
typed flags, progress, color, size, gravity, velocity, and position. The two
intermediate vectors also render as `Vec3` values. This improves the tracked
analysis artifact only: focused matching remains the honest 97.61%, 146/147,
prefix 79, with all 32 operands clean and the documented x87 scheduling gap.

## 2026-07-28 mobile RNG range provenance

iOS explicitly preserves unit-random normalization followed by semantic range
scales, and Android corroborates the same normalizer/range family. The Windows
values remain platform-specific: spread `0.2`, progress variation `0.5`,
grayscale variation `0.3`, and position scale `10`. Expressing those products
from `1 / 32768` compiles byte-identically at 97.61%, 146/147 instructions,
prefix 79, with all 32 masks clean.

The platform-specific particle count, texture, and range values remain
untouched; mobile supplies source provenance rather than replacement constants.

## 2026-07-29 owner/x87 scheduling boundary

Three recorded mutation sweeps exhaust the credible source-level ways to move
the up-seed conversion, owner load, and scaled-vector expression without
inventing a dependency. Across 50 evaluated variants (41 unique), none improve:
13 are score-neutral and 37 regress. The owner/seed sweep contributes 9
variants, the vector spelling/order sweep 12, and their complete two-site
interaction 29.

The score-neutral alternatives either compile byte-identically or move the
owner load earlier while shortening the exact prefix from 79 to 72.
Integer-seed provenance, delayed float conversion, component reordering, and
copy-then-scale forms all regress. Binary Ninja confirms the native sequence
loads `owner_game` at `0x43f7c3`, before converting the saved up draw, then
keeps the rate live across the three products and emits the otherwise
unrecovered `fxch` at `0x43f826`.

The honest result therefore remains 97.61%, 146/147 instructions, prefix 79,
with all 32 masked operands clean. Android/iOS range provenance supports the
current random-vector semantics, but no mobile-backed owner or component
spelling recovers that Windows VC6 x87 schedule. Do not force it with
`volatile`, a dummy dependency, or a fake alias.
