# update_challenge_setup_screen @ 0x416370

First structured scratch for the challenge/time-trial setup updater. The
screen controller layout is shared through `challenge_setup_screen.h`; the
larger game-root offsets stay scratch-local until more callers agree.

## Recovered behavior

- Always hides gameplay score widgets before processing the setup screen.
- Mode `0` and mode `4` consume next/previous level button clicks, reload the
  frontend level definition, refresh the level-name widget, and update the
  previous/next disabled flags against level `0` and `data_4df9b8`.
- Mode `1` consumes Back, Play, and Replay for the challenge sliders. The live
  slider values are persisted into `data_4df958` and `data_4df960` as
  `(int)(value * 100.0f + 0.1f)`.
- Mode `4` refreshes the Time Trial best-time widget through the same
  member-style `format_time_trial_string` call shape used by `update_subgame`,
  then shows or hides the Replay button from the selected replay record.
- Replay launch marks `game +0xff25d0` and stores `game +0xff25d4` as either
  the challenge replay record at `game +0xfb3050` or the selected Time Trial
  record at `game +0x944150 + selected * 0x1fac0`.

## Match state

Retained result: 80.68%, 355 target instructions, 354 candidate instructions,
8-instruction prefix, and 33 clean / 2 unresolved / 0 mismatched masked
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
- `data_4df9b8` is the same route-limit global used by the galaxy scratches,
  but it is still an unresolved masked operand in this scratch.
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
