# Windows RE Batch 2026-03-24

This is the current runtime-blocked packet for the automated port loop.
It is also the active working dossier for the current loop target.

Rule for this batch:
- no Zig edits
- no top-level status-ledger churn
- update this packet or one focused runtime note only
- if you update a focused runtime note, reflect the outcome back into this packet before rerunning the loop

Boundary for this dossier:
- owner boundary: outer bridge and attachment-exit handoff controllers
- safe-to-code boundary: none until the batch is complete
- scaffold kill-list to prepare for the next replacement decision:
  - `OuterBridgeRequest` as the conceptual center of bridge routing in `zig/src/main.zig`
  - grounded or trampoline attachment-exit settle proxy paths in `zig/src/gameplay.zig`

## Goal

Capture the Windows-side evidence needed to unblock the next real replacement batch.

Do these in order:
1. failure handoff
2. completion handoff
3. attachment-exit consumers
4. outer subgame startup and bridge flags

## 1. Failure Handoff

Use [docs/re/windows-debugging-wants.md](../../docs/re/windows-debugging-wants.md) sections 2 and 4 as the source checklist.

Required outputs:
- the exact selector for respawn vs final loss
- the visible-life decrement commit point
- whether hazard death and floor-gap fall share the same late handoff

Capture notes:
- break on `initialize_subgoldy_death`, `update_cutscene`, `update_subgoldy`, `update_subgoldy_resurrect`
- watch `player + 0x41d`, `+0x424`, `+0x42c`, `+0x430`, `+0x434`, `+0x438`
- record one spare-life postal death, one no-life postal death, and one challenge or time-trial death

## 2. Completion Handoff

Use [docs/re/windows-debugging-wants.md](../../docs/re/windows-debugging-wants.md) section 3.

Required outputs:
- first frame where `completion_handoff_active` becomes true
- first call to `initialize_completion_screen`
- first call to `complete_subgame`
- the exact owner of the `2.0s` voice gate and `5.0s` fade

Capture notes:
- break on `update_subgoldy`, `update_cutscene`, `initialize_completion_screen`, `complete_subgame`
- watch `player + 0x440`, `+0x444`, `+0x448`, `+0x44e`

## 3. Attachment-Exit Consumers

Use [docs/re/windows-debugging-wants.md](../../docs/re/windows-debugging-wants.md) section 4 and [docs/re/windows-cdb-session-2026-03-15.md](../../docs/re/windows-cdb-session-2026-03-15.md).

Required outputs:
- the direct consumers of `post_follow_value_b`
- the late retirement path that actually clears `attachment_exit_pending` after swept re-entry
- whether overlapping `0x40` / `0x80` probes can both succeed in one tick

Capture notes:
- break on `end_track_attachment_follow_state`, `update_subgoldy`, `update_cameraman`
- watch `player + 0x41d`, `+0x42c`, `+0x430`, `+0x434`, `+0x44c`, `+0x44d`
- keep ARCADE007 as the first repro lane unless a better shipped path family appears

Current 2026-03-24 result:
- fresh artifact: `artifacts/snailmail-windbg.log`
- fresh focused pack: `artifacts/cdb-attachment-reentry-pack-live-09510d9c-2026-03-24.txt`
- `ARCADE007` remains the right first repro; repeated `HalfPipe` exits still hit `end_track_attachment_follow_state`
- repeated `attachment_end_enter` hits all used the live player `0x09510d9c` and reported `seg = 0x1b`
- `post_follow_value_a` (`player + 0x42c`) is now runtime-confirmed as a real camera input in the captured window
  - the live access watch fired at `0x4465c1`
  - that address sits inside `update_cameraman`
  - the read happens while `attachment_exit_pending` is still set
- `post_follow_value_b` (`player + 0x430`) still has no confirmed downstream consumer in the captured window
  - the observed `post_b_access` hits were the helper-side writes in `end_track_attachment_follow_state`
  - no later direct read was captured during this pass
- the only late `attachment_exit_pending` clear captured again was `0x43ce75`
  - that matches the already narrowed jetpack-only branch
  - it still does not identify the generic post-swept-re-entry retirement lane
- `exit_gate_b_set` still fired at `attachment_exit_progress = 0x3f2aaaab` with negative `world_y`, which keeps the older gate-B fall threshold interpretation intact
- the narrowed re-entry pack attached cleanly and stayed live, but this pass still did not hit:
  - `0x43bdf0` / `0x43bec5` swept re-entry probes
  - `0x43c355` pending branch
  - `0x43bf6f`, `0x43c06d`, or `0x43c3ea` non-jetpack clear sites
  - `0x43c3f8` re-entry voice lane

Net status for section 3:
- one open question is materially narrowed: `post_follow_value_a` is confirmed live camera carryover, while `post_follow_value_b` remains unconsumed in the observed window
- section 3 is still incomplete because the real post-swept-re-entry retirement path and the overlapping `0x40` / `0x80` probe behavior were not hit in this session
- if this section is revisited, keep the current focused pack and bias the repro toward skimming back onto the path or adjacent floor immediately after a `HalfPipe` exit

## 4. Outer Bridge

Use [docs/re/windows-debugging-wants.md](../../docs/re/windows-debugging-wants.md) section 5.

Required outputs:
- the saved-owner producers still missing behind states `26/27/28`
- the startup meaning of the fresh-start bytes
- enough evidence to decide whether the next replacement target is the literal outer bridge or attachment-exit carryover

Capture notes:
- break on `initialize_subgoldy`, `initialize_subgame`, `build_subgame_level`, `update_subgame`
- also break on `update_new_game_menu`, `update_main_menu`, `update_high_score_screen`, `exit_high_score_screen`
- watch `[controller + 0x94]`, `[controller + 0x98]`, and the replay scratch lanes already listed in the debugger wants doc

## Done Criteria

This batch is complete only when all of these are true:
- there is at least one fresh Windows artifact or note for each section above
- the next replacement target is decision-complete enough to choose between outer bridge and attachment-exit carryover
- no Zig proxy patch was made during the batch

Current batch status:
- section 3 now has fresh partial Windows evidence, but not its full done criteria
- sections 1, 2, and 4 still need fresh Windows captures before the replacement decision is ready

## Expected Next Replacement Boundary

If the bridge wins the next replacement target:
- extract the outer bridge and saved-owner state machine out of `zig/src/main.zig`

If attachment-exit carryover wins the next replacement target:
- extract the attachment-exit carryover owner and follow-exit controller out of `zig/src/gameplay.zig`
