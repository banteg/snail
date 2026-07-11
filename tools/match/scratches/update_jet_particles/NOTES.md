# update_jet_particles @ 0x43a690

First typed scratch for the jetpack hover-particle updater.

Recovered relationships under test:

- `update_jet_particles` is modeled as a no-argument
  `SubHover` member. BN's raw prototype is the ABI-equivalent
  `__fastcall(SubHover*)`, but the caller passes
  `ecx = &owner_player->sub_hover`, which supports the member spelling.
- It only runs while `SubHover::state == 1` and while the game
  active-player latch at `game+0x3bf3dc` equals `game+0x3bf43c->+0xbc`.
- The existing `JetParticleSlot[15][2]` grid at controller `+0x20` is consumed
  directly. Each frame, both sprites in each row receive the same size and a
  position projected backward along the owning player's forward vector.
- `game+0x3bf934` and `game+0x3bf940` are the world-space authored
  `JetpackLeft` and `JetpackRight` hotspots (indices 13 and 14).
  `player+0x29dc` is `presentation.live_matrix.basis_forward`.
- On the final row, the helper occasionally emits a sprite `0x21` puff owned by
  `game+0x3bbae4`, using the same shared `Sprite` fields as the other particle
  producers: flags, progress, lifetime, color, size, velocity, gravity, and
  position.

The owner chain is now closed through the shared types: the gauge borrows its
containing `Player` and `SubgameRuntime`; the runtime embeds that same player,
whose presentation owns the animation channel, live matrix, and hotspot banks.

Focused Wibo status:

- Current scratch: 52.96%, target 181 insns, candidate 174 insns, 16 masked
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
  `0x50` frame with both loop counters and later velocity temporaries, while
  the current C++ source lets VC6 keep the inner counter in a saved register
  and collapse the frame to `0x44`.
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
- 2026-06-20 RNG/local-order pass: the then-current source used size scale
  before forward scale and reached `46.89%`; later resolved-constant inspection
  showed that this reversed the native random draws.

2026-07-11 ownership and source-order closure:

- Resolved target constants prove the first random draw is `forward_scale`
  (`+0.4`) and the second is `size_scale` (`+0.119999997`). Correcting that
  semantic order, declaring the row after both draws, laying out the zero-column
  branch first, and retaining a real pointer to `Player::velocity` raises
  focused Wibo from `46.89%` to `52.96%`, `174/181`, with `16` clean masked
  operands.
- `JetGameView`, `JetPlayerView`, and `JetActiveRuntimeView` are retired. The
  animation gate is
  `Player.presentation.jetpack_channel.anim_manager.active_animation` versus
  slot 0's visual-root animation; puff ownership is `Player::player_slot`, and
  its motion source is `Player::velocity`.
- The target still has a `0x50` frame versus candidate `0x44`. Honest aggregate
  position and trail-velocity probes regressed, so the residual remains the
  loop-index register choice and x87/local scheduling rather than fabricated
  padding or volatile state.

Cross-port Android and iOS identify this member as `cRSubHover::Jets()`.
Android also retains sibling `JetInit`/`JetUnInit` methods over the same inline
grid, closing the exact 0x214-byte `SubHover` ownership without changing the
honest 52.96% Windows partial.
