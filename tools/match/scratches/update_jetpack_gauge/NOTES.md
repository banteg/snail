Current recovery: **exact**, 131/131 instructions over 490 native bytes, with
all 34 masked references clean. The September 5 recovery supersedes earlier
state-dispatch and completion-owner residual claims.

# update_jetpack_gauge @ 0x43a390

Source-shaped partial scratch for the jetpack countdown/warning controller.

Current match: 94.66% (`131/131` candidate/target instructions,
`34` clean masked operands).

Recovered behavior:

- native treats state `0` and non-`1` states as immediate returns; only state
  `1` advances `progress` by `progress_step`;
- it ends hover and clears the controller when progress exceeds 1.0 or the
  player passes `game->completion_row_start - 5`;
- it ramps warning intensity at the start, holds it through the middle range,
  and fades it out after `0.94`;
- while in the middle range it samples the current runtime row through
  `cRSubGame::RowFromPos(game+0x42fde4)` on the owner at `game+0x74618` and forces
  `progress = 0.94` when `BYTE1(row->flags) & 0x80` is set, i.e. the 32-bit
  flag mask is `0x8000`;
- once active, it updates wobble x/y/alpha and calls the one-instruction
  `spawn_track_speedup` address with the authored `cRSubHover::Hover`
  `(Vector3&, float)` receiver/signature.

Important corrections made during matching:

- inactive state `0` does not call `end_jetpack_hover`; it returns before any
  cleanup;
- the `0.94` middle/fade branch is naturally expressed as `> 0.94` first, then
  the middle hold branch;
- the empty `spawn_track_speedup` target is `ret 8`; cross-port evidence now
  proves the hover call is a real `SubHover` member alias, so the former fake
  derived caller view is retired.

Known residuals:

- native spells the first inactive-state comparison as `sub eax, edi`, while
  the candidate uses the equivalent `cmp eax, edi`;
- `game`/`player` loads around the completion-row check use different registers,
  though the field offsets and behavior are aligned.

2026-06-20 type cleanup: the jetpack presentation receiver is intentionally a
scratch-local `UpdateJetpackPresentationView`, paired with
`ArmJetpackPresentationView` in `arm_jetpack_gauge`. That removes the false
shared unresolved-layout row without promoting any unproven
authored `Snail` fields. Rebuilt matcher stays at 85.82% with
34 clean masked operands; `arm_jetpack_gauge` remains exact at 18/18.

2026-06-20 state-dispatch retry: spelling the state gate as an explicit
`live_state` ladder recovers native's early `xor edi, edi` before testing the
controller state and improves focused Wibo to `85.93%`, with prefix `6/131`
and the same 34 clean masked operands. VC6 still uses `cmp eax, edi` plus a
separate `test eax, eax` after `dec eax`, while native reuses flags from
`sub eax, edi` and `dec eax`; a `switch (state - zero)` spelling regressed to
`84.29%` and disturbed the progress-add x87 order, so keep the ladder.

2026-06-21 subgame owner typing: `SubHover::game` is now typed
as `cRSubGame*`, and the global row-sampler cast uses the same shared
runtime view at `g_game_base + 0x74618`. This removes the scratch-local
generic `Game` shell without moving the codegen; focused Wibo remains at
`85.93%`, `132/131`, prefix `6/131`, with 34 clean masked operands.

2026-07-11 player/root ownership closure: `SubHover::player` is
the borrowed containing `Player*`; the completion check reads its real
`position.z`. Global presentation and row-sampler paths now resolve through
`GameRoot::subgame` and its embedded player, retiring
`PlayerForJetpackGauge` and `UpdateJetpackPresentationView`. Focused Wibo is
unchanged at `85.93%`, `132/131`, prefix `6/131`, with 34 clean masks.

2026-07-11 authored-owner closure: Android and iOS identify the entire method
as `cRSubHover::AI()`. Android matches the Windows state/progress fields,
borrowed parent pointers, warning curve, wobble outputs, JetUnInit edge, runtime
row flag, and final `Hover(tVector&, float)` call. The exact owner is 0x214
bytes at `Player +0x2750`; the stable Windows function names remain unchanged.
Replacing the fake derived no-op caller with the typed SubHover member call is
codegen-neutral at the same honest 85.93% with 34 clean masks.

## 2026-07-14 JetPack row flag

The auto-shutoff test now consumes `SUBROW_FLAG_JETPACK_OFF`, copied from the
authored `JetPack=Off` metadata lane. It belongs to `SubRow::flags`; the same
numeric `0x8000` in the separate `cRSubLoc::lane_and_flags` owner is unrelated.
Focused output remains 85.93%, 132/131 instructions, prefix 6/131, with all 34
operands clean.

## 2026-07-14 hover lifecycle ownership

The native early ladder and teardown store now name
`SUB_HOVER_STATE_INACTIVE`; the only armed value is
`SUB_HOVER_STATE_ACTIVE`. This preserves the deliberate VC6 ladder shape and
the honest 85.93%, 132/131-instruction partial, prefix 6/131, with all 34
operands clean.

## 2026-07-18 durable SubHover replay

The focused Binary Ninja and IDA replay now pins this function as authored
`void __thiscall(SubHover*)`, verifies the exact 0x214-byte receiver, and loads
the complete 0xb4-byte Sprite dependency used by the sibling jet methods. Both
tracked decompilers now expose `progress`, `state`, `game`, `player`, wobble,
warning, and root-owned snail presentation paths through their real owners;
the stale `cRDamageGuage` artifact description is gone. This is analysis-only
ownership recovery: focused Wibo remains honestly 85.93%, 132/131, prefix
6/131, with all 34 masks clean and no source or fakematch change.

## 2026-07-29 active-state dispatch recovery

The native opening `sub; je; dec; jne` is a two-stage state gate, not evidence
for a third lifecycle state. Keeping the real zero lifetime for teardown,
testing the inactive state first, and then dispatching the remaining value
through an active-only switch removes the candidate's redundant
`test eax, eax`. Focused matching rises from 85.93% (`132/131`) to 94.66%
with exact `131/131` instruction parity and all 34 references still clean.

Six recorded sweeps cover 47 source-shaped variants: predecrement and
short-circuit ladders, direct and zero-adjusted switches, mixed inactive
gates, completion-owner and finish-control forms, and the three-float wobble
owner. Four mixed-gate variants improve, 25 variants are byte-identical to
their baselines, and 18 regress. The retained
`live_state -= zero; if (!live_state) return; switch (live_state)` form is the
best at 94.66%.

After that improvement the diff is confined to two regions. The opening has
only native `sub eax, edi` versus candidate `cmp eax, edi`; both share the
same following `je; dec; jne`. The completion-row gate has the same typed
`cRSubGame` and `cRSubGoldy` loads rotated across EDX/ECX/EAX. Nine owner and
threshold lifetimes plus eight short-circuit/control variants leave that
region byte-identical or worse.

Windows' downstream camera expression proves the contiguous `+0x14`, `+0x18`,
and `+0x1c` lanes are local-space X/Y/Z wobble coefficients. Typed pointer and
reference component views compile identically, while four aggregate-zero
forms regress to 67–69% by introducing a different frame/copy family. The
scalar component stores remain the honest source shape; neither aggregate
assignment nor another state-syntax permutation is justified for the two
remaining compiler-allocation differences.

## 2026-08-09 authored cRSubHover surface

`cRSubHover` is now the primary shared owner, with `SubHover` retained only as
the Windows-analysis compatibility typedef. The seven lifecycle scratches
define the authored `Init`, `On`, `End`, `AI`, `JetInit`, `JetUnInit`, and
`Jets` methods and select their exact VC6 decorated symbols in `scratch.conf`.

Live Binary Ninja xrefs in the Windows image retain the complete caller graph:
Goldy initialization calls `Init`, collision calls `On`, Goldy AI calls `AI`,
presentation calls `Jets`, `AI` calls `End`/`JetUnInit`, and `On` calls
`JetInit`. The `AI` call at `0x43a536` still shares the folded `0x43d880` body
with `cRSubGame::AddSpeedUp`; Android's separate `Hover(tVector&, float)` body
supplies that authored spelling.

The type/symbol promotion is codegen-neutral: all six exact siblings remain
exact, while `AI` remains at 94.66%, 131/131 instructions, with all 34 masked
operands clean. None of the 47 recorded state, threshold, completion-owner,
or wobble-lifetime variants was reopened.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and both mobile
`cRSubHover::AI()` bodies establish the complete lifecycle: active-state gate,
progress and finish thresholds, Player/SubGame borrows, row-controlled jetpack
shutoff, warning curve, wobble outputs, presentation/particle teardown, and
final hover callback. All 131 instructions and all 34 references are
represented.

The remaining 94.66% delta is one equivalent `sub`/`cmp` flag source and a
rotation of the game, player, and threshold registers. It leaves no lifecycle
state, field, or owner unresolved, and experiment history does not limit the
classification.

## 2026-09-05 expression lifetime probe

A six-form whole-body state-dispatch probe recovers the native opening subtraction when the active body remains inside the switch. This improves to 95.42%; the completion-owner register rotation remains under investigation.

## 2026-09-05 whole-switch and comparison source recovery

Keeping the active body inside the state switch reproduces native's opening
`sub; je; dec; jne` sequence, improving 94.66% to 95.42%. The previous source
split dispatch from its body and compiled the subtraction as a comparison.

Within that switch, `player_z > (float)(completion_row_start - 5)` recovers
the EDX/ECX/EAX completion-check lifetimes and reaches 100%. The native integer
subtraction, x87 comparison, both exit conditions, and all references remain
unchanged. No state, owner, ABI, or compiler assumption needed changing.

The ledgers preserve six whole-body switch forms, nineteen completion/wobble
expression interactions, and two threshold forms. The double-conversion
alternative regressed; the final source retains the original float conversion.
