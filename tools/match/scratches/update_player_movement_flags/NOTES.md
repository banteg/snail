# update_player_movement_flags @ 0x43a1a0

Source-shaped match: 93.75%, 38/50 instruction prefix, 46/50 candidate/target
insns.

This helper maps the player movement selector at `+0x308` onto the
`movement_flags` mask at `+0x338` and the fire cadence step at `+0x2734`.
When the mask changes from `previous_movement_flags`, it refreshes the
presentation controller at `+0x2984` through `set_snail_weapon`.

Recovered selector table:

- selectors 0, 1, and 2 produce masks `1`, `2`, and `4` with step
  `0.074074075f`;
- selectors 3, 4, and 8 produce masks `8`, `16`, and `144` with step
  `0.111111104f`;
- selectors 6 and 7 produce masks `64` and `192` with step `0.13333334f`;
- selector 5 produces mask `32` with step `0.06666667f`; and
- out-of-range selectors produce mask `129` with step `0.06666667f`.

Residual:

- Native keeps a separate equal-mask block after the changed-mask return,
  reloading `movement_flags` into `ecx` before storing
  `previous_movement_flags`. VC6 tail-merges the equal branch into the changed
  branch's final return sequence for the clean C++ spelling. The old
  38/64-instruction reading was stale; the current curated extent is 50 target
  instructions with the first 38 matching exactly.
- 2026-06-16 shared-`Player` probe: the offsets now exist in `player.h`, but
  including it here changed the switch-table relocation audit from `2 ok` to
  `1 ok, 1 mismatch` (`$L441` instead of
  `update_player_movement_flags_jump_table`). Keep the compact local shell until
  that symbol-shape issue has a targeted fix.
- 2026-06-16 equal-branch probes: inverting the final comparison or spelling the
  equal path as an explicit `else` kept the 93.75% score but dirtied the
  jump-table symbol audit (`$L321`/`$L322` versus the curated table symbol).
  Keep the baseline shape unless a source-plausible table-owner fix appears.
- 2026-06-18 type/name sync: the compact local `Player` shell now marks
  `movement_flags` and `previous_movement_flags` as `unsigned int`, matching
  `tools/match/include/player.h`, while still avoiding the full shared include
  because it changes the curated jump-table symbol. Focused Wibo remains
  93.75%, 46/50 candidate/target instructions, with 2 masked operands OK. The
  IDA artifact was updated from raw `this+206/207/2509` indexing to
  `Player::movement_flags`, `previous_movement_flags`,
  `movement_fire_progress_step`, and `presentation`.
- 2026-06-19 equal-tail audit: decompiler-shaped `if (equal) { store; } else
  { set_snail_weapon; store; }`, explicit equal early-return, an
  `unchanged_flags` local, a typed `previous_flags` pointer, source label layout
  with the equal block after the changed return, and returning `movement_flags`
  directly from the equal branch all compile back to the same 93.75% candidate
  with clean `2 ok` masks. Keep the clearer baseline final branch; the only
  residual remains VC6 tail-merging the native duplicate equal-mask epilogue.
- 2026-06-20 unresolved-layout cleanup: the local presentation receiver is now
  named `PlayerMovementPresentationView`, keeping this scratch out of the
  shared `PlayerPresentationController` layout group. Full `player.h` remains
  rejected for this helper because it changes the jump-table relocation audit,
  while the compact shell keeps the 93.75% focused match and clean `2 ok`
  masks.
