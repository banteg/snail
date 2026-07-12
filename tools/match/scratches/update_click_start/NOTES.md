# update_click_start

First structured scratch for `update_click_start` @ `0x442290`.

Match status: 27.18%, 138 target instructions, 149 candidate instructions, 13
masked operands all resolved. No fakematching.

Recovered relationships:

- `ClickStart` is the exact authored `cRClickStart` RenderableBod owner with state at `+0x80`,
  prompt widget at `+0x84`, teardown progress/step at `+0x88/+0x8c`, owner
  player at `+0x98`, and prompt-hide latch at `+0xa8`;
- state `2` accepts either the app replay-launch scratch at `game+0x1066be8`
  or a live input confirm edge (`input.pressed_buttons & 0x4000`);
- accepted startup writes `Player+0x304`, recenters authored input pointers for
  slots 0 and 1, and plays SFX `8`;
- states `3/4` kill the prompt, move the embedded render transform, and recycle
  the owner through the shared BOD free-list path.

Residual mismatch:

- native uses a direct jump table for states `0..4`; this scratch still lowers
  the state dispatch as a compare chain and saves extra callee registers;
- the replay-start body is kept in raw `g_game_base` form because that improved
  the local shape, but the app replay-launch globals need a wider owner before
  they should be promoted.

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
