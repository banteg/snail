## 2026-03-23 18:33 - Iteration: tighten installed attachment entry sweep

### Target
- Installed attachment entry in `try_enter_track_attachment_from_swept_motion` parity

### Why this target
- Attachment follow is still central gameplay scaffolding, and the Zig port still depended on a source-row fallback because the geometric entry test was weaker than the recovered Windows helper.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile of `try_enter_track_attachment_from_swept_motion` (`0x42c770`) scans the installed sample array from `sample_count - 1` down to `0`.
  - The helper skips candidate samples when `sample + 0x14` is negative, which matches the sampled record's `basis_up.y` lane in the current runtime-structure notes.
  - The helper uses raw local sweep thresholds: lateral span `width/2 +/- 0.3`, start `y >= -0.2`, start `z` inside the sample `delta_length`, and end `y <= 0.001`.
- Likely:
  - The old Zig row-progress window could miss valid installed-entry candidates on curved attachments because Windows does not limit the scan to the source-row progress band.
- Unknown:
  - Whether the remaining source-row fallback can be removed entirely once more live installed-entry cases are verified.

### Zig changes
- `zig/src/gameplay.zig`
- Replaced the windowed installed-entry scan with a dedicated tail-to-head sweep helper that matches the recovered Windows thresholds and upside-down-sample rejection.
- Kept the source-row fallback intact as a backup path, but narrowed when the geometric sweep fails.
- Added focused tests for deep-sample matching and inverted-sample rejection.

### Verification
- Ran `zig fmt zig/src/gameplay.zig`.
- Ran `zig build test`.
- Added unit coverage that proves the new sweep can match a deep tail-side sample and refuses an upside-down sample even when the other local thresholds are satisfied.

### Remaining gaps
- The source-row fallback still exists.
- The port still does not model the full Windows installed-bank ownership or the family-specific nonlinear entry and exit branches.

### Next target
- Recover enough of the remaining installed-bank and nonlinear kind-`42` entry semantics to remove more of the source-row fallback without guessing.

## 2026-03-23 18:45 - Iteration: restore native negative ring shove

### Target
- Runtime ring kinds `3/7` motion parity in `handle_subgoldy_collisions` / `update_subgoldy`

### Why this target
- The Zig runtime still treated native `3/7` ring collisions as the long authored slow-status timer, while Binary Ninja now pins both the collision write and the short recovery math tightly enough to replace that guess.

### Original behavior evidence
- Confirmed:
  - `handle_subgoldy_collisions` (`0x444cf0`) routes ring kinds `3/7` to the `sfx 43` branch, writes `-0.1` into `player->velocity.z`, and skips `add_subgoldy_score`.
  - `update_subgoldy` (`0x43b120`) adds `track_center_x^2 * 0.004 * 0.25` to `player->velocity.z` each tick while that lane is negative, then clamps it back to `0`.
  - The same Win32 runtime still quantizes gameplay world `x` with `floor(x + 4.0)` and clamps the player to `[-4.0, 4.0]`, which keeps `track_center_x` at `4.0` for this motion slice.
- Likely:
  - Once the negative shove crosses zero, Windows hands control back to the broader forward-speed controller rather than leaving the velocity lane at `0`.
- Unknown:
  - The exact positive-speed controller that repopulates `Player.velocity.z` after negative rings or garbage hits is still not mapped end-to-end.

### Zig changes
- `zig/src/gameplay.zig`
- Added a runner-local native `velocity.z` override for runtime ring kinds `3/7`, seeded from the recovered `-0.1` write and advanced with the recovered zero-crossing recovery.
- Extended track stepping to handle brief backward row motion so the recovered shove actually moves Turbo backward.
- Removed the old runtime path that reused `slow_ticks` for native `3/7` collisions; authored `.slow` annotations still keep the existing timer-based behavior.
- `docs/rewrite/subsystem-status.md`
- `docs/re/audio-callsite-map.md`
- Updated the runtime-status and audio notes so they no longer claim the negative-velocity lane is still missing.

### Verification
- Ran `zig fmt zig/src/gameplay.zig`.
- Ran `zig build test`.
- Added unit coverage for the seeded `-6 rows/second` shove, the first backward row step, zero `slow_ticks` on native `3/7` collisions, and the handoff back to the base forward-speed scaffold after the override clears.

### Remaining gaps
- The broader native forward-speed controller behind `Player.velocity.z` is still unresolved.
- Garbage impacts still write into the Zig high-level motion scaffold instead of the same recovered velocity owner.

### Next target
- Port the garbage-impact motion owner so both native negative rings and garbage hits feed the same recovered velocity controller.

## 2026-03-23 18:58 - Iteration: route respawn through outer opcode 28

### Target
- Respawn ownership in `update_subgoldy_resurrect` / outer bridge handoff

### Why this target
- The outer bridge remains the top architectural risk, and Binary Ninja evidence now pins one missing lane tightly enough to replace a Zig-side special case: respawn still reloaded the level locally instead of using the native `0x1c` rebuild bridge.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy_resurrect` (`0x441fd0`) copies `app + 0x1b8` into `app + 0x1bc`, then writes `app + 0x1b8 = 0x1c` on the respawn branch.
  - The same respawn branch decrements visible lives only for gameplay mode `0` before the bridge write, matching the earlier March 15 debugger capture.
  - `update_frontend_state_machine` treats state `0x1c` as `destroy_subgame -> clear replay_active -> initialize_subgame -> jump to saved owner`.
- Likely:
  - The saved return slot at `app + 0x1bc` is a generic outer-owner state, not only a launch-surface frontend menu owner, because respawn writes the current active owner into it.
- Unknown:
  - The remaining final-loss writes that choose between `0x1a`, `0x1b`, and the special `+0x1bc = 2` override still need tighter reconstruction.

### Zig changes
- `zig/src/main.zig`
- Replaced the bespoke respawn reload path with an explicit outer-bridge request using opcode `28` plus a respawn-only active-run rebuild target.
- Captured the live runner state before teardown, rebuilt through the shared bridge lane, then restored the native-surviving respawn lanes onto the rebuilt runner.
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Updated the bridge notes so they now record the confirmed `app + 0x1b8/+0x1bc` respawn write pattern and no longer describe respawn as only an app-local reload helper.

### Verification
- `zig fmt zig/src/main.zig`
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- This confirms the new bridge target compiles, the focused respawn bridge test passes, and the wider runtime still builds after the ownership change.

### Git
- Branch: `master`
- Commit(s):
  - `75f7775 bridge: route respawn through outer opcode 28`
- Push: pushed to remote branch

### Remaining gaps
- Final-loss bridge ownership is still only partially literal, especially the `0x1a` vs `0x1b` split and the special saved-owner override to state `2`.
- The port still rebuilds respawn through the app-side loader instead of the literal Windows frontend state-machine driver.

### Next target
- Reconstruct the final-loss leg in `update_subgoldy_resurrect`, especially when it overwrites the saved return slot with `2` versus preserving the current owner before states `0x1a/0x1b`.

## 2026-03-23 19:07 - Iteration: align replay-backed final-loss bridge lane

### Target
- Replay-backed final-loss return ownership in `update_subgoldy_resurrect`

### Why this target
- The outer bridge is still the top architectural risk, and new Binary Ninja evidence was finally strong enough to replace one concrete wrong abstraction: replay-backed failed returns still used opcode `28` even though the native final-loss lane does not.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy_resurrect` (`0x441fd0`) final loss writes `game + 0x1270fc8 = 2`, calls `complete_subgame(game, 1)`, then branches on `game + 0xff25d1`.
  - When `selected_level_record_persistent != 0`, that branch copies `app + 0x1b8` into `app + 0x1bc` and sets `app + 0x1b8 = 0x1a`.
  - The replay-clearing rebuild opcode `0x1c` appears only on the respawn leg in this helper, not on the selected-level-record final-loss leg.
- Likely:
  - The selected-level-record final-loss branch is the native source for replay-backed failed result returns, so using opcode `26` is closer than the old respawn-style opcode `28`.
- Unknown:
  - The successful selected-level-record return lane that uses state `0x1b`.
  - The meaning of the postal-mode gate at `data_4df904 + 0x30d`.

### Zig changes
- `zig/src/main.zig`
- Replay-backed failed result returns now use destroy-return semantics instead of opcode `28`.
- Destroy-return handoff now also clears the selected replay context when returning replay-backed failures to the launch surface, so the app does not keep stale replay state after the native `0x1a`-shaped branch.
- Added focused tests for failed replay-backed bridge selection and teardown.
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Recorded the confirmed `selected_level_record_persistent -> 0x1a` final-loss branch and narrowed the remaining `0x1b` / `+0x30d` gap explicitly.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge change compiles, the new result-routing tests pass, and the runtime still builds after the teardown change.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `bridge: align replay-backed failed return opcode`
- Push: pending push after commit

### Remaining gaps
- Successful selected-level-record returns still are not mapped to the native `0x1b` lane.
- The postal-only `data_4df904 + 0x30d` gate remains unnamed and unported.
- The wider Windows continue/overlay owner around states `0x1a/0x1b/0x1c` is still only partially literal.

### Next target
- Recover the success-side selected-level-record bridge lane that chooses `0x1b`, and identify the postal gate at `data_4df904 + 0x30d` well enough to replace more of the generic post-run return mapping.

## 2026-03-23 19:15 - Iteration: stop replay completion from using opcode 28

### Target
- Replay-backed completion return ownership in `update_subgoldy` / outer bridge dispatch

### Why this target
- The outer bridge is still the top ownership risk, and Binary Ninja now pins one concrete wrong Zig path tightly enough to replace it: successful replay-backed result exits still used opcode `28` even though the native completion handoff does not.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy` (`0x43b120`) begins the final completion handoff after the `5.0s` fade gate, flushes `row_event_display` if needed, and then calls `complete_subgame`.
  - Binary Ninja shows the selected-level-record persistent completion branch copying the current outer owner into `app + 0x1bc` and setting `app + 0x1b8 = 0x1a`, not `0x1c`.
  - Binary Ninja and IDA both show `update_frontend_state_machine` state `0x1a` as `destroy_subgame -> jump to saved owner`, while `0x1c` is the separate rebuild-plus-clear-replay bridge.
- Likely:
  - The current Zig selected replay playback state is closer to the native selected-level-record persistent lane than to the non-persistent completion branch that uses `0x1b`, so replay-backed completion exits should use destroy-return semantics.
- Unknown:
  - The writer and exact semantics of `selected_level_record_persistent`.
  - The non-persistent completion branch that uses `0x1b`.
  - The special completion override that forces saved owner `2` when `level_mode == 7`.
  - The final-loss postal-mode gate at `data_4df904 + 0x30d`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Replay-backed successful result exits now use destroy-return bridge semantics instead of opcode `28`.
- Added focused tests for replay-backed completion exits to the time-trial route map and challenge high-score return paths.
- Reduced one explicit outer-bridge scaffold: replay completion no longer reuses the respawn-only clear-replay rebuild lane.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge mapper compiles, the new replay-backed completion regression coverage passes, and the wider runtime still builds after the bridge change.

### Git
- Branch: `master`
- Commit(s):
  - `55d40ae bridge: stop replay completion from using opcode 28`
- Push: pushed to remote branch

### Remaining gaps
- The non-persistent completion-side `0x1b` bridge lane is still not mapped onto Zig state.
- The `level_mode == 7` completion override and the final-loss postal gate at `data_4df904 + 0x30d` still need tighter owner recovery.
- Replay-backed abandon/overlay exits still need their own direct native corroboration instead of inference from the result paths.

### Next target
- Recover the writer and real meaning of `selected_level_record_persistent`, then port the remaining completion-side `0x1b` branch without guessing.

## 2026-03-23 19:25 - Iteration: split transient selected-record result returns

### Target
- Outer-bridge result routing for transient selected-level-record runs

### Why this target
- The outer bridge is still the highest-value ownership gap, and the current Zig code was still conflating "replay samples exist" with the native `selected_level_record_persistent` lane.

### Original behavior evidence
- Confirmed:
  - BN `update_subgoldy` shows the selected-level-record completion split saving the current owner, then using `state 0x1a` only when `game + 0xff25d1` is set and `state 0x1b` otherwise.
  - BN `update_subgoldy_resurrect` shows the same post-loss split after `complete_subgame(game, 1)`, with the extra postal-only `data_4df904 + 0x30d` gate on the non-persistent side.
  - BN `update_galaxy` and `update_challenge_setup_screen` both write `selected_level_record_active = 1` and the selected-record pointer, but do not show a matching `selected_level_record_persistent` write.
  - BN `initialize_subgame`, `update_subgame`, and `destroy_subgame`, with IDA corroboration from `build_subgame_level`, treat `selected_level_record_persistent` as a separate lifecycle lane that survives rebuild state `7` and is cleared on teardown.
- Likely:
  - The current frontend-selected replay launches in Zig correspond to the native transient selected-record lane until the persistent-writer path is recovered.
- Unknown:
  - The writer for `selected_level_record_persistent`.
  - The special completion override that forces saved owner `2` when `level_mode == 7`.
  - The exact postal final-loss meaning of `data_4df904 + 0x30d`.

### Zig changes
- `zig/src/main.zig`
- Added an explicit `selected_level_record_persistent` flag instead of reusing replay-payload presence as the bridge opcode proxy.
- Routed transient challenge/time-trial selected-record result exits through opcode `27` (`rebuild_return`) while reserving opcode `26` (`destroy_return`) for the separate persistent lane.
- Added focused tests for transient vs persistent selected-record post-run opcode selection.
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Recorded that current frontend launchers only arm the active selected-record lane and that the persistent-lane writer remains unresolved.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge helper compiles, the new transient/persistent result-routing coverage passes, and the wider runtime still builds after the bridge split.

### Git
- Branch: `master`
- Commit(s):
  - `5cb533c bridge: split transient selected-record result returns`
- Push: pushed to remote branch

### Remaining gaps
- The persistent selected-record writer is still not recovered.
- Postal non-persistent final loss still has the unresolved `data_4df904 + 0x30d` gate.
- Replay-backed abandon/overlay exits still need their own direct native corroboration instead of inheriting result-path reasoning.

### Next target
- Recover the actual writer and semantics of `selected_level_record_persistent`, then finish the remaining postal/override bridge branches without guessing.

## 2026-03-23 19:33 - Iteration: restore postal selected replay completion opcode

### Target
- Outer-bridge opcode parity for postal selected-record completion returns

### Why this target
- The outer bridge is still the top ownership risk, and the current Zig bridge was still flattening one confirmed native split: postal selected-replay completions were using destroy-return semantics even though `update_subgoldy` already shows the non-persistent completion lane rebuilding through `0x1b`.

### Original behavior evidence
- Confirmed:
  - BN disassembly of `update_subgoldy` (`0x43b120`) writes `app + 0x1b8 = 0x1b` on the non-persistent selected-record completion branch after saving the current outer owner, with only the separate tutorial `level_mode == 7` override forcing `0x1a`.
  - BN disassembly of `update_subgoldy_resurrect` (`0x441fd0`) keeps postal final loss separate: non-persistent postal loss only uses `0x1b` when app byte `+0x30d` is non-zero, otherwise it forces `app + 0x1b8 = 0x1a` and `app + 0x1bc = 2`.
  - IDA exports for `add_arcade_high_score`, `add_survival_high_score`, `destroy_high_score_screen`, and `update_completion_screen` show app byte `+0x30d` is a high-score-entry / high-score-screen continuation flag, not a generic gameplay mode byte.
- Likely:
  - Postal selected-record completion should already be treated like the other confirmed non-persistent selected-record completion paths, while postal selected-record final loss still depends on the unresolved live meaning of the `+0x30d` flag during gameplay.
- Unknown:
  - The writer for `selected_level_record_persistent`.
  - The full end-to-end owner semantics of app byte `+0x30d` during postal gameplay final loss.
  - Whether any additional launch path besides the currently mapped score-entry flow can arm `+0x30d`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Split postal selected-record completion from postal selected-record failure at the bridge opcode chooser, so confirmed postal selected-replay completions now use rebuild-return semantics while postal failures stay conservative.
- Added focused regression coverage for transient postal selected-replay completion vs failure opcode selection.
- Reduced one outer-bridge over-flattening: the port no longer routes confirmed postal selected-replay completions through destroy-return.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge opcode split compiles, the new postal replay regression coverage passes, and the wider runtime still builds after the bridge change.

### Git
- Branch: `master`
- Commit(s):
  - `2c0bedc` `bridge: restore postal selected replay completion opcode`
- Push: pushed to remote branch

### Remaining gaps
- Postal selected-record final loss still depends on the unresolved runtime meaning of app byte `+0x30d`.
- The writer and exact semantics of `selected_level_record_persistent` are still unresolved.
- The tutorial `level_mode == 7` completion override is documented, but the wider preserved-owner writer is still missing.

### Next target
- Recover the runtime owner and writer chain for app byte `+0x30d`, then port the remaining postal selected-record final-loss bridge split without guessing.

## 2026-03-23 19:40 - Iteration: confirm tutorial completion bridge override

### Target
- Outer-bridge tutorial completion override at native `level_mode == 7`

### Why this target
- The outer bridge is still the top project risk, and the checklist still treated the native `level_mode == 7 -> 0x1a / saved owner 2` completion branch as unresolved even though current BN and IDA evidence is now strong enough to show it is just the tutorial-completion lane the port already uses.

### Original behavior evidence
- Confirmed:
  - BN decompile of `update_subgoldy` (`0x43b120`) forces `app + 0x1b8 = 0x1a` and `app + 0x1bc = 2` on the special completion branch when `game->level_mode == 7`.
  - BN plus IDA decompile of `initialize_subgame` (`0x4374b0`) and `update_subgame` (`0x438b90`) both treat `level_mode == 7` as tutorial mode: tutorial init path, tutorial update, hidden HUD widgets, and `build_subgame_level(..., 0)` on rebuild state `7`.
  - The Zig bridge already routes tutorial completion through `destroy_return` to `New Game -> Tutorial`, which is the same native `26 -> 2` owner lane.
- Likely:
  - The stale checklist item existed because the branch was first recovered before `level_mode == 7` itself had been pinned to tutorial mode.
- Unknown:
  - The writer for `selected_level_record_persistent`.
  - The exact postal final-loss use of app byte `+0x30d`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Added a focused regression test that pins tutorial completion to `destroy_return` back into the `New Game -> Tutorial` owner.
- Removed the stale bridge gap from the runtime/status/checklist docs and replaced it with the confirmed tutorial-mode reading of native `level_mode == 7`.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- This confirms the new bridge assertion compiles and the current port still passes the full Zig test suite after the docs/test cleanup.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `bridge: confirm tutorial completion return lane`
- Push: pending push after commit

### Remaining gaps
- The writer and exact semantics of `selected_level_record_persistent` are still unresolved.
- The exact postal final-loss use of app byte `+0x30d` is still unresolved.

### Next target
- Recover the owner and writer chain behind app byte `+0x30d`, then port the remaining postal final-loss bridge split without guessing.
