# Windows CDB Session 2026-03-15

This note tracks the first Windows-native live debugger session against `SnailMail_unwrapped.exe` using external `cdb` plus the local `bn` Binary Ninja bridge.

Binary Ninja stays useful for static cross-checking during the session, but its own DbgEng debug-server path currently crashes on this machine, so the stable runtime lane is `cdb -server` plus `cdb -remote`.

## Setup

- gameplay target: `C:\dev\snail\artifacts\bin\SnailMail_unwrapped.exe`
- Binary Ninja target: `C:/share/snail/SnailMail_unwrapped.exe.bndb`
- server command:

```powershell
cdb.exe -server tcp:port=5005,password=secret -logo C:\dev\snail\artifacts\snailmail-windbg.log -pn SnailMail_unwrapped.exe -noio
```

- client command:

```powershell
cdb.exe -remote tcp:server=127.0.0.1,port=5005,password=secret -bonc
```

- runtime note:
  - the process is 32-bit under WOW64, so the client should switch to x86 view after attach with `.effmach x86`

## Baseline Findings

- the `bn` bridge is healthy and sees one active target: `SnailMail_unwrapped.exe.bndb`
- the `cdb` remote client connects cleanly to the long-lived server on `127.0.0.1:5005`
- the first stop after attach is the expected loader breakpoint at `ntdll!DbgBreakPoint`
- the module loaded at base `0x00400000` during this session
- after switching to x86 mode and issuing `g`, the process resumes normally under the remote client

## Current Focus

Capture one full live attachment lifecycle in the original game:

1. `try_enter_track_attachment_from_swept_motion`
2. `begin_track_attachment_follow_state`
3. `update_track_attachment_follow_state`
4. the exit helper currently named `begin_post_follow_carryover`

This is the highest-value next runtime target because the rewrite is still blocked on:

- curve-accurate attachment-follow
- exact attachment entry and exit semantics
- the remaining `HALFPIPE` and `WARP` gaps called out in the existing RE notes

## Static Anchor Points

- `0x42c770` `try_enter_track_attachment_from_swept_motion`
  - current prototype: `float __thiscall(void* arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7, void* arg8)`
- `0x420c40` `begin_track_attachment_follow_state`
  - current prototype: `void* __thiscall(char* arg1, void* arg2, void* arg3, int32_t arg4)`
- `0x420cb0` `update_track_attachment_follow_state`
  - current prototype: `void __thiscall(char* arg1, float arg2, float* arg3, void* arg4)`
- `0x43af60` `begin_post_follow_carryover`
  - current prototype: `int32_t __fastcall(void* arg1)`
  - behavior still matches the older attachment-exit notes better than the current name

## Confirmed Structure / Behavior Cross-Checks

`begin_track_attachment_follow_state` still matches the recovered follow-state layout:

- `+0x00`: active flag
- `+0x04`: active attachment-template pointer
- `+0x08`: owner attachment-runtime record
- `+0x0c`: current segment index
- `+0x10`: progress within the current sampled segment
- `+0x14`: local height above the attachment surface
- `+0x2c`: interpolated output position
- `+0x38`: player pointer

Live-static cross-check from the current Binary Ninja decompile:

- sets active flag to `1`
- stores runtime cell `+0x38` as the active attachment pointer
- stores the owner runtime record
- zeroes segment index
- seeds progress from `world_z - cell_anchor_z`
- seeds local height from `world_y - 0.49`
- stores the player pointer
- copies a row-derived scalar into attachment `+0x98`

`0x43af60` is worth treating as the current attachment-exit helper despite the present Binja name:

- if `player + 0x384` is active, it copies `*(player + 0x388) + 0x98` into `player + 0x430`
- copies `player + 0x3a0` into `player + 0x42c`
- clears `player + 0x384`
- sets `player + 0x41d = 1`
- seeds `player + 0x424` from current player `z`
- zeroes `player + 0x434`, `player + 0x44c`, and `player + 0x44d`

That is materially consistent with the older `end_track_attachment_follow_state` description in `docs/re/attachment-follow.md`.

## Next Live Repro

The next useful user-driven repro is:

- load a path-heavy level
- stay roughly centered
- deliberately enter the first visible path-follow section
- ideally choose a level with an obvious `HALFPIPE`, `WARP`, or loop-like attachment corridor

The immediate goal is not a long free-play run. One clean attachment begin and one clean exit is enough to inspect the live state and compare it against the current static model.

## Session Findings

### ARCADE007 (`To Infinity!`)

Static level context:

- level file: `artifacts/extracted/SnailMail.dat/LEVELS/ARCADE007.TXT`
- in-game name: `To Infinity!`
- segment list includes `HalfPipe.txt`
- `HalfPipe.txt` carries a full `Path=HalfPipe` row of `PPPPPPPP`

Live debugger result from the first gameplay pass:

- the `begin_track_attachment_follow_state` breakpoint at `0x420c40` fired during level 7 play
- captured entry pointers:
  - `follow = 0x0d339120`
  - `cell = 0x0d33dcd0`
  - `pos = 0x0d338e04`
  - `player = 0x0d338d9c`

Immediate interpretation:

- at least one shipped `HalfPipe` segment in `ARCADE007` does produce a real live attachment begin
- this closes one practical open question from the older notes: `HALFPIPE` is not just parsed at startup, it can drive a real `attachment_begin` transition in gameplay

Second gameplay pass through the same path family captured one live `update_track_attachment_follow_state` sample:

- `follow = 0x0d339120`
- `seg = 0`
- `prog = 0`
- `height = 0`
- `player = 0x0d338d9c`
- `tmpl = 0x0df72e8c`
- `owner = 0x0d33dcd0`

Raw follow-state dump at the first sampled update:

```text
0d339120  00000001 0df72e8c 0d33dcd0 00000000
0d339130  00000000 00000000 00000000 00000000
0d339140  00000000 3f800000 00000000 00000000
0d339150  41020abd 40800000 0d338d9c 00000000
0d339160  00000000 3ecaa9ba 3caaaaab 00000000
0d339170  00000000 00000000
```

Interpretation:

- the active flag at `follow + 0x00` is `1`, matching the recovered layout
- `follow + 0x04` still points at a stable live template object
- `follow + 0x08` still points at the owner runtime cell captured at entry
- `follow + 0x0c`, `+0x10`, and `+0x14` were all still zero at this earliest sampled follow update
- `follow + 0x38` still points at the same player object captured at begin

The same run then produced three more `attachment_begin` hits with the same follow and player pointers but different cell pointers:

- `cell = 0x0d34c184`
- `cell = 0x0d352250`
- `cell = 0x0d358370`

Conservative read:

- the first `HalfPipe` pass in `ARCADE007` is enough to enter real attachment-follow and then continue encountering additional attachment-entry cells or sub-sections on the same live player object
- the first confirmed `HALFPIPE` route is therefore a good Windows repro lane and there is no need to switch levels yet

Later in the same level-7 session, after the player fell, lost one life, restarted, and eventually finished the level back to the galaxy screen, the attachment-exit helper at `0x43af60` also fired:

- `player = 0x0d338d9c`
- `active = 0`
- `exit_a = 0`
- `exit_b = 0`

Important caveat:

- the current `cdb` breakpoint was placed at the helper entry, so this snapshot is best interpreted as a proof that the helper really does run on the live path out of attachment-follow
- it is not yet the best post-write capture of `attachment_exit_anchor_z`, `attachment_exit_progress`, `attachment_exit_progress_step`, `post_follow_value_a`, and `post_follow_value_b`

Practical conclusion:

- the fall or restart path in `ARCADE007` is enough to reach the confirmed attachment-exit helper
- the next runtime improvement should be a two-stage breakpoint pair that captures both helper entry and the post-write state at the helper return site

After fixing the `cdb` instrumentation to stop after the begin helper had already populated the follow-state struct, we captured a corrected initialized begin snapshot at `0x420c7a`:

- `follow = 0x0d339120`
- `active = 1`
- `tmpl = 0x0df70d14`
- `owner = 0x0d34c184`
- `seg = 0`
- `prog = 0x3d134000`
- `height = 0`
- `player = 0x0d338d9c`
- `cell = 0x0d34c184`
- `pos = 0x0d338e04`

Raw struct dump at the corrected begin stop:

```text
0d339120  00000001 0df70d14 0d34c184 00000000
0d339130  3d134000 00000000 00000000 00000000
0d339140  00000000 3f800000 00000000 befa4000
0d339150  3ef9eb70 41f71416 0d338d9c 00000000
0d339160  00000000 3f5aaa5e 3caaaaab 00000000
0d339170  00000000 00000000
```

Interpretation:

- this corrected stop matches the recovered static layout materially better than the earlier entry-edge dump
- `follow + 0x00 = 1` confirms the active flag write
- `follow + 0x04` now points at a stable initialized template object for this specific live `HalfPipe` entry
- `follow + 0x08` matches the active owner attachment-runtime cell
- `follow + 0x0c = 0` still shows the entry begins on segment index `0`
- `follow + 0x10 = 0x3d134000` is a small positive entry progress seed, consistent with `world_z - cell_anchor_z`
- `follow + 0x14 = 0` means this particular entry hit at the reference attachment height or close enough to round to zero in this snapshot
- `follow + 0x38` still points at the same live player object seen in prior hits

This is the first high-confidence Windows `cdb` snapshot of a fully initialized attachment-begin state, not just the entry edge or a later sampled follow tick.

Immediately after resuming from that corrected begin stop, the improved two-stage exit pair also fired on the same live player object:

- `attachment_end_enter`: `player=0x0d338d9c active=1 tmpl=0x0df70d14 owner=0x0d34c184 seg=2`
- `attachment_end_post`: `player=0x0d338d9c active=0 anchor=0x42bad90b prog=0 step=0x3c888889 post_a=0 post_b=0`

Useful float conversions from the post-exit snapshot:

- entry `prog = 0x3d134000` -> `0.03594971f`
- exit `anchor = 0x42bad90b` -> `93.42391f`
- exit `step = 0x3c888889` -> `0.01666667f`

Raw post-exit dump around `player + 0x420`:

```text
0d3391bc  00000000 42bad90b 00000000 00000000
0d3391cc  00000000 00000000 3c888889 0cf0909c
```

Static cross-check against `0x43af60` / `begin_post_follow_carryover`:

- `player + 0x388` is the active attachment-template pointer, not the follow-state pointer
- `player + 0x38c` is the owner attachment-runtime cell
- `player + 0x390` is a small integer state field and this live exit hit captured `2`
- `player + 0x424` latches current player `z` as `attachment_exit_anchor_z`
- `player + 0x42c` and `player + 0x430` are the post-follow carryover values and were both zero in this exit
- `player + 0x434` is zeroed on exit
- `player + 0x438` carries the exit progress step and this live hit matched `1/60`
- `player + 0x44c` and `player + 0x44d` are byte-sized gates cleared by the helper; earlier dword-sized `cdb` logging overstated their values

Practical conclusion:

- this Windows-native session now covers a full attachment lifecycle on a shipped `HalfPipe` lane: begin, at least one update, and confirmed exit
- the entry seed and exit anchor are both live nonzero values, so the remaining follow-up work is no longer "does the path run?" but "how do progress and carryover evolve across mid-follow samples?"

Static follow-up on the post-exit state machine:

- `update_subgoldy` is the first confirmed consumer of the exit-side fields seeded by `0x43af60`
- at `0x43ce8a`..`0x43ce96`, it accumulates `player + 0x438` into `player + 0x434` every tick
- the first live exit step value, `0.01666667f`, is exactly `1/60`, so `attachment_exit_progress` appears to advance in frame-sized increments
- at `0x43ce9c`, it compares the accumulated progress against `0.7f`
- if that threshold is crossed and `player + 0x44c` is still clear, it plays a voice event and sets `player + 0x44c = 1`
- later in the same block, if `player + 0x44d` is still clear and the player `z` has crossed the deeper threshold checked at `0x43cef7`, it plays a second voice event and sets `player + 0x44d = 1`

That narrows the next runtime target considerably: the next useful live probe is no longer the raw exit helper, but the `update_subgoldy` path around `0x43ce8a` and the first transition where `attachment_exit_progress` crosses the `0.7f` gate.

Later in the same Windows session, a replay armed with the post-exit gate probes captured a cleaner mid-follow sample and the first visible post-exit progress gate:

- first sampled `attachment_update`:
  - `follow = 0x0d339120`
  - `seg = 0`
  - `prog = 0`
  - `height = 0xbefae148` -> `-0.49f`
  - `tmpl = 0x0df72e8c`
  - `owner = 0x0d33dcd0`
  - `player = 0x0d338d9c`
- `attachment_end_enter` on the same pass:
  - `player = 0x0d338d9c`
  - `active = 0`
  - `tmpl = 0x0df72e8c`
  - `owner = 0x0d33dcd0`
  - `seg = 0x1b`
- `attachment_end_post` on the same pass:
  - `anchor = 0x425c6801` -> `55.10157f`
  - `prog = 0`
  - `step = 0x3c888889` -> `0.01666667f`
  - `gate_a = 0`
  - `gate_b = 0`
  - `post_a = 0`
  - `post_b = 0`

The first stop inside the post-exit threshold block landed at `0x43cea9`:

- `progress = 0x3f377777` -> `0.7166666f`
- `step = 0x3c888889` -> `1/60`
- `gate_a = 1`
- `gate_b = 0`
- `anchor = 55.10157f`

Interpretation:

- the mid-follow `height = -0.49f` matches the static entry formula and shows the player is already riding the attachment floor offset rather than hovering at the earlier zero-height sample
- on this replay, `begin_post_follow_carryover` was entered with `active = 0`, so the active follow flag can already be clear by the time the helper runs
- the helper still re-seeds the exit interpolation state even when entered with `active = 0`
- by the time execution first stopped in the `0x43cea9` gate block, `gate_a` was already `1`, so that breakpoint catches the first sampled tick in the `>= 0.7f` path, not necessarily the exact write that flips `player + 0x44c`
- `0.7166666f` is effectively `43/60`, which is consistent with the helper's `1/60` exit step and places the first observed gate just after forty-two ticks of post-exit progress accumulation

One later pass in the same session also produced a deeper post-exit sample:

- `attachment_end_enter`: `player=0x0d338d9c active=0 tmpl=0x0df7255c owner=0x0d37dc3c seg=0x1b`
- `attachment_end_post`: `anchor=0x440dc5e2` -> `567.0919f`, `prog=0`, `step=0x3c888889`, `gate_a=0`, `gate_b=0`
- `attachment_exit_gate_b`: `progress=0x3f2aaaab` -> `0.6666667f`, `z=0xc0e5f0e6` -> `-7.185657f`, `anchor=567.0919f`

Conservative read:

- `gate_b` can fire on some attachment-exit paths, but it is not a mandatory part of every clean level finish
- the first captured `gate_b` sample happened while both byte gates still read zero in the stop payload, so this probe is landing at the start of the deeper threshold block rather than after all gate writes complete

Finally, a replay armed with exact `update_subgoldy` callsite probes for all four direct callers of `begin_post_follow_carryover`:

- `0x43b9b8`
- `0x43c008`
- `0x43c34b`
- `0x43c507`

finished cleanly without hitting any of those four sites.

Practical implication:

- at least one clean-finish level-complete path is bypassing the `update_subgoldy -> begin_post_follow_carryover` carryover-arm lane entirely
- the helper and the post-exit progress gates are therefore real runtime behavior, but they are not the only way attachment-follow is retired during ordinary play

## `cdb` Breakpoint Pack Pivot: Completion And Death Handoff

Timestamp: `2026-03-15T11:26:55.9277158+04:00`

After the attachment-follow pass, the live `cdb` session was pivoted to the next higher-value questions:

- first write to `completion_handoff_active`
- exact `update_cutscene` callsite that invokes `initialize_completion_screen`
- exact `update_subgoldy` callsite that invokes `complete_subgame`
- exact death selector branch that chooses respawn versus final loss
- visible-life decrement writer

The armed live breakpoint set is:

- `0x43a9c0` `initialize_subgoldy`
  - log only
  - refreshes the stable live `player` pointer for the session
- `0x446b04` `update_cutscene -> initialize_subgoldy_death`
  - log only
  - captures death-handoff entry with current mode, lives, `world_y`, and gate bytes
- `0x446e51` `initialize_subgoldy_death -> initialize_subgoldy_resurrect(player, 1)`
  - stop
  - labeled `death_select_final_loss`
- `0x446e59` `initialize_subgoldy_death -> initialize_subgoldy_resurrect(player, 0)`
  - stop
  - labeled `death_select_respawn`
- `0x441fa0` `initialize_subgoldy_resurrect`
  - log only
  - confirms the branch argument as observed by the callee
- `0x446bfe` `update_cutscene -> initialize_completion_screen`
  - stop
  - captures the first cutscene-side completion-screen handoff with current cutscene state and completion-handoff fields
- `0x43c981`
- `0x43c9af`
- `0x43c9c8`
  - stop
  - the three direct `update_subgoldy -> complete_subgame` callsites

Two hardware write watches were also armed against the currently stable live player object `0x0d338d9c`:

- `player + 0x4340 = 0x0d33d0dc`
  - `visible_life_stock`
  - stop on the exact writer
- `player + 0x440 = 0x0d3391dc`
  - `completion_handoff_active`
  - stop on the first arm or clear site

Observed immediately after arming:

- `initialize_subgoldy` fired with `player=0x0d338d9c mode=0 lives=2 control_source=0x0cf0909c`
- the player object remained stable across the current session, so absolute watchpoints are acceptable for this run
- one existing completion transition hit `0x43c9af`, showing `complete_subgame_call_1` with:
  - `game=0x0cf7d638`
  - `player=0x0d338d9c`
  - `mode=0`
  - `completion_handoff_active=1`
  - `completion_handoff_timer=0x40a33333`
  - `completion_handoff_voice_gate=1`

Planned repro order for this pivot:

1. normal level completion from galaxy start
2. hazard death with spare lives in Postal mode
3. hazard death with zero spare lives in Postal mode
4. floor-gap fall for comparison

Practical read:

- the anchor-writer question from the earlier wish list is now lower priority because the old `player + 0x1840` / `+0x1888` reads are already better explained as `snail_hotspots_world` outputs maintained by `update_snail_skin`
- the current best `cdb` return is now precise handoff timing and selector ownership rather than more generic attachment tracing

The first stop after arming the new watch set happened immediately on level selection from the galaxy screen and clarified the startup write path for `visible_life_stock`.

Live `cdb` stop:

- watchpoint: `player + 0x4340 = 0x0d33d0dc`
- printed as:
  - `[visible_life_stock_write] eip=00435f6c lives=3 mode=0`

Important caveat:

- the processor watch fired after the actual write completed
- the instruction at the stop site, `0x435f6c`, is the following `lea`
- the real writer is the immediately preceding instruction at `0x435f66`

Recovered block in `populate_runtime_track_cells_from_segments`:

- `0x435f41`: `*(arg1 + 0xff25dc) = 0`
- `0x435f49`: `if (eax_9 == 3)`
- `0x435f51`: `*(arg1 + 0x1270fc8) = 1`
- `0x435f5b`: `*(arg1 + 0x3bba48) = 0`
- `0x435f61`: `sub_4403a0(arg1 + 0x3bb764)`
- `0x435f66`: `*(arg1 + 0x3bfaa4) = 3`
- `0x435f72`: `cRTime::Zero()` / `zero_timer_counters()`

Practical conclusion:

- `visible_life_stock` is definitely reseeded to `3` during course build in `populate_runtime_track_cells_from_segments`
- this is the startup or rebuild seed, not the gameplay decrement
- the current `cdb` watch was tightened after this stop to auto-continue when the new value is `3`, so subsequent life-stock stops should represent non-seed writes

The same cleanup pass also tightened the completion watch:

- `player + 0x440` now auto-continues when the new value is `0`
- it should stop only on the first arm of `completion_handoff_active`

That filtered watch immediately paid off on the next clean level finish.

First completion-handoff arm:

- watchpoint: `player + 0x440 = 0x0d3391dc`
- printed as:
  - `[completion_handoff_active_arm] eip=0043c7b7 active=1 timer=0 step=3c888889 voice_gate=0`

As with the earlier life-stock watch, the processor stop landed after the write completed. The actual write sequence in `update_subgoldy` is the block immediately before `0x43c7b7`:

- `0x43c797`: `*(ebp + 0x42e8) = 5`
- `0x43c79d`: `play_sound_effect(0)`
- `0x43c7a2`: `*(ebp + 0x41c) = 0`
- `0x43c7b0`: `*(ebp + 0x440) = 1`

Live state at the arm stop:

- `player = 0x0d338d9c`
- `game = 0x0cf7d638`
- `mode = 0`
- `completion_handoff_active = 1`
- `completion_handoff_timer = 0`
- `completion_handoff_timer_step = 0x3c888889` -> `1/60`
- `completion_handoff_voice_gate = 0`
- `player + 0x42e8 = 5`

Useful nearby values:

- `game + 0x58 = 0x2f1` -> `753`
- the float constant compared in the immediately following gate is `0x40200000` -> `2.5f`
- `player.z = *(player + 0x70) = 0x443c40b6` -> about `753.01f`

Practical interpretation:

- this is the first frame where the completion handoff becomes active
- the handoff is armed inside `update_subgoldy`, not only later in frontend code
- the arm path also clears `attachment_exit_pending`-adjacent state at `player + 0x41c`, seeds the one-shot presentation field at `player + 0x42e8`, and resets the timer lane to `0` with `1/60` step

The same replay then hit the cutscene-side completion-screen initializer.

Live stop at `0x446bfe` inside `update_cutscene`:

- `cutscene = 0x0d33d078`
- `cutscene.player = 0x0d338d9c`
- `cutscene.state = 6`
- `initialize_completion_screen(...)` is called from that state-`6` leg

Recovered pre-call block:

- `0x446b88`: `arg1[3] = 6`
- `0x446b8f`: `arg1[0x14] = 0`
- `0x446b96`: `arg1[0x15] = 0x3c088889`
- `0x446bb6`: `arg1[0x16].b = 1`
- `0x446bf7`: `var_100 = *(arg1[1] + 0x4338)`
- `0x446bfe`: `initialize_completion_screen(data_4df904 + 0x12e6df0, var_100, var_fc_24)`

Live values at that call:

- `player + 0x4338 = 0x0000000f`
- `completion_handoff_active = 1`
- `completion_handoff_timer = 0x3c888889` -> `1/60`
- `completion_handoff_timer_step = 0x3c888889` -> `1/60`
- packed gate dword at `player + 0x44c` read `0x00000101`
  - `attachment_exit_gate_a = 1`
  - `attachment_exit_gate_b = 1`
  - `completion_handoff_voice_gate = 0`

Practical conclusion:

- the completion screen is initialized almost immediately after the handoff arm, not only at the later `5.0s` frontend exit
- in this build, the observed call site is `update_cutscene` state `6`
- the first `initialize_completion_screen` call happened with the completion timer at exactly one tick (`1/60`)

At the end of this capture, the debugger remained armed for the later `update_subgoldy -> complete_subgame` callsites. That last transition appears to require advancing beyond the completion screen rather than occurring at the instant the screen is created.

Advancing past the completion screen in the same session then hit the final completion handoff:

- breakpoint label: `complete_subgame_call_1`
- stop site: `0x43c9af` inside `update_subgoldy`
- live print:
  - `[complete_subgame_call_1] game=0x0cf7d638 player=0x0d338d9c mode=0 active=1 timer=40a2aaaa voice_gate=1`

Useful immediate context:

- `esi = 0`, and this callsite is the `push esi; call complete_subgame` leg
- the call is therefore `complete_subgame(game, 0)` on this replay
- `completion_handoff_timer = 0x40a2aaaa` -> `5.083333f`
- `completion_handoff_timer_step = 0x3c888889` -> `1/60`
- packed byte lane at `player + 0x44c` read `0x00010101`
  - `attachment_exit_gate_a = 1`
  - `attachment_exit_gate_b = 1`
  - `completion_handoff_voice_gate = 1`

Recovered nearby block:

- `0x43c8fb`: subtract `player + 0x448` from `player + 0x444`
- `0x43c907`: write back adjusted timer
- `0x43c913`: compare `player + 0x444` against `5.0f`
- `0x43c934`: `begin_frontend_fade_out(...)`
- `0x43c953`: if `game + 0x12727ec != 0`, `flush_row_event_display(game + 0x12727d8)`
- `0x43c960`: load `game`
- `0x43c969`: if `game->mode != 0`, branch toward the non-Postal completion call
- `0x43c97d`: separate branch for the final-level case
- `0x43c9af`: `complete_subgame(game, 0)`
- `0x43c9ba`: `*(game + 0x1270fc8) = 1`

Practical completion-chain result:

1. `update_subgoldy` arms `completion_handoff_active`
2. `update_cutscene` state `6` calls `initialize_completion_screen`
3. once the handoff timer passes roughly `5.0s`, `update_subgoldy` begins the frontend fade, flushes row-event display if needed, and calls `complete_subgame`
4. on this Postal-mode replay, the observed final callsite was `complete_subgame(game, 0)` at `0x43c9af`

This resolves the main completion-timing uncertainty:

- Windows does initialize the completion screen almost immediately from cutscene state `6`
- the later `~5s` delay belongs to the frontend fade and final `complete_subgame` exit, not to the first completion-screen creation

## Slug Death With Spare Lives: Respawn Selector And Life Decrement

After the completion pass, a separate live repro used a slug enemy collision in Postal mode while the player still had all three visible lives.

First death-path stop:

- log line:
  - `[death_handoff_entry] player=0x0d338d9c mode=0 lives=3 world_y=0x3efae148 exit_pending=0 gate_a=1 gate_b=0 cutscene_state=0xc`

Useful conversion:

- `world_y = 0x3efae148` -> `0.49f`

Practical meaning:

- this slug death entered the death handoff while the player was still on-track at positive height
- it is therefore distinct from the older floor-gap or deep-fall path and confirms that `initialize_subgoldy_death` is not reserved for `world_y < -7`

The selector immediately chose the respawn branch:

- log line:
  - `[death_select_respawn] player=0x0d338d9c mode=0 lives=3 world_y=0x3efae148`
- stop site:
  - `0x446e59`
- recovered pre-call block:
  - `0x446e45`: `eax = *(ecx + 0x4340)`
  - `0x446e4b`: `test eax, eax`
  - `0x446e4d`: `jg 0x446e57`
  - `0x446e57`: `push 0`
  - `0x446e59`: `call initialize_subgoldy_resurrect`

Practical conclusion:

- Postal mode (`mode = 0`) with `visible_life_stock > 0` takes the `initialize_subgoldy_resurrect(player, 0)` branch
- this runtime capture matches the earlier static branch recovery exactly

The callee-side log confirmed the same branch argument:

- `[initialize_subgoldy_resurrect] player=0x0d338d9c final_loss=0 lives=3 mode=0`

An immediate respawn-state sample after initialization showed:

- `visible_life_stock = 3`
- `final_loss = 0`
- `flag84 = 1`
- `player + 0x8c = 0x3c888889`
- `player + 0x90 = 0x3c088889`
- `frontend_fade_state = 0`

Later in the same respawn sequence, the first `update_subgoldy_resurrect` tick was captured:

- `[update_subgoldy_resurrect_tick] player=0x0d338d9c lives=3 final_loss=0 flag84=1 t8c=0x3c888889 t90=0x3c088889 fade=0`

The actual visible-life decrement then fired at the predicted site:

- direct breakpoint stop:
  - `0x44205b`: `dec dword ptr [esi+0x4340]`
- live watchpoint confirmation immediately afterward:
  - `[visible_life_stock_nonseed_write] eip=0x442061 lives=2 mode=0`

Recovered surrounding block:

- `0x44204c`: `eax = *(esi + 0x408)`
- `0x442052`: `jne 0x442084`
- `0x442054`: `ecx = *(eax + 0x40)`
- `0x442057`: `test ecx, ecx`
- `0x442059`: `jne 0x442061`
- `0x44205b`: `dec dword ptr [esi + 0x4340]`
- `0x442061`: load global app pointer
- `0x442079`: `*(app + 0x1b8) = 0x1c`

Practical result:

- the visible-life decrement is committed inside `update_subgoldy_resurrect`, not at death selection time
- for the captured Postal respawn branch, the decrement is an actual `dec` on `player + 0x4340`
- the selector and the decrement are therefore cleanly separated in time:
  - selector at `initialize_subgoldy_death`
  - commit later in `update_subgoldy_resurrect`

This settles the spare-life hazard-death case:

- slug death uses the generic death handoff
- Postal mode with `lives > 0` chooses respawn
- the life counter drops later in the respawn-update path, not during the initial death selector

## Slug Death At Zero Lives: Final-Loss Branch

After two more identical slug deaths, the same session drove the visible life stock from `2 -> 1 -> 0`.

The final decrement replay was:

- selector:
  - `[death_handoff_entry] player=0x0d338d9c mode=0 lives=1 world_y=0x3efae148 exit_pending=0 gate_a=1 gate_b=0 cutscene_state=0xc`
  - `[death_select_respawn] player=0x0d338d9c mode=0 lives=1 world_y=0x3efae148`
- delayed commit:
  - `[respawn_life_decrement] player=0x0d338d9c lives_before=1 mode=0 progress=0x3f81110c fade=0 final_loss=0`
  - watchpoint confirmation immediately after:
    - `[visible_life_stock_nonseed_write] eip=0x442061 lives=0 mode=0`
- post-restart confirmation:
  - `[init_subgoldy] player=0x0d338d9c mode=0 lives=0 control_source=0x0cf0909c`

With the counter now at zero, the next slug death finally took the other selector branch:

- `[death_handoff_entry] player=0x0d338d9c mode=0 lives=0 world_y=0x3efae148 exit_pending=0 gate_a=1 gate_b=0 cutscene_state=0xc`
- `[death_select_final_loss] player=0x0d338d9c mode=0 lives=0 world_y=0x3efae148`
- stop site:
  - `0x446e51`

Recovered selector block:

- `0x446e45`: `eax = *(ecx + 0x4340)`
- `0x446e4b`: `test eax, eax`
- `0x446e4d`: `jg 0x446e57`
- `0x446e4f`: `push 1`
- `0x446e51`: `call initialize_subgoldy_resurrect`

The callee-side probe immediately confirmed the branch argument:

- `[initialize_subgoldy_resurrect] player=0x0d338d9c final_loss=1 lives=0 mode=0`

Later in the same `update_subgoldy_resurrect` path, the branch-specific stop landed at `0x442084`:

- `[respawn_complete_subgame_branch] player=0x0d338d9c mode=0 progress=0x3f81110c fade=0 final_loss=1`

Recovered final-loss block:

- `0x442084`: `*(game + 0x1270fc8) = 2`
- `0x442094`: `push 1`
- `0x442096`: `complete_subgame(game, 1)`
- `0x4420a1`: read `game + 0xff25d1`
- `0x4420c2`: one return leg sets `app + 0x1b8 = 0x1a`

Important contrast with the respawn branch:

- `player + 0x4340` was already `0`
- the final-loss path did **not** execute the decrement at `0x44205b`
- instead, it routed through `complete_subgame(game, 1)` after setting `game + 0x1270fc8 = 2`

This settles the Postal hazard-death selector completely:

- `visible_life_stock > 0`:
  - `initialize_subgoldy_death -> initialize_subgoldy_resurrect(player, 0)`
  - later decrement in `update_subgoldy_resurrect`
- `visible_life_stock == 0`:
  - `initialize_subgoldy_death -> initialize_subgoldy_resurrect(player, 1)`
  - no further life decrement
  - later `update_subgoldy_resurrect` routes through `complete_subgame(game, 1)`

## Floor-Gap Fall: Direct `update_subgoldy` Death Caller

After the slug-death work, the same session was re-armed specifically for a clean void fall with only four death-path stops enabled:

- `0x43c093`: direct `update_subgoldy -> initialize_subgoldy_death`
- `0x446b04`: `update_cutscene -> initialize_subgoldy_death`
- `0x446e59`: respawn selector
- `0x446e51`: final-loss selector

The next clean floor-gap repro finally hit the direct caller first:

- `[fall_death_via_update_subgoldy] player=0x0d338d9c mode=0 lives=1 world_y=0xc0e0e49c move=0 death_flag84=0 exit_pending=1 gate_a=1 gate_b=0`
- stop site:
  - `0x43c093`: `call initialize_subgoldy_death`

`world_y = 0xc0e0e49c` converts to roughly `-7.027906f`, which is below the static `-7.0f` threshold already recovered from `update_subgoldy`:

- `0x43c07a`: `fcomp dword ptr [0x4975bc]`
- `0x43c087`: `mov al, byte ptr [ebp + 0x84]`
- `0x43c08f`: `jne 0x43c098`
- `0x43c093`: `call initialize_subgoldy_death`

This confirms that at least one ordinary floor-gap death path does **not** begin in `update_cutscene`; it begins directly in `update_subgoldy` once the live player state crosses the void threshold with `flag84 == 0`.

Continuing from that stop immediately reached the same selector family used by slug death:

- `[death_select_respawn] player=0x0d338d9c mode=0 lives=1 world_y=0xc0e0e49c`
- stop site:
  - `0x446e59`: `call initialize_subgoldy_resurrect`

Practical result:

- floor-gap fall and hazard death share the same downstream `initialize_subgoldy_death` selector
- the important difference is the entry lane:
  - slug death was observed entering from the `update_cutscene` side with positive `world_y = 0.49f`
  - floor-gap fall was observed entering directly from `update_subgoldy` with negative `world_y ~= -7.03f`
- this resolves the earlier ambiguity about why some gap falls never touched the cutscene-side probe

The follow-up zero-life repro confirmed that the selector result also matches the slug-death final-loss case:

- `[fall_death_via_update_subgoldy] player=0x0d338d9c mode=0 lives=0 world_y=0xc0e0e49c move=0 death_flag84=0 exit_pending=1 gate_a=1 gate_b=0`
- immediate selector stop:
  - `[death_select_final_loss] player=0x0d338d9c mode=0 lives=0 world_y=0xc0e0e49c`
  - `0x446e51`: `call initialize_subgoldy_resurrect`

Practical conclusion:

- ordinary floor-gap fall uses a different entry lane than slug death
- once both arrive at `initialize_subgoldy_death`, the zero-life selector outcome is the same:
  - `lives == 0` takes `death_select_final_loss`
  - `lives > 0` takes `death_select_respawn`

## Intro Camera Trace: `update_cutscene` And `update_subgame_camera`

After the death-path work, the live `cdb` session was repurposed to a narrow intro-camera logging pass with three probes:

- `0x4466d0` `update_cutscene`
  - log only on state changes
  - captures current cutscene state, player world position, hotspot `12` (`CameraSkidStop`), hotspot `18` (`CameraIntroTalk`), and the cutscene controller translation at `cutscene + 0x40/+0x44/+0x48`
- `0x4460a4` `update_subgame_camera`
  - log only when the shared camera selects the override source
- `0x4460c1` `update_subgame_camera`
  - log only when the shared camera selects the live cameraman source

One fresh level start produced a clean intro sequence:

- `[cutscene_state_change] ... state=1 ... hotspot12=(0xbf136114,0x40f34c9c,0x40bcfaad) hotspot18=(0x3f5c154d,0x40f87c88,0x40bccf42) cutscene_xyz=(0x3f728032,0x400c78a0,0x41b9a77f)`
- `[camera_source_override] ... active=2 snap=1 override_xyz=(0x3f5c154d,0x40f87c88,0x40bccf42) ...`
- `[cutscene_state_change] ... state=2 ... hotspot18=(0x3f5bcd8e,0x410415d8,0x40bccf42) cutscene_xyz=(0x3f5c154d,0x40f87c88,0x40bccf42)`
- `[cutscene_state_change] ... state=8 ... hotspot18=(0x3f4a6a39,0x4102e94e,0x40be1e1a) cutscene_xyz=(0x3f4abc01,0x4102e82a,0x40be19bd)`
- `[cutscene_state_change] ... state=9 ... cutscene_xyz=(0x34922b3e,0x41325927,0x401ab3dc)`
- `[camera_source_cameraman] ... snap=0 cameraman_xyz=(0x00000000,0x41325927,0x401ab3d8) ...`

Practical read from that intro trace:

- the runtime intro state order `1 -> 2 -> 8 -> 9` is now confirmed by direct capture
- `update_subgame_camera` does switch the shared camera to the override source during intro
- the first override translation exactly matches hotspot `18` (`CameraIntroTalk`), not hotspot `12`
- later intro states continue to track very close to hotspot `18`
- the handoff back to gameplay happens when the shared camera source flips back to the live cameraman path, and the cameraman translation at that moment is almost identical to the final cutscene translation

Most important current conclusion:

- the intro camera is not just "cameraman with a different FOV"
- it really does route through the cutscene override lane in `update_subgame_camera`
- for the captured intro leg, hotspot `18` (`CameraIntroTalk`) is the dominant anchor; hotspot `12` (`CameraSkidStop`) did not win the first source-selection decision

## Completion Camera Trace: `update_cutscene` And `update_subgame_camera`

The same logging probes were then left armed across one full level completion.

The completion side produced a clean second cutscene sequence:

- `[cutscene_state_change] ... state=5 ... hotspot12=(0xbf712072,0x3ed08330,0x44023d49) hotspot18=(0x3ef70b57,0x3f2345fc,0x440238f4) cutscene_xyz=(0x00000000,0x41325ad8,0x401940e6)`
- `[camera_source_override] subgame=0x0cf7d638 active=6 snap=1 override_xyz=(0xbea25fa2,0x3ffc5a1c,0x44014ef5) shared_xyz=(0xbea25a65,0x3ffc5a1c,0x44014ce5) shared_fov=0x42dc0000`
- `[cutscene_state_change] ... state=6 ... hotspot12=(0xbf80c70d,0x3ecf44e8,0x44024eba) hotspot18=(0x3ed6e0c9,0x3f22d956,0x44024d77) cutscene_xyz=(0xbea25fa2,0x3ffc5a1c,0x44014ef5)`
- `[cutscene_state_change] ... state=7 ... hotspot12=(0xbfdc56fc,0x3ef59546,0x4405604c) hotspot18=(0xc01e8693,0x3f2c4833,0x4405ae1e) cutscene_xyz=(0xc01e8995,0x3f2c6b4c,0x4405ae0a)`

Practical read from the completion trace:

- the runtime completion order `5 -> 6 -> 7` is now confirmed by direct capture
- `update_subgame_camera` again switches the shared camera onto the override source during completion
- the first completion override does **not** equal hotspot `12` or hotspot `18` exactly
  - that is consistent with the recovered state-`5` `CameraSkidStop -> CameraIntroTalk` blend path rather than a direct snap to one authored hotspot
- by state `7`, the cutscene translation is extremely close to hotspot `18` (`CameraIntroTalk`)

Current best interpretation:

- intro and completion both use the override-camera lane in `update_subgame_camera`
- intro begins by snapping to hotspot `18`
- completion begins from a blended override that is distinct from both source hotspots and then converges toward hotspot `18`
- this is directionally consistent with the static `state 5` blend recovery and explains why the current Zig cutscene camera is still wrong if it treats completion as only a delayed frontend handoff or as one fixed anchor

## Slug Death Camera Trace: `update_cutscene` And `update_subgame_camera`

The same logging probes remained armed for one slug death with spare lives. After an earlier ambiguity about whether the trace had already crossed into the respawn intro-talk handoff, the probe pack was widened to log hotspot `17` (`CameraSlugDeath`) alongside hotspots `12` and `18`.

The death path again produced the expected state order:

- `[cutscene_state_change] ... state=a ... hotspot12=(0xc0458d82,0x3ee4e6f4,0x432076e0) hotspot17=(0xbffdcbc8,0x3f9b7c42,0x4319196f) hotspot18=(0xbfd5250f,0x3f2ee0fe,0x4320909b) cutscene_xyz=(0x00000000,0x41325ada,0x40193ecd)`
- `[camera_source_override] subgame=0x0cf7d638 active=0xb snap=1 override_xyz=(0xbfd54201,0x3ffc5a1c,0x431ccffc) shared_xyz=(0xbfd4bf0a,0x3ffc5a1c,0x431cc9db) shared_fov=0x42dc0000`
- `[cutscene_state_change] ... state=b ... hotspot12=(0xc046be0b,0x3f0879c7,0x432062bf) hotspot17=(0xc004f1db,0x3fa65ff9,0x43190278) hotspot18=(0xbfd76e39,0x3f454038,0x432078c0) cutscene_xyz=(0xbfd54201,0x3ffc5a1c,0x431ccffc)`
- `[cutscene_state_change] ... state=c ... hotspot12=(0xc05afd42,0x3f00b38c,0x431e5321) hotspot17=(0xc020f298,0x3f99d0e8,0x4316ed10) hotspot18=(0xbffdb834,0x3f1ca996,0x431e5ffc) cutscene_xyz=(0xbffde6b3,0x3f1c4617,0x431e6050)`
- immediately after death state `c`, the respawn intro reappeared and again showed the usual hotspot-`18` intro lane:
  - `[cutscene_state_change] ... state=1 ... hotspot18=(0x3f5c154d,0x40f87c88,0x40bccf42) cutscene_xyz=(0xc002aacb,0x3f190b28,0x431e6395)`
  - `[cutscene_state_change] ... state=2 ... hotspot18=(0x3f5bcd8e,0x41041752,0x40bccf42) cutscene_xyz=(0x3f5c154d,0x40f87c88,0x40bccf42)`
  - `[cutscene_state_change] ... state=8 ... hotspot18=(0x3f4a6a39,0x4102eac8,0x40be1e1a) cutscene_xyz=(0x3f4abc01,0x4102e9a4,0x40be19bd)`

Practical read from the widened death trace:

- the runtime death order `a -> b -> c` is confirmed again by direct capture
- `update_subgame_camera` again switches the shared camera onto the override source during death
- the `state=a` cutscene translation is still the pre-death gameplay value, so the first usable death-camera sample is the immediate override written between `state=a` and `state=b`
- that first usable death override is already much closer to hotspot `18` than hotspot `17`
  - at the `state=b` sample, the active death override is about `0.01697` units from hotspot `18` and about `0.41118` units from hotspot `17`
- by `state=c`, the cutscene translation is effectively on hotspot `18`
  - the `state=c` translation is about `0.00142` units from hotspot `18` and about `0.53120` units from hotspot `17`
- the later respawn intro still converges onto hotspot `18` in the same way as a fresh level start

Most useful current conclusion:

- death, like intro and completion, uses the override-camera lane in `update_subgame_camera`
- this widened slug-death capture does **not** support hotspot `17` (`CameraSlugDeath`) as the live death-camera anchor for the observed respawn path
- the best present read is stronger than before: the first usable death override is already on the hotspot-`18` lane, and the later closeness to hotspot `18` is not just an artifact of the respawn intro handoff

## Hotspot Constructor Captures: `initialize_cutscene` And `update_snail_skin`

After the hotspot comparisons, the probe pack was narrowed to the actual constructor path:

- `initialize_cutscene`
- `update_snail_skin`
- static readback from `build_snail_hotspots`

The purpose was to settle whether hotspot `18` is a fixed authored world-space anchor or a runtime product of the cutscene/player matrix setup.

### Intro Constructor Capture

One clean intro transition from the black level-start screen produced the following sequence:

- first stop at `initialize_cutscene` entry:
  - live state after one instruction:
    - `cutscene.state = 1`
    - `player = 0x0d338d9c`
    - `src1604_t = (0x00000000, 0x40f480a1, 0x40800000)`
    - `src1684_t = (0x00000000, 0x40f47644, 0x40800000)`
    - hotspot `18` was still zero before the rebuild
- second stop at `update_snail_skin` entry:
  - `player = 0x0d33b720`
  - `hotspot18_before = (0xc018e52e, 0x3f248a6e, 0x441ed5ca)` from the prior level state
  - `src1604_t = (0x00000000, 0x40f480a1, 0x40800000)`
  - `src1684_t = (0x00000000, 0x40f47644, 0x40800000)`
- after stepping out of `update_snail_skin`, hotspot `18` became:
  - `(0x3f5c154d, 0x40f87c88, 0x40bccf42)`

Practical read from the intro constructor capture:

- hotspot `18` is rebuilt during the intro path rather than treated as a fixed authored constant
- the rebuild happens through `update_snail_skin` / `build_snail_hotspots`
- the two source translations feeding the rebuild are already populated before the hotspot update and are nearly identical during intro start
- the rebuilt hotspot `18` exactly matches the earlier intro-camera override sample

### Completion Constructor Capture

One normal level finish produced the matching completion-side sequence:

- first stop at `update_cutscene` state `5` entry:
  - `cutscene = 0x0d33d078`
  - `player = 0x0d33b720`
  - `hotspot18 = (0x3f678197, 0x3f4a9266, 0x4402f3a3)`
  - `cutscene_xyz = (0x00000000, 0x4132ac86, 0x40690d9f)`
- second stop at `update_snail_skin` during `cutscene.state = 6`:
  - `subgame = 0x0d33b720`
  - `player = 0x0d338d9c`
  - `hotspot18_before = (0x00000000, 0x00000000, 0x00000000)`
  - `src1604_t = (0xbe6cf236, 0x3efbd016, 0x440295fd)`
  - `src1684_t = (0xbe584000, 0x3f05325b, 0x440295d2)`
- after stepping out of `update_snail_skin`, hotspot `18` became:
  - `(0x3f498b24, 0x3f2a67f2, 0x44030a36)`

Practical read from the completion constructor capture:

- completion uses the same hotspot rebuild lane as intro
- hotspot `18` is again synthesized during the cutscene path, not simply read as a fixed authored world-space marker
- the rebuild is fed by the same two source matrices, but unlike intro they are measurably different during completion
- the rebuilt hotspot `18` lands in the same neighborhood as the earlier completion camera trace, which is consistent with a live matrix-driven rebuild rather than a single static anchor lookup

### Death Constructor Capture

One spare-life slug death produced the matching death-side sequence:

- first stop at `update_cutscene` state `a` entry:
  - `cutscene = 0x0d33d078`
  - `player = 0x0d33b720`
  - `hotspot17 = (0xbfac04a4, 0x3f922f50, 0x43128213)`
  - `hotspot18 = (0xbf7347b6, 0x3f0af7f0, 0x4319f703)`
  - `cutscene_xyz = (0x00000000, 0x41325ad4, 0x4019436c)`
- second stop at `update_snail_skin` during `cutscene.state = 0xb`:
  - `subgame = 0x0d33b720`
  - `player = 0x0d338d9c`
  - `hotspot17_before = (0x00000000, 0x00000000, 0x00000000)`
  - `hotspot18_before = (0x00000000, 0x00000000, 0x00000000)`
  - `src1604_t = (0xbfdac122, 0x3f0da750, 0x4317edfc)`
  - `src1684_t = (0xbfdd4000, 0x3f147a3d, 0x4317edb4)`
- after stepping out of `update_snail_skin`, the rebuilt hotspot vectors became:
  - `hotspot17 = (0xbfad329d, 0x3f9dc3f2, 0x43126af6)`
  - `hotspot18 = (0xbf72ca4a, 0x3f224005, 0x4319dfc0)`

Practical read from the death constructor capture:

- death uses the same `update_snail_skin` / `build_snail_hotspots` rebuild lane as intro and completion
- during the observed death transition, both hotspot `17` and hotspot `18` are zeroed before the rebuild and then synthesized from the same two source matrices
- this means hotspot `17` is not just a static authored marker sitting untouched in memory; it is also regenerated on the runtime cutscene path
- combined with the earlier death-camera trace, the current best read is:
  - the death camera still tracks the hotspot-`18` lane in the observed spare-life path
  - hotspot `17` is real and rebuilt, but we still do not have evidence that the live spare-life death camera actually selects it as the active shot anchor

Most useful current conclusion:

- the camera bug in the Zig port is unlikely to be only "wrong hotspot id"
- intro, completion, and death all show the cutscene hotspots being synthesized from runtime matrix state
- the next high-value step is to recover the exact formula inside `build_snail_hotspots` or the source-matrix setup feeding `1604` and `1684`, because that is now the most likely place where the port diverges from Windows

### Intro Source-Matrix Dump

A later clean intro repro was instrumented to dump the full `1604` and `1684` matrices at the first `update_snail_skin` hit after `cutscene.state = 1` had been observed. The useful capture landed at `cutscene.state = 2`, with both hotspot vectors still zero before the rebuild:

- `[intro_update_snail_skin_matrix_dump] subgame=0x0d33b720 player=0x0d338d9c state=2 hotspot17=(0,0,0) hotspot18=(0,0,0)`
- `1604` matrix:
  - row 0: `(0x3f7ffffb, 0x3a490fda, 0x00000000, 0x00000000)`
  - row 1: `(0xba490fda, 0x3f7ffffb, 0x00000000, 0x00000000)`
  - row 2: `(0x00000000, 0x00000000, 0x3f800000, 0x00000000)`
  - translation: `(0xba82f25b, 0x410216a6, 0x40800000)`
- `1684` matrix:
  - row 0: `(0x3f800000, 0x00000000, 0x00000000, 0x00000000)`
  - row 1: `(0x00000000, 0x3f800000, 0x00000000, 0x00000000)`
  - row 2: `(0x00000000, 0x00000000, 0x3f800000, 0x00000000)`
  - translation: `(0x00000000, 0x41020c33, 0x40800000)`

Practical read from that matrix dump:

- `1684` is effectively an identity-orientation source with only a world translation
- `1604` is almost the same translation but with a tiny planar rotation and a very small X offset
- so the intro hotspot rebuild is not combining two dramatically different source frames at this point; it is operating on two nearly coincident sources, one of which already carries a small rotation or local offset
- this strengthens the current read that the port bug is likely in the exact hotspot-construction math or source-matrix preparation, not in broad cutscene-state selection

### Intro Camera Driver-Chain Capture

After the constructor traces, the probe pack moved one level upstream:

- `look_at_point`
- `linear_interpolate_matrix`
- the source switch inside `update_subgame_camera`

The purpose was to stop sampling downstream hotspot outputs and instead capture the actual driver chain that publishes the live intro camera.

Static recovery first:

- `look_at_point` callsites inside `update_cutscene`:
  - `0x446771`
  - `0x44680f`
  - `0x446a1e`
  - `0x446af3`
  - `0x446d20`
  - `0x446dd3`
- `linear_interpolate_matrix` callsites inside `update_cutscene`:
  - `0x446850`
  - `0x446a5f`
  - `0x446d61`

The fresh intro repro produced two important state families.

#### State `2`: direct `look_at_point` drive into `cutscene + 0x10`

Early intro repeatedly hit the `look_at_point` call returning to `0x446771`:

- `[cutscene_look_at] ret=00446771 state=2 dst=0x0d33d088 dst_t=(0x3f5c154d,0x40f87c88,0x40bccf42) target=0x0d33b788 target=(0x00000000,0x40f480a1,0x40800000)`
- later samples in the same state kept the same destination matrix and moved the target gradually, for example:
  - `target=(0x3d521673,0x40f4ce3b,0x408a9547)`
  - `target=(0x3e310116,0x40f56388,0x4095c15e)`

At the same time, `update_subgame_camera` reported the override source becoming active:

- `[camera_source_override] state=2 override_t=(0x3f5c154d,0x40f87c88,0x40bccf42) shared_t=(0x00000000,0x40400000,0x00000000) shared_fov=0x42dc0000`

Practical read from state `2`:

- the live cutscene matrix at `cutscene + 0x10` is already the active override source
- `update_cutscene` is not snapping to a prebuilt hotspot here; it is repeatedly reorienting that live matrix toward a moving target vector with `look_at_point`
- translation is already on the intro-talk lane at this phase, while orientation is still being actively recomputed

#### State `8`: blend from a temporary look-at matrix into the cameraman matrix

Later intro repeatedly hit the second `look_at_point` / `linear_interpolate_matrix` pair:

- `[cutscene_look_at] ret=0044680f state=8 dst=0x0019fc10 dst_t=(0x3f4a6a39,0x4102eac3,0x40be1e1a) target=0x0d33b788 target=(0x3c9fd3e7,0x41019ba2,0x40800814)`
- `[cutscene_lerp] ret=00446850 state=8 dst=0x0d33d088 a=0x0019fc10 b=0x0019fc50 alpha=0x00000000 a_t=(0x3f4a6a39,0x4102eac3,0x40be1e1a) b_t=(0x00000000,0x41325ad4,0x4019436c)`

As state `8` progressed:

- `a_t` kept moving through a long sequence of look-at positions
- `b_t` stayed fixed at `(0x00000000,0x41325ad4,0x4019436c)`
- `alpha` ramped upward from `0` toward `1.0`

Representative later samples:

- `alpha=0x3db851ec` with `a_t=(0x3f0560af,0x410c3159,0x40c5a59b)`
- `alpha=0x3ec7bbfd` with `a_t=(0xbece2fdb,0x4113ff4f,0x40c5dd38)`
- `alpha=0x3f20d4fd` with `a_t=(0xbf1fba92,0x411881f4,0x40bc13ed)`
- `alpha=0x3f51ec00` with `a_t=(0xbf4d88f0,0x411e4bf9,0x40a72d2d)`
- `alpha=0x3f68ba31` with `a_t=(0xbf638d5d,0x41247f1c,0x40842c91)`
- `alpha=0x3f851ece` with `a_t=(0xbf81ddd8,0x412cfabf,0x402f2f74)`
- `alpha=0x3fa2f98f` with `a_t=(0xbf9f79b8,0x413579b9,0x3f7f71eb)`
- `alpha=0x3fc1de00` with `a_t=(0xbfbc5051,0x413df897,0xbed3fe5a)`
- `alpha=0x3fe03fbd` with `a_t=(0xbfd88bfe,0x414677ef,0xbfa5f2df)`
- `alpha=0x3fff1108` with `a_t=(0xbff4917c,0x414ef697,0xc017e6c0)`

Practical read from state `8`:

- `update_cutscene` first builds a temporary stack matrix with `look_at_point`
- it then blends the live cutscene matrix at `cutscene + 0x10` between:
  - `a`: that temporary look-at matrix
  - `b`: another stack matrix whose translation matches the cameraman lane
- the intro handoff back to gameplay is therefore an explicit matrix interpolation, not a hotspot swap or a direct snap to the cameraman output

#### End of intro: shared source flips back to cameraman

Once the interpolation completed, `update_subgame_camera` flipped the shared camera source back to cameraman:

- `[camera_source_cameraman] state=0 cameraman_t=(0x00000000,0x41325ad4,0x4019436c) shared_t=(0x37568f35,0x41325aae,0x40194429) shared_fov=0x42dc0000`

The cameraman translation matches the fixed `b_t` used throughout the state `8` interpolation.

Most useful current conclusion:

- the intro camera is actively driven upstream by `update_cutscene`
- state `2` repeatedly orients the live cutscene matrix toward a moving target with `look_at_point`
- state `8` blends that live matrix back toward the cameraman matrix with `linear_interpolate_matrix`
- `update_subgame_camera` only publishes the result and then flips the shared source back to cameraman once the handoff completes
- hotspot rebuilds are therefore downstream artifacts of the same cutscene state, not the best place to understand the camera motion itself
