# `update_slug_hazard_ai` recovery notes

Target: `SlugHazardRuntime::update_slug_hazard_ai @ 0x43f930` (`thiscall`, 1772 bytes, 464 instructions).

Initial source-shaped scratch reconstructs the slug hazard runtime update:

- pause-gated state switch for states `0` through `4`;
- active-state hit flash, blink texture toggles, encounter voice randomization,
  pass-player latch, engagement voice trigger, sprite position sync, nuke kill,
  and contact-target registration;
- lateral sine state with the same pass-player, removal, nuke, and contact
  tail as the active state;
- death-toss setup using the `SDI` random signed-float tag and subgame-rate
  timing lanes at `+0x9c`, `+0xa0`, `+0xa4`, and `+0xa8`;
- shared facing-angle/follow-orientation tail before `update_slug_voice_ai()`;
- inline BOD-list removal through the global `g_game_base + 0x5a8` free list.

2026-06-19 focused result: 66.15%, 464 target instructions vs 434 candidate
instructions, 0-instruction prefix, 47 masked operands ok, 1 unresolved switch
jump-table relocation, and 1 masked string-order mismatch.

Recovered shape changes that improved the scratch:

- The hit-flash gate is a nonzero progress check, not a strict positive check.
- The encounter and engagement proximity gates are strict `player.z + threshold
  > slug.z` checks, matching the native `test ah, 0x41` x87 branch pattern.
- The blink texture branches duplicate the `set_sprite_texture_ref` call and
  draw-mode store; the native block does not tail-merge that call.
- The physical switch order places state `4` before states `2` and `3`.
- The state-2 random death velocity is staged through a stack `Vector3` before
  assigning `velocity`.
- Native does not set `passed_player` in the engagement voice gate; only the
  direct pass-player z comparison sets that latch.

Remaining residuals:

- Native reserves a `0x14` stack frame while the best retained source reserves
  `0x10`. The extra native dword appears tied to state-2 x87/temporary staging,
  but adding a standalone toss-X temporary did not improve codegen.
- The inline list-removal blocks still tail-merge differently. The masked audit
  reports target `0x43ff7e` as `"List remove"` while the aligned candidate push
  is `"List remove NEXTBOD"`.
- State-2 death-direction sign correction and list-removal scheduling remain
  register/x87 allocation debt rather than missing behavior.

Rejected probes:

- Caching `owner_game` in a local regressed the prologue by saving `ebp`; direct
  member access is required for the current shape.
- Function-scope random/death locals alone emitted the same code as the
  narrower-source version and did not fix the frame size.
- Rewriting the proximity gates as `>=` kept the wrong `test ah, 0x1` branch
  pattern; strict `>` is required.
- Adding a separate `random_x` temporary after the stack `Vector3` retained the
  same 66.15% score and still emitted a `0x10` frame, so it was removed.
