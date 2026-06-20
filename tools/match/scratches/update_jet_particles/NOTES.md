# update_jet_particles @ 0x43a690

First typed scratch for the jetpack hover-particle updater.

Recovered relationships under test:

- `update_jet_particles` is modeled as a no-argument
  `JetpackGaugeController` member. BN's raw prototype is the ABI-equivalent
  `__fastcall(JetpackGaugeController*)`, but the only current caller passes
  `ecx = &owner_player->jetpack_gauge`, which supports the member spelling.
- It only runs while `JetpackGaugeController::state == 1` and while the game
  active-player latch at `game+0x3bf3dc` equals `game+0x3bf43c->+0xbc`.
- The existing `JetParticleSlot[15][2]` grid at controller `+0x20` is consumed
  directly. Each frame, both sprites in each row receive the same size and a
  position projected backward along the owning player's forward vector.
- `game+0x3bf934` and `game+0x3bf940` are the two nozzle/source positions used
  for the two columns. `player+0x29dc` is the forward vector source for this
  effect.
- On the final row, the helper occasionally emits a sprite `0x21` puff owned by
  `game+0x3bbae4`, using the same shared `Sprite` fields as the other particle
  producers: flags, progress, lifetime, color, size, velocity, gravity, and
  position.

The `Game` and `Player` views are deliberately scratch-local until this is
cross-checked against `update_jetpack_gauge` / `update_subgoldy` or another
consumer of the same offsets.

Focused Wibo status:

- Current scratch: 46.89%, target 181 insns, candidate 173 insns, 13 masked
  operands OK and no unresolved or mismatched masked operands.
- Corrected assumption: unlike `orthogonalize_matrix`, spelling the helper as a
  member did not by itself improve codegen; the free fastcall and member forms
  were effectively equivalent here. The useful source-shape fix was avoiding a
  long-lived `JetGameView* game` local, which had made VC6 save `ebx` before
  the state gates. Native saves the controller in `edi`, performs the gates,
  then saves `ebx/ebp/esi`.
- Whole-`Vector3` copies for the two nozzle positions are better than direct
  component streaming. That moved the scratch from 32.65% to 45.14% and matches
  native's explicit dword copies for the source position local.
- Remaining mismatch is mostly stack/local schedule: native keeps a larger
  `0x50` frame with x/y offset temporaries and later velocity temporaries,
  while the current C++ source lets VC6 collapse much of that into FPU stack
  flow and a `0x38` frame.
- 2026-06-18 BN field sync: `JetParticleSlot` is now promoted in the BN headers
  as `Sprite* sprite`, `wobble_x`, `wobble_y`, and `wobble_alpha`. The tracked
  BN export now resolves the emitted trail-puff `Sprite` fields (`flags`,
  progress/lifetime, color, size, velocity, gravity, and position); the focused
  Wibo result remains 45.14% with the same stack/local-schedule residual.
- 2026-06-20 shared position-copy audit: changing the regular grid sprite copy
  from explicit `position.x/y/z` stores to `slot->sprite->position =
  base_position` regresses to 39.43%, keeping the same mask mismatch. Changing
  only the emitted trail-puff copy from explicit `out_position->x/y/z` stores
  to `*out_position = base_position` regresses to 43.87%. Keep the explicit
  field stores here: unlike the pickup spawners, aggregate assignment collapses
  the stack/local schedule this scratch still needs.
- 2026-06-20 RNG/local-order correction: native consumes the first RNG value as
  `size_scale` (`+0.119999997`) and the second as `forward_scale` (`+0.4`),
  not the reverse. Keeping the projected forward offset as an explicit
  `Vector3` stack local raises the frame from `0x38` to `0x44` and improves the
  focused score from 45.14% to 46.89%. A matching `Vector3` local for the
  emitted trail-puff velocity grows the frame again but regresses to 41.24%, so
  the velocity remains split into scalar locals.
