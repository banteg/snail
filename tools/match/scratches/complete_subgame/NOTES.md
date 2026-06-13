# Dossier — bridge result-bank snapshot (match deferred; cluster 10)

complete_subgame @ 0x438700 = cRSubGame::Complete(bool). Semantics:

- display_score_stats on the score block (game+0x3B 73 64 region)
- marks the per-run completion bit (|= 8) in the 6-byte-stride run table
  at game+0xFD2A04-ish indexed by the run counter at game+0xFF25DC,
  increments both counters
- unless global byte_4B2F40 & 1: snapshots the run into the result bank
  at game+0xFD29F0.. (score, the 0x18-byte stat block, level ids, mode,
  timers from game+0x126...), sets the result-active dword = 1
- the (mode != 1 || flag) && !replay-suppress && completed gate then
  dispatches add_time_trial_high_score / the postal-challenge high-score
  adds per mode — the saved-owner producers the bridge checklist hunts
  live downstream of these calls

Match deferred: app/bridge cluster (board order last); the field map
above is what the Zig bridge lanes need for verification.

## Scratch status

Promoted to a matcher scratch on 2026-06-13. Current result: 75.28%,
90/88 instructions, 7/88 prefix. The current scratch covers:

- `display_score_stats` on the score block at `game+0x3bb764`
- 6-byte run-record completion bit at `game+0xfd2b84 + cursor*6`, now
  modeled as bit 3 (`0x08`, completed) in the first byte of the record
- completion counter and replay cursor increments
- global `byte_4b2f40 & 1` snapshot suppression
- result-record snapshot at `game+0xfd2b10`, including the six-dword stat
  copy and timer tails at `game+0xff25c0`/`game+0xff25c4`
- high-score dispatch gates for arcade, survival, and time-trial modes

Earlier progress: rewriting the high-score mode checks as a direct
`switch (level_mode)` improved the scratch from 59.89% to 62.50% and brought
the candidate back to instruction-count parity. This also matches the native
dispatch shape more closely: arcade for mode 0, survival for mode 1, and
time-trial for mode 4.

Latest progress: scoping `ResultRecord* record = &result_record` to the
snapshot block recovers native `ebp` ownership for the high-score record
argument and improves the scratch from 62.50% to 74.16%. The declaration must
remain at the top of the snapshot block: VC6 then reserves `ebp` up front but
schedules the `lea ebp, [game+0xfd2b10]` near the native result-tail stores.
Moving the declaration later makes VC6 fall back to `esi`.

Tooling-pass progress: `snail match diff --regions` isolates the two useful
residual clusters: the 6-byte run-record flag store and the result snapshot
store schedule. Reordering only independent snapshot assignments to load the
difficulty/source-arg tails before storing `score_tail` improves the scratch
from 74.16% to 75.28%. The same region report shows the high-score dispatch
tail is still structurally stable; the remaining score comes from the byte-OR
shape and register allocation in the snapshot block.

Rejected experiments:

- An over-shaped `ResultRecord*` snapshot rewrite with staged field stores
  regressed to 42.22%; reverted.
- A high-score-only `ResultRecord*` local did not change the match at 62.50%;
  reverted.
- Function-scope or post-display `ResultRecord* record` declarations recovered
  `ebp` but placed the `lea` too early and topped out at 73.03%/71.91%;
  keeping the declaration inside the snapshot block is better.
- Declaring `record` immediately before the active/source-tail stores regressed
  to 62.50% and used `esi` for high-score record pushes.
- An explicit `level_mode` snapshot local regressed to 64.04%.
- Signed-vs-unsigned byte spelling for the run record did not change codegen.
- A bitfield spelling for the completed flag did not recover native's direct
  memory `or`.
- A flags-byte spelling for the completed bit also left the contextual codegen
  unchanged, even though standalone `snail match idioms` probes show VC6 can
  emit direct `or byte [base + index*6], 0x8` for both byte-array and bitfield
  stride-6 forms.
- Locals for the delayed difficulty/source-arg snapshot fields did not change
  codegen; a `source_score_tail` preload local only reproduced the same 75.28%
  schedule as the simple assignment order.
- 2026-06-13 tooling recheck: the new `snail match idioms` stride-6 probes
  still show VC6 can emit a direct `or byte [base + index*6], 0x8` in
  isolation, but both struct-field and byte-stride spellings in this full
  scratch keep the contextual load/or/store sequence. A `replay_cursor` local
  regressed to 58.76% by moving the index into different registers. Moving the
  `score_tail` assignment before the six-dword stats copy kept the same score
  but stored too early, before `rep movsd`, so keep the current snapshot order.
- 2026-06-13 post-push tool pass: `snail match diff --regions
  --region-context 1` confirms the remaining useful clusters are still the
  byte-OR and result-snapshot schedule. The `sparse-switch-0-1-4` idiom probe
  matches the high-score dispatch tail, so that switch shape is not the
  blocker. Reordering the post-copy fields to store `score_tail`,
  `level_index_tail`, `level_arg_tail`, then `difficulty_tail` kept the same
  75.28% headline score but worsened the localized snapshot region; delaying
  only `source_arg_tail` until after the first timer snapshot regressed to
  74.16%. Keep the current store order.

Residuals: VC6 still emits a load/or/store for the run-record byte where native
uses a direct memory `or`, and the result snapshot still differs in register
allocation around the difficulty/timer fields. Result-record pointer ownership
now matches native `ebp`; do not force the remaining byte-OR or store-schedule
residuals with volatile or fake aliasing.
