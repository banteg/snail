# initialize_click_start

`initialize_click_start` @ `0x442170` seeds the subgame "Click to Start"
owner. It allocates the prompt widget, links the owner into the active BOD
list, resets the player-side startup/replay index at `Player+0x304`, and hides
the prompt immediately when the app replay-launch scratch is active.

Match status: 100.00%, 79/79 target instructions, 13 masked operands all
resolved. No fakematching.

Recovered relationships:

- the owner is a `RenderableBod` subclass; `update_click_start` later moves the
  embedded transform at `+0x38`;
- active-list flags reuse the shared BOD semantics: `0x200` linked,
  `0x40` iterator guard;
- the borrowed parent at owner `+0x98` is the real `Player*`; Android and iOS
  expose the authored signature `cRClickStart::Init(cRSubGoldy*)` and perform
  the same parent `startup_track_index` clear;
- the complete Windows child is exactly 0xac bytes at `Player +0xa0`, ending
  immediately before `Player::row_event_cutscene_started` at `+0x14c`.

Source-shape note: the active-list insertion wants the same native-looking
pointer reload idiom as nearby BOD owners, including the temporary
`current->list_prev` readback before assigning the list head.

2026-07-12 authored-owner closure: `ClickStartController` and the synthetic
`ClickStartPlayer` prefix are retired in favor of exact `ClickStart` and its
borrowed `Player*`. Focused Wibo remains exact at 79/79 instructions.

2026-07-12 root/replay owner closure: prompt allocation now uses the exact
`GameRoot::border_manager`, active-list insertion uses
`GameRoot::active_bod_list.first`, and the initial hide decision reads
`SubgameRuntime::replay_launch_active`. These typed substitutions preserve the
exact 79/79 instruction match and close the initializer's remaining raw root
offsets.
