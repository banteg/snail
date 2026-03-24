# Windows Frida Handoff

This handoff is for the Windows-side agent that will run the original game under Frida and collect runtime evidence for the remaining RE gaps.

Use this together with:

- [Frida runtime trace](frida-runtime-trace.md)
- [Path system](path-system.md)
- [tools/frida/snailmail-runtime-trace.js](../../tools/frida/snailmail-runtime-trace.js)
- [tools/frida/snailmail-path-oracle.js](../../tools/frida/snailmail-path-oracle.js)

## Goal

Static RE is now strong on:

- `SnailMail.dat`
- `.x2` rendering and animation
- `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- the hardcoded `Path=` name table
- the main track-build and render-cache pipeline

The remaining gaps are runtime-behavior questions:

- when `P/p` rows become real attachment-follow transitions
- how the player state evolves while attachment-follow is active and when it exits
- how the death path selects respawn vs final loss and when visible lives decrement
- when completion arms, initializes the completion screen, and first calls `complete_subgame`
- how often `Salt:` spawns without authored `&` rows
- how live salt hazards move after spawn
- where health, jetpack, and ring rows become live entities or effects
- what authored `JetPack=Off` rows do in live play
- what `NoFall` rows actually suppress at runtime
- how often `M` rows turn into slug spawns in real play

## Required Setup

From the Windows machine, have all of these available:

1. A checkout or copy of this repo.
2. The original game files plus a locally generated [SnailMail_unwrapped.exe](../../artifacts/bin/SnailMail_unwrapped.exe). If it is missing, generate it first with `uv run snail unwrap`.
3. Frida CLI installed and working on Windows.
4. The trace script at [tools/frida/snailmail-runtime-trace.js](../../tools/frida/snailmail-runtime-trace.js).
5. The focused path oracle at [tools/frida/snailmail-path-oracle.js](../../tools/frida/snailmail-path-oracle.js) when the target is `HALFPIPE`/`WARP`/loop-family runtime behavior instead of general gameplay.

Recommended quick checks:

```powershell
frida --version
Get-ChildItem .\tools\frida\snailmail-runtime-trace.js
Get-ChildItem .\artifacts\bin\SnailMail_unwrapped.exe
```

## Important Targeting Rules

- Prefer `SnailMail_unwrapped.exe`, not `SnailMail.exe`.
- The script is written for the 32-bit gameplay runtime and accepts either `SnailMail_unwrapped.exe` or `SnailMail.RWG`.
- The script resolves addresses relative to the loaded module base, so ASLR is fine as long as the module is really the gameplay image.
- Keep captures short and focused. Several short NDJSON files are much better than one giant noisy trace.

## Current Hook Set

The script currently hooks these points:

- `0x437eb0` `normalize_level_runtime_fields`
- `0x429ae0` `find_segment_path_index_by_name`
- `0x43b120` `update_subgoldy`
- `0x43c7b7` `completion_handoff_active_arm`
- `0x404920` `initialize_completion_screen_entry` filtered to completion return `0x446c03`
- `0x438700` `complete_subgame_entry` filtered to completion returns `0x43c986`, `0x43c9b4`, and `0x43c9cd`
- `0x446b04` `death_handoff_via_cutscene`
- `0x43c093` `death_handoff_via_update_subgoldy`
- `0x441fa0` `death_select_state_set`
- `0x441fd0` `update_subgoldy_resurrect_enter`
- `0x44205b` `respawn_life_decrement`
- `0x442096` `respawn_complete_subgame_branch`
- `0x42c770` `try_enter_track_attachment_from_swept_motion`
- `0x420c40` `begin_track_attachment_follow_state`
- `0x420cb0` `update_track_attachment_follow_state`
- `0x43af60` `end_track_attachment_follow_state`
- `0x43d4d0` `sample_track_floor_height_at_position`
- `0x43da80` `spawn_track_garbage_hazard`
- `0x43d6c0` `spawn_track_health_pickup`
- `0x43d890` `spawn_track_jetpack_pickup`
- `0x43df10` `spawn_track_ring_or_special_effect`
- `0x441560` `spawn_salt_runtime_entity`
- `0x4417d0` `update_salt_hazard`
- `0x441740` `deactivate_salt_runtime_entity`
- `0x43dc80` `spawn_slug_runtime_entity`
- `0x447040` `get_track_cell_row_index` for row tagging when safe

For the narrower path oracle, the current hook set is:

- `0x437eb0` `normalize_level_runtime_fields`
- `0x429ae0` `find_segment_path_index_by_name`
- `0x435eb0` `populate_runtime_track_cells_from_segments`
- `0x4444b0` `project_position_onto_track_attachment`
- `0x42c770` `try_enter_track_attachment_from_swept_motion`
- `0x420c40` `begin_track_attachment_follow_state`
- `0x420cb0` `update_track_attachment_follow_state`
- `0x43af60` `end_track_attachment_follow_state`
- `0x42b920` `compute_kind42_attachment_transform`

Important payload notes for the current script:

- `SnailMail_unwrapped.exe` is now the primary runtime target
- `path_lookup.path_name` is canonicalized from the recovered path-index table when possible
- `path_lookup.path_name_raw` is still included for debugging bad or truncated reads
- `level_start.selected_track_id` is only meaningful when `active_level_present` is true
- for tutorial-like captures, prefer `mode_before` and `mode_after` over `selected_track_id`
- `level_start.build_flags`, `track_row_start`, and `track_row_end` are now emitted and are the main fields to compare against the static track-builder notes
- every traced `cell` object now includes `flags` from `cell + 0x4`, not just `tile_type` and world position
- every traced `cell` object now also includes `floor_height` from `cell + 0x14`
- row-cell and gameplay-grid captures now also expose `row_scalar_a`, `row_scalar_b`, and `payload` from `+0x24`, `+0x34`, and `+0x50`
- `cell.storage` now tells you whether the event points at a gameplay grid cell or a row-cell attachment record
- `cell.lane` is now derived for gameplay grid cells from the recovered runtime grid layout
- `player_update` and `attachment_end` are `thiscall` methods and the newest script version reads their object state from `ecx`
- `player_update.cell` is now sampled from player position via `get_track_grid_cell_at_world_position`; the older ambiguous field is retained only as `raw_cell`
- attachment events now include:
  - `template_summary` with the active attachment template header floats, kind, mirror or variant flags, terminal flag, sample count, width or scale, and sample-array pointers
  - `template_summary.row_scalar_a` through `row_scalar_d` from `+0x98/+0x9c/+0xa0/+0xa4`
  - `follow_state_summary` with the active follow sample index, progress, vertical offset, orientation-ish vector, and output pose
- `player_update` now also exposes the cached pair-cell pointers at `player + 0x98/+0x9c` as `cached_track_pair_cell_a` and `cached_track_pair_cell_b`
- `player_update` now also emits the statically recovered attachment-exit latch fields:
  - `movement_flag_selector`
  - `movement_flags`
  - `previous_movement_flags`
  - `movement_rate_scalar`
  - `movement_mode_selector`
  - `attachment_exit_pending`
  - `attachment_exit_anchor_z`
  - `post_follow_value_a`
  - `post_follow_value_b`
  - `attachment_exit_progress`
  - `attachment_exit_progress_step`
  - `attachment_exit_gate_a`
  - `attachment_exit_gate_b`
- `movement_flags_update` now samples the `movement_flag_selector -> movement_flags` switch directly at `0x43a1a0`
- `track_pair_payload` now records the scalar written into the cached pair-cell payload slots at `0x43d3d0`
- `player_update`, `movement_flags_update`, and `track_pair_payload` now also expose the typed movement integrator and row-event state:
  - `level_mode`
  - `level_mode_arg`
  - `track_center_x`
  - `track_state_latch`
  - `replay_active`
  - `replay_track_index`
  - `movement_progress`
  - `track_z_offset`
  - `track_z_anchor`
  - `row_event_id`
  - `row_event_state`
  - `row_event_timer`
  - `row_event_data_a`
  - `row_event_data_b`
- `attachment_end` is now emitted on return and should carry both:
  - `before_follow_state_summary`, `before_template_summary`, `before_follow_sample_index`, `before_follow_progress`
  - post-call `attachment_exit_pending`, `attachment_exit_anchor_z`, `attachment_exit_progress`, `attachment_exit_progress_step`, and the follow-effect gates
- if you are reusing an older local script copy on Windows, replace it first; the March 8 long capture proved the older copy misses `player_update` entirely and misreports `attachment_end`
- the stable March 24 Windows death pack now disables these crash-prone probes by default:
  - `death_handoff_cutscene`
  - `death_handoff_update`
  - `respawn_life_decrement`
  - `respawn_complete_subgame_branch`
- the stable reduced death-side probes are:
  - `death_select_state_set` at `0x441fa0`
  - `update_subgoldy_resurrect_enter` at `0x441fd0`
- the current checked-in `failure_handoff` profile stays on that stable reduced pack:
  - `death_select_state_set` at `0x441fa0`
  - `update_subgoldy_resurrect_enter` at `0x441fd0`
- `snailmail-trace-20260324-174006-708.ndjson` did capture one useful extra fact before crashing:
  - `respawn_life_decrement` fired once at `respawn_progress = 1.008` with `lives_before = 3`, `final_loss = 0`, and `game_fade = 74`
  - because that run died immediately afterward, `0x44205b` and `0x442096` are now treated as crash-prone and are no longer armed by default
- `snailmail-trace-20260324-174348-6980.ndjson` confirmed that the restored reduced `failure_handoff` profile is stable again and does land the missing final-loss selector:
  - `death_select_final_loss` fired with `final_loss = 1`, `lives = 0`, `app.owner = 0xb`, and `app.saved = 0xb`
  - the same run also re-saw earlier spare-life respawn selectors while the player burned lives down, so the reduced pack is safe for repeated life-burn repros
- the next three reduced-pack traces closed the remaining section-1 asks:
  - `snailmail-trace-20260324-174803-7452.ndjson`
    - Postal slug death and Postal fall death both landed `death_select_respawn`
    - the fall lane is distinguishable by negative `world_y` and later `world_z`, but the selector outcome is the same
  - `snailmail-trace-20260324-174918-6984.ndjson`
    - Time Trial hazard death and Time Trial fall death both landed `death_select_final_loss`
  - `snailmail-trace-20260324-175010-6056.ndjson`
    - Challenge fall death also landed `death_select_final_loss`
    - this closes the required non-Postal death-family evidence, even though the current reduced profile does not trace the later high-score-entry UI
- the current checked-in default is now the section-3 `attachment_exit` profile:
  - `movement_flags_update`
  - `player_update`
  - `attachment_begin`
  - `attachment_update`
  - `attachment_end`
- that profile is intended for `ARCADE007` / `HalfPipe` re-entry work and keeps death, completion, pickup, hazard, salt, and slug hooks off
- the newer script also emits focused handoff events with app-side owner state from `data_4df904`:
  - `completion_handoff_arm`
  - `completion_screen_init`
  - `complete_subgame_call`
  - `death_handoff_cutscene`
  - `death_handoff_update`
  - `death_select_respawn`
  - `death_select_final_loss`
  - `respawn_enter`
  - `respawn_life_decrement`
  - `respawn_complete_subgame_branch`

Expected event names in the NDJSON:

- `module_ready`
- `hooks_installed`
- `level_start`
- `path_lookup`
- `movement_flags_update`
- `player_update`
- `completion_handoff_arm`
- `completion_screen_init`
- `complete_subgame_call`
- `death_handoff_cutscene`
- `death_handoff_update`
- `death_select_respawn`
- `death_select_final_loss`
- `respawn_enter`
- `respawn_life_decrement`
- `respawn_complete_subgame_branch`
- `track_pair_payload`
- `attachment_begin`
- `attachment_update`
- `attachment_end`
- `floor_sample`
- `garbage_spawn`
- `health_pickup`
- `jetpack_pickup`
- `ring_effect`
- `salt_spawn`
- `salt_update`
- `salt_deactivate`
- `slug_spawn`

Latest stable death-side result on 2026-03-24:

- `snailmail-trace-20260324-165745-4468.ndjson` loaded the reduced pack without crashing
- it captured a spare-life Postal death with `death_select_respawn` followed by repeated `respawn_enter`
- the same trace then rolled into a fresh `level_start` and `attachment_begin`, which currently looks like an ordinary respawn rebuild path

Latest stable completion-side result on 2026-03-24:

- `snailmail-trace-20260324-172644-2560.ndjson` loaded the `completion_handoff` profile without crashing
- it captured the first `completion_handoff_arm`, one `completion_screen_init`, and the first `complete_subgame_call`
- `completion_handoff_arm` first flipped `voice_gate` from `false` at `timer = 2.000` to `true` at `timer = 2.017` on the same live player-owned handoff state
- the current `completion_screen_init` hook is trustworthy as a call confirmation but still has a bad field decode, so do not trust its derived `player` or `game` fields yet
- `snailmail-trace-20260324-173402-14228.ndjson` extended the same lane and showed the handoff timer flattening at `4.983` while the same player-owned handoff state and `app.owner = 0xb` remained live until `complete_subgame`
- local recovery of the same `update_subgoldy` block closes the reason for that plateau:
  - `player + 0x444` is the completion timer
  - `player + 0x448` is the step
  - `player + 0x44e` is the one-shot `2.0s` voice latch
  - once the completion logic forces the timer to `5.1f`, it immediately subtracts one step back to `~4.983` before checking the `> 5.0` branch
- section 2 is now considered closed

Latest stable attachment-side result on 2026-03-24:

- `snailmail-trace-20260324-175650-8440.ndjson` loaded the `attachment_exit` profile without crashing
- it captured `21` real `attachment_begin` events, `2976` `attachment_update` events, and `4` real `attachment_end` events on `ARCADE007`
- the trace did not hit `attachment_probe`, so the swept-entry helper itself is still not directly confirmed on this pass
- the four detach events split into two runtime families:
  - two retired immediately with no sustained `attachment_exit_pending` window
  - two kept `attachment_exit_pending = 1` for about `2.93` to `2.95` seconds while the player stayed unattached on tile `0x00`
- in those longer windows, `attachment_exit_progress` climbed from about `0.017` / `0.133` to about `2.95` / `2.933`, and both follow-effect gates flipped on around `0.67`
- neither `post_follow_value_a` nor `post_follow_value_b` went nonzero anywhere in the trace
- the first reattached `player_update` after each long skim window showed `attachment_exit_pending = 0` and `attachment_exit_progress = 0`, so the next successful `attachment_begin` is now runtime-confirmed as one generic non-jetpack retirement path
## How To Run

Run the spawn flow from `artifacts\bin` on the Windows machine so the game starts with the expected working directory.

Spawn the gameplay binary under Frida:

```powershell
cd .\artifacts\bin
frida -f .\SnailMail_unwrapped.exe -l ..\..\tools\frida\snailmail-runtime-trace.js
```

For the path oracle instead:

```powershell
cd .\artifacts\bin
frida -f .\SnailMail_unwrapped.exe -l ..\..\tools\frida\snailmail-path-oracle.js
```

If spawn still exits immediately, start the game normally from `artifacts\bin` and attach from the repo root instead:

```powershell
cd C:\path\to\repo
frida -n SnailMail_unwrapped.exe -l .\tools\frida\snailmail-runtime-trace.js
```

The script now creates `C:\share\snail\frida\` itself and writes NDJSON there with a generated filename like `snailmail-trace-20260308-153000-1234.ndjson`.
Keep the first console line from each run because it prints the exact file path that was opened.

Before running any new capture, sync the latest repo copy of [tools/frida/snailmail-runtime-trace.js](../../tools/frida/snailmail-runtime-trace.js) onto the Windows machine. The most recent local fixes corrected:

- `update_subgoldy`
- `end_track_attachment_follow_state`
- `get_track_grid_cell_at_world_position`
- the cell-layout split between gameplay grid cells and row-cell attachment records

Without that update, the capture will still be useful for probes, pickups, and hazard spawns, but it will under-report player state and attachment exits.

Current checked-in default:

- `TRACE_PROFILE = "completion_handoff"` in [tools/frida/snailmail-runtime-trace.js](../../tools/frida/snailmail-runtime-trace.js)
- that profile keeps only:
  - `level_start`
  - `completion_handoff_arm`
  - `completion_screen_init`
  - `complete_subgame_call`
- verify the trace by checking `hooks_installed.profile = "completion_handoff"` in the second NDJSON row

For the path oracle, the newest script focuses on:

- installed `P/p` row ownership after `populate_runtime_track_cells_from_segments`
- live bank-root choice (`game + 0xff2914` vs `game + 0xff29bc`)
- runtime path-family identity by installed owner, template kind, and path-name index
- projection, entry, follow, exit, and warp-transform events for attachment families

## Capture Matrix

Run these captures in roughly this order.

### 1. Path Attachment Capture

Purpose:

- prove the full chain from `Path=<name>` lookup to `attachment_probe` to `attachment_begin`
- capture a full attachment lifecycle with sampled `player_update`, `attachment_update`, and `attachment_end`

Best target:

- `LEVELS/ARCADE028.TXT`

Why:

- strongest current path-heavy arcade target
- many repeated public path families

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade028-path.ndjson` before handing it back

What to do in-game:

1. Start `Twisterific`.
2. Play until at least one obvious path-follow section is entered.
3. Quit once `attachment_begin` has clearly fired.

Success criteria:

- at least one `path_lookup`
- at least one `player_update`
- at least one `attachment_probe`
- at least one `attachment_begin`
- at least one `attachment_update`
- at least one `attachment_end`
- at least one `movement_flags_update`
- at least one `track_pair_payload`
- at least one attachment event carrying non-null `template_summary.sample_count`
- at least one `player_update` or `floor_sample` carrying non-null `sampled_floor_height`

### 2. Scalar Salt Capture

Purpose:

- confirm salt spawning when `Salt:` is high but authored `&` rows are absent

Best target:

- `LEVELS/ARCADE039.TXT`

Why:

- current top scalar-salt level
- static corpus has `Salt:100` and `0` explicit `&` rows

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade039-salt.ndjson` before handing it back

What to do in-game:

1. Start `Sodium Squared`.
2. Play long enough for ambient hazard spawning to occur.
3. Quit after multiple `salt_spawn` or after a few minutes if nothing fires.

Success criteria:

- one `level_start` showing the normalized salt scalar
- at least one `salt_spawn` or a clean negative result after a reasonable play window

### 3. Authored Salt And Ring Capture

Purpose:

- separate authored `&` behavior from scalar salt
- observe ring effect rows, pickups, and ordinary player updates in a controlled tutorial flow

Best target:

- `LEVELS/TUTORIAL.TXT`

Why:

- strongest combined authored-salt and ring tutorial target
- static clue: `Salt:0`, so any `salt_spawn` should correlate with authored rows rather than the scalar fallback

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `tutorial-salt-ring.ndjson` before handing it back

Success criteria:

- `level_start`
- ring-heavy progression in a low-noise level
- any `salt_spawn` behavior with `Salt:0`
- at least one of `ring_effect`, `health_pickup`, or `jetpack_pickup`

### 4. JetPack-Off Capture

Purpose:

- observe live response on authored `JetPack=Off` rows

Best target:

- `LEVELS/ARCADE025.TXT`

Why:

- currently the cleanest level for explicit `JetPack=Off`

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade025-jetpackoff.ndjson` before handing it back

Success criteria:

- `level_start`
- clear passage through the `JetPackOff` segment
- useful correlation between authored rows and observed movement or timer behavior

### 5. No-Fall Capture

Purpose:

- observe how trampoline-heavy `NoFall` content behaves in live play

Best target:

- `LEVELS/ARCADE047.TXT`

Why:

- strongest repeated `NoFall` exposure in the current corpus

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade047-nofall.ndjson` before handing it back

### 6. Slug Capture

Purpose:

- confirm whether dense `M` rows really drive slug spawns in the expected way

Best target:

- `LEVELS/ARCADE029.TXT`

Why:

- best current slug-like level from the local planner

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade029-slugs.ndjson` before handing it back

## What To Hand Back

After each run, keep:

- the raw NDJSON file
- the in-game level name
- a short human note with what you actually did
- whether the run ended normally, crashed, or got stuck

Good note format:

```text
arcade028-path.ndjson
Level: Twisterific
Actions: started level, stayed center lane, entered first visible path section, quit after first attachment follow
Notes: saw one obvious path transition near TwisterA/TwisterB segment
```

## How To Summarize After Copying Back

Once the NDJSON files are back in this repo on macOS or Linux, summarize them from the repo root:

```bash
uv run snail trace summary /path/to/arcade028-path.ndjson
uv run snail trace summary /path/to/arcade039-salt.ndjson
uv run snail trace summary /path/to/tutorial-salt-ring.ndjson
uv run snail trace plan --limit 5
```

## Known Static Context

The Windows agent should assume all of these are already established statically:

- `Path=<name>` resolves through a `51`-entry hardcoded table in RWG.
- Most public path names now map to concrete constructor families in the world-init block.
- `WARP` is the only public path slot still missing from that aligned constructor table.
- `P/p` cells install runtime attachment pointers on neighboring cells.
- the main player update can enter a dedicated attachment-follow state from those attachments.
- `Salt:` and authored `&` are not the same system.
- `JetPack=Off` seeds runtime `0x8000`, but `0x8000` is later reused by edge-variant logic too.
- `NoFall` is live runtime state and already affects glyph normalization.

## Open Questions To Prioritize

- Which named `Path=` families actually produce `attachment_begin` events in live play?
- What does one full attachment-follow lifecycle look like in sampled `player_update`, `attachment_update`, and `attachment_end` events?
- Do high `Salt:` levels spawn salt hazards without any authored `&` rows?
- What trajectories do live `salt_update` samples show before `salt_deactivate`?
- Which ring-effect kinds and pickup helpers correspond to the authored rows we already parse statically?
- Does `Salt:0` plus authored `&` still produce `salt_spawn` in the expected rows?
- What concrete gameplay effect shows up on authored `JetPack=Off` rows?
- How often do `M`-heavy levels actually call `spawn_slug_runtime_entity`?

## If Something Goes Wrong

- If no `module_ready` or `hooks_installed` event appears, you are probably attached to the wrong process.
- If the game launches but no events appear, attach to `SnailMail_unwrapped.exe` directly instead of the wrapper. Falling back to `SnailMail.RWG` is still valid if you have not generated the unwrapped image yet.
- If output is too noisy, stop the run and switch to a shorter target level instead of letting one huge trace grow.
- If the game crashes immediately under Frida, keep the failing NDJSON or console output anyway. Even a failed launch is useful if it happens consistently.
