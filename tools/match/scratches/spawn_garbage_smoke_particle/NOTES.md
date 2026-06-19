# spawn_garbage_smoke_particle

`spawn_garbage_smoke_particle` @ 0x43d5a0 is the smoke-effect producer called
from the pinned `update_garbage_hazard` burst state.

Behavior:

- Gates on `byte_4df934 & 0x10` before doing any sprite work.
- Allocates sprite id 33 from `g_sprite_manager` for the owning player slot.
- Marks the sprite as effect-rendered (`flags |= 0x800`), zeros progress and
  lifetime lanes, and derives progress/lifetime rates from `game->subgame_rate`.
- Seeds white color, scale `(0.30000001, 1.3)`, velocity scaled by `0.2`, and
  position copied from the garbage hazard.

Match status: 85.14% (72 candidate instructions vs 76 target, 5/76 exact
prefix). This is source-shaped and useful as a garbage-smoke semantic anchor,
but not exact.

Residual:

- The accepted raw float-lane tail keeps the color copy and scale stores at
  native `sprite + 0x2c`, `+0x60`, and `+0x64`. The remaining residual is the
  native `lea velocity; add position-base` setup and stack-staged scaled
  velocity reloads; the candidate still stores the tail through direct
  `sprite + offset` lanes.
- The helper is modeled as `void`: `update_garbage_hazard` ignores the result,
  and native simply leaves the success path's copied `position.z` dword in
  `eax`. Modeling a byte return was an invalid assumption that added a final
  `mov al, [position.z]` in the candidate.

Rejected source-shape probes:

- Cdecl `allocate_sprite(archive, ...)` regressed the call shape; existing
  sprite scratches confirm this is `g_sprite_manager.allocate_sprite(...)`.
- An `int` return with a byte flag local forced an extra stack slot and
  regressed to 63.69%.
- A separate scaled-velocity aggregate local over-allocated the stack and
  regressed to 67.55%.
- Rewriting the hot sprite setup as explicit word-lane stores including the
  color copy regressed to 72.00%. It delayed the early `sprite += 0x48` symptom
  but disrupted the color and velocity schedule, so keep the aggregate color
  assignment.
- 2026-06-16 Player consolidation: the owner slot now comes from shared
  `player.h` (`Player::player_slot`) with the same 76.82% score and clean
  `9 ok` masked audit.
- 2026-06-16 BN cross-check: the field schedule is the same sprite emitter
  idiom as `spawn_golb_smoke`. The confirmed word lanes are color `0xb..0xe`,
  position `0x12..0x14`, velocity `0x15..0x17`, `size_start/size_end`
  `0x18/0x19`, progress `0x1a`, progress/lifetime steps `0x1b/0x1d`,
  lifetime `0x1c`, and gravity `0x1e`; this supports the current shared
  `Sprite` field names but does not unlock a source-shape improvement.
- 2026-06-16 sprite-emitter idiom pass: spelling explicit `out_velocity` and
  `out_position` pointers matches the clearer source view kept by
  `spawn_golb_smoke` but compiles identically here. The residual early
  `sprite += 0x48` remained, so the focused score stayed 76.82% at that point.
- 2026-06-16 return-type correction: changing the shared declaration and
  scratch implementation from `char` to `void` removes the artificial success
  path byte reload and improves the focused score from 76.82% to 84.56%.
  The caller `update_garbage_hazard` remains at 80.00%, confirming the return
  value is not part of the gameplay contract.
- 2026-06-16 smoke velocity retry: hoisting `out_velocity` before the size writes
  compiled identically and did not fix native's delayed `sprite += 0x48`
  schedule. Replacing the reused `Color4f` lanes with explicit
  `scaled_x/scaled_y/scaled_z` locals regressed the focused score to `68.03%`.
  Keep the color-local velocity staging.
- 2026-06-19 sprite-base/velocity staging audit: making the `set_color_rgba`
  result explicit and saving alpha bits until after the size fields recovers a
  longer sprite-base lifetime, but breaks the native aggregate color-copy shape
  and regresses to 67.57%. Direct `sprite->velocity`/`sprite->position` field
  stores are codegen-neutral at 84.56%, and reading the reused `Color4f` lanes
  through a local pointer optimizes back to the same candidate. Copying the lanes
  into named scaled-velocity locals regresses to 81.33% with extra x87 churn.
  Keep the existing aggregate color copy plus `out_velocity`/`out_position`
  spelling; the remaining residual is still delayed sprite-base advance and
  native stack-staged velocity reload scheduling.
- 2026-06-19 output-view lifetime retry: focused Wibo still reports 84.56%,
  73/76 candidate instructions, 5/76 prefix, and 9 clean masked operands. A
  byte-base view (`sprite_bytes + 0x54/+0x48`), interleaving the X velocity
  store immediately after computing `color.r`, and declaring both typed
  `out_velocity`/`out_position` views before the velocity math are all
  codegen-neutral. None recover native's delayed `sprite += 0x48` or the
  stack-staged velocity X reload. This typed-output-only result is superseded by
  the raw float-lane tail below.
- 2026-06-19 shared smoke tail pass: using a raw `float* sprite_words` view
  after the aggregate color copy for `size_start/size_end`, velocity, gravity,
  and position improves focused Wibo from 84.56% to 85.14% (72/76 candidate
  instructions, 5/76 prefix, 9 clean masked operands). The same idiom improves
  `spawn_golb_smoke`, so this is a real shared emitter source-shape lead rather
  than a one-off tweak. Predeclaring both raw lane views is codegen-neutral.
  Mixing raw size stores with typed `sprite->velocity`/`sprite->position`
  falls back to 84.56% because the compiler again advances the sprite base
  before the color copy. Explicit `scaled_x/scaled_y/scaled_z` locals regress
  to 72.60% and lose two clean masked operands. Keep the raw tail while leaving
  the aggregate color assignment intact.
- 2026-06-20 emitter-tail retry: mutating the raw sprite cursor after forming
  the velocity pointer, matching the IDA `v11 = v6 + 21; v6 += 18` shape, is
  codegen-neutral at 85.14%. Interleaving the X velocity store immediately
  after computing `color.r` also stays at 85.14% but is less native because it
  emits a direct `fstp [sprite+0x54]`. Keep the accepted raw-tail shape.
