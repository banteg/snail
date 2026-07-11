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
- Completion initializes the embedded `SubgameRuntime::completion` immediately on the state `5`
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
  delivery. It still needs a second callsite before promotion into a shared
  owner.

Focused match:

- 2026-06-18 initial: 44.67%, 505 target instructions versus 480 candidate
  instructions.
- 2026-06-18 local-lifetime correction: 46.29%, still 505 target instructions
  versus 480 candidate instructions, with 33 masked operands OK, two unresolved
  relocation artifacts, and one real alignment mismatch. Hoisting the two
  recurring camera matrices and three vector temporaries to function scope
  moves the generated frame from `0x9c` to `0xa8` and lines up the state-8
  matrix/vector stack slots with native.
- Native code order is `1/2`, `8`, `9`, `10/11`, `12`, `5/6`, `7`; keeping that
  source order improves alignment over the decompiler's displayed case order.
- Main remaining shape gaps are stack frame size/temporary placement
  (`0xe8` native versus `0xa8` candidate), register allocation for the shared
  `-1`/`0.00833333377f` constants, and matrix/vector staging inside the
  death/completion interpolation legs.
- Rejected probes: swapping the two matrix locals for states `11`/`6` regressed
  to 38.17%, and a shared `float` local for `0.00833333377f` produced no score
  movement or saved-register constant hoist.

2026-06-20 switch-table audit: the cutscene state table at `0x446e00` is now
named `update_cutscene_state_jump_table` with candidate alias `$L2639`.
Focused Wibo remains `46.29%`; the switch table is a real layout mismatch.

2026-06-20 offset audit: `0x42fec4` is now named
`g_player_intro_cutscene_latch_offset` (`g_player_block + 0x148`). Native clears
the byte on the intro close-in camera leg; no consumer has been recovered yet, so
the Player field stays conservatively named `intro_cutscene_latch`. Masked audit
is now `34 ok / 0 unresolved / 2 mismatch`.

2026-07-11 owner closure: the mode read now comes from
`GameRoot::subgame.level_mode`; removing `CompletionGameView` is codegen-neutral
at 46.29%.

2026-07-11 cRCompletion owner recovery: state 5 now calls
`game->subgame.completion.initialize_completion_screen(...)` directly. The
receiver is the same 0x50-byte owner proven by cRCompletion AI/UnInit/
RegisterParcel, rather than a standalone root-level result screen. This source
shape raises the focused match from 46.29% (480/505, 34 clean operands and two
mismatches) to 68.97% (481/505, 55 clean operands and one real jump-table
mismatch). The gain is retained as ownership evidence, not tuned padding.
