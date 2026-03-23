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

## 2026-03-23 19:53 - Iteration: restore garbage lateral velocity lane

### Target
- Track-mode garbage collision motion ownership in `handle_subgoldy_collisions` / `update_subgoldy`

### Why this target
- Gameplay runtime ownership is still one of the biggest parity gaps, and Binary Ninja plus IDA now pin one narrow garbage-hit slice strongly enough to replace a wrong scaffold: the port still jumped `lane_center` directly and even moved while invincible instead of using the native `velocity.x` lane.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile of `handle_subgoldy_collisions` (`0x444cf0`) computes the garbage contact vector as hazard position minus player position, then only when `movement_flags & 0x80` is clear writes `player->velocity.x -= contact.x * player->velocity.z * 0.18` and `player->velocity.z -= contact.z * player->velocity.z * 0.10`.
  - Binary Ninja and the checked-in IDA export both show `update_subgoldy` (`0x43b120`) adding `velocity.x/y/z` into player position on the grounded track path, then damping `velocity.x` by `1 - track_center_x * 0.1`.
  - The same runtime still clamps gameplay world `x` to `[-4.0, 4.0]`, which matches the port’s existing track-width world-x bounds.
- Likely:
  - Attachment-follow consumes the same velocity block through `update_track_attachment_follow_state(..., this + 1040)`, but the exact attachment-side use of garbage-hit `velocity.x` is still not isolated tightly enough to replace the current fallback there.
- Unknown:
  - The broader grounded forward `velocity.z` controller once garbage hits or native negative rings hand control back.
  - The exact attachment-follow consumer semantics for garbage-seeded `velocity.x`.

### Zig changes
- `zig/src/gameplay.zig`
- Replaced the instant track-mode garbage `lane_center` shove with a decaying per-tick `native_velocity_x_per_tick` lane shaped after native `player->velocity.x`.
- Corrected the garbage contact-vector sign to use hazard-to-player direction, and applied the native invincible guard so garbage hits no longer change motion while invincible.
- Kept the attachment-follow fallback explicit, but corrected its shove sign as well instead of leaving the old inverted direction in place.
- Added focused regression coverage for delayed lateral shove, the per-tick `0.6` decay, the corrected forward-sign formula, and the invincible motion guard.
- `docs/re/runtime-structures.md`
- `docs/rewrite/binary-comparison-findings.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- Narrowed the docs so they now describe garbage collisions as a native-shaped lateral `velocity.x` owner in track mode while leaving the forward `velocity.z` recovery explicitly unresolved.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- This confirms the new garbage-motion tests compile and pass, the existing gameplay suite stays green, and the live runtime still builds after the ownership change.

### Git
- Branch: `master`
- Commit(s):
  - `ba4c0d5` `gameplay: restore garbage lateral velocity x lane`
- Push: pushed to remote branch

### Remaining gaps
- Garbage forward recovery still returns through `speed_rows_per_second` instead of the full native `velocity.z` owner.
- Attachment-follow still does not consume the recovered garbage-hit velocity block literally.

### Next target
- Recover the grounded forward `velocity.z` controller in `update_subgoldy` strongly enough to stop handing garbage hits and native negative rings back to the scaffolded `speed_rows_per_second` lane.

## 2026-03-23 20:03 - Iteration: route postal replay loss to New Game

### Target
- Outer-bridge target for transient postal selected-record final loss

### Why this target
- The outer bridge is still the highest-value ownership gap, and BN plus IDA now pin one concrete replay-sensitive asymmetry strongly enough to land end-to-end: postal replay failure was still returning to the postal high-score browser instead of taking the native `0x1a -> owner 2` New Game lane.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile of `update_subgoldy_resurrect` (`0x441fd0`) shows transient selected-record final loss taking `state 0x1b` only for non-postal modes or when app byte `+0x30d` is non-zero; otherwise postal final loss forces `state 0x1a` and overwrites the saved owner with `2`.
  - Binary Ninja decompile of `complete_subgame` (`0x438700`) shows `add_arcade_high_score` / `add_survival_high_score` only run when `selected_level_record_active == 0`.
  - The checked-in IDA exports for `add_arcade_high_score`, `add_survival_high_score`, and `destroy_high_score_screen` show app byte `+0x30d` is the high-score-screen continuation flag.
  - Because transient selected-record runs keep `selected_level_record_active == 1`, postal replay-backed final loss cannot seed app byte `+0x30d`, so that branch keeps the native `0x1a -> owner 2` New Game return.
- Likely:
  - Owner `2` remains the already-ported New Game return lane used by tutorial completion and ordinary postal final loss.
- Unknown:
  - The writer for `selected_level_record_persistent`.
  - The exact non-selected-record postal final-loss use of app byte `+0x30d`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Added a selected-record return-target override so transient postal replay failures now route to `New Game -> Postal` instead of the postal high-score browser.
- Updated the bridge regression test to pin the native per-source failure split.
- Narrowed the outer-bridge docs so they now treat the remaining `+0x30d` uncertainty as a non-selected-record postal gap rather than a replay-backed one.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge mapper compiles, the updated replay-failure regression passes, and the runtime still builds after the outer-bridge change.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `bridge: route postal replay loss to New Game`
- Push: pending push after commit

### Remaining gaps
- The writer and exact semantics of `selected_level_record_persistent` are still unresolved.
- The exact non-selected-record postal final-loss use of app byte `+0x30d` is still unresolved.

### Next target
- Recover the writer for `selected_level_record_persistent`, or tighten the remaining non-selected-record postal `+0x30d` bridge split if that path becomes easier to isolate first.

## 2026-03-23 20:14 - Iteration: document app-side replay launch scratch

### Target
- Outer-bridge replay-launch scratch ownership behind saved-replay starts

### Why this target
- The outer bridge is still the top project risk, and the current docs still treated the persistent replay lane mostly as an unresolved `game + 0xff25d1` mystery even though BN plus the checked-in IDA exports now pin a narrower upstream app-side replay-launch lane strongly enough to record without guessing.

### Original behavior evidence
- Confirmed:
  - `update_high_score_screen` replay-row clicks seed app replay-launch scratch before jumping to frontend state `10`: a selected record pointer at `app + 0x1066bec`, replay-launch bytes at `+0x1066be8/+0x1066be9`, a replay return state at `+0x1066bf0 = 0x12`, and the mode/owner bank at `app + 119190`.
  - The New Game menu's random replay branch seeds the same app replay-launch bytes plus the selected record pointer and mode/owner bank, but uses replay return state `2` instead of `0x12`.
  - `initialize_click_start`, `update_pause_menu`, and `update_completion_screen` all read those same app replay-launch fields later, so they are live runtime inputs rather than dead scratch.
  - `update_frontend_state_machine` state `0x1c` clears app dword `+0x12e55e0` on the clear-replay rebuild lane.
- Likely:
  - The app replay-launch scratch is the upstream source that eventually feeds the subgame-local persistent replay lane used by `update_subgoldy` / `update_subgoldy_resurrect`.
- Unknown:
  - The exact copy or constructor path that turns the app replay-launch scratch into `game + 0xff25d1`.
  - Whether the same app lane also writes the preserved-owner bridge slot at `[controller + 0x98]` or only runs in parallel with it.

### Zig changes
- No Zig runtime code changed.
- Updated `docs/re/runtime-structures.md`, `docs/re/windows-debugging-wants.md`, `docs/rewrite/port-status.md`, `docs/rewrite/subsystem-status.md`, and `docs/rewrite/remaining-work-checklist.md`.
- Reduced one doc-side scaffold: the repo now distinguishes the transient game-side selected-record lane from the separate app-side replay-launch scratch used by high-score replay rows and the menu replay path.

### Verification
- Reviewed the relevant BN decompiles for `update_frontend_state_machine`, `update_high_score_screen`, `update_pause_menu`, `initialize_click_start`, `update_galaxy`, `update_challenge_setup_screen`, `initialize_subgame`, `build_subgame_level`, `update_subgame`, and `destroy_subgame`.
- Cross-checked the checked-in IDA exports for the same functions plus `initialize_completion_screen`, `update_completion_screen`, `update_new_game_menu`, `launch_frontend_level_mode`, and `exit_high_score_screen`.
- Ran `git diff --check`.
- No build or test run was needed because this chunk only changes RE/docs, not Zig behavior.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `re: document app-side replay launch scratch`
- Push: pending push after commit

### Remaining gaps
- The exact copy site from app replay-launch scratch into `game + 0xff25d1` is still unresolved.
- The preserved-owner writer behind `[controller + 0x98]` is still unresolved.
- The exact non-selected-record postal final-loss use of app byte `+0x30d` is still unresolved.

### Next target
- Catch the first runtime write that turns the app replay-launch scratch (`+0x1066bec/+0x1066be8/+0x1066be9/+0x1066bf0`) into the subgame-local persistent replay lane at `game + 0xff25d1`.

## 2026-03-23 20:27 - Iteration: stage pause-abandon score entry

### Target
- Pause-menu abandon score-entry continuation in the outer bridge / post-run frontend flow

### Why this target
- The outer bridge is still the top project risk, and the Zig pause-menu `End Game` path still dropped ordinary postal/challenge partial scores even though BN plus IDA now pin the native exit-prompt side effect tightly enough to improve one concrete lane without guessing.

### Original behavior evidence
- Confirmed:
  - `update_pause_menu` routes ordinary gameplay abandon through exit-prompt owner `2`, replay-backed abandon through owner `3`, and tutorial abandon through owner `7`.
  - `update_completion_screen` case `2` calls `complete_subgame(game, 1)` before returning from the pause-menu exit prompt, then branches on app byte `+0x30d` to decide whether the shared high-score entry screen stays active.
  - `add_arcade_high_score` and `add_survival_high_score` both set app state `0x14` plus app byte `+0x30d = 1`, which is the shared high-score-entry continuation flag cleared later by `destroy_high_score_screen`.
  - `update_completion_screen` case `3` skips `complete_subgame` and returns replay-backed abandon through the app replay-return state at `+0x1066bf0`, so the score-entry side effect belongs to the ordinary non-replay lane, not the replay lane.
- Likely:
  - The ordinary pause-menu abandon high-score continuation should use the same shared inline name-entry screen as other postal/challenge score-entry paths, even though the exact post-entry owner after `exit_high_score_screen` is still only partially traced in Zig.
- Unknown:
  - The exact post-entry return owner for ordinary postal abandon after the high-score screen exits.
  - The remaining non-selected-record postal uses of app byte `+0x30d` outside this pause-menu lane.

### Zig changes
- `zig/src/main.zig`
- Added a direct standalone high-score-entry staging helper for pause-menu abandon, so non-replay postal/challenge abandons can enter the shared post-level name-entry screen when the partial score places.
- Added a separate return-request lane for standalone post-level high-score entry so submit/cancel can return through the current preserved-owner bridge path without faking a completion-screen result.
- Kept replay-backed abandon on the existing replay-return path and left the exact post-entry owner for ordinary abandon explicitly documented as still approximate.
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- Recorded that ordinary pause-menu abandon now stages the native high-score-entry side effect and narrowed the remaining owner gap to the post-entry return lane.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- The new standalone abandon score-entry tests pass, the existing result-flow tests still pass, and the wider runtime still builds after the pause-menu abandon change.

### Git
- Branch: `master`
- Commit(s):
  - `461969f bridge: stage pause-abandon score entry`
- Push: pushed to remote branch

### Remaining gaps
- The exact post-entry return owner for ordinary pause-menu abandon still rides the Zig preserved-owner abstraction.
- Replay-persistent launch ownership (`game + 0xff25d1`) is still unresolved.
- The remaining non-selected-record postal `+0x30d` branches still need tighter tracing.

### Next target
- Trace the ordinary pause-menu abandon post-entry owner through `exit_high_score_screen` / `update_completion_screen` strongly enough to replace the preserved-owner fallback on that lane.

## 2026-03-23 20:34 - Iteration: narrow persistent replay bridge source

### Target
- Static provenance of `game + 0xff25d1` (`selected_level_record_persistent`) in the replay-sensitive outer bridge

### Why this target
- The outer bridge is still the top ownership risk, and the saved-replay lane was still framed too broadly as "find the writer" even though BN, IDA, and a whole-image disassembly sweep were already strong enough to narrow the real gap further.

### Original behavior evidence
- Confirmed:
  - Whole-image static disassembly shows no direct nonzero store to `game + 0xff25d1`; the only direct store to that byte is the teardown clear in `destroy_subgame` at `0x438b13`.
  - `initialize_subgame`, `build_subgame_level`, `update_subgame`, `update_subgoldy`, `update_subgoldy_resurrect`, and `initialize_click_start` only read or compare `game + 0xff25d1`.
  - `build_subgame_level` gates its replay-backed mode, level, replay-speed, and scalar copies on `selected_level_record_active || selected_level_record_persistent`, so the missing step is upstream of that build/init sequence.
  - App dword `+0x12e55e0` is not a clean replay-only source candidate: `update_new_game_menu`, `exit_high_score_screen`, and `update_pause_menu` all write `2` there, while `update_frontend_state_machine` state `0x1c` clears it.
- Likely:
  - The persistent replay lane reaches subgame through a helper, constructor-side copy, or object-lifetime path that static offset sweeps do not expose as a direct `+0xff25d1 = 1` store.
- Unknown:
  - The exact function or lifetime transition that first makes the app replay scratch observable as `game + 0xff25d1`.

### Zig changes
- No Zig runtime code changed.
- Updated `docs/re/runtime-structures.md`, `docs/re/windows-debugging-wants.md`, `docs/rewrite/subsystem-status.md`, and `docs/rewrite/remaining-work-checklist.md`.
- Reduced one RE-side blind spot: the remaining replay-persistent bridge gap is now documented as constructor/copy provenance, not another shallow direct-writer search.

### Verification
- Ran `git diff --check`.
- Reviewed `bn decompile` / `bn disasm` for `initialize_subgame`, `build_subgame_level`, `update_subgame`, `destroy_subgame`, `update_pause_menu`, `update_high_score_screen`, and `update_new_game_menu`.
- Cross-checked the same question with the checked-in IDA exports plus a whole-image `objdump -Mintel -d ... | rg "ff25d1|12e55e0"` sweep.
- This gives high confidence in the negative result: the remaining gap is provenance, not a missed obvious setter.

### Git
- Branch: `master`
- Commit(s):
  - `cd9b7f2 re: narrow persistent replay bridge source`
- Push: pushed to remote branch after the accompanying worklog update commit

### Remaining gaps
- The constructor/copy path that makes app replay scratch visible as `game + 0xff25d1`.
- The exact non-selected-record postal final-loss use of app byte `+0x30d`.

### Next target
- Trace the first live transition of `game + 0xff25d1` in Windows around `initialize_subgame`, `build_subgame_level`, and `initialize_click_start`, while watching the app replay scratch fields and the outer bridge slots together.

## 2026-03-23 20:44 - Iteration: arm persistent replay launch alias

### Target
- Persistent vs transient selected-record launch ownership in the outer bridge

### Why this target
- The outer bridge is still the top risk, and the repo now had enough BN/IDA evidence to replace one concrete wrong abstraction: postal/challenge replay launches from the high-score screen were still treated as transient even though the native launch lane already exposes the persistent bit directly.

### Original behavior evidence
- Confirmed:
  - `update_frontend_state_machine` initializes subgame at `data_4df904 + 0x74618`.
  - `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch write `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0` before frontend state `10`.
  - Those app offsets alias `game + 0xff25d0/+0xff25d1/+0xff25d4/+0xff25d8` exactly, so the replay-row launch path writes the persistent selected-record lane directly instead of through a later copy helper.
  - `update_galaxy` and `update_challenge_setup_screen` still only arm the transient `selected_level_record_active` lane.
- Likely:
  - Postal/challenge high-score replay launches are the native persistent selected-record family, while route-map best-trial launches stay transient.
- Unknown:
  - The exact replay-backed abandon/overlay routing split now that the persistent launch provenance is resolved.
  - The exact non-selected-record postal final-loss use of app byte `+0x30d`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- High-score replay launches now arm `selected_level_record_persistent` in Zig, while route-map best-trial launches stay transient.
- Result-bridge tests now cover the persistent postal replay lane as well as the source-to-persistence split.
- Removed one bridge-side scaffold: the port no longer hardwires every selected replay launch to the transient lane.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the replay-launch split compiles, the bridge tests pass, and the wider runtime still builds after the ownership correction.

### Git
- Branch: `master`
- Commit(s):
  - `466dade` `bridge: arm persistent selected replay launches`
- Push: pushed to remote branch

### Remaining gaps
- Replay-backed abandon and overlay exits still need their own direct native corroboration now that persistent launch provenance is resolved.
- The exact non-selected-record postal final-loss `+0x30d` branch is still unresolved.

### Next target
- Trace replay-backed pause-abandon and overlay exits strongly enough to split the persistent high-score replay lane from the transient route-map best-trial lane without inference.

## 2026-03-23 20:50 - Iteration: align persistent replay pause-abandon bridge

### Target
- Persistent selected-record pause `End Game` routing in `update_pause_menu` / `update_completion_screen`

### Why this target
- The outer bridge is still the top ownership risk, and BN plus IDA were finally strong enough to replace one concrete wrong abstraction: high-score replay pause abandon still reused the respawn-only clear-replay rebuild lane.

### Original behavior evidence
- Confirmed:
  - `update_pause_menu` (`0x4407a0`) copies the current outer owner into the completion-screen saved-owner slot, then picks completion state `3` when `app + 0x1066be9` (`selected_level_record_persistent`) is `1`.
  - The same branch picks completion state `7` for tutorial mode and `2` otherwise; it does not branch on replay sample presence.
  - `update_completion_screen` (`0x4067e0`) state `3` destroys subgame and restores the owner saved at `app + 0x1066bf0`; it does not use frontend state `0x1c`.
  - `update_frontend_state_machine` still reserves state `0x1c` for `destroy_subgame -> clear replay_active -> initialize_subgame -> jump to saved owner`, so the persistent pause-abandon lane is a `0x1a`-shaped destroy-return, not opcode `28`.
- Likely:
  - High-score replay launches use the same saved-owner destroy-return path for pause abandon and result exits because both lanes consume the persistent selected-record byte and the shared `+0x1066bf0` return slot.
- Unknown:
  - The transient route-map best-trial pause-abandon path when replay playback is active but `selected_level_record_persistent == 0`.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Switched persistent selected-record abandon from `rebuild_clear_replay_return` to `destroy_return` keyed from `selected_level_record_persistent` instead of replay-sample presence.
- Added focused coverage for the confirmed persistent destroy-return lane and left the transient replay-abandon fallback explicitly documented as unresolved.
- Reduced one bridge-side scaffold: high-score replay pause abandon no longer reuses the respawn-only opcode-`28` lane.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the bridge change compiles, the abandon-routing tests pass, and the wider runtime still builds after the bridge correction.

### Git
- Branch: `master`
- Commit(s):
  - `2eec4a3` `bridge: align persistent replay pause-abandon bridge`
- Push: pushed to remote branch

### Remaining gaps
- The transient replay-backed pause-abandon and overlay lane for route-map best-trial launches is still unresolved.
- The exact non-selected-record postal final-loss use of app byte `+0x30d` is still unresolved.

### Next target
- Trace the transient selected-record pause-abandon lane strongly enough to decide whether route-map best-trial replay uses the state-`2` completion branch verbatim or another bridge helper beyond the current fallback.

## 2026-03-23 20:57 - Iteration: align transient replay pause-abandon opcode

### Target
- Route-map best-trial replay pause `End Game` routing in `update_pause_menu` / `update_completion_screen`

### Why this target
- The outer bridge is still the top ownership risk, and the current Zig bridge still used the respawn-only clear-replay rebuild opcode for transient selected replay abandon even though BN plus IDA were finally strong enough to pin the native pause-abandon lane directly.

### Original behavior evidence
- Confirmed:
  - BN `update_pause_menu` (`0x4407a0`) picks completion state `2` whenever `app + 0x1066be9` (`selected_level_record_persistent`) is clear and the run is not tutorial mode.
  - BN plus IDA `update_completion_screen` (`0x4067e0`) state `2` calls `complete_subgame(game, 1)`, then destroys completion/pause/subgame and, for `level_mode == 4` or `1`, reinitializes subgame directly instead of using frontend state `0x1c`.
  - BN `complete_subgame` (`0x438700`) only seeds the app `+0x30d` high-score continuation flag when `selected_level_record_active == 0`, so transient selected-record replay abandons skip that side path.
  - BN `initialize_subgame` (`0x4374b0`) uses the preserved nonzero continuation selector plus `level_mode == 4` to rebuild the galaxy owner through `initialize_galaxy` / `reset_subgame`.
- Likely:
  - Route-map best-trial replay pause abandon is the native transient rebuild lane corresponding to opcode `27`, not the respawn-only clear-replay lane `28`.
- Unknown:
  - The transient replay-backed overlay lane for route-map best-trial launches.
  - The exact non-selected-record postal final-loss use of app byte `+0x30d`.

### Zig changes
- `zig/src/main.zig`
- Switched transient selected replay pause abandon from `rebuild_clear_replay_return` to `rebuild_return`.
- Replaced the old fallback comment with the confirmed BN/IDA reconstruction and updated the focused regression test to pin opcode `27`.
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Recorded the confirmed state-`2` transient replay abandon path and narrowed the remaining bridge gap down to the overlay lane rather than abandon plus overlay together.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the bridge model compiles, the updated abandon-routing test passes, the wider runtime still builds, and the mixed Zig/docs patch is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `a0c988c` `bridge: align transient replay pause-abandon opcode`
- Push: pushed to remote branch

### Remaining gaps
- The transient replay-backed overlay lane for route-map best-trial launches is still unresolved.
- The exact non-selected-record postal final-loss use of app byte `+0x30d` is still unresolved.

### Next target
- Trace the transient route-map replay overlay exit strongly enough to decide whether it shares the same non-clear rebuild lane as pause abandon or still uses a different bridge/helper path.

## 2026-03-23 21:06 - Iteration: restore non-postal failed return owners

### Target
- Ordinary non-selected challenge/time-trial failed-result return ownership

### Why this target
- The outer bridge is still the top ownership risk, and Binary Ninja evidence was finally strong enough to replace one concrete wrong fallback: non-postal failures still returned to the main menu in Zig even though the native rebuild lane points back into mode-owned front-end controllers.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy_resurrect` (`0x441fd0`) copies the current owner into `app + 0x1bc` and sets `app + 0x1b8 = 0x1b` for non-postal, non-persistent final loss.
  - `update_frontend_state_machine` (`0x4107d0`) state `0x1b` destroys subgame, initializes subgame, then jumps to the saved owner.
  - `initialize_subgame` (`0x4374b0`) consumes the nonzero continuation selector by mode: `level_mode == 1` calls `initialize_challenge_setup_screen`, while `level_mode == 4` calls `initialize_galaxy`.
  - `exit_high_score_screen` (`0x417b50`) also restores owner `2` for postal entries and owner `0x0a` for challenge entries, which matches the challenge-side setup rebuild rather than a main-menu exit.
- Likely:
  - The current Zig `New Game -> Challenge Mode` owner is the closest existing abstraction for the native challenge-setup screen until that controller is ported literally.
- Unknown:
  - The exact non-selected-record postal final-loss split on app byte `+0x30d`.
  - The transient replay-backed overlay lane for route-map best-trial launches.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `worklog.md`
- Challenge failure no longer falls back to the main menu; it now returns through the existing `challenge_mode` menu owner.
- Time-trial failure no longer falls back to the main menu; it now returns to the replay Star Map owner.
- Reduced one bridge-side fallback: non-postal failed-result owners now follow the recovered mode-owned return surfaces instead of one generic menu exit.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the bridge mapping compiles, the updated return-target tests pass, the runtime still builds, and the mixed Zig/docs patch is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `868318a` `bridge: restore non-postal failed return owners`
- Push: pushed to remote branch

### Remaining gaps
- The transient replay-backed overlay lane for route-map best-trial launches is still unresolved.
- The exact non-selected-record postal final-loss use of app byte `+0x30d` is still unresolved.
- The port still collapses the native challenge-setup owner onto the `New Game -> Challenge Mode` menu item.

### Next target
- Trace the transient route-map replay overlay exit strongly enough to decide whether it shares the same non-clear rebuild lane as pause abandon or still uses a different bridge/helper path.

## 2026-03-23 21:14 - Iteration: match post-entry abandon return owner

### Target
- Ordinary pause-menu abandon post-level high-score return ownership

### Why this target
- The outer bridge is still the top ownership risk, and the Zig port still sent standalone postal/challenge abandon score entry back through the preserved gameplay launch owner even though the native high-score-entry lane was finally tight enough to replace that shortcut.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile of `add_arcade_high_score` (`0x4176a0`) and `add_survival_high_score` (`0x417780`) shows both helpers arming active state `0x14` and setting app byte `+0x30d = 1`.
  - Binary Ninja decompile of `update_high_score_screen` (`0x417260`) shows the post-entry commit path ending in `exit_high_score_screen()`, not in a preserved gameplay-owner restore helper.
  - Binary Ninja decompile plus the checked-in IDA export for `exit_high_score_screen` (`0x417b50`) show that post-entry exit returns by the surviving run mode lane: postal (`level_mode == 0`) to frontend state `2`, challenge (`level_mode == 1`) to frontend state `10`.
- Likely:
  - The current Zig `Challenge Mode` menu owner remains the closest stand-in for native frontend state `10` until the literal challenge-setup controller is ported.
- Unknown:
  - The exact non-selected-record postal final-loss use of `data_4df904 + 0x30d`.
  - The transient replay-backed overlay route for route-map best-trial launches.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Standalone post-level high-score entry no longer reuses the generic abandon return request; it now derives its return owner from the same failure/result bridge lane the native post-entry high-score exit uses.
- Added regression coverage for postal and challenge abandon score entry so postal returns to the New Game owner and challenge stays on the challenge-owner stand-in after name entry.
- Reduced one explicit outer-bridge shortcut: ordinary abandon score entry no longer rides `preserved_frontend_owner`.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the updated bridge mapper compiles, the new abandon score-entry tests pass, and the runtime still builds after the owner change.

### Git
- Branch: `master`
- Commit(s):
  - `b16cd62` `bridge: match post-entry abandon return owner`
- Push: pushed to remote branch

### Remaining gaps
- The exact non-selected-record postal final-loss use of `data_4df904 + 0x30d` is still unresolved.
- The transient replay-backed overlay route for route-map best-trial launches still lacks a direct native confirmation.
- Challenge post-entry return still uses the port's `Challenge Mode` menu stand-in rather than a literal challenge-setup controller.

### Next target
- Recover the remaining non-selected-record postal final-loss split on `data_4df904 + 0x30d`, so the last ordinary post-run postal bridge lane stops depending on the current heuristic.

## 2026-03-23 21:24 - Iteration: capture failed score-entry return owner

### Target
- Ordinary postal/challenge failed-result high-score entry ownership in `update_subgoldy_resurrect` / `complete_subgame`

### Why this target
- The outer bridge is still the top ownership risk, and BN plus IDA were finally strong enough to replace one remaining app-side shortcut: failed postal/challenge score entry still stayed attached to the live completion-screen result object in Zig even though the Win32 branch preserves owner `0x14` before the `0x1b` rebuild-return lane.

### Original behavior evidence
- Confirmed:
  - BN `add_arcade_high_score` (`0x4176a0`) and `add_survival_high_score` (`0x417780`) both arm active owner `0x14` and set app byte `+0x30d = 1`.
  - BN `update_subgoldy_resurrect` (`0x441fd0`) copies the current owner into `app + 0x1bc` before setting `app + 0x1b8 = 0x1b`; on ordinary qualifying postal/challenge failure, that preserved owner is therefore the already-armed `0x14` post-level high-score screen.
  - BN `complete_subgame` (`0x438700`) only seeds that `+0x30d` / high-score-owner side path when `selected_level_record_active == 0`.
  - IDA agrees on the same ordering in `update_subgoldy_resurrect`, including the postal `+0x30d` split and the preserved-owner write before state `27`.
- Likely:
  - The current Zig `Challenge Mode` menu owner remains the closest stand-in for the native challenge-setup owner that receives the post-entry return after state `10`.
- Unknown:
  - The transient replay-backed overlay route for route-map best-trial launches.
  - The literal Windows outer-controller rebuild still remains unported; the Zig bridge still maps onto existing front-end owners directly.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Failed postal/challenge score entry now captures its post-entry return request immediately once the high-score owner takes over, instead of keeping `pending_run_result` live through name entry.
- Added focused regression coverage for postal/challenge failed-result handoff objects so the recovered return owners stay pinned.
- Reduced one bridge-side shortcut: the `+0x30d` failure branch is now modeled as a saved-owner handoff into the shared post-level high-score owner rather than as a completion-screen-local continuation.

### Verification
- `zig fmt zig/src/main.zig`
- `git diff --check`
- `zig build test`
- `zig build`
- This confirms the bridge patch formats cleanly, passes the focused/new regression coverage plus the full test suite, and still builds the runtime.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `bridge: capture failed score-entry return owner`
- Push: pending push after commit

### Remaining gaps
- The transient replay-backed overlay route for route-map best-trial launches still lacks a direct native confirmation.
- The port still does not drive these bridge lanes through the literal Windows outer-controller rebuild state machine.
- Challenge-side returns still use the port's `Challenge Mode` owner stand-in instead of a literal challenge-setup controller.

### Next target
- Trace the transient replay-backed overlay route for route-map best-trial launches strongly enough to decide whether it shares the same non-clear rebuild lane as pause abandon or uses a different bridge/helper path.

## 2026-03-23 21:35 - Iteration: restart selected replay on native marker exit

### Target
- Selected-record replay flag-`0x8` tail routing in `update_subgoldy`

### Why this target
- The outer bridge is still the top ownership risk, and the last replay-side “overlay lane” was still running on a direct Zig UI shortcut even though BN plus IDA were finally strong enough to pin the native marker branch directly.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy` (`0x43b120`) checks the selected-record sample byte at `record + runtime_track_index * 6 + 0x74` while `selected_level_record_active != 0`, `runtime_track_index < sample_count`, and `movement_state != 2`.
  - That branch copies replay `x` from sample word `+0x70`, feeds `track_state_latch` from sample bit `0x4`, and when sample bit `0x8` is set writes `app + 0x1b8 = 0x1a`, `app + 0x1bc = 10`, sets app byte `+0x30c = 1`, then calls `begin_frontend_fade_in(app + 0x24)`.
  - `update_frontend_state_machine` state `10` is the subgame-init owner, so the marker loops back through `initialize_subgame` rather than returning to the launch surface.
- Likely:
  - The app byte at `+0x30c` is a generic front-end fade/transition latch reused by other launch helpers, not a replay-only ownership selector.
- Unknown:
  - The exact user-facing semantics of app byte `+0x30c`.
  - Whether any other replay sample bits besides `0x1/0x2/0x4/0x8` drive additional native gameplay or UI consumers.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Replaced the selected-replay marker shortcut that jumped straight back to route-map/high-score UI with a native-shaped destroy-return replay restart request.
- Added focused coverage that pins replay flag-`0x8` to `opcode 26` plus the current replay target, preserving the selected-record context instead of clearing it.
- Reduced one explicit bridge scaffold: the route-map replay “overlay exit” no longer depends on the old launch-surface shortcut.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the new replay-marker bridge compiles, the added bridge regression passes, the full runtime still builds, and the mixed Zig/docs patch is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `2dd1e3d` `bridge: restart selected replay on native marker exit`
- Push: pending push after worklog commit

### Remaining gaps
- The current port still maps challenge-side rebuild returns onto the `Challenge Mode` menu stand-in instead of the literal challenge-setup controller.
- The ordinary postal final-loss split on app byte `+0x30d` is still only partially recovered.
- The literal Windows outer-controller rebuild still remains abstracted behind the Zig bridge request lane.

### Next target
- Recover the ordinary non-selected postal final-loss `+0x30d` split strongly enough to replace the last remaining postal bridge heuristic.
