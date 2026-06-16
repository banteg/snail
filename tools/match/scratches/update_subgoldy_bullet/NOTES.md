# update_subgoldy_bullet @ 0x43e830

Live source map for the ring/special-effect parent virtual updater.

Current match:

- `68.48%`, `327/336` candidate/target instructions, with `33` masked
  operands ok.
- A score-improving `>= tau` phase-wrap spelling was rejected because native
  uses the strict `> tau` x87 condition (`test ah, 0x41` after compare).
- The method is modeled as `void`: native exits do not establish a meaningful
  return value, and the earlier `void*` surface forced extra return-value
  cleanup in the candidate.

Evidence:

- Parent `+0x80` is a state word, not a boolean. Observed states are `0`
  inactive, `1` normal orbit/update, `2 -> 3` target-collapse transition, and
  `4 -> 5` expansion/removal transition.
- Parent `+0x1d4/+0x1d8` are transition progress and transition step.
- Parent `+0x1dc` gates the sine-driven `position.x` oscillation using
  `active_phase +0x1e0` and `active_phase_step +0x1e4`.
- The parent child-array evidence remains consistent with the other ring
  scratches: ten particles at `+0x90`, stride `0x20`.
- The updater reads owner `+0x2964` as a target vector during state `3`, but
  that player-side field is intentionally not promoted from this single use.

Type consolidation:

- `RingOrSpecialEffectParent::state`, `transition_progress`,
  `transition_step`, `oscillate_x`, and `RingEffectRateSource::paused` are now
  in `tools/match/include/ring_special_effect_types.h`.
- `RingOrSpecialEffectParticle` still stays scratch-local. The layout is
  consistent, but the method return-type surface is not yet consistent enough
  across updater/emitter/initializer scratches to promote cleanly.

Residual:

- Native duplicates the list-removal/child-kill tail for the three removal
  exits. The scratch now spells those exits explicitly, which raised the match
  from `28.32%` to `68.48%`.
- Remaining residuals are mostly switch and stack-shape differences: VC6 still
  collapses case `0`/default into a `state - 1` jump table, while native uses a
  direct `0..5` jump table; the transition-vector interpolation also uses fewer
  stack temporaries than native.
