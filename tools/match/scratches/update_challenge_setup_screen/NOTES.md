# update_challenge_setup_screen @ 0x416370

First structured scratch for the challenge/time-trial setup updater. The
screen controller layout is shared through `challenge_setup_screen.h`, and its
`game` pointer is now recovered as a borrowed `SubgameRuntime*`.

## Recovered behavior

- Always hides gameplay score widgets before processing the setup screen.
- Mode `0` and mode `4` consume next/previous level button clicks, reload the
  frontend level definition, refresh the level-name widget, and update the
  previous/next disabled flags against level `0` and
  `RuntimeConfig::highest_galaxy_route_index`.
- Mode `1` consumes Back, Play, and Replay for the challenge sliders. The live
  slider values are persisted into the RuntimeConfig completion-source fields as
  `(int)(value * 100.0f + 0.1f)`.
- Mode `4` refreshes the Time Trial best-time widget through the same
  member-style `format_time_trial_string` call shape used by `update_subgame`,
  then shows or hides the Replay button from the selected replay record.
- Replay launch sets `SubgameRuntime::selected_level_record_active` and stores
  `selected_level_record` as either the owned
  `HighScoreBank::survival_pending_record` or the selected
  `HighScoreBank::time_trial_route_records` entry.

## Match state

Retained result: 80.68%, 355 target instructions, 354 candidate instructions,
8-instruction prefix, and 35 clean / 0 unresolved / 0 mismatched masked
operands.

The source is shaped as a sparse `switch` with `case 4` first. VC6 emits the
native `sub eax, 0; je mode0; dec eax; je mode1; sub eax, 3` dispatch from that
shape, while ordinary `if/else` kept mode `0` as the physical fallthrough and
regressed the body alignment.

The selected Time Trial replay record is not kept as a long-lived pointer.
Native loads the record's active flag for Replay button visibility, then
recomputes the record pointer after the Replay click destroys the screen.

Remaining residuals:

- The candidate is one instruction shorter, so the initial branch-label targets
  are one byte/label off despite the instruction stream lining up through the
  mode `4` body.
- Register choice differs in the Time Trial replay-tail pointer calculation
  and in the challenge slider/replay store block.

Rejected probes:

- Keeping a `Game*` local made VC6 save `ebx` and dropped the score to 62.36%.
- A direct high-level `if/else` mode dispatch improved neither the sparse
  switch branch labels nor the physical case order.

2026-06-20 type cleanup: `TimeTrialStringFormatter` now comes from the shared
method-only header. This keeps the existing member-style `ecx = game+0xff25e0`
source shape while removing the duplicate local type; the focused score stayed
80.68%.

2026-06-21 validation after the shared `SubgameRuntime` front-controller
promotion: focused Wibo is still `80.68%`, `354/355`, prefix `8/355`, and the
masked audit is now clean at `35 ok / 0 unresolved / 0 mismatch` under the
current symbol set.

2026-07-11 ownership closure: the former raw challenge replay and Time Trial
record windows are both owned by `SubgameRuntime::high_score_bank`; the replay
selection latch and pointer are direct `SubgameRuntime` fields. The ownership
rewrite is codegen-neutral at 80.68%, 354/355 instructions, prefix 8/355, and
35 clean masked operands.

2026-07-11 config-owner pass: the route limit and both completion slider
sources now come from the shared `RuntimeConfig` aggregate. Focused Wibo stays
at 80.68%, 354/355 instructions, prefix 8/355, with all 35 operands clean.
