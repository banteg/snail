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
  `player+0x29dc` is inherited `presentation.transform.basis_forward`.
- On the final row, the helper occasionally emits a sprite `0x21` puff owned by
  `game+0x3bbae4`, using the same shared `Sprite` fields as the other particle
  producers: flags, progress, lifetime, color, size, velocity, gravity, and
  position.

The owner chain is now closed through the shared types: the gauge borrows its
containing `Player` and `SubgameRuntime`; the runtime embeds that same player,
whose presentation owns the animation channel and hotspot banks while
inheriting its render transform.

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
  slot 0's `RenderableBod::object->animation`; puff ownership is
  `Player::player_slot`, and
  its motion source is `Player::velocity`.
- The target still has a `0x50` frame versus candidate `0x44`. Honest aggregate
  position and trail-velocity probes regressed, so the residual remains the
  loop-index register choice and x87/local scheduling rather than fabricated
  padding or volatile state.

Cross-port Android and iOS identify this member as `cRSubHover::Jets()`.
Android also retains sibling `JetInit`/`JetUnInit` methods over the same inline
grid, closing the exact 0x214-byte `SubHover` ownership without changing the
honest 52.96% Windows partial.

## 2026-07-14 typed particle-bank closure

- The Windows slot expression is now `particle_slots[row][column]` on the
  exact embedded `JetParticleSlot[15][2]` bank. VC6 emits the same indexed
  address as the former raw `this + ((column + row * 2 + 2) << 4)` spelling,
  preserving `52.96%`, `174/181` candidate/target instructions, and all `16`
  clean masked operands.
- Android `cRSubHover::Jets()` independently walks the same inline two-column
  rows and borrows the same Player hotspots, forward basis, velocity, and
  sprite-manager owner. No slot, Sprite, Player, or runtime pointer is retained
  beyond the update; the bank storage remains owned by `SubHover`.
- Retesting aggregate regular-position assignment after the July RNG/order
  recovery regressed to `49.30%`. Reversing the nozzle predicate regressed to
  `52.39%`; a nested `for` spelling and interleaved puff velocity/position
  stores were codegen-neutral. Those source-shape probes were reverted. The
  remaining `0x50` target versus `0x44` candidate frame is still honest loop
  counter and x87-temporary allocation debt, not missing storage ownership.

## 2026-07-14 presentation transform inheritance

The forward basis now follows `Snail`'s inherited
`RenderableBod::transform`; no separate presentation matrix owner exists at
that offset. The focused partial is byte-identical at 52.96%, 174/181
instructions, with all 16 masked operands clean.

## 2026-07-14 authored expression and lifetime cleanup

The scratch now limits row, column, position, offset, colour, and detached-puff
velocity temporaries to the lexical regions that own them. None escapes the
update. Android `cRSubHover::Jets()` independently expresses the row fraction
as `row / 14.0f`; VC6 folds that authored division to the native
`0.0714285746f` multiply. The projected nozzle position now uses the shared
in-place `Vector3::operator+=`, and the sprite flag update is the ordinary
`flags |= 0x800` member expression. These source-shaped changes are
byte-identical at 52.96%, 174/181 instructions, a 0x44 candidate frame, and 16
clean masked operands.

The remaining native 0x50 frame was audited without adding synthetic storage.
A borrowed pointer to the persistent grid sprite position regressed to 45.20%
and introduced two masked-constant misalignments. Whole-vector grid assignment
reached 49.30%; post-tested outer-loop spelling reached 52.39%; member and
free-function scaled-vector expressions reached 51.83%. A real detached-puff
`Vector3` velocity owner grew the candidate frame only to 0x4c and regressed to
50.14%; combining it with aggregate grid assignment fell to 44.82%. All were
reverted. Native's stack-spilled column and saved-register x/y ownership remain
honest compiler-allocation debt, not a reason to add padding, volatile locals,
or address-taking without a semantic owner.
