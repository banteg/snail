# `update_subgame` recovery notes

Target: `update_subgame @ 0x438b90` (`thiscall`, 3748 bytes, 1033 instructions).

This scratch reconstructs the outer gameplay state machine and the state-2 runtime update path rather than using a minimal placeholder. The source was shaped against both decompile exports and repeatedly measured with the VC6.5 `/O2 /G5 /W3` matcher toolchain.

`cRSubGame::garbage_frequency` at `+0x125ffd8` and `salt_frequency` at
`+0x125ffdc` are the normalized level-script spawn controls. The garbage lane
drives the 0.8..1.0 random threshold and the salt lane drives the 0.98..1.0
threshold; `build_subgame_level` seeds both and `complete_subgame` persists
both into the replay/high-score record. The corrected completion snapshots and
their two semantic source locals produce a focused 79.94% result
(`1036/1033`, `129` clean operands, and no unresolved, mismatched, or
unaudited masked operands).

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
`cRSubGame::runtime_rows`:

- `SubRow` stride: `0xf4` bytes;
- row flags: `+0x00`;
- embedded `RowModel`: `+0x04`;
- overloaded parcel projection payload: `+0x90`;
- embedded attachment `BodBase`: `+0xb0` (position at `+0xc0`);
- authored ring/effect speed: `+0xe8`;
- track cell stride: `0x54` bytes;
- four fringe-object pointers begin at the cell's `+0x44` lane.

`RuntimeCellSlotBase` deliberately preserves the indexed slot base and accesses the cell through its native `+0x3bfac8` displacement. A direct typed `cRSubLoc*` caused VC6 to fold that displacement too early and materially changed register allocation.

The runtime block includes plausible original insertion idioms for the two intrusive lists and semantic lanes for parcels, fringe objects, health pickups, speedups, jetpacks, garbage and salt hazards, slugs, and authored/ambient rings.

## Compiler-shape findings

Several source-level details were important rather than cosmetic:

- Reloading the fringe object after `get_track_skirt_color` removes an otherwise persistent pointer spill. This recovers the native `0x3c` frame, `ebp` row index, `edi` cell-offset base, and `ebx` zero value.
- The tile `29`/`30` path scores better as a nested block with an inner auxiliary-data test.
- The fringe selector is signed `cell_index % 8`; replacing it with `& 7` loses the target's signed modulus sequence.
- The four authored tile-35 ring variants converge on one shared last-ring-Z assignment.
- RNG calls are kept on the left side of comparisons where that produces the native operand ordering and clean call audits.
- Completion-source values are captured in semantic X/Y locals before either
  receiver field is written, preserving ownership while giving VC6 the closer
  native load/store schedule.
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

## Remaining differences

Focused matcher result: 79.94%, 1036 candidate instructions versus 1033 target
instructions, 9-instruction prefix, and 129 clean masked operands with no
unresolved, mismatched, or unaudited operands.

The first normalized instruction mismatch is the destination label of the
range-check `ja`; its semantics agree, but later block sizes give the target and
candidate labels different identities. Both switch jump-table operands are
content-audited as ordered local destinations rather than being compared by raw
label spelling.

The semantic structure and ownership are pinned. The remaining non-proof-grade
regions are:

1. residual state-1 configuration and galaxy-result register scheduling;
2. residual authored/ambient ring register scheduling;
3. residual HUD and handoff register scheduling;
4. residual branch-label identities driven by the remaining block layout.

## 2026-07-27 mobile-proven jump-table audit

Android `0x82214` and iOS `0x33a50` are exact-demangled
`cRSubGame::AI()` bodies for this Windows function. Both preserve the outer
state switch over `0, 1, 2, 3, 4, 7` and the nested mode switch over
`0, 1, 4, 7`, including the shared default/camera tails. That independent
source proves the case ownership and order; it does not justify rewriting the
Windows source merely to reproduce local labels.

The Windows and scratch tables instead differ only where surrounding blocks
change size:

- outer target: `b4,117,257,26,3f,d68,d68,4f`;
- outer candidate: `b4,117,256,26,3f,d6e,d6e,4f`;
- nested target: `14d,205,d68,d68,1a8,d68,d68,214`;
- nested candidate: `14c,204,d6e,d6e,1a8,d6e,d6e,213`.

For the nested table, all eight ordered destinations pair through the
whole-function normalized instruction alignment. The outer table has seven
such pairs; its remaining case begins at exact offset `+0x26`, where VC6 merely
schedules the state assignment and the following field load in opposite order.

The audit now evaluates each ordered destination independently: an exact
function-relative offset is accepted directly, while a shifted destination
must be backed by normalized instruction alignment. Equal table length and case
order remain mandatory, so this does not waive permutations or unproven
destinations. The source and 79.94% instruction score are unchanged; the audit
improves from `121 ok / 2 mismatch` to `123 ok / 0 mismatch`, with the same 12
honestly unaudited references.

## 2026-07-26 completion-snapshot ownership correction

The state-1 snapshot copies like-named configuration lanes into like-named
subgame lanes. Raw Windows instructions at `0x438cb3..0x438ccd` load
`g_runtime_config +0x40` (`g_challenge_speed_percent`) into
`cRSubGame +0x28`, then load `g_runtime_config +0x48`
(`g_challenge_difficulty_percent`) into `cRSubGame +0x2c`:

```asm
mov ecx, dword [0x4df958]
mov eax, dword [esi+0x40]
mov dword [esi+0x28], ecx
mov edx, dword [0x4df960]
add esp, 8
cmp eax, 7
fstp st(0)
mov dword [esi+0x2c], edx
```

The previous scratch crossed those sources solely because that spelling
resembled the target register schedule. That was a semantic error hidden by
partial sequence alignment: the audit paired one later same-key reference and
silently omitted other reference-bearing instructions. Two honest semantic
locals improve the score from 79.75% to 79.94% and restore X-to-X/Y-to-Y
ownership. The matcher now reports every unpaired reference instruction as
`unaudited`; this partial function currently has 121 paired references, 12
unaudited locations, and only the same two true jump-table mismatches.

## 2026-07-24 runtime-row active-list borrow

The state-2 row activation path now keeps its two ownership layers distinct.
`runtime_row_anchor->row.row_model` is the complete embedded `RowModel` owner,
while `GameRoot::active_bod_list.first`, its reload, and the newly installed
head are borrowed `BodNode*` values. Native instructions
`0x43905d..0x43909c` confirm that the root list stores only the zero-offset
inherited node and never takes ownership of the containing row.

Binary Ninja had promoted the two list-head reloads back into `RowModel*`,
producing false `body.bod.bod` traversals through the root list. The focused
`--update-subgame-only` replay pins the exact five MLIL lifetimes behind the
shared Bod and row-layout guards. IDA independently already renders the same
sequence as `BodNode **p_first`, `BodNode *first`, and `BodNode *list_prev`,
so no Ghidra tie-break is needed. This is analysis-only ownership recovery;
the matching source and its honest result are unchanged.

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
`cRSubGame::AI` directly and uses the shared
`cRSubGame` front-controller window for pause menu, challenge setup,
galaxy route, selected replay state, and rebuild selector fields. Focused Wibo
is unchanged at `67.53%`, `1046/1033`, prefix `9/1033`, with the same
`108 ok / 2 mismatch` masked audit. `spawn_track_speedup` remains a
member-style call surface on `cRSubGame` because this caller wants the
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
embedded `cRSubGame::galaxy` at `+0x1260020`, retiring the duplicate
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

## 2026-07-19 directional fringe-slot ownership

The state-2 runtime-cell consumer walks the four contiguous directional
`Fringe*` slots at `cRSubLoc +0x44..+0x50`. The cell owns those pointer
slots; each non-null `Fringe` remains borrowed from the embedded
`FringeManager`, is temporarily linked through
`cRSubGame::fringe_attachment_list_head`, and receives a copied skirt
colour through its inherited `BodBase::color`.

A narrow guarded Binary Ninja replay now pins eight lifetimes around that
operation: the slot cursor/count, current object, attachment-list successor and
flags, returned skirt colour, explicit post-call object reload, and destination
colour. The reload is visible in MLIL and independently required by the
matching scratch to preserve the native `0x3c` frame/register allocation; HLIL
folds it back into `*fringe_slot_cursor`. The corrected `tColour*` return local
now renders four named component copies instead of an `int32_t*` array.

All eight annotations survive reanalysis, and a second replay skips all eight
as already current. Matcher source is unchanged; this is ownership recovery,
not a score-shaping edit. The focused result remains exactly 79.75%,
1036/1033 instructions, prefix 9/1033, with 117 clean operands and the same two
honest jump-table mismatches. No fakematch was introduced.

2026-07-11 slug voice manager ownership: the state-2 update now calls the
embedded `cRSubGame::slug_voice_manager` directly. Android retains the
same owner/member as `cRSlugVoiceManager::AI()`, and the preceding exact
initializer closes the complete 0x0c-byte object. Focused output remains
78.22%, 1033/1033, with 116 clean operands and the same two honest jump-table
mismatches.

## 2026-07-30 state-one cross-port boundary

Android `cRSubGame::AI()` independently preserves four potentially
compiler-relevant state-one choices: it snapshots `level_mode` before the two
challenge configuration copies, keeps separate results for the two galaxy
calls and the challenge call, orders the nested cases numerically, and shares
the galaxy destroy and challenge/case-7 build-zero exits at source level. The
Windows decompile confirms the same semantic case destinations even though VC6
duplicates and schedules some of those tails.

Four recorded sweeps exercise all 18 bounded variants of those choices.
Mode-snapshot placement and every one-, two-, and three-branch result lifetime
combination are byte-identical to the retained source. Numeric case order,
shared build-zero, and three shared galaxy-destroy spellings regress to
`77.24%`-`78.98%` and lose one or more clean reference pairings. No variant
improves the score or creates a proof-quality tradeoff.

The current matcher audits all 129 reference operands cleanly at the retained
`79.94%` (`1036/1033`) result. The experiment ledger has four consecutive
non-winning sweeps, so the state-one residual is now bounded: it needs a new
Windows-specific lifetime or surrounding-block insight rather than more
cross-port case order, result ownership, or shared-label shaping.

2026-07-11 cRTutorial owner: the mode-7 tick now calls the embedded
`tutorial.update_tutorial()` directly. The exact Init/AI/UnInit siblings,
mobile symbols, and the native 0x1c size ledger prove the owner at `+0xa858`;
the local one-method `TutorialRuntime` shell is retired. Focused output remains
78.22%, 1033/1033, with 116 clean operands and the same two real table-shape
mismatches.

2026-07-13 runtime-row window and child-owner pass:

- `cRSubGame +0x20/+0x24` is the rolling runtime-row scan window, now
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
  rooted at the authored `cRSubGame`/`cRSubGame` object.
- The old `pause_gate +0x74621` lane mixed root-object and subgame-relative
  coordinates. Since the subgame is embedded at root `+0x74618`, the real
  field is `subgame_pause_gate +0x09` on the receiver.
- The exact 0x4364-byte `Player` is now embedded at runtime `+0x3bb764`, ending
  at the first runtime cell at `+0x3bfac8`; the former flattened stopwatch,
  warning, and presentation aliases are retired. Cameraman, salt, sub-lazer,
  hover, and player backlinks all borrow `cRSubGame*` consistently.
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

2026-07-13 shared runtime-cell AI dispatch: the active cRSubLoc slot-zero call
now uses the shared `BodAiDispatch` ABI overlay instead of a scratch-local
virtual class. This preserves the explicit cRBod-compatible vtable word and
does not change focused output: 78.22%, 1033/1033 instructions, 116 clean
operands, and the same two honest jump-table mismatches.

2026-07-13 runtime-owner consolidation:

- The scratch-local `ActiveRuntimeRow` shell is retired. All row accesses now
  use `runtime_rows[cell_index]` and the canonical `SubRow` children:
  `row_model`, `parcel_spawn_position`, `attachment_body`, and `ring_speed`.
- The formerly raw root offsets are established `GameRoot` ownership:
  `render_skip_count`, `active_bod_list`, `star_manager`, `fade.state`,
  `intro.hide_for_replay_latch`, `intro.attract_reset_progress`, and player
  zero's current/saved front-end states.
- The Time Trial HUD record is exactly
  `sub_high_score.time_trial_route_records[level_mode_arg]` because
  `0x68b4c8 + 0x2b8c88 == 0x944150`. Direct owner access recovers the native
  index/address sequence and a further clean audited operand.
- The runtime-cell body now names `object` and `render_arg_20`; adjacent lanes
  use `cRSubLoc` pointer arithmetic, and the projected ring cell is explicitly
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
base, and all anchor reads use `cRSubLoc::position`. The exact constructor and
0x54 stride preserve the main-loop scratch byte-for-byte at 79.75%, 1036/1033
instructions, with 117 clean operands and the same two honest table mismatches.

The native-shape `RuntimeCellSlotBase` now derives its leading extent from
`offsetof(cRSubGame, runtime_cells)`, and the one pause-path byte store
derives `subgame_pause_gate` the same way. This retains the late cell-base
displacement and byte-store scheduling documented above without repeating
`0x3bfac8` or `+9` as unowned layout facts. Focused metrics and audited
operands remain unchanged.

## 2026-07-14 cRSubPause owner closure

The state-3/4 pause branch now enters the authored `SubPause` embedded at
`cRSubGame +0x14`. Cross-port `cRSubPause::Init()` and
`cRSubPause::AI()` symbols, plus Android's three-pointer body layout, close the
0x0c-byte owner without changing the honest partial baseline: 79.75%,
1036/1033 instructions, 117 clean operands, and the same two table mismatches.

## 2026-07-14 runtime row-flag consumers

The row scan now names the model-present and parcel-spawn lanes, while the
ring dispatcher names all five authored ring modes and the explicit suppress
bit. These are `SubRow` flags; they are intentionally separate from the
adjacent `cRSubLoc::lane_and_flags` hazard/cache owner. Focused output remains
byte-identical at 79.75%, 1036/1033 instructions, prefix 9/1033, 117 clean
operands, and the same two table-identity mismatches.

## 2026-07-14 game-wide feature consumers

The row scanner now names the distinct game-wide gates for parcel requests,
health pickups, ambient garbage and salt, slug hazards, and default ramp
rings. These are `cRSubGame::runtime_flags` bits, not `SubRow` metadata.
Focused output remains byte-identical at 79.75%, 1,036/1,033 instructions,
prefix 9/1,033, 117 clean operands, and the same two table mismatches.

## 2026-07-14 ring kind producers

The row scanner now passes `SubRingKind` values instead of raw integers:
authored normal/power-up/explode/slow rows map to kinds `5/8/6/7`, ordinary
ramp rings map to default normal `4`, and explosive ramps map to kind `2`.
Focused output remains 79.75%, 1,036/1,033 instructions, prefix 9/1,033, 117
clean operands, and the same two table-identity mismatches.

## 2026-07-14 analysis receiver closure

The live Binary Ninja receiver was a stale same-size `Game*` named type. The
guarded catalog repair recreated only the exact known function as a
`cRSubGame*` method and preserved its sole user-defined receiver. The
tracked decompile drops from 90 raw receiver-offset expressions to 17 while
recovering the state machine, rebuild and replay selectors, player and
click-start children, runtime row and cell slabs, pickup/hazard pools, HUD, and
camera ownership. The remaining raw expressions are unresolved early scalars
and indexed row lanes; they are not evidence for the retired `Game` aggregate.

IDA's saved receiver lvar now agrees with its prototype and exposes the same
owner graph without `int this` arithmetic. This is analysis-only: the honest
focused frontier remains 79.75%, 1,036/1,033 instructions, 117 clean operands,
and the same two table-identity mismatches.

## 2026-07-14 control-prefix ownership closure

The first 0x28 bytes of `cRSubGame` now use the same producer/consumer
names in the matcher, both analysis headers, and both decompilers. This body
provides the main consumers for `resume_requested`, `subgame_pause_gate`,
`pause_fade`, `pause_fade_step`, and `scan_reset`; reset, initialization,
camera, pause-menu, and track-mirror helpers independently witness the other
prefix fields. The tracked BN/IDA exports no longer flatten these lanes into
padding or raw offsets.

This is analysis-only and leaves the honest 79.75%, 1,036/1,033 frontier and
its two table-identity mismatches unchanged. The nearby BodBase heads at
`+0x355c7c`, `+0x355cec`, and `+0x355d5c` still have no consumer beyond their
constructor writes, so they remain conservatively unnamed instead of being
assigned speculative owners.

The narrow Binary Ninja replay now batches its verified field and prototype
updates. The same ownership replay that previously reanalyzed after every
item completes in one analysis batch while preserving direct user types and
readback verification.

## 2026-07-15 shared front-end root ownership

IDA now composes the constructor-proven front-end block into the same
`GameRoot` used by the subgame tail. This function consequently reaches the
embedded `StarManager` and both `Intro` replay fields directly. The row and
cell induction registers remain byte offsets: treating them as `SubRow *` or
`cRSubLoc *` would invent ownership, so the replay deliberately leaves
them alone.

This is analysis-only. The honest focused frontier remains 79.75% at
1,036/1,033 instructions, with 117 clean operands and the same two jump-table
identity mismatches.

## 2026-07-17 runtime row/cell containing-owner replay

- The native row scan retains a borrowed `cRSubGame`-relative containing
  base at the `0xf4` row stride. Binary Ninja's exact EDI identity is
  `RegisterVariableSourceType / 1188 / 73`; IDA's register definition is
  `0x439035`, with the saved stack lifetime at `0x439038` / stack offset 76.
  Both now read back as `RuntimeRowStrideAnchor *`, exposing row flags, the
  primary and attachment bodies, projection payload, and attachment position.
- The eight-lane cell scan reuses EDI under the disjoint Binary Ninja identity
  `RegisterVariableSourceType / 1384 / 73`; IDA defines the same lifetime at
  `0x4390f9`. `RuntimeCellStrideAnchor *` keeps the native `0x54` cell stride
  while naming the current cell, the immediate previous/next lanes, same-lane
  neighboring rows, and the projected cell six rows (`0xfc0`) ahead.
- IDA's address-symbol collisions at `0x5ccac8`, `0x5ccacc`, `0x5ccad0`,
  `0x5ccb58`, `0x5ccb78`, and `0x5ccb88` are normalized only at the nine proven
  instructions. Replay then renders structure fields instead of unrelated
  `byte_`/`unk_` globals; the operand values read back unchanged.
- These are borrowed cursors into `cRSubGame`; neither lifetime owns or
  transfers any row, cell, body, or fringe allocation. No source change is
  justified by the metadata pass. The honest focused baseline remains 79.75%,
  1036 candidate versus 1033 target instructions, 117 clean masked operands,
  and the same two real jump-table target-identity mismatches.

## 2026-07-17 time-trial route-record cursor ownership

The mode-4 HUD path retains the native `game + level_mode_arg * 0x1fac0`
pointer before reading the persistent route record. Binary Ninja's exact EAX
identity is `RegisterVariableSourceType / 3386 / 66`; IDA defines the same
register lifetime at `0x4398cb`. Both now read back as
`TimeTrialRouteRecordCursor *` and render `record.active` plus the record's
score/time union instead of raw `+0x944150/+0x944158` loads.

The cursor's prefix aliases the enclosing `cRSubGame`; its terminal
`SubSolution` is the record already owned by
`SubHighScore::time_trial_route_records[level_mode_arg]`. It is not a second
record bank or a new allocation. The matching source already expresses that
primary owner, so no source edit is justified and the honest baseline remains
79.75%, 1036/1033 instructions, prefix 9/1033, 117 clean masked operands, and
the same two jump-table target-identity mismatches.

## 2026-07-24 parcel spawn-position consumer

The parcel activation path now consumes
`runtime_rows[cell_index].parcel_spawn_position`. The runtime-grid builder
initializes this row-owned vector from authored parcel-local coordinates, and
the normal/challenge placers convert it to world space before setting
`SUBROW_FLAG_PARCEL_SPAWN_REQUESTED`. This helper then passes the same address
to `spawn_track_parcel`, whose parameter is independently recovered as
`Vector3* world_position`.

That final handoff closes the `SubRow +0x90` field's ownership and rules out a
generic projection payload. The rename is layout- and codegen-neutral:
focused Wibo remains 79.75%, 1036/1033 instructions, with 117 clean operands
and the same two jump-table identity mismatches.

## 2026-07-25 replay-exit root lifetime

The replay-exit fork uses EAX for two unrelated values: the persistent branch
loads the previous integer `GamePlayer::frontend_state`, while the
non-persistent branch reloads `g_game_base` before storing state 27. Binary
Ninja merged those sibling definitions and rendered only the latter write as
raw `GameRoot +0x1b8`.

The replay now splits the pointer-producing definition at `0x4399b8`
(`RegisterVariableSourceType / 3624 / 66`) and types only that lifetime as
`GameRoot *`. Both branches consequently expose
`GamePlayer::saved_frontend_state` and `frontend_state`, matching IDA and the
exact source without falsely retyping the sibling integer. This is
analysis-only; the honest 79.75%, 1036/1033 frontier and its two jump-table
identity mismatches remain unchanged.

## 2026-07-27 dual-mobile ring dispatch

Android and iOS `cRSubGame::AI()` preserve the same four-bit absence ladder as
the Windows row-event path. The first available bit wins in this order:
normal ring -> kind 5, power-up ring -> kind 8, explode ring -> kind 6, and
slow ring -> kind 7. iOS selects one kind before one shared AddRing call;
Android converges four branches on its call. Together they prove the authored
ring-kind semantics and priority without transferring either port's compiler
layout.

Two natural Windows probes were measured and removed. Selecting a shared kind
before one spawner call regressed focused Wibo from 79.94% to 58.14%; spelling
the priority as an explicit nested absence ladder reached only 78.40%. The
retained Windows source is therefore still the best honest VC6 shape.

## 2026-07-28 dual-mobile ring-speed ownership

The eight Windows loads feeding `spawn_track_ring_or_special_effect` use the
same strength-reduced address:

`game + ((row + (row * 3 + 0x12414) * 0x14 + 0x615c) << 2)`

Expanding it gives `game + 0x5ccbb0 + row * 0xf4`, exactly
`cRSubGame::runtime_rows[row].ring_speed` because `runtime_rows` begins at
`+0x5ccac8` and `SubRow::ring_speed` is `+0xe8`. IDA 9.4 already renders that
owner. Android `cRSubGame::AI()` at `0x82214` and iOS `cRSubGame::AI()` at
`0x33a50` independently pass their corresponding current-row scalar to
`cRSubGame::AddRing`, corroborating the authored relationship without
transplanting either mobile layout into Windows.

VC6 never materializes a `SubRow*` for these accesses: it leaves the row
calculation as a dword index and loads through `[game + index * 4]`. Retyping
that integer as a row pointer would be false ownership. The Binary Ninja replay
therefore attaches byte-guarded comments to the eight exact load instructions
instead. The generic narrow-sync layer now supports transactional, read-back
verified instruction comments, so future non-materialized owners can be
preserved without fakematching or fake pointer lifetimes. This is analysis-only
and leaves the honest focused frontier unchanged at 79.94%, 1036/1033
instructions, 123 clean operands, and the two jump-table identity residuals.

## 2026-07-30 transfer-aware reference audit

The ordered memory-transfer audit now pairs the remaining same-field accesses
across x87 and integer register allocation without changing the source or
normalizing their instructions as equal. The focused frontier stays 79.94%,
1036/1033 instructions, prefix 9/1033, while all 129 masked-reference sites
are now audited and clean. The earlier two one-sided audit residuals were
alignment debt, not different jump-table targets or missing owners.

## 2026-08-09 outer-state bridge and Windows lifetime boundary

The replay-exit tail is already byte-for-byte native once its function-relative
displacement is ignored. The target sequence at `+0xdf4..+0xe62` and candidate
sequence at `+0xdfa..+0xe68` have the same loads, saved/current state copies,
literal `26`/`27` publications, attract-reset comparison, and epilogue. The
six-byte shift is accumulated earlier in the state-2 body; it is not evidence
for a different replay-exit owner or control-flow shape.

Three exact neighboring scratches close the outer-state contract:

- `update_frontend_state_machine` is 100.00%, 180/180 instructions, and proves
  state 26 as `UnInit -> restore saved`, state 27 as
  `UnInit -> Init -> restore saved`, state 28 as
  `UnInit -> selector 0 -> Init -> restore saved`, and state 29 as the
  initialize-and-fall-through entry to state-30 thanks-screen updates;
- `destroy_subgame` is 100.00%, 246/246 instructions, and proves that a
  persistent replay overwrites `saved_frontend_state` with state 18 while
  clearing the persistent latch;
- `update_subgoldy_resurrect` is 100.00%, 76/76 instructions, and proves the
  saved-current-state copy followed by state 28 for an ordinary resurrection.

Together with the native completion-exit producer, this makes the seemingly
generic saved-state copy precise. `update_subgame` publishes state 26 for a
persistent replay, whose teardown redirects to state 18, and state 27 for a
transient replay, whose teardown/rebuild restores the saved gameplay owner.
The last-galaxy completion producer stores state 29 before publishing state 26;
after teardown the exact outer dispatcher enters the state-29/state-30 thanks
screen pair.

The recorded `replay-exit-owner` sweep bounds six natural source spellings.
Decimal constants, branch-local `GameRoot*`/`GamePlayer*` borrows, and one
common player borrow are codegen-neutral at 79.94%. Hoisting the duplicated
saved-state copy regresses by 19 fuzzy bytes, while selecting state 26/27 into
one local regresses by 23 fuzzy bytes and leaves one reference unaudited. The
explicit sibling branches are therefore retained; collapsing them would erase
both native layout evidence and the distinct teardown semantics.

One additional Windows-witnessed state-one sweep tested all six placements of
the challenge-speed store, `level_mode` snapshot, and challenge-difficulty
load/store that were not covered by the earlier mobile-oriented lifetime
sweep. Every form produced the same 79.75% result, seven fuzzy bytes below the
retained source, while keeping all 129 references clean. This rules out that
config/mode interleaving as the missing Windows lifetime. No matching source
change is retained: the focused frontier remains 79.94%, 1036/1033
instructions, prefix 9/1033, with 129 clean references and no unresolved,
mismatched, or unaudited operands.

## 2026-08-09 authored-ring argument-lifetime boundary

The Windows tile-35 path keeps the four authored kinds as distinct branches.
After the row flags load at `0x439565`, the native tests normal, power-up,
explode, and slow at `0x439587`, `0x4395af`, `0x4395d7`, and `0x4395ff`.
Each arm independently forms `runtime_rows[cell_index].ring_speed`, borrows
the embedded Player, and publishes its kind before jumping to the single
cell-argument tail at `0x43983d`. That tail forms `&cell_slot->cell`, calls the
exact `spawn_track_ring_or_special_effect` at `0x439846`, reloads the cell Z at
`0x43984b`, and stores `player.last_ring_spawn_z` at `0x439851`.

The exact 100.00%, 347/347 callee at `0x43df10` independently closes the ABI as
`(cRSubLoc* cell, int kind, Player* player, float ring_speed)`. This makes the
four native branch inputs real short borrows, not an inferred shared argument
pack or a long-lived row owner.

Two recorded five-variant sweeps bound the natural C++ lifetime spellings.
Branch-local `cRSubLoc*` and `Player*` aliases are byte-identical to the
retained source at 79.94%. Hoisting a cell pointer/reference across the ladder
falls to 72.31%, hoisting the Player falls to 72.23%, and pairing the two falls
to 74.47%. Branch-local ring-speed values fall to 71.95%; the common call-only
cell pointer also reaches only 71.95%. Every regressive form loses at least one
clean reference pairing or creates unaudited sites.

The source therefore already expresses the correct authored lifetimes:
distinct branch-local arguments whose identical call suffix VC6 partially
tail-merges. No source change is retained, and no shared kind, common owner,
float spill, or register hint is justified. Focused output remains 79.94%,
1036/1033 instructions, prefix 9/1033, with all 129 references clean. Canonical
source SHA-256: `8829bbf7f6800ae3c0172c02d0c5a488a29733843358f626ff20ee6f6cabd7a0`.
