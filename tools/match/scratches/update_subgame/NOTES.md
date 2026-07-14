# `update_subgame` recovery notes

Target: `update_subgame @ 0x438b90` (`thiscall`, 3748 bytes, 1033 instructions).

This scratch reconstructs the outer gameplay state machine and the state-2 runtime update path rather than using a minimal placeholder. The source was shaped against both decompile exports and repeatedly measured with the VC6.5 `/O2 /G5 /W3` matcher toolchain.

`SubgameRuntime::garbage_frequency` at `+0x125ffd8` and `salt_frequency` at
`+0x125ffdc` are the normalized level-script spawn controls. The garbage lane
drives the 0.8..1.0 random threshold and the salt lane drives the 0.98..1.0
threshold; `build_subgame_level` seeds both and `complete_subgame` persists
both into the replay/high-score record. Direct member access preserves the
focused 78.22% result (`1033/1033`, `116` clean operands and the two existing
jump-table label mismatches).

## Recovered control flow

The front switch now models the principal native states:

- states `3` and `4`: pause-menu initialization followed by the intentional fallthrough into its first update;
- state `7`: selected-replay bootstrap and level-zero rebuild;
- state `0`: continuation/rebuild selector, persistent replay lane, star-field hide, and fallthrough to the setup dispatcher;
- state `1`: galaxy, challenge, and tutorial/setup dispatch, including destroy-and-handoff returns;
- state `2`: selected-level overlay, timer advance, tutorial and slug-voice updates, pause/resume gates, click-start suppression, runtime-row processing, HUD updates, and camera handoff.

The shared camera call is left at function tail, while native early-return paths retain direct camera calls where that source shape scores better.

## Runtime layout findings

The row scanner uses the canonical `SubRow` owner at
`SubgameRuntime::runtime_rows`:

- `SubRow` stride: `0xf4` bytes;
- row flags: `+0x00`;
- embedded `RowModel`: `+0x04`;
- overloaded parcel projection payload: `+0x90`;
- embedded attachment `BodBase`: `+0xb0` (position at `+0xc0`);
- authored ring/effect speed: `+0xe8`;
- track cell stride: `0x54` bytes;
- four fringe-object pointers begin at the cell's `+0x44` lane.

`RuntimeCellSlotBase` deliberately preserves the indexed slot base and accesses the cell through its native `+0x3bfac8` displacement. A direct typed `TrackRowCell*` caused VC6 to fold that displacement too early and materially changed register allocation.

The runtime block includes plausible original insertion idioms for the two intrusive lists and semantic lanes for parcels, fringe objects, health pickups, speedups, jetpacks, garbage and salt hazards, slugs, and authored/ambient rings.

## Compiler-shape findings

Several source-level details were important rather than cosmetic:

- Reloading the fringe object after `get_track_skirt_color` removes an otherwise persistent pointer spill. This recovers the native `0x3c` frame, `ebp` row index, `edi` cell-offset base, and `ebx` zero value.
- The tile `29`/`30` path scores better as a nested block with an inner auxiliary-data test.
- The fringe selector is signed `cell_index % 8`; replacing it with `& 7` loses the target's signed modulus sequence.
- The four authored tile-35 ring variants converge on one shared last-ring-Z assignment.
- RNG calls are kept on the left side of comparisons where that produces the native operand ordering and clean call audits.
- Completion-source assignments intentionally retain the matcher-confirmed X/Y source ordering.
- Duplicating the challenge-setup `result == 1` build-zero path scores better than sharing the later case-7 label; the native places that build return before the challenge destroy path.
- `format_time_trial_string` is the receiver-free body of
  `cRTimeTrial::TimeString(cRTime&)`; callers bind the exact embedded owner at
  `game + 0xff25e0`, recovering the native `ecx` setup at the HUD callsites.

These choices recover the exact native prologue through the state range test:

```asm
sub esp, 0x3c
push ebx
push ebp
push esi
push edi
mov esi, ecx
call calc_subgame_rate
mov eax, [esi+0x3c]
cmp eax, 7
```

## Remaining mismatches

Focused matcher result: 79.75%, 1036 candidate instructions versus 1033 target instructions, 9-instruction prefix, 117 clean masked operands, and 2 jump-table mismatches.

The first mismatch is the destination label of the range-check `ja`; its semantics agree, but later block sizes give the normalized target and candidate labels different identities. Both switch jump-table operands are now content-audited and classified as real mismatches, not unresolved data or call targets.

The semantic structure and ownership are pinned. The remaining non-proof-grade
regions are:

1. state-1 galaxy setup case ordering and shared build/destroy exits;
2. residual authored/ambient ring register scheduling;
3. residual HUD and handoff register scheduling;
4. residual jump-table target identities driven by the remaining block layout.

Rejected continuation trials:

- moving the selected-level handoff to a tail `goto` label still emitted the same measured layout;
- spelling the pause-state setup with raw offsets did not change the prologue mismatch;
- materializing a time-trial `record` base local improved one address sequence but regressed the surrounding HUD/camera tail.

2026-06-20 type cleanup: the shared Time Trial header took over the formatter
receiver used here and by the challenge setup/HUD callers. The broad
`update_subgame` scratch stayed at 67.53%.

2026-07-11 TimeTrial ownership: the receiver is now the complete embedded
0x330-byte `TimeTrial`, with its far boundary proven by PathManager at
+0xff2910. The typed owner is codegen-neutral at the current 78.22% baseline;
its internals remain opaque because TimeString does not read them.

2026-06-21 receiver cleanup: the scratch now defines
`SubgameRuntime::update_subgame` directly and uses the shared
`SubgameRuntime` front-controller window for pause menu, challenge setup,
galaxy route, selected replay state, and rebuild selector fields. Focused Wibo
is unchanged at `67.53%`, `1046/1033`, prefix `9/1033`, with the same
`108 ok / 2 mismatch` masked audit. `spawn_track_speedup` remains a
member-style call surface on `SubgameRuntime` because this caller wants the
historical receiver lookup even though the standalone helper body is
`__stdcall`/receiver-free. `uv run snail match types --paths` still reports no
generic `Game` owner row.

2026-07-10 embedded-player ownership: `game + 0x3bb764` is the complete
embedded `Player`/`cRSubGoldy`, not a standalone score block. The measured
extent is exact: `0x3bb764 + sizeof(Player) (0x4364) == 0x3bfac8`, the first
runtime track cell. This unifies the previously flattened aliases for
`position.z +0x70`, `click_start.state +0x120`, `cameraman +0x200`, score/timer
lanes `+0x2e4/+0x2e8`, `player_slot +0x380`, `velocity.z +0x418`,
`control_source +0x43c`, and `interaction_max_z +0x2980`. The shared runtime
now embeds `Player player` directly; the temporary `player_storage` union and
all contextual aliases have been retired. This scratch routes all player gates
and spawn arguments through that member while preserving the current 78.22%,
1033/1033 result, 116 clean operands, and the same two jump-table mismatches.
Exact `calc_subgame_rate` and `update_subgame_camera` remain exact.

2026-07-12 nested ClickStart ownership: the native gate at Player +0x120 is
now expressed as `player.click_start.state`, the state lane of the exact
0xac-byte cRClickStart child at Player +0xa0. Focused Wibo remains 78.22%,
1033/1033 instructions; the two existing jump-table masks are unchanged.

A named `Player*` kept across the pause/fade bridge measured `70.53%` and
reduced the candidate to `1037` instructions, but it displaced the native
`ebx` zero / `edi` state roles and made the operand audit pair the target
`spawn_track_speedup` call with candidate `spawn_track_health_pickup`. That
variant is rejected rather than retaining an attractive score with a new
semantic masked-operand mismatch.

2026-07-10 bridge-tail layout: expressing the selected-level handoff as the
cold side of an inverted state-2 bridge places it after the gameplay/HUD body,
matching the independent Windows and Android control-flow evidence. Duplicating
the current-to-previous application-state snapshot inside the persistent and
non-persistent arms recovers the exact native tail instructions. Together these
changes improve focused Wibo from `67.53%`, `1046/1033`, `108 ok` to `69.45%`,
`1049/1033`, `111 ok`, while preserving the same two jump-table mismatches and
introducing no call/data mismatch. Direct embedded-player owners now cover its
completion gate, stopwatch, interaction bound, total score, lives, and the
`last_ring_spawn_z +0x37c` lane initialized by `initialize_subgoldy`.

Retested neighbors on the new bridge layout: materializing the time-trial
record base regressed `68.94%` to `67.95%`; a shared ambient-ring speed local
grew the frame from `0x3c` to `0x40` and regressed to `61.11%`; a named control
source was codegen-neutral. None were retained.

2026-07-10 projected-ring address ownership: the projected cell at
`cell + 0xfc0` is a contextual address, not a long-lived local owner. Inlining
that address in the three projected-ring arms removes the invented `ebx`
lifetime and recovers the native repeated address formation plus shared
post-call last-Z store. Focused Wibo improves from `69.45%`, `1049/1033`,
`111 ok` to `70.97%`, `1027/1033`, `115 ok`, with the exact `0x3c` frame and
the same two jump-table mismatches. No call or data operand mismatch is added.

2026-07-10 time-trial record owner retest: after shortening the projected-cell
lifetime, the semantic `record = game + level_mode_arg * 0x1fac0` pointer no
longer perturbs the surrounding frame allocation. It now recovers the native
`add eax, esi` followed by in-place `+0x944158` reuse, improving focused Wibo
from `70.97%`, `1027/1033`, `115 ok` to `71.32%`, `1028/1033`, `116 ok` with
the same two jump-table mismatches and no unresolved or mismatched call/data
operand. The earlier record-local regressions remain useful allocation-history
evidence, but no longer describe the retained layout.

2026-07-10 authored garbage-hazard arm: tile `33` is a dedicated authored
spawn case, while tiles `1`/`21` enter the gated procedural generator. Keeping
those as sibling `if` / `else if` arms recovers the native five-instruction
argument setup and shared call tail that the combined boolean expression had
optimized away. Focused Wibo improves from `71.32%`, `1028/1033` to `78.22%`,
`1033/1033`; the frame stays `0x3c`, all 116 audited call/data operands remain
clean, and only the same two jump-table identities mismatch.

Final no-fakematch boundary: retesting a named `Player*` across the complete
state-2 body after the garbage-arm correction regressed to `64.93%`, grew the
candidate to `1043` instructions, reduced the clean operand audit to `110`,
and again paired target `spawn_track_speedup` with candidate
`spawn_track_health_pickup`. Shortening the application-state receiver scope
and adding an explicit row-window exit were codegen-neutral at `78.22%`.
Neither is retained. The current scratch is pinned at the exact target
instruction count with no unresolved or mismatched call/data operand; further
register or label shaping needs new independent source evidence.

2026-07-11 galaxy ownership: the state-zero route dispatch now uses the
embedded `SubgameRuntime::galaxy` at `+0x1260020`, retiring the duplicate
`CompletionGalaxyRoute` view. Focused output remains 78.22%, 1033/1033, with
the same two jump-table mismatches and 116 clean operands.

2026-07-11 track group ownership: the row-window linker now uses three embedded
`BodBase` sentinels directly: `track_body_list_head +0x355b9c` for ordinary
cells, `special_track_cell_list_head +0x355cb4` for tile 29/30 bodies, and
`fringe_attachment_list_head +0x355b64` for row attachment bodies and all four
fringe handles. The typed expressions are codegen-neutral at 78.22%, 1033/1033.

The shared-header generation places `$L5096` at object `+0xe58` and `$L5097`
at `+0xe78`, but the matcher's bounded-content audit rejects both against the
target tables. Their destination sequences differ because the surrounding
state dispatch is still structurally unmatched. They remain two real masked
mismatches with 116 other operands clean; no aliases are registered.

2026-07-11 slug voice manager ownership: the state-2 update now calls the
embedded `SubgameRuntime::slug_voice_manager` directly. Android retains the
same owner/member as `cRSlugVoiceManager::AI()`, and the preceding exact
initializer closes the complete 0x0c-byte object. Focused output remains
78.22%, 1033/1033, with 116 clean operands and the same two honest jump-table
mismatches.

2026-07-11 cRTutorial owner: the mode-7 tick now calls the embedded
`tutorial.update_tutorial()` directly. The exact Init/AI/UnInit siblings,
mobile symbols, and the native 0x1c size ledger prove the owner at `+0xa858`;
the local one-method `TutorialRuntime` shell is retired. Focused output remains
78.22%, 1033/1033, with 116 clean operands and the same two real table-shape
mismatches.

2026-07-13 runtime-row window and child-owner pass:

- `SubgameRuntime +0x20/+0x24` is the rolling runtime-row scan window, now
  named `runtime_row_scan_begin` / `runtime_row_scan_end`. `scan_reset` seeds
  the begin at zero and the end from either `runtime_row_count` or the player
  interaction Z window; subsequent ticks advance begin to the prior end, and
  every path caps the exclusive end at `completion_row_start + 20`.
- The state-one challenge callback now uses the embedded `gui`; authored and
  procedural salt spawns use the embedded `salt_hazards`; time-trial HUD
  formatting uses the embedded `time_trial`; and score rendering uses the
  borrowed `top_score_widget` / `bottom_score_widget` handles plus the owned
  `active_level_score`. The scratch-local `BorderInit` shell is removed.
- The pause bridge now reaches the prompt through
  `player.click_start.prompt`, and the state-2 gates name the existing
  `resume_requested`, `subgame_pause_gate`, `pause_fade`, `pause_fade_step`,
  `runtime_flags`, row-count, and mirror-front fields directly.
- These are ownership and layout clarifications, not register shaping.
  Focused Wibo remains 78.22% with the exact 1033/1033 instruction count,
  116 clean masked operands, and only the two already-documented state-table
  layout mismatches.

2026-07-13 path-template analysis owner closure:

- The Binary Ninja/IDA path-template campaign no longer declares a parallel
  `Game` aggregate for this receiver. Every field and helper on that shell is
  rooted at the authored `SubgameRuntime`/`cRSubGame` object.
- The old `pause_gate +0x74621` lane mixed root-object and subgame-relative
  coordinates. Since the subgame is embedded at root `+0x74618`, the real
  field is `subgame_pause_gate +0x09` on the receiver.
- The exact 0x4364-byte `Player` is now embedded at runtime `+0x3bb764`, ending
  at the first runtime cell at `+0x3bfac8`; the former flattened stopwatch,
  warning, and presentation aliases are retired. Cameraman, salt, sub-lazer,
  hover, and player backlinks all borrow `SubgameRuntime*` consistently.
- Binary Ninja declaration preview verifies the sparse analysis owner at exact
  size 0x1272838 and reverts without mutating the database. Matching source is
  unchanged: focused Wibo remains 78.22%, 1033/1033 instructions, with 116
  clean operands and the same two honest jump-table mismatches. The adjacent
  `update_subgoldy` baseline likewise remains 72.51%, 2067/2087, with its one
  existing follow-table mismatch.

2026-07-13 final runtime-tail closure: the analysis owner now exposes the
embedded `gui`, `galaxy`, rebuild selector, slug-voice cadence scalars, and
contact-target manager already used by this scratch, rather than hiding the
whole `+0x125ffd8..+0x12727d8` interval behind one byte array. The previewed
field chain closes exactly and leaves focused Wibo unchanged at 78.22%,
1033/1033 instructions, with 116 clean operands and the same two honest
jump-table mismatches.

2026-07-13 shared runtime-cell AI dispatch: the active SubLoc slot-zero call
now uses the shared `BodAiDispatch` ABI overlay instead of a scratch-local
virtual class. This preserves the explicit cRBod-compatible vtable word and
does not change focused output: 78.22%, 1033/1033 instructions, 116 clean
operands, and the same two honest jump-table mismatches.

2026-07-13 runtime-owner consolidation:

- The scratch-local `ActiveRuntimeRow` shell is retired. All row accesses now
  use `runtime_rows[cell_index]` and the canonical `SubRow` children:
  `row_model`, `projection_payload`, `attachment_body`, and `ring_speed`.
- The formerly raw root offsets are established `GameRoot` ownership:
  `render_skip_count`, `active_bod_list`, `star_manager`, `fade.state`,
  `intro.hide_for_replay_latch`, `intro.attract_reset_progress`, and player
  zero's current/saved front-end states.
- The Time Trial HUD record is exactly
  `sub_high_score.time_trial_route_records[level_mode_arg]` because
  `0x68b4c8 + 0x2b8c88 == 0x944150`. Direct owner access recovers the native
  index/address sequence and a further clean audited operand.
- The runtime-cell body now names `object` and `render_arg_20`; adjacent lanes
  use `SubLoc` pointer arithmetic, and the projected ring cell is explicitly
  the same lane six rows ahead (`6 * 8` cells). `RuntimeCellSlotBase` remains
  only to preserve VC6's native late `+0x3bfac8` displacement and register
  allocation, as documented above.

Focused Wibo improves from 78.22% to 79.75%. The candidate is 1036/1033
instructions with 117 clean masked operands, no unresolved operands, and only
the same two honest state-table identity mismatches. No score-only alias or
masked-operand waiver is introduced.

## 2026-07-14 runtime-cell base closure

Runtime cells now expose their real inherited `BodBase`: active checks and
list insertion use inherited `BodNode`, object/render fields stay on the same
base, and all anchor reads use `SubLoc::position`. The exact constructor and
0x54 stride preserve the main-loop scratch byte-for-byte at 79.75%, 1036/1033
instructions, with 117 clean operands and the same two honest table mismatches.

The native-shape `RuntimeCellSlotBase` now derives its leading extent from
`offsetof(SubgameRuntime, runtime_cells)`, and the one pause-path byte store
derives `subgame_pause_gate` the same way. This retains the late cell-base
displacement and byte-store scheduling documented above without repeating
`0x3bfac8` or `+9` as unowned layout facts. Focused metrics and audited
operands remain unchanged.

## 2026-07-14 cRSubPause owner closure

The state-3/4 pause branch now enters the authored `SubPause` embedded at
`SubgameRuntime +0x14`. Cross-port `cRSubPause::Init()` and
`cRSubPause::AI()` symbols, plus Android's three-pointer body layout, close the
0x0c-byte owner without changing the honest partial baseline: 79.75%,
1036/1033 instructions, 117 clean operands, and the same two table mismatches.

## 2026-07-14 runtime row-flag consumers

The row scan now names the model-present and parcel-spawn lanes, while the
ring dispatcher names all five authored ring modes and the explicit suppress
bit. These are `SubRow` flags; they are intentionally separate from the
adjacent `SubLoc::lane_and_flags` hazard/cache owner. Focused output remains
byte-identical at 79.75%, 1036/1033 instructions, prefix 9/1033, 117 clean
operands, and the same two table-identity mismatches.

## 2026-07-14 game-wide feature consumers

The row scanner now names the distinct game-wide gates for parcel requests,
health pickups, ambient garbage and salt, slug hazards, and default ramp
rings. These are `SubgameRuntime::runtime_flags` bits, not `SubRow` metadata.
Focused output remains byte-identical at 79.75%, 1,036/1,033 instructions,
prefix 9/1,033, 117 clean operands, and the same two table mismatches.

## 2026-07-14 ring kind producers

The row scanner now passes `SubRingKind` values instead of raw integers:
authored normal/power-up/explode/slow rows map to kinds `5/8/6/7`, ordinary
ramp rings map to default normal `4`, and explosive ramps map to kind `2`.
Focused output remains 79.75%, 1,036/1,033 instructions, prefix 9/1,033, 117
clean operands, and the same two table-identity mismatches.
