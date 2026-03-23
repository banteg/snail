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

## 2026-03-23 21:43 - Iteration: close postal final-loss bridge split

### Target
- Ordinary postal final-loss `+0x30d` bridge split in `update_subgoldy_resurrect` / `complete_subgame`

### Why this target
- The bridge checklist still treated this as the last open postal heuristic even though the native branch was now tight enough to confirm or reject directly from BN and IDA.

### Original behavior evidence
- Confirmed:
  - BN `update_subgoldy_resurrect` (`0x441fd0`) copies the current outer owner into `app + 0x1bc`, then on non-persistent final loss forces `state 0x1a -> owner 2` only when `level_mode == 0` and app byte `+0x30d == 0`; otherwise postal with `+0x30d != 0` and all non-postal modes use `state 0x1b`.
  - IDA shows the same ordering and branch shape, including the postal-mode test and the `0x1a -> owner 2` overwrite.
  - BN `complete_subgame` (`0x438700`) only reaches `add_arcade_high_score` / `add_survival_high_score` when `selected_level_record_active == 0`, and those helpers arm owner `0x14` plus app byte `+0x30d = 1`.
  - BN `destroy_high_score_screen` (`0x417220`) clears app byte `+0x30d`, and `exit_high_score_screen` (`0x417b50`) returns by surviving mode (`state 2` for postal, `state 10` for challenge).
- Likely:
  - App byte `+0x30d` is specifically the post-level high-score continuation latch, not a generic gameplay-mode flag.
- Unknown:
  - The literal challenge-setup owner is still missing in Zig even though the branch that returns to it is now confirmed.
  - The wider Windows outer-controller rebuild state machine still remains abstracted behind the Zig bridge request lane.

### Zig changes
- `zig/src/main.zig`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Replaced the stale source comment that still called the postal replay-loss split unresolved.
- Added a focused regression proving transient postal replay failures clear score-entry staging and still return through the native `0x1a -> owner 2` destroy-return lane.
- Removed the stale checklist claim that the ordinary postal final-loss `+0x30d` split was still only partially recovered.

### Verification
- `zig fmt zig/src/main.zig`
- `git diff --check`
- `zig build test`
- `zig build`
- This confirms the new regression, the source/docs tightening, and the wider runtime all still pass cleanly.

### Git
- Branch: `master`
- Commit(s):
  - `e4b24cb` `bridge: close postal final-loss split`
- Push: pushed to remote branch

### Remaining gaps
- Challenge-side rebuild returns still land on the Zig `Challenge Mode` stand-in instead of a literal `initialize_challenge_setup_screen` owner.
- The literal Windows outer-controller rebuild and saved-owner writer are still abstracted behind the current bridge request lane.

### Next target
- Port the native challenge-setup owner strongly enough that challenge rebuild returns stop using the `Challenge Mode` stand-in.

## 2026-03-23 22:05 - Iteration: restore challenge setup owner

### Target
- Literal challenge-setup owner and return lane for ordinary challenge rebuilds plus transient setup replay launches

### Why this target
- The outer bridge is still the top project risk, and BN plus IDA were already strong enough to replace the last challenge-side stand-in without guessing.

### Original behavior evidence
- Confirmed:
  - BN `initialize_challenge_setup_screen` (`0x415f50`) builds the mode-`1` owner with `Select Difficulty`, `Select Speed`, `Play`, optional `Watch Replay`, and `Back`.
  - BN plus IDA show the setup sliders seeding from `unk_4DF960` / `unk_4DF958` as raw `0..100` values converted to widget floats by `* 0.01`.
  - BN plus IDA `update_challenge_setup_screen` (`0x416370`) returns `3` on `Back`, returns `1` on `Play`, and on `Watch Replay` sets `selected_level_record_active = 1` plus the selected-record pointer without setting the persistent replay lane.
  - BN `initialize_subgame` (`0x4374b0`) and IDA `update_subgame` (`0x438b90`) rebuild `level_mode == 1` through `initialize_challenge_setup_screen` on the nonzero continuation selector.
- Likely:
  - The app-side saved-owner writer that feeds that rebuild lane still sits outside the current named Zig bridge surface.
- Unknown:
  - The exact writer for the preserved front-end owner / saved outer-controller slot outside the already-confirmed respawn and result branches.
  - Any remaining low-level challenge-setup widget/controller details beyond the now-recovered owner, return targets, and replay split.

### Zig changes
- `zig/src/frontend.zig`
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Added a literal `challenge_setup_menu` front-end phase, restored its recovered slider/button layout, and made `New Game -> Challenge Mode` enter that owner instead of launching challenge gameplay directly.
- Ordinary challenge result, abandon, and post-level high-score-entry returns now rebuild to the challenge-setup owner, and transient setup `Watch Replay` launches now return through the non-persistent setup lane instead of the high-score browser.
- Removed the remaining challenge-side stand-in from the rewrite docs/checklist and recorded the transient challenge-setup replay split explicitly.

### Verification
- `zig fmt zig/src/main.zig zig/src/frontend.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the recovered owner compiles, the updated bridge regressions pass, and the full runtime still builds cleanly.

### Git
- Branch: `master`
- Commit(s):
  - `cbce312` `bridge: restore challenge setup owner`
  - `3f8a96f` `docs: update worklog`
- Push: pushed to remote branch

### Remaining gaps
- The saved-owner writer behind the native `26/27/28` bridge jump is still unresolved.
- The outer bridge is still modeled as an explicit request dispatcher instead of the literal rebuilt controller object.

### Next target
- Recover the saved-owner writer / preserved-owner slot that feeds the native `26/27/28` bridge jump outside the already-confirmed respawn self-return path.

## 2026-03-23 22:24 - Iteration: split replay launch return owner

### Target
- Outer-bridge replay launch context for persistent saved-replay starts

### Why this target
- The outer bridge is still the top project risk, and the current Zig replay bridge was still deriving persistent replay return ownership from `SelectedLevelRecordSource` even though BN plus IDA already showed a separate saved return-state lane on the native high-score and menu replay launchers.

### Original behavior evidence
- Confirmed:
  - `update_high_score_screen` replay-row clicks seed `app + 0x1066bec`, `+0x1066be8 = 1`, `+0x1066be9 = 1`, `+0x1066bf0 = 0x12`, and `+119190` before jumping to frontend state `10`.
  - The New Game menu's random replay branch seeds the same replay-launch scratch, but uses `app + 0x1066bf0 = 2` instead of `0x12`.
  - `update_frontend_state_machine` initializes subgame at `data_4df904 + 0x74618`, so that app scratch aliases `game + 0xff25d0/+0xff25d1/+0xff25d4/+0xff25d8` directly.
  - `update_pause_menu` and `update_completion_screen` both consume `app + 0x1066be9` / `+0x1066bf0`; completion state `3` destroys subgame and restores the dword saved at `+0x1066bf0`.
  - The high-score and menu replay launchers therefore do not derive their later return owner from the selected replay source alone.
- Likely:
  - The Zig bridge should carry replay launch `source`, persistent lane, and saved return owner as separate fields instead of reconstructing them from the selected-record source enum.
- Unknown:
  - The saved-owner writer behind the native `26/27/28` bridge jump outside the replay-launch scratch path.
  - The full New Game random replay UI/path and any remaining `+119190` owner-bank semantics beyond the now-recovered launch writes.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `worklog.md`
- Replaced the source-derived replay bridge payload with an explicit `SelectedLevelRecordLaunch { source, persistent, return_target }`.
- Stored `selected_level_record_return_target` separately in `AppState`, and preserved that launch context across replay abandon, replay-tail restart, and replay-backed result rebuilds.
- Added regression coverage for persistent replay launches whose return owner differs from the replay source, and fixed older `undefined`-state tests to initialize the new launch-context reads explicitly.
- Reduced one bridge-side scaffold: persistent replay return ownership is no longer inferred from `SelectedLevelRecordSource` alone.

### Verification
- `zig fmt zig/src/main.zig`
- `git diff --check`
- `zig build test`
- `zig build`
- This confirms the launch-context split compiles, the replay bridge regressions pass, and the wider runtime still builds cleanly.

### Git
- Branch: `master`
- Commit(s):
  - `11b4e23` `bridge: split replay launch return owner from source`
- Push: pushed to remote branch

### Remaining gaps
- The saved-owner writer behind the native `26/27/28` bridge jump is still unresolved.
- The New Game random replay UI/path is still not exposed in Zig even though its persistent launch scratch shape is now modeled.

### Next target
- Trace `[controller + 0x98]` / `data_4df904 + 110` together with `+119190` and `+4299516` to recover the native saved-owner writer behind the outer bridge.

## 2026-03-23 22:36 - Iteration: document new game replay attract lane

### Target
- New Game menu random replay attract launch lane

### Why this target
- The outer bridge is still the top parity risk, and BN plus IDA already pinned a narrow replay-launch slice with remaining scaffolding in docs and tests but without enough evidence to justify a live Zig launcher implementation.

### Original behavior evidence
- Confirmed:
  - `update_new_game_menu` rotates a menu-local cursor through `0..4`, wraps `5 -> 0`, and only probes replay banks on cursor values `0`, `1`, and `3`.
  - Those probe lanes map to the postal, challenge, and completion / Time Trial banks, write `app + 0x74658 = 0/1/4`, and on success seed `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0` before jumping to frontend state `10`.
  - The menu replay branch uses the same persistent selected-record scratch lane as high-score replay rows, but seeds `app + 0x1066bf0 = 2` for the later return owner.
  - The launcher is gated by menu-local float fields at `data_4df904 + 0x4f2dc + 0x10/+0x14`, clears the accumulator back to `0.0` before the bank probe loop, and gives up after `1000` attempts.
  - On that give-up path, `update_new_game_menu` writes menu locals `+0x8 = 0` and `+0xc = 0x3991a2b4` (`0.00027777778f`) and returns without launching.
- Likely:
  - The current Zig bridge should preserve those recovered menu-owned return targets by replay bank even before the live attract timer / trigger is implemented.
- Unknown:
  - The writer that seeds the menu-local step at `data_4df904 + 0x4f2dc + 0x14`.
  - The rest of that New Game attract controller's lifetime outside the now-confirmed probe / launch branch.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `docs/re/windows-debugging-wants.md`
- Added regression coverage that pins persistent New Game replay return ownership for postal, challenge, and completion-backed replay banks.
- Documented the recovered menu replay attract bank rotation, `1000`-attempt probe cap, persistent replay scratch writes, and the remaining timer-step gap.
- Reduced one replay-side scaffold: the docs/checklist no longer treat the missing piece as a generic unexplained launcher when the bank split and return-state writes are already confirmed.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the added bridge regression compiles, the full Zig suite still passes, and the narrowed replay-attract docs landed without whitespace or patch-shape issues.

### Git
- Branch: `master`
- Commit(s):
  - `96ce4ee` `re: document new game replay attract lane`
- Push: pushed to remote branch

### Remaining gaps
- The saved-owner writer behind the native `26/27/28` bridge jump is still unresolved.
- The New Game replay attract timer / trigger producer at `data_4df904 + 0x4f2dc + 0x14` is still not recovered, so the live launcher remains intentionally unimplemented.

### Next target
- Trace the writer for the New Game attract timer-step field together with `[controller + 0x98]`, `data_4df904 + 110`, and the app replay-launch scratch to connect the menu trigger to the native outer-bridge owner handoff.

## 2026-03-23 22:44 - Iteration: narrow replay attract controller layout

### Target
- New Game replay-attract controller layout and startup replay-scratch ownership

### Why this target
- The outer bridge is still the top risk, but the missing `+0x14` timer-step writer was too narrow to guess live; BN plus IDA already pinned enough surrounding structure to land a durable docs chunk that sharpens the next Windows trace.

### Original behavior evidence
- Confirmed:
  - BN `update_new_game_menu` (`0x417eb0`) accumulates menu-local float `+0x14` into `+0x10`, enters the replay-bank probe once that accumulator exceeds `1.0`, and resets `+0x10` back to `0.0` before the bank-search loop.
  - BN plus IDA show the same menu object rotating cursor `+0x0` through `0..4`, probing replay banks only on values `0/1/3`, setting the persistent replay scratch at `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`, and resetting menu locals `+0x8 = 0` plus `+0xc = 0x3991a2b4` on both successful launch and the `1000`-attempt give-up path.
  - BN `initialize_click_start` (`0x442170`) hides the `Click to Start` prompt whenever `app + 0x1066be8 != 0`.
  - IDA `initialize_game_assets_and_world` (`0x40acf0`) clears app bytes `+17198056/+17198057` during startup, so the replay-launch bits do not persist across a fresh app init.
- Likely:
  - Menu byte `+0x4` is a replay-attract hide latch: input clears it only after unhiding all six New Game widgets, and a successful replay launch sets it to `1` immediately before `destroy_main_menu`.
- Unknown:
  - The writer that seeds the menu-local float step at `data_4df904 + 0x4f2dc + 0x14`.
  - The exact role of the secondary timer lane at `data_4df904 + 0x4f2dc + 0x8/+0xc`.

### Zig changes
- `docs/re/runtime-structures.md`
- `docs/re/windows-debugging-wants.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `analysis/symbols/gameplay-functions.json`
- Documented the New Game replay-attract controller's firmer partial field layout, the startup clear of the persistent replay-launch bits, and the click-start suppressor that already consumes that scratch.
- Tightened the symbol manifest descriptions for `initialize_game_assets_and_world`, `update_new_game_menu`, and `initialize_click_start`.
- Reduced one bridge-side blind spot without inventing a live launcher.

### Verification
- `uv run snail symbols`
- `git diff --check`
- This confirms the symbol manifest still validates and the docs/manifests patch is whitespace-clean. No Zig build or test was run because no runtime code changed.

### Git
- Branch: `master`
- Commit(s):
  - `5c5a669` `re: narrow replay attract controller layout`
  - `b469688` `docs: update worklog`
- Push: pushed to remote branch

### Remaining gaps
- The New Game replay-attract timer-step writer at `data_4df904 + 0x4f2dc + 0x14` is still unresolved.
- The secondary timer lane at `+0x8/+0xc` still lacks a confirmed runtime role.
- The saved-owner writer behind the native `26/27/28` bridge jump is still unresolved.

### Next target
- Trace the writer for `data_4df904 + 0x4f2dc + 0x14` together with the replay scratch and preserved-owner bridge fields so the missing New Game attract trigger can be connected to the native outer-controller handoff.

## 2026-03-23 22:55 - Iteration: restore new game tutorial gate

### Target
- Config-backed New Game tutorial gate parity

### Why this target
- The outer bridge replay-attract lane is still blocked on the unresolved timer-step writer, but the same RE pass exposed one smaller front-end mismatch with complete enough evidence to land safely: the Zig menu still showed `Postal Mode`, `Time Trial`, and `Challenge Mode` immediately instead of respecting the native tutorial gate.

### Original behavior evidence
- Confirmed:
  - `initialize_new_game_menu` (`0x417bc0`) hides the `Postal Mode`, `Time Trial`, and `Challenge Mode` widgets while `data_4df9d8 == 0`.
  - `update_new_game_menu` (`0x417eb0`) sets `data_4df9d8 = 1` on the `Tutorial` branch before leaving the menu.
  - `initialize_default_runtime_config` seeds the same byte through the default config blob tail, so the default value is `0`.
- Likely:
  - `data_4df9d8` is a persisted New Game tutorial-progress gate rather than a purely transient menu scratch byte, because it lives inside the config-backed defaults block and the New Game constructor consumes it directly.
- Unknown:
  - The exact native save cadence for that byte beyond the app's broader config save path.

### Zig changes
- `zig/src/config.zig`
- `zig/src/main.zig`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- Exposed the recovered `SnailMail.cfg +0xc0` tutorial-gate byte through the config blob.
- Hid the three gated New Game rows in the existing authored layout, skipped them during keyboard or mouse selection while the gate is clear, and flipped the gate when the Tutorial path launches.
- Reduced one front-end scaffold: the port no longer shows the later New Game modes before the recovered tutorial latch is set.

### Verification
- `zig fmt zig/src/config.zig zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the recovered config field compiles cleanly, the focused New Game visibility/selection tests pass, and the full runtime still builds after the front-end gate change.

### Git
- Branch: `master`
- Commit(s):
  - `429b596` `frontend: restore new game tutorial gate`
- Push: pushed to remote branch

### Remaining gaps
- The New Game replay-attract timer-step writer at `data_4df904 + 0x4f2dc + 0x14` is still unresolved, so the live random replay launcher remains intentionally unported.
- The saved-owner writer behind the native `26/27/28` bridge jump is still unresolved.

### Next target
- Recover the writer for `data_4df904 + 0x4f2dc + 0x14` and the role of the `+0x8/+0xc` timer lane strongly enough to port the New Game random replay attract launcher without guessing.

## 2026-03-23 23:11 - Iteration: split current-row attachment begin from swept re-entry

### Target
- Attachment-follow entry ownership inside `update_subgoldy`

### Why this target
- The attachment-follow phase still carried one of the highest-value remaining scaffolds: the swept installed-entry path was reusing an invented current-row fallback even though Binary Ninja and IDA now make the native direct-begin versus swept-reentry split clear enough to land.

### Original behavior evidence
- Confirmed:
  - `update_subgoldy` calls `begin_track_attachment_follow_state` directly from the live current cell when `player + 0x41d == 0` and the runtime tile is `29` or `30`.
  - The same function only reaches `try_enter_track_attachment_from_swept_motion` when `player + 0x41d != 0`.
  - The swept helper still probes installed owner slots in Windows order rather than acting as the generic current-row begin path.
- Likely:
  - Zig's current trigger for the swept re-entry helper is still broader than the native owner gate behind `player + 0x41d`.
- Unknown:
  - The exact runtime owner/state rule that sets and clears the native `attachment_exit_pending` gate around the swept re-entry branch.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/rewrite/index.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Split current-row installed entry from the swept installed-entry helper, removed the synthetic current-row fallback from the sweep path, and added tests that cover direct current-row begin and later-row installed spans.
- Updated the rewrite notes/checklist to describe the recovered `update_subgoldy` branch split and narrowed the remaining gap to the exact native owner gate.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the gameplay patch still formats, builds, and passes the current test suite, and that the final diff is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `b38944a` `port: split current-row attachment begin from sweep re-entry`
- Push: pushed to remote branch

### Remaining gaps
- Zig still uses a broader gameplay trigger than the native `attachment_exit_pending` branch when deciding whether to probe swept installed entry.
- The full installed-bank owner pairing and the native post-exit seed/value semantics are still unresolved.

### Next target
- Tighten the swept re-entry owner until it is gated by the native `attachment_exit_pending` branch instead of the current broader gameplay trigger.

## 2026-03-23 23:22 - Iteration: gate swept re-entry on live exit pending

### Target
- Swept attachment re-entry ownership inside `update_subgoldy`

### Why this target
- Attachment follow is still one of the highest-value gameplay parity risks, and the Zig runner was still letting the later visited-row pass opportunistically arm swept installed entry even though BN and IDA now pin that helper behind the live `attachment_exit_pending` branch.

### Original behavior evidence
- Confirmed:
  - BN `update_subgoldy` only reaches `try_enter_track_attachment_from_swept_motion` after testing `player + 0x41d` (`attachment_exit_pending`) nonzero.
  - The two native callsites are both keyed from the live current cell row flags (`0x40` then `0x80`) before `follow_state.active` is checked.
  - IDA agrees that the direct `29/30` current-cell begin path runs only while `attachment_exit_pending` is clear, and the swept helper is the separate re-entry lane.
- Likely:
  - The Zig visited-row scan was over-broad because Windows probes re-entry from the current cell after movement, not from older rows consumed by the row-event pass.
- Unknown:
  - Whether a successful swept re-entry clears `attachment_exit_pending` immediately or only through a later controller.
  - The remaining overlap semantics when both installed-owner bits are present on the same live row.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Moved swept installed re-entry out of `processRow` and onto the current-row attachment prime path, so it now only probes the live current row while `attachment_exit_pending` is armed.
- Kept the direct `29/30` current-row begin path intact for the non-exit-pending lane.
- Added regression coverage that proves visited-row processing no longer arms swept re-entry, while the current-row prime path still does once `attachment_exit_pending` is set.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `git diff --check`
- `zig build test`
- `zig build`
- This confirms the gameplay patch formats cleanly, the full test suite still passes with the new current-row re-entry test, and the runtime still builds after the owner change.

### Git
- Branch: `master`
- Commit(s):
  - `f06e4d9` `port: gate swept attachment re-entry on exit pending`
- Push: pushed to remote branch

### Remaining gaps
- The exact post-success clear/overlap semantics around `attachment_exit_pending` are still unresolved.
- The full installed-bank ownership and row-slot pairing rules are still not ported.

### Next target
- Recover the remaining post-success `attachment_exit_pending` / overlapping-owner behavior strongly enough to remove more of the attachment re-entry scaffold without guessing.

## 2026-03-23 23:33 - Iteration: gate swept re-entry on live row flags

### Target
- Current-row swept attachment re-entry slot gating in `update_subgoldy`

### Why this target
- Attachment follow is still one of the highest-value gameplay parity risks, and the current Zig sweep path still treated any installed span on the live row as a valid re-entry candidate even though BN plus IDA now pin the native owner boundary to the live `flags_b` slot bits.

### Original behavior evidence
- Confirmed:
  - BN `update_subgoldy` probes `try_enter_track_attachment_from_swept_motion` only from the live current row while `player + 0x41d` (`attachment_exit_pending`) is nonzero.
  - The first swept callsite is gated by the current row's `flags_b & 0x40` bit, and the second callsite is gated by `flags_b & 0x80`.
  - BN callsite context shows the second probe only runs if `player + 0x41d` is still nonzero after the first call returns.
  - IDA corroborates the same `0x40` then `0x80` slot split around the two `try_enter_track_attachment_from_swept_motion` callsites.
- Likely:
  - The old Zig installed-span iteration could arm sweep re-entry from rows that still carried an installed owner in preview data but no longer exposed the live native slot bit on the current cell.
- Unknown:
  - The exact post-success clear/overlap semantics around `attachment_exit_pending` once the first swept probe succeeds.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Current-row swept re-entry now keys off the live row's recovered owner bits instead of any installed span: `0x40` probes the primary slot first, and `0x80` only gets a second probe if `attachment_exit_pending` survives the first call.
- Added focused regression coverage for the new owner boundary: no live `0x40/0x80` bit means no sweep probe, and a synthetic secondary-slot row only begins through the `0x80` lane.
- Reduced one attachment-entry scaffold: the port no longer treats installed row-span presence alone as sufficient to attempt swept re-entry.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- This confirms the gameplay patch formats cleanly, the full Zig suite still passes with the new slot-gating regressions, the runtime still builds, and the mixed Zig/docs patch is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `2f19b3a` `port: gate swept attachment re-entry on live row flags`
- Push: pushed to remote branch

### Remaining gaps
- The exact post-success clear/overlap semantics around `attachment_exit_pending` are still unresolved.
- The full installed-bank ownership and row-slot pairing rules are still not ported.

### Next target
- Recover whether a successful `flags_b & 0x40` swept re-entry clears `attachment_exit_pending` soon enough to suppress the `0x80` probe on overlapping rows, or whether the second slot can still overwrite the first in the same tick.

## 2026-03-23 23:44 - Iteration: narrow attachment voice-4 milestone gate

### Target
- `voice 4` milestone semantics in `update_track_attachment_follow_state`

### Why this target
- Attachment follow is still one of the highest-priority parity risks, and the docs were still treating the missing `voice 4` cue as a straightforward unported milestone even though BN evidence was finally strong enough to test whether that branch was actually safe to port.

### Original behavior evidence
- Confirmed:
  - Binary Ninja raw disassembly of `update_track_attachment_follow_state` (`0x420cb0`) increments `follow_state->sample_index`, compares the new value against `template->sample_count << 1`, and only then reaches the `voice 4` call at `0x420d30`.
  - The same helper later exits follow when `follow_state->sample_index == template->sample_count`.
  - `begin_track_attachment_follow_state` (`0x420c40`) seeds `follow_state->sample_index = 0`.
  - IDA matches the same control flow and the same contradictory `2 * sample_count` gate before the `voice 4` call.
- Likely:
  - Under the current typed read of `follow_state + 0xc` as the live sample index and `template + 0x44` as the template sample count, the `voice 4` branch is unreachable.
- Unknown:
  - Whether the current counter typing is still wrong, or whether the `voice 4` callsite is stale/dead code that never fires in the shipped runtime.

### Zig changes
- `docs/re/attachment-follow.md`
- `docs/re/audio-callsite-map.md`
- `analysis/runtime/native-audio-callsites.md`
- `docs/rewrite/remaining-work-checklist.md`
- `docs/rewrite/subsystem-status.md`
- `analysis/symbols/gameplay-functions.json`
- No Zig runtime changes; documented that the `voice 4` lane should not be ported until live tracing or stronger type recovery resolves the counter mismatch.

### Verification
- Inspected Binary Ninja decompile, raw disassembly, field xrefs, and `play_voice_manager` callsites for `update_track_attachment_follow_state`.
- Cross-checked the same helper in IDA (`artifacts/ida/functions/00420cb0-update_track_attachment_follow_state.c`).
- Ran `uv run snail symbols`.
- This confirms the symbol-manifest edits remain valid and that the new docs reflect a direct BN/IDA contradiction instead of a guessed port gap.

### Git
- Branch: `master`
- Commit(s):
  - `9c4272f` `re: narrow contradictory attachment voice-4 gate`
- Push: pushed to remote branch

### Remaining gaps
- The live meaning of the `voice 4` lane is still unresolved because the current typed follow/template counters make the static gate contradictory.
- Template fields around `+0x44` and `+0x9c` may still need stronger typing before the follow milestone and special-branch semantics can be ported safely.

### Next target
- Trace or re-type the follow/template counters around `update_track_attachment_follow_state`, especially `follow_state + 0xc` and template `+0x44/+0x9c`, before attempting any `voice 4` milestone port.

## 2026-03-23 23:52 - Iteration: store native replay return owner lane

### Target
- Persistent selected-replay return-owner storage in the outer bridge context

### Why this target
- The outer bridge is still the top ownership risk, and BN plus IDA now pin one concrete remaining abstraction error tightly enough to remove it: the port still stored persistent replay returns as a high-level target even though Windows carries a raw saved owner state at `+0xff25d8` / `+0x1066bf0`.

### Original behavior evidence
- Confirmed:
  - `update_high_score_screen` (`0x417260`) seeds `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0` before state `10`, with `+0x1066bf0 = 18` on replay-row launches.
  - `update_new_game_menu` (`0x417eb0`) seeds the same persistent replay scratch on the random replay-attract branch, with `app + 0x1066bf0 = 2`.
  - `update_pause_menu` (`0x4407a0`) branches on `app + 0x1066be9` and sends persistent replay abandon through completion state `3`.
  - `update_completion_screen` (`0x4067e0`) state `3` destroys subgame and restores `app + 0x1066bf0` directly into the active frontend owner.
- Likely:
  - The current port only needs two literal persistent replay return-owner values for now: `18` (`High Scores`) and `2` (`New Game`).
- Unknown:
  - The full lifetime of `game + 0xff25d8` after subgame init is still not traced end-to-end.
  - The New Game replay-attract timer-step writer at `data_4df904 + 0x4f2dc + 0x14` is still unresolved.

### Zig changes
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- Added a native-shaped `SelectedReplayReturnState` lane for persistent replay launch context and now derive a higher-level bridge target from that raw owner only when the app needs to rebuild a frontend shell.
- Kept the older high-level target only as a fallback for transient or non-native replay launch cases instead of using it as the primary stored lane for persistent replay ownership.
- Tightened replay-bridge tests so persistent high-score/New Game returns assert against the raw stored owner state instead of relying on an inferred target.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- This confirms the bridge refactor compiles, the replay-bridge regression tests still pass, and the runtime build remains healthy after the ownership change.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `bridge: store native persistent replay return owner`
- Push: pending push after commit

### Remaining gaps
- The port still does not implement the New Game replay-attract timer/controller itself.
- Persistent replay launch storage is now more literal, but the saved-owner writer behind the general `26/27/28` bridge slot is still unresolved outside the replay-specific lanes.

### Next target
- Recover the New Game replay-attract timer-step writer and its `+0x8/+0xc/+0x10/+0x14` controller semantics well enough to port that persistent launcher without guessing.

## 2026-03-24 00:06 - Iteration: seed non-random course-end threshold from last block

### Target
- Completion-handoff course-end threshold ownership in `populate_runtime_track_cells_from_segments` / `LoadedLevelPreview`

### Why this target
- Cutscene and handoff runtime fields are still a top priority, and the preview still seeded `course_end_threshold` from a last-row fallback even though Binary Ninja now pins the native non-random producer tightly enough to replace that guess.

### Original behavior evidence
- Confirmed:
  - Binary Ninja and IDA both show non-random `populate_runtime_track_cells_from_segments` seeding `game + 0x54` from the generated runtime row count, then writing `game + 0x58 = game + 0x54 - game + 0x1abf1c`.
  - In the non-random branch, `game + 0x54` is built from the first-block length, the final `Last:` block length, and the summed middle-segment lengths before `update_subgoldy` ever reads `game + 0x58`.
  - The March 15 `cdb` capture hit the first completion-handoff arm with `game + 0x58 = 753`, which matches the start of `ARCADE000`'s final `Last:` block rather than the last populated row.
- Likely:
  - On non-random shipped levels, the completion handoff arms at the start of the final `Last:` block, not at `total_rows - 1`.
  - Random challenge-style builders still need the native `Length`-driven generated row count before the same producer can be ported safely in Zig.
- Unknown:
  - The exact random-builder row-count producer in the current Zig preview, including the challenge-only length scaling lane.

### Zig changes
- `zig/src/track.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Replaced the non-random `course_end_threshold` fallback with the recovered start-of-final-`Last:`-block producer.
- Kept random level previews on the old fallback and documented that remaining gap explicitly instead of guessing a `Length`-driven row count.
- Added focused tests for the non-random producer and for the retained random fallback.

### Verification
- `zig fmt zig/src/track.zig`
- `zig build test`
- `zig build`
- This confirms the new threshold producer compiles, the full test suite still passes, and the runtime build remains healthy after the handoff-threshold change.

### Git
- Branch: `master`
- Commit(s):
  - `64d003a` `port: seed non-random course-end threshold from last block`
- Push: pushed to remote branch

### Remaining gaps
- Random challenge-style builders still keep the old fallback because the preview does not yet synthesize the native `Length`-driven generated row count.
- The broader random/runtime track builder ownership, including challenge-only scaling, is still only partial in Zig.

### Next target
- Recover the random `Length` row-count producer in `populate_runtime_track_cells_from_segments` well enough to remove the remaining `course_end_threshold` fallback on challenge-style builds.

## 2026-03-24 00:19 - Iteration: seed random challenge course-end threshold from Length

### Target
- Random challenge-style `course_end_threshold` parity in `populate_runtime_track_cells_from_segments` / `LoadedLevelPreview`

### Why this target
- Cutscene and handoff runtime fields are still a top priority, and the previous run left one explicit completion fallback behind even though BN plus IDA now pin the random mode-1 threshold producer tightly enough to replace it without guessing the whole random strip builder.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile and raw disassembly of `populate_runtime_track_cells_from_segments` (`0x435eb0`) show `game + 0x54` seeding from `game + 0x1b0138` (`Length:`), then for mode `1` applying `floor((game + 0x34) * 0.65 + 0.35) * Length` before writing `game + 0x58 = game + 0x54 - game + 0x1abf1c`.
  - `load_level_definition_file` (`0x447480`) stores the middle-segment count at `game + 0xa874`, the authored `Length:` dword at `game + 0x1b0138`, and the `Random:yes` byte at `game + 0x1b013c`.
  - `copy_segment_definition_to_level_slot` (`0x447300`) and the same builder path show `game + 0x1abf1c` is the final `Last:` block row count consumed by that subtraction.
  - `build_subgame_level` (`0x437eb0`) restores `game + 0x34` from selected-record compact field `+0x50`, which matches the recovered `challenge_difficulty_value` lane in the compact score record layout.
- Likely:
  - Ordinary non-replay challenge launches feed the same `game + 0x34` lane from the live challenge-difficulty slider, so the current Zig `currentRunChallengeDifficultyScalar()` is the right producer for the recovered threshold math.
- Unknown:
  - The preview still does not build the native generated random middle strip, so total row ownership and the exact random segment sequence remain unresolved.

### Zig changes
- `zig/src/track.zig`
- `zig/src/main.zig`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `analysis/symbols/gameplay-functions.json`
- Replaced the random challenge-style completion threshold fallback with the recovered `Length` / scalar producer while leaving the broader random strip builder unchanged.
- Added focused coverage for the new random-threshold path and kept the fallback test for callers that do not supply the native scalar.
- Corrected the recovered game-side level block notes: `game + 0xa874` is the loaded middle-segment count, not the old row-event placeholder label.

### Verification
- `zig fmt zig/src/main.zig zig/src/track.zig`
- `zig build test`
- `zig build`
- `uv run snail symbols`
- This confirms the threshold patch compiles, the new and existing track tests pass, the runtime still builds, and the symbol manifest stays consistent after the description update.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `port: seed random challenge course-end threshold from Length`
- Push: pending push after commit

### Remaining gaps
- Random challenge-style previews still concatenate every candidate middle segment instead of the native generated strip.
- The non-replay writer for `game + 0x34` is still inferred from the selected-record restore path rather than recovered directly from the ordinary challenge launcher.

### Next target
- Recover the native random middle-strip generator well enough to replace the remaining challenge preview ownership with the real generated row sequence instead of the current all-segments scaffold.

## 2026-03-24 00:27 - Iteration: narrow new game replay attract selector lanes

### Target
- New Game replay-attract bridge lane and the raw rebuild selector behind `game + 0x1270fc8` / app `+0x12e55e0`

### Why this target
- The outer bridge is still the top architectural risk, and BN plus IDA now pinned one missing launch-side slice tightly enough to reduce ambiguity without guessing runtime code: the New Game replay-attract path and selector-`1` vs selector-`2` rebuild split.

### Original behavior evidence
- Confirmed:
  - `update_new_game_menu` (`0x417eb0`) direct `Postal Mode` destroys the menu, writes frontend state `10`, writes `app + 0x74658 = 0`, and writes app `+0x12e55e0 = 2` without seeding the selected-record scratch.
  - The same helper's replay-attract lane rotates a menu-local cursor through `0..4`, probes only banks `0/1/3`, gives up after `1000` attempts, seeds `app + 0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`, and resets menu locals `+0x8/+0xc` to `0` and `1/3600`.
  - `initialize_subgame` (`0x4374b0`) treats selector `1` as the postal post-completion reopen path and selector `2` as the ordinary rebuild/start lane by `level_mode`.
- Likely:
  - The menu-local byte at `data_4df904 + 0x4f2dc + 0x4` is the replay-attract hide latch, because successful replay launch sets it to `1` and later input clears it before unhiding all six menu widgets.
- Unknown:
  - The writer for the menu-local replay-attract step at `+0x14`.
  - The exact later role of the `+0x8/+0xc` secondary timer lane.

### Zig changes
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `analysis/symbols/gameplay-functions.json`
- Tightened the raw bridge-memory docs so selector `1` vs `2` is no longer just "not replay-only": selector `1` now explicitly maps to the postal post-completion reopen, and selector `2` to the ordinary rebuild/start lane.
- Recorded the exact New Game replay-attract bank scan, direct-button split, persistent scratch writes, and the still-unresolved timer-step producer.
- Reduced one doc-side scaffold: the repo no longer treats app dword `+0x12e55e0` as only a rejected replay clue; it now has a narrower evidence-backed bridge meaning.

### Verification
- `uv run snail symbols`
- Re-read BN decompile and raw disassembly for `update_new_game_menu`, `initialize_new_game_menu`, and `initialize_subgame`, with the repo's IDA export as a second opinion.
- This validates the symbol manifest after the description updates and keeps the new selector/attract notes tied to matching BN+IDA control flow instead of inference.

### Git
- Branch: `master`
- Commit(s):
  - `c295ddb` `re: narrow new game replay attract selector lanes`
- Push: pushed to remote branch

### Remaining gaps
- The New Game random replay attract launcher is still not exposed in Zig because the timer-step writer at `data_4df904 + 0x4f2dc + 0x14` is still unresolved.
- The saved-owner writer behind the native `26/27/28` bridge jump remains unresolved outside the already-confirmed handoff lanes.

### Next target
- Recover the writer for the New Game replay-attract timer step at `data_4df904 + 0x4f2dc + 0x14`, and confirm whether the `+0x8/+0xc` timer lane later feeds that step or only gates menu re-entry after an attract launch.

## 2026-03-24 00:39 - Iteration: clarify replay attract startup suppressor

### Target
- New Game replay-attract hide-latch and click-start startup suppressor

### Why this target
- The outer bridge is still the highest-value gap, and this was the narrowest replay-launch lane where BN plus IDA already pinned real consumers but the repo still described part of the behavior as open.

### Original behavior evidence
- Confirmed:
  - `update_new_game_menu` (`0x417eb0`) resets menu locals `+0x8/+0xc` to `0` and `1/3600` on both successful replay launch and the `1000`-attempt give-up path.
  - `initialize_subgoldy` (`0x43a9c0`) unconditionally calls `initialize_click_start` (`0x442170`).
  - `initialize_click_start` hides the `Click to Start` widget immediately when `app + 0x1066be8 != 0`.
  - `update_subgame` (`0x438b90`) later reads `data_4df904 + 0x4f2e4`, compares it against `1.0`, and clears `data_4df904 + 0x4f2e0` once that threshold is exceeded.
- Likely:
  - The menu-local `+0x8/+0xc` pair is a secondary replay-attract startup suppressor lane rather than a generic menu re-entry timer.
- Unknown:
  - The writer for the menu-local replay-attract step at `data_4df904 + 0x4f2dc + 0x14`.
  - The updater or reseed path for the secondary suppressor lane at `data_4df904 + 0x4f2dc + 0x8/+0xc`.

### Zig changes
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `analysis/symbols/gameplay-functions.json`
- Tightened the replay-launch docs so the New Game menu `+0x8/+0xc` lane is no longer treated as wholly unknown: it is now recorded as a confirmed startup suppressor consumed by `update_subgame`.
- Recorded that `initialize_subgoldy` always constructs the click-start owner and that persistent replay launches suppress that prompt directly through `initialize_click_start`.
- Added symbol descriptions so `initialize_subgoldy` and `update_click_start` preserve the newly recovered startup-owner behavior.

### Verification
- `uv run snail symbols`
- `git diff --check`
- Re-read BN decompile plus raw disassembly for `update_new_game_menu`, `initialize_click_start`, `initialize_subgoldy`, and `update_subgame`, with the repo's IDA export as a second opinion where the startup suppressor path was ambiguous.
- This validates the symbol manifest after the description updates and keeps the new startup-suppressor notes tied to confirmed consumers rather than guesswork.

### Git
- Branch: `master`
- Commit(s):
  - `9e05c0b` `re: document replay attract startup suppressor`
- Push: pushed to remote branch

### Remaining gaps
- The New Game random replay attract launcher is still not exposed in Zig because the writer for the menu-local replay-attract step at `+0x14` is still unresolved.
- The secondary suppressor lane at `+0x8/+0xc` now has a confirmed consumer, but its updater or reseed path is still unknown.

### Next target
- Recover the writer for `data_4df904 + 0x4f2dc + 0x14`, then trace whether the `+0x8/+0xc` suppressor lane advances alongside it or is maintained by a separate owner.

## 2026-03-24 00:48 - Iteration: narrow swept re-entry gate persistence

### Target
- Immediate `attachment_exit_pending` behavior around primary/secondary swept attachment re-entry in `update_subgoldy`

### Why this target
- The replay-attract timer-step writer is still blocked on missing provenance, and attachment follow remained the next highest-value narrow lane with enough Binary Ninja and IDA evidence to close one real uncertainty without guessing runtime behavior.

### Original behavior evidence
- Confirmed:
  - BN `update_subgoldy` (`0x43b120`) probes `try_enter_track_attachment_from_swept_motion` from `flags_b & 0x40` first, then re-tests `player + 0x41d` before the `flags_b & 0x80` callsite.
  - Raw disassembly of `try_enter_track_attachment_from_swept_motion` (`0x42c770`) plus the checked-in IDA export do not show a direct helper-side clear of `player + 0x41d` before control returns to that second gate check.
  - BN field xrefs on `Player.attachment_exit_pending` (`+0x41d`) only show direct writes in `initialize_subgoldy_fall_state` and `update_subgoldy`, not in the swept-entry helper itself.
- Likely:
  - Overlapping rows still leave the `0x80` probe reachable in the same tick after a successful `0x40` re-entry attempt.
- Unknown:
  - Which later controller finally retires `attachment_exit_pending` after swept re-entry.
  - Whether two geometrically valid overlapping probes can overwrite each other in one tick under shipped content.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/re/windows-debugging-wants.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Added a focused regression that pins the confirmed immediate behavior: successful swept re-entry leaves `attachment_exit_pending` armed.
- Tightened the current-row swept-entry source comment so the code records why the gate stays live across the primary probe.
- Removed the stale docs/checklist claim that the immediate post-success clear itself is still the open question; the remaining gap is now the later retirement path plus live overlap outcome.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `git diff --check`
- This confirms the new regression compiles and passes, the existing Zig suite stays green, and the mixed Zig/docs patch is whitespace-clean.

### Git
- Branch: `master`
- Commit(s):
  - `800e202` `re: narrow swept attachment gate persistence`
- Push: pushed to remote branch

### Remaining gaps
- The later controller that finally retires `attachment_exit_pending` after swept re-entry is still unresolved.
- Live overlap where both `0x40` and `0x80` probes are geometrically valid still needs direct confirmation.
- The full installed-bank ownership and row-slot pairing rules are still not ported.

### Next target
- Recover the later `attachment_exit_pending` retirement path after swept re-entry, then confirm with a live overlap whether two valid probes can overwrite each other in one tick.

## 2026-03-24 00:56 - Iteration: narrow attachment exit retirement clears

### Target
- Later `attachment_exit_pending` retirement after swept re-entry in `update_subgoldy`

### Why this target
- Attachment follow is still one of the highest-value gameplay parity risks, and the immediate same-tick sweep behavior is already narrowed. The remaining question is now the later retirement path, and BN plus the checked-in IDA export were strong enough to eliminate two wrong static stories without guessing runtime behavior.

### Original behavior evidence
- Confirmed:
  - Binary Ninja field xrefs show `player + 0x41d` (`attachment_exit_pending`) is only written by `initialize_subgoldy_fall_state` and five clear sites inside `update_subgoldy`: `0x43bcb3`, `0x43bf6f`, `0x43c06d`, `0x43c3ea`, and `0x43ce75`.
  - Binary Ninja field xrefs show `player + 0x434` (`attachment_exit_progress`) is only written by `initialize_subgoldy_fall_state` and the single `update_subgoldy` store at `0x43ce96`.
  - Raw BN plus the checked-in IDA export still show `try_enter_track_attachment_from_swept_motion` does not directly clear `attachment_exit_pending` before the caller re-tests the same byte for the secondary `0x80` probe.
  - The `0x43c3ea` clear follows the tile-`22` trampoline settle branch and the `sfx 41` landing cue, while `0x43bf6f` follows the ordinary snap-to-ride-height branch.
- Likely:
  - `0x43c06d` is a separate floor-snap retirement branch.
  - `0x43bcb3` and `0x43ce75` are later motion-state clears inside `update_subgoldy`, but their exact gameplay-owner labels are still unresolved.
- Unknown:
  - Which of those five clear sites is the common post-swept-re-entry retirement path.
  - Whether a geometrically valid `0x40`/`0x80` overlap can still reach two successful probes before one of those later clears wins.
  - Whether the common re-entry retirement can fire while a re-entered follow state is already active or only after returning to track movement.

### Zig changes
- `docs/re/attachment-follow.md`
- `docs/re/runtime-structures.md`
- `docs/re/windows-debugging-wants.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `analysis/symbols/gameplay-functions.json`
- No Zig runtime behavior changed.
- Reduced one attachment-follow blind spot: the repo no longer treats helper-side clear or raw progress-expiry clear as viable static explanations for later `attachment_exit_pending` retirement.

### Verification
- `uv run snail symbols`
- `git diff --check`
- Reviewed BN field xrefs, `bn callsites`, raw disassembly, and the checked-in IDA export for `update_subgoldy` and `try_enter_track_attachment_from_swept_motion`.
- This gives high confidence in the negative result: the missing retirement path is one of the later `update_subgoldy` clear sites, not another hidden helper-side or timer-only clear.

### Git
- Branch: `master`
- Commit(s):
  - `edc7ca4` `re: narrow attachment exit retirement clears`
- Push: pushed to remote branch

### Remaining gaps
- The common post-swept-re-entry retirement path among the five `update_subgoldy` clear sites is still unresolved.
- The current Zig timer-based `attachment_exit_pending` clear remains scaffolded because the matching native clear-site context is not yet mapped tightly enough to replace it safely.
- Live overlap where both `0x40` and `0x80` probes are geometrically valid still needs direct confirmation.

### Next target
- Classify which `update_subgoldy` clear site actually retires `attachment_exit_pending` after swept re-entry, ideally with a focused Windows capture that watches the five clear sites alongside successful `0x40`/`0x80` probes.

## 2026-03-24 01:04 - Iteration: retire jetpack-owned attachment exit clear

### Target
- Active-jetpack `attachment_exit_pending` retirement in `update_subgoldy` / Zig attachment-exit controller

### Why this target
- Attachment follow is still a top gameplay parity risk, and the current Zig code still used a broad `progress >= 1.0` retirement story even though BN plus IDA now pin one concrete late-clear owner tightly enough to replace part of that scaffold safely.

### Original behavior evidence
- Confirmed:
  - BN disassembly and decompile of `update_subgoldy` show the late clear at `0x43ce75` is reached only from `0x43ce23` when `player + 0x275c == 1`, which matches the current `jetpack_gauge.state` lane.
  - That `0x43ce23 -> 0x43ce75` branch executes before the `attachment_exit_progress` update at `0x43ce8a` and the gate-A block at `0x43ce9c`, so the active-jetpack slice does not wait for the later progress gates.
  - IDA’s checked-in `update_subgoldy` export agrees that the same late clear is guarded by `player_1->jetpack_gauge.state == 1`.
- Likely:
  - The current Zig `jetpack.active` bool is a close enough stand-in for the native `jetpack_gauge.state == 1` slice to retire `attachment_exit_pending` in active gameplay without waiting on the generic timeout.
- Unknown:
  - Which of the remaining non-jetpack clear sites is the common post-swept-re-entry retirement path.
  - The exact gameplay-owner label behind the separate `0x43bcb3` motion-state clear.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/re/runtime-structures.md`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Retired `attachment_exit_pending` immediately on the evidence-backed active-jetpack lane instead of letting that slice fall through the generic progress-expiry scaffold.
- Added focused tests for jetpack-owned exit retirement and the same-tick route-end completion consequence.
- Reduced one attachment-follow scaffold and narrowed the remaining retirement-path docs so `0x43ce75` is no longer treated as a generic/common candidate.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- Re-read BN disassembly/decompile plus the checked-in IDA export for `update_subgoldy`, focusing on `0x43ce23`, `0x43ce75`, and the surrounding late gate block.
- This gives high confidence that the new Zig branch matches one confirmed native owner lane and that the wider runtime still builds and tests cleanly after the change.

### Git
- Branch: `master`
- Commit(s):
  - `287744c attachment: retire active-jetpack exit clear`
- Push: pushed to remote branch

### Remaining gaps
- The common post-swept-re-entry retirement path among the remaining non-jetpack clears is still unresolved.
- The `0x43bcb3` later motion-state clear still needs a tighter gameplay-owner label.
- Live overlap where both `0x40` and `0x80` probes are geometrically valid still needs direct confirmation.

### Next target
- Recover which of the remaining non-jetpack `update_subgoldy` clear sites actually retires `attachment_exit_pending` after swept re-entry, ideally with a focused Windows capture over the surviving clear sites plus successful `0x40`/`0x80` probes.

## 2026-03-24 01:14 - Iteration: drop synthetic attachment exit timeout clear

### Target
- Active-phase `attachment_exit_pending` retirement in the Zig attachment-exit controller

### Why this target
- Attachment follow is still a top gameplay parity risk, and the repo docs already ruled out the current Zig `progress >= 1.0` clear as a native explanation. BN plus IDA now pin enough real clear sites to replace that timeout with a narrower evidence-backed proxy.

### Original behavior evidence
- Confirmed:
  - BN field xrefs still show `attachment_exit_progress` is only written by `initialize_subgoldy_fall_state` and the single `update_subgoldy` store at `0x43ce96`.
  - BN plus the checked-in IDA export show `attachment_exit_pending` only clears at `0x43bcb3`, `0x43bf6f`, `0x43c06d`, `0x43c3ea`, and `0x43ce75`.
  - `0x43bf6f` is an ordinary grounded snap-to-ride-height clear, `0x43c06d` is another floor-snap clear in a separate gated branch, `0x43c3ea` is the trampoline landing clear, and `0x43ce75` is the already-ported active-jetpack clear.
  - No current static evidence supports a raw `attachment_exit_progress >= 1.0` timeout clear in Windows.
- Likely:
  - Because the Zig port still lacks the full native airborne carryover after non-fall attachment exits, an active-phase grounded/trampoline settle proxy is closer to the recovered Windows clear sites than the old synthetic timeout expiry.
- Unknown:
  - Which remaining clear site is the common post-swept-re-entry retirement lane.
  - The gameplay-owner meaning of the separate `0x43bcb3` motion-state clear.
  - The full native airborne carryover between `end_track_attachment_follow_state` and those later active-phase settle clears.

### Zig changes
- `zig/src/gameplay.zig`
- `docs/re/attachment-follow.md`
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Removed the Zig-only `attachment_exit_progress >= 1.0` retirement path.
- Kept the confirmed active-jetpack clear and added an active-phase grounded/trampoline settle proxy for the native `0x43bf6f` / `0x43c06d` / `0x43c3ea` lanes.
- Added focused tests proving fall-phase progress no longer clears the gate by itself and that settled active track rows can still retire the gate so completion is not blocked indefinitely.

### Verification
- `zig fmt zig/src/gameplay.zig`
- `zig build test`
- `zig build`
- Re-read BN disassembly/xrefs plus the checked-in IDA export for the five `update_subgoldy` clear sites and the `player + 0x41c` / `player + 0x41d` neighborhood.
- This gives high confidence that the port no longer claims a fake native timeout clear and still compiles/tests after the narrower retirement behavior change.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `attachment: drop synthetic exit timeout clear`
- Push: pending push after commit

### Remaining gaps
- The common post-swept-re-entry retirement path among the remaining non-jetpack clear sites is still unresolved.
- The active-phase grounded/trampoline retire is still a conservative proxy because the full native airborne carryover is not ported yet.
- The `0x43bcb3` later motion-state clear still needs a tighter gameplay-owner label.

### Next target
- Recover which remaining non-jetpack `update_subgoldy` clear site actually wins after swept re-entry, especially whether the common lane is one of the grounded snaps or the unresolved `0x43bcb3` motion-state branch.

## 2026-03-24 01:18 - Iteration: route thanks-screen exit into credits

### Target
- Final postal completion handoff from the Thanks For Playing owner into the next frontend owner

### Why this target
- The outer subgame/frontend bridge is still the top architecture risk, and BN plus IDA already pinned one concrete wrong Zig lane tightly enough to replace it safely: the Thanks-screen exit still faded straight to the main menu instead of following the native owner handoff.

### Original behavior evidence
- Confirmed:
  - BN `update_frontend_state_machine` shows state `0x1d` initializing the Thanks owner, advancing to state `0x1e`, and state `0x0e` initializing the credits intro screen.
  - BN and the checked-in IDA export for `update_thanks_for_playing_screen` (`0x4340f0`) show the continue branch only firing once `this + 8 >= 2`, playing `sfx 8`, and starting the frontend fade while no other fade is active.
  - BN and IDA `uninit_thanks_screen` (`0x4340c0`) then kill the border and write app state `0x0e`, so the Thanks owner hands off into credits rather than back to the main menu.
- Likely:
  - The current Zig credits phase is the closest native match for that `0x0e` handoff because the port already maps it to `initialize_intro_screen(..., "Intro/Credits.txt")`-shaped assets and music.
- Unknown:
  - The broader preserved-owner writer behind bridge states `26/27/28` is still unresolved.

### Zig changes
- `zig/src/main.zig`
- `docs/rewrite/port-status.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- Thanks-screen continue now plays the native confirm cue, only arms while the frontend fade is idle, and fades into the credits phase instead of the main menu.
- Added a focused unit test locking the native `thanks -> credits` handoff.
- Reduced one explicit outer-bridge mismatch in the status docs: `29/30` no longer stop at a vague "return to shell" description.

### Verification
- `zig fmt zig/src/main.zig`
- `zig build test`
- `zig build`
- `git diff --check`
- Re-read BN decompile for `update_frontend_state_machine`, `update_thanks_for_playing_screen`, `initialize_thanks_for_playing_screen`, and `uninit_thanks_screen`, with the checked-in IDA exports as a second opinion.
- This gives high confidence that the port now follows the native Thanks-owner exit target and still builds/tests cleanly.

### Git
- Branch: `master`
- Commit(s):
  - `2b50547 bridge: route thanks screen exit into credits`
- Push: pushed to remote branch

### Remaining gaps
- The preserved-owner writer behind bridge states `26/27/28` is still unresolved.
- The port still models the bridge as an explicit dispatcher instead of the literal Windows outer controller object.
- Remaining replay-sensitive and post-overlay owner details still need tighter bridge reconstruction.

### Next target
- Recover the writer for the preserved-owner bridge slot consumed by states `26/27/28`, so the remaining outer-bridge returns stop relying on inferred owner capture.

## 2026-03-24 01:27 - Iteration: pin selected-replay startup bridge writer

### Target
- Selected-record startup saved-owner write in `update_subgame`

### Why this target
- The outer bridge is still the top architecture risk, and the repo memory still claimed the `26/27/28` saved-owner writer was broadly unresolved even though whole-image BN evidence was now strong enough to narrow that claim.

### Original behavior evidence
- Confirmed:
  - `update_frontend_state_machine` reads the bridge jump target from `[controller + 0x98]` after states `0x1a/0x1b/0x1c`.
  - Whole-image BN instruction search found a direct startup-side store in `update_subgame` (`0x439994` / `0x4399b2`), with the checked-in IDA export corroborating the same block.
  - In `update_subgame` state `2`, when `selected_level_record_active != 0` and either the click-start owner raises flag `0x4000` while `game + 0xc == 0` or the New Game replay-attract hide latch at `data_4df904 + 0x4f2e0` is armed, Windows copies `app + 0x1b8` into `app + 0x1bc`.
  - The same block then writes `app + 0x1b8 = 0x1a` when `selected_level_record_persistent != 0`, otherwise `app + 0x1b8 = 0x1b`.
- Likely:
  - The earlier "saved-owner writer unresolved" note was too broad; the remaining gap is the full set of non-startup helper producers, not whether the field ever has a direct writer.
- Unknown:
  - Which non-startup helpers besides the already confirmed gameplay-side branches seed distinct saved owners before `26/27/28`.
  - Who writes the New Game replay-attract timer step at `data_4df904 + 0x4f2dc + 0x14`.

### Zig changes
- `docs/re/runtime-structures.md`
- `docs/rewrite/subsystem-status.md`
- `docs/rewrite/remaining-work-checklist.md`
- `docs/re/windows-debugging-wants.md`
- Recorded the confirmed `update_subgame` startup-side `save current owner -> 0x1a/0x1b` bridge write.
- Narrowed the remaining bridge unknowns so the repo no longer claims the saved-owner writer is globally unresolved.
- Reduced stale RE scaffolding in the bridge tracker and debugger-wants docs.

### Verification
- Re-read BN decompile/disassembly for `update_frontend_state_machine`, `update_subgame`, `initialize_click_start`, and the `0x439994` / `0x4399b2` block.
- Re-read the checked-in IDA export for `update_subgame` as a second opinion on the same startup branch.
- Ran `git diff --check`.
- This gives high confidence that the updated docs match direct static evidence and stay internally consistent.

### Git
- Branch: `master`
- Commit(s):
  - pending commit: `re: document selected-replay startup bridge writer`
- Push: pending push after commit

### Remaining gaps
- The literal Windows outer-controller object is still not modeled in Zig.
- The full set of non-startup saved-owner producers before `26/27/28` is still incomplete.
- The New Game replay-attract timer and suppressor writers remain unresolved.

### Next target
- Recover either the non-startup helper that still seeds saved owners before `26/27/28`, or the New Game replay-attract timer-step writer at `data_4df904 + 0x4f2dc + 0x14`.
