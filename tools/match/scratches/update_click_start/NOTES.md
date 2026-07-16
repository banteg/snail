# update_click_start

First structured scratch for `update_click_start` @ `0x442290`.

Match status: exact, 138/138 instructions with full prefix and all 24 masked
operands clean. No fakematching.

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

Previously resolved residual:

- the earlier partial already used the same five-entry jump-table dispatch and
  138-instruction budget, but differed around the replay-record flag update;
- before the final layout correction, the candidate jump table remained a
  local compiler symbol whose shifted case destinations could not be proved;
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
`current_high_score_record.run_records[cursor]`; the 16-bit `flags` owner is
ORed with `0x20` and then has bit zero cleared, while
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

## 2026-07-14 analysis ownership synchronization

The proven five-value `ClickStartState` now propagates through the shared
analysis header and the narrow Binary Ninja field replay at owner `+0x80`.
The same replay now preserves the complete high-confidence tail, including the
borrowed `owner_player` backlink at `+0x98`, instead of its stale generic
`player` alias.
State one remains explicitly `UNKNOWN_1`: neither Windows nor the available
mobile writers justify a stronger name. Matcher source and the honest 84.06%,
138/138-instruction partial are unchanged.

## 2026-07-15 replay dispatch ownership

The two launch-gate tests now read
`SubgameRuntime::replay_launch_active` directly instead of preserving an
authored-looking but unsupported scratch local. VC6 folds those reads into the
native `dl` lifetime around the borrowed replay record, including the native
`ebp` save/restore and the second `test dl, dl`. This raises the focused match
from 84.06% (138/138) to 90.65% (140/138), with all 23 ordinary masked
references still clean.

The native five-entry table at `0x4424ec` is now tracked as
`update_click_start_state_jump_table`. Independent image inspection gives
entries `0x4424ea`, `0x4424ea`, `0x4422d8`, `0x4423f4`, and `0x44243f`, mapping
states 0/1 to the common return and states 2/3/4 to the three recovered bodies.
The matcher therefore reports one content-audited table mismatch instead of an
unresolved compiler-local symbol: the candidate's two extra byte load/store
instructions shift every later table destination by four bytes.

The remaining difference is the already-pinned replay-record byte-OR idiom:
native uses a direct memory `or`, while contextual VC6 compilation emits
load/or/store. Typed record pointers, a flattened byte lane, explicit casts,
signedness, and a 16-bit union view were neutral or worse and were rejected.
No alias, volatile qualifier, synthetic control flow, or local table alias was
kept to hide the mismatch.

## 2026-07-16 replay flag-word closure

The paired compact loader proves that the expanded `ReplayRunRecord +0x04`
lane is one 16-bit `flags` owner: it zero-extends a compact byte and stores a
word. The exact initializer independently clears the same lane as one of three
consecutive words. Compact serialization intentionally persists only its low
byte.

Using that recovered member directly lets VC6 emit the native memory byte-OR
followed by the word AND. `update_click_start` is now exact at 138/138
instructions with full prefix and all 24 masked operands clean, including the
audited five-entry jump table. The source lost an aliasing cast; no scheduling
hint or fakematch was added.
