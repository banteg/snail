# update_subgoldy_bullet @ 0x43e830

Live source map for the ring/special-effect parent virtual updater.

Current match:

- `28.32%`, `229/336` candidate/target instructions, with `12` masked
  operands ok.
- A score-improving `>= tau` phase-wrap spelling was rejected because native
  uses the strict `> tau` x87 condition (`test ah, 0x41` after compare).

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

- This is intentionally a first live source map. The native function duplicates
  the list-removal/child-kill tail for several state exits, while this scratch
  currently keeps one shared removal tail for readability.
