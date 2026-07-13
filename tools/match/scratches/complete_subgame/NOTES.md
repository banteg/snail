# Dossier — bridge result-bank snapshot (match deferred; cluster 10)

complete_subgame @ 0x438700 = cRSubGame::Complete(bool). Semantics:

- `Player::display_score_stats` on the runtime's embedded Player
  (`game+0x3bb764`)
- marks the per-run completion bit (|= 8) in the 6-byte-stride run table
  at game+0xFD2A04-ish indexed by the run counter at game+0xFF25DC,
  increments both counters
- unless `g_cheat_state.flags & 1`: snapshots the run into the result bank
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

- `Player::display_score_stats` on the embedded Player at `game+0x3bb764`
- 6-byte run-record completion bit at `game+0xfd2b84 + cursor*6`, now
  modeled as bit 3 (`0x08`, completed) in the first byte of the record
- completion counter and replay cursor increments
- global `CheatState::flags & 1` snapshot suppression
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
  replay-level, replay-speed, and difficulty lanes kept the same
  75.28% headline score but worsened the localized snapshot region; delaying
  only `source_tail` until after the first timer snapshot regressed to
  74.16%. Keep the current store order.
- A follow-up `snail match dump` comparison made the native post-copy schedule
  explicit (`score_tail`, replay-level/difficulty/replay-speed lanes, timer A,
  `source_tail`, timer B), but spelling that order directly in the scratch
  regressed to 74.16%. Leave this as register-allocation/scheduling residual,
  not a source-order mandate.
- 2026-06-14 recheck: the current localized diff still isolates the same
  byte-OR and snapshot-scheduling clusters, and the `byte-array-stride6-or`,
  `byte-field-stride6-or`, and `bitfield-stride6-set` idiom probes all emit
  the native direct-memory `or byte [..], 0x8` in isolation. Naming the selected
  run record as `RunRecord* run_record` in the full scratch still emitted the
  same contextual load/or/store sequence and was reverted as neutral churn.
- 2026-06-15 reference-audit pass: the curated reference manifest named
  `byte_4b2f40` and the high-score bank offset, clearing the masked operand audit
  without changing the normalized score. The remaining residual is still the
  byte-OR and snapshot scheduling shape below.
- 2026-06-16 score-view split was a temporary sparse-layout interpretation.
  The later complete-extent proof below supersedes it: the apparent overlap is
  the single embedded `Player`, not a separate `RunScoreStats` object plus
  runtime aliases.
- 2026-06-18 shared-record pass: `tools/match/include/sub_solution.h`
  now models the full 0x1fac0 high-score/replay record starting at
  `game+0xfd2b10`, including the 6-byte replay run table and aligned replay
  scalar fields. `complete_subgame` now writes `current_high_score_record`
  instead of a local 0x54 `ResultRecord` prefix, and the replay bonus source
  lanes are stored as `challenge_speed_value` /
  `challenge_difficulty_value`.
  Focused Wibo remains at the pinned 75.28%.
- 2026-06-18 decompiler-sync pass: the narrow BN/IDA `SubgameRuntime` headers
  now carry the sparse proven runtime layout through `sub_high_score`,
  `current_high_score_record`, replay cursor, selected-level gates, timers, and
  route-active state. BN now renders the high-score dispatch as calls through
  `runtime->sub_high_score` and `runtime->current_high_score_record` instead
  of raw `runtime + 0x68b4c8` / `runtime + 0xfd2b10` offsets.

Residuals: VC6 still emits a load/or/store for the run-record byte where native
uses a direct memory `or`, and the result snapshot still differs in register
allocation around the difficulty/timer fields. High-score record pointer ownership
now matches native `ebp`; do not force the remaining byte-OR or store-schedule
residuals with volatile, raw offset macros, or fake aliasing. Treat this
scratch as pinned unless new source evidence explains the contextual byte-OR.

## 2026-07-10 ownership audit

The native call tail makes the lifetime boundary explicit: `ebp` is the
address of `SubgameRuntime::current_high_score_record`, while `ecx` is the
address of the same runtime's embedded `sub_high_score`. The three `add_*`
helpers borrow that working record, normalize some metadata in place, and copy
its value into bank-owned result/ranking arrays; no helper stores the input
pointer. The replay run table is therefore owned by the working record, and
the selected-level bytes are only dispatch gates, not alternate owners.

A post-increment cursor spelling regressed the focused match to `71.91%` and
was reverted. Moving the completion-bit operation behind an inline record
method stayed at `75.28%` but worsened the localized address shape and was also
reverted. The direct-memory byte `or` remains an honest compiler-context
residual rather than a reason to introduce an alias or volatile fakematch.

## 2026-07-11 Player owner closure

The exact `0x4364`-byte `Player` begins at `SubgameRuntime +0x3bb764` and ends
at the first runtime track cell. `complete_subgame` therefore snapshots
`player.total_score`, the six-dword `player.stopwatch`, `player.score_tail`,
`player.startup_track_index`, and `player.completion_handoff_active`; none are
independent SubgameRuntime fields. BN has only one reference to
`Player +0x300`, the dword copy into `SubSolution::score_tail`, so that
name remains deliberately narrow.

Removing `RunScoreStats` and the sparse runtime overlay preserves the honest
75.28%, 90/88-instruction result with eight clean operands. An explicit local
for `player.score_tail` was codegen-neutral and was not retained. The two known
residual clusters remain the contextual replay-byte OR and snapshot scheduling;
ownership no longer depends on either mismatch.

## 2026-07-11 CheatState owner closure

The address previously described by its low-byte consumers is the complete
`0x10`-byte global `CheatState`: `flags` at `+0x00`, an unused dword at `+0x04`,
and the eight-byte recent-text buffer at `+0x08`. The next curated global starts
exactly at `0x4b2f50`, independently bounding that extent. Bit 0 suppresses the
completion snapshot here, while bit 1 relaxes the subgoldy environment gate;
initialization and per-frame cheat parsing operate on the same owner.

Promoting `g_cheat_state` through all four consumers preserves the focused
scores and operand audits for `complete_subgame`, `update_subgoldy`,
`run_frame_update`, and `initialize_game_assets_and_world`. The three CheatState
methods remain exact, and the shared extern lint is now clean.

## 2026-07-11 hazard-frequency ownership

The two former `source_timer_*` dwords at `SubgameRuntime +0x125ffd8` and
`+0x125ffdc` are the live normalized `Garbage:` and `Salt:` frequencies:

- `load_level_definition_file` parses the authored percentage fields into the
  embedded `SubTracks` owner;
- `build_subgame_level` divides them by 100, or restores the same floats from
  a selected replay record;
- `update_subgame` uses them in the garbage and salt random-spawn thresholds;
- `complete_subgame` bit-copies them into the working `SubSolution`, and
  compact replay serialization preserves the same two lanes.

The shared runtime and replay headers now use `garbage_frequency` and
`salt_frequency`, with explicit integer-bit aliases only where the native
snapshot uses integer moves. Focused matching remains the honest pinned
75.28%; this is ownership recovery, not instruction shaping.

## 2026-07-13 canonical Binary Ninja replay

The stable `SubgameRuntime*` receiver ABI is now replayed together with the
complete owner map. The tracked BN export contains no raw offsets: the snapshot
comes from the embedded `Player`, lands in `current_high_score_record`, and is
dispatched through the embedded `sub_high_score` bank. A health check pins that
owner graph. Matching source remains unchanged at the honest 75.28% frontier.
