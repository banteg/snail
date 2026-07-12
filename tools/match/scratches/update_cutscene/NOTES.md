# update_cutscene @ 0x4466d0

Structural recovery for authored `cRCutScene::AI` on the exact 0x5c-byte
`CutScene` embedded at `Snail +0x1958`.

Recovered relationships:

- `CutScene::state` drives the `1 -> 2 -> 8 -> 9` intro path, `5 -> 6 -> 7`
  completion path, and `10 -> 11 -> 12` death path.
- `camera_mode`, `live_matrix`, `progress`, `progress_step`, and
  `force_camera_update` are confirmed members on the `CutScene` inline object.
- `Snail::snail_hotspots_world[12]` is the completion
  skid-stop source and `snail_hotspots_world[18]` is the recurring intro-talk
  look-at anchor.
- Completion initializes the embedded `SubgameRuntime::completion` immediately on the state `5`
  entry handoff while entering state `6`, then plays SFX `46`.
- Death entry plays voice set `3`, releases snail weapons, and later falls back
  to voice set `11` if `initialize_subgoldy_death` does not consume the gate.
- Completion entry writes the invincible-shell cutscene roll pair at
  `presentation +0x192c/+0x1930` (`cutscene_roll_progress/step`), not the
  regular wobble phase fields at `+0x15bc/+0x15c0`.

Closed ownership:

- `Player +0x200` is the exact `Cameraman::live_matrix` at the head of the
  embedded 0xd8-byte `Player::cameraman` owner. States `6`, `8`, and `11` use it
  as their camera blend source.
- `g_game_base +0x2247f8` is
  `SubgameRuntime::level_definition.parcel_count`, the same total consumed by
  parcel placement and the collision HUD path. State `5` compares it with
  `Player::parcels_collected` for the perfect-delivery flag.

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
the byte on the intro close-in camera leg. Cross-port `cRClickStart` ownership
now proves this is `Player::click_start.hide_prompt` at child `+0xa8`; clearing
it lets the prompt be revealed. The stable global reference name remains
unchanged. Masked audit is `34 ok / 0 unresolved / 2 mismatch`.

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

2026-07-11 authored-owner closure: Android `cRCutScene::AI` uses the same
owner offsets (`state +0x0c`, matrix `+0x10`, progress `+0x50/+0x54`, update
gate `+0x58`) and the same intro/completion/death state families. iOS v1.5
places `cRCutScene::AI` in `SubGame.o`. The shared type is now the exact 0x5c
`CutScene`; the old analysis headers incorrectly padded it to 0x64 and thereby
misattributed the following `Player::parcels_collected` word at `Player+0x4338`
to a nonexistent CutScene tail.

2026-07-12 camera/parcel ownership and source-shape pass:

- The intro latch is now expressed through
  `GameRoot::subgame.embedded_player()->click_start.hide_prompt`, and all four
  raw `Player +0x200` matrix copies now use
  `Player::cameraman.live_matrix`. Both are codegen-neutral owner recovery.
- A real `Vector3 operator-` spelling plus the existing scaled-vector operators
  recovers the native intro pushback temporary. Keeping a distinct completion
  camera matrix recovers the exact native `0xe8` stack frame rather than the
  prior `0xa8` candidate frame.
- Limiting `Player::parcels_collected` to the two completion-mode branches
  recovers the native mode-first load schedule. The scratch retains the direct
  `g_game_base +0x2247f8` spelling because the fully typed member expression
  changes register lifetime and regresses the focused result; the owner itself
  is no longer unresolved.
- Focused Wibo improves from 68.97% (481/505 instructions, prefix 0, 55 clean
  masked operands) to 72.53% (496/505, prefix 10, 57 clean masked operands).
  The sole masked mismatch remains the compiler-emitted jump-table identity.
  Chained completion-vector algebra regressed, while a named perfect-delivery
  boolean was codegen-neutral; neither probe was retained.
