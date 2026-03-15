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
4. the exit helper currently named `initialize_subgoldy_fall_state`

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
- `0x43af60` `initialize_subgoldy_fall_state`
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

Static cross-check against `0x43af60` / `initialize_subgoldy_fall_state`:

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
- on this replay, `initialize_subgoldy_fall_state` was entered with `active = 0`, so the active follow flag can already be clear by the time the helper runs
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

Finally, a replay armed with exact `update_subgoldy` callsite probes for all four direct callers of `initialize_subgoldy_fall_state`:

- `0x43b9b8`
- `0x43c008`
- `0x43c34b`
- `0x43c507`

finished cleanly without hitting any of those four sites.

Practical implication:

- at least one clean-finish level-complete path is bypassing the `update_subgoldy -> initialize_subgoldy_fall_state` fall-helper lane entirely
- the helper and the post-exit progress gates are therefore real runtime behavior, but they are not the only way attachment-follow is retired during ordinary play
