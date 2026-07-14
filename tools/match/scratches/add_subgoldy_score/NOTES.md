# add_subgoldy_score

Proof-grade match: 100.00%, 58/58 instructions, with six clean masked
operands.

- `score_kind` selects fixed point awards for regular hazards/parcels and uses
  `bonus_score` only for score kind `5`.
- 2026-06-18 bucket enum pass: display strings and producer callsites now back
  the shared names in `score_buckets.h`:
  `SUBGOLDY_SCORE_GARBAGE`, `SUBGOLDY_SCORE_SLUG`, `SUBGOLDY_SCORE_RING`,
  `SUBGOLDY_SCORE_PARCEL_COLLECT`, `SUBGOLDY_SCORE_PARCEL_DELIVER`, and
  `SUBGOLDY_SCORE_BONUS`.
- The six buckets at `Player+0x310` accumulate per-kind points; `Player+0x2e4`
  is the total subgame score.
- Crossing a 50,000-point boundary increments `Player+0x4340` up to a visible
  life stock cap of `9`.
- The score sound `0x2c` only plays after the 50,000-point threshold awards a
  life, and is gated off while `SubgameRuntime::level_mode` or the root-owned
  `FrontendFade::state` is nonzero.
- The function is a `void` mutator in source terms.
- `END=0x44037e` excludes the native switch jump-table data that follows the
  final `ret`.
- The earlier `89.66%` scratch put the sound gate after the threshold/life
  award block. The target branches directly to the epilogue when the threshold
  is not crossed or the visible life stock is capped, matching the IDA and
  Binary Ninja decompile nesting. Moving the sound gate inside `if (lives < 9)`
  recovers the native epilogue placement and proves the helper.
- 2026-06-20 Player header consolidation: the current shared `player.h`
  declaration preserves the proof-grade instruction stream and switch-table
  audit (`100.00%`, `58/58`, `6 ok / 0`), so this scratch no longer carries a
  compact local `Player` shell.
- 2026-06-16 shared-audio probe: replacing the local `SoundEffectManager`
  call view with `audio_system.h` produced the same switch-table audit
  regression (`5 ok, 1 mismatch`). Keep the compact local sound view here too.
- 2026-06-20 narrow sound-manager header pass: `SoundEffectManager` was split
  into `sound_effect_manager.h`, with `audio_system.h` including that call
  surface. Including the narrow header here is codegen/audit neutral at the
  accepted baseline (`89.66%`, `58/58`, `39/58` prefix, `6 ok / 0`), avoiding
  the broad `audio_system.h` switch-table regression while removing this
  scratch's local sound-manager copy.
- 2026-06-20 life-award sound nesting: moved the game-state sound gate inside
  the visible-life increment block. Focused Wibo now matches at `100.00%`,
  `58/58` instructions, `58/58` prefix, with `6 ok / 0` masks.
- 2026-07-14 root gate ownership: the two remaining raw game offsets now use
  `GameRoot::subgame.level_mode` and `GameRoot::fade.state`. Focused Wibo stays
  exact at `58/58` instructions with all six operands clean.
