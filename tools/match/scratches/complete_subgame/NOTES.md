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

Promoted to a matcher scratch on 2026-06-13. Current result: 59.89%,
89/88 instructions. The first scratch covers:

- `display_score_stats` on the score block at `game+0x3bb764`
- 6-byte run-record completion bit at `game+0xfd2b84 + cursor*6`
- completion counter and replay cursor increments
- global `byte_4b2f40 & 1` snapshot suppression
- result-record snapshot at `game+0xfd2b10`, including the six-dword stat
  copy and timer tails at `game+0xff25c0`/`game+0xff25c4`
- high-score dispatch gates for arcade, survival, and time-trial modes

Residuals: VC6 still emits a load/or/store for the run-record byte where native
uses a direct memory `or`, keeps the result-record pointer in `esi` instead of
native `ebp`, and reorders several independent result-field stores around the
six-dword copy. Do not force these with volatile or fake aliasing.
