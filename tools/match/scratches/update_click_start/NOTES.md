# update_click_start

First structured scratch for `update_click_start` @ `0x442290`.

Match status: 84.06%, 138 target instructions, 138 candidate instructions,
prefix 5/138, with 23 masked operands resolved and the candidate-local jump
table symbol left honestly unresolved. No fakematching.

Recovered relationships:

- `ClickStart` is the exact authored `cRClickStart` RenderableBod owner with state at `+0x80`,
  prompt widget at `+0x84`, teardown progress/step at `+0x88/+0x8c`, owner
  player at `+0x98`, and prompt-hide latch at `+0xa8`;
- the state lane is now closed as inactive `0`, unknown/reserved `1`, waiting
  for start `2`, accepted/pending `3`, and teardown `4`; no Windows or mobile
  writer gives state `1` a stronger semantic name;
- state `2` accepts either the app replay-launch scratch at `game+0x1066be8`
  or a live input confirm edge (`input.pressed_buttons & 0x4000`);
- accepted startup writes `Player+0x304`, recenters authored input pointers for
  slots 0 and 1, and plays SFX `8`;
- states `3/4` kill the prompt, move the embedded render transform, and recycle
  the owner through the shared BOD free-list path.

Residual mismatch:

- native and candidate now use the same five-entry jump-table dispatch and the
  same 138-instruction budget; the remaining state-2 differences are register
  allocation around the replay-record test and the byte flag update;
- the candidate jump table is a local compiler symbol, so the matcher cannot
  yet prove it is the native table even though the dispatch entries and case
  order agree;
- `GameRoot::backdrop.unknown_660` is the exact owner of the byte raised on
  waiting-state entry, but this is its sole Windows reference, so its role
  remains deliberately unnamed.

2026-07-11 pause-owner closure: the prompt-hide gate now reads
`GameRoot::subgame.subgame_pause_gate`; removing the synthetic `GamePauseView`
is codegen-neutral at 27.18%, 149/138 instructions, prefix 1/138, and 13 clean
masked operands. The separate replay-start block remains raw here pending a
source-shape pass; this change does not claim new ownership for it.

2026-07-12 authored-owner closure: Android and iOS map this body to
`cRClickStart::AI()`. Android independently preserves the prompt hide lane,
state-2 replay/input handoff, parent startup-index write, pointer recenter,
SFX 8, state-3 random seed and teardown setup, and state-4 BOD removal. Its
RenderableBod base is 0x0c bytes smaller, while every tail field keeps the same
relative order. The exact Windows type/parent substitution is codegen-neutral
at the honest 27.18%, 149/138 instructions, with 13 clean masks. Removing the
explicit range guard or replacing early returns with breaks was neutral or
worse and still produced a compare tree, so no jump-table fakematch was kept.

2026-07-12 replay/root ownership pass: the state-2 handoff now uses the exact
`SubgameRuntime::replay_launch_active`, `replay_launch_record`, and
`replay_update_cursor` fields. Live input records are addressed through
`current_high_score_record.run_records[cursor]`; the low-byte `flags` view is
ORed with `0x20`, the intentional 16-bit view clears bit zero, and
`current_high_score_record.source_tail` receives the cursor. State 3 seeds the
RNG from `current_high_score_record.runtime_build_seed`. Prompt teardown and
BOD recycling now use `GameRoot::border_manager` and `active_bod_list`.

At that stage all substitutions were codegen-neutral at 27.18% (149/138,
prefix 1, 13 clean masks), and the native jump-table lowering remained the
honest structural blocker. The pass below supersedes that source shape.

## 2026-07-14 state-machine and lifecycle recovery

The authored five-state control flow is now expressed with named labels behind
the source `switch`. MSVC emits the native `cmp`/`ja`/five-entry jump-table
dispatch, preserving the observed state-2, state-3, and state-4 address order.
The acceptance path is expressed positively: replay launch accepts record flag
`0x20`, while live launch requires the visible prompt and the input edge.

State-4 recycling now uses the shared `BodList::remove_bod` owner instead of a
second handwritten transcription. Independent cursor reads for the byte and
word replay-flag updates recover the native 138-instruction budget. The result
moves from 27.18% (149/138) to 84.06% (138/138), with prefix 5/138 and no
masked-reference mismatch.

`ClickStartState` records the four proven roles and deliberately retains
`CLICK_START_STATE_UNKNOWN_1`. The back-pointer at `+0x98` is now
`owner_player`, and all known player/subgame consumers use
`CLICK_START_STATE_WAITING_FOR_START` rather than a bare `2`. Exact
`initialize_click_start` remains 79/79. No volatile qualifier, synthetic
branch, register-shaped helper, or other fakematch was retained.
