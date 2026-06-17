# update_cutscene @ 0x4466d0

First structural recovery for `CutsceneAI::update_cutscene`.

Recovered relationships:

- `CutsceneAI::state` drives the `1 -> 2 -> 8 -> 9` intro path, `5 -> 6 -> 7`
  completion path, and `10 -> 11 -> 12` death path.
- `camera_mode`, `live_matrix`, `progress`, `progress_step`, and
  `force_camera_update` are confirmed members on the `CutsceneAI` inline object.
- `PlayerPresentationController::snail_hotspots_world[12]` is the completion
  skid-stop source and `snail_hotspots_world[18]` is the recurring intro-talk
  look-at anchor.
- Completion initializes `CompletionResultScreen` immediately on the state `5`
  entry handoff while entering state `6`, then plays SFX `46`.
- Death entry plays voice set `3`, releases snail weapons, and later falls back
  to voice set `11` if `initialize_subgoldy_death` does not consume the gate.
- Completion entry writes the invincible-shell cutscene roll pair at
  `presentation +0x192c/+0x1930` (`cutscene_roll_progress/step`), not the
  regular wobble phase fields at `+0x15bc/+0x15c0`.

Kept local for now:

- `Player +0x200` is copied as the blend source matrix in states `6`, `8`, and
  `11`. The scratch uses a local accessor until another writer/consumer confirms
  the member name.
- `g_game_base +0x2247f8` is the target-count comparison used for perfect
  delivery. It needs a second callsite before promotion into `CompletionGameView`.

Focused match:

- 2026-06-18: 44.67%, 505 target instructions versus 480 candidate
  instructions.
- Native code order is `1/2`, `8`, `9`, `10/11`, `12`, `5/6`, `7`; keeping that
  source order improves alignment over the decompiler's displayed case order.
- Main remaining shape gaps are stack frame size/temporary placement
  (`0xe8` native versus `0x9c` candidate), register allocation for the shared
  `-1`/`0.00833333377f` constants, and matrix/vector staging inside the three
  interpolation legs.
