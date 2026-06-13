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

Promoted to a matcher scratch on 2026-06-13. Current result: 74.16%,
90/88 instructions, 7/88 prefix. The current scratch covers:

- `display_score_stats` on the score block at `game+0x3bb764`
- 6-byte run-record completion bit at `game+0xfd2b84 + cursor*6`, now
  modeled as bit 3 (`completed`) in the first byte of the record
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
  memory `or`, but it documents the recovered bit-level semantics without
  changing the score.

Residuals: VC6 still emits a load/or/store for the run-record byte where native
uses a direct memory `or`, and reorders several independent result-field stores
around the six-dword copy. Result-record pointer ownership now matches native
`ebp`; do not force the remaining byte-OR or store-schedule residuals with
volatile or fake aliasing.
