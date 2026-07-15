# update_new_game_menu

Authored `cRIntro::AI()` owner method retained under the stable Windows harness
name `update_new_game_menu` @ `0x417eb0`.

Current match: 100.00%, 273/273 instructions, prefix 273/273, with all 62
masked operands resolved and clean.

Recovered relationships:

- menu buttons at `+0x30/+0x34/+0x38/+0x3c/+0x40/+0x44` dispatch postal,
  time trial, challenge, tutorial, help, and back respectively;
- the text-input wakeup also accepts the shared live input confirm edge
  `GameInput.input.pressed_buttons & 0x4000`;
- `replay_attract_bank_cursor` at `+0x00` rotates through `0..4`, but only
  banks `0`, `1`, and `3` probe replay/high-score records;
- record bases `game+0x6ffae8`, `game+0x85c128`, and `game+0x9b8768` are
  0x1fac0-stride persistent record banks, with selected modes `0`, `1`, and
  `4`;
- the menu seeds the same replay-launch scratch as high-score and click-start:
  `game+0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`;
- the launch return state is `2` from the new-game attract path and `18` from
  the high-score browser path.

Source-shape note: the seven teardown calls now use the recovered
`Intro::destroy_new_game_menu` name. Native passes `this` in `ECX`, and Android
independently names the authored method `cRIntro::UnInit()`. Its body is folded
with `MainMenu::destroy_main_menu` at the same Windows address.

The earlier residual came from spelling the replay-attract cases as an
`if/else` chain and retaining one root pointer across each button dispatch.

2026-07-10 owner closure: the three replay bases are now typed as
`SubHighScore::postal_records`, `survival_records`, and
`time_trial_route_records`; replay handoff fields and `level_mode` are owned by
the same embedded `SubgameRuntime`. Removing the synthetic cross-root game view
changes VC6 reload scheduling slightly, so the honest focused score moves from
63.94% to 63.06%.

2026-07-12 authored-owner correction: the symbol-bearing ARM body is
`cRIntro::AI()`. It checks the same widget activation bits, dispatches the same
mode/help/back states, and drives the same owner-local random replay-attract
loop; its additional Pro-Challenge branch is port-specific.

## 2026-07-12 exact source-shape recovery

- Direct `g_game` writes preserve native's independent global reloads across
  each early-return button branch; a retained local root pointer was the source
  of the old scheduling residual.
- A real `switch` on `replay_attract_bank_cursor` produces native's `0/1/3`
  subtract-and-decrement dispatch and case layout. Preincrementing the cursor
  in its wrap test recovers the native store-before-compare sequence.
- The replay search is a `do` loop while the selected record is null and the
  attempt count is below 1000. Expressing the post-loop path as
  `if (attempts < 1000)` for the launch, followed by the shared miss timer
  reset, naturally produces native's shared failure tail.

Together these ordinary control-flow and ownership forms raise the method from
63.06% (263/273, prefix 41) to exact 100.00% (273/273, prefix 273), with 62
clean operands. No padding, volatile barriers, dummy dependencies, inline
assembly, or register-forcing constructs are used.

## 2026-07-13 replay-bank root cleanup

The attract loop now uses the same typed `g_game` graph as the button paths:
its selected record, three owned `SubHighScore` banks, replay-launch slot, and
`level_mode` all belong to `SubgameRuntime`. Removing the remaining raw
`GameRoot` casts preserves native's independent loads and keeps the method
exact at 273/273 with all 62 operands clean.

## 2026-07-15 Binary Ninja Intro replay

The repeatable root sync now installs the exact `Intro` receiver used by the
authored `cRIntro::AI()` body. Its refreshed artifact retains the six named
buttons, replay timers, and bank cursor while also exposing the canonical
player, SubHighScore, and replay-handoff graph. This is analysis replay only;
the exact 273/273 matcher source does not change.
