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
instructions, 0-instruction prefix, 47 masked operands ok, 0 unresolved
operands, and 2 masked mismatches after the state switch table was named.

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
- The state switch table at `0x440008` is now audited as
  `update_slug_hazard_ai_state_jump_table`; its remaining difference is a real
  table-layout mismatch, not an unresolved relocation.
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

2026-06-21 subgame owner typing:

- `SlugHazardRuntime::owner_game` is now a shared `SubgameRuntime*`, removing
  this scratch's local generic `Game` shell.
- The consumed lanes are `subgame_pause_gate`, `subgame_rate`, and the shared
  `EnemyManager` at `+0x1270fd4`; focused Wibo remains 66.15%,
  434/464 candidate/target instructions, with 47 clean masked operands and the
  same two masked mismatches.

2026-07-11 blink-source ownership:

- The blink cadence call now targets `SubgameRuntime::advance_blink_random()`
  directly; the synthetic `BlinkRandomTable` cast and header are gone.
- The global-root address expression is retained because the native callsite
  itself passes `g_game_base +0x74618`, rather than the slug's borrowed owner
  pointer. Focused matching remains 66.15%, 434/464 instructions, with the
  same 47 clean operands and two documented mismatches.

## 2026-07-11 cRSlug owner and table relation

The receiver is now the primary `Slug` type. Windows independently proves the
method relation because the exact constructor installs table `0x497324`, whose
entry is this function at 0x43f930; Android and iOS both retain
`cRSlug::AI()`. Focused matching remains the honest 66.15%, 434/464
instructions, with 47 clean operands and the two documented structural table /
list-string mismatches. No label, padding, or dummy-local fakematch is used.
