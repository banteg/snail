# update_completion_screen

`update_completion_screen` @ `0x4067e0` is the Yes/No exit-prompt state
machine. It is driven by `update_frontend_state_machine` on the prompt object at
`game+0x4f3ac`, while `initialize_completion_screen` initializes the separate
delivery-complete result object at `game+0x12e6df0`.

Exact match: 100.00%, 207/207 instructions, 69 masked operands all resolved.

Source-shape notes:

- The native switch subtracts 2 from `state` and uses the jump table at
  `0x406b90`.
- VC6 only matched after the case bodies were ordered by native block layout:
  states `9, 10, 11, 2, 7, 3, 4, 8`.
- `destroy_main_menu` still wants member-call spelling at this callsite so that
  `ecx` is prepared with the main-menu owner even though the helper itself
  ignores `this`.

Recovered relationships:

- State 2 completes the active subgame and either returns to a dirty frontend
  state or restarts challenge/time-trial style modes.
- The state 2 and 11 gates check
  `GameRoot::players[0].high_score_entry_pending` at `+0x30d`, not the
  player's ordinary redispatch byte at `+0x30c`.
- State 3 returns through `GameRoot::subgame.replay_launch_return_state` at
  root `+0x1066bf0`, matching the replay-launch handoff recovered from
  high-score and new-game menu paths.
- State 8 launches the outbound `Alpha72.url` resource helper, clears
  `game+0x568`, and returns to frontend state 0.
- The trailing No button always restores `previous_frontend_state` and clears
  `game+0x568`.

2026-07-11 owner closure: the synthetic cross-root completion view was removed.
The prompt is `GameRoot::exit_controller`; pause state, galaxy, replay, and
subgame methods belong to `GameRoot::subgame`; menu objects and the link latch
belong directly to `GameRoot`. The complete rewrite remains exact at 207/207.

Android and iOS retain the authored owner as `cRExit::AI()`. The primary
`Exit` rename is codegen-neutral and keeps all 69 operands clean.
